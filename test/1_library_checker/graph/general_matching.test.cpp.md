---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Graph/Matching.hpp
    title: Graph/Matching.hpp
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/general_matching
    links:
    - https://judge.yosupo.jp/problem/general_matching
  bundledCode: "#line 1 \"test/1_library_checker/graph/general_matching.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/general_matching\"\n#line\
    \ 2 \"default_code.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace std;\ntypedef\
    \ long long ll;\ntypedef pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n#define\
    \ X first\n#define Y second\n#define SZ(a) ((int)a.size())\n#define ALL(v) v.begin(),\
    \ v.end()\ntemplate<class A, class B>\nostream& operator<<(ostream& os, const\
    \ pair<A, B> &a) {\n    os << \"(\" << a.first << \", \" << a.second << \")\"\
    ;\n    return os;\n}\ntemplate <typename T>\nconcept PrintableContainer = requires(T&\
    \ a) {\n    a.begin();\n    a.end();\n} && !std::same_as<std::remove_cvref_t<T>,\
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
    }\n#line 3 \"test/1_library_checker/graph/general_matching.test.cpp\"\n\n#line\
    \ 2 \"Graph/Matching.hpp\"\n\n#line 2 \"Graph/base.hpp\"\n\ntemplate<bool directed\
    \ = true, typename Edge = void, typename Vertex = void>\nclass Graph {\npublic:\n\
    \    static constexpr bool hasEdgeWeight = !std::is_same_v<Edge, void>;\n    static\
    \ constexpr bool hasVertexWeight = !std::is_same_v<Vertex, void>;\n    using edge_value_type\
    \ = Edge;\n    using vertex_value_type = Vertex;\n    struct Empty {};\n    struct\
    \ edge_v {\n        int from, to;\n        [[no_unique_address]] std::conditional_t<hasEdgeWeight,\
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
    \   return res;\n    }\n    std::vector<std::pair<int, int>>& adj(int idx) {\n\
    \        return G[idx];\n    }\n    const std::vector<std::pair<int, int>>& adj(int\
    \ idx) const {\n        return G[idx];\n    }\n    Graph reversed() const {\n\
    \        Graph res(n());\n        for (auto &e : edges)\n            res.add_edge(e.reversed());\n\
    \        if constexpr (hasVertexWeight) res.set_vertex_weight(weight);\n     \
    \   return res;\n    }\n    std::pair<std::vector<int>, std::vector<int>> cycle()\
    \ {\n        std::vector<int> vis(this->n());\n        std::vector<int> res_v,\
    \ res_e;\n        int cyc_end = -1;\n        auto dfs = [&](auto self, int u,\
    \ int f) -> int {\n            vis[u] = 1;\n            for (auto [v, eid] : G[u])\
    \ {\n                if (eid == f || vis[v] == 2) continue;\n                if\
    \ (vis[v] == 1) {\n                    res_v.push_back(u);\n                 \
    \   res_e.push_back(eid);\n                    cyc_end = v;\n                \
    \    return 1;\n                }\n                int rt = self(self, v, eid);\n\
    \                if (rt) {\n                    if (rt == 1) { \n            \
    \            res_e.push_back(eid);\n                        res_v.push_back(u);\n\
    \                    }\n                    if (cyc_end == u) rt = 2;\n      \
    \              return rt;\n                }\n            }\n            vis[u]\
    \ = 2;\n            return 0;\n        };\n        for (int i = 0; i < this->n();\
    \ ++i)\n            if (!vis[i] && dfs(dfs, i, -1))\n                break;\n\
    \        std::ranges::reverse(res_v);\n        std::ranges::reverse(res_e);\n\
    \        return std::make_pair(res_v, res_e);\n    }\n    Graph<true, Edge, Vertex>\
    \ oriented(const std::vector<int> &rk) const requires (!directed) {\n        Graph<true,\
    \ Edge, Vertex> res(this->n());\n        for (auto &e : edges)\n            if\
    \ (rk[e.from] < rk[e.to])\n                res.add_edge(e);\n            else\n\
    \                res.add_edge(e.reversed());\n        return res;\n    }\n};\n\
    \ntemplate<typename Edge = void, typename Vertex = void>\nclass UndirectedGraph\
    \ : public Graph<false, Edge, Vertex> {\npublic:\n    using Graph<false, Edge,\
    \ Vertex>::Graph;\n};\n#line 4 \"Graph/Matching.hpp\"\n\n/*\nmatch[u] = -1 implies\
    \ no match\n*/\nstruct Matching : public Graph<false, void, void> { // 0-base\n\
    \    using super = Graph<false, void, void>;\n    std::queue<int> q;\n    std::vector<int>\
    \ fa, s, vis, pre, match;\n    int Find(int u)\n    { return u == fa[u] ? u :\
    \ fa[u] = Find(fa[u]); }\n    int LCA(int x, int y) {\n        static int tk =\
    \ 0; tk++; x = Find(x); y = Find(y);\n        for (;; swap(x, y)) if (x != this->n())\
    \ {\n            if (vis[x] == tk) return x;\n            vis[x] = tk;\n     \
    \       x = Find(pre[match[x]]);\n        }\n    }\n    void Blossom(int x, int\
    \ y, int l) {\n        for (; Find(x) != l; x = pre[y]) {\n            pre[x]\
    \ = y, y = match[x];\n            if (s[y] == 1) q.push(y), s[y] = 0;\n      \
    \      for (int z: {x, y}) if (fa[z] == z) fa[z] = l;\n        }\n    }\n    bool\
    \ Bfs(int r) {\n        iota(ALL(fa), 0); fill(ALL(s), -1);\n        q = queue<int>();\
    \ q.push(r); s[r] = 0;\n        for (; !q.empty(); q.pop()) {\n            for\
    \ (int x = q.front(); auto [u, eid] : this->adj(x))\n                if (s[u]\
    \ == -1) {\n                    if (pre[u] = x, s[u] = 1, match[u] == this->n())\
    \ {\n                        for (int a = u, b = x, last; b != this->n(); a =\
    \ last, b = pre[a])\n                            last = match[b], match[b] = a,\
    \ match[a] = b;\n                        return true;\n                    }\n\
    \                    q.push(match[u]); s[match[u]] = 0;\n                } else\
    \ if (!s[u] && Find(u) != Find(x)) {\n                    int l = LCA(u, x);\n\
    \                    Blossom(x, u, l); Blossom(u, x, l);\n                }\n\
    \        }\n        return false;\n    }\n    Matching(int n) : super(n), fa(n\
    \ + 1), s(n + 1), vis(n + 1), pre(n + 1, n), match(n + 1, n) {}\n    int solve()\
    \ {\n        int ans = 0;\n        for (int x = 0; x < this->n(); ++x)\n     \
    \       if (match[x] == this->n())\n                ans += Bfs(x);\n        std::ranges::replace(match,\
    \ this->n(), -1);\n        return ans;\n    }\n};\n#line 5 \"test/1_library_checker/graph/general_matching.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, m;\n  \
    \  cin >> n >> m;\n    Matching mch(n);\n    while (m--) {\n        int u, v;\n\
    \        cin >> u >> v;\n        mch.add_edge(u, v);\n    }\n    cout << mch.solve()\
    \ << \"\\n\";\n    for (int i = 0; i < n; ++i)\n        if (mch.match[i] > i)\n\
    \            cout << i << \" \" << mch.match[i] << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/general_matching\"\n#include\
    \ \"default_code.hpp\"\n\n#include \"Graph/Matching.hpp\"\n\nint main() {\n  \
    \  ios::sync_with_stdio(0), cin.tie(0);\n    int n, m;\n    cin >> n >> m;\n \
    \   Matching mch(n);\n    while (m--) {\n        int u, v;\n        cin >> u >>\
    \ v;\n        mch.add_edge(u, v);\n    }\n    cout << mch.solve() << \"\\n\";\n\
    \    for (int i = 0; i < n; ++i)\n        if (mch.match[i] > i)\n            cout\
    \ << i << \" \" << mch.match[i] << \"\\n\";\n}\n"
  dependsOn:
  - default_code.hpp
  - Graph/Matching.hpp
  - Graph/base.hpp
  isVerificationFile: true
  path: test/1_library_checker/graph/general_matching.test.cpp
  requiredBy: []
  timestamp: '2026-05-06 14:22:55+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/graph/general_matching.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/graph/general_matching.test.cpp
- /verify/test/1_library_checker/graph/general_matching.test.cpp.html
title: test/1_library_checker/graph/general_matching.test.cpp
---
