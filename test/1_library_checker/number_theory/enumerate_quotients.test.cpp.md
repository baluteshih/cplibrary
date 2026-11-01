---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/floor_enumerate.hpp
    title: Numeric/floor_enumerate.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_quotients
    links:
    - https://judge.yosupo.jp/problem/enumerate_quotients
  bundledCode: "#line 1 \"test/1_library_checker/number_theory/enumerate_quotients.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_quotients\"\n#line\
    \ 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/number_theory/enumerate_quotients.test.cpp\"\n\n\
    #line 2 \"Numeric/floor_enumerate.hpp\"\n\n/* \ncall (x, l, r) such that i in\
    \ [l, r) having x = floor(n / i)\nx is enumerated from large to small\n*/\ntemplate<typename\
    \ T, typename F>\nvoid floor_enumerate(T n, F func) {\n    for (T l = 1, r; l\
    \ <= n; l = r + 1) {\n        T x = n / l;\n        r = n / x;\n        func(x,\
    \ l, r + 1);\n    }\n}\n#line 5 \"test/1_library_checker/number_theory/enumerate_quotients.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    long\
    \ long n;\n    std::cin >> n;\n    std::vector<long long> ans;\n    floor_enumerate(n,\
    \ [&](long long x, [[maybe_unused]] long long l, [[maybe_unused]] long long r)\
    \ {\n        ans.push_back(x); \n    });\n    std::ranges::reverse(ans);\n   \
    \ std::cout << ans.size() << \"\\n\";\n    for (int i = 0; i < int(ans.size());\
    \ ++i)\n        std::cout << ans[i] << \" \\n\"[i + 1 == int(ans.size())];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_quotients\"\n\
    #include \"assumption.hpp\"\n\n#include \"Numeric/floor_enumerate.hpp\"\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    long long\
    \ n;\n    std::cin >> n;\n    std::vector<long long> ans;\n    floor_enumerate(n,\
    \ [&](long long x, [[maybe_unused]] long long l, [[maybe_unused]] long long r)\
    \ {\n        ans.push_back(x); \n    });\n    std::ranges::reverse(ans);\n   \
    \ std::cout << ans.size() << \"\\n\";\n    for (int i = 0; i < int(ans.size());\
    \ ++i)\n        std::cout << ans[i] << \" \\n\"[i + 1 == int(ans.size())];\n}\n"
  dependsOn:
  - assumption.hpp
  - Numeric/floor_enumerate.hpp
  isVerificationFile: true
  path: test/1_library_checker/number_theory/enumerate_quotients.test.cpp
  requiredBy: []
  timestamp: '2026-06-20 01:45:49+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/number_theory/enumerate_quotients.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/number_theory/enumerate_quotients.test.cpp
- /verify/test/1_library_checker/number_theory/enumerate_quotients.test.cpp.html
title: test/1_library_checker/number_theory/enumerate_quotients.test.cpp
---
