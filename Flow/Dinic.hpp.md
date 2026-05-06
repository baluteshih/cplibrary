---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  _extendedRequiredBy:
  - icon: ':x:'
    path: Flow/bounded_flow.hpp
    title: Flow/bounded_flow.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/4_codeforces/106033E.test.cpp
    title: test/4_codeforces/106033E.test.cpp
  - icon: ':x:'
    path: test/7_loj/bounded_flow.test.cpp
    title: test/7_loj/bounded_flow.test.cpp
  - icon: ':x:'
    path: test/7_loj/max_bounded_flow.test.cpp
    title: test/7_loj/max_bounded_flow.test.cpp
  - icon: ':x:'
    path: test/7_loj/maxflow.test.cpp
    title: test/7_loj/maxflow.test.cpp
  - icon: ':x:'
    path: test/7_loj/min_bounded_flow.test.cpp
    title: test/7_loj/min_bounded_flow.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Flow/Dinic.hpp\"\n\n#line 2 \"Graph/base.hpp\"\n\ntemplate<bool\
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
    \ Vertex>::Graph;\n};\n#line 4 \"Flow/Dinic.hpp\"\n\ntemplate<typename T>\nstruct\
    \ FlowWeight {\n    T cap, flow;\n    FlowWeight() : cap(0), flow(0) {}\n    FlowWeight(T\
    \ c, T f = 0) : cap(c), flow(f) {}\n    friend ostream& operator<<(ostream& os,\
    \ const FlowWeight &v) {\n        os << \"[\" << v.cap << \", \" << v.flow <<\
    \ \"]\";\n        return os;\n    }\n};\n\ntemplate<class T>\nclass Dinic : public\
    \ Graph<true, FlowWeight<T>, void> { // 0-base\npublic:\n    using super = Graph<true,\
    \ FlowWeight<T>, void>;\n    std::vector<int> dis, cur;\n    T dfs(int u, T push_cap,\
    \ int t) {\n        if (u == t || push_cap == 0) return push_cap;\n        for\
    \ (int &i = cur[u]; i < std::ssize(this->G[u]); ++i) {\n            auto [v, eid]\
    \ = this->G[u][i];\n            auto &w = this->edges[eid].weight;\n         \
    \   if (dis[v] == dis[u] + 1 && w.cap > w.flow) {\n                T df = dfs(v,\
    \ std::min(w.cap - w.flow, push_cap), t);\n                if (df > T(0)) {\n\
    \                    w.flow += df;\n                    this->edges[eid ^ 1].weight.flow\
    \ -= df;\n                    return df;\n                }\n            }\n \
    \       }\n        dis[u] = -1;\n        return 0;\n    }\n    bool bfs(int s,\
    \ int t) {\n        std::ranges::fill(dis, -1);\n        std::queue<int> q;\n\
    \        q.push(s);\n        dis[s] = 0;\n        while (!q.empty()) {\n     \
    \       int u = q.front();\n            q.pop();\n            for (auto [v, eid]\
    \ : this->G[u]) {\n                auto &w = this->edges[eid].weight;\n      \
    \          if (dis[v] == -1 && w.cap > w.flow) {\n                    dis[v] =\
    \ dis[u] + 1;\n                    q.push(v);\n                }\n           \
    \ }\n        }\n        return dis[t] != -1;\n    }\n    Dinic(int _n) : super(_n),\
    \ dis(_n), cur(_n) {}\n    void add_edge(int u, int v, T cap) {\n        super::add_edge(u,\
    \ v, FlowWeight<T>(cap, 0));\n        super::add_edge(v, u, FlowWeight<T>(0, 0));\n\
    \    }\n    T maxflow(int s, int t) {\n        T flow = 0, df;\n        while\
    \ (bfs(s, t)) {\n            std::ranges::fill(cur, 0);\n            while ((df\
    \ = dfs(s, std::numeric_limits<T>::max(), t)) > 0)\n                flow += df;\n\
    \        }\n        return flow;\n    }\n    std::vector<std::pair<T, std::vector<int>>>\
    \ get_route(int s, int t) {\n        std::vector<std::pair<T, std::vector<int>>>\
    \ res;\n        auto backup_edges = this->edges; \n        for (auto &e : this->edges)\
    \ {\n            if (e.weight.cap > 0) e.weight.cap = e.weight.flow;\n       \
    \     e.weight.flow = 0;\n        }\n\n        std::vector<int> stk;\n       \
    \ auto route = [&](auto self, int u, T push_cap) -> T {\n            if (u ==\
    \ t || push_cap == 0) {\n                if (push_cap > 0) stk.push_back(u);\n\
    \                return push_cap;\n            }\n            for (int &i = cur[u];\
    \ i < std::ssize(this->G[u]); ++i) {\n                auto [v, eid] = this->G[u][i];\n\
    \                auto &w = this->edges[eid].weight;\n                if (dis[v]\
    \ == dis[u] + 1 && w.cap > w.flow) {\n                    T df = self(self, v,\
    \ std::min(w.cap - w.flow, push_cap));\n                    if (df > 0) {\n  \
    \                      w.flow += df;\n                        stk.push_back(u);\n\
    \                        return df;\n                    }\n                }\n\
    \            }\n            dis[u] = -1;\n            return 0;\n        };\n\n\
    \        while (bfs(s, t)) {\n            std::ranges::fill(cur, 0);\n       \
    \     T df;\n            while ((df = route(route, s, std::numeric_limits<T>::max()))\
    \ > 0) {\n                std::ranges::reverse(stk);\n                res.emplace_back(df,\
    \ stk);\n                stk.clear();\n            }\n        }\n        \n  \
    \      this->edges = std::move(backup_edges); \n        return res;\n    }\n \
    \   void reset() {\n        for (auto &e : this->edges) e.weight.flow = 0;\n \
    \   }\n    T get_flow(int s) {\n        T res = T();\n        for (auto [v, eid]\
    \ : this->G[s])\n            res += this->edges[eid].weight.flow;\n        return\
    \ res;\n    }\n};\n"
  code: "#pragma once\n\n#include \"Graph/base.hpp\"\n\ntemplate<typename T>\nstruct\
    \ FlowWeight {\n    T cap, flow;\n    FlowWeight() : cap(0), flow(0) {}\n    FlowWeight(T\
    \ c, T f = 0) : cap(c), flow(f) {}\n    friend ostream& operator<<(ostream& os,\
    \ const FlowWeight &v) {\n        os << \"[\" << v.cap << \", \" << v.flow <<\
    \ \"]\";\n        return os;\n    }\n};\n\ntemplate<class T>\nclass Dinic : public\
    \ Graph<true, FlowWeight<T>, void> { // 0-base\npublic:\n    using super = Graph<true,\
    \ FlowWeight<T>, void>;\n    std::vector<int> dis, cur;\n    T dfs(int u, T push_cap,\
    \ int t) {\n        if (u == t || push_cap == 0) return push_cap;\n        for\
    \ (int &i = cur[u]; i < std::ssize(this->G[u]); ++i) {\n            auto [v, eid]\
    \ = this->G[u][i];\n            auto &w = this->edges[eid].weight;\n         \
    \   if (dis[v] == dis[u] + 1 && w.cap > w.flow) {\n                T df = dfs(v,\
    \ std::min(w.cap - w.flow, push_cap), t);\n                if (df > T(0)) {\n\
    \                    w.flow += df;\n                    this->edges[eid ^ 1].weight.flow\
    \ -= df;\n                    return df;\n                }\n            }\n \
    \       }\n        dis[u] = -1;\n        return 0;\n    }\n    bool bfs(int s,\
    \ int t) {\n        std::ranges::fill(dis, -1);\n        std::queue<int> q;\n\
    \        q.push(s);\n        dis[s] = 0;\n        while (!q.empty()) {\n     \
    \       int u = q.front();\n            q.pop();\n            for (auto [v, eid]\
    \ : this->G[u]) {\n                auto &w = this->edges[eid].weight;\n      \
    \          if (dis[v] == -1 && w.cap > w.flow) {\n                    dis[v] =\
    \ dis[u] + 1;\n                    q.push(v);\n                }\n           \
    \ }\n        }\n        return dis[t] != -1;\n    }\n    Dinic(int _n) : super(_n),\
    \ dis(_n), cur(_n) {}\n    void add_edge(int u, int v, T cap) {\n        super::add_edge(u,\
    \ v, FlowWeight<T>(cap, 0));\n        super::add_edge(v, u, FlowWeight<T>(0, 0));\n\
    \    }\n    T maxflow(int s, int t) {\n        T flow = 0, df;\n        while\
    \ (bfs(s, t)) {\n            std::ranges::fill(cur, 0);\n            while ((df\
    \ = dfs(s, std::numeric_limits<T>::max(), t)) > 0)\n                flow += df;\n\
    \        }\n        return flow;\n    }\n    std::vector<std::pair<T, std::vector<int>>>\
    \ get_route(int s, int t) {\n        std::vector<std::pair<T, std::vector<int>>>\
    \ res;\n        auto backup_edges = this->edges; \n        for (auto &e : this->edges)\
    \ {\n            if (e.weight.cap > 0) e.weight.cap = e.weight.flow;\n       \
    \     e.weight.flow = 0;\n        }\n\n        std::vector<int> stk;\n       \
    \ auto route = [&](auto self, int u, T push_cap) -> T {\n            if (u ==\
    \ t || push_cap == 0) {\n                if (push_cap > 0) stk.push_back(u);\n\
    \                return push_cap;\n            }\n            for (int &i = cur[u];\
    \ i < std::ssize(this->G[u]); ++i) {\n                auto [v, eid] = this->G[u][i];\n\
    \                auto &w = this->edges[eid].weight;\n                if (dis[v]\
    \ == dis[u] + 1 && w.cap > w.flow) {\n                    T df = self(self, v,\
    \ std::min(w.cap - w.flow, push_cap));\n                    if (df > 0) {\n  \
    \                      w.flow += df;\n                        stk.push_back(u);\n\
    \                        return df;\n                    }\n                }\n\
    \            }\n            dis[u] = -1;\n            return 0;\n        };\n\n\
    \        while (bfs(s, t)) {\n            std::ranges::fill(cur, 0);\n       \
    \     T df;\n            while ((df = route(route, s, std::numeric_limits<T>::max()))\
    \ > 0) {\n                std::ranges::reverse(stk);\n                res.emplace_back(df,\
    \ stk);\n                stk.clear();\n            }\n        }\n        \n  \
    \      this->edges = std::move(backup_edges); \n        return res;\n    }\n \
    \   void reset() {\n        for (auto &e : this->edges) e.weight.flow = 0;\n \
    \   }\n    T get_flow(int s) {\n        T res = T();\n        for (auto [v, eid]\
    \ : this->G[s])\n            res += this->edges[eid].weight.flow;\n        return\
    \ res;\n    }\n};\n"
  dependsOn:
  - Graph/base.hpp
  isVerificationFile: false
  path: Flow/Dinic.hpp
  requiredBy:
  - Flow/bounded_flow.hpp
  timestamp: '2026-05-06 14:22:55+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/4_codeforces/106033E.test.cpp
  - test/7_loj/maxflow.test.cpp
  - test/7_loj/max_bounded_flow.test.cpp
  - test/7_loj/min_bounded_flow.test.cpp
  - test/7_loj/bounded_flow.test.cpp
documentation_of: Flow/Dinic.hpp
layout: document
redirect_from:
- /library/Flow/Dinic.hpp
- /library/Flow/Dinic.hpp.html
title: Flow/Dinic.hpp
---
