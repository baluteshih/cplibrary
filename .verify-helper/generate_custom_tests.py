#!/usr/bin/env python3
"""
Custom Testcase Pre-run Generator for online-judge-verify-helper.

Scans test files (*.test.cpp) for custom generator directives:
  #define PROBLEM "https://..."
  #define GENERATOR "path/to/gen.py" (or .cpp)
  #define REFERENCE "path/to/ref.cpp" (optional)
  #define TESTCASES_DIR "path/to/testcases" (optional)

If test cases already exist in .verify-helper/cache/<md5>/test and the generator/test
files haven't changed (checked via SHA256 fingerprint), generation is skipped.
Otherwise, test cases are generated and placed into .verify-helper/cache/<md5>/test,
which oj-verify will automatically pick up without downloading.
"""

import hashlib
import os
import re
import shlex
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Optional


def get_cxx_compiler_info() -> tuple[str, List[str]]:
    cxx = os.environ.get("CXX", "g++")
    flags = ["-std=c++23", "-O2", "-I."]

    # Read config.toml if available
    config_path = Path(".verify-helper/config.toml")
    if config_path.exists():
        try:
            import tomllib  # Python 3.11+
        except ImportError:
            try:
                import tomli as tomllib
            except ImportError:
                tomllib = None

        if tomllib:
            try:
                cfg = tomllib.loads(config_path.read_text())
                envs = cfg.get("languages", {}).get("cpp", {}).get("environments", [])
                if envs:
                    if "CXX" not in os.environ:
                        cxx = envs[0].get("CXX", cxx)
                    flags = envs[0].get("CXXFLAGS", flags)
                    if "-I." not in flags and "-I" not in flags:
                        flags.append("-I.")
            except Exception as e:
                print(f"[Pre-Verify] Warning: failed to parse config.toml: {e}", file=sys.stderr)

    return cxx, flags


def compile_cpp(src_path: Path, output_binary: Path) -> bool:
    cxx, flags = get_cxx_compiler_info()
    cmd = [cxx] + flags + ["-o", str(output_binary), str(src_path)]
    print(f"[Pre-Verify] Compiling {src_path} -> {output_binary}...")
    res = subprocess.run(cmd)
    return res.returncode == 0


def parse_directives(test_file: Path) -> Dict[str, str]:
    directives = {}
    content = test_file.read_text(errors="ignore")

    # Match #define KEY "value" or #define KEY value
    define_pattern = re.compile(r'^\s*#define\s+([A-Za-z0-9_]+)\s*(?:["\']([^"\']*)["\']|(\S+))?', re.MULTILINE)
    for match in define_pattern.finditer(content):
        key = match.group(1)
        val = match.group(2) if match.group(2) is not None else match.group(3) or ""
        directives[key] = val.strip()

    # Also match // verification-helper: KEY value
    helper_pattern = re.compile(r'\b(?:verify|verification)-helper:\s*([A-Za-z0-9_]+)\s*(.*)?$', re.MULTILINE)
    for match in helper_pattern.finditer(content):
        key = match.group(1)
        val = (match.group(2) or "").strip().strip('"\'')
        directives[key] = val

    return directives


def compute_fingerprint(files: List[Path]) -> str:
    h = hashlib.sha256()
    for f in sorted(files):
        if f.exists() and f.is_file():
            h.update(str(f).encode())
            h.update(f.read_bytes())
    return h.hexdigest()


