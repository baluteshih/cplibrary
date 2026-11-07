#!/usr/bin/env python3
"""Check validator bounds/format and exact default-checker output handling."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
validator = root / 'validator/build/validator'
cases = [('0\n', True), ('2\n-100000000 100000000\n0 0\n', True),
         ('-1\n', False), ('200001\n', False), ('1\n100000001 0\n', False),
         ('1\n0 -100000001\n', False), ('1\n1.5 0\n', False),
         ('1\n0\n', False), ('0\nextra\n', False), ('1\n0  0\n', False)]
for text, valid in cases:
    result = subprocess.run([str(validator)], input=text, text=True, capture_output=True)
    assert (result.returncode == 42) == valid, (text, result.returncode, result.stderr)
checker = root / 'sandbox/default/checker-compile/build/checker'
with tempfile.TemporaryDirectory(prefix='hulls-checker-') as temporary:
    directory = Path(temporary)
    inf, ans = directory / 'input', directory / 'answer'
    inf.write_text('0\n')
    ans.write_text('0\n0\n0\n0\n')
    outputs = [('0\n0\n0\n0\n', True), ('0 0 0 0\n\n', True),
               ('0 0 0', False), ('0 0 0 0 extra', False),
               ('0 0 0 1', False), ('0.0 0 0 0', False)]
    for text, valid in outputs:
        result = subprocess.run([str(checker), str(inf), str(ans), str(directory) + '/'],
                                input=text, text=True, capture_output=True)
        assert (result.returncode == 42) == valid, (text, result.returncode, result.stderr)
print(f'{len(cases)} validator and {len(outputs)} checker checks passed')
