---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/Combination.hpp
    title: Numeric/Combination.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/DynamicModint.hpp
    title: Numeric/DynamicModint.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/barrett.hpp
    title: Numeric/barrett.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
    links:
    - https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod
  bundledCode: "#line 1 \"test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp\"\
    \n\n#line 2 \"Numeric/Combination.hpp\"\n\n#line 2 \"Numeric/internal_math.hpp\"\
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
    }  // namespace internal\n#line 4 \"Numeric/Combination.hpp\"\n\ntemplate<class\
    \ T>\nrequires std::derived_from<T, internal::modint_base>\nclass Combination\
    \ {\n    inline static int N = 1;\npublic:\n    inline static std::vector<T> fac\
    \ = {T(1)};\n    inline static std::vector<T> ifac = {T(1)};\n    Combination(int\
    \ n) { ensure_upper_bound(n); }\n    Combination(int n, T v) { \n        N = 1;\n\
    \        std::vector<T>(n, v.raw(1)).swap(fac);\n        std::vector<T>(n, v.raw(1)).swap(ifac);\n\
    \        ensure_upper_bound(n);\n    }\n    T C(int n, int m) {\n        if (n\
    \ < m || m < 0) return 0;\n        return fac[n] * ifac[m] * ifac[n - m];\n  \
    \  }\n    T invC(int n, int m) {\n        assert(n >= m && m >= 0);\n        return\
    \ ifac[n] * fac[m] * fac[n - m];\n    }\n    T P(int n, int m) {\n        if (n\
    \ < m) return 0;\n        return fac[n] * ifac[n - m];\n    }\n    T H(int n,\
    \ int m) {\n        return C(n + m - 1, m);\n    }\n    // a - b <= k and all\
    \ non-empty proper prefix have a - b < k\n    T extend_catalan(int a, int b, int\
    \ k) {\n        if (a - b == k) return C(a + b - 1, a - 1) - C(a + b - 1, b +\
    \ k);\n        return C(a + b, a) - C(a + b, b + k); \n    }\n    void ensure_upper_bound(int\
    \ n) {\n        if (N >= n) return;\n        fac.resize(n), ifac.resize(n);\n\
    \        for (int i = N; i < n; ++i)\n            fac[i] = fac[i - 1] * i;\n \
    \       ifac.back() = fac.back().inv();\n        for (int i = n - 2; i >= N; --i)\n\
    \            ifac[i] = ifac[i + 1] * (i + 1);\n        N = n;\n    }\n};\nnamespace\
    \ CombFunc {\ntemplate<class T>\nstd::vector<T> power(T base, int n) {\n    std::vector<T>\
    \ res(n + 1, 1);\n    for (int i = 1; i <= n; ++i)\n        res[i] = res[i - 1]\
    \ * base;\n    return res;\n}\ntemplate<class T>\nstd::vector<T> ipower(T base,\
    \ int n) {\n    return power(base.inv(), n);\n}\ntemplate<class T>\nstd::vector<T>\
    \ linear_inverse(int n) {\n    std::vector<T> res(n + 1, 1);\n    int MOD = T().mod();\n\
    \    for (int i = 2; i <= n; ++i) {\n        res[i] = res[MOD % i] * (MOD - MOD\
    \ / i); \n    }\n    return res;\n}\n}\n#line 2 \"Numeric/DynamicModint.hpp\"\n\
    \n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n#line 2\
    \ \"Numeric/barrett.hpp\"\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nstruct barrett {\n    unsigned\
    \ int _m;\n    unsigned long long im;\n    explicit barrett(unsigned int m) :\
    \ _m(m), im((unsigned long long)(-1) / m + 1) {}\n    unsigned int umod() const\
    \ { return _m; }\n    unsigned int modulo(unsigned long long z) const {\n    \
    \    if (_m == 1) return 0;\n#ifdef _MSC_VER\n        unsigned long long x;\n\
    \        _umul128(z, im, &x);\n#else\n        unsigned long long x = (unsigned\
    \ long long)(((unsigned __int128)(z)*im) >> 64);\n#endif\n        unsigned long\
    \ long y = x * _m;\n        return (z - y + (z < y ? _m : 0));\n    }\n    unsigned\
    \ int mul(unsigned int a, unsigned int b) const {\n        return modulo((unsigned\
    \ long long)a * b);\n    }\n    unsigned long long floor(unsigned long long z)\
    \ const {\n        if (_m == 1) return z;\n        unsigned long long x = (unsigned\
    \ long long)(((unsigned __int128)(z)*im) >> 64);\n        unsigned long long y\
    \ = x * _m;\n        return (z < y ? x - 1 : x);\n    }\n    std::pair<unsigned\
    \ long long, unsigned int> divmod(unsigned long long z) const {\n        if (_m\
    \ == 1) return {z, 0};\n        unsigned long long x = (unsigned long long)(((unsigned\
    \ __int128)(z)*im) >> 64);\n        unsigned long long y = x * _m;\n        if\
    \ (z < y) return {x - 1, z - y + _m};\n        return {x, z - y};\n    }\n};\n\
    #line 6 \"Numeric/DynamicModint.hpp\"\n\ntemplate <int id> struct dynamic_modint\
    \ : internal::modint_base {\n    using mint = dynamic_modint;\n\n  public:\n \
    \   static int mod() { return (int)(bt.umod()); }\n    static void set_mod(int\
    \ m) {\n        assert(1 <= m);\n        bt = barrett(m);\n    }\n    static mint\
    \ raw(int v) {\n        mint x;\n        x._v = v;\n        return x;\n    }\n\
    \n    dynamic_modint() : _v(0) {}\n    template <class T, internal::is_signed_int_t<T>*\
    \ = nullptr>\n    dynamic_modint(T v) {\n        long long x = (long long)(v %\
    \ (long long)(mod()));\n        if (x < 0) x += mod();\n        _v = (unsigned\
    \ int)(x);\n    }\n    template <class T, internal::is_unsigned_int_t<T>* = nullptr>\n\
    \    dynamic_modint(T v) {\n        _v = (unsigned int)(v % mod());\n    }\n\n\
    \    unsigned int val() const { return _v; }\n\n    mint& operator++() {\n   \
    \     _v++;\n        if (_v == umod()) _v = 0;\n        return *this;\n    }\n\
    \    mint& operator--() {\n        if (_v == 0) _v = umod();\n        _v--;\n\
    \        return *this;\n    }\n    mint operator++(int) {\n        mint result\
    \ = *this;\n        ++*this;\n        return result;\n    }\n    mint operator--(int)\
    \ {\n        mint result = *this;\n        --*this;\n        return result;\n\
    \    }\n\n    mint& operator+=(const mint& rhs) {\n        _v += rhs._v;\n   \
    \     if (_v >= umod()) _v -= umod();\n        return *this;\n    }\n    mint&\
    \ operator-=(const mint& rhs) {\n        _v += mod() - rhs._v;\n        if (_v\
    \ >= umod()) _v -= umod();\n        return *this;\n    }\n    mint& operator*=(const\
    \ mint& rhs) {\n        _v = bt.mul(_v, rhs._v);\n        return *this;\n    }\n\
    \    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }\n\
    \n    mint operator+() const { return *this; }\n    mint operator-() const { return\
    \ mint() - *this; }\n\n    mint pow(long long n) const {\n        assert(0 <=\
    \ n);\n        mint x = *this, r = 1;\n        while (n) {\n            if (n\
    \ & 1) r *= x;\n            x *= x;\n            n >>= 1;\n        }\n       \
    \ return r;\n    }\n    mint inv() const {\n        auto eg = internal::inv_gcd(_v,\
    \ mod());\n        assert(eg.first == 1);\n        return eg.second;\n    }\n\n\
    \    friend mint operator+(const mint& lhs, const mint& rhs) {\n        return\
    \ mint(lhs) += rhs;\n    }\n    friend mint operator-(const mint& lhs, const mint&\
    \ rhs) {\n        return mint(lhs) -= rhs;\n    }\n    friend mint operator*(const\
    \ mint& lhs, const mint& rhs) {\n        return mint(lhs) *= rhs;\n    }\n   \
    \ friend mint operator/(const mint& lhs, const mint& rhs) {\n        return mint(lhs)\
    \ /= rhs;\n    }\n    friend bool operator==(const mint& lhs, const mint& rhs)\
    \ {\n        return lhs._v == rhs._v;\n    }\n    friend bool operator!=(const\
    \ mint& lhs, const mint& rhs) {\n        return lhs._v != rhs._v;\n    }\n   \
    \ friend std::strong_ordering operator<=>(const mint& lhs, const mint& rhs) {\n\
    \        return lhs._v <=> rhs._v;\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const mint& v) {\n        os << v._v;\n        return os;\n    }\n    friend\
    \ std::istream& operator>>(std::istream& is, mint& v) {\n        long long x;\n\
    \        is >> x;\n        x %= (long long)(umod());\n        if (x < 0) x +=\
    \ umod();\n        v._v = (unsigned int)(x);\n        return is;\n    }\n\n  private:\n\
    \    unsigned int _v;\n    static barrett bt;\n    static unsigned int umod()\
    \ { return bt.umod(); }\n};\ntemplate <int id> barrett dynamic_modint<id>::bt(998244353);\n\
    \nusing modint = dynamic_modint<-1>;\n\n/*\nmodint::set_mod(p);\n*/\n#line 6 \"\
    test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ t, m;\n    std::cin >> t >> m;\n    modint v;\n    v.set_mod(m);\n    Combination<modint>\
    \ comb(std::min(10000000, m), v);\n    while (t--) {\n        int n, k;\n    \
    \    std::cin >> n >> k;\n        std::cout << comb.C(n, k) << \"\\n\";\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod\"\
    \n#include \"assumption.hpp\"\n\n#include \"Numeric/Combination.hpp\"\n#include\
    \ \"Numeric/DynamicModint.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int t, m;\n    std::cin >> t >> m;\n    modint v;\n  \
    \  v.set_mod(m);\n    Combination<modint> comb(std::min(10000000, m), v);\n  \
    \  while (t--) {\n        int n, k;\n        std::cin >> n >> k;\n        std::cout\
    \ << comb.C(n, k) << \"\\n\";\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Numeric/Combination.hpp
  - Numeric/internal_math.hpp
  - Numeric/DynamicModint.hpp
  - Numeric/barrett.hpp
  isVerificationFile: true
  path: test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
  requiredBy: []
  timestamp: '2026-06-29 01:18:59+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
- /verify/test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp.html
title: test/1_library_checker/enumerative_combinatorics/binomial_coefficient_prime_mod.test.cpp
---
