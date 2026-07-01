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
    path: Convolution/convolution.hpp
    title: Convolution/convolution.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/UnifiedWeight.hpp
    title: Graph/UnifiedWeight.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/crt.hpp
    title: Numeric/crt.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/internal_primitive_root.hpp
    title: Numeric/internal_primitive_root.hpp
  - icon: ':heavy_check_mark:'
    path: Polynomial/NTT.hpp
    title: Polynomial/NTT.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
    links:
    - https://judge.yosupo.jp/problem/frequency_table_of_tree_distance
  bundledCode: "#line 1 \"test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp\"\
    \n\n#line 2 \"Tree/centroid_divide_and_conquer.hpp\"\n\n#line 2 \"Tree/Tree.hpp\"\
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
    \ Vertex>::Graph;\n};\n#line 2 \"Graph/UnifiedWeight.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate <typename A, typename B>\nconcept Addable = !std::is_void_v<A> &&\
    \ !std::is_void_v<B> && requires(A a, B b) { a + b; };\n\ntemplate <typename A,\
    \ typename B>\nconcept Subtractable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a - b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a * b; };\n#line 4 \"Graph/UnifiedWeight.hpp\"\n\ntemplate <typename Edge,\
    \ typename Vertex>\nstruct UnifiedWeight {\n    using type = std::conditional_t<std::is_void_v<Vertex>,\
    \ Edge, Vertex>;\n};\n\ntemplate <typename Edge, typename Vertex>\nusing UnifiedWeight_t\
    \ = typename UnifiedWeight<Edge, Vertex>::type;\n\ntemplate <typename Edge, typename\
    \ Vertex>\nconcept AddableUnifiedWeight = \n    (std::is_void_v<Vertex> && Addable<Edge,\
    \ Edge>) ||\n    (Addable<Vertex, Vertex> && (std::is_void_v<Edge> || Addable<Vertex,\
    \ Edge>));\n#line 6 \"Tree/Tree.hpp\"\n\ntemplate<typename Edge = void, typename\
    \ Vertex = void>\nclass Tree : public Graph<false, Edge, Vertex> {\npublic:\n\
    \    using super = Graph<false, Edge, Vertex>;\n    using super::hasEdgeWeight;\n\
    \    using super::hasVertexWeight;\n    using WeightType = UnifiedWeight_t<Edge,\
    \ Vertex>;\n    int current_root;\n    std::vector<int> pa, dfs_in, dfs_out;\n\
    \    std::vector<int> preorder, postorder;\n    Tree(int n): super(n), current_root(-1)\
    \ {}\n    Tree(const super &graph, const std::vector<int> &edge_index): super(graph.n()),\
    \ current_root(-1) {\n        assert(int(edge_index.size()) + 1 == this->n());\n\
    \        for (int eid : edge_index)\n            this->add_edge(graph.edge(eid));\n\
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
    \  return res;\n    }\n    auto weighted_distance(int root = -1) requires (AddableUnifiedWeight<Edge,\
    \ Vertex>) {\n        if (current_root == -1 || (root != -1 && current_root !=\
    \ root)) {\n            assert(root != -1);\n            traverse(root);\n   \
    \     }\n        std::vector<WeightType> res(this->n());\n        predfs([&](int\
    \ u) {\n            res[u] = res[parent(u)];\n            if constexpr (hasEdgeWeight)\
    \ if (u != root)\n                res[u] = res[u] + parent_edge(u).weight;\n \
    \           if constexpr (hasVertexWeight)\n                res[u] = res[u] +\
    \ this->weight[u];\n        });\n        return res;\n    }\n    std::vector<int>\
    \ subtree_size(int root = -1) {\n        if (current_root == -1 || (root != -1\
    \ && current_root != root)) {\n            assert(root != -1);\n            traverse(root);\n\
    \        }\n        std::vector<int> res(this->n(), 1);\n        postdfs([&](int\
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
    \        });\n        return res;\n    }\n};\n#line 2 \"Algebra/NullFunc.hpp\"\
    \n\nstruct NullFunc {\n    constexpr void operator()(auto&&...) const {}\n};\n\
    #line 5 \"Tree/centroid_divide_and_conquer.hpp\"\n\n/*\npre_func: void pre_func(int\
    \ u, int f);\n    - u: current vertex, f: parent\n    - the center would be called\
    \ at first with pre_func(c, -1);\nmerge_func: void merge_func(int c, std::vector<std::vector<int>>\
    \ groups);\n    - c: the center, groups: subtrees with pre-order\npost_func: void\
    \ post_func(int u, std::vector<int> child);\n    - u: current vertex, child: child\
    \ vertices\npost_merge_func: void post_merge_func(int c, std::vector<int> cent_child);\n\
    \    - c: the center, cent_child: c's center children \nreturn value: c_pa[u]:\
    \ the centroid parent of u\n*/\n\ntemplate<typename _Tree, typename F_Pre = NullFunc,\
    \ typename F_Merge = NullFunc, typename F_Post = NullFunc, typename F_PMerge =\
    \ NullFunc>\nstd::vector<int> centroid_divide_and_conquer(_Tree &tree, F_Pre pre_func\
    \ = NullFunc{}, F_Merge merge_func = NullFunc{}, F_Post post_func = NullFunc{},\
    \ F_PMerge post_merge_func = NullFunc{}) {\n    constexpr bool useMerge = !std::is_same_v<std::decay_t<decltype(merge_func)>,\
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
    \    return res;\n}\n#line 2 \"Convolution/convolution.hpp\"\n\n#line 2 \"Numeric/Modint.hpp\"\
    \n\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n#line\
    \ 2 \"Numeric/internal_math.hpp\"\n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\nconstexpr\
    \ long long safe_mod(long long x, long long m) {\n    x %= m;\n    if (x < 0)\
    \ x += m;\n    return x;\n}\nconstexpr long long pow_mod_constexpr(long long x,\
    \ long long n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m = (unsigned\
    \ int)(m);\n    unsigned long long r = 1;\n    unsigned long long y = safe_mod(x,\
    \ m);\n    while (n) {\n        if (n & 1) r = (r * y) % _m;\n        y = (y *\
    \ y) % _m;\n        n >>= 1;\n    }\n    return r;\n}\nconstexpr bool is_prime_constexpr(int\
    \ n) {\n    if (n <= 1) return false;\n    if (n == 2 || n == 7 || n == 61) return\
    \ true;\n    if (n % 2 == 0) return false;\n    long long d = n - 1;\n    while\
    \ (d % 2 == 0) d /= 2;\n    constexpr long long bases[3] = {2, 7, 61};\n    for\
    \ (long long a : bases) {\n        long long t = d;\n        long long y = pow_mod_constexpr(a,\
    \ t, n);\n        while (t != n - 1 && y != 1 && y != n - 1)\n            y =\
    \ y * y % n, t <<= 1;\n        if (y != n - 1 && t % 2 == 0)\n            return\
    \ false;\n    }\n    return true;\n}\ntemplate <int n> constexpr bool is_prime\
    \ = is_prime_constexpr(n);\nconstexpr std::pair<long long, long long> inv_gcd(long\
    \ long a, long long b) {\n    a = safe_mod(a, b);\n    if (a == 0) return {b,\
    \ 0};\n    long long s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n        long\
    \ long u = s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp = s;\n\
    \        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0 < 0)\
    \ m0 += b / s;\n    return {s, m0};\n}\n}  // namespace internal\n\nnamespace\
    \ internal {\n#ifndef _MSC_VER\n    template <class T>\n        using is_signed_int128\
    \ =\n        typename std::conditional<std::is_same<T, __int128_t>::value ||\n\
    \        std::is_same<T, __int128>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using is_unsigned_int128 =\n        typename\
    \ std::conditional<std::is_same<T, __uint128_t>::value ||\n        std::is_same<T,\
    \ unsigned __int128>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using make_unsigned_int128 =\n        typename\
    \ std::conditional<std::is_same<T, __int128_t>::value,\n                 __uint128_t,\n\
    \                 unsigned __int128>;\n    template <class T>\n        using is_integral\
    \ = typename std::conditional<std::is_integral<T>::value ||\n        is_signed_int128<T>::value\
    \ ||\n        is_unsigned_int128<T>::value,\n        std::true_type,\n       \
    \ std::false_type>::type;\n    template <class T>\n        using is_signed_int\
    \ = typename std::conditional<(is_integral<T>::value &&\n                std::is_signed<T>::value)\
    \ ||\n        is_signed_int128<T>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using is_unsigned_int =\n        typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_unsigned<T>::value) ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<\n        is_signed_int128<T>::value,\n\
    \        make_unsigned_int128<T>,\n        typename std::conditional<std::is_signed<T>::value,\n\
    \        std::make_unsigned<T>,\n        std::common_type<T>>::type>::type;\n\
    #else\n    template <class T> using is_integral = typename std::is_integral<T>;\n\
    \    template <class T>\n        using is_signed_int =\n        typename std::conditional<is_integral<T>::value\
    \ && std::is_signed<T>::value,\n                 std::true_type,\n           \
    \      std::false_type>::type;\n    template <class T>\n        using is_unsigned_int\
    \ =\n        typename std::conditional<is_integral<T>::value &&\n        std::is_unsigned<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<is_signed_int<T>::value,\n\
    \              std::make_unsigned<T>,\n              std::common_type<T>>::type;\n\
    #endif\n    template <class T> using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\n\
    \    template <class T> using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\n\
    \    template <class T> using to_unsigned_t = typename to_unsigned<T>::type;\n\
    \    struct modint_base {};\n    struct static_modint_base : modint_base {};\n\
    \    template <class T> using is_modint = std::is_base_of<modint_base, T>;\n \
    \   template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\
    }  // namespace internal\n#line 5 \"Numeric/Modint.hpp\"\n\ntemplate <int m, std::enable_if_t<(1\
    \ <= m)>* = nullptr>\nstruct static_modint : internal::static_modint_base {\n\
    \    using mint = static_modint;\n\n  public:\n    static constexpr int mod()\
    \ { return m; }\n    static mint raw(int v) {\n        mint x;\n        x._v =\
    \ v;\n        return x;\n    }\n\n    static_modint() : _v(0) {}\n    template\
    \ <class T, internal::is_signed_int_t<T>* = nullptr>\n    static_modint(T v) {\n\
    \        long long x = (long long)(v % (long long)(umod()));\n        if (x <\
    \ 0) x += umod();\n        _v = (unsigned int)(x);\n    }\n    template <class\
    \ T, internal::is_unsigned_int_t<T>* = nullptr>\n    static_modint(T v) {\n  \
    \      _v = (unsigned int)(v % umod());\n    }\n\n    unsigned int val() const\
    \ { return _v; }\n\n    mint& operator++() {\n        _v++;\n        if (_v ==\
    \ umod()) _v = 0;\n        return *this;\n    }\n    mint& operator--() {\n  \
    \      if (_v == 0) _v = umod();\n        _v--;\n        return *this;\n    }\n\
    \    mint operator++(int) {\n        mint result = *this;\n        ++*this;\n\
    \        return result;\n    }\n    mint operator--(int) {\n        mint result\
    \ = *this;\n        --*this;\n        return result;\n    }\n\n    mint& operator+=(const\
    \ mint& rhs) {\n        _v += rhs._v;\n        if (_v >= umod()) _v -= umod();\n\
    \        return *this;\n    }\n    mint& operator-=(const mint& rhs) {\n     \
    \   _v -= rhs._v;\n        if (_v >= umod()) _v += umod();\n        return *this;\n\
    \    }\n    mint& operator*=(const mint& rhs) {\n        unsigned long long z\
    \ = _v;\n        z *= rhs._v;\n        _v = (unsigned int)(z % umod());\n    \
    \    return *this;\n    }\n    mint& operator/=(const mint& rhs) { return *this\
    \ = *this * rhs.inv(); }\n\n    mint operator+() const { return *this; }\n   \
    \ mint operator-() const { return mint() - *this; }\n\n    mint pow(long long\
    \ n) const {\n        assert(0 <= n);\n        mint x = *this, r = 1;\n      \
    \  while (n) {\n            if (n & 1) r *= x;\n            x *= x;\n        \
    \    n >>= 1;\n        }\n        return r;\n    }\n    mint inv() const {\n \
    \       if (prime) {\n            assert(_v);\n            return pow(umod() -\
    \ 2);\n        } else {\n            auto eg = internal::inv_gcd(_v, m);\n   \
    \         assert(eg.first == 1);\n            return eg.second;\n        }\n \
    \   }\n\n    friend mint operator+(const mint& lhs, const mint& rhs) {\n     \
    \   return mint(lhs) += rhs;\n    }\n    friend mint operator-(const mint& lhs,\
    \ const mint& rhs) {\n        return mint(lhs) -= rhs;\n    }\n    friend mint\
    \ operator*(const mint& lhs, const mint& rhs) {\n        return mint(lhs) *= rhs;\n\
    \    }\n    friend mint operator/(const mint& lhs, const mint& rhs) {\n      \
    \  return mint(lhs) /= rhs;\n    }\n    friend bool operator==(const mint& lhs,\
    \ const mint& rhs) {\n        return lhs._v == rhs._v;\n    }\n    friend bool\
    \ operator!=(const mint& lhs, const mint& rhs) {\n        return lhs._v != rhs._v;\n\
    \    }\n    friend std::strong_ordering operator<=>(const mint& lhs, const mint&\
    \ rhs) {\n        return lhs._v <=> rhs._v;\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const mint& v) {\n        os << v._v;\n        return os;\n    }\n    friend\
    \ std::istream& operator>>(std::istream& is, mint& v) {\n        long long x;\n\
    \        is >> x;\n        x %= (long long)(umod());\n        if (x < 0) x +=\
    \ umod();\n        v._v = (unsigned int)(x);\n        return is;\n    }\n\n  private:\n\
    \    unsigned int _v;\n    static constexpr unsigned int umod() { return m; }\n\
    \    static constexpr bool prime = internal::is_prime<m>;\n};\n\nusing modint998244353\
    \ = static_modint<998244353>;\nusing modint1000000007 = static_modint<1000000007>;\n\
    #line 2 \"Polynomial/NTT.hpp\"\n\n#line 2 \"Numeric/internal_primitive_root.hpp\"\
    \n\n#line 4 \"Numeric/internal_primitive_root.hpp\"\n\n// reference: Atcoder Library\
    \ https://github.com/atcoder/ac-library\n\nnamespace internal { \n// Compile time\
    \ primitive root\n// @param m must be prime\n// @return primitive root (and minimum\
    \ in now)\nconstexpr int primitive_root_constexpr(int m) {\n    if (m == 2) return\
    \ 1;\n    if (m == 167772161) return 3;\n    if (m == 469762049) return 3;\n \
    \   if (m == 754974721) return 11;\n    if (m == 998244353) return 3;\n    int\
    \ divs[20] = {};\n    divs[0] = 2;\n    int cnt = 1;\n    int x = (m - 1) / 2;\n\
    \    while (x % 2 == 0) x /= 2;\n    for (int i = 3; (long long)(i)*i <= x; i\
    \ += 2) {\n        if (x % i == 0) {\n            divs[cnt++] = i;\n         \
    \   while (x % i == 0) {\n                x /= i;\n            }\n        }\n\
    \    }\n    if (x > 1) {\n        divs[cnt++] = x;\n    }\n    for (int g = 2;;\
    \ g++) {\n        bool ok = true;\n        for (int i = 0; i < cnt; i++) {\n \
    \           if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {\n         \
    \       ok = false;\n                break;\n            }\n        }\n      \
    \  if (ok) return g;\n    }\n}\ntemplate <int m> constexpr int primitive_root\
    \ = primitive_root_constexpr(m);\n}  // namespace internal\n#line 5 \"Polynomial/NTT.hpp\"\
    \n\ntemplate<typename T>\nrequires std::derived_from<T, internal::modint_base>\n\
    class NTT {\n    inline static int max_size = 1;\n    inline static std::vector<T>\
    \ w{1, T(1)};\n    inline static const T root = internal::primitive_root_constexpr(T::mod());\n\
    \    static void ensure_upper_bound(int n) {\n        if (max_size < n) {\n  \
    \          while (max_size <= n) max_size <<= 1;\n            w.resize(max_size);\n\
    \            std::ranges::fill(w, 1);\n            T dw = root.pow((T::mod() -\
    \ 1) / max_size);\n            for (int s = max_size / 2; s; s >>= 1, dw *= dw)\
    \ {\n                w[s] = 1;\n                for (int j = 1; j < s; ++j) \n\
    \                    w[s + j] = w[s + j - 1] * dw;\n            }\n        }\n\
    \    }\npublic:\n    static constexpr int ntt_max_limit = []() {\n        unsigned\
    \ int m = T::mod() - 1;\n        int limit = 1;\n        while ((m & 1) == 0)\
    \ {\n            limit <<= 1;\n            m >>= 1;\n        }\n        return\
    \ limit;\n    }();\n    static void ntt(std::vector<T> &a, bool inv = false) {\
    \ //0 <= a[i] < P\n        int n = a.size();\n        assert((n & (n - 1)) ==\
    \ 0);\n        ensure_upper_bound(n);\n        for (int i = 0, j = 1; j < n -\
    \ 1; ++j) {\n            for (int k = n >> 1; (i ^= k) < k; k >>= 1);\n      \
    \      if (j < i) std::swap(a[i], a[j]);\n        }\n        for (int s = 1; s\
    \ < n; s <<= 1) {\n            for (int i = 0; i < n; i += s * 2) {\n        \
    \        for (int j = 0; j < s; ++j) {\n                    T tmp = a[i + s +\
    \ j] * w[s + j];\n                    a[i + s + j] = a[i + j] - tmp;\n       \
    \             a[i + j] += tmp;\n                }\n            }\n        }\n\
    \        if (!inv) return;\n        T iv = T(n).inv(); \n        std::reverse(a.begin()\
    \ + 1, a.begin() + n);\n        for (int i = 0; i < n; ++i) a[i] *= iv;\n    }\n\
    \    static size_t maxsize() {\n        return max_size;\n    }\n    static std::vector<T>\
    \ convolution(std::vector<T> a, std::vector<T> b) {\n        if (a.empty() ||\
    \ b.empty()) return std::vector<T>();\n        int n = 1, sz = int(a.size()) +\
    \ int(b.size()) - 1;\n        while (n < sz) n <<= 1;\n        assert(n <= ntt_max_limit\
    \ && \"the result length exceeds the limit of the prime can support\");\n    \
    \    a.resize(n), b.resize(n);\n        ntt(a), ntt(b);\n        for (int i =\
    \ 0; i < n; ++i)\n            a[i] = a[i] * b[i];\n        ntt(a, true);\n   \
    \     a.resize(sz);\n        return a;\n    }\n};\n#line 2 \"Numeric/crt.hpp\"\
    \n\n// source: https://maspypy.github.io/library/mod/crt3.hpp\n\nconstexpr unsigned\
    \ int mod_pow_constexpr(unsigned long long a, unsigned long long n, unsigned int\
    \ mod) {\n    a %= mod;\n    unsigned long long res = 1;\n    for (int i = 0;\
    \ i < 32; ++i) {\n        if (n & 1) res = res * a % mod;\n        a = a * a %\
    \ mod, n /= 2;\n    }\n    return res;\n}\n\ntemplate <typename T, unsigned int\
    \ p0, unsigned int p1>\nT CRT2(unsigned long long a0, unsigned long long a1) {\n\
    \    static_assert(p0 < p1);\n    static constexpr unsigned long long x0_1 = mod_pow_constexpr(p0,\
    \ p1 - 2, p1);\n    unsigned long long c = (a1 - a0 + p1) * x0_1 % p1;\n    return\
    \ a0 + c * p0;\n}\n\ntemplate <typename T, unsigned int p0, unsigned int p1, unsigned\
    \ int p2>\nT CRT3(unsigned long long a0, unsigned long long a1, unsigned long\
    \ long a2) {\n    static_assert(p0 < p1 && p1 < p2);\n    static constexpr unsigned\
    \ long long x1 = mod_pow_constexpr(p0, p1 - 2, p1);\n    static constexpr unsigned\
    \ long long x2 = mod_pow_constexpr((unsigned long long)(p0) * p1 % p2, p2 - 2,\
    \ p2);\n    static constexpr unsigned long long p01 = (unsigned long long)(p0)\
    \ * p1;\n    unsigned long long c = (a1 - a0 + p1) * x1 % p1;\n    unsigned long\
    \ long ans_1 = a0 + c * p0;\n    c = (a2 - ans_1 % p2 + p2) * x2 % p2;\n    return\
    \ T(ans_1) + T(c) * T(p01);\n}\n#line 6 \"Convolution/convolution.hpp\"\n\ntemplate<int\
    \ C = 1, typename T = modint998244353>\nstd::vector<T> convolution(std::vector<T>\
    \ a, std::vector<T> b) {\n    static_assert(1 <= C && C <= 3, \"NTT convolution\
    \ must use 1, 2, or 3 primes.\");\n    if (a.empty() || b.empty()) return std::vector<T>();\n\
    \n    if constexpr (std::derived_from<T, internal::static_modint_base>) {\n  \
    \      int sz = a.size() + b.size() - 1;\n        if (std::bit_ceil((unsigned\
    \ int)sz) <= NTT<T>::ntt_max_limit)\n            return NTT<T>::convolution(a,\
    \ b);\n    }\n    \n    static constexpr int p0 = 167772161;\n    static constexpr\
    \ int p1 = 469762049;\n    static constexpr int p2 = 754974721;\n\n    auto get_val\
    \ = [](const T& x) {\n        if constexpr (std::derived_from<T, internal::modint_base>)\
    \ return x.val();\n        else return x;\n    };\n\n    auto do_ntt = [&](auto\
    \ P_tag) {\n        constexpr int P = decltype(P_tag)::value;\n        using mint\
    \ = static_modint<P>;\n        std::vector<mint> a_mint(a.size()), b_mint(b.size());\n\
    \        for (int i = 0; i < int(a.size()); ++i) a_mint[i] = get_val(a[i]);\n\
    \        for (int i = 0; i < int(b.size()); ++i) b_mint[i] = get_val(b[i]);\n\
    \        return NTT<mint>::convolution(a_mint, b_mint);\n    };\n\n    auto res\
    \ = [&]() {\n        if constexpr (C == 1)\n            return std::make_tuple(do_ntt(std::integral_constant<int,\
    \ p0>{}));\n        else if constexpr (C == 2)\n            return std::make_tuple(do_ntt(std::integral_constant<int,\
    \ p0>{}),\n                                   do_ntt(std::integral_constant<int,\
    \ p1>{}));\n        else\n            return std::make_tuple(do_ntt(std::integral_constant<int,\
    \ p0>{}),\n                                   do_ntt(std::integral_constant<int,\
    \ p1>{}),\n                                   do_ntt(std::integral_constant<int,\
    \ p2>{}));\n    }();\n\n    std::vector<T> c(std::get<0>(res).size());\n    for\
    \ (int i = 0; i < int(c.size()); ++i)\n        if constexpr (C == 1)\n       \
    \     c[i] = T(std::get<0>(res)[i].val());\n        else if constexpr (C == 2)\n\
    \            c[i] = CRT2<T, p0, p1>(std::get<0>(res)[i].val(),\n             \
    \                      std::get<1>(res)[i].val());\n        else if constexpr\
    \ (C == 3)\n            c[i] = CRT3<T, p0, p1, p2>(std::get<0>(res)[i].val(),\n\
    \                                       std::get<1>(res)[i].val(),\n         \
    \                              std::get<2>(res)[i].val());\n    return c;\n}\n\
    #line 6 \"test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp\"\
    \n\nusing mint = modint998244353;\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n;\n    std::cin >> n;\n    Tree tree(n);\n    for\
    \ (int i = 1; i < n; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n\
    \        tree.add_edge(u, v);\n    }\n    std::vector<int> depth(n);\n    std::vector<long\
    \ long> ans(n);\n    centroid_divide_and_conquer(tree, [&](int u, int f) {\n \
    \       if (f == -1) depth[u] = 0;\n        else depth[u] = depth[f] + 1;\n  \
    \  }, [&](int c, const std::vector<std::vector<int>> &groups) {\n        (void)c;\n\
    \        if (groups.empty()) return;\n        int mx = 0;\n        for (auto &vec\
    \ : groups)\n            for (auto v : vec)\n                mx = std::max(mx,\
    \ depth[v] + 1);\n        std::vector<long long> cnt(mx);\n        cnt[0] = 1;\n\
    \        for (auto &vec : groups)\n            for (auto v : vec)\n          \
    \      ++cnt[depth[v]];\n        convolution<2>(cnt, cnt).swap(cnt);\n       \
    \ for (int i = 0; i < int(cnt.size()); ++i)\n            ans[i] += cnt[i];\n \
    \       for (auto &vec : groups) {\n            mx = 0;\n            for (auto\
    \ v : vec)\n                mx = std::max(mx, depth[v] + 1);\n            std::vector<long\
    \ long>(mx).swap(cnt);\n            for (auto v : vec)\n                ++cnt[depth[v]];\n\
    \            convolution<2>(cnt, cnt).swap(cnt);\n            for (int i = 0;\
    \ i < int(cnt.size()); ++i)\n                ans[i] -= cnt[i];\n        }\n  \
    \  });\n    for (int i = 1; i < n; ++i)\n        std::cout << ans[i] / 2 << \"\
    \ \\n\"[i + 1 == n];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/frequency_table_of_tree_distance\"\
    \n#include \"assumption.hpp\"\n\n#include \"Tree/centroid_divide_and_conquer.hpp\"\
    \n#include \"Convolution/convolution.hpp\"\n\nusing mint = modint998244353;\n\n\
    int main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n;\n\
    \    std::cin >> n;\n    Tree tree(n);\n    for (int i = 1; i < n; ++i) {\n  \
    \      int u, v;\n        std::cin >> u >> v;\n        tree.add_edge(u, v);\n\
    \    }\n    std::vector<int> depth(n);\n    std::vector<long long> ans(n);\n \
    \   centroid_divide_and_conquer(tree, [&](int u, int f) {\n        if (f == -1)\
    \ depth[u] = 0;\n        else depth[u] = depth[f] + 1;\n    }, [&](int c, const\
    \ std::vector<std::vector<int>> &groups) {\n        (void)c;\n        if (groups.empty())\
    \ return;\n        int mx = 0;\n        for (auto &vec : groups)\n           \
    \ for (auto v : vec)\n                mx = std::max(mx, depth[v] + 1);\n     \
    \   std::vector<long long> cnt(mx);\n        cnt[0] = 1;\n        for (auto &vec\
    \ : groups)\n            for (auto v : vec)\n                ++cnt[depth[v]];\n\
    \        convolution<2>(cnt, cnt).swap(cnt);\n        for (int i = 0; i < int(cnt.size());\
    \ ++i)\n            ans[i] += cnt[i];\n        for (auto &vec : groups) {\n  \
    \          mx = 0;\n            for (auto v : vec)\n                mx = std::max(mx,\
    \ depth[v] + 1);\n            std::vector<long long>(mx).swap(cnt);\n        \
    \    for (auto v : vec)\n                ++cnt[depth[v]];\n            convolution<2>(cnt,\
    \ cnt).swap(cnt);\n            for (int i = 0; i < int(cnt.size()); ++i)\n   \
    \             ans[i] -= cnt[i];\n        }\n    });\n    for (int i = 1; i < n;\
    \ ++i)\n        std::cout << ans[i] / 2 << \" \\n\"[i + 1 == n];\n}\n"
  dependsOn:
  - assumption.hpp
  - Tree/centroid_divide_and_conquer.hpp
  - Tree/Tree.hpp
  - Graph/base.hpp
  - Graph/UnifiedWeight.hpp
  - Algebra/ValidOperation.hpp
  - Algebra/NullFunc.hpp
  - Convolution/convolution.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - Polynomial/NTT.hpp
  - Numeric/internal_primitive_root.hpp
  - Numeric/crt.hpp
  isVerificationFile: true
  path: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
  requiredBy: []
  timestamp: '2026-06-30 23:51:20+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
- /verify/test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp.html
title: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
---