def process_test_file(test_file: Path, root_dir: Path) -> bool:
    directives = parse_directives(test_file)
    problem_url = directives.get("PROBLEM")
    generator_rel = directives.get("GENERATOR")
    testcases_dir_rel = directives.get("TESTCASES_DIR")
    reference_rel = directives.get("REFERENCE")

    if not problem_url or (not generator_rel and not testcases_dir_rel):
        return True  # Not a custom generator test

    # oj-verify's cache directory convention:
    url_md5 = hashlib.md5(problem_url.encode()).hexdigest()
    cache_base = root_dir / ".verify-helper" / "cache" / url_md5
    test_dir = cache_base / "test"
    fingerprint_file = cache_base / ".generator_fingerprint"

    # Dependency tracking for fingerprint
    dep_files = [test_file]
    gen_path: Optional[Path] = None
    ref_path: Optional[Path] = None

    if generator_rel:
        gen_path = (test_file.parent / generator_rel).resolve()
        if not gen_path.exists():
            gen_path = (root_dir / generator_rel).resolve()
        dep_files.append(gen_path)

    if reference_rel:
        ref_path = (test_file.parent / reference_rel).resolve()
        if not ref_path.exists():
            ref_path = (root_dir / reference_rel).resolve()
        dep_files.append(ref_path)

    # Check cache validity
    current_fingerprint = compute_fingerprint(dep_files)
    if (
        test_dir.exists()
        and any(test_dir.glob("*.in"))
        and any(test_dir.glob("*.out"))
        and fingerprint_file.exists()
        and fingerprint_file.read_text().strip() == current_fingerprint
    ):
        print(f"[Pre-Verify] Cache hit for {test_file.relative_to(root_dir)}. Skipping generation.")
        return True

    print(f"[Pre-Verify] Generating custom testcases for {test_file.relative_to(root_dir)}...")
    if test_dir.exists():
        shutil.rmtree(test_dir)
    test_dir.mkdir(parents=True, exist_ok=True)

    # Mode 1: Static testcases directory
    if testcases_dir_rel:
        source_dir = (test_file.parent / testcases_dir_rel).resolve()
        if not source_dir.exists():
            source_dir = (root_dir / testcases_dir_rel).resolve()
        if not source_dir.exists():
            print(f"[Pre-Verify] Error: TESTCASES_DIR '{source_dir}' not found!", file=sys.stderr)
            return False

        for f in source_dir.glob("*"):
            if f.suffix in [".in", ".out"]:
                shutil.copy2(f, test_dir / f.name)

    # Mode 2: Dynamic Generator
    elif gen_path and gen_path.exists():
        gen_exec: Optional[Path] = None
        temp_binaries: List[Path] = []

        try:
            if gen_path.suffix == ".py":
                gen_cmd_prefix = [sys.executable, str(gen_path)]
            elif gen_path.suffix in [".cpp", ".cc"]:
                gen_exec = cache_base / "generator.bin"
                temp_binaries.append(gen_exec)
                if not compile_cpp(gen_path, gen_exec):
                    print(f"[Pre-Verify] Error compiling generator {gen_path}", file=sys.stderr)
                    return False
                gen_cmd_prefix = [str(gen_exec)]
            else:
                gen_cmd_prefix = [str(gen_path)]

            # Run generator passing target directory
            # If generator accepts target directory, it can write test_*.in / test_*.out directly
            print(f"[Pre-Verify] Running generator: {' '.join(gen_cmd_prefix)} {test_dir}...")
            res = subprocess.run(gen_cmd_prefix + [str(test_dir)])
            if res.returncode != 0:
                print(f"[Pre-Verify] Generator returned non-zero exit code: {res.returncode}", file=sys.stderr)
                return False

            # Check if .out files are missing and need reference solver
            in_files = sorted(test_dir.glob("*.in"))
            if not in_files:
                print(f"[Pre-Verify] Error: No .in files were produced in {test_dir}", file=sys.stderr)
                return False

            out_files = list(test_dir.glob("*.out"))
            if len(out_files) < len(in_files):
                # We need to generate matching .out files using reference or test_file
                solver_src = ref_path if (ref_path and ref_path.exists()) else test_file
                solver_bin = cache_base / "solver.bin"
                temp_binaries.append(solver_bin)

                print(f"[Pre-Verify] Producing .out files using {solver_src.name}...")
                if not compile_cpp(solver_src, solver_bin):
                    print(f"[Pre-Verify] Error compiling solver {solver_src}", file=sys.stderr)
                    return False

                for in_f in in_files:
                    out_f = in_f.with_suffix(".out")
                    with open(in_f, "rb") as fin, open(out_f, "wb") as fout:
                        run_res = subprocess.run([str(solver_bin)], stdin=fin, stdout=fout)
                        if run_res.returncode != 0:
                            print(f"[Pre-Verify] Error running solver on {in_f.name}", file=sys.stderr)
                            return False

        finally:
            for tb in temp_binaries:
                if tb.exists():
                    tb.unlink()

    else:
        print(f"[Pre-Verify] Error: Generator file '{generator_rel}' not found!", file=sys.stderr)
        return False

    # Save fingerprint upon success
    fingerprint_file.write_text(current_fingerprint)
    in_count = len(list(test_dir.glob("*.in")))
    out_count = len(list(test_dir.glob("*.out")))
    print(f"[Pre-Verify] Done! Created {in_count} test inputs and {out_count} test outputs in {test_dir}.")
    return True


def main():
    root_dir = Path.cwd()
    test_files = sorted(root_dir.glob("test/**/*.test.cpp"))
    success = True
    processed = 0

    for tf in test_files:
        directives = parse_directives(tf)
        if "GENERATOR" in directives or "TESTCASES_DIR" in directives:
            processed += 1
            if not process_test_file(tf, root_dir):
                success = False

    if processed == 0:
        print("[Pre-Verify] No custom generator directives found.")
    else:
        print(f"[Pre-Verify] Processed {processed} custom test file(s).")

    if not success:
        sys.exit(1)


if __name__ == "__main__":
    main()
