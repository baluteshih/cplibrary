#!/usr/bin/env python3
"""Topology/precondition checks and exhaustive small checker acceptance sets."""
from pathlib import Path
import subprocess
import tempfile
import crosscheck as oracle

ROOT = Path(__file__).resolve().parents[1]
validator = ROOT / 'validator/build/validator'
checker = ROOT / 'checker/build/checker'
square = [(0, 0), (8, 0), (8, 8), (0, 8)]
pentagon = [(0, 0), (4, 0), (6, 3), (3, 6), (-1, 3)]


def text(points, query='I 1 1'):
    return f'{len(points)} 1\n' + ''.join(f'{x} {y}\n' for x, y in points) + query + '\n'


cases = [(text(square), True), (text(square[2:] + square[:2]), True),
         (text([(0, 0)]), True), (text([(-1, 1), (1, -1)]), True),
         (text(square, 'T -1 0'), True),
         (text(square, 'T 1 1'), False), (text(square, 'T 0 0'), False),
         (text(square, 'T 4 0'), False), (text([(0, 0)], 'T 1 1'), False),
         (text([(-1, 1), (1, -1)], 'T 1 1'), False),
         (text(square, 'D 0 0'), False),
         (text(list(reversed(square))), False),
         (text([pentagon[i] for i in [0, 2, 4, 1, 3]]), False),
         (text(square + square), False),
         (text([(0, 0), (4, 0), (8, 0), (8, 8), (0, 8)]), False),
         (text([(0, 0), (8, 0), (4, 1), (8, 8), (0, 8)]), False),
         (text([(0, 0), (1, 1), (2, 2)]), False),
         (text([(1, -1), (-1, 1)]), False),
         (text([(0, 0), (0, 0)]), False),
         ('0 1\n', False), ('200001 1\n', False), ('1 200001\n', False),
         ('1 0\n', False), (text(square, 'X 1 1'), False),
         (text(square, 'D 100000001 1'), False),
         (text([(100000001, 0)]), False),
         (text(square, 'I 1.5 1'), False),
         (text(square, 'I 1  1'), False), (text(square) + 'extra\n', False)]
for data, accepted in cases:
    process = subprocess.run([str(validator)], input=data, text=True, capture_output=True)
    assert (process.returncode == 42) == accepted, (data, process.returncode, process.stderr)
checks = 0
with tempfile.TemporaryDirectory(prefix='queries-checker-') as temporary:
    directory = Path(temporary)
    inf, ans = directory / 'input', directory / 'answer'
    def check(points, query, reference, output, expected):
        global checks
        inf.write_text(oracle.encode(points, [query]))
        ans.write_text(reference + '\n')
        process = subprocess.run([str(checker), str(inf), str(ans), str(directory) + '/'],
                                 input=output + '\n', text=True, capture_output=True)
        assert (process.returncode == 42) == expected, (points, query, reference, output, process.stderr)
        checks += 1
    for direction in [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (-100000000, 1)]:
        query = ('D', *direction)
        allowed = oracle.allowed(square, query)
        for reference in allowed:
            for candidate in range(-1, len(square) + 1):
                check(square, query, str(reference), str(candidate), candidate in allowed)
    for p in [(-2, 0), (10, 4), (4, 10), (-1, 8), (9, 9), (-1, -1)]:
        query = ('T', *p)
        first, second = oracle.allowed(square, query)
        for ref_a in first:
            for ref_b in second:
                for a in range(4):
                    for b in range(4):
                        check(square, query, f'{ref_a} {ref_b}', f'{a} {b}', a in first and b in second)
    for word in ['IN', 'ON', 'OUT', 'in', 'NaN', 'IN extra', '']:
        check(square, ('I', 4, 4), 'IN', word, word == 'IN')
    for output in ['2', '2 1 extra', '2.0 1', '-1 1', '4 1', '']:
        check(square, ('T', 10, 4), '2 1', output, False)
    check([(0, 0)], ('D', 1, 0), '0', '0', True)
    for reference in ['0', '1']:
        for candidate in ['0', '1']:
            check([(0, 0), (1, 0)], ('D', 1, 0), reference, candidate, True)
print(f'{len(cases)} validator and {checks} checker checks passed')
