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
    \ floor_sum(T n, T m, T a, T b) {\n    Res ans = 0;\n    if (a >= m) ans += Res(n\
    \ - 1) * Res(n) * Res(a / m) / Res(2), a %= m;\n    if (b >= m) ans += Res(n)\
    \ * Res(b / m), b %= m;\n    Res y_max = (a * n + b) / m, x_max = (y_max * m -\
    \ b);\n    if (y_max == 0) return ans;\n    ans += Res(n - (x_max + a - 1) / a)\
    \ * Res(y_max);\n    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);\n   \
    \ return ans;\n}\n#line 5 \"test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp\"\
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
  timestamp: '2026-06-20 01:45:49+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
- /verify/test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp.html
title: test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
---
