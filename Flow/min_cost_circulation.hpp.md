---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Flow/min_cost_max_flow.hpp
    title: Flow/min_cost_max_flow.hpp
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Flow/bounded_cost_circulation.hpp
    title: Flow/bounded_cost_circulation.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/min_cost_b_flow.test.cpp
    title: test/1_library_checker/graph/min_cost_b_flow.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/submission/194239
  bundledCode: "#line 2 \"Flow/min_cost_circulation.hpp\"\n\n#line 2 \"Graph/base.hpp\"\
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
    \ Vertex>::Graph;\n};\n#line 2 \"Flow/min_cost_max_flow.hpp\"\n\n#line 4 \"Flow/min_cost_max_flow.hpp\"\
    \n\ntemplate<typename T, typename C = T>\nstruct CostFlowWeight {\n    T cap;\n\
    \    C cost;\n    T flow;\n    CostFlowWeight() : cap(0), cost(0), flow(0) {}\n\
    \    CostFlowWeight(T c, C w, T f = 0) : cap(c), cost(w), flow(f) {}\n    friend\
    \ ostream& operator<<(ostream& os, const CostFlowWeight &v) {\n        os << \"\
    [\" << v.cap << \", \" << v.cost << \", \" << v.flow << \"]\";\n        return\
    \ os;\n    }\n};\n\ntemplate<typename T, typename C = T>\nclass min_cost_max_flow\
    \ : public Graph<true, CostFlowWeight<T, C>, void> { // 0-base\npublic:\n    using\
    \ super = Graph<true, CostFlowWeight<T, C>, void>;\n    std::vector<int> past;\n\
    \    std::vector<C> dis, pot;\n    std::vector<T> up;\n    template<bool bellmanford\
    \ = true>\n    bool shortest_path(int s, int t) {\n        std::vector<int> inq(this->n());\n\
    \        std::ranges::fill(dis, std::numeric_limits<C>::max());\n        std::conditional_t<bellmanford,\
    \ std::queue<int>, std::priority_queue<std::pair<C, int>, std::vector<std::pair<C,\
    \ int>>, std::greater<std::pair<C, int>>>> q;\n        auto relax = [&](int u,\
    \ C d, T cap, int eid) {\n            if (cap > 0 && dis[u] > d) {\n         \
    \       dis[u] = d, up[u] = cap, past[u] = eid;\n                if constexpr\
    \ (!bellmanford) q.emplace(dis[u], u);\n                else if (!inq[u]) inq[u]\
    \ = 1, q.push(u);\n            }\n        };\n        relax(s, 0, std::numeric_limits<T>::max(),\
    \ -1);\n        while (!q.empty()) {\n            C d;\n            int u;\n \
    \           if constexpr (bellmanford) u = q.front();\n            else std::tie(d,\
    \ u) = q.top();\n            q.pop();\n            if constexpr (bellmanford)\
    \ inq[u] = 0;\n            else if (dis[u] != d) continue;\n            for (auto\
    \ [v, eid] : this->G[u]) {\n                auto &w = this->edges[eid].weight;\n\
    \                C d2 = dis[u] + w.cost + pot[u] - pot[v];\n                relax(v,\
    \ d2, std::min(up[u], w.cap - w.flow), eid);\n            }\n        }\n     \
    \   return dis[t] != std::numeric_limits<C>::max();\n    }\n    min_cost_max_flow(int\
    \ _n) : super(_n), past(_n), dis(_n), pot(_n), up(_n) {} \n    template<bool bellmanford\
    \ = true, bool neg = true>\n    std::pair<T, C> solve(int s, int t) {\n      \
    \  T flow = 0;\n        C cost = 0;\n        if constexpr (neg) shortest_path<true>(s,\
    \ t), dis = pot;\n        for (; shortest_path<bellmanford>(s, t); dis = pot)\
    \ {\n            for (int i = 0; i < this->n(); ++i) dis[i] += pot[i] - pot[s];\n\
    \            flow += up[t], cost += dis[t] * up[t];\n            for (int i =\
    \ t; past[i] != -1; i = this->edges[past[i]].from) {\n                this->edges[past[i]].weight.flow\
    \ += up[t];\n                this->edges[past[i] ^ 1].weight.flow -= up[t];\n\
    \            }\n        }\n        return std::make_pair(flow, cost);\n    }\n\
    \    void add_edge(int a, int b, T cap, C cost) {\n        super::add_edge(a,\
    \ b, CostFlowWeight(cap, cost, T(0)));\n        super::add_edge(b, a, CostFlowWeight(T(0),\
    \ -cost, T(0)));\n    }\n};\n#line 5 \"Flow/min_cost_circulation.hpp\"\n\n// source:\
    \ https://judge.yosupo.jp/submission/194239\ntemplate<typename T, typename C =\
    \ T>\nclass min_cost_circulation : public Graph<true, CostFlowWeight<T, C>, void>\
    \ { // 0-base\npublic:\n    using super = Graph<true, CostFlowWeight<T, C>, void>;\n\
    \    std::vector<int> vis, fa, fae;\n    int visc;\n    std::vector<C> pi;\n \
    \   min_cost_circulation(int _n) : super(_n), vis(_n), visc(0), pi(_n) {} \n \
    \   C phi(int x) {\n        if (fa[x] == -1) return 0;\n        if (vis[x] ==\
    \ visc) return pi[x];\n        vis[x] = visc;\n        return pi[x] = phi(fa[x])\
    \ - this->edges[fae[x]].weight.cost;\n    }\n    int lca(int u, int v) {\n   \
    \     for (; u != -1 || v != -1; swap(u, v))\n            if (u != -1) {\n   \
    \             if (vis[u] == visc) return u;\n                vis[u] = visc;\n\
    \                u = fa[u];\n            }\n        return -1;\n    }\n    void\
    \ pushflow(int x) {\n        int v = this->edges[x].from, u = this->edges[x].to;\n\
    \        ++visc;\n        if (int w = lca(u, v); w == -1) {\n            while\
    \ (v != -1)\n                swap(x ^= 1, fae[v]), swap(u, fa[v]), swap(u, v);\n\
    \        }\n        else {\n            int z = u, dir = 0;\n            T f =\
    \ this->edges[x].weight.flow;\n            std::vector<int> cyc = {x};\n     \
    \       for (int d : {0, 1})\n                for (int i = (d ? u : v); i != w;\
    \ i = fa[i]) {\n                    cyc.push_back(fae[i] ^ d);\n             \
    \       if (f > this->edges[fae[i] ^ d].weight.flow) {\n                     \
    \   f = this->edges[fae[i] ^ d].weight.flow;\n                        z = i, dir\
    \ = d;\n                    }\n                }\n            for (int i : cyc)\
    \ {\n                this->edges[i].weight.flow -= f;\n                this->edges[i\
    \ ^ 1].weight.flow += f;\n            }\n            if (dir) x ^= 1, swap(u,\
    \ v);\n            while (u != z)\n                swap(x ^= 1, fae[v]), swap(u,\
    \ fa[v]), swap(u, v);\n        }\n    }\n    void dfs(int u) {\n        vis[u]\
    \ = visc;\n        for (auto [v, eid] : this->G[u])\n            if (vis[v] !=\
    \ visc && this->edges[eid].weight.flow)\n                fa[v] = u, fae[v] = eid,\
    \ dfs(v);\n    }\n    void solve() {\n        fa.assign(this->n(), -1), fae.assign(this->n(),\
    \ -1);\n        ++visc, dfs(0);\n        for (int fail = 0; fail < int(this->edges.size());)\n\
    \            for (int i = 0; i < int(this->edges.size()); ++i)\n             \
    \   if (this->edges[i].weight.flow && this->edges[i].weight.cost < phi(this->edges[i].from)\
    \ - phi(this->edges[i].to))\n                    fail = 0, pushflow(i), ++visc;\n\
    \                else\n                    ++fail;\n    }\n    void add_edge(int\
    \ a, int b, T cap, C cost) {\n        super::add_edge(a, b, CostFlowWeight<T,\
    \ C>(cap, cost, cap));\n        super::add_edge(b, a, CostFlowWeight<T, C>(T(0),\
    \ -cost, T(0)));\n    }\n    C get_cost() {\n        C res = 0;\n        for (int\
    \ i = 0; i < int(this->edges.size()); i += 2)\n            res += this->edges[i].weight.cost\
    \ * (this->edges[i].weight.cap - this->edges[i].weight.flow);\n        return\
    \ res;\n    }\n    std::vector<T> get_cap() {\n        std::vector<T> res;\n \
    \       for (int i = 0; i < int(this->edges.size()); i += 2)\n            res.push_back(this->edges[i].weight.cap\
    \ - this->edges[i].weight.flow);\n        return res;\n    }\n    std::vector<C>\
    \ get_potential() {\n        std::vector<C> d(this->n());\n        std::vector<int>\
    \ inq(this->n(), true);\n        std::queue<int> q;\n        for (int i = 0; i\
    \ < this->n(); ++i)\n            q.push(i);\n        while (!q.empty()) {\n  \
    \          int u = q.front();\n            q.pop();\n            inq[u] = false;\n\
    \            for (auto [v, eid] : this->G[u])\n                if (this->edges[eid].weight.flow\
    \ && d[v] > d[u] + this->edges[eid].weight.cost) {\n                    d[v] =\
    \ d[u] + this->edges[eid].weight.cost;\n                    if (!inq[v]) {\n \
    \                       inq[v] = true;\n                        q.push(v);\n \
    \                   }\n                }\n        }\n        return d;\n    }\n\
    };\n"
  code: "#pragma once\n\n#include \"Graph/base.hpp\"\n#include \"Flow/min_cost_max_flow.hpp\"\
    \n\n// source: https://judge.yosupo.jp/submission/194239\ntemplate<typename T,\
    \ typename C = T>\nclass min_cost_circulation : public Graph<true, CostFlowWeight<T,\
    \ C>, void> { // 0-base\npublic:\n    using super = Graph<true, CostFlowWeight<T,\
    \ C>, void>;\n    std::vector<int> vis, fa, fae;\n    int visc;\n    std::vector<C>\
    \ pi;\n    min_cost_circulation(int _n) : super(_n), vis(_n), visc(0), pi(_n)\
    \ {} \n    C phi(int x) {\n        if (fa[x] == -1) return 0;\n        if (vis[x]\
    \ == visc) return pi[x];\n        vis[x] = visc;\n        return pi[x] = phi(fa[x])\
    \ - this->edges[fae[x]].weight.cost;\n    }\n    int lca(int u, int v) {\n   \
    \     for (; u != -1 || v != -1; swap(u, v))\n            if (u != -1) {\n   \
    \             if (vis[u] == visc) return u;\n                vis[u] = visc;\n\
    \                u = fa[u];\n            }\n        return -1;\n    }\n    void\
    \ pushflow(int x) {\n        int v = this->edges[x].from, u = this->edges[x].to;\n\
    \        ++visc;\n        if (int w = lca(u, v); w == -1) {\n            while\
    \ (v != -1)\n                swap(x ^= 1, fae[v]), swap(u, fa[v]), swap(u, v);\n\
    \        }\n        else {\n            int z = u, dir = 0;\n            T f =\
    \ this->edges[x].weight.flow;\n            std::vector<int> cyc = {x};\n     \
    \       for (int d : {0, 1})\n                for (int i = (d ? u : v); i != w;\
    \ i = fa[i]) {\n                    cyc.push_back(fae[i] ^ d);\n             \
    \       if (f > this->edges[fae[i] ^ d].weight.flow) {\n                     \
    \   f = this->edges[fae[i] ^ d].weight.flow;\n                        z = i, dir\
    \ = d;\n                    }\n                }\n            for (int i : cyc)\
    \ {\n                this->edges[i].weight.flow -= f;\n                this->edges[i\
    \ ^ 1].weight.flow += f;\n            }\n            if (dir) x ^= 1, swap(u,\
    \ v);\n            while (u != z)\n                swap(x ^= 1, fae[v]), swap(u,\
    \ fa[v]), swap(u, v);\n        }\n    }\n    void dfs(int u) {\n        vis[u]\
    \ = visc;\n        for (auto [v, eid] : this->G[u])\n            if (vis[v] !=\
    \ visc && this->edges[eid].weight.flow)\n                fa[v] = u, fae[v] = eid,\
    \ dfs(v);\n    }\n    void solve() {\n        fa.assign(this->n(), -1), fae.assign(this->n(),\
    \ -1);\n        ++visc, dfs(0);\n        for (int fail = 0; fail < int(this->edges.size());)\n\
    \            for (int i = 0; i < int(this->edges.size()); ++i)\n             \
    \   if (this->edges[i].weight.flow && this->edges[i].weight.cost < phi(this->edges[i].from)\
    \ - phi(this->edges[i].to))\n                    fail = 0, pushflow(i), ++visc;\n\
    \                else\n                    ++fail;\n    }\n    void add_edge(int\
    \ a, int b, T cap, C cost) {\n        super::add_edge(a, b, CostFlowWeight<T,\
    \ C>(cap, cost, cap));\n        super::add_edge(b, a, CostFlowWeight<T, C>(T(0),\
    \ -cost, T(0)));\n    }\n    C get_cost() {\n        C res = 0;\n        for (int\
    \ i = 0; i < int(this->edges.size()); i += 2)\n            res += this->edges[i].weight.cost\
    \ * (this->edges[i].weight.cap - this->edges[i].weight.flow);\n        return\
    \ res;\n    }\n    std::vector<T> get_cap() {\n        std::vector<T> res;\n \
    \       for (int i = 0; i < int(this->edges.size()); i += 2)\n            res.push_back(this->edges[i].weight.cap\
    \ - this->edges[i].weight.flow);\n        return res;\n    }\n    std::vector<C>\
    \ get_potential() {\n        std::vector<C> d(this->n());\n        std::vector<int>\
    \ inq(this->n(), true);\n        std::queue<int> q;\n        for (int i = 0; i\
    \ < this->n(); ++i)\n            q.push(i);\n        while (!q.empty()) {\n  \
    \          int u = q.front();\n            q.pop();\n            inq[u] = false;\n\
    \            for (auto [v, eid] : this->G[u])\n                if (this->edges[eid].weight.flow\
    \ && d[v] > d[u] + this->edges[eid].weight.cost) {\n                    d[v] =\
    \ d[u] + this->edges[eid].weight.cost;\n                    if (!inq[v]) {\n \
    \                       inq[v] = true;\n                        q.push(v);\n \
    \                   }\n                }\n        }\n        return d;\n    }\n\
    };\n"
  dependsOn:
  - Graph/base.hpp
  - Flow/min_cost_max_flow.hpp
  isVerificationFile: false
  path: Flow/min_cost_circulation.hpp
  requiredBy:
  - Flow/bounded_cost_circulation.hpp
  timestamp: '2026-05-06 14:22:55+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/graph/min_cost_b_flow.test.cpp
documentation_of: Flow/min_cost_circulation.hpp
layout: document
redirect_from:
- /library/Flow/min_cost_circulation.hpp
- /library/Flow/min_cost_circulation.hpp.html
title: Flow/min_cost_circulation.hpp
---
