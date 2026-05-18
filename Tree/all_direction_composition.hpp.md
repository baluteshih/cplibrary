---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/SwagQueue.hpp
    title: DataStructure/SwagQueue.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/UnifiedWeight.hpp
    title: Graph/UnifiedWeight.hpp
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/Tree.hpp
    title: Tree/Tree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/tree_path_composite_sum.test.cpp
    title: test/1_library_checker/tree/tree_path_composite_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Tree/all_direction_composition.hpp\"\n\n#line 2 \"Tree/Tree.hpp\"\
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
    \                res.add_edge(e.reversed());\n        return res;\n    }\n};\n\
    \ntemplate<typename Edge = void, typename Vertex = void>\nclass UndirectedGraph\
    \ : public Graph<false, Edge, Vertex> {\npublic:\n    using Graph<false, Edge,\
    \ Vertex>::Graph;\n};\n#line 2 \"Graph/UnifiedWeight.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate<typename T, typename Fallback>\nusing ReplaceVoid = std::conditional_t<std::same_as<T,\
    \ void>, Fallback, T>;\n\ntemplate <typename A, typename B>\nconcept ValidAddableState\
    \ =\n    (!std::same_as<A, void> || !std::same_as<B, void>) ||\n    requires(const\
    \ ReplaceVoid<A, B>& a, \n             const ReplaceVoid<B, A>& b) {\n       \
    \ a + b;\n    };\n\ntemplate <typename A, typename B>\nconcept ValidSubtractableState\
    \ = \n    (!std::same_as<A, void> || !std::same_as<B, void>) ||\n    requires(const\
    \ ReplaceVoid<A, B>& a, \n             const ReplaceVoid<B, A>& b) {\n       \
    \ a - b;\n    };\n#line 4 \"Graph/UnifiedWeight.hpp\"\n\ntemplate <typename Edge,\
    \ typename Vertex>\nstruct UnifiedWeight {\n    using type = std::conditional_t<!std::is_same_v<Vertex,\
    \ void>, Vertex, Edge>;\n};\n\ntemplate <typename Edge, typename Vertex>\nusing\
    \ UnifiedWeight_t = typename UnifiedWeight<Edge, Vertex>::type;\n#line 5 \"Tree/Tree.hpp\"\
    \n\ntemplate<typename Edge = void, typename Vertex = void>\nclass Tree : public\
    \ Graph<false, Edge, Vertex> {\npublic:\n    using super = Graph<false, Edge,\
    \ Vertex>;\n    using super::hasEdgeWeight;\n    using super::hasVertexWeight;\n\
    \    using WeightType = UnifiedWeight_t<Edge, Vertex>;\n    int current_root;\n\
    \    std::vector<int> pa, dfs_in, dfs_out;\n    std::vector<int> preorder, postorder;\n\
    \    Tree(int n): super(n), current_root(-1) {}\n    Tree(const super &graph,\
    \ const std::vector<int> &edge_index): super(graph.n()), current_root(-1) {\n\
    \        assert(int(edge_index.size()) + 1 == this->n());\n        for (int eid\
    \ : edge_index)\n            this->add_edge(graph.edge(eid));\n    }\n    void\
    \ traverse(int root = 0) {\n        current_root = root;\n        std::vector<int>(this->n()).swap(pa);\n\
    \        std::vector<int>(this->n()).swap(dfs_in);\n        std::vector<int>(this->n()).swap(dfs_out);\n\
    \        preorder.clear(), preorder.reserve(this->n());\n        postorder.clear(),\
    \ postorder.reserve(this->n());\n        int dft = -1;\n        auto dfs = [&](auto&\
    \ self, int u, int f) -> void {\n            pa[u] = f;\n            dfs_in[u]\
    \ = ++dft;\n            preorder.push_back(u);\n            for (auto [v, eid]\
    \ : this->G[u])\n                if (eid != f)\n                    self(self,\
    \ v, eid);\n            dfs_out[u] = dft;\n            postorder.push_back(u);\n\
    \        };\n        dfs(dfs, root, -1);\n    }\n    bool ancestor(int u, int\
    \ v) const {\n        return dfs_in[u] <= dfs_in[v] && dfs_out[v] <= dfs_out[u];\n\
    \    }\n    void run_order(const std::vector<int> &order, const auto &func) {\n\
    \        for (int i : order)\n            func(i);\n    }\n    void predfs(const\
    \ auto &func) {\n        run_order(preorder, func);\n    }\n    void postdfs(const\
    \ auto &func) {\n        run_order(postorder, func);\n    }\n    int parent(int\
    \ u) const {\n        if (pa[u] == -1) return u;\n        return this->opposite(u,\
    \ pa[u]);\n    }\n    int parent_eid(int u) const {\n        return pa[u];\n \
    \   }\n    super::edge_v& parent_edge(int u) {\n        assert(pa[u] != -1);\n\
    \        return this->edge(pa[u]);\n    }\n    super::edge_v parent_edge(int u)\
    \ const {\n        assert(pa[u] != -1);\n        return this->edge(pa[u]);\n \
    \   }\n    std::vector<int> parents(int root = -1) {\n        if (current_root\
    \ == -1 || (root != -1 && current_root != root)) {\n            assert(root !=\
    \ -1);\n            traverse(root);\n        }\n        std::vector<int> res(this->n());\n\
    \        for (int i = 0; i < this->n(); ++i)\n            res[i] = parent(i);\n\
    \        return res;\n    }\n    std::vector<int> depth(int root = -1) {\n   \
    \     if (current_root == -1 || (root != -1 && current_root != root)) {\n    \
    \        assert(root != -1);\n            traverse(root);\n        }\n       \
    \ std::vector<int> res(this->n(), -1);\n        predfs([&](int u) {\n        \
    \    res[u] = res[parent(u)] + 1;\n        });\n        return res;\n    }\n \
    \   auto distance_edge(int root = -1) requires (hasEdgeWeight) {\n        if (current_root\
    \ == -1 || (root != -1 && current_root != root)) {\n            assert(root !=\
    \ -1);\n            traverse(root);\n        }\n        std::vector<Edge> res(this->n());\n\
    \        predfs([&](int u) {\n            if (parent_eid(u) != -1)\n         \
    \       res[u] = res[parent(u)] + parent_edge(u).weight;\n        });\n      \
    \  return res;\n    }\n    auto weighted_distance(int root = -1) requires (ValidAddableState<Edge,\
    \ Vertex>) {\n        if (current_root == -1 || (root != -1 && current_root !=\
    \ root)) {\n            assert(root != -1);\n            traverse(root);\n   \
    \     }\n        std::vector<WeightType> res(this->n());\n        predfs([&](int\
    \ u) {\n            res[u] = res[parent(u)];\n            if constexpr (hasEdgeWeight)\
    \ if (u != root)\n                res[u] = res[u] + parent_edge(u).weight;\n \
    \           if constexpr (hasVertexWeight)\n                res[u] = res[u] +\
    \ this->weight[u];\n        });\n        return res;\n    }\n    std::vector<int>\
    \ subtree_size(int root = -1) {\n        if (current_root == -1 || (root != -1\
    \ && current_root != root)) {\n            assert(root != -1);\n            traverse(root);\n\
    \        }\n        std::vector<int> res(this->n(), 1);\n        predfs([&](int\
    \ u) {\n            for (auto [v, eid] : this->G[u])\n                if (eid\
    \ != parent_eid(u))\n                    res[u] += res[v];\n        });\n    \
    \    return res;\n    }\n    std::vector<int> path(int u, int v, int root = -1)\
    \ {\n        if (current_root == -1 || (root != -1 && current_root != root)) {\n\
    \            if (root == -1) root = 0;\n            traverse(root);\n        }\n\
    \        std::vector<int> lft, rgt;\n        while (!ancestor(v, u)) {\n     \
    \       rgt.push_back(v);\n            v = parent(v);\n        }\n        while\
    \ (u != v) {\n            lft.push_back(u);\n            u = parent(u);\n    \
    \    }\n        lft.push_back(u);\n        lft.insert(lft.end(), rgt.rbegin(),\
    \ rgt.rend());\n        return lft; \n    }\n    unsigned long long shift_hash_value(unsigned\
    \ long long z) {\n        z ^= z >> 12; z ^= z << 25; z ^= z >> 27;\n        return\
    \ z * 2685821657736338717LL;\n    }\n    std::vector<unsigned long long> hash_values(int\
    \ root = -1, unsigned long long seed = 7122) {\n        if (current_root == -1\
    \ || (root != -1 && current_root != root)) {\n            if (root == -1) root\
    \ = 0;\n            traverse(root);\n        }\n        std::vector<unsigned long\
    \ long> res(this->n());\n        postdfs([&](int u) {\n            res[u] = seed;\n\
    \            for (auto [v, eid] : this->G[u])\n                if (eid != parent_eid(u))\n\
    \                    res[u] += res[v];\n            res[u] = shift_hash_value(res[u]);\n\
    \        });\n        return res;\n    }\n};\n#line 2 \"DataStructure/SwagQueue.hpp\"\
    \n\ntemplate<typename T>\nclass SwagQueue {\n    int sz = 0;\n    std::vector<T>\
    \ data, cum_l;\n    T cum_r;\npublic:\n    SwagQueue() : cum_l(1, T()), cum_r()\
    \ {}\n    int size() { return sz; }\n    void push(T x) {\n        ++sz;\n   \
    \     cum_r = cum_r + x;\n        data.push_back(x);\n    }\n    void pop() {\n\
    \        --sz;\n        cum_l.pop_back();\n        if (cum_l.empty()) {\n    \
    \        cum_l.push_back(T());\n            cum_r = T();\n            while (int(data.size())\
    \ > 1) {\n                cum_l.push_back(data.back() + cum_l.back());\n     \
    \           data.pop_back();\n            }\n            data.pop_back();\n  \
    \      }\n    }\n    T lprod() { return cum_l.back(); }\n    T rprod() { return\
    \ cum_r; }\n    T prod() { return lprod() + rprod(); }\n};\n#line 5 \"Tree/all_direction_composition.hpp\"\
    \n\ntemplate<typename Edge, typename Vertex>\nrequires (ValidAddableState<Vertex,\
    \ Vertex> && ValidAddableState<Vertex, Edge>)\nstd::vector<UnifiedWeight_t<Edge,\
    \ Vertex>> all_direction_composition(Tree<Edge, Vertex> &tree) {\n    static constexpr\
    \ bool hasEdgeWeight = Tree<Edge, Vertex>::hasEdgeWeight;\n    static constexpr\
    \ bool hasVertexWeight =  Tree<Edge, Vertex>::hasVertexWeight;\n    std::vector<UnifiedWeight_t<Edge,\
    \ Vertex>> dp(tree.n()), res(tree.n()), recv(tree.n());\n    if (tree.current_root\
    \ == -1) tree.traverse(); \n    tree.postdfs([&](int u) {\n        for (auto [v,\
    \ eid] : tree[u])\n            if (v != tree.parent(u)) {\n                if\
    \ constexpr (hasEdgeWeight) dp[v] = dp[v] + tree.edge(eid).weight;\n         \
    \       dp[u] = dp[u] + dp[v];\n            }\n        if constexpr (hasVertexWeight)\
    \ dp[u] = dp[u] + tree.vertex(u);\n    });\n    std::vector<SwagQueue<UnifiedWeight_t<Edge,\
    \ Vertex>>> swag(tree.n());\n    tree.predfs([&](int u) {\n        if (tree.parent(u)\
    \ != u) {\n            swag[tree.parent(u)].pop();\n            recv[u] = swag[tree.parent(u)].prod();\n\
    \            if constexpr (hasVertexWeight) recv[u] = recv[u] + tree.vertex(tree.parent(u));\n\
    \            if constexpr (hasEdgeWeight) recv[u] = recv[u] + tree.parent_edge(u).weight;\n\
    \            swag[tree.parent(u)].push(dp[u]);\n        }\n        for (auto [v,\
    \ eid] : tree[u])\n            if (v != tree.parent(u))\n                swag[u].push(dp[v]);\n\
    \        swag[u].push(recv[u]);\n        res[u] = swag[u].prod();\n        if\
    \ constexpr (hasVertexWeight) res[u] = res[u] + tree.vertex(u); \n    });\n  \
    \  return res;\n}\n"
  code: "#pragma once\n\n#include \"Tree/Tree.hpp\"\n#include \"DataStructure/SwagQueue.hpp\"\
    \n\ntemplate<typename Edge, typename Vertex>\nrequires (ValidAddableState<Vertex,\
    \ Vertex> && ValidAddableState<Vertex, Edge>)\nstd::vector<UnifiedWeight_t<Edge,\
    \ Vertex>> all_direction_composition(Tree<Edge, Vertex> &tree) {\n    static constexpr\
    \ bool hasEdgeWeight = Tree<Edge, Vertex>::hasEdgeWeight;\n    static constexpr\
    \ bool hasVertexWeight =  Tree<Edge, Vertex>::hasVertexWeight;\n    std::vector<UnifiedWeight_t<Edge,\
    \ Vertex>> dp(tree.n()), res(tree.n()), recv(tree.n());\n    if (tree.current_root\
    \ == -1) tree.traverse(); \n    tree.postdfs([&](int u) {\n        for (auto [v,\
    \ eid] : tree[u])\n            if (v != tree.parent(u)) {\n                if\
    \ constexpr (hasEdgeWeight) dp[v] = dp[v] + tree.edge(eid).weight;\n         \
    \       dp[u] = dp[u] + dp[v];\n            }\n        if constexpr (hasVertexWeight)\
    \ dp[u] = dp[u] + tree.vertex(u);\n    });\n    std::vector<SwagQueue<UnifiedWeight_t<Edge,\
    \ Vertex>>> swag(tree.n());\n    tree.predfs([&](int u) {\n        if (tree.parent(u)\
    \ != u) {\n            swag[tree.parent(u)].pop();\n            recv[u] = swag[tree.parent(u)].prod();\n\
    \            if constexpr (hasVertexWeight) recv[u] = recv[u] + tree.vertex(tree.parent(u));\n\
    \            if constexpr (hasEdgeWeight) recv[u] = recv[u] + tree.parent_edge(u).weight;\n\
    \            swag[tree.parent(u)].push(dp[u]);\n        }\n        for (auto [v,\
    \ eid] : tree[u])\n            if (v != tree.parent(u))\n                swag[u].push(dp[v]);\n\
    \        swag[u].push(recv[u]);\n        res[u] = swag[u].prod();\n        if\
    \ constexpr (hasVertexWeight) res[u] = res[u] + tree.vertex(u); \n    });\n  \
    \  return res;\n}\n"
  dependsOn:
  - Tree/Tree.hpp
  - Graph/base.hpp
  - Graph/UnifiedWeight.hpp
  - Algebra/ValidOperation.hpp
  - DataStructure/SwagQueue.hpp
  isVerificationFile: false
  path: Tree/all_direction_composition.hpp
  requiredBy: []
  timestamp: '2026-05-18 13:56:28+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/tree/tree_path_composite_sum.test.cpp
documentation_of: Tree/all_direction_composition.hpp
layout: document
redirect_from:
- /library/Tree/all_direction_composition.hpp
- /library/Tree/all_direction_composition.hpp.html
title: Tree/all_direction_composition.hpp
---
