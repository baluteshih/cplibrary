---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/SegmentTree.hpp
    title: DataStructure/SegmentTree.hpp
  - icon: ':question:'
    path: Graph/UnifiedWeight.hpp
    title: Graph/UnifiedWeight.hpp
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/HeavyLightDecomposition.hpp
    title: Tree/HeavyLightDecomposition.hpp
  - icon: ':question:'
    path: Tree/Tree.hpp
    title: Tree/Tree.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/vertex_set_path_composite
  bundledCode: "#line 1 \"test/1_library_checker/tree/vertex_set_path_composite.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
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
    }\n#line 3 \"test/1_library_checker/tree/vertex_set_path_composite.test.cpp\"\n\
    \n#line 2 \"Numeric/Modint.hpp\"\n\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
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
    #line 2 \"Tree/HeavyLightDecomposition.hpp\"\n\n#line 2 \"Tree/Tree.hpp\"\n\n\
    #line 2 \"Graph/base.hpp\"\n\ntemplate<bool directed = true, typename Edge = void,\
    \ typename Vertex = void>\nclass Graph {\npublic:\n    static constexpr bool hasEdgeWeight\
    \ = !std::is_same_v<Edge, void>;\n    static constexpr bool hasVertexWeight =\
    \ !std::is_same_v<Vertex, void>;\n    using edge_value_type = Edge;\n    using\
    \ vertex_value_type = Vertex;\n    struct Empty {};\n    struct edge_v {\n   \
    \     int from, to;\n        [[no_unique_address]] std::conditional_t<hasEdgeWeight,\
    \ Edge, Empty> weight;\n        edge_v() {}\n        edge_v(int u, int v) : from(u),\
    \ to(v) {}\n        template <typename W>\n        edge_v(int u, int v, const\
    \ W &w) requires(hasEdgeWeight) : from(u), to(v), weight(w) {}\n        template\
    \ <typename OtherEdge>\n        edge_v(const OtherEdge &other) requires(hasEdgeWeight\
    \ && requires(OtherEdge o) { o.weight; }) \n            : from(other.from), to(other.to),\
    \ weight(other.weight) {}\n        template <typename OtherEdge>\n        edge_v(const\
    \ OtherEdge &other) requires(!hasEdgeWeight || !requires(OtherEdge o) { o.weight;\
    \ }) \n            : from(other.from), to(other.to) {} \n        edge_v reversed()\
    \ const {\n            edge_v res(*this);\n            std::swap(res.from, res.to);\n\
    \            return res;\n        }\n        friend ostream& operator<<(ostream&\
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
    #line 2 \"Graph/UnifiedWeight.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\n\
    \ntemplate<typename T, typename Fallback>\nusing ReplaceVoid = std::conditional_t<std::same_as<T,\
    \ void>, Fallback, T>;\n\ntemplate <typename A, typename B>\nconcept ValidAddableState\
    \ =\n    (std::same_as<A, void> && std::same_as<B, void>) ||\n    requires(const\
    \ ReplaceVoid<A, B>& a, \n             const ReplaceVoid<B, A>& b) {\n       \
    \ a + b;\n    };\n\ntemplate <typename A, typename B>\nconcept ValidSubtractableState\
    \ = \n    (std::same_as<A, void> && std::same_as<B, void>) ||\n    requires(const\
    \ ReplaceVoid<A, B>& a, \n             const ReplaceVoid<B, A>& b) {\n       \
    \ a - b;\n    };\n#line 4 \"Graph/UnifiedWeight.hpp\"\n\ntemplate <typename Edge,\
    \ typename Vertex>\nstruct UnifiedWeight {\n    using type = std::conditional_t<!std::is_same_v<Vertex,\
    \ void>, Vertex, Edge>;\n};\n\ntemplate <typename Edge, typename Vertex>\nusing\
    \ UnifiedWeight_t = typename UnifiedWeight<Edge, Vertex>::type;\n#line 5 \"Tree/Tree.hpp\"\
    \n\ntemplate<typename Edge = void, typename Vertex = void>\nclass Tree : public\
    \ Graph<false, Edge, Vertex> {\npublic:\n    using super = Graph<false, Edge,\
    \ Vertex>;\n    using super::hasEdgeWeight;\n    using super::hasVertexWeight;\n\
    \    using WeightType = UnifiedWeight_t<Edge, Vertex>;\n    int current_root;\n\
    \    std::vector<int> pa, dfs_in, dfs_out;\n    std::vector<int> preorder, postorder;\n\
    \    Tree(int n): super(n), current_root(-1) {}\n    Tree(const super &graph,\
    \ const std::vector<int> &edge_index): super(graph.n()), current_root(-1) {\n\
    \        assert(int(edge_index.size()) + 1 == this->n());\n        for (int eid\
    \ : edge_index)\n            this->add_edge(graph.edge(eid));\n    }\n    void\
    \ traverse(int root = 0) {\n        current_root = root;\n        std::vector<int>(this->n()).swap(pa);\n\
    \        std::vector<int>(this->n()).swap(dfs_in);\n        std::vector<int>(this->n()).swap(dfs_out);\n\
    \        preorder.clear(), preorder.reserve(this->n());\n        postorder.clear(),\
    \ postorder.reserve(this->n());\n        int dft = -1;\n        auto dfs = [&](auto&\
    \ self, int u, int f) -> void {\n            pa[u] = f;\n            dfs_in[u]\
    \ = ++dft;\n            preorder.push_back(u);\n            for (auto [v, eid]\
    \ : this->G[u])\n                if (eid != f)\n                    self(self,\
    \ v, eid);\n            dfs_out[u] = dft;\n            postorder.push_back(u);\n\
    \        };\n        dfs(dfs, root, -1);\n    }\n    bool ancestor(int u, int\
    \ v) const {\n        return dfs_in[u] <= dfs_in[v] && dfs_out[v] <= dfs_out[u];\n\
    \    }\n    void run_order(const std::vector<int> &order, const auto &func) {\n\
    \        for (int i : order)\n            func(i);\n    }\n    void predfs(const\
    \ auto &func) {\n        run_order(preorder, func);\n    }\n    void postdfs(const\
    \ auto &func) {\n        run_order(postorder, func);\n    }\n    int parent(int\
    \ u) const {\n        if (pa[u] == -1) return u;\n        return this->opposite(u,\
    \ pa[u]);\n    }\n    int parent_eid(int u) const {\n        return pa[u];\n \
    \   }\n    super::edge_v& parent_edge(int u) {\n        assert(pa[u] != -1);\n\
    \        return this->edge(pa[u]);\n    }\n    super::edge_v parent_edge(int u)\
    \ const {\n        assert(pa[u] != -1);\n        return this->edge(pa[u]);\n \
    \   }\n    std::vector<int> parents(int root = -1) {\n        if (current_root\
    \ == -1 || (root != -1 && current_root != root)) {\n            assert(root !=\
    \ -1);\n            traverse(root);\n        }\n        std::vector<int> res(this->n());\n\
    \        for (int i = 0; i < this->n(); ++i)\n            res[i] = parent(i);\n\
    \        return res;\n    }\n    std::vector<int> depth(int root = -1) {\n   \
    \     if (current_root == -1 || (root != -1 && current_root != root)) {\n    \
    \        assert(root != -1);\n            traverse(root);\n        }\n       \
    \ std::vector<int> res(this->n(), -1);\n        predfs([&](int u) {\n        \
    \    res[u] = res[parent(u)] + 1;\n        });\n        return res;\n    }\n \
    \   auto distance_edge(int root = -1) requires (hasEdgeWeight) {\n        if (current_root\
    \ == -1 || (root != -1 && current_root != root)) {\n            assert(root !=\
    \ -1);\n            traverse(root);\n        }\n        std::vector<Edge> res(this->n());\n\
    \        predfs([&](int u) {\n            if (parent_eid(u) != -1)\n         \
    \       res[u] = res[parent(u)] + parent_edge(u).weight;\n        });\n      \
    \  return res;\n    }\n    auto weighted_distance(int root = -1) requires (ValidAddableState<Edge,\
    \ Vertex>) {\n        if (current_root == -1 || (root != -1 && current_root !=\
    \ root)) {\n            assert(root != -1);\n            traverse(root);\n   \
    \     }\n        std::vector<WeightType> res(this->n());\n        predfs([&](int\
    \ u) {\n            res[u] = res[parent(u)];\n            if constexpr (hasEdgeWeight)\
    \ if (u != root)\n                res[u] = res[u] + parent_edge(u).weight;\n \
    \           if constexpr (hasVertexWeight)\n                res[u] = res[u] +\
    \ this->weight[u];\n        });\n        return res;\n    }\n    std::vector<int>\
    \ subtree_size(int root = -1) {\n        if (current_root == -1 || (root != -1\
    \ && current_root != root)) {\n            assert(root != -1);\n            traverse(root);\n\
    \        }\n        std::vector<int> res(this->n(), 1);\n        predfs([&](int\
    \ u) {\n            for (auto [v, eid] : this->G[u])\n                if (eid\
    \ != parent_eid(u))\n                    res[u] += res[v];\n        });\n    \
    \    return res;\n    }\n    std::vector<int> path(int u, int v, int root = -1)\
    \ {\n        if (current_root == -1 || (root != -1 && current_root != root)) {\n\
    \            if (root == -1) root = 0;\n            traverse(root);\n        }\n\
    \        std::vector<int> lft, rgt;\n        while (!ancestor(v, u)) {\n     \
    \       rgt.push_back(v);\n            v = parent(v);\n        }\n        while\
    \ (u != v) {\n            lft.push_back(u);\n            u = parent(u);\n    \
    \    }\n        lft.push_back(u);\n        lft.insert(lft.end(), rgt.rbegin(),\
    \ rgt.rend());\n        return lft; \n    }\n    unsigned long long shift_hash_value(unsigned\
    \ long long z) {\n        z ^= z >> 12; z ^= z << 25; z ^= z >> 27;\n        return\
    \ z * 2685821657736338717LL;\n    }\n    std::vector<unsigned long long> hash_values(int\
    \ root = -1, unsigned long long seed = 7122) {\n        if (current_root == -1\
    \ || (root != -1 && current_root != root)) {\n            if (root == -1) root\
    \ = 0;\n            traverse(root);\n        }\n        std::vector<unsigned long\
    \ long> res(this->n());\n        postdfs([&](int u) {\n            res[u] = seed;\n\
    \            for (auto [v, eid] : this->G[u])\n                if (eid != parent_eid(u))\n\
    \                    res[u] += res[v];\n            res[u] = shift_hash_value(res[u]);\n\
    \        });\n        return res;\n    }\n};\n#line 4 \"Tree/HeavyLightDecomposition.hpp\"\
    \n\ntemplate<typename Edge = void, typename Vertex = void>\nclass HeavyLightDecomposition\
    \ : public Tree<Edge, Vertex> {\npublic:\n    using super = Tree<Edge, Vertex>;\n\
    \    HeavyLightDecomposition(int n): super(n) {} \n    HeavyLightDecomposition(const\
    \ super &tree): super(tree) {}\n    std::vector<int> sz, top, dep, tail;\n   \
    \ void build(int root = 0) {\n        this->current_root = root;\n        std::vector<int>(this->n()).swap(this->pa);\n\
    \        std::vector<int>(this->n()).swap(this->dfs_in);\n        std::vector<int>(this->n()).swap(this->dfs_out);\n\
    \        std::vector<int>(this->n(), 1).swap(sz);\n        std::vector<int>(this->n()).swap(top);\n\
    \        std::vector<int>(this->n()).swap(dep);\n        std::vector<int>(this->n()).swap(tail);\n\
    \        this->preorder.clear(), this->preorder.reserve(this->n());\n        this->postorder.clear(),\
    \ this->postorder.reserve(this->n());\n        auto dfs_sz = [&](auto& self, int\
    \ u, int f) -> void {\n            int max_sub = 0;\n            for (int i =\
    \ 0; i < int(this->G[u].size()); ++i) {\n                auto [v, eid] = this->G[u][i];\n\
    \                if (eid == f) continue;\n                self(self, v, eid);\n\
    \                sz[u] += sz[v];\n                if (sz[v] > max_sub) {\n   \
    \                 max_sub = sz[v];\n                    std::swap(this->G[u][0],\
    \ this->G[u][i]); \n                }\n            }\n        };\n        dfs_sz(dfs_sz,\
    \ root, -1);\n        this->traverse(root);\n        this->predfs([&](int u) {\n\
    \            int f = this->parent(u);\n            if (u == f || this->opposite(f,\
    \ this->G[f][0].second) != u)\n                top[u] = u;\n            else\n\
    \                top[u] = top[f];\n            tail[top[u]] = u;\n           \
    \ if (u != f) dep[u] = dep[f] + 1;\n        });\n    }\n    int lca(int u, int\
    \ v) const {\n        while (top[u] != top[v]) {\n            if (dep[top[u]]\
    \ > dep[top[v]]) u = this->parent(top[u]);\n            else v = this->parent(top[v]);\n\
    \        }\n        return dep[u] < dep[v] ? u : v;\n    }\n    // func(int l,\
    \ int r, bool is_up), intervals are [l, r), is_up is true if the interval is towarding\
    \ to the root\n    template <bool is_edge, class F>\n    void work_path(int u,\
    \ int v, F func) const {\n        std::vector<std::pair<int, int>> up_path, down_path;\n\
    \        while (top[u] != top[v]) {\n            if (dep[top[u]] > dep[top[v]])\
    \ {\n                up_path.emplace_back(this->dfs_in[top[u]], this->dfs_in[u]\
    \ + 1);\n                u = this->parent(top[u]);\n            }\n          \
    \  else {\n                down_path.emplace_back(this->dfs_in[top[v]], this->dfs_in[v]\
    \ + 1);\n                v = this->parent(top[v]);\n            }\n        }\n\
    \        if (dep[u] < dep[v])\n            down_path.emplace_back(this->dfs_in[u]\
    \ + is_edge, this->dfs_in[v] + 1);\n        else if (dep[u] > dep[v] || !is_edge)\n\
    \            up_path.emplace_back(this->dfs_in[v] + is_edge, this->dfs_in[u] +\
    \ 1);\n        for (auto [l, r] : up_path) func(l, r, true);\n        std::reverse(down_path.begin(),\
    \ down_path.end());\n        for (auto [l, r] : down_path) func(l, r, false);\n\
    \    }\n    // func(int l, int r), intervals are [l, r), intervals could be empty\n\
    \    template <bool is_edge, class F>\n    void work_subtree(int u, F func) const\
    \ {\n        func(this->dfs_in[u] + is_edge, this->dfs_out[u] + 1);\n    }\n};\n\
    #line 2 \"DataStructure/SegmentTree.hpp\"\n\ntemplate<typename Value = int, typename\
    \ Tag = void, bool pushdown = true>\nclass SegmentTree {\n    static constexpr\
    \ bool hasTag = !std::is_same_v<Tag, void>;\n    static_assert(pushdown || hasTag,\
    \ \"Lazy tag must exist when pushdown is false\");\n    int n;\n    vector<Value>\
    \ seg;\n    struct Empty {};\n    [[no_unique_address]] std::conditional_t<hasTag,\
    \ std::vector<Tag>, Empty> lazy;\n    Value get_val(int rt) {\n        if constexpr\
    \ (pushdown) return seg[rt];\n        else return seg[rt] + lazy[rt];\n    }\n\
    \    void up(int rt) {\n        seg[rt] = get_val(rt << 1) + get_val(rt << 1 |\
    \ 1);\n    }\n    void give_tag(int rt, auto tag) requires (hasTag) {\n      \
    \  if constexpr (pushdown) seg[rt] = seg[rt] + tag;\n        lazy[rt] = lazy[rt]\
    \ + tag;\n    }\n    void down(int rt) requires (hasTag && pushdown) {\n     \
    \   give_tag(rt << 1, lazy[rt]);\n        give_tag(rt << 1 | 1, lazy[rt]);\n \
    \       lazy[rt] = Tag();\n    }\n    void initialize(int l, int r, int rt, const\
    \ vector<Value> &data) {\n        if (r - l == 1) \n            return seg[rt]\
    \ = data[l], void();\n        int mid = (l + r) >> 1;\n        initialize(l, mid,\
    \ rt << 1, data);\n        initialize(mid, r, rt << 1 | 1, data);\n        up(rt);\n\
    \    }\n    Value range_prod(int L, int R, int l, int r, int rt) {\n        if\
    \ (L <= l && R >= r)\n            return get_val(rt);\n        if constexpr (hasTag\
    \ && pushdown) down(rt);\n        int mid = (l + r) >> 1;\n        if constexpr\
    \ (pushdown) {\n            if (R <= mid) return range_prod(L, R, l, mid, rt <<\
    \ 1);\n            if (L >= mid) return range_prod(L, R, mid, r, rt << 1 | 1);\n\
    \            return range_prod(L, R, l, mid, rt << 1) + range_prod(L, R, mid,\
    \ r, rt << 1 | 1); \n        }\n        else {\n            if (R <= mid) return\
    \ range_prod(L, R, l, mid, rt << 1) + lazy[rt];\n            if (L >= mid) return\
    \ range_prod(L, R, mid, r, rt << 1 | 1) + lazy[rt];\n            return range_prod(L,\
    \ R, l, mid, rt << 1) + range_prod(L, R, mid, r, rt << 1 | 1) + lazy[rt];\n  \
    \      }\n    }\n    void modify(int x, int l, int r, int rt, const Value &v)\
    \ {\n        if (r - l == 1)\n            return seg[rt] = v, void();\n      \
    \  if constexpr (hasTag && pushdown) down(rt);\n        int mid = (l + r) >> 1;\n\
    \        if constexpr (pushdown) {\n            if (x < mid) modify(x, l, mid,\
    \ rt << 1, v);\n            else modify(x, mid, r, rt << 1 | 1, v);\n        }\n\
    \        else {\n            if (x < mid) modify(x, l, mid, rt << 1, v - lazy[rt]);\n\
    \            else modify(x, mid, r, rt << 1 | 1, v - lazy[rt]);\n        }\n \
    \       up(rt);\n    }\n    void transform(int x, int l, int r, int rt, const\
    \ auto &func) {\n        if (r - l == 1)\n            return func(seg[rt]), void();\n\
    \        if constexpr (hasTag && pushdown) down(rt);\n        int mid = (l + r)\
    \ >> 1;\n        if (x < mid) transform(x, l, mid, rt << 1, func);\n        else\
    \ transform(x, mid, r, rt << 1 | 1, func);\n        up(rt);\n    }\n    void range_transform(int\
    \ L, int R, int l, int r, int rt, const auto &tag) requires (hasTag) {\n     \
    \   if (L <= l && R >= r)\n            return give_tag(rt, tag);\n        if constexpr\
    \ (pushdown) down(rt);\n        int mid = (l + r) >> 1;\n        if (L < mid)\
    \ range_transform(L, R, l, mid, rt << 1, tag);\n        if (R > mid) range_transform(L,\
    \ R, mid, r, rt << 1 | 1, tag);\n        up(rt);\n    }\n    void range_transform_beats(int\
    \ L, int R, int l, int r, int rt, const auto &tag, const auto &tag_condition,\
    \ auto... tag_sum) requires (hasTag) {\n        if (L <= l && R >= r && tag_condition([&]{\
    \ if constexpr(pushdown) return seg[rt]; else return get_val(rt) + (..., tag_sum);\
    \ }()))\n            return give_tag(rt, tag);\n        assert(r - l > 1);\n \
    \       if constexpr (pushdown) down(rt);\n        else ((tag_sum = tag_sum +\
    \ lazy[rt]), ...);\n        int mid = (l + r) >> 1;\n        if (L < mid) range_transform_beats(L,\
    \ R, l, mid, rt << 1, tag, tag_condition, tag_sum...);\n        if (R > mid) range_transform_beats(L,\
    \ R, mid, r, rt << 1 | 1, tag, tag_condition, tag_sum...);\n        up(rt);\n\
    \    }\n    int range_left_search(int L, int R, int l, int r, int rt, const auto\
    \ &condition, auto... tag_sum) {\n        if (r - l == 1) {\n            if (!condition([&]{\
    \ if constexpr(pushdown) return seg[rt]; else return get_val(rt) + (..., tag_sum);\
    \ }()))\n                return R;\n            return l;\n        }\n       \
    \ int mid = (l + r) >> 1;\n        if constexpr (hasTag && pushdown) down(rt);\n\
    \        if constexpr (!pushdown) ((tag_sum = tag_sum + lazy[rt]), ...);\n   \
    \     if (L <= l && R >= r) {\n            if (condition([&]{ if constexpr(pushdown)\
    \ return seg[rt << 1]; else return get_val(rt << 1) + (..., tag_sum); }()))\n\
    \                return range_left_search(L, R, l, mid, rt << 1, condition, tag_sum...);\n\
    \            return range_left_search(L, R, mid, r, rt << 1 | 1, condition, tag_sum...);\n\
    \        }\n        int left = R;\n        if (L < mid) left = range_left_search(L,\
    \ R, l, mid, rt << 1, condition, tag_sum...);\n        if (left == R) {\n    \
    \        if (R > mid) return range_left_search(L, R, mid, r, rt << 1 | 1, condition,\
    \ tag_sum...);\n            return R;\n        }\n        return left;\n    }\n\
    \    int range_right_search(int L, int R, int l, int r, int rt, const auto &condition,\
    \ auto... tag_sum) {\n        if (r - l == 1) {\n            if (!condition([&]{\
    \ if constexpr(pushdown) return seg[rt]; else return get_val(rt) + (..., tag_sum);\
    \ }()))\n                return L - 1;\n            return l;\n        }\n   \
    \     int mid = (l + r) >> 1;\n        if constexpr (hasTag && pushdown) down(rt);\n\
    \        if constexpr (!pushdown) ((tag_sum = tag_sum + lazy[rt]), ...);\n   \
    \     if (L <= l && R >= r) {\n            if (condition([&]{ if constexpr(pushdown)\
    \ return seg[rt << 1 | 1]; else return get_val(rt << 1 | 1) + (..., tag_sum);\
    \ }()))\n                return range_right_search(L, R, mid, r, rt << 1 | 1,\
    \ condition, tag_sum...);\n            return range_right_search(L, R, l, mid,\
    \ rt << 1, condition, tag_sum...);\n        }\n        int right = L - 1;\n  \
    \      if (R > mid) right = range_right_search(L, R, mid, r, rt << 1 | 1, condition,\
    \ tag_sum...);\n        if (right == L - 1) {\n            if (L < mid) return\
    \ range_right_search(L, R, l, mid, rt << 1, condition, tag_sum...);\n        \
    \    return L - 1;\n        }\n        return right;\n    }\n    Value get(int\
    \ x, int l, int r, int rt) {\n        [[no_unique_address]] std::conditional_t<!pushdown,\
    \ Tag, Empty> tag;\n        while (r - l > 1) {\n            if constexpr (hasTag\
    \ && pushdown) down(rt);\n            if constexpr (!pushdown) tag = tag + lazy[rt];\n\
    \            int mid = (l + r) >> 1;\n            if (x < mid) r = mid, rt = rt\
    \ << 1;\n            else l = mid, rt = rt << 1 | 1;\n        }\n        if constexpr\
    \ (pushdown) return seg[rt];\n        else return get_val(rt) + tag;\n    }\n\
    \    void printnode(int l, int r, int rt) {\n        std::cerr << \"[\" << l <<\
    \ \", \" << r << \"): \";\n        if constexpr (hasTag) std::cerr << \"val =\
    \ \" << seg[rt] << \", tag = \" << lazy[rt];\n        else std::cerr << seg[rt];\n\
    \        std::cerr << \"\\n\";\n    }\n    void printinfo(int L, int R, int l,\
    \ int r, int rt) {\n        printnode(l, r, rt);\n        if (L <= l && R >= r)\n\
    \            return;\n        int mid = (l + r) >> 1;\n        if (L < mid) printinfo(L,\
    \ R, l, mid, rt << 1);\n        if (R > mid) printinfo(L, R, mid, r, rt << 1 |\
    \ 1);\n    }\n    void printall(int l, int r, int rt) {\n        printnode(l,\
    \ r, rt);\n        if (r - l == 1) return;\n        int mid = (l + r) >> 1;\n\
    \        printall(l, mid, rt << 1);\n        printall(mid, r, rt << 1 | 1);\n\
    \    }\n    public:\n    SegmentTree(const vector<Value> &data): n(data.size()),\
    \ seg(n << 2) { \n        if constexpr (hasTag) lazy.resize(n << 2); \n      \
    \  initialize(0, n, 1, data);\n    }\n    SegmentTree(int size): SegmentTree(vector<Value>(size))\
    \ {}\n    Value get(int x) {\n        assert(0 <= x && x < n);\n        return\
    \ get(x, 0, n, 1);\n    }\n    Value range_prod(int l, int r) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l == r) return Value();\n\
    \        return range_prod(l, r, 0, n, 1);\n    }\n    void modify(int x, const\
    \ Value &v) {\n        assert(0 <= x && x < n);\n        modify(x, 0, n, 1, v);\n\
    \    }\n    void transform(int x, const auto &func) {\n        assert(0 <= x &&\
    \ x < n);\n        transform(x, 0, n, 1, func);\n    }\n    void range_transform(int\
    \ l, int r, const auto &tag) requires (hasTag) {\n        assert(0 <= l && r <=\
    \ n);\n        assert(l <= r);\n        if (l < r)\n            range_transform(l,\
    \ r, 0, n, 1, tag);\n    }\n    void range_transform_beats(int l, int r, const\
    \ auto &tag, const auto &tag_condition) requires (hasTag) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l < r)\n            range_transform_beats(l,\
    \ r, 0, n, 1, tag, tag_condition);\n    }\n    /*\n       For the given element\
    \ range [l, r)\n       Perform segment tree binary search within the range with\
    \ left half first \n     */\n    int range_left_search(const auto &condition,\
    \ int l = -1, int r = -1) {\n        if (l == -1 && r == -1) l = 0, r = n;\n \
    \       assert(0 <= l && r <= n);\n        assert(l <= r);\n        if (l == r)\
    \ return r;\n        return range_left_search(l, r, 0, n, 1, condition);\n   \
    \ }\n    /*\n       For the given element range (l, r]\n       Perform segment\
    \ tree binary search within the range with right half first \n     */\n    int\
    \ range_right_search(const auto &condition, int l = -1, int r = -1) {\n      \
    \  if (l == -1 && r == -1) l = -1, r = n - 1;\n        ++l, ++r;\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l == r) return l - 1;\n\
    \        return range_right_search(l, r, 0, n, 1, condition);\n    }\n    void\
    \ printinfo(int l, int r) {\n        assert(0 <= l && r <= n);\n        assert(l\
    \ <= r);\n        std::cerr << \"\\e[1;33mInfo [\" << l << \", \" << r << \"):\\\
    n\";\n        if (l < r) \n            printinfo(l, r, 0, n, 1);\n        cerr\
    \ << \"\\e[0m\\n\";\n    }\n    void printall() {\n        std::cerr << \"\\e[1;33mInfo\
    \ all:\\n\";\n        printall(0, n, 1);\n        cerr << \"\\e[0m\\n\";\n   \
    \ }\n};\n#line 7 \"test/1_library_checker/tree/vertex_set_path_composite.test.cpp\"\
    \n\nusing mint = modint998244353;\n\ntemplate<bool rv = false>\nstruct Value {\n\
    \    mint a, b;\n    Value(mint _a = 0, mint _b = 0): a(_a), b(_b) {}\n    template<typename\
    \ Vother>\n    Value(const Vother &v): a(v.a), b(v.b) {}\n    Value operator+(const\
    \ Value &rhs) {\n        if constexpr (rv) return Value(a * rhs.a, rhs.a * b +\
    \ rhs.b);\n        else return Value(a * rhs.a, a * rhs.b + b);\n    }\n    mint\
    \ get_val(mint x) {\n        return a * x + b;\n    }\n    friend ostream& operator<<(ostream&\
    \ os, const Value &v) {\n        os << v.a << \" \" << v.b;\n        return os;\n\
    \    }\n    friend istream& operator>>(istream& is, Value &v) {\n        is >>\
    \ v.a >> v.b;\n        return is;\n    }\n};\n\nint main() {\n    ios::sync_with_stdio(0),\
    \ cin.tie(0);\n    int n, q;\n    cin >> n >> q;\n    HeavyLightDecomposition<>\
    \ hld(n);\n    vector<Value<false>> arr(n);\n    for (auto &i : arr)\n       \
    \ cin >> i;\n    for (int i = 1; i < n; ++i) {\n        int u, v;\n        cin\
    \ >> u >> v;\n        hld.add_edge(u, v);\n    }\n    hld.build();\n    vector<Value<false>>\
    \ weight(n);\n    for (int i = 0; i < n; ++i)\n        weight[i] = arr[hld.preorder[i]];\n\
    \    vector<Value<true>> rweight(weight.begin(), weight.end());\n    SegmentTree<Value<false>>\
    \ seg(weight);\n    SegmentTree<Value<true>> rseg(rweight);\n    while (q--) {\n\
    \        int type;\n        cin >> type;\n        if (type == 0) {\n         \
    \   int p;\n            Value v;\n            cin >> p >> v;\n            seg.modify(hld.dfs_in[p],\
    \ v);\n            rseg.modify(hld.dfs_in[p], v);\n        }\n        else {\n\
    \            int u, v;\n            mint x;\n            cin >> u >> v >> x;\n\
    \            hld.work_path<false>(u, v, [&](int l, int r, bool is_up) {\n    \
    \            if (is_up) x = seg.range_prod(l, r).get_val(x); \n              \
    \  else x = rseg.range_prod(l, r).get_val(x);\n            }); \n            cout\
    \ << x << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
    \n#include \"default_code.hpp\"\n\n#include \"Numeric/Modint.hpp\"\n#include \"\
    Tree/HeavyLightDecomposition.hpp\"\n#include \"DataStructure/SegmentTree.hpp\"\
    \n\nusing mint = modint998244353;\n\ntemplate<bool rv = false>\nstruct Value {\n\
    \    mint a, b;\n    Value(mint _a = 0, mint _b = 0): a(_a), b(_b) {}\n    template<typename\
    \ Vother>\n    Value(const Vother &v): a(v.a), b(v.b) {}\n    Value operator+(const\
    \ Value &rhs) {\n        if constexpr (rv) return Value(a * rhs.a, rhs.a * b +\
    \ rhs.b);\n        else return Value(a * rhs.a, a * rhs.b + b);\n    }\n    mint\
    \ get_val(mint x) {\n        return a * x + b;\n    }\n    friend ostream& operator<<(ostream&\
    \ os, const Value &v) {\n        os << v.a << \" \" << v.b;\n        return os;\n\
    \    }\n    friend istream& operator>>(istream& is, Value &v) {\n        is >>\
    \ v.a >> v.b;\n        return is;\n    }\n};\n\nint main() {\n    ios::sync_with_stdio(0),\
    \ cin.tie(0);\n    int n, q;\n    cin >> n >> q;\n    HeavyLightDecomposition<>\
    \ hld(n);\n    vector<Value<false>> arr(n);\n    for (auto &i : arr)\n       \
    \ cin >> i;\n    for (int i = 1; i < n; ++i) {\n        int u, v;\n        cin\
    \ >> u >> v;\n        hld.add_edge(u, v);\n    }\n    hld.build();\n    vector<Value<false>>\
    \ weight(n);\n    for (int i = 0; i < n; ++i)\n        weight[i] = arr[hld.preorder[i]];\n\
    \    vector<Value<true>> rweight(weight.begin(), weight.end());\n    SegmentTree<Value<false>>\
    \ seg(weight);\n    SegmentTree<Value<true>> rseg(rweight);\n    while (q--) {\n\
    \        int type;\n        cin >> type;\n        if (type == 0) {\n         \
    \   int p;\n            Value v;\n            cin >> p >> v;\n            seg.modify(hld.dfs_in[p],\
    \ v);\n            rseg.modify(hld.dfs_in[p], v);\n        }\n        else {\n\
    \            int u, v;\n            mint x;\n            cin >> u >> v >> x;\n\
    \            hld.work_path<false>(u, v, [&](int l, int r, bool is_up) {\n    \
    \            if (is_up) x = seg.range_prod(l, r).get_val(x); \n              \
    \  else x = rseg.range_prod(l, r).get_val(x);\n            }); \n            cout\
    \ << x << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - Tree/HeavyLightDecomposition.hpp
  - Tree/Tree.hpp
  - Graph/base.hpp
  - Graph/UnifiedWeight.hpp
  - Algebra/ValidOperation.hpp
  - DataStructure/SegmentTree.hpp
  isVerificationFile: true
  path: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
  requiredBy: []
  timestamp: '2026-05-19 02:16:25+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/tree/vertex_set_path_composite.test.cpp
- /verify/test/1_library_checker/tree/vertex_set_path_composite.test.cpp.html
title: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
---
