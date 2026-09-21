"""
Custom Testcase Pre-run Generator for online-judge-verify-helper.

Supports:
1. Standard tmt-cli ICPC Problem Packages (Recommended):
   Any directory containing `*.test.cpp`, `problem.yaml`, and `recipe`.
   Runs `tmt gen` to generate, validate, solve, and check testcases,
   then prepares test inputs, expected outputs, and the custom checker
   bridge for oj-verify.

2. Legacy Directives (for simple or backwards-compatible tests):
   #define PROBLEM "https://..."
   #define GENERATOR "gen.py" (or .cpp)
   #define CHECKER "checker.cpp"
   #define TESTCASES_DIR "path/to/testcases"

Cached in .verify-helper/cache/<url_md5>/test to avoid redundant regeneration.
"""

import hashlib
import os
import re
import shlex
import shutil
import subprocess
import sys
from pathlib import Path
from typing import Dict, List, Optional, Set


def patch_oj_verify():
    """
    Patches installed onlinejudge_verify components:
    Passes --judge-command to oj when a custom checker exists in cache.
    """
    try:
        import onlinejudge_verify.verify
        verify_py = Path(onlinejudge_verify.verify.__file__)
        content = verify_py.read_text()
        marker = "# [custom-checker-patch]"
        if marker not in content:
            target = "if isinstance(problem, onlinejudge.service.library_checker.LibraryCheckerProblem):"
            replacement = f"""custom_checker = directory / 'checker'
        if custom_checker.exists():
            command += ['--judge-command', str(custom_checker.resolve())]  {marker}
        {target}"""
            if target in content:
                verify_py.write_text(content.replace(target, replacement, 1))
                print("[Pre-Verify] Enabled custom checker support in onlinejudge_verify.")
    except Exception as e:
        print(f"[Pre-Verify] Note: Could not auto-patch onlinejudge_verify.verify ({e}).", file=sys.stderr)


def get_cxx_compiler_info() -> tuple[str, List[str]]:
    cxx = os.environ.get("CXX", "g++")
    flags = ["-std=c++20", "-O2", "-I."]

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


def compile_cpp(src_path: Path, output_binary: Path, extra_include: Optional[Path] = None) -> bool:
    cxx, flags = get_cxx_compiler_info()
    includes = [f"-I{src_path.parent}"]
    if extra_include and extra_include.exists():
        includes.append(f"-I{extra_include.resolve()}")
    cmd = [cxx] + flags + includes + ["-o", str(output_binary), str(src_path)]
    print(f"[Pre-Verify] Compiling {src_path.name} -> {output_binary.name}...")
    res = subprocess.run(cmd)
    return res.returncode == 0


def ensure_tmt_cli(root_dir: Path) -> Optional[List[str]]:
    """Returns the command to execute tmt-cli, cloning it outside the workspace if necessary."""
    tmt_bin = shutil.which("tmt")
    if tmt_bin:
        return [tmt_bin]

    external_candidates = [
        Path("/tmp/tmt-cli"),
        Path.home() / ".cache" / "tmt-cli",
        Path.home() / ".local" / "share" / "tmt-cli",
    ]
    for c in external_candidates:
        script = c / "tmt.py"
        if script.exists():
            return [sys.executable, str(script)]

    target_dir = Path("/tmp/tmt-cli")
    target_script = target_dir / "tmt.py"
    print(f"[Pre-Verify] tmt-cli not found. Cloning into {target_dir}...")
    try:
        target_dir.parent.mkdir(parents=True, exist_ok=True)
        res = subprocess.run(
            ["git", "clone", "--depth", "1", "https://github.com/Task-Management-Tools/tmt-cli.git", str(target_dir)],
            capture_output=True,
            text=True,
        )
        if res.returncode == 0 and target_script.exists():
            print("[Pre-Verify] Successfully cloned tmt-cli.")
            return [sys.executable, str(target_script)]
        else:
            print(f"[Pre-Verify] Error cloning tmt-cli: {res.stderr}", file=sys.stderr)
    except Exception as e:
        print(f"[Pre-Verify] Failed to auto-clone tmt-cli: {e}", file=sys.stderr)

    return None


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


