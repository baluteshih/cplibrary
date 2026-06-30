---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/concept.hpp
    title: Algebra/Monoid/concept.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/size_value.hpp
    title: Algebra/size_value.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/DefaultAllocator.hpp
    title: Default Allocator
  - icon: ':heavy_check_mark:'
    path: DataStructure/DisjointSet.hpp
    title: Disjoint Set Union (DSU)
  - icon: ':heavy_check_mark:'
    path: DataStructure/LeftistTree.hpp
    title: Leftist Tree
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/directedmst.test.cpp
    title: test/1_library_checker/graph/directedmst.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Graph/minimum_arborescence.hpp\"\n\n#line 2 \"Graph/base.hpp\"\
    \n\ntemplate<bool directed = true, typename Edge = void, typename Vertex = void>\n\
    class Graph {\npublic:\n    static constexpr bool is_directed = directed;\n  \
    \  static constexpr bool hasEdgeWeight = !std::is_same_v<Edge, void>;\n    static\
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
    \ Vertex>::Graph;\n};\n#line 2 \"DataStructure/DisjointSet.hpp\"\n\n#line 2 \"\
    Algebra/Monoid/concept.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\n\ntemplate\
    \ <typename A, typename B>\nconcept Addable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a + b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Subtractable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b)\
    \ { a - b; };\n\ntemplate <typename A, typename B>\nconcept Multiplicable = !std::is_void_v<A>\
    \ && !std::is_void_v<B> && requires(A a, B b) { a * b; };\n#line 4 \"Algebra/Monoid/concept.hpp\"\
    \n\ntemplate<typename T>\nconcept isMonoid = Addable<T, T> && std::default_initializable<T>;\n\
    \ntemplate<typename T>\nconcept isCommutativeMonoid = isMonoid<T>;\n#line 4 \"\
    DataStructure/DisjointSet.hpp\"\n\ntemplate<typename T = void, bool undo_tag =\
    \ false>\nclass DisjointSet {\nprotected:\n    static constexpr bool hasT = isCommutativeMonoid<T>;\n\
    \    int n;\n    std::vector<int> boss, sz;\n    struct Empty {};\n    [[no_unique_address]]\
    \ std::conditional_t<hasT, std::vector<T>, Empty> data;\n    [[no_unique_address]]\
    \ std::conditional_t<undo_tag, std::vector<std::pair<int*, int>>, Empty> cache;\n\
    \    [[no_unique_address]] std::conditional_t<undo_tag && hasT, std::vector<std::pair<T*,\
    \ T>>, Empty> data_cache;\npublic:\n    DisjointSet(int n_): n(n_), boss(n), sz(n,\
    \ 1) {\n        std::iota(boss.begin(), boss.end(), 0);\n        if constexpr\
    \ (hasT) data.resize(n);\n    }\n    DisjointSet(const std::ranges::range auto\
    \ &data_) requires (hasT) : n(data_.size()), boss(n), sz(n, 1), data(data_) {\n\
    \        std::iota(boss.begin(), boss.end(), 0);\n    }\n    virtual int leader(int\
    \ u) {\n        if (boss[u] == u) return u;\n        if constexpr (undo_tag) return\
    \ leader(boss[u]);\n        else return boss[u] = leader(boss[u]);\n    }\n  \
    \  int size(int u) {\n        return sz[leader(u)];\n    }\n    bool same(int\
    \ u, int v) {\n        return leader(u) == leader(v);\n    }\n    bool merge(int\
    \ u, int v, bool force = false) {\n        u = leader(u), v = leader(v);\n   \
    \     if (u == v) return false;\n        if (sz[u] < sz[v] && !force) std::swap(u,\
    \ v);\n        if constexpr (undo_tag) {\n            cache.emplace_back(&boss[v],\
    \ boss[v]); \n            cache.emplace_back(&sz[u], sz[v]); \n            if\
    \ constexpr (hasT)\n                data_cache.emplace_back(&data[u], data[u]);\n\
    \        }\n        boss[v] = u;\n        sz[u] += sz[v];\n        if constexpr\
    \ (hasT) {\n            data[u] = data[u] + data[v]; \n        }\n        return\
    \ true;\n    }\n    size_t version() requires (undo_tag && !hasT) {\n        return\
    \ cache.size();\n    }\n    std::pair<size_t, size_t> version() requires (undo_tag\
    \ && hasT) {\n        return std::make_pair(cache.size(), data_cache.size());\n\
    \    }\n    void undo(auto req_version) requires (undo_tag) {\n        while (version()\
    \ != req_version) {\n            if constexpr (!hasT) {\n                *cache.back().first\
    \ = cache.back().second;\n                cache.pop_back();\n            }\n \
    \           else {\n                if (cache.size() > req_version.first) {\n\
    \                    *cache.back().first = cache.back().second;\n            \
    \        cache.pop_back();\n                }\n                else {\n      \
    \              *data_cache.back().first = data_cache.back().second;\n        \
    \            data_cache.pop_back();\n                }\n            }\n      \
    \  }\n    }\n    auto& getdata(int u) requires (hasT) {\n        return data[leader(u)];\n\
    \    }\n    void data_transform(int u, auto func) requires (hasT) {\n        auto\
    \ &cur = getdata(u);\n        if constexpr (undo_tag)\n            data_cache.emplace_back(&cur,\
    \ cur);\n        func(cur);\n    }\n    std::vector<std::vector<int>> groups()\
    \ {\n        std::vector<std::vector<int>> result(n);\n        for (int i = 0;\
    \ i < n; ++i)\n            result[leader(i)].push_back(i);\n        result.erase(remove_if(result.begin(),\
    \ result.end(), [](auto &g) { return g.empty(); }), result.end());\n        return\
    \ result;\n    }\n};\n#line 2 \"DataStructure/LeftistTree.hpp\"\n\n#line 2 \"\
    Algebra/size_value.hpp\"\n\nstruct size_v {\n    int sz;\n    size_v(int sz_ =\
    \ 0): sz(sz_) {}\n    size_v operator+(const size_v &rhs) const {\n        return\
    \ size_v(sz + rhs.sz);\n    }\n    int size() const {\n        return sz; \n \
    \   }\n    friend std::ostream& operator<<(std::ostream& os, const size_v &v)\
    \ {\n        os << v.sz;\n        return os;\n    }\n};\n#line 2 \"DataStructure/DefaultAllocator.hpp\"\
    \n\ntemplate<typename T>\nstruct DefaultAllocator {\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        return new T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { delete p; }\n};\n#line 6 \"DataStructure/LeftistTree.hpp\"\
    \n\ntemplate<typename Key = int,\n         typename Tag = void,\n         typename\
    \ Info = void,\n         template<typename> class Allocator = DefaultAllocator,\n\
    \         bool persistent = false\n>\nclass LeftistTree { \n    static constexpr\
    \ bool hasTag = !std::is_same_v<Tag, void>;\n    static constexpr bool hasInfo\
    \ = !std::is_same_v<Info, void>;\n    struct Empty {};\n    template <bool Condition,\
    \ typename T>\n    static auto get_default() {\n        if constexpr (Condition)\
    \ return T();\n        else return Empty{};\n    }\n    static_assert(!hasTag\
    \ || Addable<Key, Tag>);\n    struct node {\n        node *l = nullptr, *r = nullptr;\n\
    \        Key key;\n        [[no_unique_address]] std::conditional_t<hasTag, Tag,\
    \ Empty> lazy = get_default<hasTag, Tag>();\n        [[no_unique_address]] std::conditional_t<hasInfo,\
    \ Info, Empty> info = get_default<hasInfo, Info>();\n        int rank = 0;\n \
    \       void up() {\n            if (get_rank(r) > get_rank(l)) std::swap(r, l);\n\
    \            rank = get_rank(r) + 1;\n        }\n        void give_tag(const auto\
    \ &tag) requires (hasTag) {\n            key = key + tag;\n            lazy =\
    \ lazy + tag;\n        }\n        void down() requires (hasTag) {\n          \
    \  bool need_tag = false;\n            if constexpr (std::equality_comparable<Tag>)\
    \ need_tag = (lazy != Tag());\n            else need_tag = true;\n           \
    \ if (!need_tag) return;\n            if (l) {\n                if constexpr (persistent)\
    \ l = NodeAlloc::allocate(*l);\n                l->give_tag(lazy);\n         \
    \   }\n            if (r) {\n                if constexpr (persistent) r = NodeAlloc::allocate(*r);\n\
    \                r->give_tag(lazy);\n            }\n            lazy = Tag();\n\
    \        }\n        node() = default;\n        node(const auto &v) requires (!hasInfo)\
    \ : key(v) {}\n        node(const auto &k, const auto &v) requires (hasInfo) :\
    \ key(k), info(v) {}\n        friend std::ostream& operator<<(std::ostream& os,\
    \ const node &v) {\n            if constexpr (hasInfo) os << \"{key = \" << v.key\
    \ << \", info = \" << v.info << \"}\";\n            else os << v.key;\n      \
    \      return os;\n        }\n    };\n    using NodeAlloc = Allocator<node>;\n\
    \    node *root = nullptr;\n    int sz = 0;\n    static node *merge(node *left,\
    \ node *right) {\n        if (!left || !right) return left ? left : right;\n \
    \       if (right->key < left->key) std::swap(left, right);\n        if constexpr\
    \ (persistent) left = NodeAlloc::allocate(*left); \n        left->down();\n  \
    \      left->r = merge(left->r, right);\n        left->up();\n        return left;\n\
    \    }\n    void erase(node *&o) {\n        if constexpr (persistent) o = NodeAlloc::allocate(*o);\n\
    \        o->down();\n        node *tmp = o;\n        o = merge(o->l, o->r);\n\
    \        NodeAlloc::deallocate(tmp);\n    }\n    static void free(node *&ptr)\
    \ requires (!persistent) {\n        if (ptr == nullptr) return;\n        free(ptr->l);\n\
    \        free(ptr->r);\n        NodeAlloc::deallocate(ptr);\n        ptr = nullptr;\n\
    \    }\n    static int get_rank(node *p) { return p ? p->rank : -1; }\npublic:\n\
    \    LeftistTree() = default;\n    LeftistTree(node *root_) : root(root_) {}\n\
    \    LeftistTree(const auto &v) requires (!hasInfo) : root(NodeAlloc::allocate(v)),\
    \ sz(1) {}\n    LeftistTree(const auto &k, const auto &v) requires (hasInfo) :\
    \ root(NodeAlloc::allocate(k, v)), sz(1) {}\n    void destruct() requires (!persistent)\
    \ {\n        free(root);\n        sz = 0;\n    }\n    void transform(const auto\
    \ &tag) requires (hasTag) {\n        if (root) {\n            if constexpr (persistent)\
    \ root = NodeAlloc::allocate(*root);\n            root->give_tag(tag);\n     \
    \   }\n    }\n    void swap(LeftistTree &rhs) {\n        std::swap(root, rhs.root);\n\
    \        std::swap(sz, rhs.sz);\n    }\n    bool empty() {\n        return root\
    \ == nullptr;\n    }\n    int size() {\n        return sz;\n    }\n    void clear()\
    \ {\n        root = nullptr;\n        sz = 0;\n    }\n    Key top() {\n      \
    \  return root->key;\n    }\n    auto topinfo() requires (hasInfo) {\n       \
    \ return root->info;\n    }\n    void pop() {\n        erase(root);\n        --sz;\n\
    \    }\n    void join(LeftistTree &rhs) {\n        root = merge(root, rhs.root);\n\
    \        sz += rhs.sz;\n        rhs.clear();\n    }\n    template<typename...\
    \ Args>\n    void push(Args&&... args) {\n        root = merge(root, NodeAlloc::allocate(std::forward<Args>(args)...));\n\
    \        sz += 1;\n    }\n};\n#line 6 \"Graph/minimum_arborescence.hpp\"\n\n//\
    \ Return the index of spanning tree edges, return empty if no solution (takecare\
    \ of n = 1)\ntemplate<typename graph>\nstd::vector<int> minimum_arborescence(const\
    \ graph &G, int root) {\n    using T = graph::edge_value_type;\n    int n = G.n();\n\
    \    std::vector<LeftistTree<T, T, int>> heap(n * 2);\n    for (int i = 0; i <\
    \ G.m(); ++i)\n        heap[G.edge(i).to].push(G.edge(i).weight, i);\n    DisjointSet\
    \ dsu(n * 2);\n    std::vector<int> v(n * 2, -1), pa(n * 2, -1), r(n * 2);\n \
    \   v[root] = n + 1;\n    int pc = n;\n    for (int i = 0; i < n; ++i)\n     \
    \   if (v[i] == -1) {\n            for (int p = i; v[p] == -1 || v[p] == i; p\
    \ = dsu.leader(G.edge(r[p]).from)) {\n                if (v[p] == i) {\n     \
    \               int q = p; p = pc++;\n                    do {\n             \
    \           heap[q].transform(T(0) - heap[q].top());\n                       \
    \ pa[q] = p, dsu.merge(p, q, true), heap[p].join(heap[q]);\n                 \
    \   } while ((q = dsu.leader(G.edge(r[q]).from)) != p);\n                }\n \
    \               v[p] = i;\n                while (!heap[p].empty() && dsu.leader(G.edge(heap[p].topinfo()).from)\
    \ == p)\n                    heap[p].pop();\n                if (heap[p].empty())\
    \ return {}; // no solution\n                r[p] = heap[p].topinfo();\n     \
    \       }\n        }\n    std::vector<int> ans;\n    for (int i = pc - 1; i >=\
    \ 0; --i)\n        if (i != root && v[i] != n) {\n            for (int f = G.edge(r[i]).to;\
    \ ~f && v[f] != n; f = pa[f])\n                v[f] = n;\n            ans.push_back(r[i]);\n\
    \        }\n    return ans;\n}\n"
  code: "#pragma once\n\n#include \"Graph/base.hpp\"\n#include \"DataStructure/DisjointSet.hpp\"\
    \n#include \"DataStructure/LeftistTree.hpp\"\n\n// Return the index of spanning\
    \ tree edges, return empty if no solution (takecare of n = 1)\ntemplate<typename\
    \ graph>\nstd::vector<int> minimum_arborescence(const graph &G, int root) {\n\
    \    using T = graph::edge_value_type;\n    int n = G.n();\n    std::vector<LeftistTree<T,\
    \ T, int>> heap(n * 2);\n    for (int i = 0; i < G.m(); ++i)\n        heap[G.edge(i).to].push(G.edge(i).weight,\
    \ i);\n    DisjointSet dsu(n * 2);\n    std::vector<int> v(n * 2, -1), pa(n *\
    \ 2, -1), r(n * 2);\n    v[root] = n + 1;\n    int pc = n;\n    for (int i = 0;\
    \ i < n; ++i)\n        if (v[i] == -1) {\n            for (int p = i; v[p] ==\
    \ -1 || v[p] == i; p = dsu.leader(G.edge(r[p]).from)) {\n                if (v[p]\
    \ == i) {\n                    int q = p; p = pc++;\n                    do {\n\
    \                        heap[q].transform(T(0) - heap[q].top());\n          \
    \              pa[q] = p, dsu.merge(p, q, true), heap[p].join(heap[q]);\n    \
    \                } while ((q = dsu.leader(G.edge(r[q]).from)) != p);\n       \
    \         }\n                v[p] = i;\n                while (!heap[p].empty()\
    \ && dsu.leader(G.edge(heap[p].topinfo()).from) == p)\n                    heap[p].pop();\n\
    \                if (heap[p].empty()) return {}; // no solution\n            \
    \    r[p] = heap[p].topinfo();\n            }\n        }\n    std::vector<int>\
    \ ans;\n    for (int i = pc - 1; i >= 0; --i)\n        if (i != root && v[i] !=\
    \ n) {\n            for (int f = G.edge(r[i]).to; ~f && v[f] != n; f = pa[f])\n\
    \                v[f] = n;\n            ans.push_back(r[i]);\n        }\n    return\
    \ ans;\n}\n"
  dependsOn:
  - Graph/base.hpp
  - DataStructure/DisjointSet.hpp
  - Algebra/Monoid/concept.hpp
  - Algebra/ValidOperation.hpp
  - DataStructure/LeftistTree.hpp
  - Algebra/size_value.hpp
  - DataStructure/DefaultAllocator.hpp
  isVerificationFile: false
  path: Graph/minimum_arborescence.hpp
  requiredBy: []
  timestamp: '2026-06-30 20:37:16+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/graph/directedmst.test.cpp
documentation_of: Graph/minimum_arborescence.hpp
layout: document
redirect_from:
- /library/Graph/minimum_arborescence.hpp
- /library/Graph/minimum_arborescence.hpp.html
title: Graph/minimum_arborescence.hpp
---
