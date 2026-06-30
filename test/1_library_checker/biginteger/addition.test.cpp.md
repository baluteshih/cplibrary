---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Misc/bigint.hpp
    title: Misc/bigint.hpp
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/crt.hpp
    title: Numeric/crt.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/internal_primitive_root.hpp
    title: Numeric/internal_primitive_root.hpp
  - icon: ':heavy_check_mark:'
    path: Polynomial/NTT.hpp
    title: Polynomial/NTT.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/addition_of_big_integers
    links:
    - https://judge.yosupo.jp/problem/addition_of_big_integers
  bundledCode: "#line 1 \"test/1_library_checker/biginteger/addition.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/addition_of_big_integers\"\n\
    #line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/biginteger/addition.test.cpp\"\n\n#line 2 \"Misc/bigint.hpp\"\
    \n\n#line 2 \"Numeric/Modint.hpp\"\n\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    #line 2 \"Numeric/internal_math.hpp\"\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
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
    #line 2 \"Polynomial/NTT.hpp\"\n\n#line 2 \"Numeric/internal_primitive_root.hpp\"\
    \n\n#line 4 \"Numeric/internal_primitive_root.hpp\"\n\n// reference: Atcoder Library\
    \ https://github.com/atcoder/ac-library\n\nnamespace internal { \n// Compile time\
    \ primitive root\n// @param m must be prime\n// @return primitive root (and minimum\
    \ in now)\nconstexpr int primitive_root_constexpr(int m) {\n    if (m == 2) return\
    \ 1;\n    if (m == 167772161) return 3;\n    if (m == 469762049) return 3;\n \
    \   if (m == 754974721) return 11;\n    if (m == 998244353) return 3;\n    int\
    \ divs[20] = {};\n    divs[0] = 2;\n    int cnt = 1;\n    int x = (m - 1) / 2;\n\
    \    while (x % 2 == 0) x /= 2;\n    for (int i = 3; (long long)(i)*i <= x; i\
    \ += 2) {\n        if (x % i == 0) {\n            divs[cnt++] = i;\n         \
    \   while (x % i == 0) {\n                x /= i;\n            }\n        }\n\
    \    }\n    if (x > 1) {\n        divs[cnt++] = x;\n    }\n    for (int g = 2;;\
    \ g++) {\n        bool ok = true;\n        for (int i = 0; i < cnt; i++) {\n \
    \           if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {\n         \
    \       ok = false;\n                break;\n            }\n        }\n      \
    \  if (ok) return g;\n    }\n}\ntemplate <int m> constexpr int primitive_root\
    \ = primitive_root_constexpr(m);\n}  // namespace internal\n#line 5 \"Polynomial/NTT.hpp\"\
    \n\ntemplate<typename T>\nrequires std::derived_from<T, internal::modint_base>\n\
    class NTT {\n    inline static int max_size = 1;\n    inline static std::vector<T>\
    \ w{1, T(1)};\n    inline static const T root = internal::primitive_root_constexpr(T::mod());\n\
    \    static void ensure_upper_bound(int n) {\n        if (max_size < n) {\n  \
    \          while (max_size <= n) max_size <<= 1;\n            w.resize(max_size);\n\
    \            std::ranges::fill(w, 1);\n            T dw = root.pow((T::mod() -\
    \ 1) / max_size);\n            for (int s = max_size / 2; s; s >>= 1, dw *= dw)\
    \ {\n                w[s] = 1;\n                for (int j = 1; j < s; ++j) \n\
    \                    w[s + j] = w[s + j - 1] * dw;\n            }\n        }\n\
    \    }\npublic:\n    static constexpr int ntt_max_limit = []() {\n        unsigned\
    \ int m = T::mod() - 1;\n        int limit = 1;\n        while ((m & 1) == 0)\
    \ {\n            limit <<= 1;\n            m >>= 1;\n        }\n        return\
    \ limit;\n    }();\n    static void ntt(std::vector<T> &a, bool inv = false) {\
    \ //0 <= a[i] < P\n        int n = a.size();\n        assert((n & (n - 1)) ==\
    \ 0);\n        ensure_upper_bound(n);\n        for (int i = 0, j = 1; j < n -\
    \ 1; ++j) {\n            for (int k = n >> 1; (i ^= k) < k; k >>= 1);\n      \
    \      if (j < i) std::swap(a[i], a[j]);\n        }\n        for (int s = 1; s\
    \ < n; s <<= 1) {\n            for (int i = 0; i < n; i += s * 2) {\n        \
    \        for (int j = 0; j < s; ++j) {\n                    T tmp = a[i + s +\
    \ j] * w[s + j];\n                    a[i + s + j] = a[i + j] - tmp;\n       \
    \             a[i + j] += tmp;\n                }\n            }\n        }\n\
    \        if (!inv) return;\n        T iv = T(n).inv(); \n        std::reverse(a.begin()\
    \ + 1, a.begin() + n);\n        for (int i = 0; i < n; ++i) a[i] *= iv;\n    }\n\
    \    static size_t maxsize() {\n        return max_size;\n    }\n    static std::vector<T>\
    \ convolution(std::vector<T> a, std::vector<T> b) {\n        if (a.empty() ||\
    \ b.empty()) return std::vector<T>();\n        int n = 1, sz = int(a.size()) +\
    \ int(b.size()) - 1;\n        while (n < sz) n <<= 1;\n        assert(n <= ntt_max_limit\
    \ && \"the result length exceeds the limit of the prime can support\");\n    \
    \    a.resize(n), b.resize(n);\n        ntt(a), ntt(b);\n        for (int i =\
    \ 0; i < n; ++i)\n            a[i] = a[i] * b[i];\n        ntt(a, true);\n   \
    \     a.resize(sz);\n        return a;\n    }\n};\n#line 2 \"Numeric/crt.hpp\"\
    \n\n// source: https://maspypy.github.io/library/mod/crt3.hpp\n\nconstexpr unsigned\
    \ int mod_pow_constexpr(unsigned long long a, unsigned long long n, unsigned int\
    \ mod) {\n    a %= mod;\n    unsigned long long res = 1;\n    for (int i = 0;\
    \ i < 32; ++i) {\n        if (n & 1) res = res * a % mod;\n        a = a * a %\
    \ mod, n /= 2;\n    }\n    return res;\n}\n\ntemplate <typename T, unsigned int\
    \ p0, unsigned int p1>\nT CRT2(unsigned long long a0, unsigned long long a1) {\n\
    \    static_assert(p0 < p1);\n    static constexpr unsigned long long x0_1 = mod_pow_constexpr(p0,\
    \ p1 - 2, p1);\n    unsigned long long c = (a1 - a0 + p1) * x0_1 % p1;\n    return\
    \ a0 + c * p0;\n}\n\ntemplate <typename T, unsigned int p0, unsigned int p1, unsigned\
    \ int p2>\nT CRT3(unsigned long long a0, unsigned long long a1, unsigned long\
    \ long a2) {\n    static_assert(p0 < p1 && p1 < p2);\n    static constexpr unsigned\
    \ long long x1 = mod_pow_constexpr(p0, p1 - 2, p1);\n    static constexpr unsigned\
    \ long long x2 = mod_pow_constexpr((unsigned long long)(p0) * p1 % p2, p2 - 2,\
    \ p2);\n    static constexpr unsigned long long p01 = (unsigned long long)(p0)\
    \ * p1;\n    unsigned long long c = (a1 - a0 + p1) * x1 % p1;\n    unsigned long\
    \ long ans_1 = a0 + c * p0;\n    c = (a2 - ans_1 % p2 + p2) * x2 % p2;\n    return\
    \ T(ans_1) + T(c) * T(p01);\n}\n#line 6 \"Misc/bigint.hpp\"\n\n// source https://maspypy.github.io/library/bigint/base.hpp\
    \ \nstruct BigInteger {\n    static constexpr long long TEN[] = {\n        1LL,\n\
    \        10LL,\n        100LL,\n        1000LL,\n        10000LL,\n        100000LL,\n\
    \        1000000LL,\n        10000000LL,\n        100000000LL,\n        1000000000LL,\n\
    \        10000000000LL,\n        100000000000LL,\n        1000000000000LL,\n \
    \       10000000000000LL,\n        100000000000000LL,\n        1000000000000000LL,\n\
    \        10000000000000000LL,\n        100000000000000000LL,\n        1000000000000000000LL,\n\
    \    };\n    static constexpr int LOG = 9;\n    static constexpr int MOD = TEN[LOG];\n\
    \    using bint = BigInteger;\n    int sgn;\n    std::vector<int> dat;\n\n   \
    \ BigInteger() : sgn(0) {}\n    BigInteger(__int128 val) {\n        if (val ==\
    \ 0) {\n            sgn = 0;\n            return;\n        }\n        sgn = 1;\n\
    \        if (val != 0) {\n            if (val < 0) sgn = -1, val = -val;\n   \
    \         while (val > 0) {\n                dat.push_back(val % MOD), val /=\
    \ MOD;\n            }\n        }\n    }\n    BigInteger(std::string s) {\n   \
    \     assert(!s.empty());\n        sgn = 1;\n        if (s[0] == '-') {\n    \
    \        sgn = -1;\n            s.erase(s.begin());\n            assert(!s.empty());\n\
    \        }\n        if (s[0] == '0') {\n            sgn = 0;\n            return;\n\
    \        }\n        std::ranges::reverse(s);\n        int n = s.size();\n    \
    \    int m = (n + LOG - 1) / LOG;\n        dat.assign(m, 0);\n        for (int\
    \ i = 0; i < n; ++i)\n            dat[i / LOG] += TEN[i % LOG] * int(s[i] - '0');\n\
    \    }\n    bool operator<(const bint &p) const {\n        if (sgn != p.sgn) {\n\
    \            return sgn < p.sgn;\n        }\n        if (sgn == 0) return false;\n\
    \        if (dat.size() != p.dat.size()) {\n            if (sgn == 1) return dat.size()\
    \ < p.dat.size();\n            if (sgn == -1) return dat.size() > p.dat.size();\n\
    \        }\n        for (int i = dat.size() - 1; i >= 0; --i) {\n            if\
    \ (dat[i] == p.dat[i]) continue;\n            if (sgn == 1) return dat[i] < p.dat[i];\n\
    \            if (sgn == -1) return dat[i] > p.dat[i];\n        }\n        return\
    \ false;\n    }\n    bool operator>(const bint &p) const { return p < *this; }\n\
    \    bool operator<=(const bint &p) const { return !(*this > p); }\n    bool operator>=(const\
    \ bint &p) const { return !(*this < p); }\n    bint &operator+=(const bint p)\
    \ {\n        if (sgn == 0) {\n            return *this = p;\n        }\n     \
    \   if (p.sgn == 0) return *this;\n        if (sgn != p.sgn) {\n            *this\
    \ -= (-p);\n            return *this;\n        }\n        int n = std::max(dat.size(),\
    \ p.dat.size());\n        dat.resize(n + 1);\n        for (int i = 0; i < n; ++i)\
    \ {\n            if (i < int(p.dat.size())) dat[i] += p.dat[i];\n            if\
    \ (dat[i] >= MOD) dat[i] -= MOD, dat[i + 1] += 1;\n        }\n        while (!dat.empty()\
    \ && dat.back() == 0) dat.pop_back();\n        if (dat.empty()) sgn = 0;\n   \
    \     return *this;\n    }\n    bint &operator-=(const bint p) {\n        if (p.sgn\
    \ == 0) return *this;\n        if (sgn == 0) return *this = (-p);\n        if\
    \ (sgn != p.sgn) {\n            *this += (-p);\n            return *this;\n  \
    \      }\n        if ((sgn == 1 && *this < p) || (sgn == -1 && *this > p)) {\n\
    \            *this = p - *this;\n            sgn = -sgn;\n            return *this;\n\
    \        }\n        for (int i = 0; i < int(p.dat.size()); ++i)\n            dat[i]\
    \ -= p.dat[i];\n        for (int i = 0; i + 1 < int(dat.size()); ++i) {\n    \
    \        if (dat[i] < 0) dat[i] += MOD, dat[i + 1] -= 1;\n        }\n        while\
    \ (!dat.empty() && dat.back() == 0)\n            dat.pop_back();\n        if (dat.empty())\
    \ sgn = 0;\n        return *this;\n    }\n    bint &operator*=(const bint &p)\
    \ {\n        sgn *= p.sgn;\n        if (sgn == 0) dat.clear();\n        else dat\
    \ = convolve(dat, p.dat);\n        return *this;\n    }\n    // bint &operator/=(const\
    \ bint &p) { return *this; }\n    bint operator-() const {\n        bint p = *this;\n\
    \        p.sgn *= -1;\n        return p;\n    }\n    bint operator+(const bint\
    \ &p) const { return bint(*this) += p; }\n    bint operator-(const bint &p) const\
    \ { return bint(*this) -= p; }\n    bint operator*(const bint &p) const { return\
    \ bint(*this) *= p; }\n    // bint operator/(const modint &p) const { return modint(*this)\
    \ /= p; }\n    bool operator==(const bint &p) const {\n        return (sgn ==\
    \ p.sgn && dat == p.dat);\n    }\n    bool operator!=(const bint &p) const { return\
    \ !((*this) == p); }\n    void swap(bint &other) {\n        std::swap(sgn, other.sgn);\n\
    \        std::swap(dat, other.dat);\n    }\n    std::vector<int> convolve(const\
    \ std::vector<int> &a, const std::vector<int> &b) {\n        int n = a.size(),\
    \ m = b.size();\n        if (!n || !m) return {};\n        if (std::min(n, m)\
    \ <= 500) {\n            std::vector<int> c(n + m - 1);\n            unsigned\
    \ __int128 x = 0;\n            for (int k = 0; k < n + m - 1; ++k) {\n       \
    \         int s = std::max<int>(0, k + 1 - m), t = std::min<int>(k, n - 1);\n\
    \                for (int i = s; i < t + 1; ++i)\n                    x += (unsigned\
    \ long long)(a[i]) * b[k - i];\n                c[k] = x % MOD, x = x / MOD;\n\
    \            }\n            while (x > 0)\n                c.push_back(x % MOD),\
    \ x = x / MOD;\n            return c;\n        }\n        static constexpr int\
    \ p0 = 167772161;\n        static constexpr int p1 = 469762049;\n        static\
    \ constexpr int p2 = 754974721;\n        using mint0 = static_modint<p0>;\n  \
    \      using mint1 = static_modint<p1>;\n        using mint2 = static_modint<p2>;\n\
    \        std::vector<mint0> a0(a.begin(), a.end()), b0(b.begin(), b.end());\n\
    \        std::vector<mint1> a1(a.begin(), a.end()), b1(b.begin(), b.end());\n\
    \        std::vector<mint2> a2(a.begin(), a.end()), b2(b.begin(), b.end());\n\
    \        auto c0 = NTT<mint0>::convolution(a0, b0);\n        auto c1 = NTT<mint1>::convolution(a1,\
    \ b1);\n        auto c2 = NTT<mint2>::convolution(a2, b2);\n        std::vector<int>\
    \ c(c0.size());\n        unsigned __int128 x = 0;\n        for (int i = 0; i <\
    \ n + m - 1; ++i) {\n            x += CRT3<unsigned __int128, p0, p1, p2>(c0[i].val(),\
    \ c1[i].val(), c2[i].val());\n            c[i] = x % MOD, x = x / MOD;\n     \
    \   }\n        while (x)\n            c.push_back(x % MOD), x = x / MOD;\n   \
    \     return c;\n    }\n    std::string to_string() const {\n        if (dat.empty())\
    \ return \"0\";\n        std::string s;\n        for (int x : dat) {\n       \
    \     for (int i = 0; i < LOG; ++i) {\n                s += '0' + (x % 10);\n\
    \                x = x / 10;\n            }\n        }\n        while (s.back()\
    \ == '0') s.pop_back();\n        if (sgn == -1) s += '-';\n        std::ranges::reverse(s);\n\
    \        return s;\n    }\n    friend std::istream& operator>>(std::istream &is,\
    \ bint &p) {\n        std::string s;\n        auto &res = is >> s;\n        p\
    \ = bint(s);\n        return res;\n    }\n    friend std::ostream& operator<<(std::ostream\
    \ &os, const bint &p) { return os << p.to_string(); }\n    // ignore overflow\
    \ \n    long long to_ll() {\n        long long x = 0;\n        for (int i = dat.size()\
    \ - 1; i >= 0; --i)\n            x = MOD * x + dat[i];\n        return sgn * x;\n\
    \    }\n};\n#line 5 \"test/1_library_checker/biginteger/addition.test.cpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int t;\n\
    \    std::cin >> t;\n    while (t--) {\n        BigInteger a, b;\n        std::cin\
    \ >> a >> b;\n        std::cout << a + b << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/addition_of_big_integers\"\
    \n#include \"assumption.hpp\"\n\n#include \"Misc/bigint.hpp\"\n\nint main() {\n\
    \    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int t;\n    std::cin\
    \ >> t;\n    while (t--) {\n        BigInteger a, b;\n        std::cin >> a >>\
    \ b;\n        std::cout << a + b << \"\\n\";\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Misc/bigint.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - Polynomial/NTT.hpp
  - Numeric/internal_primitive_root.hpp
  - Numeric/crt.hpp
  isVerificationFile: true
  path: test/1_library_checker/biginteger/addition.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 13:39:32+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/biginteger/addition.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/biginteger/addition.test.cpp
- /verify/test/1_library_checker/biginteger/addition.test.cpp.html
title: test/1_library_checker/biginteger/addition.test.cpp
---
