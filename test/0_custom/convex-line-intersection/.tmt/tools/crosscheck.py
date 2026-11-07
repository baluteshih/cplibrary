#!/usr/bin/env python3
"""Exact Fraction oracle, cyclic-shift/translation/reversal checks and formal-data audit."""
from fractions import Fraction
from pathlib import Path
import hashlib
import json
import random
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def cross(a, b):
    return a[0] * b[1] - a[1] * b[0]


def sub(a, b):
    return a[0] - b[0], a[1] - b[1]


def hull(points):
    points = sorted(set(points))
    def chain(sequence):
        result = []
        for p in sequence:
            while len(result) > 1 and cross(sub(result[-1], result[-2]), sub(p, result[-2])) <= 0:
                result.pop()
            result.append(p)
        return result
    return chain(points)[:-1] + chain(points[::-1])[:-1]


def oracle(polygon, query):
    a, b = query
    d = sub(b, a)
    length = d[0] ** 2 + d[1] ** 2
    sides = [cross(d, sub(p, a)) for p in polygon]
    intersections = {}
    for i, p in enumerate(polygon):
        j = (i + 1) % len(polygon)
        if sides[i] == sides[j] == 0:
            return f'EDGE {i}'
        if sides[i] == 0:
            relative = sub(p, a)
            t = Fraction(relative[0] * d[0] + relative[1] * d[1], length)
            intersections[t] = i
        if sides[i] * sides[j] < 0:
            edge = sub(polygon[j], p)
            t = Fraction(cross(sub(p, a), edge), cross(d, edge))
            intersections[t] = i
    if not intersections:
        return 'EMPTY'
    times = sorted(intersections)
    if len(times) == 1:
        return f'POINT {intersections[times[0]]}'
    assert len(times) == 2
    return f'CUT {intersections[times[0]]} {intersections[times[-1]]}'


def encode(polygon, queries):
    return f'{len(polygon)} {len(queries)}\n' + ''.join(f'{x} {y}\n' for x, y in polygon) + ''.join(f'{a[0]} {a[1]} {b[0]} {b[1]}\n' for a, b in queries)


def run(exe, polygon, queries):
    result = subprocess.run([str(exe)], input=encode(polygon, queries), text=True, capture_output=True, check=True)
    lines = result.stdout.splitlines()
    assert len(lines) == len(queries), (len(lines), len(queries))
    return lines


def read_case(path):
    values = list(map(int, path.read_text().split()))
    n, q = values[:2]
    polygon = [tuple(values[i:i + 2]) for i in range(2, 2 + 2 * n, 2)]
    queries = [(tuple(values[i:i + 2]), tuple(values[i + 2:i + 4])) for i in range(2 + 2 * n, len(values), 4)]
    assert len(queries) == q
    return polygon, queries


def main():
    exe = Path(sys.argv[1]).resolve()
    rng = random.Random(271828)
    comparisons = 0
    counts = dict.fromkeys(['EMPTY', 'POINT', 'EDGE', 'CUT'], 0)
    cases = []
    for path in sorted((ROOT / 'generator/manual').glob('*.in')):
        cases.append(read_case(path))
    for _ in range(180):
        polygon = hull([(rng.randint(-15, 15), rng.randint(-15, 15)) for _ in range(20)])
        queries = []
        for i, p in enumerate(polygon):
            nxt = polygon[(i + 1) % len(polygon)]
            queries.append((p, nxt))
            queries.append((p, polygon[(i + 2) % len(polygon)]))
            previous = polygon[(i - 1) % len(polygon)]
            # Tangent through p, directed between the incoming and outgoing edges.
            direction = sub(nxt, previous)
            queries.append((p, (p[0] + direction[0], p[1] + direction[1])))
        for _ in range(80):
            a = rng.randint(-30, 30), rng.randint(-30, 30)
            b = rng.randint(-30, 30), rng.randint(-30, 30)
            if a != b:
                queries.append((a, b))
        cases.append((polygon, queries))
    for index, (polygon, queries) in enumerate(cases):
        transforms = [(polygon, queries)]
        shift = rng.randrange(len(polygon))
        transforms.append((polygon[shift:] + polygon[:shift], queries))
        transforms.append((polygon, [(b, a) for a, b in queries]))
        translated_polygon = [(x + 101, y - 73) for x, y in polygon]
        translated_queries = [((a[0] + 101, a[1] - 73), (b[0] + 101, b[1] - 73)) for a, b in queries]
        if all(max(abs(x), abs(y)) <= 100000000 for x, y in translated_polygon + [p for query in translated_queries for p in query]):
            transforms.append((translated_polygon, translated_queries))
        for points, lines in transforms:
            expected = [oracle(points, query) for query in lines]
            actual = run(exe, points, lines)
            if actual != expected:
                j = next(j for j in range(len(lines)) if actual[j] != expected[j])
                raise AssertionError((index, points, lines[j], actual[j], expected[j]))
            comparisons += len(lines)
            for answer in expected:
                counts[answer.split()[0]] += 1
    formal = sorted((ROOT / 'testcases').glob('*.in'))
    sampled = 0
    for path in formal:
        polygon, queries = read_case(path)
        expected = path.with_suffix('.ans').read_text().splitlines()
        if path.stem == '1-samples-1':
            assert path.with_suffix('.ans').read_text().split() == (ROOT / 'generator/manual/s1.ans').read_text().split()
        actual = run(exe, polygon, queries)
        assert actual == expected, path.name
        # Large polygons: oracle scans all edges for a bounded selection of queries.
        chosen = list(range(len(queries))) if len(polygon) * len(queries) <= 100000 else sorted(set([0, len(queries) - 1] + [rng.randrange(len(queries)) for _ in range(8)]))
        for j in chosen:
            assert oracle(polygon, queries[j]) == expected[j], (path.name, j)
        sampled += len(chosen)
        reverse = [(b, a) for a, b in queries[:100]]
        reversed_answers = run(exe, polygon, reverse)
        for answer, original in zip(reversed_answers, actual[:100]):
            tokens = original.split()
            if tokens[0] == 'CUT':
                tokens[1], tokens[2] = tokens[2], tokens[1]
            assert answer == ' '.join(tokens), path.name
    for name, (mtime, digest) in json.loads((ROOT / 'tools/statement-snapshot.json').read_text()).items():
        path = ROOT / name
        assert path.stat().st_mtime_ns == mtime and hashlib.sha256(path.read_bytes()).hexdigest() == digest
    report = {'small_configurations': len(cases), 'oracle_query_comparisons': comparisons,
              'classifications_checked': counts, 'formal_cases': len(formal),
              'formal_oracle_queries': sampled, 'input_bytes': sum(p.stat().st_size for p in formal),
              'answer_bytes': sum(p.with_suffix('.ans').stat().st_size for p in formal),
              'statement_content_and_mtimes_unchanged': True}
    (ROOT / 'tools/crosscheck-report.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
