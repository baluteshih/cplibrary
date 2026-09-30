---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/fast_gcd.hpp\"\n\ntemplate <typename T> struct make_unsigned_cp\
    \ { using type = std::make_unsigned_t<T>; };\ntemplate <> struct make_unsigned_cp<__int128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned_cp<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <typename T> using make_unsigned_cp_t\
    \ = typename make_unsigned_cp<T>::type;\n\ntemplate <typename T>\ninline int ctz(T\
    \ x) {\n    if constexpr (sizeof(T) <= 4) return __builtin_ctz(x);\n    else if\
    \ constexpr (sizeof(T) <= 8) return __builtin_ctzll(x);\n    else {\n        uint64_t\
    \ lo = x;\n        return lo ? __builtin_ctzll(lo) : 64 + __builtin_ctzll(x >>\
    \ 64);\n    }\n}\n\ntemplate <typename T>\ninline T fast_gcd(T a, T b) {\n   \
    \ using U = make_unsigned_cp_t<T>;\n    U ua, ub;\n\n    if constexpr (T(-1) <\
    \ T(0)) {\n        ua = a < 0 ? -static_cast<U>(a) : static_cast<U>(a);\n    \
    \    ub = b < 0 ? -static_cast<U>(b) : static_cast<U>(b);\n    }\n    else {\n\
    \        ua = a;\n        ub = b;\n    }\n\n    if (!ua || !ub) return static_cast<T>(ua\
    \ | ub);\n\n    int shift = ctz(ua | ub);\n    ua >>= ctz(ua);\n    \n    while\
    \ (ub) {\n        ub >>= ctz(ub);\n        if (ua > ub) std::swap(ua, ub);\n \
    \       ub -= ua;\n    }\n    \n    return static_cast<T>(ua << shift);\n}\n"
  code: "#pragma once\n\ntemplate <typename T> struct make_unsigned_cp { using type\
    \ = std::make_unsigned_t<T>; };\ntemplate <> struct make_unsigned_cp<__int128_t>\
    \ { using type = __uint128_t; };\ntemplate <> struct make_unsigned_cp<__uint128_t>\
    \ { using type = __uint128_t; };\ntemplate <typename T> using make_unsigned_cp_t\
    \ = typename make_unsigned_cp<T>::type;\n\ntemplate <typename T>\ninline int ctz(T\
    \ x) {\n    if constexpr (sizeof(T) <= 4) return __builtin_ctz(x);\n    else if\
    \ constexpr (sizeof(T) <= 8) return __builtin_ctzll(x);\n    else {\n        uint64_t\
    \ lo = x;\n        return lo ? __builtin_ctzll(lo) : 64 + __builtin_ctzll(x >>\
    \ 64);\n    }\n}\n\ntemplate <typename T>\ninline T fast_gcd(T a, T b) {\n   \
    \ using U = make_unsigned_cp_t<T>;\n    U ua, ub;\n\n    if constexpr (T(-1) <\
    \ T(0)) {\n        ua = a < 0 ? -static_cast<U>(a) : static_cast<U>(a);\n    \
    \    ub = b < 0 ? -static_cast<U>(b) : static_cast<U>(b);\n    }\n    else {\n\
    \        ua = a;\n        ub = b;\n    }\n\n    if (!ua || !ub) return static_cast<T>(ua\
    \ | ub);\n\n    int shift = ctz(ua | ub);\n    ua >>= ctz(ua);\n    \n    while\
    \ (ub) {\n        ub >>= ctz(ub);\n        if (ua > ub) std::swap(ua, ub);\n \
    \       ub -= ua;\n    }\n    \n    return static_cast<T>(ua << shift);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/fast_gcd.hpp
  requiredBy: []
  timestamp: '2026-09-30 15:40:33+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Numeric/fast_gcd.hpp
layout: document
redirect_from:
- /library/Numeric/fast_gcd.hpp
- /library/Numeric/fast_gcd.hpp.html
title: Numeric/fast_gcd.hpp
---
