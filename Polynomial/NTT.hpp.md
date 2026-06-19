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
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Convolution/OnlineConvolution.hpp
    title: Convolution/OnlineConvolution.hpp
  - icon: ':question:'
    path: Convolution/convolution.hpp
    title: Convolution/convolution.hpp
  - icon: ':heavy_check_mark:'
    path: Misc/bigint.hpp
    title: Misc/bigint.hpp
  - icon: ':heavy_check_mark:'
    path: Numbers/bell_number.hpp
    title: Numbers/bell_number.hpp
  - icon: ':heavy_check_mark:'
    path: Numbers/partition_number.hpp
    title: Numbers/partition_number.hpp
  - icon: ':heavy_check_mark:'
    path: Polynomial/Bostan_Mori.hpp
    title: Polynomial/Bostan_Mori.hpp
  - icon: ':question:'
    path: Polynomial/Polynomial.hpp
    title: Polynomial/Polynomial.hpp
  - icon: ':x:'
    path: Polynomial/Sqrt.hpp
    title: Polynomial/Sqrt.hpp
  - icon: ':x:'
    path: Polynomial/interpolate.hpp
    title: Polynomial/interpolate.hpp
  - icon: ':x:'
    path: Polynomial/lagrange_interpolate_iota.hpp
    title: Polynomial/lagrange_interpolate_iota.hpp
  - icon: ':heavy_check_mark:'
    path: Polynomial/linear_recursion.hpp
    title: Polynomial/linear_recursion.hpp
  - icon: ':x:'
    path: Polynomial/shift.hpp
    title: Polynomial/shift.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/biginteger/addition.test.cpp
    title: test/1_library_checker/biginteger/addition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/biginteger/multiplication.test.cpp
    title: test/1_library_checker/biginteger/multiplication.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/convolution.test.cpp
    title: test/1_library_checker/convolution/convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/convolution_mod_1000000007.test.cpp
    title: test/1_library_checker/convolution/convolution_mod_1000000007.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/convolution_online.test.cpp
    title: test/1_library_checker/convolution/convolution_online.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/bell_number.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/bell_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/enumerative_combinatorics/partition_function.test.cpp
    title: test/1_library_checker/enumerative_combinatorics/partition_function.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/other/kth_term_of_linearly_recurrent_sequence.test.cpp
    title: test/1_library_checker/other/kth_term_of_linearly_recurrent_sequence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/polynomial/division_of_polynomials.test.cpp
    title: test/1_library_checker/polynomial/division_of_polynomials.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/polynomial/exp_of_formal_power_series.test.cpp
    title: test/1_library_checker/polynomial/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/polynomial/inv_of_formal_power_series.test.cpp
    title: test/1_library_checker/polynomial/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/polynomial/log_of_formal_power_series.test.cpp
    title: test/1_library_checker/polynomial/log_of_formal_power_series.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/polynomial/multipoint_evaluation.test.cpp
    title: test/1_library_checker/polynomial/multipoint_evaluation.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/polynomial/polynomial_interpolation.test.cpp
    title: test/1_library_checker/polynomial/polynomial_interpolation.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/polynomial/polynomial_taylor_shift.test.cpp
    title: test/1_library_checker/polynomial/polynomial_taylor_shift.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/polynomial/pow_of_formal_power_series.test.cpp
    title: test/1_library_checker/polynomial/pow_of_formal_power_series.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/polynomial/product_of_polynomial_sequence.test.cpp
    title: test/1_library_checker/polynomial/product_of_polynomial_sequence.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/polynomial/shift_of_sampling_points_of_polynomial.test.cpp
    title: test/1_library_checker/polynomial/shift_of_sampling_points_of_polynomial.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/polynomial/sqrt_of_formal_power_series.test.cpp
    title: test/1_library_checker/polynomial/sqrt_of_formal_power_series.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
    title: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Polynomial/NTT.hpp\"\n\n#line 2 \"Numeric/Modint.hpp\"\n\
    \n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n#line 2\
    \ \"Numeric/internal_math.hpp\"\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
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
    \ a;\n    }\n};\n"
  code: "#pragma once\n\n#include \"Numeric/Modint.hpp\"\n#include \"Numeric/internal_primitive_root.hpp\"\
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
    \     a.resize(sz);\n        return a;\n    }\n};\n"
  dependsOn:
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - Numeric/internal_primitive_root.hpp
  isVerificationFile: false
  path: Polynomial/NTT.hpp
  requiredBy:
  - Numbers/partition_number.hpp
  - Numbers/bell_number.hpp
  - Misc/bigint.hpp
  - Convolution/OnlineConvolution.hpp
  - Convolution/convolution.hpp
  - Polynomial/linear_recursion.hpp
  - Polynomial/lagrange_interpolate_iota.hpp
  - Polynomial/Bostan_Mori.hpp
  - Polynomial/Polynomial.hpp
  - Polynomial/interpolate.hpp
  - Polynomial/Sqrt.hpp
  - Polynomial/shift.hpp
  timestamp: '2026-06-19 13:11:38+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/1_library_checker/convolution/convolution.test.cpp
  - test/1_library_checker/convolution/convolution_online.test.cpp
  - test/1_library_checker/convolution/convolution_mod_1000000007.test.cpp
  - test/1_library_checker/other/kth_term_of_linearly_recurrent_sequence.test.cpp
  - test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
  - test/1_library_checker/biginteger/addition.test.cpp
  - test/1_library_checker/biginteger/multiplication.test.cpp
  - test/1_library_checker/enumerative_combinatorics/bell_number.test.cpp
  - test/1_library_checker/enumerative_combinatorics/partition_function.test.cpp
  - test/1_library_checker/polynomial/inv_of_formal_power_series.test.cpp
  - test/1_library_checker/polynomial/pow_of_formal_power_series.test.cpp
  - test/1_library_checker/polynomial/polynomial_interpolation.test.cpp
  - test/1_library_checker/polynomial/exp_of_formal_power_series.test.cpp
  - test/1_library_checker/polynomial/multipoint_evaluation.test.cpp
  - test/1_library_checker/polynomial/product_of_polynomial_sequence.test.cpp
  - test/1_library_checker/polynomial/division_of_polynomials.test.cpp
  - test/1_library_checker/polynomial/log_of_formal_power_series.test.cpp
  - test/1_library_checker/polynomial/polynomial_taylor_shift.test.cpp
  - test/1_library_checker/polynomial/sqrt_of_formal_power_series.test.cpp
  - test/1_library_checker/polynomial/shift_of_sampling_points_of_polynomial.test.cpp
documentation_of: Polynomial/NTT.hpp
layout: document
redirect_from:
- /library/Polynomial/NTT.hpp
- /library/Polynomial/NTT.hpp.html
title: Polynomial/NTT.hpp
---
