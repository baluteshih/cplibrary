---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Graph/BCC.hpp
    title: Graph/BCC.hpp
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/bipolar_orientation.hpp
    title: Graph/bipolar_orientation.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/st_numbering
    links:
    - https://judge.yosupo.jp/problem/st_numbering
  bundledCode: "#line 1 \"test/1_library_checker/graph/st_numbering.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/st_numbering\"\n#line 2 \"default_code.hpp\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\ntypedef long long ll;\ntypedef\
    \ pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n#define X first\n#define Y second\n\
    #define SZ(a) ((int)a.size())\n#define ALL(v) v.begin(), v.end()\ntemplate<class\
    \ A, class B>\nostream& operator<<(ostream& os, const pair<A, B> &a) {\n    os\
    \ << \"(\" << a.first << \", \" << a.second << \")\";\n    return os;\n}\ntemplate\
    \ <typename T>\nconcept PrintableContainer = requires(T& a) {\n    a.begin();\n\
    \    a.end();\n} && !std::same_as<std::remove_cvref_t<T>, std::string> &&\n  \
    \   !std::same_as<std::remove_cvref_t<T>, std::string_view> &&\n     !std::is_convertible_v<T,\
    \ const char*>;\ntemplate <PrintableContainer T>\nstd::ostream& operator<<(std::ostream&\
    \ os, const T& a) {\n    os << \"[ \";\n    bool first = true;\n    for (const\
    \ auto& item : a) {\n        if (!first) os << \", \";\n        os << item;\n\
    \        first = false;\n    }\n    return os << \" ]\";\n}\n#ifdef bbq\n#include\
    \ <experimental/iterator>\n#define safe cerr<<__PRETTY_FUNCTION__<<\" line \"\
    <<__LINE__<<\" safe\\n\"\n#define sepline sepline_() \n#define debug(a...) debug_(#a,\
    \ a)\n#define orange(a...) orange_(#a, a)\nvoid debug_(auto s, auto ...a) {\n\
    \    cerr << \"\\e[1;32m(\" << s << \") = (\";\n    int f = 0;\n    (..., (cerr\
    \ << (f++ ? \", \" : \"\") << a));\n    cerr << \")\\e[0m\\n\";\n}\nvoid orange_(auto\
    \ s, auto L, auto R) {\n    cerr << \"\\e[1;33m[ \" << s << \" ] = [ \";\n   \
    \ using namespace experimental;\n    copy(L, R, make_ostream_joiner(cerr, \",\
    \ \"));\n    cerr << \" ]\\e[0m\\n\";\n}\nvoid sepline_(int length = 50) {\n \
    \   cerr << \"\\e[1;35m\";\n    cerr << string(length, '=');\n    cerr << \"\\\
    e[0m\\n\";\n}\n#else\n#define safe ((void)0)\n#define sepline safe\n#define debug(...)\
    \ safe\n#define orange(...) safe\n#endif\n\nvoid chmax(auto &x, auto val) {\n\
    \    x = max(x, val);\n}\n\nvoid chmin(auto &x, auto val) {\n    x = min(x, val);\n\
    }\n\nvector<int> count_array(const auto &container, int sz = -1) {\n    if (sz\
    \ == -1) sz = *ranges::max_element(container) + 1;\n    vector<int> res(sz);\n\
    \    for (auto x : container) ++res[x];\n    return res;\n}\n\ntemplate<class\
    \ T>\nvoid discretization(vector<T> &vals) {\n    ranges::sort(vals);\n    vals.erase(ranges::unique(vals).begin(),\
    \ vals.end());\n}\n#line 3 \"test/1_library_checker/graph/st_numbering.test.cpp\"\
    \n\n#line 2 \"Graph/BCC.hpp\"\n\r\n#line 2 \"Graph/base.hpp\"\n\ntemplate<bool\
    \ directed = true, typename Edge = void, typename Vertex = void>\nclass Graph\
    \ {\npublic:\n    static constexpr bool hasEdgeWeight = !std::is_same_v<Edge,\
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
    \          return res;\n        }\n        friend ostream& operator<<(ostream&\
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
    #line 4 \"Graph/BCC.hpp\"\n\r\ntemplate<typename Edge = void, typename Vertex\
    \ = void>\r\nstruct BCC : public Graph<false, Edge, Vertex> { // 0-base\r\n  \
    \  using super = Graph<false, Edge, Vertex>;\r\n    int dft, nbcc;\r\n    std::vector<int>\
    \ low, dfn, bln, stk, is_ap;\r\n    std::vector<std::vector<int>> bcc;\r\n   \
    \ void make_bcc(int u) {\r\n        bcc.emplace_back(1, u); \r\n        for (;\
    \ stk.back() != u; stk.pop_back())\r\n            bln[stk.back()] = nbcc, bcc[nbcc].push_back(stk.back());\r\
    \n        stk.pop_back(), bln[u] = nbcc++;\r\n    }\r\n    void dfs(int u, int\
    \ f) {\r\n        int child = 0;\r\n        low[u] = dfn[u] = ++dft, stk.push_back(u);\r\
    \n        for (auto [v, eid] : this->G[u])\r\n            if (!dfn[v]) {\r\n \
    \               dfs(v, u), ++child;\r\n                low[u] = std::min(low[u],\
    \ low[v]);\r\n                if (dfn[u] <= low[v]) {\r\n                    is_ap[u]\
    \ = 1, bln[u] = nbcc;\r\n                    make_bcc(v), bcc.back().push_back(u);\r\
    \n                }\r\n            } else if (dfn[v] < dfn[u] && v != f)\r\n \
    \               low[u] = std::min(low[u], dfn[v]);\r\n        if (f == -1 && child\
    \ < 2) is_ap[u] = 0;\r\n        if (f == -1 && child == 0) make_bcc(u);\r\n  \
    \  }\r\n    BCC(int n) : super(n), dft(), nbcc(), low(n), dfn(n), bln(n), is_ap(n)\
    \ {}\r\n    BCC(const super &G) : super(G), dft(), nbcc(), low(G.n()), dfn(G.n()),\
    \ bln(G.n()), is_ap(G.n()) {}\r\n    void solve() {\r\n        for (int i = 0;\
    \ i < this->n(); ++i)\r\n            if (!dfn[i]) dfs(i, -1);\r\n    }\r\n   \
    \ /*\r\n    Return std::pair<idx, tree adj matrix>\r\n    idx[u]: the new vertex\
    \ index of the vertex u belongs to\r\n    */\r\n    std::pair<std::vector<int>,\
    \ std::vector<std::vector<int>>> block_cut_tree() const {\r\n        int count\
    \ = nbcc;\r\n        std::vector<int> cir, newbln(bln);\r\n        std::vector<std::vector<int>>\
    \ nG;\r\n        cir.resize(count);\r\n        for (int i = 0; i < this->n();\
    \ ++i)\r\n            if (is_ap[i])\r\n                newbln[i] = count++;\r\n\
    \        cir.resize(count, 1), nG.resize(count);\r\n        for (int i = 0; i\
    \ < count && !cir[i]; ++i)\r\n            for (int j : bcc[i])\r\n           \
    \     if (is_ap[j])\r\n                    nG[i].push_back(newbln[j]), nG[newbln[j]].push_back(i);\r\
    \n        return {newbln, nG};\r\n    } // up to 2 * n - 2 nodes!! bln[i] for\
    \ id\r\n};\r\n#line 2 \"Graph/bipolar_orientation.hpp\"\n\n#line 4 \"Graph/bipolar_orientation.hpp\"\
    \n\n// there exists bipolar orientation iff the graph is biconnected after adding\
    \ the edge (s, t)\ntemplate<typename Edge, typename Vertex>\nstd::vector<int>\
    \ bipolar_orientation(Graph<false, Edge, Vertex> &G, int s, int t) {\n    assert(s\
    \ != t);\n    assert(G.m() > 0);\n    int n = G.n();\n    assert(0 <= s && s <\
    \ n);\n    assert(0 <= t && t < n);\n    G[s].insert(G[s].begin(), std::make_pair(t,\
    \ -1));\n    std::vector<int> vis(n), low(n), pa(n, -1), sgn(n), ord;\n    auto\
    \ dfs = [&](auto self, int u) -> void {\n        ord.push_back(u);\n        low[u]\
    \ = vis[u] = ord.size();\n        for (auto [v, eid] : G[u])\n            if (!vis[v])\n\
    \                pa[v] = u, self(self, v), low[u] = std::min(low[u], low[v]);\n\
    \            else\n                low[u] = std::min(low[u], vis[v]);\n    };\n\
    \    dfs(dfs, s);\n    std::vector<int> nxt(n + 1, n), prv = nxt;\n    nxt[s]\
    \ = t, prv[t] = s, sgn[s] = -1;\n    for (int i : ord)\n        if (i != s &&\
    \ i != t) {\n            int p = pa[i], l = ord[low[i] - 1];\n            if (sgn[l]\
    \ > 0)\n                nxt[i] = nxt[prv[i] = p], nxt[p] = prv[nxt[p]] = i;\n\
    \            else\n                prv[i] = prv[nxt[i] = p], prv[p] = nxt[prv[p]]\
    \ = i;\n            sgn[p] = -sgn[l];\n        }\n    std::vector<int> res;\n\
    \    for (int x = s; x != n; x = nxt[x]) res.push_back(x);\n    G[s].erase(G[s].begin());\n\
    \    return res;\n}\n#line 6 \"test/1_library_checker/graph/st_numbering.test.cpp\"\
    \n\nvoid solve() {\n    int n, m, s, t;\n    cin >> n >> m >> s >> t;\n    if\
    \ (m == 0) {\n        cout << \"No\\n\";\n        return;\n    }\n    UndirectedGraph<>\
    \ G(n);\n    while (m--) {\n        int u, v;\n        cin >> u >> v;\n      \
    \  G.add_edge(u, v);\n    }\n    BCC bcc(G);\n    bcc.add_edge(s, t);\n    bcc.solve();\n\
    \    if (bcc.nbcc > 1)\n        cout << \"No\\n\";\n    else {\n        cout <<\
    \ \"Yes\\n\";\n        auto res = bipolar_orientation(G, s, t);\n        vector<int>\
    \ ans(n);\n        for (int i = 0; i < n; ++i) ans[res[i]] = i;\n        for (int\
    \ i = 0; i < n; ++i)\n            cout << ans[i] << \" \\n\"[i + 1 == n];\n  \
    \  }\n}\n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int t;\n\
    \    cin >> t;\n    while (t--) {\n        solve();\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/st_numbering\"\n#include\
    \ \"default_code.hpp\"\n\n#include \"Graph/BCC.hpp\"\n#include \"Graph/bipolar_orientation.hpp\"\
    \n\nvoid solve() {\n    int n, m, s, t;\n    cin >> n >> m >> s >> t;\n    if\
    \ (m == 0) {\n        cout << \"No\\n\";\n        return;\n    }\n    UndirectedGraph<>\
    \ G(n);\n    while (m--) {\n        int u, v;\n        cin >> u >> v;\n      \
    \  G.add_edge(u, v);\n    }\n    BCC bcc(G);\n    bcc.add_edge(s, t);\n    bcc.solve();\n\
    \    if (bcc.nbcc > 1)\n        cout << \"No\\n\";\n    else {\n        cout <<\
    \ \"Yes\\n\";\n        auto res = bipolar_orientation(G, s, t);\n        vector<int>\
    \ ans(n);\n        for (int i = 0; i < n; ++i) ans[res[i]] = i;\n        for (int\
    \ i = 0; i < n; ++i)\n            cout << ans[i] << \" \\n\"[i + 1 == n];\n  \
    \  }\n}\n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int t;\n\
    \    cin >> t;\n    while (t--) {\n        solve();\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - Graph/BCC.hpp
  - Graph/base.hpp
  - Graph/bipolar_orientation.hpp
  isVerificationFile: true
  path: test/1_library_checker/graph/st_numbering.test.cpp
  requiredBy: []
  timestamp: '2026-05-19 02:16:25+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/graph/st_numbering.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/graph/st_numbering.test.cpp
- /verify/test/1_library_checker/graph/st_numbering.test.cpp.html
title: test/1_library_checker/graph/st_numbering.test.cpp
---
