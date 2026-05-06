---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/miller_rabin.hpp
    title: Numeric/miller_rabin.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/mod_inv.hpp
    title: Numeric/mod_inv.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/mod_pow.hpp
    title: Numeric/mod_pow.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/pollard_rho.hpp
    title: Numeric/pollard_rho.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/primitive_root.hpp
    title: Numeric/primitive_root.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://maspypy.github.io/library/mod/binomial.hpp
  bundledCode: "#line 2 \"Numeric/Binomial.hpp\"\n\n#line 2 \"Numeric/internal_math.hpp\"\
    \n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\n#include\
    \ <utility>\n#include <cassert>\n#include <numeric>\n#include <type_traits>\n\n\
    #ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\n\n// @param\
    \ m `1 <= m`\n// @return x mod m\nconstexpr long long safe_mod(long long x, long\
    \ long m) {\n    x %= m;\n    if (x < 0) x += m;\n    return x;\n}\n\n// Fast\
    \ modular multiplication by barrett reduction\n// Reference: https://en.wikipedia.org/wiki/Barrett_reduction\n\
    // NOTE: reconsider after Ice Lake\nstruct barrett {\n    unsigned int _m;\n \
    \   unsigned long long im;\n    explicit barrett(unsigned int m) : _m(m), im((unsigned\
    \ long long)(-1) / m + 1) {}\n    unsigned int umod() const { return _m; }\n \
    \   unsigned int modulo(unsigned long long z) const {\n        if (_m == 1) return\
    \ 0;\n#ifdef _MSC_VER\n        unsigned long long x;\n        _umul128(z, im,\
    \ &x);\n#else\n        unsigned long long x = (unsigned long long)(((unsigned\
    \ __int128)(z)*im) >> 64);\n#endif\n        unsigned long long y = x * _m;\n \
    \       return (z - y + (z < y ? _m : 0));\n    }\n    unsigned int mul(unsigned\
    \ int a, unsigned int b) const {\n        return modulo((unsigned long long)a\
    \ * b);\n    }\n    unsigned long long floor(unsigned long long z) const {\n \
    \       if (_m == 1) return z;\n        unsigned long long x = (unsigned long\
    \ long)(((unsigned __int128)(z)*im) >> 64);\n        unsigned long long y = x\
    \ * _m;\n        return (z < y ? x - 1 : x);\n    }\n    std::pair<unsigned long\
    \ long, unsigned int> divmod(unsigned long long z) const {\n        if (_m ==\
    \ 1) return {z, 0};\n        unsigned long long x = (unsigned long long)(((unsigned\
    \ __int128)(z)*im) >> 64);\n        unsigned long long y = x * _m;\n        if\
    \ (z < y) return {x - 1, z - y + _m};\n        return {x, z - y};\n    }\n};\n\
    \n// @param n `0 <= n`\n// @param m `1 <= m`\n// @return `(x ** n) % m`\nconstexpr\
    \ long long pow_mod_constexpr(long long x, long long n, int m) {\n    if (m ==\
    \ 1) return 0;\n    unsigned int _m = (unsigned int)(m);\n    unsigned long long\
    \ r = 1;\n    unsigned long long y = safe_mod(x, m);\n    while (n) {\n      \
    \  if (n & 1) r = (r * y) % _m;\n        y = (y * y) % _m;\n        n >>= 1;\n\
    \    }\n    return r;\n}\n\n// Reference:\n// M. Forisek and J. Jancina,\n// Fast\
    \ Primality Testing for Integers That Fit into a Machine Word\n// @param n `0\
    \ <= n`\nconstexpr bool is_prime_constexpr(int n) {\n    if (n <= 1) return false;\n\
    \    if (n == 2 || n == 7 || n == 61) return true;\n    if (n % 2 == 0) return\
    \ false;\n    long long d = n - 1;\n    while (d % 2 == 0) d /= 2;\n    constexpr\
    \ long long bases[3] = {2, 7, 61};\n    for (long long a : bases) {\n        long\
    \ long t = d;\n        long long y = pow_mod_constexpr(a, t, n);\n        while\
    \ (t != n - 1 && y != 1 && y != n - 1) {\n            y = y * y % n;\n       \
    \     t <<= 1;\n        }\n        if (y != n - 1 && t % 2 == 0) {\n         \
    \   return false;\n        }\n    }\n    return true;\n}\ntemplate <int n> constexpr\
    \ bool is_prime = is_prime_constexpr(n);\n\n// @param b `1 <= b`\n// @return pair(g,\
    \ x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g\nconstexpr std::pair<long\
    \ long, long long> inv_gcd(long long a, long long b) {\n    a = safe_mod(a, b);\n\
    \    if (a == 0) return {b, 0};\n\n    // Contracts:\n    // [1] s - m0 * a =\
    \ 0 (mod b)\n    // [2] t - m1 * a = 0 (mod b)\n    // [3] s * |m1| + t * |m0|\
    \ <= b\n    long long s = b, t = a;\n    long long m0 = 0, m1 = 1;\n\n    while\
    \ (t) {\n        long long u = s / t;\n        s -= t * u;\n        m0 -= m1 *\
    \ u;  // |m1 * u| <= |m1| * s <= b\n\n        // [3]:\n        // (s - t * u)\
    \ * |m1| + t * |m0 - m1 * u|\n        // <= s * |m1| - t * u * |m1| + t * (|m0|\
    \ + |m1| * u)\n        // = s * |m1| + t * |m0| <= b\n\n        auto tmp = s;\n\
    \        s = t;\n        t = tmp;\n        tmp = m0;\n        m0 = m1;\n     \
    \   m1 = tmp;\n    }\n    // by [3]: |m0| <= b/g\n    // by g != b: |m0| < b/g\n\
    \    if (m0 < 0) m0 += b / s;\n    return {s, m0};\n}\n}  // namespace internal\n\
    \nnamespace internal {\n\n#ifndef _MSC_VER\n    template <class T>\n        using\
    \ is_signed_int128 =\n        typename std::conditional<std::is_same<T, __int128_t>::value\
    \ ||\n        std::is_same<T, __int128>::value,\n        std::true_type,\n   \
    \     std::false_type>::type;\n\n    template <class T>\n        using is_unsigned_int128\
    \ =\n        typename std::conditional<std::is_same<T, __uint128_t>::value ||\n\
    \        std::is_same<T, unsigned __int128>::value,\n        std::true_type,\n\
    \        std::false_type>::type;\n\n    template <class T>\n        using make_unsigned_int128\
    \ =\n        typename std::conditional<std::is_same<T, __int128_t>::value,\n \
    \                __uint128_t,\n                 unsigned __int128>;\n\n    template\
    \ <class T>\n        using is_integral = typename std::conditional<std::is_integral<T>::value\
    \ ||\n        is_signed_int128<T>::value ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using is_signed_int = typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_signed<T>::value) ||\n        is_signed_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using is_unsigned_int =\n        typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_unsigned<T>::value) ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<\n        is_signed_int128<T>::value,\n\
    \        make_unsigned_int128<T>,\n        typename std::conditional<std::is_signed<T>::value,\n\
    \        std::make_unsigned<T>,\n        std::common_type<T>>::type>::type;\n\n\
    #else\n\n    template <class T> using is_integral = typename std::is_integral<T>;\n\
    \n    template <class T>\n        using is_signed_int =\n        typename std::conditional<is_integral<T>::value\
    \ && std::is_signed<T>::value,\n                 std::true_type,\n           \
    \      std::false_type>::type;\n\n    template <class T>\n        using is_unsigned_int\
    \ =\n        typename std::conditional<is_integral<T>::value &&\n        std::is_unsigned<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<is_signed_int<T>::value,\n\
    \              std::make_unsigned<T>,\n              std::common_type<T>>::type;\n\
    \n#endif\n\n    template <class T>\n        using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\n\
    \n    template <class T>\n        using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\n\
    \n    template <class T> using to_unsigned_t = typename to_unsigned<T>::type;\n\
    \n}  // namespace internal\n\n#line 229 \"Numeric/internal_math.hpp\"\n\n#ifdef\
    \ _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\n\n    struct\
    \ modint_base {};\n    struct static_modint_base : modint_base {};\n\n    template\
    \ <class T> using is_modint = std::is_base_of<modint_base, T>;\n    template <class\
    \ T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\n}  // namespace\
    \ internal\n#line 2 \"Numeric/primitive_root.hpp\"\n\n#line 2 \"Numeric/pollard_rho.hpp\"\
    \n\n#line 2 \"Numeric/miller_rabin.hpp\"\n\ntemplate<typename T>\nbool _miller_rabin(T\
    \ a, T n) {\n    if ((a = a % n) == 0) return 1;\n    if ((n & 1) ^ 1) return\
    \ n == 2;\n    static auto mul = [&](T x, T y, T mod) {\n        if constexpr\
    \ (sizeof(T) == 4) return (long long)x * y % mod;\n        else return (__int128)x\
    \ * y % mod;\n    };\n    T t = std::countr_zero(std::make_unsigned_t<T>(n - 1)),\
    \ x = 1;\n    T tmp = (n - 1) >> t;\n    for (; tmp; tmp >>= 1, a = mul(a, a,\
    \ n))\n        if(tmp & 1) x = mul(x, a, n);\n    if (x == 1 || x == n - 1) return\
    \ 1;\n    while (--t)\n        if ((x = mul(x, x, n)) == n - 1) return 1;\n  \
    \  return 0;\n}\n\ntemplate<typename T>\nbool miller_rabin(T n) {\n    if (n ==\
    \ 1) return false;\n    static std::vector<T> _base[4] = {{2, 7, 61}, {2, 13,\
    \ 23, 1662803}, {2, 3, 5, 7, 11, 13}, {2, 325, 9375, 28178, 450775, 9780504, 1795265022}};\n\
    \    std::vector<T> base =\n        (n < 4759123141ll) ? _base[0] :\n        (n\
    \ < 1122004669633ll) ? _base[1] :\n        (n < 3474749660383ll) ? _base[2] :\
    \ _base[3];\n    for (T b : base)\n        if (!_miller_rabin(b, n))\n       \
    \     return false;\n    return true;\n}\n#line 4 \"Numeric/pollard_rho.hpp\"\n\
    \n/*\nreturn an unsorted prime list\n*/\ntemplate<typename T>\nstd::vector<T>\
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
    \ self(self, d);\n    };\n    factorize(factorize, n);\n    return res;\n}\n#line\
    \ 2 \"Numeric/mod_pow.hpp\"\n\ntemplate<typename T>\nT mod_pow(T a, long long\
    \ n, T mod) {\n    assert(n >= 0);\n    if (mod == 1) return 0;\n    a = ((a %=\
    \ mod) < 0 ? a + mod : a);\n    static auto mul = [&](T x, T y, T _mod) {\n  \
    \      if constexpr (sizeof(T) == 4) return (long long)x * y % _mod;\n       \
    \ else return (__int128)x * y % _mod;\n    };\n    T res = 1;\n    for (; n; n\
    \ >>= 1, a = mul(a, a, mod))\n        if (n & 1)\n            res = mul(res, a,\
    \ mod);\n    return res;\n}\n#line 5 \"Numeric/primitive_root.hpp\"\n\ntemplate<typename\
    \ T>\nT primitive_root(T p) {\n    auto pfacs = pollard_rho(p - 1);\n    std::ranges::sort(pfacs);\n\
    \    pfacs.erase(std::ranges::unique(pfacs).begin(), pfacs.end());\n    auto check\
    \ = [&](T g) -> bool {\n        for (auto pf : pfacs)\n            if (mod_pow(g,\
    \ (p - 1) / pf, p) == 1) return false;\n        return true;\n    };\n    std::conditional_t<sizeof(T)\
    \ == 4, std::mt19937, std::mt19937_64> rng(880301);\n    while (1) {\n       \
    \ T x = rng() % (p - 1) + 1;\n        if (check(x)) return x;\n    }\n    return\
    \ -1;\n}\n#line 2 \"Numeric/mod_inv.hpp\"\n\ntemplate<typename T>\nT mod_inv(T\
    \ val, T mod) {\n    if (mod == 0) return 0;\n    mod = std::abs(mod);\n    val\
    \ %= mod;\n    if (val < 0) val += mod;\n    T a = val, b = mod, u = 1, v = 0,\
    \ t;\n    while (b > 0) {\n        t = a / b;\n        swap(a -= t * b, b), swap(u\
    \ -= t * v, v);\n    }\n    if (u < 0) u += mod;\n    return u;\n}\n#line 7 \"\
    Numeric/Binomial.hpp\"\n\n// source: https://maspypy.github.io/library/mod/binomial.hpp\n\
    struct BinomialPrimePower {\n    using barrett = internal::barrett;\n    int p,\
    \ e, pp, root, ord;\n    std::vector<int> exp, log_fact, power;\n    barrett bt_p,\
    \ bt_pp;\n    BinomialPrimePower(int _p, int _e) : p(_p), e(_e), power(e + 1,\
    \ 1), bt_p(1), bt_pp(1) {\n        for (int i = 0; i < e; ++i) power[i + 1] =\
    \ power[i] * p;\n        pp = power[e];\n        bt_p = barrett(p), bt_pp = barrett(pp);\n\
    \        std::vector<int> log;\n        if (p == 2) {\n            if (e <= 1)\
    \ { return; }\n            root = 5;\n            ord = pp / 4;\n            exp.assign(ord,\
    \ 1);\n            log.assign(pp, 0);\n            for (int i = 0; i < ord - 1;\
    \ ++i) { exp[i + 1] = (exp[i] * root) & (pp - 1); }\n            for (int i =\
    \ 0; i < ord; ++i) log[exp[i]] = log[pp - exp[i]] = i;\n        }\n        else\
    \ {\n            root = primitive_root(p);\n            ord = pp / p * (p - 1);\n\
    \            exp.assign(ord, 1);\n            log.assign(pp, 0);\n           \
    \ for (int i = 0; i < ord - 1; ++i) { exp[i + 1] = bt_pp.mul(exp[i], root); }\n\
    \            for (int i = 0; i < ord; ++i) log[exp[i]] = i;\n        }\n     \
    \   log_fact.assign(pp, 0);\n        for (int i = 1; i < pp; ++i) {\n        \
    \    log_fact[i] = log_fact[i - 1] + log[i];\n            if (log_fact[i] >= ord)\
    \ log_fact[i] -= ord;\n        }\n    }\n    int C(long long n, long long i) {\n\
    \        assert(n >= 0);\n        if (i < 0 || i > n) return 0;\n        long\
    \ long a = i, b = n - i;\n        if (pp == 2) { return ((a & b) == 0 ? 1 : 0);\
    \ }\n        int log = 0, cnt_p = 0, sgn = 0;\n        if (e > 1) {\n        \
    \    while (n && cnt_p < e) {\n                auto [n1, nr1] = bt_pp.divmod(n);\n\
    \                auto [a1, ar1] = bt_pp.divmod(a);\n                auto [b1,\
    \ br1] = bt_pp.divmod(b);\n                log += log_fact[nr1] - log_fact[ar1]\
    \ - log_fact[br1];\n                if (p > 2) sgn += (n1 & 1) + (a1 & 1) + (b1\
    \ & 1);\n                else sgn += (((nr1 + 1) & 4) + ((ar1 + 1) & 4) + ((br1\
    \ + 1) & 4)) / 4;\n                n = bt_p.floor(n), a = bt_p.floor(a), b = bt_p.floor(b);\n\
    \                cnt_p += n - a - b;\n            }\n        }\n        else {\n\
    \            while (n && cnt_p < e) {\n                auto [n1, nr1] = bt_pp.divmod(n);\n\
    \                auto [a1, ar1] = bt_pp.divmod(a);\n                auto [b1,\
    \ br1] = bt_pp.divmod(b);\n                log += log_fact[nr1] - log_fact[ar1]\
    \ - log_fact[br1];\n                if (p > 2)\n                    sgn += (n1\
    \ & 1) + (a1 & 1) + (b1 & 1);\n                else\n                    sgn +=\
    \ ((nr1 + 1) >> 2 & 1) + ((ar1 + 1) >> 2 & 1) + ((br1 + 1) >> 2 & 1);\n      \
    \          n = n1, a = a1, b = b1;\n                cnt_p += n - a - b;\n    \
    \        }\n        }\n        if (cnt_p >= e) return 0;\n        log %= ord;\n\
    \        if (log < 0) log += ord;\n        int res = exp[log];\n        if (sgn\
    \ & 1) res = pp - res;\n        return bt_pp.mul(power[cnt_p], res);\n    }\n\
    };\n\nstruct Binomial {\n    using barrett = internal::barrett;\n    int mod;\n\
    \    std::vector<BinomialPrimePower> BPP;\n    std::vector<int> crt_coef;\n  \
    \  barrett bt;\n    Binomial(int _mod) : mod(_mod), bt(mod) {\n        auto pfacs\
    \ = pollard_rho(mod);\n        std::ranges::sort(pfacs);\n        for (int i =\
    \ 0, j = 0; i < int(pfacs.size()); i = j) {\n            int pp = 1;\n       \
    \     while (j < int(pfacs.size()) && pfacs[i] == pfacs[j]) ++j, pp *= pfacs[i];\n\
    \            BPP.emplace_back(pfacs[i], j - i);\n            int other = mod /\
    \ pp;\n            crt_coef.push_back((long long)other * mod_inv(other, pp) %\
    \ mod);\n        }\n    }\n    int C(long long n, long long k) {\n        assert(n\
    \ >= 0);\n        if (k < 0 || k > n) return 0;\n        int ans = 0;\n      \
    \  for (int s = 0; s < int(crt_coef.size()); ++s)\n            ans = bt.modulo(ans\
    \ + (unsigned long long)(BPP[s].C(n, k)) * crt_coef[s]);\n        return ans;\n\
    \    }\n};\n"
  code: "#pragma once\n\n#include \"Numeric/internal_math.hpp\"\n#include \"Numeric/primitive_root.hpp\"\
    \n#include \"Numeric/pollard_rho.hpp\"\n#include \"Numeric/mod_inv.hpp\"\n\n//\
    \ source: https://maspypy.github.io/library/mod/binomial.hpp\nstruct BinomialPrimePower\
    \ {\n    using barrett = internal::barrett;\n    int p, e, pp, root, ord;\n  \
    \  std::vector<int> exp, log_fact, power;\n    barrett bt_p, bt_pp;\n    BinomialPrimePower(int\
    \ _p, int _e) : p(_p), e(_e), power(e + 1, 1), bt_p(1), bt_pp(1) {\n        for\
    \ (int i = 0; i < e; ++i) power[i + 1] = power[i] * p;\n        pp = power[e];\n\
    \        bt_p = barrett(p), bt_pp = barrett(pp);\n        std::vector<int> log;\n\
    \        if (p == 2) {\n            if (e <= 1) { return; }\n            root\
    \ = 5;\n            ord = pp / 4;\n            exp.assign(ord, 1);\n         \
    \   log.assign(pp, 0);\n            for (int i = 0; i < ord - 1; ++i) { exp[i\
    \ + 1] = (exp[i] * root) & (pp - 1); }\n            for (int i = 0; i < ord; ++i)\
    \ log[exp[i]] = log[pp - exp[i]] = i;\n        }\n        else {\n           \
    \ root = primitive_root(p);\n            ord = pp / p * (p - 1);\n           \
    \ exp.assign(ord, 1);\n            log.assign(pp, 0);\n            for (int i\
    \ = 0; i < ord - 1; ++i) { exp[i + 1] = bt_pp.mul(exp[i], root); }\n         \
    \   for (int i = 0; i < ord; ++i) log[exp[i]] = i;\n        }\n        log_fact.assign(pp,\
    \ 0);\n        for (int i = 1; i < pp; ++i) {\n            log_fact[i] = log_fact[i\
    \ - 1] + log[i];\n            if (log_fact[i] >= ord) log_fact[i] -= ord;\n  \
    \      }\n    }\n    int C(long long n, long long i) {\n        assert(n >= 0);\n\
    \        if (i < 0 || i > n) return 0;\n        long long a = i, b = n - i;\n\
    \        if (pp == 2) { return ((a & b) == 0 ? 1 : 0); }\n        int log = 0,\
    \ cnt_p = 0, sgn = 0;\n        if (e > 1) {\n            while (n && cnt_p < e)\
    \ {\n                auto [n1, nr1] = bt_pp.divmod(n);\n                auto [a1,\
    \ ar1] = bt_pp.divmod(a);\n                auto [b1, br1] = bt_pp.divmod(b);\n\
    \                log += log_fact[nr1] - log_fact[ar1] - log_fact[br1];\n     \
    \           if (p > 2) sgn += (n1 & 1) + (a1 & 1) + (b1 & 1);\n              \
    \  else sgn += (((nr1 + 1) & 4) + ((ar1 + 1) & 4) + ((br1 + 1) & 4)) / 4;\n  \
    \              n = bt_p.floor(n), a = bt_p.floor(a), b = bt_p.floor(b);\n    \
    \            cnt_p += n - a - b;\n            }\n        }\n        else {\n \
    \           while (n && cnt_p < e) {\n                auto [n1, nr1] = bt_pp.divmod(n);\n\
    \                auto [a1, ar1] = bt_pp.divmod(a);\n                auto [b1,\
    \ br1] = bt_pp.divmod(b);\n                log += log_fact[nr1] - log_fact[ar1]\
    \ - log_fact[br1];\n                if (p > 2)\n                    sgn += (n1\
    \ & 1) + (a1 & 1) + (b1 & 1);\n                else\n                    sgn +=\
    \ ((nr1 + 1) >> 2 & 1) + ((ar1 + 1) >> 2 & 1) + ((br1 + 1) >> 2 & 1);\n      \
    \          n = n1, a = a1, b = b1;\n                cnt_p += n - a - b;\n    \
    \        }\n        }\n        if (cnt_p >= e) return 0;\n        log %= ord;\n\
    \        if (log < 0) log += ord;\n        int res = exp[log];\n        if (sgn\
    \ & 1) res = pp - res;\n        return bt_pp.mul(power[cnt_p], res);\n    }\n\
    };\n\nstruct Binomial {\n    using barrett = internal::barrett;\n    int mod;\n\
    \    std::vector<BinomialPrimePower> BPP;\n    std::vector<int> crt_coef;\n  \
    \  barrett bt;\n    Binomial(int _mod) : mod(_mod), bt(mod) {\n        auto pfacs\
    \ = pollard_rho(mod);\n        std::ranges::sort(pfacs);\n        for (int i =\
    \ 0, j = 0; i < int(pfacs.size()); i = j) {\n            int pp = 1;\n       \
    \     while (j < int(pfacs.size()) && pfacs[i] == pfacs[j]) ++j, pp *= pfacs[i];\n\
    \            BPP.emplace_back(pfacs[i], j - i);\n            int other = mod /\
    \ pp;\n            crt_coef.push_back((long long)other * mod_inv(other, pp) %\
    \ mod);\n        }\n    }\n    int C(long long n, long long k) {\n        assert(n\
    \ >= 0);\n        if (k < 0 || k > n) return 0;\n        int ans = 0;\n      \
    \  for (int s = 0; s < int(crt_coef.size()); ++s)\n            ans = bt.modulo(ans\
    \ + (unsigned long long)(BPP[s].C(n, k)) * crt_coef[s]);\n        return ans;\n\
    \    }\n};\n"
  dependsOn:
  - Numeric/internal_math.hpp
  - Numeric/primitive_root.hpp
  - Numeric/pollard_rho.hpp
  - Numeric/miller_rabin.hpp
  - Numeric/mod_pow.hpp
  - Numeric/mod_inv.hpp
  isVerificationFile: false
  path: Numeric/Binomial.hpp
  requiredBy: []
  timestamp: '2026-05-04 10:37:09+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/enumerative_combinatorics/binomial_coefficient.test.cpp
documentation_of: Numeric/Binomial.hpp
layout: document
redirect_from:
- /library/Numeric/Binomial.hpp
- /library/Numeric/Binomial.hpp.html
title: Numeric/Binomial.hpp
---
