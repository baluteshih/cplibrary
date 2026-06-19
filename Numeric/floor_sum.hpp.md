---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
    title: test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/floor_sum.hpp\"\n\n// sum^{n-1}_0 floor((a * i +\
    \ b) / m) in log(n + m + a + b)\ntemplate<typename T = long long, typename Res\
    \ = T>\nRes floor_sum(T n, T m, T a, T b) {\n    Res ans = 0;\n    if (a >= m)\
    \ ans += Res(n - 1) * Res(n) * Res(a / m) / Res(2), a %= m;\n    if (b >= m) ans\
    \ += Res(n) * Res(b / m), b %= m;\n    Res y_max = (a * n + b) / m, x_max = (y_max\
    \ * m - b);\n    if (y_max == 0) return ans;\n    ans += Res(n - (x_max + a -\
    \ 1) / a) * Res(y_max);\n    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);\n\
    \    return ans;\n}\n"
  code: "#pragma once\n\n// sum^{n-1}_0 floor((a * i + b) / m) in log(n + m + a +\
    \ b)\ntemplate<typename T = long long, typename Res = T>\nRes floor_sum(T n, T\
    \ m, T a, T b) {\n    Res ans = 0;\n    if (a >= m) ans += Res(n - 1) * Res(n)\
    \ * Res(a / m) / Res(2), a %= m;\n    if (b >= m) ans += Res(n) * Res(b / m),\
    \ b %= m;\n    Res y_max = (a * n + b) / m, x_max = (y_max * m - b);\n    if (y_max\
    \ == 0) return ans;\n    ans += Res(n - (x_max + a - 1) / a) * Res(y_max);\n \
    \   ans += floor_sum(y_max, a, m, (a - x_max % a) % a);\n    return ans;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/floor_sum.hpp
  requiredBy: []
  timestamp: '2026-06-20 01:45:49+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
documentation_of: Numeric/floor_sum.hpp
layout: document
redirect_from:
- /library/Numeric/floor_sum.hpp
- /library/Numeric/floor_sum.hpp.html
title: Numeric/floor_sum.hpp
---
