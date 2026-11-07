#!/usr/bin/env python3
"""Independent integer full-scan oracle, legal answer sets, metamorphic checks."""
from pathlib import Path
import hashlib
import json
import random
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def cross(a, b, c):
    return (b[0] - a[0]) * (c[1] - a[1]) - (b[1] - a[1]) * (c[0] - a[0])


def hull(points):
    points = sorted(set(points))
    if len(points) < 2:
        return points
    def chain(sequence):
        result = []
        for p in sequence:
            while len(result) > 1 and cross(result[-2], result[-1], p) <= 0:
                result.pop()
            result.append(p)
        return result
    return chain(points)[:-1] + chain(points[::-1])[:-1]


def location(polygon, p):
    if len(polygon) == 1:
        return 'ON' if p == polygon[0] else 'OUT'
    for a, b in zip(polygon, polygon[1:] + polygon[:1]):
        if cross(a, b, p) == 0 and min(a[0], b[0]) <= p[0] <= max(a[0], b[0]) and min(a[1], b[1]) <= p[1] <= max(a[1], b[1]):
            return 'ON'
    if len(polygon) == 2:
        return 'OUT'
    return 'IN' if all(cross(a, b, p) > 0 for a, b in zip(polygon, polygon[1:] + polygon[:1])) else 'OUT'


def allowed(polygon, query):
    kind, x, y = query
    if kind == 'I':
        return location(polygon, (x, y))
    if kind == 'D':
        values = [x * py - y * px for px, py in polygon]
        best = max(values)
        return {i for i, value in enumerate(values) if value == best}
    p = x, y
    assert len(polygon) >= 3 and location(polygon, p) == 'OUT'
    first = {i for i, a in enumerate(polygon) if all(cross(p, a, b) >= 0 for b in polygon)}
    second = {i for i, a in enumerate(polygon) if all(cross(p, a, b) <= 0 for b in polygon)}
    assert 1 <= len(first) <= 2 and 1 <= len(second) <= 2
    return first, second


def valid(polygon, query, line):
    expected = allowed(polygon, query)
    tokens = line.split()
    if query[0] == 'I':
        return tokens == [expected]
    try:
        indices = list(map(int, tokens))
    except ValueError:
        return False
    if query[0] == 'D':
        return len(indices) == 1 and indices[0] in expected
    return len(indices) == 2 and indices[0] in expected[0] and indices[1] in expected[1]


def encode(polygon, queries):
    return f'{len(polygon)} {len(queries)}\n' + ''.join(f'{x} {y}\n' for x, y in polygon) + ''.join(f'{kind} {x} {y}\n' for kind, x, y in queries)


def run(exe, polygon, queries):
    result = subprocess.run([str(exe)], input=encode(polygon, queries), text=True, capture_output=True, check=True)
    lines = result.stdout.splitlines()
    assert len(lines) == len(queries)
    return lines


def read_case(path):
    lines = path.read_text().splitlines()
    n, q = map(int, lines[0].split())
    polygon = [tuple(map(int, line.split())) for line in lines[1:n + 1]]
    queries = [(kind, int(x), int(y)) for kind, x, y in (line.split() for line in lines[n + 1:])]
    assert len(queries) == q
    return polygon, queries


