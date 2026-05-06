---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Graph/SCC.hpp
    title: Graph/SCC.hpp
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/other/two_sat.test.cpp
    title: test/1_library_checker/other/two_sat.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Misc/2sat.hpp\"\n\n#line 2 \"Graph/SCC.hpp\"\n\n#line 2\
    \ \"Graph/base.hpp\"\n\ntemplate<bool directed = true, typename Edge = void, typename\
    \ Vertex = void>\nclass Graph {\npublic:\n    static constexpr bool hasEdgeWeight\
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
    \ Vertex>::Graph;\n};\n#line 4 \"Graph/SCC.hpp\"\n\ntemplate<typename Edge = void,\
    \ typename Vertex = void>\nstruct SCC : public Graph<true, Edge, Vertex>  { //\
    \ 0-base\n    using super = Graph<true, Edge, Vertex>;\n    int dft, nscc;\n \
    \   std::vector<int> low, dfn, bln, instack, stk;\n    void dfs(int u) {\n   \
    \     low[u] = dfn[u] = ++dft;\n        instack[u] = 1, stk.push_back(u);\n  \
    \      for (auto [v, eid] : this->G[u])\n            if (!dfn[v])\n          \
    \      dfs(v), low[u] = std::min(low[u], low[v]);\n            else if (instack[v]\
    \ && dfn[v] < dfn[u])\n                low[u] = std::min(low[u], dfn[v]);\n  \
    \      if (low[u] == dfn[u]) {\n            for (; stk.back() != u; stk.pop_back())\n\
    \                bln[stk.back()] = nscc, instack[stk.back()] = 0;\n          \
    \  instack[u] = 0, bln[u] = nscc++, stk.pop_back();\n        }\n    }\n    SCC(int\
    \ n): super(n), dft(), nscc(), low(n), dfn(n), bln(n), instack(n) {}\n    void\
    \ solve() {\n        for (int i = 0; i < this->n(); ++i)\n            if (!dfn[i])\
    \ dfs(i);\n    }\n    std::vector<std::vector<int>> components() {\n        std::vector<std::vector<int>>\
    \ res(nscc);\n        for (int i = 0; i < this->n(); ++i)\n            res[bln[i]].push_back(i);\n\
    \        std::ranges::reverse(res);\n        return res;\n    }\n}; // scc_id(i):\
    \ bln[i]\n#line 4 \"Misc/2sat.hpp\"\n\nstruct SAT { // 0-base\n    int n;\n  \
    \  std::vector<bool> istrue;\n    SCC<> scc;\n    SAT(int _n): n(_n), istrue(n\
    \ + n), scc(n + n) {}\n    int rv(int a) {\n        return a >= n ? a - n : a\
    \ + n;\n    }\n    void add_clause(int a, int b) {\n        scc.add_edge(rv(a),\
    \ b), scc.add_edge(rv(b), a);\n    }\n    bool solve() {\n        scc.solve();\n\
    \        for (int i = 0; i < n; ++i) {\n            if (scc.bln[i] == scc.bln[i\
    \ + n]) return false;\n            istrue[i] = scc.bln[i] < scc.bln[i + n];\n\
    \            istrue[i + n] = !istrue[i];\n        }\n        return true;\n  \
    \  }\n};\n"
  code: "#pragma once\n\n#include \"Graph/SCC.hpp\"\n\nstruct SAT { // 0-base\n  \
    \  int n;\n    std::vector<bool> istrue;\n    SCC<> scc;\n    SAT(int _n): n(_n),\
    \ istrue(n + n), scc(n + n) {}\n    int rv(int a) {\n        return a >= n ? a\
    \ - n : a + n;\n    }\n    void add_clause(int a, int b) {\n        scc.add_edge(rv(a),\
    \ b), scc.add_edge(rv(b), a);\n    }\n    bool solve() {\n        scc.solve();\n\
    \        for (int i = 0; i < n; ++i) {\n            if (scc.bln[i] == scc.bln[i\
    \ + n]) return false;\n            istrue[i] = scc.bln[i] < scc.bln[i + n];\n\
    \            istrue[i + n] = !istrue[i];\n        }\n        return true;\n  \
    \  }\n};\n"
  dependsOn:
  - Graph/SCC.hpp
  - Graph/base.hpp
  isVerificationFile: false
  path: Misc/2sat.hpp
  requiredBy: []
  timestamp: '2026-05-06 14:22:55+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/other/two_sat.test.cpp
documentation_of: Misc/2sat.hpp
layout: document
redirect_from:
- /library/Misc/2sat.hpp
- /library/Misc/2sat.hpp.html
title: Misc/2sat.hpp
---
