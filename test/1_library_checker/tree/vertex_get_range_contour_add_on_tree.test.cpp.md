---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/NullFunc.hpp
    title: Algebra/NullFunc.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/BIT.hpp
    title: Binary Indexed Tree (BIT)
  - icon: ':heavy_check_mark:'
    path: Graph/UnifiedWeight.hpp
    title: Graph/UnifiedWeight.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/CentroidDS/DistanceSolver.hpp
    title: Tree/CentroidDS/DistanceSolver.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/CentroidTree.hpp
    title: Tree/CentroidTree.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/Tree.hpp
    title: Tree/Tree.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/centroid_divide_and_conquer.hpp
    title: Tree/centroid_divide_and_conquer.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree
    links:
    - https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree
  bundledCode: "#line 1 \"test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp\"\
    \n\n#line 2 \"Tree/CentroidDS/DistanceSolver.hpp\"\n\n#line 2 \"Tree/CentroidTree.hpp\"\
    \n\n#line 2 \"Tree/Tree.hpp\"\n\n#line 2 \"Graph/base.hpp\"\n\ntemplate<bool directed\
    \ = true, typename Edge = void, typename Vertex = void>\nclass Graph {\npublic:\n\
    \    static constexpr bool hasEdgeWeight = !std::is_same_v<Edge, void>;\n    static\
    \ constexpr bool hasVertexWeight = !std::is_same_v<Vertex, void>;\n    using edge_value_type\
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
    #line 2 \"Graph/UnifiedWeight.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\n\
    \ntemplate<typename T, typename Fallback>\nusing ReplaceVoid = std::conditional_t<std::same_as<T,\
    \ void>, Fallback, T>;\n\ntemplate <typename A, typename B>\nconcept ValidAddableState\
    \ =\n    requires(const ReplaceVoid<A, B>& a, \n             const ReplaceVoid<B,\
    \ A>& b) {\n        a + b;\n    };\n\ntemplate <typename A, typename B>\nconcept\
    \ ValidSubtractableState = \n    requires(const ReplaceVoid<A, B>& a, \n     \
    \        const ReplaceVoid<B, A>& b) {\n        a - b;\n    };\n#line 4 \"Graph/UnifiedWeight.hpp\"\
    \n\ntemplate <typename Edge, typename Vertex>\nstruct UnifiedWeight {\n    using\
    \ type = std::conditional_t<!std::is_same_v<Vertex, void>, Vertex, Edge>;\n};\n\
    \ntemplate <typename Edge, typename Vertex>\nusing UnifiedWeight_t = typename\
    \ UnifiedWeight<Edge, Vertex>::type;\n#line 5 \"Tree/Tree.hpp\"\n\ntemplate<typename\
    \ Edge = void, typename Vertex = void>\nclass Tree : public Graph<false, Edge,\
    \ Vertex> {\npublic:\n    using super = Graph<false, Edge, Vertex>;\n    using\
    \ super::hasEdgeWeight;\n    using super::hasVertexWeight;\n    using WeightType\
    \ = UnifiedWeight_t<Edge, Vertex>;\n    int current_root;\n    std::vector<int>\
    \ pa, dfs_in, dfs_out;\n    std::vector<int> preorder, postorder;\n    Tree(int\
    \ n): super(n), current_root(-1) {}\n    Tree(const super &graph, const std::vector<int>\
    \ &edge_index): super(graph.n()), current_root(-1) {\n        assert(int(edge_index.size())\
    \ + 1 == this->n());\n        for (int eid : edge_index)\n            this->add_edge(graph.edge(eid));\n\
    \    }\n    void traverse(int root = 0) {\n        current_root = root;\n    \
    \    std::vector<int>(this->n()).swap(pa);\n        std::vector<int>(this->n()).swap(dfs_in);\n\
    \        std::vector<int>(this->n()).swap(dfs_out);\n        preorder.clear(),\
    \ preorder.reserve(this->n());\n        postorder.clear(), postorder.reserve(this->n());\n\
    \        int dft = -1;\n        auto dfs = [&](auto& self, int u, int f) -> void\
    \ {\n            pa[u] = f;\n            dfs_in[u] = ++dft;\n            preorder.push_back(u);\n\
    \            for (auto [v, eid] : this->G[u])\n                if (eid != f)\n\
    \                    self(self, v, eid);\n            dfs_out[u] = dft;\n    \
    \        postorder.push_back(u);\n        };\n        dfs(dfs, root, -1);\n  \
    \  }\n    bool ancestor(int u, int v) const {\n        return dfs_in[u] <= dfs_in[v]\
    \ && dfs_out[v] <= dfs_out[u];\n    }\n    void run_order(const std::vector<int>\
    \ &order, const auto &func) {\n        for (int i : order)\n            func(i);\n\
    \    }\n    void predfs(const auto &func) {\n        run_order(preorder, func);\n\
    \    }\n    void postdfs(const auto &func) {\n        run_order(postorder, func);\n\
    \    }\n    int parent(int u) const {\n        if (pa[u] == -1) return u;\n  \
    \      return this->opposite(u, pa[u]);\n    }\n    int parent_eid(int u) const\
    \ {\n        return pa[u];\n    }\n    super::edge_v& parent_edge(int u) {\n \
    \       assert(pa[u] != -1);\n        return this->edge(pa[u]);\n    }\n    super::edge_v\
    \ parent_edge(int u) const {\n        assert(pa[u] != -1);\n        return this->edge(pa[u]);\n\
    \    }\n    std::vector<int> parents(int root = -1) {\n        if (current_root\
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
    \        });\n        return res;\n    }\n};\n#line 2 \"Tree/centroid_divide_and_conquer.hpp\"\
    \n\n#line 2 \"Algebra/NullFunc.hpp\"\n\nstruct NullFunc {\n    constexpr void\
    \ operator()(auto&&...) const {}\n};\n#line 5 \"Tree/centroid_divide_and_conquer.hpp\"\
    \n\n/*\npre_func: void pre_func(int u, int f);\n    - u: current vertex, f: parent\n\
    \    - the center would be called at first with pre_func(c, -1);\nmerge_func:\
    \ void merge_func(int c, std::vector<std::vector<int>> groups);\n    - c: the\
    \ center, groups: subtrees with pre-order\npost_func: void post_func(int u, std::vector<int>\
    \ child);\n    - u: current vertex, child: child vertices\npost_merge_func: void\
    \ post_merge_func(int c, std::vector<int> cent_child);\n    - c: the center, cent_child:\
    \ c's center children \nreturn value: c_pa[u]: the centroid parent of u\n*/\n\n\
    template<typename _Tree, typename F_Pre = NullFunc, typename F_Merge = NullFunc,\
    \ typename F_Post = NullFunc, typename F_PMerge = NullFunc>\nstd::vector<int>\
    \ centroid_divide_and_conquer(_Tree &tree, F_Pre pre_func = NullFunc{}, F_Merge\
    \ merge_func = NullFunc{}, F_Post post_func = NullFunc{}, F_PMerge post_merge_func\
    \ = NullFunc{}) {\n    constexpr bool useMerge = !std::is_same_v<std::decay_t<decltype(merge_func)>,\
    \ NullFunc>;\n    constexpr bool usePre   = !std::is_same_v<std::decay_t<decltype(pre_func)>,\
    \ NullFunc>;\n    constexpr bool usePost  = !std::is_same_v<std::decay_t<decltype(post_func)>,\
    \ NullFunc>;\n    constexpr bool usePostMerge  = !std::is_same_v<std::decay_t<decltype(post_merge_func)>,\
    \ NullFunc>;\n    int n = tree.n();\n    std::vector<int> done(n), sz(n), res(n);\n\
    \    auto get_cent = [&](auto self, int u, int f, int &mx, int &c, int num) ->\
    \ void {\n        int mxsz = 0;\n        sz[u] = 1;\n        for (auto [v, eid]\
    \ : tree[u])\n            if (!done[v] && v != f) {\n                self(self,\
    \ v, u, mx, c, num);\n                sz[u] += sz[v];\n                mxsz =\
    \ std::max(mxsz, sz[v]);\n            }\n        if (mx > std::max(mxsz, num -\
    \ sz[u]))\n            mx = std::max(mxsz, num - sz[u]), c = u;\n    };\n    auto\
    \ dfs = [&](auto self, int u, int f, auto &g) -> void {\n        if constexpr\
    \ (useMerge) g.push_back(u);\n        if constexpr (usePre) pre_func(u, f);\n\
    \        std::conditional_t<usePost, std::vector<int>, typename _Tree::Empty>\
    \ child;\n        for (auto [v, eid] : tree[u])\n            if (!done[v] && v\
    \ != f) {\n                self(self, v, u, g);\n                if constexpr\
    \ (usePost) child.push_back(v);\n            }\n        if constexpr (usePost)\
    \ post_func(u, child);\n    };\n    auto cut = [&](auto self, int u, int num)\
    \ -> int {\n        int mx = n + 1, c = 0;\n        get_cent(get_cent, u, -1,\
    \ mx, c, num);\n        done[c] = 1;\n        std::conditional_t<useMerge, std::vector<std::vector<int>>,\
    \ typename _Tree::Empty> groups;\n        if constexpr (usePre) pre_func(c, -1);\n\
    \        std::conditional_t<usePost, std::vector<int>, typename _Tree::Empty>\
    \ child;\n        for (auto [v, eid] : tree[c])\n            if (!done[v]) {\n\
    \                if constexpr (useMerge) {\n                    groups.emplace_back();\n\
    \                    groups.back().reserve(sz[v] > sz[c] ? num - sz[c] : sz[v]);\n\
    \                    dfs(dfs, v, c, groups.back());\n                }\n     \
    \           else dfs(dfs, v, c, groups);\n                if constexpr (usePost)\
    \ child.push_back(v);\n            }\n        if constexpr (usePost) post_func(c,\
    \ child);\n        if constexpr (useMerge) merge_func(c, groups);\n        std::conditional_t<usePostMerge,\
    \ std::vector<int>, typename _Tree::Empty> cent_child;\n        for (auto [v,\
    \ eid] : tree[c])\n            if (!done[v]) {\n                int ch;\n    \
    \            if (sz[v] > sz[c])\n                    ch = self(self, v, num -\
    \ sz[c]);\n                else\n                    ch = self(self, v, sz[v]);\n\
    \                res[ch] = c;\n                if constexpr (usePostMerge) cent_child.push_back(ch);\n\
    \            }\n        if constexpr (usePostMerge) post_merge_func(c, cent_child);\n\
    \        done[c] = 0;\n        return c;\n    };\n    res[cut(cut, 0, n)] = -1;\n\
    \    return res;\n}\n#line 5 \"Tree/CentroidTree.hpp\"\n\ntemplate<typename Edge\
    \ = void, typename Vertex = void>\nclass CentroidTree : public Tree<Edge, Vertex>\
    \ {\npublic:\n    std::vector<int> c_pa;\n    using super = Tree<Edge, Vertex>;\n\
    \    CentroidTree(int n): super(n) {} \n    CentroidTree(const super &tree): super(tree)\
    \ {}\n    template<typename F_Pre = NullFunc, typename F_Merge = NullFunc, typename\
    \ F_Post = NullFunc>\n    void build(F_Pre pre_func = NullFunc{}, F_Merge merge_func\
    \ = NullFunc{}, F_Post post_func = NullFunc{}) {\n        c_pa = centroid_divide_and_conquer(*this,\
    \ pre_func, merge_func, post_func);\n    }\n    /*\n    action(c, prev_c)\n  \
    \      - c: current centorid\n        - prev_c: previous centroid, -1 if none\n\
    \    */\n    void climb(int u, auto action) const {\n        int c = u, prev_c\
    \ = -1;\n        while (c != -1) {\n            action(c, prev_c);\n         \
    \   prev_c = c;\n            c = c_pa[c];\n        }\n    }\n};\n#line 4 \"Tree/CentroidDS/DistanceSolver.hpp\"\
    \n\ntemplate<typename DS>\nclass DistanceSolver : public CentroidTree<void, void>\
    \ {\npublic:\n    using super = CentroidTree<void, void>;\n    std::vector<std::vector<int>>\
    \ c_dist;\n    std::vector<DS> tr_self, tr_parent;\n    DistanceSolver(int n)\
    \ : super(n), c_dist(n), tr_self(n, 0), tr_parent(n, 0) {}\n    void build() {\n\
    \        std::vector<int> dis(this->n());\n        super::build([&](int u, int\
    \ f) {\n            if (f == -1) dis[u] = 0;\n            else dis[u] = dis[f]\
    \ + 1;\n            c_dist[u].push_back(dis[u]);\n        }, [&](int c, const\
    \ std::vector<std::vector<int>> &groups) {\n            int mx = 1;\n        \
    \    for (auto &vec : groups)\n                for (auto v : vec)\n          \
    \          mx = std::max(mx, dis[v] + 1);\n            tr_self[c] = DS(mx);\n\
    \            if (int(c_dist[c].size()) >= 2) {\n                mx = c_dist[c][int(c_dist[c].size())\
    \ - 2] + 1;\n                for (auto &vec : groups)\n                    for\
    \ (auto v : vec)\n                        mx = std::max(mx, c_dist[v][int(c_dist[v].size())\
    \ - 2] + 1);\n                tr_parent[c] = DS(mx);\n            }\n        });\n\
    \        for (int i = 0; i < this->n(); ++i) std::ranges::reverse(c_dist[i]);\n\
    \    }\n    /*\n    action(ds, d, prev)\n        - ds: the data structure on the\
    \ corresponding centroid\n        - d: the distance from u to the centroid\n \
    \       - prev: whether using prev centroid\n    */\n    template<typename Func>\n\
    \    void climb(int u, Func action) {\n        int jump_steps = 0;\n        super::climb(u,\
    \ [&](int c, int prev_c) {\n            action(tr_self[c], c_dist[u][jump_steps],\
    \ false);\n            if (prev_c != -1)\n                action(tr_parent[prev_c],\
    \ c_dist[u][jump_steps], true);\n            ++jump_steps;\n        });\n    }\n\
    };\n#line 2 \"DataStructure/BIT.hpp\"\n\ntemplate<class T>\nclass BIT { // 0-base\n\
    public:\n    int n;\n    T total_;\n    std::vector<T> bit;\n    BIT(int _n) :\
    \ n(_n), total_(), bit(n + 1) {}\n    template<typename U>\n    BIT(const std::vector<U>\
    \ &arr) : n(arr.size()), total_(std::accumulate(arr.begin(), arr.end(), T())),\
    \ bit(n + 1) {\n        for (int x = 1; x <= n; ++x) {\n            bit[x] = arr[x\
    \ - 1];\n            int y = x - (x & -x);\n            for (int i = x - 1; i\
    \ > y; i -= i & -i)\n                bit[x] = bit[x] + bit[i];\n        }\n  \
    \  }\n    void modify(int x, T v) {\n        total_ = total_ + v;\n        for\
    \ (++x; x <= n; x += x & -x)\n            bit[x] = bit[x] + v;\n    }\n    T prefix(int\
    \ x) {\n        T res = T();\n        for (++x; x; x -= x & -x)\n            res\
    \ = res + bit[x];\n        return res;\n    }\n    T suffix(int x) requires requires(T\
    \ x, T y) { x - y; } {\n        return total_ - prefix(x - 1);\n    }\n    T range(int\
    \ l, int r) requires requires(T x, T y) { x - y; } { // [l, r)\n        if (l\
    \ >= r) return T();\n        T res = prefix(r - 1) - prefix(l - 1);\n        return\
    \ res;\n    }\n    int kth(int k) { // 0-base query\n        assert((n & (n -\
    \ 1)) == 0);\n        ++k;\n        int res = 0;\n        for (int i = n >> 1;\
    \ i >= 1; i >>= 1) {\n            if (bit[res + i] < k)\n                k -=\
    \ bit[res += i];\n        }\n        return res;\n    }\n    T total() {\n   \
    \     return total_;\n    }\n};\n#line 6 \"test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    std::vector<int> arr(n);\n    for (int &i\
    \ : arr)\n        std::cin >> i;\n    DistanceSolver<BIT<long long>> tree(n);\n\
    \    for (int i = 1; i < n; ++i) {\n        int u, v;\n        std::cin >> u >>\
    \ v;\n        tree.add_edge(u, v);\n    }\n    tree.build();\n    auto range_add\
    \ = [&](auto &ds, int l, int r, int x) {\n        l = std::max(l, 0), r = std::min(r,\
    \ ds.n);\n        if (l >= r) return;\n        ds.modify(l, x);\n        ds.modify(r,\
    \ -x);\n    };\n    while (q--) {\n        int op, p;\n        std::cin >> op\
    \ >> p;\n        if (op == 0) {\n            int l, r, x;\n            std::cin\
    \ >> l >> r >> x;\n            tree.climb(p, [&](auto &ds, int d, [[maybe_unused]]\
    \ bool prev) {\n                range_add(ds, l - d, r - d, x);\n            });\n\
    \        }\n        else {\n            long long ans = arr[p];\n            tree.climb(p,\
    \ [&](auto &ds, int d, bool prev) {\n                long long res = ds.prefix(d);\n\
    \                if (prev) ans -= res;\n                else ans += res;\n   \
    \         });\n            std::cout << ans << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_get_range_contour_add_on_tree\"\
    \n#include \"assumption.hpp\"\n\n#include \"Tree/CentroidDS/DistanceSolver.hpp\"\
    \n#include \"DataStructure/BIT.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<int>\
    \ arr(n);\n    for (int &i : arr)\n        std::cin >> i;\n    DistanceSolver<BIT<long\
    \ long>> tree(n);\n    for (int i = 1; i < n; ++i) {\n        int u, v;\n    \
    \    std::cin >> u >> v;\n        tree.add_edge(u, v);\n    }\n    tree.build();\n\
    \    auto range_add = [&](auto &ds, int l, int r, int x) {\n        l = std::max(l,\
    \ 0), r = std::min(r, ds.n);\n        if (l >= r) return;\n        ds.modify(l,\
    \ x);\n        ds.modify(r, -x);\n    };\n    while (q--) {\n        int op, p;\n\
    \        std::cin >> op >> p;\n        if (op == 0) {\n            int l, r, x;\n\
    \            std::cin >> l >> r >> x;\n            tree.climb(p, [&](auto &ds,\
    \ int d, [[maybe_unused]] bool prev) {\n                range_add(ds, l - d, r\
    \ - d, x);\n            });\n        }\n        else {\n            long long\
    \ ans = arr[p];\n            tree.climb(p, [&](auto &ds, int d, bool prev) {\n\
    \                long long res = ds.prefix(d);\n                if (prev) ans\
    \ -= res;\n                else ans += res;\n            });\n            std::cout\
    \ << ans << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Tree/CentroidDS/DistanceSolver.hpp
  - Tree/CentroidTree.hpp
  - Tree/Tree.hpp
  - Graph/base.hpp
  - Graph/UnifiedWeight.hpp
  - Algebra/ValidOperation.hpp
  - Tree/centroid_divide_and_conquer.hpp
  - Algebra/NullFunc.hpp
  - DataStructure/BIT.hpp
  isVerificationFile: true
  path: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 13:11:38+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
- /verify/test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp.html
title: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
---
