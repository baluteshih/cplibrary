---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: String/z_algo.hpp
    title: String/z_algo.hpp
  - icon: ':question:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"test/1_library_checker/string/zalgorithm.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n#line 2 \"assumption.hpp\"\
    \n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3 \"test/1_library_checker/string/zalgorithm.test.cpp\"\
    \n\n#line 2 \"String/z_algo.hpp\"\n\nstd::vector<int> make_z(const std::string\
    \ &s) {\n    std::vector<int> z(s.size());\n    int l = 0, r = 0;\n    z[0] =\
    \ s.size();\n    for (int i = 1; i < std::ssize(s); ++i) {\n        z[i] = std::max(0,\
    \ std::min(r - i + 1, z[i - l]));\n        while (i + z[i] < std::ssize(s) &&\
    \ s[i + z[i]] == s[z[i]]) ++z[i];\n        if (i + z[i] - 1 > r) l = i, r = i\
    \ + z[i] - 1;\n    }\n    return z;\n}\n#line 5 \"test/1_library_checker/string/zalgorithm.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    std::string\
    \ s;\n    std::cin >> s;\n    auto z = make_z(s);\n    for (int i = 0; i < int(s.size());\
    \ ++i)\n        std::cout << z[i] << \" \\n\"[i + 1 == int(s.size())];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n#include\
    \ \"assumption.hpp\"\n\n#include \"String/z_algo.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    std::string s;\n    std::cin >> s;\n    auto z = make_z(s);\n\
    \    for (int i = 0; i < int(s.size()); ++i)\n        std::cout << z[i] << \"\
    \ \\n\"[i + 1 == int(s.size())];\n}\n"
  dependsOn:
  - assumption.hpp
  - String/z_algo.hpp
  isVerificationFile: true
  path: test/1_library_checker/string/zalgorithm.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 13:39:32+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/string/zalgorithm.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/string/zalgorithm.test.cpp
- /verify/test/1_library_checker/string/zalgorithm.test.cpp.html
title: test/1_library_checker/string/zalgorithm.test.cpp
---
