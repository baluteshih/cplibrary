---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/miller_rabin.hpp
    title: Numeric/miller_rabin.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Numeric/Binomial.hpp
    title: Numeric/Binomial.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/primitive_root.hpp
    title: Numeric/primitive_root.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/number_theory/factorize.test.cpp
    title: test/1_library_checker/number_theory/factorize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/number_theory/primitive_root.test.cpp
    title: test/1_library_checker/number_theory/primitive_root.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/pollard_rho.hpp\"\n\n#line 2 \"Numeric/miller_rabin.hpp\"\
    \n\ntemplate<typename T>\nbool _miller_rabin(T a, T n) {\n    if ((a = a % n)\
    \ == 0) return 1;\n    if ((n & 1) ^ 1) return n == 2;\n    static auto mul =\
    \ [&](T x, T y, T mod) {\n        if constexpr (sizeof(T) == 4) return (long long)x\
    \ * y % mod;\n        else return (__int128)x * y % mod;\n    };\n    T t = std::countr_zero(std::make_unsigned_t<T>(n\
    \ - 1)), x = 1;\n    T tmp = (n - 1) >> t;\n    for (; tmp; tmp >>= 1, a = mul(a,\
    \ a, n))\n        if(tmp & 1) x = mul(x, a, n);\n    if (x == 1 || x == n - 1)\
    \ return 1;\n    while (--t)\n        if ((x = mul(x, x, n)) == n - 1) return\
    \ 1;\n    return 0;\n}\n\ntemplate<typename T>\nbool miller_rabin(T n) {\n   \
    \ if (n == 1) return false;\n    static std::vector<T> _base[4] = {{2, 7, 61},\
    \ {2, 13, 23, 1662803}, {2, 3, 5, 7, 11, 13}, {2, 325, 9375, 28178, 450775, 9780504,\
    \ 1795265022}};\n    std::vector<T> base =\n        (n < 4759123141ll) ? _base[0]\
    \ :\n        (n < 1122004669633ll) ? _base[1] :\n        (n < 3474749660383ll)\
    \ ? _base[2] : _base[3];\n    for (T b : base)\n        if (!_miller_rabin(b,\
    \ n))\n            return false;\n    return true;\n}\n#line 4 \"Numeric/pollard_rho.hpp\"\
    \n\n/*\nreturn an unsorted prime list\n*/\ntemplate<typename T>\nstd::vector<T>\
    \ pollard_rho(T n) {\n    static auto mul = [&](T x, T y, T mod) {\n        if\
    \ constexpr (sizeof(T) == 4) return (long long)x * y % mod;\n        else return\
    \ (__int128)x * y % mod;\n    };\n    std::vector<T> res;\n    auto factorize\
    \ = [&](auto self, T cur) -> void {\n        if (cur == 1) return;\n        if\
    \ (miller_rabin(cur)) return res.push_back(cur);\n        if (cur % 2 == 0) {\n\
    \            int cnt = std::countr_zero(std::make_unsigned_t<T>(cur));\n     \
    \       res.resize(res.size() + cnt, 2);\n            return self(self, cur >>\
    \ cnt);\n        }\n        T p = 2, q, i = 1, x = 0, y = 0, t = 0, ct = 87;\n\
    \        #define f(x) ((mul(x, x, cur) + ct) % cur)\n        while (t++ % 64 ||\
    \ std::__gcd(p, cur) == 1) {\n            if (x == y) x = i++, y = f(x);\n   \
    \         q = mul(p, x < y ? y - x : x - y, cur);\n            if (q) p = q;\n\
    \            if (p == cur) ++ct;\n            x = f(x), y = f(f(y));\n       \
    \ }\n        T d = std::__gcd(p, cur);\n        self(self, cur / d);\n       \
    \ self(self, d);\n    };\n    factorize(factorize, n);\n    return res;\n}\n"
  code: "#pragma once\n\n#include \"Numeric/miller_rabin.hpp\"\n\n/*\nreturn an unsorted\
    \ prime list\n*/\ntemplate<typename T>\nstd::vector<T> pollard_rho(T n) {\n  \
    \  static auto mul = [&](T x, T y, T mod) {\n        if constexpr (sizeof(T) ==\
    \ 4) return (long long)x * y % mod;\n        else return (__int128)x * y % mod;\n\
    \    };\n    std::vector<T> res;\n    auto factorize = [&](auto self, T cur) ->\
    \ void {\n        if (cur == 1) return;\n        if (miller_rabin(cur)) return\
    \ res.push_back(cur);\n        if (cur % 2 == 0) {\n            int cnt = std::countr_zero(std::make_unsigned_t<T>(cur));\n\
    \            res.resize(res.size() + cnt, 2);\n            return self(self, cur\
    \ >> cnt);\n        }\n        T p = 2, q, i = 1, x = 0, y = 0, t = 0, ct = 87;\n\
    \        #define f(x) ((mul(x, x, cur) + ct) % cur)\n        while (t++ % 64 ||\
    \ std::__gcd(p, cur) == 1) {\n            if (x == y) x = i++, y = f(x);\n   \
    \         q = mul(p, x < y ? y - x : x - y, cur);\n            if (q) p = q;\n\
    \            if (p == cur) ++ct;\n            x = f(x), y = f(f(y));\n       \
    \ }\n        T d = std::__gcd(p, cur);\n        self(self, cur / d);\n       \
    \ self(self, d);\n    };\n    factorize(factorize, n);\n    return res;\n}\n"
  dependsOn:
  - Numeric/miller_rabin.hpp
  isVerificationFile: false
  path: Numeric/pollard_rho.hpp
  requiredBy:
  - Numeric/primitive_root.hpp
  - Numeric/Binomial.hpp
  timestamp: '2026-02-28 23:10:21+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/number_theory/factorize.test.cpp
  - test/1_library_checker/number_theory/primitive_root.test.cpp
  - test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
documentation_of: Numeric/pollard_rho.hpp
layout: document
redirect_from:
- /library/Numeric/pollard_rho.hpp
- /library/Numeric/pollard_rho.hpp.html
title: Numeric/pollard_rho.hpp
---
