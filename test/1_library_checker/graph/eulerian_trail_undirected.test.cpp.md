---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/eulerian_trail.hpp
    title: Graph/eulerian_trail.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/eulerian_trail_undirected
    links:
    - https://judge.yosupo.jp/problem/eulerian_trail_undirected
  bundledCode: "#line 1 \"test/1_library_checker/graph/eulerian_trail_undirected.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/eulerian_trail_undirected\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/graph/eulerian_trail_undirected.test.cpp\"\n\n\
    #line 2 \"Graph/eulerian_trail.hpp\"\n\n#line 2 \"Graph/base.hpp\"\n\ntemplate<bool\
    \ directed = true, typename Edge = void, typename Vertex = void>\nclass Graph\
    \ {\npublic:\n    static constexpr bool is_directed = directed;\n    static constexpr\
    \ bool hasEdgeWeight = !std::is_same_v<Edge, void>;\n    static constexpr bool\
    \ hasVertexWeight = !std::is_same_v<Vertex, void>;\n    using edge_value_type\
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
    \            return res;\n        }\n        friend std::ostream& operator<<(std::ostream&\
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
    \    }\n    std::vector<int> in_degree() const {\n        std::vector<int> res(n());\n\
    \        for (auto &e : edges) {\n            if constexpr (!is_directed) ++res[e.from];\n\
    \            ++res[e.to];\n        }\n        return res;\n    }\n    virtual\
    \ std::vector<int> out_degree() const {\n        std::vector<int> res(n());\n\
    \        for (auto &e : edges) {\n            if constexpr (!is_directed) ++res[e.to];\n\
    \            ++res[e.from];\n        }\n        return res;\n    }\n    std::vector<std::pair<int,\
    \ int>>& operator[](int idx) {\n        return G[idx];\n    }\n    const std::vector<std::pair<int,\
    \ int>>& operator[](int idx) const {\n        return G[idx];\n    }\n    Graph\
    \ reversed() const {\n        Graph res(n());\n        for (auto &e : edges)\n\
    \            res.add_edge(e.reversed());\n        if constexpr (hasVertexWeight)\
    \ res.set_vertex_weight(weight);\n        return res;\n    }\n    std::pair<std::vector<int>,\
    \ std::vector<int>> cycle() {\n        std::vector<int> vis(this->n());\n    \
    \    std::vector<int> res_v, res_e;\n        int cyc_end = -1;\n        auto dfs\
    \ = [&](auto self, int u, int f) -> int {\n            vis[u] = 1;\n         \
    \   for (auto [v, eid] : G[u]) {\n                if (eid == f || vis[v] == 2)\
    \ continue;\n                if (vis[v] == 1) {\n                    res_v.push_back(u);\n\
    \                    res_e.push_back(eid);\n                    cyc_end = v;\n\
    \                    return 1;\n                }\n                int rt = self(self,\
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
    \ Graph induced(const std::vector<int> &subset) const {\n        std::vector<int>\
    \ idx(n(), -1);\n        for (int cnt = 0; int i : subset) idx[i] = cnt++;\n \
    \       Graph res(subset.size());\n        for (auto e : edges) {\n          \
    \  e.from = idx[e.from], e.to = idx[e.to];\n            if (e.to == -1 || e.from\
    \ == -1) continue;\n            res.add_edge(e);\n        }\n        return res;\n\
    \    }\n};\n\ntemplate<typename Edge = void, typename Vertex = void>\nclass UndirectedGraph\
    \ : public Graph<false, Edge, Vertex> {\npublic:\n    using Graph<false, Edge,\
    \ Vertex>::Graph;\n};\n#line 4 \"Graph/eulerian_trail.hpp\"\n\ntemplate<bool circuits\
    \ = false, bool remove_isolate_vertices = true, typename graph = Graph<true, void,\
    \ void>>\nstd::pair<std::vector<int>, std::vector<int>> eulerian_trail(const graph\
    \ &G) {\n    int s = -1, t = -1;\n    auto in_degree = G.in_degree();\n    if\
    \ constexpr (G.is_directed) {\n        auto out_degree = G.out_degree();\n   \
    \     for (int i = 0; i < G.n(); ++i)\n            if (in_degree[i] != out_degree[i])\
    \ {\n                if (in_degree[i] + 1 == out_degree[i]) {\n              \
    \      if (s == -1) s = i;\n                    else return {};\n            \
    \    }\n                else if (in_degree[i] == out_degree[i] + 1) {\n      \
    \              if (t == -1) t = i;\n                    else return {};\n    \
    \            }\n                else return {};\n            }\n    }\n    else\
    \ {\n        for (int i = 0; i < G.n(); ++i)\n            if (in_degree[i] % 2\
    \ != 0) {\n                if (s == -1) s = i;\n                else if (t ==\
    \ -1) t = i;\n                else return {};\n            }\n    }\n    if (int(s\
    \ == -1) ^ int(t == -1)) return {};\n    if constexpr (circuits) if (s != -1)\
    \ return {};\n    std::vector<int> vis(G.n()), vis_edge(G.m()), cur(G.n()), res_v,\
    \ res_e;\n    if (s == -1) {\n        s = std::ranges::find_if(in_degree, [&](int\
    \ d) { return d > 0; }) - in_degree.begin();\n        if (s == G.n()) s = 0;\n\
    \        t = s;\n    }\n    if constexpr (remove_isolate_vertices)\n        for\
    \ (int i = 0; i < G.n(); ++i)\n            if (in_degree[i] == 0 && i != s)\n\
    \                vis[i] = 1;\n    auto dfs = [&](auto self, int u, int f) -> void\
    \ {\n        vis[u] = 1;\n        if (f != -1) vis_edge[f] = 1;\n        for (int\
    \ &i = cur[u]; i < int(G[u].size());) {\n            auto [v, eid] = G[u][i++];\n\
    \            if (!vis_edge[eid]) self(self, v, eid); \n        }\n        res_v.push_back(u);\n\
    \        if (f != -1) res_e.push_back(f);\n    };\n    dfs(dfs, s, -1);\n    if\
    \ (std::ranges::find(vis, 0) != vis.end() || std::ranges::find(vis_edge, 0) !=\
    \ vis_edge.end())\n        return {};\n    if constexpr (G.is_directed) std::ranges::reverse(res_v),\
    \ std::ranges::reverse(res_e);\n    return {res_v, res_e};\n}\n#line 5 \"test/1_library_checker/graph/eulerian_trail_undirected.test.cpp\"\
    \n\nvoid solve() {\n    int n, m;\n    std::cin >> n >> m;\n    UndirectedGraph<>\
    \ G(n);\n    while (m--) {\n        int u, v;\n        std::cin >> u >> v;\n \
    \       G.add_edge(u, v);\n    }\n    auto [vertices, edges] = eulerian_trail(G);\n\
    \    if (vertices.empty()) std::cout << \"No\\n\";\n    else {\n        std::cout\
    \ << \"Yes\\n\";\n        for (int i = 0; i < int(vertices.size()); ++i)\n   \
    \         std::cout << vertices[i] << \" \\n\"[i + 1 == int(vertices.size())];\n\
    \        for (int i = 0; i < int(edges.size()); ++i)\n            std::cout <<\
    \ edges[i] << \" \\n\"[i + 1 == int(edges.size())];\n    }\n}\n\nint main() {\n\
    \    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int t;\n    std::cin\
    \ >> t;\n    while (t--) {\n        solve();\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/eulerian_trail_undirected\"\
    \n#include \"assumption.hpp\"\n\n#include \"Graph/eulerian_trail.hpp\"\n\nvoid\
    \ solve() {\n    int n, m;\n    std::cin >> n >> m;\n    UndirectedGraph<> G(n);\n\
    \    while (m--) {\n        int u, v;\n        std::cin >> u >> v;\n        G.add_edge(u,\
    \ v);\n    }\n    auto [vertices, edges] = eulerian_trail(G);\n    if (vertices.empty())\
    \ std::cout << \"No\\n\";\n    else {\n        std::cout << \"Yes\\n\";\n    \
    \    for (int i = 0; i < int(vertices.size()); ++i)\n            std::cout <<\
    \ vertices[i] << \" \\n\"[i + 1 == int(vertices.size())];\n        for (int i\
    \ = 0; i < int(edges.size()); ++i)\n            std::cout << edges[i] << \" \\\
    n\"[i + 1 == int(edges.size())];\n    }\n}\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int t;\n    std::cin >> t;\n    while (t--) {\n      \
    \  solve();\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Graph/eulerian_trail.hpp
  - Graph/base.hpp
  isVerificationFile: true
  path: test/1_library_checker/graph/eulerian_trail_undirected.test.cpp
  requiredBy: []
  timestamp: '2026-06-30 20:37:16+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/graph/eulerian_trail_undirected.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/graph/eulerian_trail_undirected.test.cpp
- /verify/test/1_library_checker/graph/eulerian_trail_undirected.test.cpp.html
title: test/1_library_checker/graph/eulerian_trail_undirected.test.cpp
---
