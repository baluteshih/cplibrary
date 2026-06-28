---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/DisjointSet.hpp
    title: Disjoint Set Union (DSU)
  - icon: ':heavy_check_mark:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/complement_bfs.hpp
    title: Graph/complement_bfs.hpp
  - icon: ':heavy_check_mark:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/connected_components_of_complement_graph
    links:
    - https://judge.yosupo.jp/problem/connected_components_of_complement_graph
  bundledCode: "#line 1 \"test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/connected_components_of_complement_graph\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp\"\
    \n\n#line 2 \"Graph/base.hpp\"\n\ntemplate<bool directed = true, typename Edge\
    \ = void, typename Vertex = void>\nclass Graph {\npublic:\n    static constexpr\
    \ bool is_directed = directed;\n    static constexpr bool hasEdgeWeight = !std::is_same_v<Edge,\
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
    #line 2 \"Graph/complement_bfs.hpp\"\n\n#line 4 \"Graph/complement_bfs.hpp\"\n\
    \n// parent[u] is the bfs parent of u, parent[root] = root\ntemplate<typename\
    \ graph>\nstd::vector<int> complement_bfs(const graph &G, int start = -1) {\n\
    \    std::vector<int> vis(G.n()), cur(G.n()), parent(G.n());\n    int vcnt = 0;\n\
    \    std::iota(cur.begin(), cur.end(), 0);\n    if (start != -1) std::swap(cur[start],\
    \ cur.back());\n    while (!cur.empty()) {\n        std::queue<int> q;\n     \
    \   parent[cur.back()] = cur.back();\n        q.push(cur.back());\n        cur.pop_back();\n\
    \        while (!q.empty()) {\n            int u = q.front();\n            q.pop();\n\
    \            ++vcnt;\n            for (auto [v, eid] : G[u])\n               \
    \ vis[v] = vcnt;\n            std::vector<int> nxt;\n            for (int i :\
    \ cur)\n                if (vis[i] == vcnt) nxt.push_back(i);\n              \
    \  else q.push(i), parent[i] = u;\n            cur.swap(nxt);\n        }\n   \
    \ }\n    return parent;\n}\n#line 2 \"DataStructure/DisjointSet.hpp\"\n\ntemplate<typename\
    \ T = void, bool undo_tag = false>\nclass DisjointSet {\nprotected:\n    static\
    \ constexpr bool hasT = !std::is_same_v<T, void>;\n    int n;\n    std::vector<int>\
    \ boss, sz;\n    struct Empty {};\n    [[no_unique_address]] std::conditional_t<hasT,\
    \ std::vector<T>, Empty> data;\n    [[no_unique_address]] std::conditional_t<undo_tag,\
    \ std::vector<std::pair<int*, int>>, Empty> cache;\n    [[no_unique_address]]\
    \ std::conditional_t<undo_tag && hasT, std::vector<std::pair<T*, T>>, Empty> data_cache;\n\
    public:\n    DisjointSet(int n_): n(n_), boss(n), sz(n, 1) {\n        std::iota(boss.begin(),\
    \ boss.end(), 0);\n        if constexpr (hasT) data.resize(n);\n    }\n    DisjointSet(const\
    \ std::vector<T> &data_) requires (hasT) : n(data_.size()), boss(n), sz(n, 1),\
    \ data(data_) {\n        std::iota(boss.begin(), boss.end(), 0);\n    }\n    virtual\
    \ int leader(int u) {\n        if (boss[u] == u) return u;\n        if constexpr\
    \ (undo_tag) return leader(boss[u]);\n        else return boss[u] = leader(boss[u]);\n\
    \    }\n    int size(int u) {\n        return sz[leader(u)];\n    }\n    bool\
    \ same(int u, int v) {\n        return leader(u) == leader(v);\n    }\n    bool\
    \ merge(int u, int v, bool force = false) {\n        u = leader(u), v = leader(v);\n\
    \        if (u == v) return false;\n        if (sz[u] < sz[v] && !force) std::swap(u,\
    \ v);\n        if constexpr (undo_tag) {\n            cache.emplace_back(&boss[v],\
    \ boss[v]); \n            cache.emplace_back(&sz[u], sz[v]); \n            if\
    \ constexpr (hasT)\n                data_cache.emplace_back(&data[u], data[u]);\n\
    \        }\n        boss[v] = u;\n        sz[u] += sz[v];\n        if constexpr\
    \ (hasT) {\n            data[u] = data[u] + data[v]; \n        }\n        return\
    \ true;\n    }\n    size_t version() requires (undo_tag && !hasT) {\n        return\
    \ cache.size();\n    }\n    std::pair<size_t, size_t> version() requires (undo_tag\
    \ && hasT) {\n        return std::make_pair(cache.size(), data_cache.size());\n\
    \    }\n    void undo(auto req_version) requires (undo_tag) {\n        while (version()\
    \ != req_version) {\n            if constexpr (!hasT) {\n                *cache.back().first\
    \ = cache.back().second;\n                cache.pop_back();\n            }\n \
    \           else {\n                if (cache.size() > req_version.first) {\n\
    \                    *cache.back().first = cache.back().second;\n            \
    \        cache.pop_back();\n                }\n                else {\n      \
    \              *data_cache.back().first = data_cache.back().second;\n        \
    \            data_cache.pop_back();\n                }\n            }\n      \
    \  }\n    }\n    auto& getdata(int u) requires (hasT) {\n        return data[leader(u)];\n\
    \    }\n    void data_transform(int u, auto func) requires (hasT) {\n        auto\
    \ &cur = getdata(u);\n        if constexpr (undo_tag)\n            data_cache.emplace_back(&cur,\
    \ cur);\n        func(cur);\n    }\n    std::vector<std::vector<int>> groups()\
    \ {\n        std::vector<std::vector<int>> result(n);\n        for (int i = 0;\
    \ i < n; ++i)\n            result[leader(i)].push_back(i);\n        result.erase(remove_if(result.begin(),\
    \ result.end(), [](auto &g) { return g.empty(); }), result.end());\n        return\
    \ result;\n    }\n};\n#line 7 \"test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, m;\n    std::cin >> n >> m;\n    UndirectedGraph<> G(n);\n    while (m--)\
    \ {\n        int u, v;\n        std::cin >> u >> v;\n        G.add_edge(u, v);\n\
    \    }\n    auto parent = complement_bfs(G);\n    DisjointSet djs(n);\n    for\
    \ (int i = 0; i < n; ++i)\n        djs.merge(parent[i], i);\n    auto groups =\
    \ djs.groups();\n    std::cout << groups.size() << \"\\n\";\n    for (auto &v\
    \ : groups) {\n        std::cout << v.size();\n        for (int i : v) std::cout\
    \ << \" \" << i;\n        std::cout << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/connected_components_of_complement_graph\"\
    \n#include \"assumption.hpp\"\n\n#include \"Graph/base.hpp\"\n#include \"Graph/complement_bfs.hpp\"\
    \n#include \"DataStructure/DisjointSet.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n, m;\n    std::cin >> n >> m;\n    UndirectedGraph<>\
    \ G(n);\n    while (m--) {\n        int u, v;\n        std::cin >> u >> v;\n \
    \       G.add_edge(u, v);\n    }\n    auto parent = complement_bfs(G);\n    DisjointSet\
    \ djs(n);\n    for (int i = 0; i < n; ++i)\n        djs.merge(parent[i], i);\n\
    \    auto groups = djs.groups();\n    std::cout << groups.size() << \"\\n\";\n\
    \    for (auto &v : groups) {\n        std::cout << v.size();\n        for (int\
    \ i : v) std::cout << \" \" << i;\n        std::cout << \"\\n\";\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Graph/base.hpp
  - Graph/complement_bfs.hpp
  - DataStructure/DisjointSet.hpp
  isVerificationFile: true
  path: test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp
  requiredBy: []
  timestamp: '2026-06-28 13:32:45+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp
- /verify/test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp.html
title: test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp
---
