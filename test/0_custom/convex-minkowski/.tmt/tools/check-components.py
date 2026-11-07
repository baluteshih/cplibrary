#!/usr/bin/env python3
"""Input range/format and default exact-token checker regressions."""
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
validator = ROOT / 'validator/build/validator'
cases = [('1 1\n100000000 -100000000\n100000000 -100000000\n', True),
         ('2 2\n0 0\n0 0\n0 0\n0 0\n', True),
         ('0 1\n', False), ('1 0\n', False), ('200000 1\n', False),
         ('100001 100000\n', False), ('1 1\n100000001 0\n0 0\n', False),
         ('1 1\n0 0\n0 -100000001\n', False),
         ('1 1\n0.5 0\n0 0\n', False), ('1 1\n0  0\n0 0\n', False),
         ('1 1\n0 0\n', False), ('1 1\n0 0\n0 0\nextra\n', False)]
for text, accepted in cases:
    result = subprocess.run([str(validator)], input=text, text=True, capture_output=True)
    assert (result.returncode == 42) == accepted, (text, result.returncode, result.stderr)
checker = ROOT / 'sandbox/default/checker-compile/build/checker'
with tempfile.TemporaryDirectory(prefix='minkowski-checker-') as temporary:
    directory = Path(temporary)
    inf, ans = directory / 'input', directory / 'answer'
    inf.write_text(cases[0][0])
    ans.write_text('1\n200000000 -200000000\n')
    outputs = [('1\n200000000 -200000000\n', True),
               ('1 200000000\t-200000000\n\n', True),
               ('1 100000000 -100000000', False), ('1 200000000', False),
               ('1 200000000 -200000000 extra', False),
               ('1 200000000.0 -200000000', False), ('0', False)]
    for text, accepted in outputs:
        result = subprocess.run([str(checker), str(inf), str(ans), str(directory) + '/'],
                                input=text, text=True, capture_output=True)
        assert (result.returncode == 42) == accepted, (text, result.returncode, result.stderr)
print(f'{len(cases)} validator and {len(outputs)} checker checks passed')
