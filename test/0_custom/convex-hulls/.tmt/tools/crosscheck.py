#!/usr/bin/env python3
"""Independent support-edge oracle, metamorphic and live-library checks.
Run: python3 tools/crosscheck.py /tmp/hulls-reference /tmp/hulls-library
No geometry library or monotone-chain implementation is used by the oracle.
"""
from pathlib import Path
import hashlib
import itertools
import json
import random
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def cross(a, b, c):
    return (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0])


def distance(a, b):
    return (a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2


def oracle(raw):
    points = sorted(set(raw))
    if len(points) <= 1:
        return [points[:], points[:], points[:], points[:]]
    first, last = points[0], points[-1]
    if all(cross(first, last, point) == 0 for point in points):
        ends = [first, last]
        return [ends, points + points[-2:0:-1], ends, ends]
    # A strict directed edge supports every point on its left. Its endpoints
    # must be the extremes of all points on that supporting line.
    successor = {}
    for a, b in itertools.permutations(points, 2):
        valid = True
        for p in points:
            turn = cross(a, b, p)
            projection = (p[0] - a[0]) * (b[0] - a[0]) + (p[1] - a[1]) * (b[1] - a[1])
            if turn < 0 or (turn == 0 and not 0 <= projection <= distance(a, b)):
                valid = False
                break
        if valid:
            assert a not in successor
            successor[a] = b
    hull = [first]
    while successor[hull[-1]] != first:
        hull.append(successor[hull[-1]])
        assert len(hull) <= len(points)
    boundary = []
    for a, b in zip(hull, hull[1:] + hull[:1]):
        on_edge = [p for p in points if cross(a, b, p) == 0
                   and 0 <= (p[0] - a[0]) * (b[0] - a[0]) + (p[1] - a[1]) * (b[1] - a[1]) < distance(a, b)]
        boundary.extend(sorted(on_edge, key=lambda p: distance(a, p)))
    index = hull.index(last)
    lower = hull[:index + 1]
    upper = [first] + hull[:index - 1:-1]
    return [hull, boundary, lower, upper]


def encode(points):
    return str(len(points)) + '\n' + ''.join(f'{x} {y}\n' for x, y in points)


def decode(text):
    data = list(map(int, text.split()))
    answer = []
    offset = 0
    for _ in range(4):
        length = data[offset]
        offset += 1
        assert 0 <= length <= 400000
        answer.append([tuple(data[j:j + 2]) for j in range(offset, offset + 2 * length, 2)])
        offset += 2 * length
    assert offset == len(data)
    return answer


def run(exe, points):
    process = subprocess.run([str(exe)], input=encode(points), text=True, capture_output=True, check=True)
    return decode(process.stdout)


def read_case(path):
    data = list(map(int, path.read_text().split()))
    assert len(data) == 1 + 2 * data[0]
    return [tuple(data[j:j + 2]) for j in range(1, len(data), 2)]


def main():
    reference, library = map(lambda name: Path(name).resolve(), sys.argv[1:3])
    rng = random.Random(6027)
    grid = list(itertools.product(range(-1, 2), repeat=2))
    cases = [[point for i, point in enumerate(grid) if mask >> i & 1] for mask in range(512)]
    for _ in range(150):
        cases.append([(rng.randint(-5, 5), rng.randint(-5, 5)) for _ in range(rng.randint(0, 14))])
    cases.extend(read_case(path) for path in sorted((ROOT / 'generator/manual').glob('*.in')))
    failures = []
    comparisons = 0
    for i, points in enumerate(cases):
        transforms = [points]
        if i >= 512:
            shuffled = points[:]
            rng.shuffle(shuffled)
            transforms += [shuffled, [(x + 31, y - 47) for x, y in points],
                           [(-y, x) for x, y in points], [(y, x) for x, y in points]]
        for transformed in transforms:
            if any(max(abs(x), abs(y)) > 100000000 for x, y in transformed):
                continue
            expected = oracle(transformed)
            actual = run(reference, transformed)
            assert actual == expected, ('reference', i, transformed, actual, expected)
            comparisons += 1
            try:
                actual = run(library, transformed)
                if actual != expected:
                    failures.append({'points': transformed, 'actual': actual, 'expected': expected})
            except subprocess.CalledProcessError as error:
                failures.append({'points': transformed, 'exit_code': error.returncode})
    inputs = sorted((ROOT / 'testcases').glob('*.in'))
    largest_hull = 0
    for path in inputs:
        points = read_case(path)
        expected_text = path.with_suffix('.ans').read_text()
        process = subprocess.run([str(reference)], input=path.read_text(), text=True, capture_output=True, check=True)
        assert process.stdout.split() == expected_text.split(), path.name
        expected = decode(expected_text)
        largest_hull = max(largest_hull, len(expected[0]))
        actual = run(library, points)
        if actual != expected:
            failures.append({'testcase': path.name, 'first_differing_block': next(i for i in range(4) if actual[i] != expected[i])})
        if path.name.startswith('1-samples-'):
            number = int(path.stem.rsplit('-', 1)[1])
            sample = (ROOT / f'generator/manual/s{number}.ans').read_text()
            assert expected_text.split() == sample.split(), path.name
    for name, (mtime, digest) in json.loads((ROOT / 'tools/statement-snapshot.json').read_text()).items():
        path = ROOT / name
        assert path.stat().st_mtime_ns == mtime
        assert hashlib.sha256(path.read_bytes()).hexdigest() == digest
    report = {'oracle_configurations': len(cases), 'oracle_and_metamorphic_comparisons': comparisons,
              'formal_cases': len(inputs), 'largest_strict_hull': largest_hull,
              'input_bytes': sum(p.stat().st_size for p in inputs),
              'answer_bytes': sum(p.with_suffix('.ans').stat().st_size for p in inputs),
              'largest_answer_bytes': max(p.with_suffix('.ans').stat().st_size for p in inputs),
              'statement_content_and_mtimes_unchanged': True, 'library_failures': failures}
    (ROOT / 'tools/crosscheck-report.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
