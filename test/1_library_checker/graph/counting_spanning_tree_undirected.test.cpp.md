---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/count_spanning_tree.hpp
    title: Graph/count_spanning_tree.hpp
  - icon: ':heavy_check_mark:'
    path: Matrix/Matrix.hpp
    title: Matrix/Matrix.hpp
  - icon: ':heavy_check_mark:'
    path: Matrix/Vector.hpp
    title: Matrix/Vector.hpp
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/counting_spanning_tree_undirected
    links:
    - https://judge.yosupo.jp/problem/counting_spanning_tree_undirected
  bundledCode: "#line 1 \"test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/counting_spanning_tree_undirected\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp\"\
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
    #line 2 \"Graph/base.hpp\"\n\ntemplate<bool directed = true, typename Edge = void,\
    \ typename Vertex = void>\nclass Graph {\npublic:\n    static constexpr bool is_directed\
    \ = directed;\n    static constexpr bool hasEdgeWeight = !std::is_same_v<Edge,\
    \ void>;\n    static constexpr bool hasVertexWeight = !std::is_same_v<Vertex,\
    \ void>;\n    using edge_value_type = Edge;\n    using vertex_value_type = Vertex;\n\
    \    struct Empty {};\n    struct edge_v {\n        int from, to;\n        [[no_unique_address]]\
    \ std::conditional_t<hasEdgeWeight, Edge, Empty> weight;\n        edge_v() {}\n\
    \        edge_v(int u, int v) : from(u), to(v) {}\n        template <typename\
    \ W>\n        edge_v(int u, int v, const W &w) requires(hasEdgeWeight) : from(u),\
    \ to(v), weight(w) {}\n        template <typename OtherEdge>\n        edge_v(const\
    \ OtherEdge &other) requires(hasEdgeWeight && requires(OtherEdge o) { o.weight;\
    \ }) \n            : from(other.from), to(other.to), weight(other.weight) {}\n\
    \        template <typename OtherEdge>\n        edge_v(const OtherEdge &other)\
    \ requires(!hasEdgeWeight || !requires(OtherEdge o) { o.weight; }) \n        \
    \    : from(other.from), to(other.to) {} \n        edge_v reversed() const {\n\
    \            edge_v res(*this);\n            std::swap(res.from, res.to);\n  \
    \          return res;\n        }\n        friend std::ostream& operator<<(std::ostream&\
    \ os, const edge_v &v) {\n            os << \"(\" << v.from << \"->\" << v.to;\n\
    \            if constexpr (hasEdgeWeight) os << \", \" << v.weight;\n        \
    \    os << \")\";\n            return os;\n        }\n    };\n    std::vector<std::vector<std::pair<int,\
    \ int>>> G;\n    std::vector<edge_v> edges;\n    [[no_unique_address]] std::conditional_t<hasVertexWeight,\
    \ std::vector<Vertex>, Empty> weight;\n    Graph(int _n) : G(_n) {\n        if\
    \ constexpr (hasVertexWeight) weight.resize(_n);\n    }\n    int n() const { return\
    \ G.size(); }\n    int m() const { return edges.size(); }\n    int opposite(int\
    \ u, int eid) const { return edges[eid].from ^ edges[eid].to ^ u; }\n    auto&\
    \ edge(int idx) {\n        return edges[idx]; \n    }\n    auto &vertex(int idx)\
    \ requires (hasVertexWeight) {\n        return weight[idx];\n    }\n    const\
    \ auto& edge(int idx) const {\n        return edges[idx]; \n    }\n    const auto\
    \ &vertex(int idx) const requires (hasVertexWeight) {\n        return weight[idx];\n\
    \    }\n    auto &vertex_weight() requires (hasVertexWeight) {\n        return\
    \ weight;\n    }\n    const auto &vertex_weight() const requires (hasVertexWeight)\
    \ {\n        return weight;\n    }\n    void set_vertex_weight(const auto &vec)\
    \ {\n        for (int i = 0; i < n(); ++i)\n            weight[i] = vec[i];\n\
    \    }\n    void add_edge(int u, int v, const auto &w) requires (hasEdgeWeight)\
    \ {\n        G[u].emplace_back(v, edges.size());\n        if constexpr (!directed)\
    \ G[v].emplace_back(u, edges.size());\n        edges.emplace_back(u, v, w);\n\
    \    }\n    void add_edge(int u, int v) requires (!hasEdgeWeight) {\n        G[u].emplace_back(v,\
    \ edges.size());\n        if constexpr (!directed) G[v].emplace_back(u, edges.size());\n\
    \        edges.emplace_back(u, v);\n    }\n    void add_edge(const edge_v &e)\
    \ {\n        G[e.from].emplace_back(e.to, edges.size());\n        if constexpr\
    \ (!directed) G[e.to].emplace_back(e.from, edges.size());\n        edges.emplace_back(e);\n\
    \    }\n    void pop_edge() {\n        G[edges.back().from].pop_back();\n    \
    \    if constexpr (!directed) G[edges.back().to].pop_back();\n        edges.pop_back();\n\
    \    }\n    std::vector<int> in_degree() {\n        std::vector<int> res(n());\n\
    \        for (auto &e : edges)\n            ++res[e.to];\n        return res;\n\
    \    }\n    virtual std::vector<int> out_degree() {\n        std::vector<int>\
    \ res(n());\n        for (auto &e : edges)\n            ++res[e.from];\n     \
    \   return res;\n    }\n    std::vector<std::pair<int, int>>& operator[](int idx)\
    \ {\n        return G[idx];\n    }\n    const std::vector<std::pair<int, int>>&\
    \ operator[](int idx) const {\n        return G[idx];\n    }\n    Graph reversed()\
    \ const {\n        Graph res(n());\n        for (auto &e : edges)\n          \
    \  res.add_edge(e.reversed());\n        if constexpr (hasVertexWeight) res.set_vertex_weight(weight);\n\
    \        return res;\n    }\n    std::pair<std::vector<int>, std::vector<int>>\
    \ cycle() {\n        std::vector<int> vis(this->n());\n        std::vector<int>\
    \ res_v, res_e;\n        int cyc_end = -1;\n        auto dfs = [&](auto self,\
    \ int u, int f) -> int {\n            vis[u] = 1;\n            for (auto [v, eid]\
    \ : G[u]) {\n                if (eid == f || vis[v] == 2) continue;\n        \
    \        if (vis[v] == 1) {\n                    res_v.push_back(u);\n       \
    \             res_e.push_back(eid);\n                    cyc_end = v;\n      \
    \              return 1;\n                }\n                int rt = self(self,\
    \ v, eid);\n                if (rt) {\n                    if (rt == 1) { \n \
    \                       res_e.push_back(eid);\n                        res_v.push_back(u);\n\
    \                    }\n                    if (cyc_end == u) rt = 2;\n      \
    \              return rt;\n                }\n            }\n            vis[u]\
    \ = 2;\n            return 0;\n        };\n        for (int i = 0; i < this->n();\
    \ ++i)\n            if (!vis[i] && dfs(dfs, i, -1))\n                break;\n\
    \        std::ranges::reverse(res_v);\n        std::ranges::reverse(res_e);\n\
    \        return std::make_pair(res_v, res_e);\n    }\n    Graph<true, Edge, Vertex>\
    \ oriented(const std::vector<int> &rk) const requires (!directed) {\n        Graph<true,\
    \ Edge, Vertex> res(this->n());\n        for (auto &e : edges)\n            if\
    \ (rk[e.from] < rk[e.to])\n                res.add_edge(e);\n            else\n\
    \                res.add_edge(e.reversed());\n        return res;\n    }\n   \
    \ Graph induced(const std::vector<int> &subset) {\n        std::vector<int> idx(n,\
    \ -1);\n        for (int cnt = 0; int i : subset) idx[i] = cnt++;\n        Graph\
    \ res(subset.size());\n        for (auto e : edges) {\n            e.from = idx[e.from],\
    \ e.to = idx[e.to];\n            if (e.to == -1 || e.from == -1) continue;\n \
    \           res.add_edge(e);\n        }\n        return res;\n    }\n};\n\ntemplate<typename\
    \ Edge = void, typename Vertex = void>\nclass UndirectedGraph : public Graph<false,\
    \ Edge, Vertex> {\npublic:\n    using Graph<false, Edge, Vertex>::Graph;\n};\n\
    #line 2 \"Graph/count_spanning_tree.hpp\"\n\n#line 2 \"Matrix/Matrix.hpp\"\n\n\
    #line 2 \"Matrix/Vector.hpp\"\n\ntemplate<typename T, class Allocator = std::allocator<T>>\
    \ \nclass Vector : public std::vector<T, Allocator> {\n    int n() const { return\
    \ (int)this->size(); }\npublic:\n    Vector(int _n): std::vector<T, Allocator>(_n)\
    \ {}\n    Vector operator*(const T &v) const {\n        Vector res(*this);\n \
    \       for (int i = 0; i < n(); ++i)\n            res[i] = res[i] * v;\n    \
    \    return res;\n    }\n    Vector& operator*=(const T &v) {\n        for (int\
    \ i = 0; i < n(); ++i)\n            (*this)[i] = (*this)[i] * v;\n        return\
    \ *this;\n    }\n    Vector operator/(const T &v) const {\n        Vector res(*this);\n\
    \        for (int i = 0; i < n(); ++i)\n            res[i] = res[i] / v;\n   \
    \     return res;\n    }\n    Vector& operator/=(const T &v) {\n        for (int\
    \ i = 0; i < n(); ++i)\n            (*this)[i] = (*this)[i] / v;\n        return\
    \ *this;\n    }\n    Vector operator+(const Vector &rhs) const {\n        assert(n()\
    \ == rhs.n());\n        Vector res(n());\n        for (int i = 0; i < n(); ++i)\n\
    \            res[i] = (*this)[i] + rhs[i];\n        return res;\n    }\n    Vector&\
    \ operator+=(const Vector &rhs) {\n        assert(n() == rhs.n());\n        for\
    \ (int i = 0; i < n(); ++i)\n            (*this)[i] = (*this)[i] + rhs[i];\n \
    \       return *this;\n    }\n    T operator*(const Vector &rhs) const {\n   \
    \     assert(n() == rhs.n());\n        T res = T();\n        for (int i = 0; i\
    \ < n(); ++i)\n            res = res + (*this)[i] * rhs[i];\n        return res;\n\
    \    }\n    Vector operator|(Vector const& rhs) const {\n        Vector res(n()\
    \ + rhs.n());\n        std::copy(this->begin(), this->end(), res.begin()); \n\
    \        std::copy(rhs.begin(), rhs.end(), res.begin() + n());\n        return\
    \ res;\n    }\n    int find_pivot() {\n        int pivot = 0;\n        while (pivot\
    \ < n() && (*this)[pivot] == T(0)) ++pivot;\n        return pivot;\n    }\n};\n\
    #line 5 \"Matrix/Matrix.hpp\"\n\ntemplate<class T>\nclass Matrix : public std::vector<Vector<T>>\
    \ {\npublic:\n    enum gauss_mode {half, full, euclidean};\n    int n() const\
    \ { return (int)this->size(); }\n    int m() const { return n() ? (int)(*this)[0].size()\
    \ : 0; }\n    Matrix(int _n, int _m): std::vector<Vector<T>>(_n, Vector<T>(_m))\
    \ {}\n    Matrix(int _n): Matrix(_n, _n) {}\n    Matrix(const Vector<T> &vec):\
    \ Matrix(1, (int)vec.size()) {\n        (*this)[0] = vec;\n    }\n    Matrix transpose()\
    \ const {\n        Matrix res(m(), n());\n        for (int i = 0; i < m(); ++i)\n\
    \            for (int j = 0; j < n(); ++j)\n                res[i][j] = (*this)[j][i];\n\
    \        return res;\n    }\n    Matrix operator*(const Matrix &rhs) const {\n\
    \        assert(m() == rhs.n());\n        Matrix res(n(), rhs.m());\n        auto\
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
    \        return res;\n    }\n    Matrix minor(int _i, int _j) const {\n      \
    \  Matrix res(n() - 1, m() - 1);\n        for (int i = 0; i + 1 < n(); ++i)\n\
    \            for (int j = 0; j + 1 < m(); ++j)\n                res[i][j] = (*this)[i\
    \ + (i >= _i)][j + (j >= _j)];\n        return res;\n    }\n    static Matrix\
    \ identity(int n, T one = T(1)) {\n        Matrix res(n, n);\n        for (int\
    \ i = 0; i < n; ++i)\n            res[i][i] = one;\n        return res;\n    }\n\
    \    Matrix pow(long long k) const {\n        Matrix res(identity(n()));\n   \
    \     Matrix base(*this);\n        for (; k; k >>= 1, base = base * base)\n  \
    \          if (k & 1)\n                res = res * base;\n        return res;\n\
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
    \ std::make_pair(lower.columns(0, m()), upper.columns(0, m()));\n    }\n};\n#line\
    \ 5 \"Graph/count_spanning_tree.hpp\"\n\ntemplate<typename T, typename graph>\n\
    T count_spanning_tree(const graph &G, int root = 0) {\n    Matrix<T> mat(G.n());\n\
    \    assert(root >= 0 && root < G.n());\n    for (auto e : G.edges) {\n      \
    \  if (e.to == e.from) continue;\n        mat[e.to][e.to] += T(1);\n        mat[e.from][e.to]\
    \ -= T(1);\n        if constexpr (!graph::is_directed) {\n            mat[e.from][e.from]\
    \ += T(1);\n            mat[e.to][e.from] -= T(1);\n        }\n    }\n    return\
    \ mat.minor(root, root).det();\n}\n#line 7 \"test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp\"\
    \n\nusing mint = modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n, m;\n    std::cin >> n >> m;\n    UndirectedGraph<>\
    \ G(n);\n    while (m--) {\n        int u, v;\n        std::cin >> u >> v;\n \
    \       G.add_edge(u, v);\n    }\n    std::cout << count_spanning_tree<mint>(G)\
    \ << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/counting_spanning_tree_undirected\"\
    \n#include \"assumption.hpp\"\n\n#include \"Numeric/Modint.hpp\"\n#include \"\
    Graph/base.hpp\"\n#include \"Graph/count_spanning_tree.hpp\"\n\nusing mint = modint998244353;\n\
    \nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n,\
    \ m;\n    std::cin >> n >> m;\n    UndirectedGraph<> G(n);\n    while (m--) {\n\
    \        int u, v;\n        std::cin >> u >> v;\n        G.add_edge(u, v);\n \
    \   }\n    std::cout << count_spanning_tree<mint>(G) << \"\\n\";\n}\n"
  dependsOn:
  - assumption.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - Graph/base.hpp
  - Graph/count_spanning_tree.hpp
  - Matrix/Matrix.hpp
  - Matrix/Vector.hpp
  isVerificationFile: true
  path: test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp
  requiredBy: []
  timestamp: '2026-06-24 18:12:55+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp
- /verify/test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp.html
title: test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp
---