def get_recursive_dependencies(file_path: Path, root_dir: Path) -> Set[Path]:
    """Recursively resolves all #include dependencies within the repository."""
    root_resolved = root_dir.resolve()
    visited: Set[Path] = set()
    to_visit: List[Path] = [file_path.resolve()]

    while to_visit:
        curr = to_visit.pop()
        if curr in visited:
            continue
        visited.add(curr)

        try:
            content = curr.read_text(errors="ignore")
        except Exception:
            continue

        for line in content.splitlines():
            m = re.match(r'#include\s*["<](.*)[">]', line.strip())
            if m:
                inc_str = m.group(1)
                candidates = [
                    curr.parent / inc_str,
                    root_resolved / inc_str,
                ]
                for cand in candidates:
                    try:
                        cand_res = cand.resolve()
                        if cand_res.is_file() and (cand_res == root_resolved or root_resolved in cand_res.parents):
                            if cand_res not in visited:
                                to_visit.append(cand_res)
                            break
                    except Exception:
                        pass

    return visited


def is_verification_needed(test_file: Path, pkg_dir: Path, root_dir: Path) -> bool:
    """
    Checks if this test needs to be run by checking Git modification history
    against timestamps recorded in timestamps.remote.json / timestamps.local.json.
    Recursively tracks all included library dependencies.
    """
    ts_file = root_dir / ".verify-helper" / "timestamps.remote.json"
    if not ts_file.exists():
        ts_file = root_dir / ".verify-helper" / "timestamps.local.json"
    if not ts_file.exists():
        return True

    try:
        import json
        with open(ts_file, "r") as f:
            ts_data = json.load(f)
    except Exception:
        return True

    rel_test_str = str(test_file.resolve().relative_to(root_dir.resolve()))
    verified_time_str = ts_data.get(rel_test_str)
    if not verified_time_str:
        return True

    try:
        from datetime import datetime
        verified_dt = datetime.strptime(verified_time_str, "%Y-%m-%d %H:%M:%S %z")
    except Exception:
        return True

    # Recursively resolve all library dependencies of test_file
    root_resolved = root_dir.resolve()
    dep_files = get_recursive_dependencies(test_file, root_resolved)
    paths_to_track = [str(d.relative_to(root_resolved)) for d in dep_files]
    paths_to_track.append(str(pkg_dir.resolve().relative_to(root_resolved)))

    try:
        status_res = subprocess.run(
            ["git", "status", "--porcelain", "--"] + paths_to_track,
            cwd=root_dir,
            capture_output=True,
            text=True,
            check=False,
        )
        if status_res.returncode == 0 and status_res.stdout.strip():
            return True
    except Exception:
        return True

    try:
        log_res = subprocess.run(
            ["git", "log", "-1", "--date=iso", "--pretty=%ad", "--"] + paths_to_track,
            cwd=root_dir,
            capture_output=True,
            text=True,
            check=False,
        )
        if log_res.returncode != 0 or not log_res.stdout.strip():
            return True
        last_commit_dt = datetime.strptime(log_res.stdout.strip(), "%Y-%m-%d %H:%M:%S %z")
        if last_commit_dt <= verified_dt:
            return False
    except Exception:
        return True

    return True


