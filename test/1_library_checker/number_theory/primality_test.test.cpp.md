---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/miller_rabin.hpp
    title: Numeric/miller_rabin.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/primality_test
    links:
    - https://judge.yosupo.jp/problem/primality_test
  bundledCode: "#line 1 \"test/1_library_checker/number_theory/primality_test.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/primality_test\"\n#line 2\
    \ \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3\
    \ \"test/1_library_checker/number_theory/primality_test.test.cpp\"\n\n#line 2\
    \ \"Numeric/miller_rabin.hpp\"\n\ntemplate<typename T>\nbool _miller_rabin(T a,\
    \ T n) {\n    if ((a = a % n) == 0) return 1;\n    if ((n & 1) ^ 1) return n ==\
    \ 2;\n    static auto mul = [&](T x, T y, T mod) {\n        if constexpr (sizeof(T)\
    \ == 4) return (long long)x * y % mod;\n        else return (__int128)x * y %\
    \ mod;\n    };\n    T t = std::countr_zero(std::make_unsigned_t<T>(n - 1)), x\
    \ = 1;\n    T tmp = (n - 1) >> t;\n    for (; tmp; tmp >>= 1, a = mul(a, a, n))\n\
    \        if(tmp & 1) x = mul(x, a, n);\n    if (x == 1 || x == n - 1) return 1;\n\
    \    while (--t)\n        if ((x = mul(x, x, n)) == n - 1) return 1;\n    return\
    \ 0;\n}\n\ntemplate<typename T>\nbool miller_rabin(T n) {\n    if (n == 1) return\
    \ false;\n    static std::vector<T> _base[4] = {{2, 7, 61}, {2, 13, 23, 1662803},\
    \ {2, 3, 5, 7, 11, 13}, {2, 325, 9375, 28178, 450775, 9780504, 1795265022}};\n\
    \    std::vector<T> base =\n        (n < 4759123141ll) ? _base[0] :\n        (n\
    \ < 1122004669633ll) ? _base[1] :\n        (n < 3474749660383ll) ? _base[2] :\
    \ _base[3];\n    for (T b : base)\n        if (!_miller_rabin(b, n))\n       \
    \     return false;\n    return true;\n}\n#line 5 \"test/1_library_checker/number_theory/primality_test.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ q;\n    std::cin >> q;\n    while (q--) {\n        long long n;\n        std::cin\
    \ >> n;\n        if (miller_rabin(n)) std::cout << \"Yes\\n\";\n        else std::cout\
    \ << \"No\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/primality_test\"\n#include\
    \ \"assumption.hpp\"\n\n#include \"Numeric/miller_rabin.hpp\"\n\nint main() {\n\
    \    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int q;\n    std::cin\
    \ >> q;\n    while (q--) {\n        long long n;\n        std::cin >> n;\n   \
    \     if (miller_rabin(n)) std::cout << \"Yes\\n\";\n        else std::cout <<\
    \ \"No\\n\";\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Numeric/miller_rabin.hpp
  isVerificationFile: true
  path: test/1_library_checker/number_theory/primality_test.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 20:51:50+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/number_theory/primality_test.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/number_theory/primality_test.test.cpp
- /verify/test/1_library_checker/number_theory/primality_test.test.cpp.html
title: test/1_library_checker/number_theory/primality_test.test.cpp
---
