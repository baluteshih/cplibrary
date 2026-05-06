---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/shortest_path.test.cpp
    title: test/1_library_checker/graph/shortest_path.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Graph/Dijkstra.hpp\"\n\n#line 2 \"Graph/base.hpp\"\n\ntemplate<bool\
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
    \ Vertex>::Graph;\n};\n#line 4 \"Graph/Dijkstra.hpp\"\n\ntemplate<class T>\nclass\
    \ Dijkstra : public Graph<true, T> { // 0-base, O(mlogn)\n    using super = Graph<true,\
    \ T>;\npublic:\n    std::vector<int> parent; // parent[source] = source\n    std::vector<int>\
    \ parent_edge; // parent_edge[source] = -1 \n    std::vector<int> has_path;\n\
    \    std::vector<T> dis;\n    Dijkstra(int n): super(n), parent(n), parent_edge(n),\
    \ has_path(n), dis(n) {}\n    void solve(int source) {\n        std::ranges::fill(dis,\
    \ std::numeric_limits<T>::max());\n        std::ranges::fill(has_path, 0);\n \
    \       std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>,\
    \ std::greater<std::pair<T, int>>> pq;\n        auto relax = [&](int u, T w, int\
    \ f, int fedge) {\n            if (dis[u] > w) {\n                dis[u] = w;\n\
    \                parent[u] = f;\n                parent_edge[u] = fedge;\n   \
    \             pq.emplace(w, u);\n            }\n        };\n        relax(source,\
    \ 0, source, -1);\n        while (!pq.empty()) {\n            auto [w, u] = pq.top();\n\
    \            pq.pop();\n            if (dis[u] != w) continue;\n            has_path[u]\
    \ = true;\n            for (auto [v, e] : this->G[u])\n                relax(v,\
    \ dis[u] + this->edges[e].weight, u, e);\n        }\n    }\n    std::vector<int>\
    \ path(int target, bool vertex = true) {\n        assert(has_path[target]);\n\
    \        std::vector<int> res;\n        if (vertex) res.push_back(target);\n \
    \       for (int x = target; parent[x] != x; x = parent[x]) {\n            if\
    \ (vertex) res.push_back(parent[x]);\n            else res.push_back(parent_edge[x]);\n\
    \        }\n        std::ranges::reverse(res);\n        return res;\n    }\n};\n"
  code: "#pragma once\n\n#include \"Graph/base.hpp\"\n\ntemplate<class T>\nclass Dijkstra\
    \ : public Graph<true, T> { // 0-base, O(mlogn)\n    using super = Graph<true,\
    \ T>;\npublic:\n    std::vector<int> parent; // parent[source] = source\n    std::vector<int>\
    \ parent_edge; // parent_edge[source] = -1 \n    std::vector<int> has_path;\n\
    \    std::vector<T> dis;\n    Dijkstra(int n): super(n), parent(n), parent_edge(n),\
    \ has_path(n), dis(n) {}\n    void solve(int source) {\n        std::ranges::fill(dis,\
    \ std::numeric_limits<T>::max());\n        std::ranges::fill(has_path, 0);\n \
    \       std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>,\
    \ std::greater<std::pair<T, int>>> pq;\n        auto relax = [&](int u, T w, int\
    \ f, int fedge) {\n            if (dis[u] > w) {\n                dis[u] = w;\n\
    \                parent[u] = f;\n                parent_edge[u] = fedge;\n   \
    \             pq.emplace(w, u);\n            }\n        };\n        relax(source,\
    \ 0, source, -1);\n        while (!pq.empty()) {\n            auto [w, u] = pq.top();\n\
    \            pq.pop();\n            if (dis[u] != w) continue;\n            has_path[u]\
    \ = true;\n            for (auto [v, e] : this->G[u])\n                relax(v,\
    \ dis[u] + this->edges[e].weight, u, e);\n        }\n    }\n    std::vector<int>\
    \ path(int target, bool vertex = true) {\n        assert(has_path[target]);\n\
    \        std::vector<int> res;\n        if (vertex) res.push_back(target);\n \
    \       for (int x = target; parent[x] != x; x = parent[x]) {\n            if\
    \ (vertex) res.push_back(parent[x]);\n            else res.push_back(parent_edge[x]);\n\
    \        }\n        std::ranges::reverse(res);\n        return res;\n    }\n};\n"
  dependsOn:
  - Graph/base.hpp
  isVerificationFile: false
  path: Graph/Dijkstra.hpp
  requiredBy: []
  timestamp: '2026-05-06 14:22:55+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/graph/shortest_path.test.cpp
documentation_of: Graph/Dijkstra.hpp
layout: document
redirect_from:
- /library/Graph/Dijkstra.hpp
- /library/Graph/Dijkstra.hpp.html
title: Graph/Dijkstra.hpp
---