def process_tmt_problem(test_file: Path, root_dir: Path, problem_url: str, pkg_dir: Optional[Path] = None) -> bool:
    if pkg_dir is None:
        pkg_dir = (test_file.parent / ".tmt") if (test_file.parent / ".tmt").exists() else test_file.parent
    url_md5 = hashlib.md5(problem_url.encode()).hexdigest()
    cache_base = root_dir / ".verify-helper" / "cache" / url_md5
    test_dir = cache_base / "test"
    fingerprint_file = cache_base / ".tmt_fingerprint"
    hash_json_file = pkg_dir / "testcases" / "hash.json"
    checker_src = pkg_dir / "checker" / "checker.cpp"
    checker_wrapper = cache_base / "checker"

    # 1. Check if already generated in local cache
    dep_files = [
        test_file,
        pkg_dir / "problem.yaml",
        pkg_dir / "compiler.yaml",
        pkg_dir / "recipe",
    ]
    if hash_json_file.exists():
        dep_files.append(hash_json_file)
    if checker_src.exists():
        dep_files.append(checker_src)

    for sub in ("generator", "validator", "checker", "solutions", "include"):
        d = pkg_dir / sub
        if d.exists():
            for f in d.rglob("*"):
                if f.is_file() and "build" not in f.parts and not f.name.startswith("."):
                    dep_files.append(f)

    current_fingerprint = compute_fingerprint(list(set(dep_files)))

    cache_valid = (
        test_dir.exists()
        and any(test_dir.glob("*.in"))
        and (any(test_dir.glob("*.out")) or any(test_dir.glob("*.ans")))
        and fingerprint_file.exists()
        and fingerprint_file.read_text().strip() == current_fingerprint
    )
    if checker_src.exists() and not checker_wrapper.exists():
        cache_valid = False

    if cache_valid:
        print(f"[Pre-Verify] Cache hit for tmt package at {pkg_dir.relative_to(root_dir)}. Skipping generation.")
        return True

    # 2. Check if oj-verify will skip this test because it's already verified and unchanged in git
    if not is_verification_needed(test_file, pkg_dir, root_dir):
        print(f"[Pre-Verify] {test_file.relative_to(root_dir)} is already verified and unchanged since last verification. Skipping testcase generation.")
        return True

    print(f"[Pre-Verify] Processing tmt-cli problem package at {pkg_dir.relative_to(root_dir)}...")

    tmt_cmd = ensure_tmt_cli(root_dir)
    if not tmt_cmd:
        print("[Pre-Verify] Error: tmt-cli command could not be located or cloned.", file=sys.stderr)
        return False

    # Run tmt gen inside pkg_dir
    print(f"[Pre-Verify] Generating testcases with tmt gen...")
    run_res = subprocess.run(tmt_cmd + ["gen", "-r"], cwd=pkg_dir)
    if run_res.returncode != 0:
        print(f"[Pre-Verify] Error: 'tmt gen' failed in {pkg_dir}", file=sys.stderr)
        return False

    pkg_testcases_dir = pkg_dir / "testcases"
    in_files = sorted(pkg_testcases_dir.glob("*.in"))
    ans_files = sorted(pkg_testcases_dir.glob("*.ans"))
    if not in_files:
        print(f"[Pre-Verify] Error: No .in files generated in {pkg_testcases_dir}", file=sys.stderr)
        return False

    if test_dir.exists():
        shutil.rmtree(test_dir)
    test_dir.mkdir(parents=True, exist_ok=True)

    for inf in in_files:
        shutil.copy2(inf, test_dir / inf.name)
    for ansf in ans_files:
        shutil.copy2(ansf, test_dir / ansf.with_suffix(".out").name)

    # Compile checker and prepare bridge script for oj test
    if checker_src.exists():
        cache_base.mkdir(parents=True, exist_ok=True)
        checker_bin = cache_base / "checker.bin"
        if not compile_cpp(checker_src, checker_bin, extra_include=pkg_dir / "include"):
            print(f"[Pre-Verify] Error compiling checker {checker_src}", file=sys.stderr)
            return False

        # Bridge oj test (--judge-command) to ICPC testlib checker convention:
        # oj test calls:   $0 <input> <actual-output> <expected-output>
        # ICPC testlib:    checker <input> <expected-output> <feedback_dir> < <actual-output>
        # Exit code:       42 (OK) -> 0, 43 (WA) / other -> 1
        wrapper_content = f"""#!/usr/bin/env sh
INPUT="$1"
ACTUAL="$2"
EXPECTED="$3"
FEEDBACK_DIR="$(mktemp -d)"
"{checker_bin.resolve()}" "$INPUT" "$EXPECTED" "$FEEDBACK_DIR" < "$ACTUAL"
RET=$?
rm -rf "$FEEDBACK_DIR"
if [ "$RET" -eq 42 ]; then
    exit 0
else
    exit 1
fi
"""
        checker_wrapper.write_text(wrapper_content)
        checker_wrapper.chmod(0o755)
        print(f"[Pre-Verify] Configured ICPC checker bridge at {checker_wrapper.name}")

    fingerprint_file.write_text(current_fingerprint)
    print(f"[Pre-Verify] Done! Created {len(in_files)} testcases in {test_dir}.")
    return True


