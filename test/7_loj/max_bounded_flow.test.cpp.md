---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: Flow/Dinic.hpp
    title: Flow/Dinic.hpp
  - icon: ':x:'
    path: Flow/bounded_flow.hpp
    title: Flow/bounded_flow.hpp
  - icon: ':question:'
    path: Graph/base.hpp
    title: Graph/base.hpp
  - icon: ':question:'
    path: default_code.hpp
    title: default_code.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    IGNORE: ''
    IGNORE_IF_GCC: ''
    links:
    - https://loj.ac/p/116
  bundledCode: "#line 1 \"test/7_loj/max_bounded_flow.test.cpp\"\n#define PROBLEM\
    \ \"https://loj.ac/p/116\"\n#define IGNORE\n#line 2 \"default_code.hpp\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\ntypedef long long ll;\ntypedef pair<int,\
    \ int> pii;\ntypedef pair<ll, ll> pll;\n#define X first\n#define Y second\n#define\
    \ SZ(a) ((int)a.size())\n#define ALL(v) v.begin(), v.end()\ntemplate<class A,\
    \ class B>\nostream& operator<<(ostream& os, const pair<A, B> &a) {\n    os <<\
    \ \"(\" << a.first << \", \" << a.second << \")\";\n    return os;\n}\ntemplate\
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
    \ vals.end());\n}\n#line 4 \"test/7_loj/max_bounded_flow.test.cpp\"\n\n#line 2\
    \ \"Flow/bounded_flow.hpp\"\n\n#line 2 \"Flow/Dinic.hpp\"\n\n#line 2 \"Graph/base.hpp\"\
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
    #line 4 \"Flow/Dinic.hpp\"\n\ntemplate<typename T>\nstruct FlowWeight {\n    T\
    \ cap, flow;\n    FlowWeight() : cap(0), flow(0) {}\n    FlowWeight(T c, T f =\
    \ 0) : cap(c), flow(f) {}\n    friend ostream& operator<<(ostream& os, const FlowWeight\
    \ &v) {\n        os << \"[\" << v.cap << \", \" << v.flow << \"]\";\n        return\
    \ os;\n    }\n};\n\ntemplate<class T>\nclass Dinic : public Graph<true, FlowWeight<T>,\
    \ void> { // 0-base\npublic:\n    using super = Graph<true, FlowWeight<T>, void>;\n\
    \    std::vector<int> dis, cur;\n    T dfs(int u, T push_cap, int t) {\n     \
    \   if (u == t || push_cap == 0) return push_cap;\n        for (int &i = cur[u];\
    \ i < std::ssize(this->G[u]); ++i) {\n            auto [v, eid] = this->G[u][i];\n\
    \            auto &w = this->edges[eid].weight;\n            if (dis[v] == dis[u]\
    \ + 1 && w.cap > w.flow) {\n                T df = dfs(v, std::min(w.cap - w.flow,\
    \ push_cap), t);\n                if (df > T(0)) {\n                    w.flow\
    \ += df;\n                    this->edges[eid ^ 1].weight.flow -= df;\n      \
    \              return df;\n                }\n            }\n        }\n     \
    \   dis[u] = -1;\n        return 0;\n    }\n    bool bfs(int s, int t) {\n   \
    \     std::ranges::fill(dis, -1);\n        std::queue<int> q;\n        q.push(s);\n\
    \        dis[s] = 0;\n        while (!q.empty()) {\n            int u = q.front();\n\
    \            q.pop();\n            for (auto [v, eid] : this->G[u]) {\n      \
    \          auto &w = this->edges[eid].weight;\n                if (dis[v] == -1\
    \ && w.cap > w.flow) {\n                    dis[v] = dis[u] + 1;\n           \
    \         q.push(v);\n                }\n            }\n        }\n        return\
    \ dis[t] != -1;\n    }\n    Dinic(int _n) : super(_n), dis(_n), cur(_n) {}\n \
    \   void add_edge(int u, int v, T cap) {\n        super::add_edge(u, v, FlowWeight<T>(cap,\
    \ 0));\n        super::add_edge(v, u, FlowWeight<T>(0, 0));\n    }\n    T maxflow(int\
    \ s, int t) {\n        T flow = 0, df;\n        while (bfs(s, t)) {\n        \
    \    std::ranges::fill(cur, 0);\n            while ((df = dfs(s, std::numeric_limits<T>::max(),\
    \ t)) > 0)\n                flow += df;\n        }\n        return flow;\n   \
    \ }\n    std::vector<std::pair<T, std::vector<int>>> get_route(int s, int t) {\n\
    \        std::vector<std::pair<T, std::vector<int>>> res;\n        auto backup_edges\
    \ = this->edges; \n        for (auto &e : this->edges) {\n            if (e.weight.cap\
    \ > 0) e.weight.cap = e.weight.flow;\n            e.weight.flow = 0;\n       \
    \ }\n\n        std::vector<int> stk;\n        auto route = [&](auto self, int\
    \ u, T push_cap) -> T {\n            if (u == t || push_cap == 0) {\n        \
    \        if (push_cap > 0) stk.push_back(u);\n                return push_cap;\n\
    \            }\n            for (int &i = cur[u]; i < std::ssize(this->G[u]);\
    \ ++i) {\n                auto [v, eid] = this->G[u][i];\n                auto\
    \ &w = this->edges[eid].weight;\n                if (dis[v] == dis[u] + 1 && w.cap\
    \ > w.flow) {\n                    T df = self(self, v, std::min(w.cap - w.flow,\
    \ push_cap));\n                    if (df > 0) {\n                        w.flow\
    \ += df;\n                        stk.push_back(u);\n                        return\
    \ df;\n                    }\n                }\n            }\n            dis[u]\
    \ = -1;\n            return 0;\n        };\n\n        while (bfs(s, t)) {\n  \
    \          std::ranges::fill(cur, 0);\n            T df;\n            while ((df\
    \ = route(route, s, std::numeric_limits<T>::max())) > 0) {\n                std::ranges::reverse(stk);\n\
    \                res.emplace_back(df, stk);\n                stk.clear();\n  \
    \          }\n        }\n        \n        this->edges = std::move(backup_edges);\
    \ \n        return res;\n    }\n    void reset() {\n        for (auto &e : this->edges)\
    \ e.weight.flow = 0;\n    }\n    T get_flow(int s) {\n        T res = T();\n \
    \       for (auto [v, eid] : this->G[s])\n            res += this->edges[eid].weight.flow;\n\
    \        return res;\n    }\n};\n#line 4 \"Flow/bounded_flow.hpp\"\n\ntemplate<class\
    \ T>\nclass bounded_flow : public Dinic<T> { // 0-base\npublic:\n    using super\
    \ = Dinic<T>;\n    int real_n;\n    std::vector<T> cnt;\n    bounded_flow(int\
    \ _n) : super(_n + 2), real_n(_n), cnt(real_n + 2) {}\n    void add_edge(int u,\
    \ int v, T lcap, T rcap) {\n        cnt[u] -= lcap, cnt[v] += lcap;\n        super::super::add_edge(u,\
    \ v, FlowWeight<T>(rcap, lcap));\n        super::super::add_edge(v, u, FlowWeight<T>(0,\
    \ 0));\n    }\n    bool solve() {\n        T sum = 0;\n        int added_cnt =\
    \ 0;\n        bool res = true;\n        for (int i = 0; i < real_n; ++i)\n   \
    \         if (cnt[i] > 0)\n                super::add_edge(real_n, i, cnt[i]),\
    \ sum += cnt[i], ++added_cnt;\n            else if (cnt[i] < 0)\n            \
    \    super::add_edge(i, real_n + 1, -cnt[i]), ++added_cnt;\n        if (sum !=\
    \ this->maxflow(real_n, real_n + 1)) res = false;\n        while (added_cnt--)\
    \ this->pop_edge(), this->pop_edge();\n        return res;\n    }\n    bool solve(int\
    \ s, int t) {\n        super::add_edge(t, s, std::numeric_limits<T>::max());\n\
    \        bool res = solve();\n        this->pop_edge(), this->pop_edge();\n  \
    \      return res;\n    }\n};\n#line 6 \"test/7_loj/max_bounded_flow.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, m, s, t;\n\
    \    cin >> n >> m >> s >> t;\n    --s, --t;\n    bounded_flow<int> flow(n);\n\
    \    for (int i = 0; i < m; ++i) {\n        int u, v, l, r;\n        cin >> u\
    \ >> v >> l >> r;\n        --u, --v;\n        flow.add_edge(u, v, l, r);\n   \
    \ }\n    if (!flow.solve(s, t)) cout << \"please go home to sleep\\n\";\n    else\
    \ {\n        flow.maxflow(s, t);\n        cout << flow.get_flow(s) << \"\\n\"\
    ;\n    }\n}\n"
  code: "#define PROBLEM \"https://loj.ac/p/116\"\n#define IGNORE\n#include \"default_code.hpp\"\
    \n\n#include \"Flow/bounded_flow.hpp\"\n\nint main() {\n    ios::sync_with_stdio(0),\
    \ cin.tie(0);\n    int n, m, s, t;\n    cin >> n >> m >> s >> t;\n    --s, --t;\n\
    \    bounded_flow<int> flow(n);\n    for (int i = 0; i < m; ++i) {\n        int\
    \ u, v, l, r;\n        cin >> u >> v >> l >> r;\n        --u, --v;\n        flow.add_edge(u,\
    \ v, l, r);\n    }\n    if (!flow.solve(s, t)) cout << \"please go home to sleep\\\
    n\";\n    else {\n        flow.maxflow(s, t);\n        cout << flow.get_flow(s)\
    \ << \"\\n\";\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - Flow/bounded_flow.hpp
  - Flow/Dinic.hpp
  - Graph/base.hpp
  isVerificationFile: true
  path: test/7_loj/max_bounded_flow.test.cpp
  requiredBy: []
  timestamp: '2026-05-19 02:16:25+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/7_loj/max_bounded_flow.test.cpp
layout: document
redirect_from:
- /verify/test/7_loj/max_bounded_flow.test.cpp
- /verify/test/7_loj/max_bounded_flow.test.cpp.html
title: test/7_loj/max_bounded_flow.test.cpp
---
