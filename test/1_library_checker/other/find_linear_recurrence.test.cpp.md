---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/berlekamp_massey.hpp
    title: Numeric/berlekamp_massey.hpp
  - icon: ':heavy_check_mark:'
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
    PROBLEM: https://judge.yosupo.jp/problem/find_linear_recurrence
    links:
    - https://judge.yosupo.jp/problem/find_linear_recurrence
  bundledCode: "#line 1 \"test/1_library_checker/other/find_linear_recurrence.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\n\
    #line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/other/find_linear_recurrence.test.cpp\"\n\n#line\
    \ 2 \"Numeric/berlekamp_massey.hpp\"\n\ntemplate <typename T>\nstd::vector<T>\
    \ berlekamp_massey(const std::vector<T> &output) {\n    std::vector<T> d(output.size()\
    \ + 1), me, he;\n    for (int f = 0, i = 1; i <= int(output.size()); ++i) {\n\
    \        for (int j = 0; j < int(me.size()); ++j)\n            d[i] += output[i\
    \ - j - 2] * me[j];\n        if ((d[i] -= output[i - 1]) == 0) continue;\n   \
    \     if (me.empty()) {\n            me.resize(f = i);\n            continue;\n\
    \        }\n        std::vector<T> o(i - f - 1);\n        T k = -d[i] / d[f];\n\
    \        o.push_back(-k);\n        for (T x : he) o.push_back(x * k);\n      \
    \  if (o.size() < me.size()) o.resize(me.size());\n        for (int j = 0; j <\
    \ int(me.size()); ++j) o[j] += me[j];\n        if (i - f + int(he.size()) >= int(me.size()))\
    \ he = me, f = i;\n        me = o;\n    }\n    return me;\n}\n#line 2 \"Numeric/Modint.hpp\"\
    \n\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n#line\
    \ 2 \"Numeric/internal_math.hpp\"\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\nconstexpr\
    \ long long safe_mod(long long x, long long m) {\n    x %= m;\n    if (x < 0)\
    \ x += m;\n    return x;\n}\nconstexpr long long pow_mod_constexpr(long long x,\
    \ long long n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m = (unsigned\
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
    #line 6 \"test/1_library_checker/other/find_linear_recurrence.test.cpp\"\n\nusing\
    \ mint = modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n;\n    std::cin >> n;\n    std::vector<mint> arr(n);\n    for (mint\
    \ &i : arr) std::cin >> i;\n    auto ans = berlekamp_massey(arr);\n    std::cout\
    \ << ans.size() << \"\\n\";\n    for (int i = 0; i < int(ans.size()); ++i)\n \
    \       std::cout << ans[i] << \" \\n\"[i + 1 == int(ans.size())];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\
    \n#include \"assumption.hpp\"\n\n#include \"Numeric/berlekamp_massey.hpp\"\n#include\
    \ \"Numeric/Modint.hpp\"\n\nusing mint = modint998244353;\n\nint main() {\n  \
    \  std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n;\n    std::cin >>\
    \ n;\n    std::vector<mint> arr(n);\n    for (mint &i : arr) std::cin >> i;\n\
    \    auto ans = berlekamp_massey(arr);\n    std::cout << ans.size() << \"\\n\"\
    ;\n    for (int i = 0; i < int(ans.size()); ++i)\n        std::cout << ans[i]\
    \ << \" \\n\"[i + 1 == int(ans.size())];\n}\n"
  dependsOn:
  - assumption.hpp
  - Numeric/berlekamp_massey.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  isVerificationFile: true
  path: test/1_library_checker/other/find_linear_recurrence.test.cpp
  requiredBy: []
  timestamp: '2026-10-03 13:08:40+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/other/find_linear_recurrence.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/other/find_linear_recurrence.test.cpp
- /verify/test/1_library_checker/other/find_linear_recurrence.test.cpp.html
title: test/1_library_checker/other/find_linear_recurrence.test.cpp
---
