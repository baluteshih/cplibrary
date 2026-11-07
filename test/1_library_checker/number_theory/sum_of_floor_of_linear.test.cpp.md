---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/floor_sum.hpp
    title: Numeric/floor_sum.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/sum_of_floor_of_linear
    links:
    - https://judge.yosupo.jp/problem/sum_of_floor_of_linear
  bundledCode: "#line 1 \"test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_floor_of_linear\"\n\
    #line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp\"\n\
    \n#line 2 \"Numeric/floor_sum.hpp\"\n\n// sum^{n-1}_0 floor((a * i + b) / m) in\
    \ log(n + m + a + b)\ntemplate<typename T = long long, typename Res = T>\nRes\
    \ floor_sum(T n, T m, T a, T b) {\n    assert(n >= 0 && m > 0 && a >= 0 && b >=\
    \ 0);\n    Res N = n, M = m, A = a, B = b, ans = 0;\n    while (N != 0) {\n  \
    \      if (A >= M) {\n            Res x = N, y = N - 1;\n            if (x % 2\
    \ == 0) x /= 2;\n            else y /= 2;\n            ans += x * y * (A / M),\
    \ A %= M;\n        }\n        if (B >= M) ans += N * (B / M), B %= M;\n      \
    \  Res top = A * N + B;\n        if (top < M) break;\n        N = top / M, B =\
    \ top % M, std::swap(M, A);\n    }\n    return ans;\n}\n#line 5 \"test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp\"\
    \n\nvoid solve() {\n    long long n, m, a, b;\n    std::cin >> n >> m >> a >>\
    \ b;\n    std::cout << floor_sum(n, m, a, b) << \"\\n\";\n}\n\nint main() {\n\
    \    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int t;\n    std::cin\
    \ >> t;\n    while (t--) {\n        solve();\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sum_of_floor_of_linear\"\
    \n#include \"assumption.hpp\"\n\n#include \"Numeric/floor_sum.hpp\"\n\nvoid solve()\
    \ {\n    long long n, m, a, b;\n    std::cin >> n >> m >> a >> b;\n    std::cout\
    \ << floor_sum(n, m, a, b) << \"\\n\";\n}\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int t;\n    std::cin >> t;\n    while (t--) {\n      \
    \  solve();\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Numeric/floor_sum.hpp
  isVerificationFile: true
  path: test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
  requiredBy: []
  timestamp: '2026-11-07 14:46:12+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
- /verify/test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp.html
title: test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
---
