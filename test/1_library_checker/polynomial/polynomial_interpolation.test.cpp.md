---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':question:'
    path: Numeric/internal_primitive_root.hpp
    title: Numeric/internal_primitive_root.hpp
  - icon: ':question:'
    path: Polynomial/NTT.hpp
    title: Polynomial/NTT.hpp
  - icon: ':question:'
    path: Polynomial/Polynomial.hpp
    title: Polynomial/Polynomial.hpp
  - icon: ':x:'
    path: Polynomial/interpolate.hpp
    title: Polynomial/interpolate.hpp
  - icon: ':question:'
    path: default_code.hpp
    title: default_code.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/polynomial_interpolation
    links:
    - https://judge.yosupo.jp/problem/polynomial_interpolation
  bundledCode: "#line 1 \"test/1_library_checker/polynomial/polynomial_interpolation.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/polynomial_interpolation\"\
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
    }\n#line 3 \"test/1_library_checker/polynomial/polynomial_interpolation.test.cpp\"\
    \n\n#line 2 \"Polynomial/interpolate.hpp\"\n\n#line 2 \"Polynomial/Polynomial.hpp\"\
    \n\n#line 2 \"Polynomial/NTT.hpp\"\n\n#line 2 \"Numeric/Modint.hpp\"\n\n// Reference:\
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
    \ a;\n    }\n};\n#line 4 \"Polynomial/Polynomial.hpp\"\n\ntemplate<class T>\n\
    class Poly : public std::vector<T> {\n    using std::vector<T>::vector;\n    int\
    \ n() const { return (int)this->size(); } // n() >= 1\n    static int ceilpow2(int\
    \ sz) {\n        int m = 1;\n        while (m < sz) m <<= 1;\n        return m;\n\
    \    }\npublic:\n    Poly(const Poly &p, int m) : std::vector<T>(m) {\n      \
    \  std::copy_n(p.data(), min(p.n(), m), this->data());\n    }\n    Poly(const\
    \ std::vector<T> &v) : std::vector<T>(move(v)) {}\n    Poly& irev() { return reverse(this->data(),\
    \ this->data() + n()), *this; }\n    Poly& isz(int m) { return this->resize(m),\
    \ *this; }\n    Poly& imul(const Poly &rhs) {\n        for (int i = 0; i < n();\
    \ ++i)\n            (*this)[i] *= rhs[i];\n        return *this;\n    }\n    Poly&\
    \ strip() {\n        while (!this->empty() && this->back() == 0)\n           \
    \ this->pop_back();\n        return *this;\n    }\n    Poly operator+(const Poly\
    \ &rhs) const { // n() == rhs.n()\n        Poly res(*this);\n        for (int\
    \ i = 0; i < n(); ++i)\n            res[i] += rhs[i];\n        return res;\n \
    \   }\n    Poly operator-(const Poly &rhs) const { // n() == rhs.n()\n       \
    \ Poly res(*this);\n        for (int i = 0; i < n(); ++i)\n            res[i]\
    \ -= rhs[i];\n        return res;\n    }\n    Poly operator*(const T &rhs) const\
    \ {\n        Poly res(*this);\n        for (int i = 0; i < n(); ++i)\n       \
    \     res[i] *= rhs;\n        return res;\n    }\n    Poly operator*(const Poly\
    \ &rhs) const { // 5e5/185ms\n        return NTT<T>::convolution(*this, rhs);\n\
    \    }\n    Poly &dft(int len) {\n        assert((len & (len - 1)) == 0);\n  \
    \      isz(len);\n        NTT<T>::ntt(*this);\n        return *this;\n    }\n\
    \    Poly &idft(int len) {\n        assert((len & (len - 1)) == 0);\n        isz(len);\n\
    \        NTT<T>::ntt(*this, true);\n        return *this;\n    }\n    Poly Inv()\
    \ const { // (*this)[0] != 0, 5e5/212ms\n        if (n() == 1) return {(*this)[0].inv()};\n\
    \        int m = ceilpow2(n() * 2);\n        Poly Xi = Poly(*this, (n() + 1) /\
    \ 2).Inv().isz(m);\n        Poly Y(*this, m);\n        Xi.dft(m), Y.dft(m);\n\
    \        for (int i = 0; i < m; ++i)\n            Xi[i] *= (2 - Xi[i] * Y[i]);\n\
    \        return Xi.idft(m).isz(n());\n    }\n    Poly Dx() const {\n        Poly\
    \ ret(n() - 1);\n        for (int i = 0; i < ret.n(); ++i)\n            ret[i]\
    \ = (i + 1) * (*this)[i + 1];\n        return ret.isz(max(1, ret.n()));\n    }\n\
    \    Poly Sx() const {\n        Poly ret(n() + 1);\n        for (int i = 0; i\
    \ < n(); ++i)\n            ret[i + 1] = T(i + 1).inv() * (*this)[i];\n       \
    \ return ret;\n    }\n    Poly Ln() const { // (*this)[0] == 1, 5e5/406ms\n  \
    \      return (Dx() * Inv()).Sx().isz(n());\n    }\n    Poly Exp() const { //\
    \ (*this)[0] == 0, 5e5/886ms\n        if (n() == 1) return {1};\n        Poly\
    \ X = Poly(*this, (n() + 1) / 2).Exp().isz(n());\n        Poly Y = X.Ln(); Y[0]\
    \ = -1;\n        return (X * (*this - Y)).isz(n());\n    }\n    // M := P(P -\
    \ 1). If k >= M, k := k % M + M, 5e5/1195ms\n    Poly Pow(ll k) const {\n    \
    \    int nz = 0;\n        while (nz < n() && (*this)[nz] == 0) ++nz;\n       \
    \ if (nz * min(k, (ll)n()) >= n()) return Poly(n());\n        if (!k) return Poly(Poly\
    \ {1}, n());\n        Poly X(this->data() + nz, this->data() + nz + n() - nz *\
    \ k);\n        return ((X.Ln() * T(k)).Exp() * X[0].pow(k)).irev().isz(n()).irev();\n\
    \    }\n    Poly _tmul(int nn, const Poly &rhs) const {\n        Poly Y = ((*this)\
    \ * rhs).isz(n() + nn - 1);\n        return Poly(Y.data() + n() - 1, Y.data()\
    \ + Y.n());\n    }\n    std::vector<T> _eval(const std::vector<T> &x, const std::vector<Poly>\
    \ &up) const {\n        const int m = (int)x.size();\n        if (!m) return {};\n\
    \        std::vector<Poly> down(m * 2);\n        down[1] = Poly(up[1]).irev().isz(n()).Inv().irev()._tmul(m,\
    \ *this);\n        for (int i = 2; i < m * 2; ++i)\n            down[i] = up[i\
    \ ^ 1]._tmul(up[i].n() - 1, down[i / 2]);\n        std::vector<T> y(m);\n    \
    \    for (int i = 0; i < m; ++i) y[i] = down[m + i][0];\n        return y;\n \
    \   }\n    static std::vector<Poly> _tree1(const std::vector<T> &x) {\n      \
    \  const int m = (int)x.size();\n        std::vector<Poly> up(m * 2);\n      \
    \  for (int i = 0; i < m; ++i)\n            up[m + i] = {-x[i], 1};\n        for\
    \ (int i = m - 1; i > 0; --i) \n            up[i] = up[i * 2] * up[i * 2 + 1];\n\
    \        return up;\n    }\n    std::vector<T> Eval(const std::vector<T> &x) const\
    \ { // 1e5/696ms\n        auto up = _tree1(x); return _eval(x, up);\n    }\n \
    \   std::pair<Poly, Poly> DivMod(const Poly &rhs) const { // rhs.back() != 0,\
    \ 5e5/330ms\n        if (n() < rhs.n()) return {{0}, *this};\n        const int\
    \ m = n() - rhs.n() + 1;\n        Poly X(rhs); X.irev().isz(m);\n        Poly\
    \ Y(*this); Y.irev().isz(m);\n        Poly Q = (Y * X.Inv()).isz(m).irev();\n\
    \        X = rhs * Q, Y = *this;\n        return {Q, (Y - X).isz(max(1, rhs.n()\
    \ - 1))};\n    }\n    // should be include additionally\n    Poly Sqrt() const;\n\
    \    bool has_sqrt() const;\n    Poly& shift(T c);\n};\nusing Poly_t = Poly<modint998244353>;\n\
    #line 4 \"Polynomial/interpolate.hpp\"\n\ntemplate<class T>\nPoly<T> interpolate(const\
    \ std::vector<T> &x, const std::vector<T> &y) { // 1e5/928ms\n    const int m\
    \ = (int)x.size();\n    std::vector<Poly<T>> up = Poly<T>::_tree1(x), down(m *\
    \ 2);\n    std::vector<T> z = up[1].Dx()._eval(x, up);\n    for (int i = 0; i\
    \ < m; ++i) z[i] = y[i] / z[i];\n    for (int i = 0; i < m; ++i) down[m + i] =\
    \ {z[i]};\n    for (int i = m - 1; i > 0; --i) down[i] = down[i * 2] * up[i *\
    \ 2 + 1] + down[i * 2 + 1] * up[i * 2];\n    return down[1];\n}\n#line 5 \"test/1_library_checker/polynomial/polynomial_interpolation.test.cpp\"\
    \n\nusing mint = modint998244353;\n\nint main() {\n    ios::sync_with_stdio(0),\
    \ cin.tie(0);\n    int n;\n    cin >> n;\n    vector<mint> x(n), y(n);\n    for\
    \ (auto &i : x)\n        cin >> i;\n    for (auto &i : y)\n        cin >> i;\n\
    \    auto res = interpolate(x, y);\n    for (int i = 0; i < n; ++i)\n        cout\
    \ << res[i] << \" \\n\"[i + 1 == n];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/polynomial_interpolation\"\
    \n#include \"default_code.hpp\"\n\n#include \"Polynomial/interpolate.hpp\"\n\n\
    using mint = modint998244353;\n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n\
    \    int n;\n    cin >> n;\n    vector<mint> x(n), y(n);\n    for (auto &i : x)\n\
    \        cin >> i;\n    for (auto &i : y)\n        cin >> i;\n    auto res = interpolate(x,\
    \ y);\n    for (int i = 0; i < n; ++i)\n        cout << res[i] << \" \\n\"[i +\
    \ 1 == n];\n}\n"
  dependsOn:
  - default_code.hpp
  - Polynomial/interpolate.hpp
  - Polynomial/Polynomial.hpp
  - Polynomial/NTT.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - Numeric/internal_primitive_root.hpp
  isVerificationFile: true
  path: test/1_library_checker/polynomial/polynomial_interpolation.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 13:11:38+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/1_library_checker/polynomial/polynomial_interpolation.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/polynomial/polynomial_interpolation.test.cpp
- /verify/test/1_library_checker/polynomial/polynomial_interpolation.test.cpp.html
title: test/1_library_checker/polynomial/polynomial_interpolation.test.cpp
---
