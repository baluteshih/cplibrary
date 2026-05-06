---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Misc/MultiInt.hpp
    title: Misc/MultiInt.hpp
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: String/RollingHash.hpp
    title: String/RollingHash.hpp
  - icon: ':question:'
    path: default_code.hpp
    title: default_code.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/longest_common_substring
    links:
    - https://judge.yosupo.jp/problem/longest_common_substring
  bundledCode: "#line 1 \"test/1_library_checker/string/longest_common_substring.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/longest_common_substring\"\
    \n#line 2 \"default_code.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace std;\n\
    typedef long long ll;\ntypedef pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n\
    #define X first\n#define Y second\n#define SZ(a) ((int)a.size())\n#define ALL(v)\
    \ v.begin(), v.end()\ntemplate<class A, class B>\nostream& operator<<(ostream&\
    \ os, const pair<A, B> &a) {\n    os << \"(\" << a.first << \", \" << a.second\
    \ << \")\";\n    return os;\n}\ntemplate <typename T>\nconcept PrintableContainer\
    \ = requires(T& a) {\n    a.begin();\n    a.end();\n} && !std::same_as<std::remove_cvref_t<T>,\
    \ std::string> &&\n     !std::same_as<std::remove_cvref_t<T>, std::string_view>\
    \ &&\n     !std::is_convertible_v<T, const char*>;\ntemplate <PrintableContainer\
    \ T>\nstd::ostream& operator<<(std::ostream& os, const T& a) {\n    os << \"[\
    \ \";\n    bool first = true;\n    for (const auto& item : a) {\n        if (!first)\
    \ os << \", \";\n        os << item;\n        first = false;\n    }\n    return\
    \ os << \" ]\";\n}\n#ifdef bbq\n#include <experimental/iterator>\n#define safe\
    \ cerr<<__PRETTY_FUNCTION__<<\" line \"<<__LINE__<<\" safe\\n\"\n#define sepline\
    \ sepline_() \n#define debug(a...) debug_(#a, a)\n#define orange(a...) orange_(#a,\
    \ a)\nvoid debug_(auto s, auto ...a) {\n    cerr << \"\\e[1;32m(\" << s << \"\
    ) = (\";\n    int f = 0;\n    (..., (cerr << (f++ ? \", \" : \"\") << a));\n \
    \   cerr << \")\\e[0m\\n\";\n}\nvoid orange_(auto s, auto L, auto R) {\n    cerr\
    \ << \"\\e[1;33m[ \" << s << \" ] = [ \";\n    using namespace experimental;\n\
    \    copy(L, R, make_ostream_joiner(cerr, \", \"));\n    cerr << \" ]\\e[0m\\\
    n\";\n}\nvoid sepline_(int length = 50) {\n    cerr << \"\\e[1;35m\";\n    cerr\
    \ << string(length, '=');\n    cerr << \"\\e[0m\\n\";\n}\n#else\n#define safe\
    \ ((void)0)\n#define sepline safe\n#define debug(...) safe\n#define orange(...)\
    \ safe\n#endif\n\nvoid chmax(auto &x, auto val) {\n    x = max(x, val);\n}\n\n\
    void chmin(auto &x, auto val) {\n    x = min(x, val);\n}\n\nvector<int> count_array(const\
    \ auto &container, int sz = -1) {\n    if (sz == -1) sz = *ranges::max_element(container)\
    \ + 1;\n    vector<int> res(sz);\n    for (auto x : container) ++res[x];\n   \
    \ return res;\n}\n\ntemplate<class T>\nvoid discretization(vector<T> &vals) {\n\
    \    ranges::sort(vals);\n    vals.erase(ranges::unique(vals).begin(), vals.end());\n\
    }\n#line 3 \"test/1_library_checker/string/longest_common_substring.test.cpp\"\
    \n\n#line 2 \"Numeric/Modint.hpp\"\n\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    #line 2 \"Numeric/internal_math.hpp\"\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    \n#line 7 \"Numeric/internal_math.hpp\"\n#include <type_traits>\n\n#ifdef _MSC_VER\n\
    #include <intrin.h>\n#endif\n\nnamespace internal {\n\n// @param m `1 <= m`\n\
    // @return x mod m\nconstexpr long long safe_mod(long long x, long long m) {\n\
    \    x %= m;\n    if (x < 0) x += m;\n    return x;\n}\n\n// Fast modular multiplication\
    \ by barrett reduction\n// Reference: https://en.wikipedia.org/wiki/Barrett_reduction\n\
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
    \ internal\n#line 5 \"Numeric/Modint.hpp\"\n\ntemplate <int m, std::enable_if_t<(1\
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
    \ rhs) {\n        return lhs._v <=> rhs._v;\n    }\n    friend ostream& operator<<(ostream&\
    \ os, const mint& v) {\n        os << v._v;\n        return os;\n    }\n    friend\
    \ istream& operator>>(istream& is, mint& v) {\n        long long x;\n        is\
    \ >> x;\n        x %= (long long)(umod());\n        if (x < 0) x += umod();\n\
    \        v._v = (unsigned int)(x);\n        return is;\n    }\n\n  private:\n\
    \    unsigned int _v;\n    static constexpr unsigned int umod() { return m; }\n\
    \    static constexpr bool prime = internal::is_prime<m>;\n};\n\nusing modint998244353\
    \ = static_modint<998244353>;\nusing modint1000000007 = static_modint<1000000007>;\n\
    #line 2 \"String/RollingHash.hpp\"\n\n#line 2 \"Misc/MultiInt.hpp\"\n\ntemplate\
    \ <typename... Ints>\nstruct MultiInt {\n    std::tuple<Ints...> v;\n    MultiInt()\
    \ = default;\n    template <typename T> requires std::is_integral_v<T>\n    MultiInt(T\
    \ x) : v{ Ints(x)... } {}\n    MultiInt(Ints... args) : v{args...} {}\n    MultiInt(std::tuple<Ints...>\
    \ t) : v(t) {}\n    MultiInt& operator+=(const MultiInt& o) {\n        [&]<std::size_t...\
    \ I>(std::index_sequence<I...>) {\n            ((std::get<I>(v) += std::get<I>(o.v)),\
    \ ...);\n        }(std::index_sequence_for<Ints...>{});\n        return *this;\n\
    \    }\n    MultiInt& operator-=(const MultiInt& o) {\n        [&]<std::size_t...\
    \ I>(std::index_sequence<I...>) {\n            ((std::get<I>(v) -= std::get<I>(o.v)),\
    \ ...);\n        }(std::index_sequence_for<Ints...>{});\n        return *this;\n\
    \    }\n    MultiInt& operator*=(const MultiInt& o) {\n        [&]<std::size_t...\
    \ I>(std::index_sequence<I...>) {\n            ((std::get<I>(v) *= std::get<I>(o.v)),\
    \ ...);\n        }(std::index_sequence_for<Ints...>{});\n        return *this;\n\
    \    }\n    MultiInt& operator/=(const MultiInt& o) {\n        [&]<std::size_t...\
    \ I>(std::index_sequence<I...>) {\n            ((std::get<I>(v) /= std::get<I>(o.v)),\
    \ ...);\n        }(std::index_sequence_for<Ints...>{});\n        return *this;\n\
    \    }\n    MultiInt operator+(const MultiInt& o) const { auto res = *this; return\
    \ res += o; }\n    MultiInt operator-(const MultiInt& o) const { auto res = *this;\
    \ return res -= o; }\n    MultiInt operator*(const MultiInt& o) const { auto res\
    \ = *this; return res *= o; }\n    MultiInt operator/(const MultiInt& o) const\
    \ { auto res = *this; return res /= o; }\n    bool operator==(const MultiInt&\
    \ o) const requires requires { v == o.v; } {\n        return v == o.v;\n    }\n\
    \    std::strong_ordering operator<=>(const MultiInt& o) const requires requires\
    \ { v <=> o.v; } {\n        return v <=> o.v;\n    }\n    friend ostream& operator<<(ostream&\
    \ os, const MultiInt& obj) {\n        std::apply([&os](const auto&... args) {\n\
    \            bool first = true;\n            ((os << (first ? \"\" : \" \") <<\
    \ args, first = false), ...);\n        }, obj.v);\n        return os;\n    }\n\
    };\n#line 4 \"String/RollingHash.hpp\"\n\ntemplate <int base, typename... Ints>\n\
    struct RollingHash {\n    using Val = MultiInt<Ints...>;\n    int sz = 0;\n  \
    \  Val val;\n    inline static std::vector<Val> p_pow, p_ipow;\n    static void\
    \ initialize() {\n        p_pow = std::vector<Val>{Val(1), Val(base)};\n     \
    \   p_ipow = std::vector<Val>{Val(1), Val(1) / Val(base)};\n    }\n    static\
    \ void extend(int sz) {\n        if (p_pow.empty()) initialize();\n        int\
    \ cur = p_pow.size();\n        if (sz <= cur) return;\n        p_pow.resize(sz),\
    \ p_ipow.resize(sz);\n        if (cur < sz) {\n            for (int i = cur; i\
    \ < sz; ++i) {\n                p_pow[i] = p_pow[i - 1] * p_pow[1];\n        \
    \        p_ipow[i] = p_ipow[i - 1] * p_ipow[1]; \n            }\n        }\n \
    \   }\n    static Val get_pow(int idx) {\n        if (idx >= int(p_pow.size()))\
    \ extend(idx + 1);\n        return p_pow[idx];\n    }\n    static Val get_ipow(int\
    \ idx) {\n        if (idx >= int(p_ipow.size())) extend(idx + 1);\n        return\
    \ p_ipow[idx];\n    }\n    RollingHash() = default; \n    template <typename T>\
    \ \n    RollingHash(int _sz, T x) : sz(_sz), val(x) {}\n    RollingHash(int _sz,\
    \ Ints... args) : sz(_sz), val(args...) {}\n    RollingHash& operator+=(const\
    \ RollingHash &rhs) {\n        val += rhs.val * get_pow(sz);\n        sz += rhs.sz;\n\
    \        return *this; \n    }\n    RollingHash& operator*=(const int &v) {\n\
    \        if (v > 0) val *= get_pow(v);\n        else if (v < 0) val *= get_ipow(-v);\n\
    \        return *this;\n    }\n    RollingHash& operator-=(const RollingHash &rhs)\
    \ {\n        val -= rhs.val;\n        sz -= rhs.sz;\n        return *this; \n\
    \    }\n    RollingHash operator+(const RollingHash& o) const { auto res = *this;\
    \ return res += o; }\n    RollingHash operator-(const RollingHash& o) const {\
    \ auto res = *this; return res -= o; }\n    RollingHash operator*(const int& o)\
    \ const { auto res = *this; return res *= o; }\n    bool operator==(const RollingHash\
    \ &rhs) const {\n        return sz == rhs.sz && val == rhs.val;\n    }\n    std::strong_ordering\
    \ operator<=>(const RollingHash &rhs) const {\n        if (sz != rhs.sz) return\
    \ sz <=> rhs.sz;\n        return val <=> rhs.val;\n    }\n    static std::vector<RollingHash>\
    \ prefixHash(const auto &a) {\n        std::vector<RollingHash> res(a.size());\n\
    \        extend(a.size());\n        for (int i = 0; i < int(a.size()); ++i) {\n\
    \            res[i] = RollingHash(1, Val(a[i]));\n            if (i) res[i] =\
    \ res[i - 1] + res[i];\n        }\n        return res;\n    }\n    static RollingHash\
    \ rangeHash(const std::vector<RollingHash> &prefix_sum, int l, int r) {\n    \
    \    if (l > r) return RollingHash();\n        if (l == 0) return prefix_sum[r\
    \ - 1];\n        return (prefix_sum[r - 1] - prefix_sum[l - 1]) * (-l);\n    }\n\
    \    friend ostream& operator<<(ostream& os, const RollingHash& v) {\n       \
    \ os << v.sz << \" | \" << v.val; \n        return os;\n    }\n};\n#line 6 \"\
    test/1_library_checker/string/longest_common_substring.test.cpp\"\n\nusing mint1\
    \ = modint998244353;\nusing mint2 = modint1000000007;\nusing Hash = RollingHash<307,\
    \ mint1, mint2>;\n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n \
    \   string s, t;\n    cin >> s >> t;\n    auto prefix1 = Hash::prefixHash(s);\n\
    \    auto prefix2 = Hash::prefixHash(t);\n    int anslen = 0, a = 0, b = 0;\n\n\
    \    auto check = [&](int len) {\n        vector<pair<Hash, int>> val;\n     \
    \   val.reserve(s.size() - len + 1);\n        for (int i = 0; i <= int(s.size())\
    \ - len; ++i)\n            val.emplace_back(Hash::rangeHash(prefix1, i, i + len),\
    \ i);\n        ranges::sort(val);\n        for (int i = 0; i <= int(t.size())\
    \ - len; ++i) {\n            auto v = Hash::rangeHash(prefix2, i, i + len);\n\
    \            auto it = ranges::lower_bound(val, make_pair(v, 0));\n          \
    \  if (it != val.end() && it->first == v) {\n                anslen = len;\n \
    \               a = it->second;\n                b = i;\n                return\
    \ true;\n            }\n        }\n        return false;\n    };\n\n    int l\
    \ = 0, r = min(s.size(), t.size()) + 1;\n    while (r - l > 1) {\n        int\
    \ mid = (l + r) >> 1;\n        if (check(mid)) l = mid;\n        else r = mid;\n\
    \    }\n    cout << a << \" \" << a + anslen << \" \" << b << \" \" << b + anslen\
    \ << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/longest_common_substring\"\
    \n#include \"default_code.hpp\"\n\n#include \"Numeric/Modint.hpp\"\n#include \"\
    String/RollingHash.hpp\"\n\nusing mint1 = modint998244353;\nusing mint2 = modint1000000007;\n\
    using Hash = RollingHash<307, mint1, mint2>;\n\nint main() {\n    ios::sync_with_stdio(0),\
    \ cin.tie(0);\n    string s, t;\n    cin >> s >> t;\n    auto prefix1 = Hash::prefixHash(s);\n\
    \    auto prefix2 = Hash::prefixHash(t);\n    int anslen = 0, a = 0, b = 0;\n\n\
    \    auto check = [&](int len) {\n        vector<pair<Hash, int>> val;\n     \
    \   val.reserve(s.size() - len + 1);\n        for (int i = 0; i <= int(s.size())\
    \ - len; ++i)\n            val.emplace_back(Hash::rangeHash(prefix1, i, i + len),\
    \ i);\n        ranges::sort(val);\n        for (int i = 0; i <= int(t.size())\
    \ - len; ++i) {\n            auto v = Hash::rangeHash(prefix2, i, i + len);\n\
    \            auto it = ranges::lower_bound(val, make_pair(v, 0));\n          \
    \  if (it != val.end() && it->first == v) {\n                anslen = len;\n \
    \               a = it->second;\n                b = i;\n                return\
    \ true;\n            }\n        }\n        return false;\n    };\n\n    int l\
    \ = 0, r = min(s.size(), t.size()) + 1;\n    while (r - l > 1) {\n        int\
    \ mid = (l + r) >> 1;\n        if (check(mid)) l = mid;\n        else r = mid;\n\
    \    }\n    cout << a << \" \" << a + anslen << \" \" << b << \" \" << b + anslen\
    \ << \"\\n\";\n}\n"
  dependsOn:
  - default_code.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - String/RollingHash.hpp
  - Misc/MultiInt.hpp
  isVerificationFile: true
  path: test/1_library_checker/string/longest_common_substring.test.cpp
  requiredBy: []
  timestamp: '2026-05-04 10:37:09+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/string/longest_common_substring.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/string/longest_common_substring.test.cpp
- /verify/test/1_library_checker/string/longest_common_substring.test.cpp.html
title: test/1_library_checker/string/longest_common_substring.test.cpp
---