def process_legacy_test_file(test_file: Path, root_dir: Path) -> bool:
    directives = parse_directives(test_file)
    problem_url = directives.get("PROBLEM")
    generator_rel = directives.get("GENERATOR")
    testcases_dir_rel = directives.get("TESTCASES_DIR")
    reference_rel = directives.get("REFERENCE")
    checker_rel = directives.get("CHECKER")

    if not problem_url or (not generator_rel and not testcases_dir_rel and not checker_rel):
        return True

    url_md5 = hashlib.md5(problem_url.encode()).hexdigest()
    cache_base = root_dir / ".verify-helper" / "cache" / url_md5
    test_dir = cache_base / "test"
    fingerprint_file = cache_base / ".generator_fingerprint"

    dep_files = [test_file]
    gen_path: Optional[Path] = None
    ref_path: Optional[Path] = None
    checker_path: Optional[Path] = None

    def resolve_rel(rel: Optional[str]) -> Optional[Path]:
        if not rel:
            return None
        for candidate in [
            test_file.parent / rel,
            root_dir / rel,
        ]:
            if candidate.exists():
                return candidate.resolve()
        return (test_file.parent / rel).resolve()

    if generator_rel:
        gen_path = resolve_rel(generator_rel)
        if gen_path:
            dep_files.append(gen_path)

    if reference_rel:
        ref_path = resolve_rel(reference_rel)
        if ref_path:
            dep_files.append(ref_path)

    if checker_rel:
        checker_path = resolve_rel(checker_rel)
        if checker_path:
            dep_files.append(checker_path)

    current_fingerprint = compute_fingerprint(dep_files)
    cache_valid = (
        test_dir.exists()
        and any(test_dir.glob("*.in"))
        and any(test_dir.glob("*.out"))
        and fingerprint_file.exists()
        and fingerprint_file.read_text().strip() == current_fingerprint
    )

    checker_bin = cache_base / "checker"
    if checker_path and checker_path.exists() and not checker_bin.exists():
        cache_valid = False

    if cache_valid:
        print(f"[Pre-Verify] Cache hit for {test_file.relative_to(root_dir)}. Skipping generation.")
        return True

    if checker_path and checker_path.exists():
        cache_base.mkdir(parents=True, exist_ok=True)
        if checker_path.suffix == ".py":
            checker_bin.write_text(f'#!/usr/bin/env sh\nexec {sys.executable} "{checker_path.resolve()}" "$@"\n')
            checker_bin.chmod(0o755)
        elif checker_path.suffix in [".cpp", ".cc"]:
            if not compile_cpp(checker_path, checker_bin):
                return False

    print(f"[Pre-Verify] Generating custom testcases for {test_file.relative_to(root_dir)}...")
    if test_dir.exists():
        shutil.rmtree(test_dir)
    test_dir.mkdir(parents=True, exist_ok=True)

    if testcases_dir_rel:
        source_dir = resolve_rel(testcases_dir_rel)
        if not source_dir or not source_dir.exists():
            return False
        for f in source_dir.glob("*"):
            if f.suffix in [".in", ".out"]:
                shutil.copy2(f, test_dir / f.name)
    elif gen_path and gen_path.exists():
        temp_binaries: List[Path] = []
        try:
            if gen_path.suffix == ".py":
                gen_cmd_prefix = [sys.executable, str(gen_path)]
            elif gen_path.suffix in [".cpp", ".cc"]:
                gen_exec = cache_base / "generator.bin"
                temp_binaries.append(gen_exec)
                if not compile_cpp(gen_path, gen_exec):
                    return False
                gen_cmd_prefix = [str(gen_exec)]
            else:
                gen_cmd_prefix = [str(gen_path)]

            res = subprocess.run(gen_cmd_prefix + [str(test_dir)])
            if res.returncode != 0:
                return False

            in_files = sorted(test_dir.glob("*.in"))
            out_files = list(test_dir.glob("*.out"))
            if len(out_files) < len(in_files):
                solver_src = ref_path if (ref_path and ref_path.exists()) else test_file
                solver_bin = cache_base / "solver.bin"
                temp_binaries.append(solver_bin)
                if not compile_cpp(solver_src, solver_bin):
                    return False
                for in_f in in_files:
                    out_f = in_f.with_suffix(".out")
                    with open(in_f, "rb") as fin, open(out_f, "wb") as fout:
                        subprocess.run([str(solver_bin)], stdin=fin, stdout=fout, check=True)
        finally:
            for tb in temp_binaries:
                if tb.exists():
                    tb.unlink()
    else:
        return False

    fingerprint_file.write_text(current_fingerprint)
    return True


def main():
    root_dir = Path.cwd()
    patch_oj_verify()

    test_files = sorted(root_dir.glob("test/**/*.test.cpp"))
    success = True
    processed = 0

    for tf in test_files:
        directives = parse_directives(tf)
        problem_url = directives.get("PROBLEM")
        if not problem_url:
            continue

        # Detect tmt-cli problem package (.tmt/ subfolder or test folder)
        tmt_pkg_dir: Optional[Path] = None
        if (tf.parent / ".tmt" / "problem.yaml").exists() and (tf.parent / ".tmt" / "recipe").exists():
            tmt_pkg_dir = tf.parent / ".tmt"
        elif (tf.parent / "problem.yaml").exists() and (tf.parent / "recipe").exists():
            tmt_pkg_dir = tf.parent

        if tmt_pkg_dir is not None:
            processed += 1
            if not process_tmt_problem(tf, root_dir, problem_url, tmt_pkg_dir):
                success = False
        elif "GENERATOR" in directives or "TESTCASES_DIR" in directives or "CHECKER" in directives:
            processed += 1
            if not process_legacy_test_file(tf, root_dir):
                success = False

    if processed == 0:
        print("[Pre-Verify] No custom generator/checker directives found.")
    else:
        print(f"[Pre-Verify] Processed {processed} custom test file(s).")

    if not success:
        sys.exit(1)


if __name__ == "__main__":
    main()