def main():
    exe = Path(sys.argv[1]).resolve()
    rng = random.Random(141421)
    cases = [read_case(path) for path in sorted((ROOT / 'generator/manual').glob('*.in'))]
    for i in range(160):
        polygon = hull([(rng.randint(-15, 15), rng.randint(-15, 15)) for _ in range(20)])
        shift = rng.randrange(len(polygon))
        polygon = polygon[shift:] + polygon[:shift]
        queries = []
        for p in polygon:
            queries.append(('I', *p))
        for j, p in enumerate(polygon):
            a, b = polygon[j - 1], p
            dx, dy = b[0] - a[0], b[1] - a[1]
            queries += [('D', dx, dy), ('D', -dx, -dy)]
            for t in (-1, 2):
                external = a[0] + t * dx, a[1] + t * dy
                if location(polygon, external) == 'OUT':
                    queries.append(('T', *external))
        for _ in range(50):
            p = rng.randint(-40, 40), rng.randint(-40, 40)
            queries.append(('I', *p))
            if p != (0, 0):
                queries.append(('D', *p))
            if location(polygon, p) == 'OUT':
                queries.append(('T', *p))
        cases.append((polygon, queries))
    comparisons = 0
    ties = {'D': 0, 'T': 0}
    for index, (polygon, queries) in enumerate(cases):
        transforms = [(polygon, queries)]
        if len(polygon) >= 3:
            shift = rng.randrange(len(polygon))
            transforms.append((polygon[shift:] + polygon[:shift], queries))
        shifted = [(x + 17, y - 23) for x, y in polygon]
        shifted_queries = [(kind, x if kind == 'D' else x + 17, y if kind == 'D' else y - 23) for kind, x, y in queries]
        if all(max(abs(x), abs(y)) <= 100000000 for x, y in shifted) and all(max(abs(x), abs(y)) <= 100000000 for kind, x, y in shifted_queries):
            transforms.append((shifted, shifted_queries))
        reflected = [(-x, y) for x, y in polygon]
        if len(reflected) >= 3:
            reflected.reverse()
        else:
            reflected.sort()
        reflected_queries = [(kind, -x, y) for kind, x, y in queries]
        transforms.append((reflected, reflected_queries))
        for points, batch in transforms:
            lines = run(exe, points, batch)
            for query, line in zip(batch, lines):
                assert valid(points, query, line), (index, points, query, line, allowed(points, query))
                options = allowed(points, query)
                if query[0] == 'D' and len(options) == 2:
                    ties['D'] += 1
                if query[0] == 'T' and any(len(part) == 2 for part in options):
                    ties['T'] += 1
                comparisons += 1
    formal = sorted((ROOT / 'testcases').glob('*.in'))
    sampled = 0
    largest_n = largest_q = 0
    for path in formal:
        polygon, queries = read_case(path)
        expected = path.with_suffix('.ans').read_text().splitlines()
        actual = run(exe, polygon, queries)
        assert actual == expected, path.name
        if path.stem == '1-samples-1':
            sample = (ROOT / 'generator/manual/s1.ans').read_text().splitlines()
            assert all(valid(polygon, query, line) for query, line in zip(queries, sample))
        chosen = range(len(queries)) if len(polygon) ** 2 * len(queries) <= 1000000 else sorted(set([0, len(queries) - 1] + [rng.randrange(len(queries)) for _ in range(10)]))
        for j in chosen:
            if queries[j][0] == 'T' and len(polygon) > 100:
                a, b = map(int, actual[j].split())
                p = queries[j][1:]
                assert all(cross(p, polygon[a], v) >= 0 and cross(p, polygon[b], v) <= 0 for v in polygon)
            else:
                assert valid(polygon, queries[j], actual[j]), (path.name, j)
            sampled += 1
        largest_n = max(largest_n, len(polygon))
        largest_q = max(largest_q, len(queries))
    for name, (mtime, digest) in json.loads((ROOT / 'tools/statement-snapshot.json').read_text()).items():
        path = ROOT / name
        assert path.stat().st_mtime_ns == mtime and hashlib.sha256(path.read_bytes()).hexdigest() == digest
    report = {'small_configurations': len(cases), 'oracle_query_comparisons': comparisons,
              'ties_checked': ties, 'formal_cases': len(formal), 'formal_oracle_queries': sampled,
              'largest_n': largest_n, 'largest_q': largest_q,
              'input_bytes': sum(path.stat().st_size for path in formal),
              'answer_bytes': sum(path.with_suffix('.ans').stat().st_size for path in formal),
              'statement_content_and_mtimes_unchanged': True}
    (ROOT / 'tools/crosscheck-report.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
