---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Convolution/OnlineConvolution.hpp
    title: Convolution/OnlineConvolution.hpp
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/internal_primitive_root.hpp
    title: Numeric/internal_primitive_root.hpp
  - icon: ':heavy_check_mark:'
    path: Polynomial/NTT.hpp
    title: Polynomial/NTT.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"test/1_library_checker/convolution/convolution_online.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n#line 2\
    \ \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3\
    \ \"test/1_library_checker/convolution/convolution_online.test.cpp\"\n\n#line\
    \ 2 \"Convolution/OnlineConvolution.hpp\"\n\n// source: https://maspypy.github.io/library/poly/online/online_convolution.hpp\n\
    \n#line 2 \"Polynomial/NTT.hpp\"\n\n#line 2 \"Numeric/Modint.hpp\"\n\n// Reference:\
    \ Atcoder Library https://github.com/atcoder/ac-library\n#line 2 \"Numeric/internal_math.hpp\"\
    \n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\n#ifdef\
    \ _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\nconstexpr long\
    \ long safe_mod(long long x, long long m) {\n    x %= m;\n    if (x < 0) x +=\
    \ m;\n    return x;\n}\nconstexpr long long pow_mod_constexpr(long long x, long\
    \ long n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m = (unsigned\
    \ int)(m);\n    unsigned long long r = 1;\n    unsigned long long y = safe_mod(x,\
    \ m);\n    while (n) {\n        if (n & 1) r = (r * y) % _m;\n        y = (y *\
    \ y) % _m;\n        n >>= 1;\n    }\n    return r;\n}\nconstexpr bool is_prime_constexpr(int\
    \ n) {\n    if (n <= 1) return false;\n    if (n == 2 || n == 7 || n == 61) return\
    \ true;\n    if (n % 2 == 0) return false;\n    long long d = n - 1;\n    while\
    \ (d % 2 == 0) d /= 2;\n    constexpr long long bases[3] = {2, 7, 61};\n    for\
    \ (long long a : bases) {\n        long long t = d;\n        long long y = pow_mod_constexpr(a,\
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
    }  // namespace internal\n#line 5 \"Numeric/Modint.hpp\"\n\ntemplate <int m, std::enable_if_t<(1\
    \ <= m)>* = nullptr>\nstruct static_modint : internal::static_modint_base {\n\
    \    using mint = static_modint;\n\n  public:\n    static constexpr int mod()\
    \ { return m; }\n    static mint raw(int v) {\n        mint x;\n        x._v =\
    \ v;\n        return x;\n    }\n\n    static_modint() : _v(0) {}\n    template\
    \ <class T, internal::is_signed_int_t<T>* = nullptr>\n    static_modint(T v) {\n\
    \        long long x = (long long)(v % (long long)(umod()));\n        if (x <\
    \ 0) x += umod();\n        _v = (unsigned int)(x);\n    }\n    template <class\
    \ T, internal::is_unsigned_int_t<T>* = nullptr>\n    static_modint(T v) {\n  \
    \      _v = (unsigned int)(v % umod());\n    }\n\n    unsigned int val() const\
    \ { return _v; }\n\n    mint& operator++() {\n        _v++;\n        if (_v ==\
    \ umod()) _v = 0;\n        return *this;\n    }\n    mint& operator--() {\n  \
    \      if (_v == 0) _v = umod();\n        _v--;\n        return *this;\n    }\n\
    \    mint operator++(int) {\n        mint result = *this;\n        ++*this;\n\
    \        return result;\n    }\n    mint operator--(int) {\n        mint result\
    \ = *this;\n        --*this;\n        return result;\n    }\n\n    mint& operator+=(const\
    \ mint& rhs) {\n        _v += rhs._v;\n        if (_v >= umod()) _v -= umod();\n\
    \        return *this;\n    }\n    mint& operator-=(const mint& rhs) {\n     \
    \   _v -= rhs._v;\n        if (_v >= umod()) _v += umod();\n        return *this;\n\
    \    }\n    mint& operator*=(const mint& rhs) {\n        unsigned long long z\
    \ = _v;\n        z *= rhs._v;\n        _v = (unsigned int)(z % umod());\n    \
    \    return *this;\n    }\n    mint& operator/=(const mint& rhs) { return *this\
    \ = *this * rhs.inv(); }\n\n    mint operator+() const { return *this; }\n   \
    \ mint operator-() const { return mint() - *this; }\n\n    mint pow(long long\
    \ n) const {\n        assert(0 <= n);\n        mint x = *this, r = 1;\n      \
    \  while (n) {\n            if (n & 1) r *= x;\n            x *= x;\n        \
    \    n >>= 1;\n        }\n        return r;\n    }\n    mint inv() const {\n \
    \       if (prime) {\n            assert(_v);\n            return pow(umod() -\
    \ 2);\n        } else {\n            auto eg = internal::inv_gcd(_v, m);\n   \
    \         assert(eg.first == 1);\n            return eg.second;\n        }\n \
    \   }\n\n    friend mint operator+(const mint& lhs, const mint& rhs) {\n     \
    \   return mint(lhs) += rhs;\n    }\n    friend mint operator-(const mint& lhs,\
    \ const mint& rhs) {\n        return mint(lhs) -= rhs;\n    }\n    friend mint\
    \ operator*(const mint& lhs, const mint& rhs) {\n        return mint(lhs) *= rhs;\n\
    \    }\n    friend mint operator/(const mint& lhs, const mint& rhs) {\n      \
    \  return mint(lhs) /= rhs;\n    }\n    friend bool operator==(const mint& lhs,\
    \ const mint& rhs) {\n        return lhs._v == rhs._v;\n    }\n    friend bool\
    \ operator!=(const mint& lhs, const mint& rhs) {\n        return lhs._v != rhs._v;\n\
    \    }\n    friend std::strong_ordering operator<=>(const mint& lhs, const mint&\
    \ rhs) {\n        return lhs._v <=> rhs._v;\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const mint& v) {\n        os << v._v;\n        return os;\n    }\n    friend\
    \ std::istream& operator>>(std::istream& is, mint& v) {\n        long long x;\n\
    \        is >> x;\n        x %= (long long)(umod());\n        if (x < 0) x +=\
    \ umod();\n        v._v = (unsigned int)(x);\n        return is;\n    }\n\n  private:\n\
    \    unsigned int _v;\n    static constexpr unsigned int umod() { return m; }\n\
    \    static constexpr bool prime = internal::is_prime<m>;\n};\n\nusing modint998244353\
    \ = static_modint<998244353>;\nusing modint1000000007 = static_modint<1000000007>;\n\
    #line 2 \"Numeric/internal_primitive_root.hpp\"\n\n#line 4 \"Numeric/internal_primitive_root.hpp\"\
    \n\n// reference: Atcoder Library https://github.com/atcoder/ac-library\n\nnamespace\
    \ internal { \n// Compile time primitive root\n// @param m must be prime\n// @return\
    \ primitive root (and minimum in now)\nconstexpr int primitive_root_constexpr(int\
    \ m) {\n    if (m == 2) return 1;\n    if (m == 167772161) return 3;\n    if (m\
    \ == 469762049) return 3;\n    if (m == 754974721) return 11;\n    if (m == 998244353)\
    \ return 3;\n    int divs[20] = {};\n    divs[0] = 2;\n    int cnt = 1;\n    int\
    \ x = (m - 1) / 2;\n    while (x % 2 == 0) x /= 2;\n    for (int i = 3; (long\
    \ long)(i)*i <= x; i += 2) {\n        if (x % i == 0) {\n            divs[cnt++]\
    \ = i;\n            while (x % i == 0) {\n                x /= i;\n          \
    \  }\n        }\n    }\n    if (x > 1) {\n        divs[cnt++] = x;\n    }\n  \
    \  for (int g = 2;; g++) {\n        bool ok = true;\n        for (int i = 0; i\
    \ < cnt; i++) {\n            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) ==\
    \ 1) {\n                ok = false;\n                break;\n            }\n \
    \       }\n        if (ok) return g;\n    }\n}\ntemplate <int m> constexpr int\
    \ primitive_root = primitive_root_constexpr(m);\n}  // namespace internal\n#line\
    \ 5 \"Polynomial/NTT.hpp\"\n\ntemplate<typename T>\nrequires std::derived_from<T,\
    \ internal::modint_base>\nclass NTT {\n    inline static int max_size = 1;\n \
    \   inline static std::vector<T> w{1, T(1)};\n    inline static const T root =\
    \ internal::primitive_root_constexpr(T::mod());\n    static void ensure_upper_bound(int\
    \ n) {\n        if (max_size < n) {\n            while (max_size <= n) max_size\
    \ <<= 1;\n            w.resize(max_size);\n            std::ranges::fill(w, 1);\n\
    \            T dw = root.pow((T::mod() - 1) / max_size);\n            for (int\
    \ s = max_size / 2; s; s >>= 1, dw *= dw) {\n                w[s] = 1;\n     \
    \           for (int j = 1; j < s; ++j) \n                    w[s + j] = w[s +\
    \ j - 1] * dw;\n            }\n        }\n    }\npublic:\n    static constexpr\
    \ int ntt_max_limit = []() {\n        unsigned int m = T::mod() - 1;\n       \
    \ int limit = 1;\n        while ((m & 1) == 0) {\n            limit <<= 1;\n \
    \           m >>= 1;\n        }\n        return limit;\n    }();\n    static void\
    \ ntt(std::vector<T> &a, bool inv = false) { //0 <= a[i] < P\n        int n =\
    \ a.size();\n        assert((n & (n - 1)) == 0);\n        ensure_upper_bound(n);\n\
    \        for (int i = 0, j = 1; j < n - 1; ++j) {\n            for (int k = n\
    \ >> 1; (i ^= k) < k; k >>= 1);\n            if (j < i) std::swap(a[i], a[j]);\n\
    \        }\n        for (int s = 1; s < n; s <<= 1) {\n            for (int i\
    \ = 0; i < n; i += s * 2) {\n                for (int j = 0; j < s; ++j) {\n \
    \                   T tmp = a[i + s + j] * w[s + j];\n                    a[i\
    \ + s + j] = a[i + j] - tmp;\n                    a[i + j] += tmp;\n         \
    \       }\n            }\n        }\n        if (!inv) return;\n        T iv =\
    \ T(n).inv(); \n        std::reverse(a.begin() + 1, a.begin() + n);\n        for\
    \ (int i = 0; i < n; ++i) a[i] *= iv;\n    }\n    static size_t maxsize() {\n\
    \        return max_size;\n    }\n    static std::vector<T> convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n        if (a.empty() || b.empty()) return std::vector<T>();\n\
    \        int n = 1, sz = int(a.size()) + int(b.size()) - 1;\n        while (n\
    \ < sz) n <<= 1;\n        assert(n <= ntt_max_limit && \"the result length exceeds\
    \ the limit of the prime can support\");\n        a.resize(n), b.resize(n);\n\
    \        ntt(a), ntt(b);\n        for (int i = 0; i < n; ++i)\n            a[i]\
    \ = a[i] * b[i];\n        ntt(a, true);\n        a.resize(sz);\n        return\
    \ a;\n    }\n};\n#line 6 \"Convolution/OnlineConvolution.hpp\"\n\ntemplate<typename\
    \ T>\nstruct OnlineConvolution {\n    std::vector<T> f, g, h, fm, gm;\n    int\
    \ p;\n    \n    OnlineConvolution() : p(0) {}\n\n    T query(int idx, T f_i, T\
    \ g_i) {\n        assert(idx == p);\n        f.push_back(f_i), g.push_back(g_i);\n\
    \        int z = __builtin_ctz(p + 2), w = 1 << z, s;\n        std::vector<T>\
    \ b0, b1;\n        if (p + 2 == w) {\n            b0 = f, b0.resize(2 * w);\n\
    \            NTT<T>::ntt(b0, false);\n            b1 = g, b1.resize(2 * w);\n\
    \            NTT<T>::ntt(b1, false);\n            fm.resize(w << 1), gm.resize(w\
    \ << 1);\n            for (int i = 0; i < w; ++i) fm[i + w] = b0[i * 2], gm[i\
    \ + w] = b1[i * 2];\n            for (int i = 0; i < 2 * w; ++i) b0[i] *= b1[i];\n\
    \            s = w - 2;\n            h.resize(2 * s + 2);\n        }\n       \
    \ else {\n            b0.assign(f.end() - w, f.end()), b0.resize(2 * w);\n   \
    \         NTT<T>::ntt(b0, false);\n            for (int i = 0; i < 2 * w; ++i)\
    \ b0[i] *= gm[i + (w << 1)];\n            b1.assign(g.end() - w, g.end()), b1.resize(2\
    \ * w);\n            NTT<T>::ntt(b1, false);\n            for (int i = 0; i <\
    \ 2 * w; ++i) b0[i] += b1[i] * fm[i + (w << 1)];\n            s = w - 1;\n   \
    \     }\n        NTT<T>::ntt(b0, true);\n        for (int i = 0; i <= s; ++i)\
    \ h[p + i] += b0[s + i];\n        return h[p++];\n    }\n};\n#line 5 \"test/1_library_checker/convolution/convolution_online.test.cpp\"\
    \n\nusing mint = modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n, m;\n    std::cin >> n >> m;\n    std::vector<mint>\
    \ arr(n), brr(m);\n    for (auto &i : arr)\n        std::cin >> i;\n    for (auto\
    \ &i : brr)\n        std::cin >> i;\n    arr.resize(n + m - 1);\n    brr.resize(n\
    \ + m - 1);\n    OnlineConvolution<mint> conv;\n    for (int i = 0; i < n + m\
    \ - 1; ++i)\n        std::cout << conv.query(i, arr[i], brr[i]) << \" \\n\"[i\
    \ + 1 == int(arr.size())];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n#include\
    \ \"assumption.hpp\"\n\n#include \"Convolution/OnlineConvolution.hpp\"\n\nusing\
    \ mint = modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n, m;\n    std::cin >> n >> m;\n    std::vector<mint> arr(n), brr(m);\n\
    \    for (auto &i : arr)\n        std::cin >> i;\n    for (auto &i : brr)\n  \
    \      std::cin >> i;\n    arr.resize(n + m - 1);\n    brr.resize(n + m - 1);\n\
    \    OnlineConvolution<mint> conv;\n    for (int i = 0; i < n + m - 1; ++i)\n\
    \        std::cout << conv.query(i, arr[i], brr[i]) << \" \\n\"[i + 1 == int(arr.size())];\n\
    }\n"
  dependsOn:
  - assumption.hpp
  - Convolution/OnlineConvolution.hpp
  - Polynomial/NTT.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - Numeric/internal_primitive_root.hpp
  isVerificationFile: true
  path: test/1_library_checker/convolution/convolution_online.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 14:01:32+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/convolution/convolution_online.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/convolution/convolution_online.test.cpp
- /verify/test/1_library_checker/convolution/convolution_online.test.cpp.html
title: test/1_library_checker/convolution/convolution_online.test.cpp
---
