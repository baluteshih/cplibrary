#!/usr/bin/env python3
"""Independent 65-digit vertical-decomposition oracle and metamorphic checks.

Uses only Python's standard library. Each x slab has a fixed vertical ordering
of circle boundaries. Integrate every strip analytically, counting multiplicity.
Usage: python3 tools/crosscheck.py /path/to/reference-executable [library-executable]
"""
import decimal
from decimal import Decimal as D
import json
from pathlib import Path
import random
import subprocess
import sys

decimal.getcontext().prec = 65
PI = D('3.1415926535897932384626433832795028841971693993751058209749445923078164')
ROOT = Path(__file__).resolve().parents[1]


def atan(value):
    if value < 0:
        return -atan(-value)
    multiplier = 1
    while value > D('0.1'):
        value /= 1 + (1 + value * value).sqrt()
        multiplier *= 2
    term = value
    result = value
    for k in range(1, 1000):
        term *= -value * value
        change = term / (2 * k + 1)
        result += change
        if abs(change) < D('1e-68'):
            break
    return result * multiplier


def primitive(circle, x):
    cx, _, radius = map(D, circle)
    t = max(-radius, min(radius, x - cx))
    height = max(D(0), radius * radius - t * t).sqrt()
    angle = atan(t / height) if height else (PI / 2 if t > 0 else -PI / 2)
    return (t * height + radius * radius * angle) / 2


def oracle(circles):
    cuts = {D(x - r) for x, y, r in circles} | {D(x + r) for x, y, r in circles}
    for i, (x1, y1, r1) in enumerate(circles):
        for x2, y2, r2 in circles[:i]:
            dx, dy = x2 - x1, y2 - y1
            d2 = dx * dx + dy * dy
            if not d2 or not (r1 - r2) ** 2 <= d2 <= (r1 + r2) ** 2:
                continue
            fraction = D(d2 + r1 * r1 - r2 * r2) / (2 * d2)
            base = D(x1) + fraction * dx
            height_factor = max(D(0), D(r1 * r1) / d2 - fraction * fraction).sqrt()
            cuts.add(base - dy * height_factor)
            cuts.add(base + dy * height_factor)
    cuts = sorted(cuts)
    exact = [D(0)] * (len(circles) + 1)
    for left, right in zip(cuts, cuts[1:]):
        if right - left < D('1e-50'):
            continue
        middle = (left + right) / 2
        endpoints = []
        integrals = {}
        for i, circle in enumerate(circles):
            x, y, r = circle
            if not x - r < middle < x + r:
                continue
            height = (D(r * r) - (middle - x) ** 2).sqrt()
            integral = primitive(circle, right) - primitive(circle, left)
            for sign in (-1, 1):
                endpoints.append((D(y) + sign * height, i, sign))
                integrals[i, sign] = D(y) * (right - left) + sign * integral
        endpoints.sort()
        count = 0
        for lower, upper in zip(endpoints, endpoints[1:]):
            _, i, sign = lower
            count -= sign
            if count:
                _, j, upper_sign = upper
                exact[count] += integrals[j, upper_sign] - integrals[i, sign]
    result = [D(0)] * len(circles)
    cumulative = D(0)
    for k in range(len(circles), 0, -1):
        cumulative += exact[k]
        result[k - 1] = cumulative
    return result


def run(executable, circles):
    data = str(len(circles)) + '\n' + ''.join(f'{x} {y} {r}\n' for x, y, r in circles)
    result = subprocess.run([str(executable)], input=data, text=True, capture_output=True, check=True)
    values = [D(token) for token in result.stdout.split()]
    assert len(values) == len(circles)
    assert all(value.is_finite() for value in values)
    return values


def compare(actual, expected, label, factor=D('1e-7')):
    for k, (a, b) in enumerate(zip(actual, expected), 1):
        assert abs(a - b) <= factor * max(D(1), abs(b)), (label, k, str(a), str(b))


def read_case(path):
    tokens = list(map(int, path.read_text().split()))
    return [tuple(tokens[i:i + 3]) for i in range(1, len(tokens), 3)]


def main():
    reference = Path(sys.argv[1]).resolve()
    library = Path(sys.argv[2]).resolve() if len(sys.argv) > 2 else None
    rng = random.Random(270119)
    cases = [read_case(path) for path in sorted((ROOT / 'generator/manual').glob('*.in'))]
    for _ in range(100):
        circles = []
        for _ in range(rng.randint(1, 9)):
            if circles and rng.randrange(4) == 0:
                circles.append(rng.choice(circles))
            else:
                circles.append((rng.randint(-12, 12), rng.randint(-12, 12), rng.randint(1, 15)))
        cases.append(circles)
    # Near tangencies with unit integer changes, at large legal coordinates.
    for radius in (2, 5, 100, 9999, 10000):
        cases.append([(-radius + 1, 0, radius), (radius, 0, radius)])
    failures = []
    checks = 0
    for index, circles in enumerate(cases):
        expected = oracle(circles)
        compare(run(reference, circles), expected, f'oracle {index}')
        checks += 1
        if library:
            try:
                compare(run(library, circles), expected, f'library {index}', D('1e-6'))
            except (AssertionError, subprocess.CalledProcessError) as error:
                failures.append({'case': circles, 'reason': str(error)})
        transforms = [list(reversed(circles)), [(y, -x, r) for x, y, r in circles]]
        if all(abs(x + 713) <= 10000 and abs(y - 821) <= 10000 for x, y, r in circles):
            transforms.append([(x + 713, y - 821, r) for x, y, r in circles])
        for transformed in transforms:
            compare(run(reference, transformed), expected, f'metamorphic {index}')
            checks += 1
        if all(max(abs(x), abs(y), r) <= 5000 for x, y, r in circles):
            scaled = [(2 * x, 2 * y, 2 * r) for x, y, r in circles]
            compare(run(reference, scaled), [4 * value for value in expected], f'scale {index}')
            checks += 1
    paths = sorted((ROOT / 'testcases').glob('*.in'))
    total_bytes = sum(path.stat().st_size for path in paths)
    maximum_sum_error = D(0)
    analytic_cases = 0
    for path in paths:
        circles = read_case(path)
        values = run(reference, circles)
        total = PI * sum(r * r for x, y, r in circles)
        error = abs(sum(values) - total) / max(D(1), total)
        maximum_sum_error = max(maximum_sum_error, error)
        assert error < D('1e-10'), (path.name, 'area sum', error)
        assert all(a + D('1e-7') >= b for a, b in zip(values, values[1:])), path.name
        if path.name.startswith('3-structured-'):
            number = int(path.stem.rsplit('-', 1)[1])
            if number <= 4:
                expected = [PI * r * r for r in sorted((r for x, y, r in circles), reverse=True)]
                compare(values, expected, path.name + ' nested analytic')
                analytic_cases += 1
            elif number == 5:
                compare(values, [total] + [D(0)] * (len(circles) - 1), path.name + ' disjoint analytic')
                analytic_cases += 1
        if library:
            try:
                compare(run(library, circles), values, path.name, D('1e-6'))
            except (AssertionError, subprocess.CalledProcessError) as error:
                failures.append({'testcase': path.name, 'reason': str(error)})
    report = {'oracle_cases': len(cases), 'oracle_and_metamorphic_checks': checks,
              'formal_cases': len(paths), 'analytic_maximum_size_cases': analytic_cases,
              'input_bytes': total_bytes,
              'maximum_relative_area_sum_error': str(maximum_sum_error),
              'library_failures': failures}
    (ROOT / 'tools/crosscheck-report.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
