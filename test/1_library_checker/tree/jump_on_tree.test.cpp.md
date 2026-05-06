---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/UnifiedWeight.hpp
    title: Graph/UnifiedWeight.hpp
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/Tree.hpp
    title: Tree/Tree.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/TreeTools.hpp
    title: Tree/TreeTools.hpp
  - icon: ':question:'
    path: default_code.hpp
    title: default_code.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/jump_on_tree
    links:
    - https://judge.yosupo.jp/problem/jump_on_tree
  bundledCode: "#line 1 \"test/1_library_checker/tree/jump_on_tree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/jump_on_tree\"\n#line 2 \"default_code.hpp\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\ntypedef long long ll;\ntypedef\
    \ pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n#define X first\n#define Y second\n\
    #define SZ(a) ((int)a.size())\n#define ALL(v) v.begin(), v.end()\ntemplate<class\
    \ A, class B>\nostream& operator<<(ostream& os, const pair<A, B> &a) {\n    os\
    \ << \"(\" << a.first << \", \" << a.second << \")\";\n    return os;\n}\ntemplate\
    \ <typename T>\nconcept PrintableContainer = requires(T& a) {\n    a.begin();\n\
    \    a.end();\n} && !std::same_as<std::remove_cvref_t<T>, std::string> &&\n  \
    \   !std::same_as<std::remove_cvref_t<T>, std::string_view> &&\n     !std::is_convertible_v<T,\
    \ const char*>;\ntemplate <PrintableContainer T>\nstd::ostream& operator<<(std::ostream&\
    \ os, const T& a) {\n    os << \"[ \";\n    bool first = true;\n    for (const\
    \ auto& item : a) {\n        if (!first) os << \", \";\n        os << item;\n\
    \        first = false;\n    }\n    return os << \" ]\";\n}\n#ifdef bbq\n#include\
    \ <experimental/iterator>\n#define safe cerr<<__PRETTY_FUNCTION__<<\" line \"\
    <<__LINE__<<\" safe\\n\"\n#define sepline sepline_() \n#define debug(a...) debug_(#a,\
    \ a)\n#define orange(a...) orange_(#a, a)\nvoid debug_(auto s, auto ...a) {\n\
    \    cerr << \"\\e[1;32m(\" << s << \") = (\";\n    int f = 0;\n    (..., (cerr\
    \ << (f++ ? \", \" : \"\") << a));\n    cerr << \")\\e[0m\\n\";\n}\nvoid orange_(auto\
    \ s, auto L, auto R) {\n    cerr << \"\\e[1;33m[ \" << s << \" ] = [ \";\n   \
    \ using namespace experimental;\n    copy(L, R, make_ostream_joiner(cerr, \",\
    \ \"));\n    cerr << \" ]\\e[0m\\n\";\n}\nvoid sepline_(int length = 50) {\n \
    \   cerr << \"\\e[1;35m\";\n    cerr << string(length, '=');\n    cerr << \"\\\
    e[0m\\n\";\n}\n#else\n#define safe ((void)0)\n#define sepline safe\n#define debug(...)\
    \ safe\n#define orange(...) safe\n#endif\n\nvoid chmax(auto &x, auto val) {\n\
    \    x = max(x, val);\n}\n\nvoid chmin(auto &x, auto val) {\n    x = min(x, val);\n\
    }\n\nvector<int> count_array(const auto &container, int sz = -1) {\n    if (sz\
    \ == -1) sz = *ranges::max_element(container) + 1;\n    vector<int> res(sz);\n\
    \    for (auto x : container) ++res[x];\n    return res;\n}\n\ntemplate<class\
    \ T>\nvoid discretization(vector<T> &vals) {\n    ranges::sort(vals);\n    vals.erase(ranges::unique(vals).begin(),\
    \ vals.end());\n}\n#line 3 \"test/1_library_checker/tree/jump_on_tree.test.cpp\"\
    \n\n#line 2 \"Tree/TreeTools.hpp\"\n\n#line 2 \"Tree/Tree.hpp\"\n\n#line 2 \"\
    Graph/base.hpp\"\n\ntemplate<bool directed = true, typename Edge = void, typename\
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
    \        });\n        return res;\n    }\n};\n#line 4 \"Tree/TreeTools.hpp\"\n\
    \ntemplate<typename Edge = void, typename Vertex = void>\nclass TreeTools : public\
    \ Tree<Edge, Vertex> {\npublic:\n    using super = Tree<Edge, Vertex>;\n    using\
    \ super::Tree;\n    using super::hasEdgeWeight;\n    using super::hasVertexWeight;\n\
    \    using typename super::WeightType;\n    static constexpr bool hasWeight =\
    \ !std::is_same_v<WeightType, void>;\n    static constexpr bool hasAddition =\
    \ ((!hasEdgeWeight || !hasVertexWeight) && ValidAddableState<WeightType, WeightType>)\
    \ || \n                                        ((hasEdgeWeight && hasVertexWeight)\
    \ && ValidAddableState<Vertex, Edge>); \n    static constexpr bool hasSubtract\
    \ = ValidSubtractableState<WeightType, WeightType>; \n    std::vector<int> dep;\n\
    \    std::vector<std::vector<int>> pa_table;\n    struct Empty {};\n    [[no_unique_address]]\
    \ std::conditional_t<hasWeight, std::vector<std::vector<WeightType>>, Empty> data;\n\
    \    [[no_unique_address]] std::conditional_t<hasWeight, std::vector<std::vector<WeightType>>,\
    \ Empty> rootpath;\n    void build_rootpath(int root = -1) {\n        if (this->current_root\
    \ == -1 || (root != -1 && this->current_root != root)) {\n            if (root\
    \ == -1) root = 0;\n            this->traverse(root);\n        }\n        this->depth().swap(dep);\n\
    \        if constexpr (hasAddition) {\n            this->weighted_distance().swap(rootpath);\n\
    \        }\n    }\n    void build_patable(int root = -1) {\n        if (this->current_root\
    \ == -1 || (root != -1 && this->current_root != root)) {\n            if (root\
    \ == -1) root = 0;\n            this->traverse(root);\n        }\n        const\
    \ int L = std::__lg(this->n()); \n        vector<vector<int>>(L + 1, vector<int>(this->n())).swap(pa_table);\n\
    \        pa_table[0] = this->parents();\n        if constexpr (hasAddition) {\n\
    \            vector<vector<WeightType>>(L + 1, vector<WeightType>(this->n())).swap(data);\n\
    \            for (int i = 0; i < this->n(); ++i) {\n                if constexpr\
    \ (this->hasEdgeWeight && this->hasVertexWeight) {\n                    data[0][i]\
    \ = this->weight[i];\n                    if (i != root) data[0][i] = data[0][i]\
    \ + this->parent_edge(i).weight;\n                }\n                else if constexpr\
    \ (this->hasEdgeWeight) {\n                    if (i != root) data[0][i] = this->parent_edge(i).weight;\
    \ \n                }\n                else if constexpr (this->hasVertexWeight)\
    \ {\n                    data[0][i] = this->weight[i];\n                }\n  \
    \          }\n        }\n        for (int i = 1; i <= L; ++i)\n            for\
    \ (int j = 0; j < this->n(); ++j) {\n                pa_table[i][j] = pa_table[i\
    \ - 1][pa_table[i - 1][j]];\n                if constexpr (hasAddition)\n    \
    \                data[i][j] = data[i - 1][j] + data[i - 1][pa_table[i - 1][j]];\n\
    \            }\n    }\n    int lca(int u, int v) {\n        if (this->ancestor(u,\
    \ v)) return u;\n        if (this->ancestor(v, u)) return v;\n        int L =\
    \ __lg(this->n());\n        for (int i = L; i >= 0; --i)\n            if (!this->ancestor(pa_table[i][u],\
    \ v))\n                u = pa_table[i][u];\n        return pa_table[0][u];\n \
    \   }\n    // be aware of difference in reverse direction edges, this function\
    \ only support this when v is an ancestor of u\n    WeightType path_weight(int\
    \ u, int v) requires (hasAddition) {\n        assert(!pa_table.empty());\n   \
    \     int L = __lg(this->n());\n        WeightType res = WeightType();\n     \
    \   if (!this->ancestor(u, v)) {\n            for (int i = L; i >= 0; --i)\n \
    \               if (!this->ancestor(pa_table[i][u], v)) {\n                  \
    \  res = res + data[i][u];\n                    u = pa_table[i][u];\n        \
    \        }\n            res = res + data[0][u];\n            u = pa_table[0][u];\n\
    \        }\n        if constexpr (hasVertexWeight) res = res + this->weight[u];\n\
    \        if (!this->ancestor(v, u)) {\n            for (int i = L; i >= 0; --i)\n\
    \                if (!this->ancestor(pa_table[i][v], u)) {\n                 \
    \   res = res + data[i][v];\n                    v = pa_table[i][v];\n       \
    \         }\n            res = res + data[0][v];\n        }\n        return res;\n\
    \    }\n    int distance(int u, int v, int _lca = -1) {\n        if (dep.empty())\
    \ build_rootpath();\n        if (_lca == -1) _lca = lca(u, v);\n        return\
    \ dep[u] + dep[v] - dep[_lca] * 2;\n    }\n    auto weighted_distance(int u, int\
    \ v, int _lca = -1) requires (hasAddition && hasSubtract) {\n        if (dep.empty())\
    \ build_rootpath();\n        if (_lca == -1) _lca = lca(u, v);\n        WeightType\
    \ res = rootpath[u] + rootpath[v] - rootpath[_lca] - rootpath[_lca];\n       \
    \ if constexpr (hasVertexWeight) res = res + this->weight[_lca];\n        return\
    \ res;\n    }\n    int step(int u, int v, int d, int _lca = -1) {\n        if\
    \ (_lca == -1) _lca = lca(u, v);\n        if (d > distance(u, v, _lca))\n    \
    \        return -1;\n        if (this->ancestor(u, v)) { \n            std::swap(u,\
    \ v);\n            d = distance(u, v, _lca) - d;\n        }\n        if (this->ancestor(v,\
    \ u)) {\n            for (int i = 0; d; d >>= 1, ++i)\n                if (d &\
    \ 1)\n                    u = pa_table[i][u];\n            return u;\n       \
    \ }\n        if (d <= distance(u, _lca, _lca))\n            return step(u, _lca,\
    \ d, _lca);\n        d -= distance(u, _lca, _lca);\n        return step(v, _lca,\
    \ distance(v, _lca, _lca) - d, _lca);\n    }\n};\n#line 5 \"test/1_library_checker/tree/jump_on_tree.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n  \
    \  cin >> n >> q;\n    TreeTools<> tree(n);\n    for (int i = 1; i < n; ++i) {\n\
    \        int u, v;\n        cin >> u >> v;\n        tree.add_edge(u, v);\n   \
    \ }\n    tree.build_patable(0);\n    while (q--) {\n        int s, t, i;\n   \
    \     cin >> s >> t >> i;\n        if (i > tree.distance(s, t)) cout << \"-1\\\
    n\";\n        else cout << tree.step(s, t, i) << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/jump_on_tree\"\n#include\
    \ \"default_code.hpp\"\n\n#include \"Tree/TreeTools.hpp\"\n\nint main() {\n  \
    \  ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n    cin >> n >> q;\n \
    \   TreeTools<> tree(n);\n    for (int i = 1; i < n; ++i) {\n        int u, v;\n\
    \        cin >> u >> v;\n        tree.add_edge(u, v);\n    }\n    tree.build_patable(0);\n\
    \    while (q--) {\n        int s, t, i;\n        cin >> s >> t >> i;\n      \
    \  if (i > tree.distance(s, t)) cout << \"-1\\n\";\n        else cout << tree.step(s,\
    \ t, i) << \"\\n\";\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - Tree/TreeTools.hpp
  - Tree/Tree.hpp
  - Graph/base.hpp
  - Graph/UnifiedWeight.hpp
  - Algebra/ValidOperation.hpp
  isVerificationFile: true
  path: test/1_library_checker/tree/jump_on_tree.test.cpp
  requiredBy: []
  timestamp: '2026-05-06 14:47:46+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/tree/jump_on_tree.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/tree/jump_on_tree.test.cpp
- /verify/test/1_library_checker/tree/jump_on_tree.test.cpp.html
title: test/1_library_checker/tree/jump_on_tree.test.cpp
---
