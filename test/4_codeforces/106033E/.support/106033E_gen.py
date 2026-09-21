#!/usr/bin/env python3
"""
Official testcase generator for Codeforces Gym 106033E (Education).
Parses test/4_codeforces/data and compiles/executes C++ generators in test/4_codeforces/generators/
matching the exact testcase generation script from NTUPreliminary2025/education.
"""

import os
import shlex
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


def get_cxx_compiler_info() -> tuple[str, list[str]]:
    cxx = os.environ.get("CXX", "g++")
    flags = ["-O2", "-std=c++20"]
    return cxx, flags


def compile_generator(src_path: Path, out_binary: Path, include_dir: Path) -> bool:
    cxx, flags = get_cxx_compiler_info()
    cmd = [cxx] + flags + [f"-I{include_dir}", "-o", str(out_binary), str(src_path)]
    res = subprocess.run(cmd)
    return res.returncode == 0


def generate_all(output_dir: Path):
    output_dir.mkdir(parents=True, exist_ok=True)
    base_dir = Path(__file__).parent
    data_file = base_dir / "data"
    generators_dir = base_dir / "generators"
    samples_dir = base_dir / "samples"
    testlib_include = base_dir  # contains testlib.h

    # 1. Copy official samples
    sample_files = sorted(samples_dir.glob("*.in"))
    for idx, sf in enumerate(sample_files, start=1):
        target = output_dir / f"00_sample_{idx:02d}.in"
        shutil.copy2(sf, target)
    print(f"[Generator] Copied {len(sample_files)} official sample testcases.")

    # 2. Parse data file and generate testcases
    if not data_file.exists():
        print(f"[Generator] Error: {data_file} not found!", file=sys.stderr)
        sys.exit(1)

    with tempfile.TemporaryDirectory() as tempdir:
        tempdir_path = Path(tempdir)
        compiled_bins = {}

        current_testset = "testset"
        case_index = 1
        total_generated = 0

        for raw_line in data_file.read_text().splitlines():
            line = raw_line.strip()
            if not line or line.startswith("#"):
                continue

            if line.startswith("@testset"):
                parts = line.split()
                current_testset = parts[1] if len(parts) > 1 else "testset"
                case_index = 1
                continue

            tokens = shlex.split(line)
            if not tokens:
                continue

            gen_name = tokens[0]
            gen_args = tokens[1:]

            gen_src = generators_dir / f"{gen_name}.cpp"
            if not gen_src.exists():
                print(f"[Generator] Warning: Generator source {gen_src} not found, skipping line: {line}", file=sys.stderr)
                continue

            # Compile generator if not already compiled
            if gen_name not in compiled_bins:
                bin_path = tempdir_path / f"{gen_name}.bin"
                if not compile_generator(gen_src, bin_path, testlib_include):
                    print(f"[Generator] Error compiling {gen_src}", file=sys.stderr)
                    sys.exit(1)
                compiled_bins[gen_name] = bin_path

            bin_path = compiled_bins[gen_name]
            out_case_path = output_dir / f"{current_testset}_{case_index:02d}.in"

            with open(out_case_path, "wb") as fout:
                run_res = subprocess.run([str(bin_path)] + gen_args, stdout=fout)
                if run_res.returncode != 0:
                    print(f"[Generator] Error running {gen_name} with args {gen_args}", file=sys.stderr)
                    sys.exit(1)

            case_index += 1
            total_generated += 1

    print(f"[Generator] Successfully generated {total_generated} test cases according to {data_file.name}.")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 106033E_gen.py <output_directory>", file=sys.stderr)
        sys.exit(1)
    generate_all(Path(sys.argv[1]))
