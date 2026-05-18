---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Matrix/Vector.hpp
    title: Matrix/Vector.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
    title: test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/inverse_matrix.test.cpp
    title: test/1_library_checker/linear_algebra/inverse_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_det.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_det.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_det_arbitrary_mod.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_det_arbitrary_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_product.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_rank.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_rank.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/pow_of_matrix.test.cpp
    title: test/1_library_checker/linear_algebra/pow_of_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/system_of_linear_equations.test.cpp
    title: test/1_library_checker/linear_algebra/system_of_linear_equations.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Matrix/Matrix.hpp\"\n\n#line 2 \"Numeric/internal_math.hpp\"\
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
    \ internal\n#line 2 \"Matrix/Vector.hpp\"\n\ntemplate<typename T, class Allocator\
    \ = std::allocator<T>> \nclass Vector : public std::vector<T, Allocator> {\n \
    \   int n() const { return (int)this->size(); }\npublic:\n    Vector(int _n):\
    \ std::vector<T, Allocator>(_n) {}\n    Vector operator*(const T &v) const {\n\
    \        Vector res(*this);\n        for (int i = 0; i < n(); ++i)\n         \
    \   res[i] = res[i] * v;\n        return res;\n    }\n    Vector& operator*=(const\
    \ T &v) {\n        for (int i = 0; i < n(); ++i)\n            (*this)[i] = (*this)[i]\
    \ * v;\n        return *this;\n    }\n    Vector operator/(const T &v) const {\n\
    \        Vector res(*this);\n        for (int i = 0; i < n(); ++i)\n         \
    \   res[i] = res[i] / v;\n        return res;\n    }\n    Vector& operator/=(const\
    \ T &v) {\n        for (int i = 0; i < n(); ++i)\n            (*this)[i] = (*this)[i]\
    \ / v;\n        return *this;\n    }\n    Vector operator+(const Vector &rhs)\
    \ const {\n        assert(n() == rhs.n());\n        Vector res(n());\n       \
    \ for (int i = 0; i < n(); ++i)\n            res[i] = (*this)[i] + rhs[i];\n \
    \       return res;\n    }\n    Vector& operator+=(const Vector &rhs) {\n    \
    \    assert(n() == rhs.n());\n        for (int i = 0; i < n(); ++i)\n        \
    \    (*this)[i] = (*this)[i] + rhs[i];\n        return *this;\n    }\n    T operator*(const\
    \ Vector &rhs) const {\n        assert(n() == rhs.n());\n        T res = T();\n\
    \        for (int i = 0; i < n(); ++i)\n            res = res + (*this)[i] * rhs[i];\n\
    \        return res;\n    }\n    Vector operator|(Vector const& rhs) const {\n\
    \        Vector res(n() + rhs.n());\n        std::copy(this->begin(), this->end(),\
    \ res.begin()); \n        std::copy(rhs.begin(), rhs.end(), res.begin() + n());\n\
    \        return res;\n    }\n    int find_pivot() {\n        int pivot = 0;\n\
    \        while (pivot < n() && (*this)[pivot] == T(0)) ++pivot;\n        return\
    \ pivot;\n    }\n};\n#line 5 \"Matrix/Matrix.hpp\"\n\ntemplate<class T>\nclass\
    \ Matrix : public std::vector<Vector<T>> {\npublic:\n    enum gauss_mode {half,\
    \ full, euclidean};\n    int n() const { return (int)this->size(); }\n    int\
    \ m() const { return n() ? (int)(*this)[0].size() : 0; }\n    Matrix(int _n, int\
    \ _m): std::vector<Vector<T>>(_n, Vector<T>(_m)) {}\n    Matrix(int _n): Matrix(_n,\
    \ _n) {}\n    Matrix(const Vector<T> &vec): Matrix(1, (int)vec.size()) {\n   \
    \     (*this)[0] = vec;\n    }\n    Matrix transpose() const {\n        Matrix\
    \ res(m(), n());\n        for (int i = 0; i < m(); ++i)\n            for (int\
    \ j = 0; j < n(); ++j)\n                res[i][j] = (*this)[j][i];\n        return\
    \ res;\n    }\n    Matrix operator*(const Matrix &rhs) const {\n        assert(m()\
    \ == rhs.n());\n        Matrix res(n(), rhs.m());\n        auto _rhs = rhs.transpose();\n\
    \        for (int i = 0; i < res.n(); ++i)\n            for (int j = 0; j < res.m();\
    \ ++j)\n                res[i][j] = (*this)[i] * _rhs[j];\n        return res;\n\
    \    }\n    Matrix operator*(const T &v) const {\n        Matrix res(*this);\n\
    \        for (int i = 0; i < res.n(); ++i)\n            for (int j = 0; j < res.m();\
    \ ++j)\n                res[i][j] = res[i][j] * v;\n        return res;\n    }\n\
    \    Matrix operator/(const Matrix &rhs) const {\n        assert(m() == rhs.n());\n\
    \        return *this * rhs.inv();\n    }\n    Matrix operator+(const Matrix &rhs)\
    \ const {\n        assert(n() == rhs.n());\n        assert(m() == rhs.m());\n\
    \        Matrix res(n(), m());\n        for (int i = 0; i < res.n(); ++i)\n  \
    \          res[i] = (*this)[i] + rhs[i];\n        return res;\n    }\n    Matrix\
    \ operator|(Matrix const& rhs) const {\n        assert(n() == rhs.n());\n    \
    \    Matrix res(n(), m() + rhs.m());\n        for (int i = 0; i < n(); ++i)\n\
    \            res[i] = (*this)[i] | rhs[i];\n        return res;\n    }\n    Matrix\
    \ rows(int l, int r) const {\n        assert(l <= r);\n        assert(r <= n());\n\
    \        Matrix res(r - l, m());\n        for (int i = 0; i < r - l; ++i)\n  \
    \          res[i] = (*this)[l + i];\n        return res;\n    }\n    Matrix columns(int\
    \ l, int r) const {\n        if (m() == 0) return Matrix(0, 0);\n        assert(l\
    \ <= r);\n        assert(r <= m());\n        Matrix res(n(), r - l);\n       \
    \ for (int i = 0; i < n(); ++i)\n            std::copy((*this)[i].begin() + l,\
    \ (*this)[i].begin() + r, res[i].begin());\n        return res;\n    }\n    static\
    \ Matrix identity(int n, T one = T(1)) {\n        Matrix res(n, n);\n        for\
    \ (int i = 0; i < n; ++i)\n            res[i][i] = one;\n        return res;\n\
    \    }\n    Matrix pow(long long k) const {\n        Matrix res(identity(n()));\n\
    \        Matrix base(*this);\n        for (; k; k >>= 1, base = base * base)\n\
    \            if (k & 1)\n                res = res * base;\n        return res;\n\
    \    }\n    Vector<T> apply(const Vector<T> &x) {\n        return (*this * Matrix(x).transpose()).transpose()[0];\n\
    \    }\n    template<gauss_mode mode = half>\n    void eliminate(int i) {\n  \
    \      int pivot = (*this)[i].find_pivot();\n        if (pivot < m()) {\n    \
    \        T pinv = 0;\n            if constexpr (mode != euclidean) pinv = T(1)\
    \ / (*this)[i][pivot];\n            for (int j = (mode != full) * i; j < n();\
    \ ++j)\n                if (j != i) {\n                    if constexpr (mode\
    \ != euclidean) (*this)[j] += (*this)[i] * (*this)[j][pivot] * pinv * T(-1);\n\
    \                    else {\n                        int parity = 1;\n       \
    \                 while ((*this)[j][pivot] != T(0)) {\n                      \
    \      T q;\n                            if constexpr (std::derived_from<T, internal::modint_base>)\
    \ q = T((*this)[i][pivot].val() / (*this)[j][pivot].val());\n                \
    \            else q = (*this)[i][pivot] / (*this)[j][pivot];\n               \
    \             (*this)[i] += (*this)[j] * q * T(-1);\n                        \
    \    std::swap((*this)[i], (*this)[j]);\n                            parity *=\
    \ -1;\n                        }\n                        (*this)[j] *= T(parity);\n\
    \                    }\n                }\n        }\n    }\n    template<gauss_mode\
    \ mode = half>\n    Matrix& gauss() {\n        for (int i = 0; i < n(); ++i) {\n\
    \            if constexpr (mode == euclidean) {\n                if ((*this)[i][i]\
    \ == T(0)) {\n                    for (int j = i + 1; j < n(); ++j) {\n      \
    \                  if ((*this)[j][i] != T(0)) {\n                            std::swap((*this)[i],\
    \ (*this)[j]);\n                            (*this)[j] *= T(-1);\n           \
    \                 break;\n                        }\n                    }\n \
    \               }\n                if ((*this)[i][i] == T(0)) continue;\n    \
    \        }\n            eliminate<mode>(i);\n        }\n        return *this;\n\
    \    }\n    std::pair<std::vector<int>, std::vector<int>> sort_classify(int lim)\
    \ {\n        int rk = 0;\n        std::vector<int> pivots, free;\n        for\
    \ (int j = 0; j < lim; ++j) {\n            if (rk < n() && (*this)[rk][j] == T(0))\
    \ {\n                for (int i = rk + 1; i < n(); ++i) {\n                  \
    \  if ((*this)[i][j] != T(0)) {\n                        std::swap((*this)[i],\
    \ (*this)[rk]);\n                        (*this)[rk] *= T(-1);\n             \
    \       }\n                }\n            }\n            if (rk < n() && (*this)[rk][j]\
    \ != T(0)) {\n                pivots.push_back(j);\n                rk++;\n  \
    \          } \n            else {\n                free.push_back(j);\n      \
    \      }\n        }\n        return std::make_pair(pivots, free);\n    }\n   \
    \ template<gauss_mode mode = half>\n    std::pair<std::vector<int>, std::vector<int>>\
    \ echelonize(int lim) {\n        return gauss<mode>().sort_classify(lim);\n  \
    \  }\n    template<gauss_mode mode = half>\n    std::pair<std::vector<int>, std::vector<int>>\
    \ echelonize() {\n        return echelonize<mode>(m());\n    }\n    int rank()\
    \ const {\n        if (n() > m()) return transpose().rank();\n        return Matrix(*this).echelonize().first.size();\n\
    \    }\n    template<gauss_mode mode = half>\n    T det() const {\n        assert(n()\
    \ == m());\n        Matrix cur = *this;\n        cur.echelonize<mode>();\n   \
    \     T res = T(1);\n        for (int i = 0; i < n(); ++i)\n            res =\
    \ res * cur[i][i];\n        return res;\n    }\n    std::pair<T, Matrix> inv()\
    \ const {\n        assert(n() == m());\n        Matrix cur = *this | identity(n());\n\
    \        if ((int)cur.echelonize<full>(n()).first.size() < n())\n            return\
    \ std::make_pair(0, Matrix(0, 0));\n        T det = 1;\n        for (int i = 0;\
    \ i < n(); ++i) {\n            det = det * cur[i][i];\n            cur[i] = cur[i]\
    \ / cur[i][i];\n        }\n        return std::make_pair(det, cur.columns(n(),\
    \ n() + n()));\n    }\n    Matrix kernel() const {\n        Matrix A(*this);\n\
    \        auto [pivots, free] = A.echelonize<full>();\n        Matrix sols((int)free.size(),\
    \ m());\n        for (int j = 0; j < (int)pivots.size(); ++j) {\n            T\
    \ scale = T(1) / A[j][pivots[j]];\n            for (int i = 0; i < (int)free.size();\
    \ ++i)\n                sols[i][pivots[j]] = A[j][free[i]] * scale;\n        }\n\
    \        for (int i = 0; i < (int)free.size(); ++i)\n            sols[i][free[i]]\
    \ = T(-1);\n        return sols;\n    }\n    // return (x, basis)\n    // (*this)\
    \ * (x^T + basis^T) = t^T\n    std::optional<std::pair<Matrix, Matrix>> solve(const\
    \ Matrix &t) const {\n        int dimt = t.n();\n        Matrix sols = (*this\
    \ | t.transpose()).kernel();\n        if (sols.n() < dimt) return std::nullopt;\n\
    \        Matrix upper = sols.rows(0, sols.n() - dimt);\n        Matrix lower =\
    \ sols.rows(sols.n() - dimt, sols.n());\n        if (lower.columns(m(), lower.m())\
    \ != identity(dimt) * T(-1))\n            return std::nullopt;\n        return\
    \ std::make_pair(lower.columns(0, m()), upper.columns(0, m()));\n    }\n};\n"
  code: "#pragma once\n\n#include \"Numeric/internal_math.hpp\"\n#include \"Matrix/Vector.hpp\"\
    \n\ntemplate<class T>\nclass Matrix : public std::vector<Vector<T>> {\npublic:\n\
    \    enum gauss_mode {half, full, euclidean};\n    int n() const { return (int)this->size();\
    \ }\n    int m() const { return n() ? (int)(*this)[0].size() : 0; }\n    Matrix(int\
    \ _n, int _m): std::vector<Vector<T>>(_n, Vector<T>(_m)) {}\n    Matrix(int _n):\
    \ Matrix(_n, _n) {}\n    Matrix(const Vector<T> &vec): Matrix(1, (int)vec.size())\
    \ {\n        (*this)[0] = vec;\n    }\n    Matrix transpose() const {\n      \
    \  Matrix res(m(), n());\n        for (int i = 0; i < m(); ++i)\n            for\
    \ (int j = 0; j < n(); ++j)\n                res[i][j] = (*this)[j][i];\n    \
    \    return res;\n    }\n    Matrix operator*(const Matrix &rhs) const {\n   \
    \     assert(m() == rhs.n());\n        Matrix res(n(), rhs.m());\n        auto\
    \ _rhs = rhs.transpose();\n        for (int i = 0; i < res.n(); ++i)\n       \
    \     for (int j = 0; j < res.m(); ++j)\n                res[i][j] = (*this)[i]\
    \ * _rhs[j];\n        return res;\n    }\n    Matrix operator*(const T &v) const\
    \ {\n        Matrix res(*this);\n        for (int i = 0; i < res.n(); ++i)\n \
    \           for (int j = 0; j < res.m(); ++j)\n                res[i][j] = res[i][j]\
    \ * v;\n        return res;\n    }\n    Matrix operator/(const Matrix &rhs) const\
    \ {\n        assert(m() == rhs.n());\n        return *this * rhs.inv();\n    }\n\
    \    Matrix operator+(const Matrix &rhs) const {\n        assert(n() == rhs.n());\n\
    \        assert(m() == rhs.m());\n        Matrix res(n(), m());\n        for (int\
    \ i = 0; i < res.n(); ++i)\n            res[i] = (*this)[i] + rhs[i];\n      \
    \  return res;\n    }\n    Matrix operator|(Matrix const& rhs) const {\n     \
    \   assert(n() == rhs.n());\n        Matrix res(n(), m() + rhs.m());\n       \
    \ for (int i = 0; i < n(); ++i)\n            res[i] = (*this)[i] | rhs[i];\n \
    \       return res;\n    }\n    Matrix rows(int l, int r) const {\n        assert(l\
    \ <= r);\n        assert(r <= n());\n        Matrix res(r - l, m());\n       \
    \ for (int i = 0; i < r - l; ++i)\n            res[i] = (*this)[l + i];\n    \
    \    return res;\n    }\n    Matrix columns(int l, int r) const {\n        if\
    \ (m() == 0) return Matrix(0, 0);\n        assert(l <= r);\n        assert(r <=\
    \ m());\n        Matrix res(n(), r - l);\n        for (int i = 0; i < n(); ++i)\n\
    \            std::copy((*this)[i].begin() + l, (*this)[i].begin() + r, res[i].begin());\n\
    \        return res;\n    }\n    static Matrix identity(int n, T one = T(1)) {\n\
    \        Matrix res(n, n);\n        for (int i = 0; i < n; ++i)\n            res[i][i]\
    \ = one;\n        return res;\n    }\n    Matrix pow(long long k) const {\n  \
    \      Matrix res(identity(n()));\n        Matrix base(*this);\n        for (;\
    \ k; k >>= 1, base = base * base)\n            if (k & 1)\n                res\
    \ = res * base;\n        return res;\n    }\n    Vector<T> apply(const Vector<T>\
    \ &x) {\n        return (*this * Matrix(x).transpose()).transpose()[0];\n    }\n\
    \    template<gauss_mode mode = half>\n    void eliminate(int i) {\n        int\
    \ pivot = (*this)[i].find_pivot();\n        if (pivot < m()) {\n            T\
    \ pinv = 0;\n            if constexpr (mode != euclidean) pinv = T(1) / (*this)[i][pivot];\n\
    \            for (int j = (mode != full) * i; j < n(); ++j)\n                if\
    \ (j != i) {\n                    if constexpr (mode != euclidean) (*this)[j]\
    \ += (*this)[i] * (*this)[j][pivot] * pinv * T(-1);\n                    else\
    \ {\n                        int parity = 1;\n                        while ((*this)[j][pivot]\
    \ != T(0)) {\n                            T q;\n                            if\
    \ constexpr (std::derived_from<T, internal::modint_base>) q = T((*this)[i][pivot].val()\
    \ / (*this)[j][pivot].val());\n                            else q = (*this)[i][pivot]\
    \ / (*this)[j][pivot];\n                            (*this)[i] += (*this)[j] *\
    \ q * T(-1);\n                            std::swap((*this)[i], (*this)[j]);\n\
    \                            parity *= -1;\n                        }\n      \
    \                  (*this)[j] *= T(parity);\n                    }\n         \
    \       }\n        }\n    }\n    template<gauss_mode mode = half>\n    Matrix&\
    \ gauss() {\n        for (int i = 0; i < n(); ++i) {\n            if constexpr\
    \ (mode == euclidean) {\n                if ((*this)[i][i] == T(0)) {\n      \
    \              for (int j = i + 1; j < n(); ++j) {\n                        if\
    \ ((*this)[j][i] != T(0)) {\n                            std::swap((*this)[i],\
    \ (*this)[j]);\n                            (*this)[j] *= T(-1);\n           \
    \                 break;\n                        }\n                    }\n \
    \               }\n                if ((*this)[i][i] == T(0)) continue;\n    \
    \        }\n            eliminate<mode>(i);\n        }\n        return *this;\n\
    \    }\n    std::pair<std::vector<int>, std::vector<int>> sort_classify(int lim)\
    \ {\n        int rk = 0;\n        std::vector<int> pivots, free;\n        for\
    \ (int j = 0; j < lim; ++j) {\n            if (rk < n() && (*this)[rk][j] == T(0))\
    \ {\n                for (int i = rk + 1; i < n(); ++i) {\n                  \
    \  if ((*this)[i][j] != T(0)) {\n                        std::swap((*this)[i],\
    \ (*this)[rk]);\n                        (*this)[rk] *= T(-1);\n             \
    \       }\n                }\n            }\n            if (rk < n() && (*this)[rk][j]\
    \ != T(0)) {\n                pivots.push_back(j);\n                rk++;\n  \
    \          } \n            else {\n                free.push_back(j);\n      \
    \      }\n        }\n        return std::make_pair(pivots, free);\n    }\n   \
    \ template<gauss_mode mode = half>\n    std::pair<std::vector<int>, std::vector<int>>\
    \ echelonize(int lim) {\n        return gauss<mode>().sort_classify(lim);\n  \
    \  }\n    template<gauss_mode mode = half>\n    std::pair<std::vector<int>, std::vector<int>>\
    \ echelonize() {\n        return echelonize<mode>(m());\n    }\n    int rank()\
    \ const {\n        if (n() > m()) return transpose().rank();\n        return Matrix(*this).echelonize().first.size();\n\
    \    }\n    template<gauss_mode mode = half>\n    T det() const {\n        assert(n()\
    \ == m());\n        Matrix cur = *this;\n        cur.echelonize<mode>();\n   \
    \     T res = T(1);\n        for (int i = 0; i < n(); ++i)\n            res =\
    \ res * cur[i][i];\n        return res;\n    }\n    std::pair<T, Matrix> inv()\
    \ const {\n        assert(n() == m());\n        Matrix cur = *this | identity(n());\n\
    \        if ((int)cur.echelonize<full>(n()).first.size() < n())\n            return\
    \ std::make_pair(0, Matrix(0, 0));\n        T det = 1;\n        for (int i = 0;\
    \ i < n(); ++i) {\n            det = det * cur[i][i];\n            cur[i] = cur[i]\
    \ / cur[i][i];\n        }\n        return std::make_pair(det, cur.columns(n(),\
    \ n() + n()));\n    }\n    Matrix kernel() const {\n        Matrix A(*this);\n\
    \        auto [pivots, free] = A.echelonize<full>();\n        Matrix sols((int)free.size(),\
    \ m());\n        for (int j = 0; j < (int)pivots.size(); ++j) {\n            T\
    \ scale = T(1) / A[j][pivots[j]];\n            for (int i = 0; i < (int)free.size();\
    \ ++i)\n                sols[i][pivots[j]] = A[j][free[i]] * scale;\n        }\n\
    \        for (int i = 0; i < (int)free.size(); ++i)\n            sols[i][free[i]]\
    \ = T(-1);\n        return sols;\n    }\n    // return (x, basis)\n    // (*this)\
    \ * (x^T + basis^T) = t^T\n    std::optional<std::pair<Matrix, Matrix>> solve(const\
    \ Matrix &t) const {\n        int dimt = t.n();\n        Matrix sols = (*this\
    \ | t.transpose()).kernel();\n        if (sols.n() < dimt) return std::nullopt;\n\
    \        Matrix upper = sols.rows(0, sols.n() - dimt);\n        Matrix lower =\
    \ sols.rows(sols.n() - dimt, sols.n());\n        if (lower.columns(m(), lower.m())\
    \ != identity(dimt) * T(-1))\n            return std::nullopt;\n        return\
    \ std::make_pair(lower.columns(0, m()), upper.columns(0, m()));\n    }\n};\n"
  dependsOn:
  - Numeric/internal_math.hpp
  - Matrix/Vector.hpp
  isVerificationFile: false
  path: Matrix/Matrix.hpp
  requiredBy: []
  timestamp: '2026-05-05 18:15:38+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
  - test/1_library_checker/linear_algebra/matrix_det.test.cpp
  - test/1_library_checker/linear_algebra/pow_of_matrix.test.cpp
  - test/1_library_checker/linear_algebra/system_of_linear_equations.test.cpp
  - test/1_library_checker/linear_algebra/matrix_det_arbitrary_mod.test.cpp
  - test/1_library_checker/linear_algebra/matrix_product.test.cpp
  - test/1_library_checker/linear_algebra/matrix_rank.test.cpp
  - test/1_library_checker/linear_algebra/inverse_matrix.test.cpp
documentation_of: Matrix/Matrix.hpp
layout: document
redirect_from:
- /library/Matrix/Matrix.hpp
- /library/Matrix/Matrix.hpp.html
title: Matrix/Matrix.hpp
---
