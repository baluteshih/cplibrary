#!/usr/bin/env python3
"""Topology/bounds validator tests and exact checker regression tests."""
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
polygon = [(0, 0), (4, 0), (4, 4), (0, 4)]


def case(points, query='1 1 2 1'):
    return f'{len(points)} 1\n' + ''.join(f'{x} {y}\n' for x, y in points) + query + '\n'


pentagon = [(0, 0), (4, 0), (6, 3), (3, 6), (-1, 3)]
cases = [(case(polygon), True), (case(polygon[2:] + polygon[:2]), True),
         (case([(0, 0), (99999999, 99999998), (100000000, 99999999)]), True),
         (case(list(reversed(polygon))), False),
         (case([(0, 0), (4, 0), (2, 1), (4, 4), (0, 4)]), False),
         (case([(0, 0), (2, 0), (4, 0), (4, 4), (0, 4)]), False),
         (case([(0, 0), (1, 1), (2, 2)]), False),
         (case([pentagon[i] for i in [0, 2, 4, 1, 3]]), False),
         (case(polygon + polygon), False), (case(polygon + [polygon[0]]), False),
         (case(polygon, '1 1 1 1'), False), (case([(0, 0), (1, 1)]), False),
         (case([(0, 0), (100000001, 0), (0, 1)]), False),
         (case(polygon, '0 0 100000001 0'), False),
         (case(polygon, '0 -100000001 1 0'), False),
         (case(polygon, '1.5 0 1 1'), False), (case(polygon) + 'extra\n', False),
         ('200001 1\n', False), ('4 200001\n', False), ('4 0\n', False),
         (case(polygon).replace('1 1 2 1', '1  1 2 1'), False)]
for text, accepted in cases:
    result = subprocess.run([str(ROOT / 'validator/build/validator')], input=text, text=True, capture_output=True)
    assert (result.returncode == 42) == accepted, (text, result.returncode, result.stderr)
checker = ROOT / 'sandbox/default/checker-compile/build/checker'
with tempfile.TemporaryDirectory(prefix='line-checker-') as temporary:
    directory = Path(temporary)
    inf, ans = directory / 'input', directory / 'answer'
    inf.write_text(case(polygon))
    ans.write_text('CUT 3 1\n')
    outputs = [('CUT 3 1\n', True), ('CUT\t3 1\n\n', True),
               ('CUT 1 3\n', False), ('CUT 3\n', False),
               ('CUT 3 1 extra\n', False), ('cut 3 1\n', False),
               ('CUT 3.0 1\n', False), ('EMPTY\n', False)]
    for text, accepted in outputs:
        result = subprocess.run([str(checker), str(inf), str(ans), str(directory) + '/', 'case_sensitive'],
                                input=text, text=True, capture_output=True)
        assert (result.returncode == 42) == accepted, (text, result.returncode, result.stderr)
print(f'{len(cases)} validator and {len(outputs)} checker regression checks passed')
