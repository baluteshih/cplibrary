---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
    title: test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/floor_sum.hpp\"\n\n// sum^{n-1}_0 floor((a * i +\
    \ b) / m) in log(n + m + a + b)\ntemplate<typename T = long long, typename Res\
    \ = T>\nRes floor_sum(T n, T m, T a, T b) {\n    assert(n >= 0 && m > 0 && a >=\
    \ 0 && b >= 0);\n    Res N = n, M = m, A = a, B = b, ans = 0;\n    while (N !=\
    \ 0) {\n        if (A >= M) {\n            Res x = N, y = N - 1;\n           \
    \ if (x % 2 == 0) x /= 2;\n            else y /= 2;\n            ans += x * y\
    \ * (A / M), A %= M;\n        }\n        if (B >= M) ans += N * (B / M), B %=\
    \ M;\n        Res top = A * N + B;\n        if (top < M) break;\n        N = top\
    \ / M, B = top % M, std::swap(M, A);\n    }\n    return ans;\n}\n"
  code: "#pragma once\n\n// sum^{n-1}_0 floor((a * i + b) / m) in log(n + m + a +\
    \ b)\ntemplate<typename T = long long, typename Res = T>\nRes floor_sum(T n, T\
    \ m, T a, T b) {\n    assert(n >= 0 && m > 0 && a >= 0 && b >= 0);\n    Res N\
    \ = n, M = m, A = a, B = b, ans = 0;\n    while (N != 0) {\n        if (A >= M)\
    \ {\n            Res x = N, y = N - 1;\n            if (x % 2 == 0) x /= 2;\n\
    \            else y /= 2;\n            ans += x * y * (A / M), A %= M;\n     \
    \   }\n        if (B >= M) ans += N * (B / M), B %= M;\n        Res top = A *\
    \ N + B;\n        if (top < M) break;\n        N = top / M, B = top % M, std::swap(M,\
    \ A);\n    }\n    return ans;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/floor_sum.hpp
  requiredBy: []
  timestamp: '2026-11-07 14:46:12+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/1_library_checker/number_theory/sum_of_floor_of_linear.test.cpp
documentation_of: Numeric/floor_sum.hpp
layout: document
redirect_from:
- /library/Numeric/floor_sum.hpp
- /library/Numeric/floor_sum.hpp.html
title: Numeric/floor_sum.hpp
---
