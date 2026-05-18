---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Flow/min_cost_circulation_old.hpp\"\n\n#line 2 \"Graph/base.hpp\"\
    \n\ntemplate<bool directed = true, typename Edge = void, typename Vertex = void>\n\
    class Graph {\npublic:\n    static constexpr bool hasEdgeWeight = !std::is_same_v<Edge,\
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
    #line 4 \"Flow/min_cost_circulation_old.hpp\"\n\ntemplate<typename T, typename\
    \ C = T>\nstruct CostCirculationFlowWeight {\n    T fcap;\n    C cost;\n    T\
    \ cap, flow;\n    CostCirculationFlowWeight() : cap(0), fcap(0), cost(0), flow(0)\
    \ {}\n    CostCirculationFlowWeight(T c, C w, T cc = 0, T f = 0) : fcap(c), cost(w),\
    \ cap(cc), flow(f) {}\n    friend ostream& operator<<(ostream& os, const CostCirculationFlowWeight\
    \ &v) {\n        os << \"[\" << v.fcap << \", \" << v.cost << \", \" << v.cap\
    \ << \", \" << v.flow << \"]\";\n        return os;\n    }\n};\n\n// O(VE * ElogC)\n\
    template<typename T, typename C = T>\nclass min_cost_circulation : public Graph<true,\
    \ CostCirculationFlowWeight<T, C>, void> { // 0-base\npublic:\n    using super\
    \ = Graph<true, CostCirculationFlowWeight<T, C>, void>;\n    std::vector<int>\
    \ past;\n    std::vector<C> dis, pot;\n    void BellmanFord(int s) {\n       \
    \ std::vector<int> inq(this->n());\n        std::ranges::fill(dis, std::numeric_limits<C>::max());\n\
    \        std::queue<int> q;\n        auto relax = [&](int u, C d, int eid) {\n\
    \            if (dis[u] > d) {\n                dis[u] = d, past[u] = eid;\n \
    \               if (!inq[u]) inq[u] = 1, q.push(u);\n            }\n        };\n\
    \        relax(s, 0, -1);\n        while (!q.empty()) {\n            int u = q.front();\n\
    \            q.pop(), inq[u] = 0;\n            for (auto [v, eid] : this->G[u])\
    \ {\n                auto &w = this->edges[eid].weight;\n                if (w.cap\
    \ > w.flow)\n                    relax(v, dis[u] + w.cost, eid);\n           \
    \ }\n        }\n    }\n    void try_edge(int eid) {\n        auto &cur = this->edges[eid];\n\
    \        auto &w = cur.weight;\n        if (w.cap > w.flow) return ++w.cap, void();\n\
    \        BellmanFord(cur.to);\n        if (dis[cur.from] + w.cost < 0) {\n   \
    \         ++w.flow, --this->edges[eid ^ 1].weight.flow;\n            for (int\
    \ i = cur.from; past[i] != -1; i = this->edges[past[i]].from) {\n            \
    \    ++this->edges[past[i]].weight.flow;\n                --this->edges[past[i]\
    \ ^ 1].weight.flow;\n            }\n        }\n        ++w.cap;\n    }\n    min_cost_circulation(int\
    \ _n) : super(_n), past(_n), dis(_n), pot(_n) {} \n    void solve(int mxlg) {\n\
    \        for (int b = mxlg; b >= 0; --b) {\n            for (int i = 0; i < this->n();\
    \ ++i)\n                for (auto [v, eid] : this->G[i]) {\n                 \
    \   this->edges[eid].weight.cap *= 2;\n                    this->edges[eid].weight.flow\
    \ *= 2;\n                }\n            for (int i = 0; i < this->n(); ++i)\n\
    \                for (auto [v, eid] : this->G[i]) {\n                    if (this->edges[eid].weight.fcap\
    \ >> b & 1)\n                        try_edge(eid);\n                }\n     \
    \   }\n    }\n    void add_edge(int a, int b, T cap, C cost) {\n        super::add_edge(a,\
    \ b, CostCirculationFlowWeight(cap, cost, T(0)));\n        super::add_edge(b,\
    \ a, CostCirculationFlowWeight(T(0), -cost, T(0)));\n    }\n    C get_cost() {\n\
    \        C res = 0;\n        for (int i = 0; i < this->n(); ++i) \n          \
    \  for (auto [v, eid] : this->G[i])\n                if (this->edges[eid].weight.flow\
    \ > 0)\n                    res += this->edges[eid].weight.cost * this->edges[eid].weight.flow;\n\
    \        return res;\n    }\n};\n"
  code: "#pragma once\n\n#include \"Graph/base.hpp\"\n\ntemplate<typename T, typename\
    \ C = T>\nstruct CostCirculationFlowWeight {\n    T fcap;\n    C cost;\n    T\
    \ cap, flow;\n    CostCirculationFlowWeight() : cap(0), fcap(0), cost(0), flow(0)\
    \ {}\n    CostCirculationFlowWeight(T c, C w, T cc = 0, T f = 0) : fcap(c), cost(w),\
    \ cap(cc), flow(f) {}\n    friend ostream& operator<<(ostream& os, const CostCirculationFlowWeight\
    \ &v) {\n        os << \"[\" << v.fcap << \", \" << v.cost << \", \" << v.cap\
    \ << \", \" << v.flow << \"]\";\n        return os;\n    }\n};\n\n// O(VE * ElogC)\n\
    template<typename T, typename C = T>\nclass min_cost_circulation : public Graph<true,\
    \ CostCirculationFlowWeight<T, C>, void> { // 0-base\npublic:\n    using super\
    \ = Graph<true, CostCirculationFlowWeight<T, C>, void>;\n    std::vector<int>\
    \ past;\n    std::vector<C> dis, pot;\n    void BellmanFord(int s) {\n       \
    \ std::vector<int> inq(this->n());\n        std::ranges::fill(dis, std::numeric_limits<C>::max());\n\
    \        std::queue<int> q;\n        auto relax = [&](int u, C d, int eid) {\n\
    \            if (dis[u] > d) {\n                dis[u] = d, past[u] = eid;\n \
    \               if (!inq[u]) inq[u] = 1, q.push(u);\n            }\n        };\n\
    \        relax(s, 0, -1);\n        while (!q.empty()) {\n            int u = q.front();\n\
    \            q.pop(), inq[u] = 0;\n            for (auto [v, eid] : this->G[u])\
    \ {\n                auto &w = this->edges[eid].weight;\n                if (w.cap\
    \ > w.flow)\n                    relax(v, dis[u] + w.cost, eid);\n           \
    \ }\n        }\n    }\n    void try_edge(int eid) {\n        auto &cur = this->edges[eid];\n\
    \        auto &w = cur.weight;\n        if (w.cap > w.flow) return ++w.cap, void();\n\
    \        BellmanFord(cur.to);\n        if (dis[cur.from] + w.cost < 0) {\n   \
    \         ++w.flow, --this->edges[eid ^ 1].weight.flow;\n            for (int\
    \ i = cur.from; past[i] != -1; i = this->edges[past[i]].from) {\n            \
    \    ++this->edges[past[i]].weight.flow;\n                --this->edges[past[i]\
    \ ^ 1].weight.flow;\n            }\n        }\n        ++w.cap;\n    }\n    min_cost_circulation(int\
    \ _n) : super(_n), past(_n), dis(_n), pot(_n) {} \n    void solve(int mxlg) {\n\
    \        for (int b = mxlg; b >= 0; --b) {\n            for (int i = 0; i < this->n();\
    \ ++i)\n                for (auto [v, eid] : this->G[i]) {\n                 \
    \   this->edges[eid].weight.cap *= 2;\n                    this->edges[eid].weight.flow\
    \ *= 2;\n                }\n            for (int i = 0; i < this->n(); ++i)\n\
    \                for (auto [v, eid] : this->G[i]) {\n                    if (this->edges[eid].weight.fcap\
    \ >> b & 1)\n                        try_edge(eid);\n                }\n     \
    \   }\n    }\n    void add_edge(int a, int b, T cap, C cost) {\n        super::add_edge(a,\
    \ b, CostCirculationFlowWeight(cap, cost, T(0)));\n        super::add_edge(b,\
    \ a, CostCirculationFlowWeight(T(0), -cost, T(0)));\n    }\n    C get_cost() {\n\
    \        C res = 0;\n        for (int i = 0; i < this->n(); ++i) \n          \
    \  for (auto [v, eid] : this->G[i])\n                if (this->edges[eid].weight.flow\
    \ > 0)\n                    res += this->edges[eid].weight.cost * this->edges[eid].weight.flow;\n\
    \        return res;\n    }\n};\n"
  dependsOn:
  - Graph/base.hpp
  isVerificationFile: false
  path: Flow/min_cost_circulation_old.hpp
  requiredBy: []
  timestamp: '2026-05-19 02:16:25+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Flow/min_cost_circulation_old.hpp
layout: document
redirect_from:
- /library/Flow/min_cost_circulation_old.hpp
- /library/Flow/min_cost_circulation_old.hpp.html
title: Flow/min_cost_circulation_old.hpp
---
