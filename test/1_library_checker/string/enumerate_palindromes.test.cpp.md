---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n \
    \ File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: string/manacher.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\
    \n#include \"assumption.hpp\"\n\n#include \"string/manacher.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    std::string s;\n\
    \    std::cin >> s;\n    auto z = manacher(s);\n    for (int i = 0; i < int(s.size());\
    \ ++i) {\n        std::cout << get_radius_odd(z, i) * 2 - 1;\n        if (i +\
    \ 1 < int(s.size())) std::cout << \" \" << get_radius_even(z, i) * 2 << \" \"\
    ;\n        else std::cout << \"\\n\";\n    }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/1_library_checker/string/enumerate_palindromes.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/1_library_checker/string/enumerate_palindromes.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/string/enumerate_palindromes.test.cpp
- /verify/test/1_library_checker/string/enumerate_palindromes.test.cpp.html
title: test/1_library_checker/string/enumerate_palindromes.test.cpp
---
