---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Convolution/bitwise_transform.hpp
    title: Convolution/bitwise_transform.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/bitwise_xor_convolution.test.cpp
    title: test/1_library_checker/convolution/bitwise_xor_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Convolution/xor_convolution.hpp\"\n\n#line 2 \"Convolution/bitwise_transform.hpp\"\
    \n\nnamespace bitwise_transform {\n    // popcount: res[j] = sum_i (-1)^{popcount(i\
    \ & j)}arr[i], ignore type\n    enum target { subset, superset, popcount };\n\
    \    enum type { zeta, mobius };\n    template<target tar, type tp = zeta, typename\
    \ T = long long>\n    void transform(std::vector<T> &arr) {\n        int n = arr.size();\
    \  \n        assert((n & (n - 1)) == 0);\n        for (int L = 2; L <= n; L <<=\
    \ 1)\n            for (int i = 0; i < n; i += L)\n                for (int j =\
    \ i; j < i + (L >> 1); ++j) {\n                    if constexpr (tar == subset)\
    \ {\n                        if constexpr (tp == zeta) arr[j + (L >> 1)] += arr[j];\n\
    \                        else arr[j + (L >> 1)] -= arr[j];\n                 \
    \   }\n                    else if constexpr (tar == superset) {\n           \
    \             if constexpr (tp == zeta) arr[j] += arr[j + (L >> 1)];\n       \
    \                 else arr[j] -= arr[j + (L >> 1)];\n                    }\n \
    \                   else std::tie(arr[j], arr[j + (L >> 1)]) = std::make_pair(arr[j]\
    \ + arr[j + (L >> 1)], arr[j] - arr[j + (L >> 1)]);\n                }\n    }\n\
    \    template<typename T>\n    std::vector<std::vector<T>> ranked_zeta(const std::vector<T>\
    \ &arr) {\n        int n = arr.size(), lg = std::__lg(n);\n        assert((n &\
    \ (n - 1)) == 0);\n        std::vector<std::vector<T>> res(lg + 1, std::vector<T>(n));\n\
    \        for (int i = 0; i < n; ++i)\n            res[std::popcount(static_cast<unsigned\
    \ int>(i))][i] = arr[i];\n        for (int i = 0; i <= lg; ++i)\n            transform<subset,\
    \ zeta>(res[i]);\n        return res;\n    }\n    template<typename T>\n    std::vector<T>\
    \ ranked_mobius(std::vector<std::vector<T>> arr) {\n        int n = arr[0].size(),\
    \ lg = arr.size() - 1;\n        assert((n & (n - 1)) == 0);\n        std::vector<T>\
    \ res(n);\n        for (int i = 0; i <= lg; ++i)\n            transform<subset,\
    \ mobius>(arr[i]);\n        for (int i = 0; i < n; ++i)\n            res[i] =\
    \ arr[std::popcount(static_cast<unsigned int>(i))][i];\n        return res;\n\
    \    }\n}\n#line 2 \"Numeric/internal_math.hpp\"\n// Reference: Atcoder Library\
    \ https://github.com/atcoder/ac-library\n\n#ifdef _MSC_VER\n#include <intrin.h>\n\
    #endif\n\nnamespace internal {\nconstexpr long long safe_mod(long long x, long\
    \ long m) {\n    x %= m;\n    if (x < 0) x += m;\n    return x;\n}\nconstexpr\
    \ long long pow_mod_constexpr(long long x, long long n, int m) {\n    if (m ==\
    \ 1) return 0;\n    unsigned int _m = (unsigned int)(m);\n    unsigned long long\
    \ r = 1;\n    unsigned long long y = safe_mod(x, m);\n    while (n) {\n      \
    \  if (n & 1) r = (r * y) % _m;\n        y = (y * y) % _m;\n        n >>= 1;\n\
    \    }\n    return r;\n}\nconstexpr bool is_prime_constexpr(int n) {\n    if (n\
    \ <= 1) return false;\n    if (n == 2 || n == 7 || n == 61) return true;\n   \
    \ if (n % 2 == 0) return false;\n    long long d = n - 1;\n    while (d % 2 ==\
    \ 0) d /= 2;\n    constexpr long long bases[3] = {2, 7, 61};\n    for (long long\
    \ a : bases) {\n        long long t = d;\n        long long y = pow_mod_constexpr(a,\
    \ t, n);\n        while (t != n - 1 && y != 1 && y != n - 1)\n            y =\
    \ y * y % n, t <<= 1;\n        if (y != n - 1 && t % 2 == 0)\n            return\
    \ false;\n    }\n    return true;\n}\ntemplate <int n> constexpr bool is_prime\
    \ = is_prime_constexpr(n);\nconstexpr std::pair<long long, long long> inv_gcd(long\
    \ long a, long long b) {\n    a = safe_mod(a, b);\n    if (a == 0) return {b,\
    \ 0};\n    long long s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n        long\
    \ long u = s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp = s;\n\
    \        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0 < 0)\
    \ m0 += b / s;\n    return {s, m0};\n}\n}  // namespace internal\n\nnamespace\
    \ internal {\n#ifndef _MSC_VER\n    template <class T>\n        using is_signed_int128\
    \ =\n        typename std::conditional<std::is_same<T, __int128_t>::value ||\n\
    \        std::is_same<T, __int128>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using is_unsigned_int128 =\n        typename\
    \ std::conditional<std::is_same<T, __uint128_t>::value ||\n        std::is_same<T,\
    \ unsigned __int128>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using make_unsigned_int128 =\n        typename\
    \ std::conditional<std::is_same<T, __int128_t>::value,\n                 __uint128_t,\n\
    \                 unsigned __int128>;\n    template <class T>\n        using is_integral\
    \ = typename std::conditional<std::is_integral<T>::value ||\n        is_signed_int128<T>::value\
    \ ||\n        is_unsigned_int128<T>::value,\n        std::true_type,\n       \
    \ std::false_type>::type;\n    template <class T>\n        using is_signed_int\
    \ = typename std::conditional<(is_integral<T>::value &&\n                std::is_signed<T>::value)\
    \ ||\n        is_signed_int128<T>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using is_unsigned_int =\n        typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_unsigned<T>::value) ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<\n        is_signed_int128<T>::value,\n\
    \        make_unsigned_int128<T>,\n        typename std::conditional<std::is_signed<T>::value,\n\
    \        std::make_unsigned<T>,\n        std::common_type<T>>::type>::type;\n\
    #else\n    template <class T> using is_integral = typename std::is_integral<T>;\n\
    \    template <class T>\n        using is_signed_int =\n        typename std::conditional<is_integral<T>::value\
    \ && std::is_signed<T>::value,\n                 std::true_type,\n           \
    \      std::false_type>::type;\n    template <class T>\n        using is_unsigned_int\
    \ =\n        typename std::conditional<is_integral<T>::value &&\n        std::is_unsigned<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<is_signed_int<T>::value,\n\
    \              std::make_unsigned<T>,\n              std::common_type<T>>::type;\n\
    #endif\n    template <class T> using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\n\
    \    template <class T> using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\n\
    \    template <class T> using to_unsigned_t = typename to_unsigned<T>::type;\n\
    \    struct modint_base {};\n    struct static_modint_base : modint_base {};\n\
    \    template <class T> using is_modint = std::is_base_of<modint_base, T>;\n \
    \   template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\
    }  // namespace internal\n#line 5 \"Convolution/xor_convolution.hpp\"\n\ntemplate<typename\
    \ T>\nstd::vector<T> xor_convolution(std::vector<T> a, std::vector<T> b) {\n \
    \   assert(a.size() == b.size());\n    bitwise_transform::transform<bitwise_transform::popcount>(a);\
    \  \n    bitwise_transform::transform<bitwise_transform::popcount>(b);\n    int\
    \ n = a.size();\n    for (int i = 0; i < n; ++i) a[i] *= b[i];\n    bitwise_transform::transform<bitwise_transform::popcount>(a);\n\
    \    if constexpr (std::derived_from<T, internal::modint_base>) {\n        T inv\
    \ = T(n).inv();\n        for (int i = 0; i < n; ++i) a[i] *= inv;\n    }\n   \
    \ else {\n        for (int i = 0; i < n; ++i) a[i] /= n;\n    }\n    return a;\n\
    }\n"
  code: "#pragma once\n\n#include \"Convolution/bitwise_transform.hpp\"\n#include\
    \ \"Numeric/internal_math.hpp\"\n\ntemplate<typename T>\nstd::vector<T> xor_convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n    assert(a.size() == b.size());\n    bitwise_transform::transform<bitwise_transform::popcount>(a);\
    \  \n    bitwise_transform::transform<bitwise_transform::popcount>(b);\n    int\
    \ n = a.size();\n    for (int i = 0; i < n; ++i) a[i] *= b[i];\n    bitwise_transform::transform<bitwise_transform::popcount>(a);\n\
    \    if constexpr (std::derived_from<T, internal::modint_base>) {\n        T inv\
    \ = T(n).inv();\n        for (int i = 0; i < n; ++i) a[i] *= inv;\n    }\n   \
    \ else {\n        for (int i = 0; i < n; ++i) a[i] /= n;\n    }\n    return a;\n\
    }\n"
  dependsOn:
  - Convolution/bitwise_transform.hpp
  - Numeric/internal_math.hpp
  isVerificationFile: false
  path: Convolution/xor_convolution.hpp
  requiredBy: []
  timestamp: '2026-06-14 15:20:09+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/convolution/bitwise_xor_convolution.test.cpp
documentation_of: Convolution/xor_convolution.hpp
layout: document
redirect_from:
- /library/Convolution/xor_convolution.hpp
- /library/Convolution/xor_convolution.hpp.html
title: Convolution/xor_convolution.hpp
---
