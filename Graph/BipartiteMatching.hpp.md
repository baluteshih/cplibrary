---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Graph/BipartiteGraph.hpp
    title: Graph/BipartiteGraph.hpp
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/bipartitematching.test.cpp
    title: test/1_library_checker/graph/bipartitematching.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Graph/BipartiteMatching.hpp\"\n\n#line 2 \"Graph/BipartiteGraph.hpp\"\
    \n\n#line 2 \"Graph/base.hpp\"\n\ntemplate<bool directed = true, typename Edge\
    \ = void, typename Vertex = void>\nclass Graph {\npublic:\n    static constexpr\
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
    #line 4 \"Graph/BipartiteGraph.hpp\"\n\ntemplate<typename Edge = void, typename\
    \ Vertex = void>\nclass BipartiteGraph : public Graph<true, Edge, Vertex> {\n\
    \    using super = Graph<true, Edge, Vertex>;\nprotected:\n    int rsize;\npublic:\n\
    \    BipartiteGraph(int _l, int _r) : super(_l), rsize(_r) {} \n    int l() const\
    \ { return this->G.size(); }\n    int r() const { return rsize; }\n    std::vector<int>\
    \ out_degree() override {\n        std::vector<int> res(rsize);\n        for (auto\
    \ &e : this->edges)\n            ++res[e.from];\n        return res;\n    }\n\
    \    BipartiteGraph reversed() {\n        Graph res(rsize, this->n());\n     \
    \   for (auto &e : this->edges) {\n            if constexpr (super::hasEdgeWeight)\
    \ res.add_edge(e.to, e.from, e.weight);\n            else res.add_edge(e.to, e.from);\n\
    \        }\n        if constexpr (super::hasVertexWeight) res.set_vertex_weight(this->weight);\n\
    \        return res;\n    }\n    /*\n    return a pair of (color, BipartiteGraph),\n\
    \    where u on the left of the BipartiteGraph iff color[u] == 0\n    the new\
    \ numbering of u will be the count of the number of same color nodes on its left\n\
    \    */\n    static std::optional<std::pair<std::vector<int>, BipartiteGraph>>\
    \ to_bipartite(Graph<false, Edge, Vertex> &graph) {\n        std::vector<int>\
    \ color(graph.n(), -1), numbering(graph.n());\n        auto dfs = [&](auto self,\
    \ int u, int c) -> bool {\n            color[u] = c;\n            for (auto [v,\
    \ eid] : graph[u])\n                if (color[v] == -1 && !self(self, v, c ^ 1))\n\
    \                    return false;\n                else if (color[v] == color[u])\n\
    \                    return false;\n            return true;\n        };\n   \
    \     int cnt[2] = {};\n        for (int i = 0; i < graph.n(); ++i) {\n      \
    \      if (color[i] == -1 && !dfs(dfs, i, 0))\n                return std::nullopt;\
    \ \n            numbering[i] = cnt[color[i]]++;\n        }\n        BipartiteGraph\
    \ res(cnt[0], cnt[1]);\n        for (int i = 0; i < graph.m(); ++i) {\n      \
    \      const auto &e = graph.edge(i);\n            int u = e.from;\n         \
    \   int v = e.to;\n            if (color[u] == 1) std::swap(u, v);\n         \
    \   u = numbering[u], v = numbering[v];\n            if constexpr (super::hasEdgeWeight)\
    \ res.add_edge(u, v, e.weight);\n            else res.add_edge(u, v);\n      \
    \  }\n        if constexpr (super::hasVertexWeight) res.set_vertex_weight(graph.vertex_weight());\n\
    \        return res;\n    }\n};\n#line 4 \"Graph/BipartiteMatching.hpp\"\n\n/*\n\
    match_left, match_right\n-1 implies no match\n*/\nstruct BipartiteMatching : public\
    \ BipartiteGraph<void, void>  { // 0-base\n    using super = BipartiteGraph<void,\
    \ void>;\n    std::vector<int> match_right, match_left;\n    std::vector<int>\
    \ dis, cur;\n    BipartiteMatching(int l, int r) : super(l, r), match_right(l),\
    \ match_left(r), dis(l + 1), cur(l) {} \n    bool dfs(int u) {\n        for (int\
    \ &i = cur[u]; i < ssize((*this)[u]); ++i) {\n            int e = (*this)[u][i].first;\n\
    \            if (match_left[e] == this->n() || (dis[match_left[e]] == dis[u] +\
    \ 1 && dfs(match_left[e])))\n                return match_right[match_left[e]\
    \ = u] = e, 1;\n        }\n        return dis[u] = -1, 0;\n    }\n    bool bfs()\
    \ {\n        std::queue<int> q;\n        std::ranges::fill(dis, -1);\n       \
    \ for (int i = 0; i < this->n(); ++i)\n            if (!~match_right[i])\n   \
    \             q.push(i), dis[i] = 0;\n        while (!q.empty()) {\n         \
    \   int u = q.front();\n            q.pop();\n            if (u == this->n())\
    \ continue;\n            for (auto [e, eid] : (*this)[u])\n                if\
    \ (!~dis[match_left[e]])\n                    q.push(match_left[e]), dis[match_left[e]]\
    \ = dis[u] + 1;\n        }\n        return dis[this->n()] != -1;\n    }\n    int\
    \ matching() {\n        int res = 0;\n        std::ranges::fill(match_right, -1);\n\
    \        std::ranges::fill(match_left, this->n());\n        while (bfs()) {\n\
    \            std::ranges::fill(cur, 0);\n            for (int i = 0; i < this->n();\
    \ ++i)\n                res += (!~match_right[i] && dfs(i));\n        }\n    \
    \    std::ranges::replace(match_left, this->n(), -1);\n        return res;\n \
    \   }\n};\n"
  code: "#pragma once\n\n#include \"Graph/BipartiteGraph.hpp\"\n\n/*\nmatch_left,\
    \ match_right\n-1 implies no match\n*/\nstruct BipartiteMatching : public BipartiteGraph<void,\
    \ void>  { // 0-base\n    using super = BipartiteGraph<void, void>;\n    std::vector<int>\
    \ match_right, match_left;\n    std::vector<int> dis, cur;\n    BipartiteMatching(int\
    \ l, int r) : super(l, r), match_right(l), match_left(r), dis(l + 1), cur(l) {}\
    \ \n    bool dfs(int u) {\n        for (int &i = cur[u]; i < ssize((*this)[u]);\
    \ ++i) {\n            int e = (*this)[u][i].first;\n            if (match_left[e]\
    \ == this->n() || (dis[match_left[e]] == dis[u] + 1 && dfs(match_left[e])))\n\
    \                return match_right[match_left[e] = u] = e, 1;\n        }\n  \
    \      return dis[u] = -1, 0;\n    }\n    bool bfs() {\n        std::queue<int>\
    \ q;\n        std::ranges::fill(dis, -1);\n        for (int i = 0; i < this->n();\
    \ ++i)\n            if (!~match_right[i])\n                q.push(i), dis[i] =\
    \ 0;\n        while (!q.empty()) {\n            int u = q.front();\n         \
    \   q.pop();\n            if (u == this->n()) continue;\n            for (auto\
    \ [e, eid] : (*this)[u])\n                if (!~dis[match_left[e]])\n        \
    \            q.push(match_left[e]), dis[match_left[e]] = dis[u] + 1;\n       \
    \ }\n        return dis[this->n()] != -1;\n    }\n    int matching() {\n     \
    \   int res = 0;\n        std::ranges::fill(match_right, -1);\n        std::ranges::fill(match_left,\
    \ this->n());\n        while (bfs()) {\n            std::ranges::fill(cur, 0);\n\
    \            for (int i = 0; i < this->n(); ++i)\n                res += (!~match_right[i]\
    \ && dfs(i));\n        }\n        std::ranges::replace(match_left, this->n(),\
    \ -1);\n        return res;\n    }\n};\n"
  dependsOn:
  - Graph/BipartiteGraph.hpp
  - Graph/base.hpp
  isVerificationFile: false
  path: Graph/BipartiteMatching.hpp
  requiredBy: []
  timestamp: '2026-05-19 02:16:25+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/graph/bipartitematching.test.cpp
documentation_of: Graph/BipartiteMatching.hpp
layout: document
redirect_from:
- /library/Graph/BipartiteMatching.hpp
- /library/Graph/BipartiteMatching.hpp.html
title: Graph/BipartiteMatching.hpp
---
