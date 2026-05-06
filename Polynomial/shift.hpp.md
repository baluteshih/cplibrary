---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/Combination.hpp
    title: Numeric/Combination.hpp
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
    path: Polynomial/Polynomial.hpp
    title: Polynomial/Polynomial.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/polynomial/polynomial_taylor_shift.test.cpp
    title: test/1_library_checker/polynomial/polynomial_taylor_shift.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Polynomial/shift.hpp\"\n\n#line 2 \"Polynomial/Polynomial.hpp\"\
    \n\n#line 2 \"Polynomial/NTT.hpp\"\n\n#line 2 \"Numeric/Modint.hpp\"\n\n// Reference:\
    \ Atcoder Library https://github.com/atcoder/ac-library\n#line 2 \"Numeric/internal_math.hpp\"\
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
    \ internal::primitive_root_constexpr(T::mod());\n    static void set_upper_bound(int\
    \ n) {\n        if (max_size < n) {\n            while (max_size <= n) max_size\
    \ <<= 1;\n            w.resize(max_size);\n            std::ranges::fill(w, 1);\n\
    \            T dw = root.pow((T::mod() - 1) / max_size);\n            for (int\
    \ s = max_size / 2; s; s >>= 1, dw *= dw) {\n                w[s] = 1;\n     \
    \           for (int j = 1; j < s; ++j) \n                    w[s + j] = w[s +\
    \ j - 1] * dw;\n            }\n        }\n    }\npublic:\n    static void ntt(vector<T>\
    \ &a, bool inv = false) { //0 <= a[i] < P\n        int n = a.size();\n       \
    \ assert((n & (n - 1)) == 0);\n        if ((int)maxsize() < n) set_upper_bound(n);\n\
    \        for (int i = 0, j = 1; j < n - 1; ++j) {\n            for (int k = n\
    \ >> 1; (i ^= k) < k; k >>= 1);\n            if (j < i) swap(a[i], a[j]);\n  \
    \      }\n        for (int s = 1; s < n; s <<= 1) {\n            for (int i =\
    \ 0; i < n; i += s * 2) {\n                for (int j = 0; j < s; ++j) {\n   \
    \                 T tmp = a[i + s + j] * w[s + j];\n                    a[i +\
    \ s + j] = a[i + j] - tmp;\n                    a[i + j] += tmp;\n           \
    \     }\n            }\n        }\n        if (!inv) return;\n        T iv = T(n).inv();\
    \ \n        reverse(a.begin() + 1, a.begin() + n);\n        for (int i = 0; i\
    \ < n; ++i) a[i] *= iv;\n    }\n    static size_t maxsize() {\n        return\
    \ max_size;\n    }\n    static vector<T> convolution(vector<T> a, vector<T> b)\
    \ {\n        if (a.empty() || b.empty()) return vector<T>();\n        int n =\
    \ 1, sz = int(a.size()) + int(b.size()) - 1;\n        while (n < sz) n <<= 1;\n\
    \        a.resize(n), b.resize(n);\n        ntt(a), ntt(b);\n        for (int\
    \ i = 0; i < n; ++i)\n            a[i] = a[i] * b[i];\n        ntt(a, true);\n\
    \        a.resize(sz);\n        return a;\n    }\n};\n#line 4 \"Polynomial/Polynomial.hpp\"\
    \n\ntemplate<class T>\nclass Poly : public std::vector<T> {\n    using std::vector<T>::vector;\n\
    \    int n() const { return (int)this->size(); } // n() >= 1\n    static int ceilpow2(int\
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
    #line 2 \"Numeric/Combination.hpp\"\n\n#line 4 \"Numeric/Combination.hpp\"\n\n\
    template<class T>\nrequires std::derived_from<T, internal::modint_base>\nclass\
    \ Combination {\n    int N;\n    void init() {\n        for (int i = 1; i <= N;\
    \ ++i)\n            fac[i] = fac[i - 1] * i;\n        ifac.back() = fac.back().inv();\n\
    \        for (int i = N - 1; i >= 0; --i)\n            ifac[i] = ifac[i + 1] *\
    \ (i + 1);\n    }\npublic:\n    vector<T> fac, ifac;\n    Combination(int n):\
    \ N(n), fac(N + 1, 1), ifac(N + 1, 1) {\n        init();\n    }\n    Combination(int\
    \ n, T base): N(n), fac(N + 1, base.raw(1)), ifac(N + 1, base.raw(1)) {\n    \
    \    init();\n    }\n    T C(int n, int m) {\n        if (n < m) return 0;\n \
    \       return fac[n] * ifac[m] * ifac[n - m];\n    }\n    T P(int n, int m) {\n\
    \        if (n < m) return 0;\n        return fac[n] * ifac[n - m];\n    }\n \
    \   T H(int n, int m) {\n        return C(n + m - 1, m);\n    }\n};\nnamespace\
    \ CombFunc {\ntemplate<class T>\nvector<T> power(T base, int n) {\n    vector<T>\
    \ res(n + 1, 1);\n    for (int i = 1; i <= n; ++i)\n        res[i] = res[i - 1]\
    \ * base;\n    return res;\n}\ntemplate<class T>\nvector<T> ipower(T base, int\
    \ n) {\n    return power(base.inv(), n);\n}\ntemplate<class T>\nvector<T> linear_inverse(int\
    \ n) {\n    vector<T> res(n + 1, 1);\n    int MOD = T().mod();\n    for (int i\
    \ = 2; i <= n; ++i) {\n        res[i] = res[MOD % i] * (MOD - MOD / i); \n   \
    \ }\n    return res;\n}\n}\n#line 5 \"Polynomial/shift.hpp\"\n\ntemplate<class\
    \ T>\nPoly<T>& Poly<T>::shift(T c) { // f(x + c), 5e5/149ms\n    if (c == 0) return\
    \ *this;\n    Poly A(*this), B(CombFunc::power(c, n()));\n    Combination<T> comb(n());\n\
    \    A.imul(comb.fac).irev();\n    B.imul(comb.ifac);\n    auto res = (A * B).isz(n()).irev();\n\
    \    for (int i = 0; i < n(); ++i)\n        (*this)[i] = res[i] * comb.ifac[i];\n\
    \    return *this;\n}\n"
  code: "#pragma once\n\n#include \"Polynomial/Polynomial.hpp\"\n#include \"Numeric/Combination.hpp\"\
    \n\ntemplate<class T>\nPoly<T>& Poly<T>::shift(T c) { // f(x + c), 5e5/149ms\n\
    \    if (c == 0) return *this;\n    Poly A(*this), B(CombFunc::power(c, n()));\n\
    \    Combination<T> comb(n());\n    A.imul(comb.fac).irev();\n    B.imul(comb.ifac);\n\
    \    auto res = (A * B).isz(n()).irev();\n    for (int i = 0; i < n(); ++i)\n\
    \        (*this)[i] = res[i] * comb.ifac[i];\n    return *this;\n}\n"
  dependsOn:
  - Polynomial/Polynomial.hpp
  - Polynomial/NTT.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - Numeric/internal_primitive_root.hpp
  - Numeric/Combination.hpp
  isVerificationFile: false
  path: Polynomial/shift.hpp
  requiredBy: []
  timestamp: '2026-05-04 10:37:09+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/polynomial/polynomial_taylor_shift.test.cpp
documentation_of: Polynomial/shift.hpp
layout: document
redirect_from:
- /library/Polynomial/shift.hpp
- /library/Polynomial/shift.hpp.html
title: Polynomial/shift.hpp
---
