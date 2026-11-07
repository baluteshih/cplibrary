#!/usr/bin/env python3
"""Regression checks for strict validation and the stated numeric checker contract."""
from pathlib import Path
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
validator = root / 'validator/build/validator'
checker = root / 'checker/build/checker'
valid = '1\n-10000 10000 10000\n'
inputs = [(valid, True), ('0\n', False), ('501\n', False),
          ('1\n10001 0 1\n', False), ('1\n0 -10001 1\n', False),
          ('1\n0 0 0\n', False), ('1\n0 0 10001\n', False),
          ('1\n0.5 0 1\n', False), ('1\n0  0 1\n', False),
          ('1\n0 0 1\nextra\n', False), ('1\n0 0\n', False)]
for text, accepted in inputs:
    result = subprocess.run([str(validator)], input=text, text=True, capture_output=True)
    assert (result.returncode == 42) == accepted, (text, result.stderr)
with tempfile.TemporaryDirectory(prefix='circle-checker-') as temporary:
    directory = Path(temporary)
    inf = directory / 'input'
    ans = directory / 'answer'
    inf.write_text('2\n0 0 1\n10 0 1\n')
    ans.write_text('6.283185307179586\n0\n')
    outputs = [('6.283185307179586\n0\n', True),
               ('6.283185307179586 0.0000009\n', True),
               ('6.283190 0\n', True), ('6.283193 0\n', False),
               ('6.283185307179586 0.0000011\n', False),
               ('6.283185307179586\n', False),
               ('6.283185307179586 0 extra\n', False),
               ('nan 0\n', False), ('inf 0\n', False),
               ('6.283185307179586 -inf\n', False),
               ('6.283185307179586 0junk\n', False)]
    for text, accepted in outputs:
        result = subprocess.run([str(checker), str(inf), str(ans), str(directory) + '/'],
                                input=text, text=True, capture_output=True)
        assert (result.returncode == 42) == accepted, (text, result.returncode, result.stderr)
print(f'{len(inputs)} validator and {len(outputs)} checker regression checks passed')
