---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/DisjointSet.hpp
    title: DataStructure/DisjointSet.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
  bundledCode: "#line 1 \"test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n#line 2 \"default_code.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace std;\n\
    typedef long long ll;\ntypedef pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n\
    #define X first\n#define Y second\n#define SZ(a) ((int)a.size())\n#define ALL(v)\
    \ v.begin(), v.end()\ntemplate<class A, class B>\nostream& operator<<(ostream&\
    \ os, const pair<A, B> &a) {\n    os << \"(\" << a.first << \", \" << a.second\
    \ << \")\";\n    return os;\n}\ntemplate <typename T>\nconcept PrintableContainer\
    \ = requires(T& a) {\n    a.begin();\n    a.end();\n} && !std::same_as<std::remove_cvref_t<T>,\
    \ std::string> &&\n     !std::same_as<std::remove_cvref_t<T>, std::string_view>\
    \ &&\n     !std::is_convertible_v<T, const char*>;\ntemplate <PrintableContainer\
    \ T>\nstd::ostream& operator<<(std::ostream& os, const T& a) {\n    os << \"[\
    \ \";\n    bool first = true;\n    for (const auto& item : a) {\n        if (!first)\
    \ os << \", \";\n        os << item;\n        first = false;\n    }\n    return\
    \ os << \" ]\";\n}\n#ifdef bbq\n#include <experimental/iterator>\n#define safe\
    \ cerr<<__PRETTY_FUNCTION__<<\" line \"<<__LINE__<<\" safe\\n\"\n#define sepline\
    \ sepline_() \n#define debug(a...) debug_(#a, a)\n#define orange(a...) orange_(#a,\
    \ a)\nvoid debug_(auto s, auto ...a) {\n    cerr << \"\\e[1;32m(\" << s << \"\
    ) = (\";\n    int f = 0;\n    (..., (cerr << (f++ ? \", \" : \"\") << a));\n \
    \   cerr << \")\\e[0m\\n\";\n}\nvoid orange_(auto s, auto L, auto R) {\n    cerr\
    \ << \"\\e[1;33m[ \" << s << \" ] = [ \";\n    using namespace experimental;\n\
    \    copy(L, R, make_ostream_joiner(cerr, \", \"));\n    cerr << \" ]\\e[0m\\\
    n\";\n}\nvoid sepline_(int length = 50) {\n    cerr << \"\\e[1;35m\";\n    cerr\
    \ << string(length, '=');\n    cerr << \"\\e[0m\\n\";\n}\n#else\n#define safe\
    \ ((void)0)\n#define sepline safe\n#define debug(...) safe\n#define orange(...)\
    \ safe\n#endif\n\nvoid chmax(auto &x, auto val) {\n    x = max(x, val);\n}\n\n\
    void chmin(auto &x, auto val) {\n    x = min(x, val);\n}\n\nvector<int> count_array(const\
    \ auto &container, int sz = -1) {\n    if (sz == -1) sz = *ranges::max_element(container)\
    \ + 1;\n    vector<int> res(sz);\n    for (auto x : container) ++res[x];\n   \
    \ return res;\n}\n\ntemplate<class T>\nvoid discretization(vector<T> &vals) {\n\
    \    ranges::sort(vals);\n    vals.erase(ranges::unique(vals).begin(), vals.end());\n\
    }\n#line 3 \"test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp\"\
    \n\n#line 2 \"DataStructure/DisjointSet.hpp\"\n\ntemplate<typename T = void, bool\
    \ undo_tag = false>\nclass DisjointSet {\nprotected:\n    static constexpr bool\
    \ hasT = !std::is_same_v<T, void>;\n    int n;\n    std::vector<int> boss, sz;\n\
    \    struct Empty {};\n    [[no_unique_address]] std::conditional_t<hasT, std::vector<T>,\
    \ Empty> data;\n    [[no_unique_address]] std::conditional_t<undo_tag, std::vector<std::pair<int*,\
    \ int>>, Empty> cache;\n    [[no_unique_address]] std::conditional_t<undo_tag\
    \ && hasT, std::vector<std::pair<T*, T>>, Empty> data_cache;\npublic:\n    DisjointSet(int\
    \ n_): n(n_), boss(n), sz(n, 1) {\n        std::iota(boss.begin(), boss.end(),\
    \ 0);\n        if constexpr (hasT) data.resize(n);\n    }\n    DisjointSet(const\
    \ std::vector<T> &data_) requires (hasT) : n(data_.size()), boss(n), sz(n, 1),\
    \ data(data_) {\n        std::iota(boss.begin(), boss.end(), 0);\n    }\n    virtual\
    \ int leader(int u) {\n        if (boss[u] == u) return u;\n        if constexpr\
    \ (undo_tag) return leader(boss[u]);\n        else return boss[u] = leader(boss[u]);\n\
    \    }\n    int size(int u) {\n        return sz[leader(u)];\n    }\n    bool\
    \ same(int u, int v) {\n        return leader(u) == leader(v);\n    }\n    bool\
    \ merge(int u, int v, bool force = false) {\n        u = leader(u), v = leader(v);\n\
    \        if (u == v) return false;\n        if (sz[u] < sz[v] && !force) std::swap(u,\
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
    \ result;\n    }\n};\n#line 5 \"test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n  \
    \  cin >> n >> q;\n    std::vector<ll> arr(n);\n    for (ll &i : arr)\n      \
    \  cin >> i;\n    DisjointSet<ll, true> djs(arr);\n    vector<vector<array<int,\
    \ 3>>> event(q << 2);\n\n    auto add_event = [&](auto self, int L, int R, int\
    \ l, int r, int rt, const array<int, 3> &e) -> void {\n        if (L <= l && R\
    \ >= r)\n            return event[rt].push_back(e);\n        int mid = (l + r)\
    \ >> 1;\n        if (L <= mid) self(self, L, R, l, mid, rt << 1, e);\n       \
    \ if (R > mid) self(self, L, R, mid + 1, r, rt << 1 | 1, e);\n    };\n\n    vector<ll>\
    \ ans;\n    map<pii, int> vis;\n    for (int i = 0; i < q; ++i) {\n        int\
    \ type;\n        cin >> type;\n        if (type == 0) {\n            int u, v;\n\
    \            cin >> u >> v;\n            if (u > v) swap(u, v);\n            vis[pii(u,\
    \ v)] = i;\n        }\n        else if (type == 1) {\n            int u, v;\n\
    \            cin >> u >> v;\n            if (u > v) swap(u, v);\n            add_event(add_event,\
    \ vis[pii(u, v)], i - 1, 0, q - 1, 1, array<int, 3>{0, u, v});\n            vis.erase(pii(u,\
    \ v));\n        }\n        else if (type == 2) {\n            int v, x;\n    \
    \        cin >> v >> x;\n            add_event(add_event, i, q - 1, 0, q - 1,\
    \ 1, array<int, 3>{1, v, x});\n        }\n        else {\n            int v;\n\
    \            cin >> v;\n            add_event(add_event, i, i, 0, q - 1, 1, array<int,\
    \ 3>{2, v, int(ans.size())});\n            ans.push_back(0);\n        }\n    }\n\
    \    for (auto [p, t] : vis)\n        add_event(add_event, t, q - 1, 0, q - 1,\
    \ 1, array<int, 3>{0, p.first, p.second});\n\n    auto dq = [&](auto self, int\
    \ l, int r, int rt) -> void {\n        auto version = djs.version();\n       \
    \ vector<pii> ask;\n        for (auto [type, a, b] : event[rt])\n            if\
    \ (type == 0)\n                djs.merge(a, b);\n            else if (type ==\
    \ 1)\n                djs.data_transform(a, [&](ll &x) {\n                   \
    \ x += b; \n                });\n            else\n                ask.emplace_back(a,\
    \ b);\n        if (l == r) {\n            for (auto [v, qid] : ask)\n        \
    \        ans[qid] = djs.getdata(v);\n        }\n        else {\n            int\
    \ mid = (l + r) >> 1;\n            self(self, l, mid, rt << 1);\n            self(self,\
    \ mid + 1, r, rt << 1 | 1);\n        }\n        djs.undo(version);\n    };\n \
    \   dq(dq, 0, q - 1, 1);\n    for (ll &i : ans)\n        cout << i << \"\\n\"\
    ;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n#include \"default_code.hpp\"\n\n#include \"DataStructure/DisjointSet.hpp\"\n\
    \nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n    cin\
    \ >> n >> q;\n    std::vector<ll> arr(n);\n    for (ll &i : arr)\n        cin\
    \ >> i;\n    DisjointSet<ll, true> djs(arr);\n    vector<vector<array<int, 3>>>\
    \ event(q << 2);\n\n    auto add_event = [&](auto self, int L, int R, int l, int\
    \ r, int rt, const array<int, 3> &e) -> void {\n        if (L <= l && R >= r)\n\
    \            return event[rt].push_back(e);\n        int mid = (l + r) >> 1;\n\
    \        if (L <= mid) self(self, L, R, l, mid, rt << 1, e);\n        if (R >\
    \ mid) self(self, L, R, mid + 1, r, rt << 1 | 1, e);\n    };\n\n    vector<ll>\
    \ ans;\n    map<pii, int> vis;\n    for (int i = 0; i < q; ++i) {\n        int\
    \ type;\n        cin >> type;\n        if (type == 0) {\n            int u, v;\n\
    \            cin >> u >> v;\n            if (u > v) swap(u, v);\n            vis[pii(u,\
    \ v)] = i;\n        }\n        else if (type == 1) {\n            int u, v;\n\
    \            cin >> u >> v;\n            if (u > v) swap(u, v);\n            add_event(add_event,\
    \ vis[pii(u, v)], i - 1, 0, q - 1, 1, array<int, 3>{0, u, v});\n            vis.erase(pii(u,\
    \ v));\n        }\n        else if (type == 2) {\n            int v, x;\n    \
    \        cin >> v >> x;\n            add_event(add_event, i, q - 1, 0, q - 1,\
    \ 1, array<int, 3>{1, v, x});\n        }\n        else {\n            int v;\n\
    \            cin >> v;\n            add_event(add_event, i, i, 0, q - 1, 1, array<int,\
    \ 3>{2, v, int(ans.size())});\n            ans.push_back(0);\n        }\n    }\n\
    \    for (auto [p, t] : vis)\n        add_event(add_event, t, q - 1, 0, q - 1,\
    \ 1, array<int, 3>{0, p.first, p.second});\n\n    auto dq = [&](auto self, int\
    \ l, int r, int rt) -> void {\n        auto version = djs.version();\n       \
    \ vector<pii> ask;\n        for (auto [type, a, b] : event[rt])\n            if\
    \ (type == 0)\n                djs.merge(a, b);\n            else if (type ==\
    \ 1)\n                djs.data_transform(a, [&](ll &x) {\n                   \
    \ x += b; \n                });\n            else\n                ask.emplace_back(a,\
    \ b);\n        if (l == r) {\n            for (auto [v, qid] : ask)\n        \
    \        ans[qid] = djs.getdata(v);\n        }\n        else {\n            int\
    \ mid = (l + r) >> 1;\n            self(self, l, mid, rt << 1);\n            self(self,\
    \ mid + 1, r, rt << 1 | 1);\n        }\n        djs.undo(version);\n    };\n \
    \   dq(dq, 0, q - 1, 1);\n    for (ll &i : ans)\n        cout << i << \"\\n\"\
    ;\n}\n"
  dependsOn:
  - default_code.hpp
  - DataStructure/DisjointSet.hpp
  isVerificationFile: true
  path: test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
- /verify/test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp.html
title: test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
---
