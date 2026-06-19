---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Misc/i128.hpp
    title: Misc/i128.hpp
  - icon: ':heavy_check_mark:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/many_aplusb_128bit
    links:
    - https://judge.yosupo.jp/problem/many_aplusb_128bit
  bundledCode: "#line 1 \"test/1_library_checker/sample/many_aplusb_128bit.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb_128bit\"\n#line\
    \ 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/sample/many_aplusb_128bit.test.cpp\"\n\n#line 2 \"\
    Misc/i128.hpp\"\n\nnamespace std {\n    std::istream &operator>>(std::istream&\
    \ is, __int128 &x) {\n        std::string s;\n        is >> s;\n        int sgn\
    \ = 1;\n        if (s[0] == '-') sgn = -1, s.erase(s.begin());\n        x = 0;\n\
    \        for (char c : s)\n            x = x * 10 + int(c - '0'); \n        x\
    \ *= sgn;\n        return is;\n    }\n    std::ostream &operator<<(std::ostream\
    \ &os, const __int128 &x) {\n        if (x < 0) return os << '-' << -x;\n    \
    \    if (x < 10) return os << int(x % 10);\n        return os << x / 10 << int(x\
    \ % 10);\n    }\n}\n#line 5 \"test/1_library_checker/sample/many_aplusb_128bit.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ t;\n    std::cin >> t;\n    while (t--) {\n        __int128 a, b;\n        std::cin\
    \ >> a >> b;\n        std::cout << a + b << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/many_aplusb_128bit\"\n\
    #include \"assumption.hpp\"\n\n#include \"Misc/i128.hpp\"\n\nint main() {\n  \
    \  std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int t;\n    std::cin >>\
    \ t;\n    while (t--) {\n        __int128 a, b;\n        std::cin >> a >> b;\n\
    \        std::cout << a + b << \"\\n\";\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Misc/i128.hpp
  isVerificationFile: true
  path: test/1_library_checker/sample/many_aplusb_128bit.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 21:01:17+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/sample/many_aplusb_128bit.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/sample/many_aplusb_128bit.test.cpp
- /verify/test/1_library_checker/sample/many_aplusb_128bit.test.cpp.html
title: test/1_library_checker/sample/many_aplusb_128bit.test.cpp
---
