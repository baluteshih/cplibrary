#!/usr/bin/env python3
"""Pair-sum oracle using exact gift wrapping, plus metamorphic/support checks."""
from pathlib import Path
import hashlib
import json
import random
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def cross(a, b, c):
    return (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0])


def distance(a, b):
    return (b[0] - a[0]) ** 2 + (b[1] - a[1]) ** 2


def gift_wrap(points):
    points = sorted(set(points))
    if len(points) <= 1:
        return points
    start = points[0]
    result = []
    current = start
    while True:
        result.append(current)
        candidate = next(p for p in points if p != current)
        for p in points:
            turn = cross(current, candidate, p)
            if turn < 0 or (turn == 0 and distance(current, p) > distance(current, candidate)):
                candidate = p
        current = candidate
        if current == start:
            return result
        assert len(result) <= len(points)


def oracle(a, b):
    return gift_wrap([(x + u, y + v) for x, y in a for u, v in b])


def encode(a, b):
    return f'{len(a)} {len(b)}\n' + ''.join(f'{x} {y}\n' for x, y in a + b)


def decode(text):
    values = list(map(int, text.split()))
    n = values[0]
    assert 1 <= n <= 200000 and len(values) == 1 + 2 * n
    return [tuple(values[i:i + 2]) for i in range(1, len(values), 2)]


def run(exe, a, b):
    result = subprocess.run([str(exe)], input=encode(a, b), text=True, capture_output=True, check=True)
    return decode(result.stdout)


def read_case(path):
    values = list(map(int, path.read_text().split()))
    n, m = values[:2]
    points = [tuple(values[i:i + 2]) for i in range(2, len(values), 2)]
    assert len(points) == n + m
    return points[:n], points[n:]


def canonicalize(points):
    if len(points) <= 2:
        return sorted(points)
    area = sum(x * v - y * u for (x, y), (u, v) in zip(points, points[1:] + points[:1]))
    if area < 0:
        points = points[::-1]
    start = points.index(min(points))
    return points[start:] + points[:start]


def main():
    exe = Path(sys.argv[1]).resolve()
    rng = random.Random(314159)
    cases = [read_case(p) for p in sorted((ROOT / 'generator/manual').glob('*.in'))]
    for _ in range(240):
        a = [(rng.randint(-9, 9), rng.randint(-9, 9)) for _ in range(rng.randint(1, 10))]
        b = [(rng.randint(-9, 9), rng.randint(-9, 9)) for _ in range(rng.randint(1, 10))]
        cases.append((a, b))
    comparisons = 0
    for i, (a, b) in enumerate(cases):
        expected = oracle(a, b)
        assert run(exe, a, b) == expected, (i, a, b)
        assert run(exe, b, a) == expected, (i, 'commutativity')
        comparisons += 2
        aa, bb = a[:], b[:]
        rng.shuffle(aa)
        rng.shuffle(bb)
        assert run(exe, aa, bb) == expected, (i, 'permutation')
        comparisons += 1
        if all(max(abs(x + 13), abs(y - 17)) <= 100000000 for x, y in a):
            shifted = [(x + 13, y - 17) for x, y in a]
            translated_answer = [(x + 13, y - 17) for x, y in expected]
            assert run(exe, shifted, b) == translated_answer, (i, 'translation')
            comparisons += 1
        reflected = canonicalize([(-x, y) for x, y in expected])
        assert run(exe, [(-x, y) for x, y in a], [(-x, y) for x, y in b]) == reflected, (i, 'reflection')
        comparisons += 1
    formal = sorted((ROOT / 'testcases').glob('*.in'))
    largest_hull = 0
    support_checks = 0
    for path in formal:
        a, b = read_case(path)
        expected = decode(path.with_suffix('.ans').read_text())
        actual = run(exe, a, b)
        assert actual == expected, path.name
        assert run(exe, b, a) == actual, (path.name, 'swap')
        assert actual[0] == min(actual) and len(set(actual)) == len(actual), path.name
        assert all(max(abs(x), abs(y)) <= 200000000 for x, y in actual), path.name
        if len(actual) >= 3:
            assert all(cross(actual[i - 2], actual[i - 1], actual[i]) > 0 for i in range(len(actual))), path.name
        if len(a) * len(b) <= 10000:
            assert oracle(a, b) == actual, path.name
        # Support identity in multiple exact directions, including edge normals.
        directions = [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (17, -31)]
        if len(actual) > 1:
            for i in sorted(set([0, len(actual) // 3, len(actual) - 1])):
                p, q = actual[i], actual[(i + 1) % len(actual)]
                directions.append((q[1] - p[1], p[0] - q[0]))
        for dx, dy in directions:
            support = lambda points: max(x * dx + y * dy for x, y in points)
            assert support(actual) == support(a) + support(b), (path.name, dx, dy)
            support_checks += 1
        largest_hull = max(largest_hull, len(actual))
    if formal:
        assert (ROOT / 'testcases/1-samples-1.ans').read_text().split() == (ROOT / 'generator/manual/s1.ans').read_text().split()
    for name, (mtime, digest) in json.loads((ROOT / 'tools/statement-snapshot.json').read_text()).items():
        path = ROOT / name
        assert path.stat().st_mtime_ns == mtime and hashlib.sha256(path.read_bytes()).hexdigest() == digest
    report = {'oracle_configurations': len(cases), 'oracle_and_metamorphic_comparisons': comparisons,
              'formal_cases': len(formal), 'formal_support_checks': support_checks,
              'largest_output_hull': largest_hull,
              'input_bytes': sum(p.stat().st_size for p in formal),
              'answer_bytes': sum(p.with_suffix('.ans').stat().st_size for p in formal),
              'largest_answer_bytes': max((p.with_suffix('.ans').stat().st_size for p in formal), default=0),
              'statement_content_and_mtimes_unchanged': True}
    (ROOT / 'tools/crosscheck-report.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
