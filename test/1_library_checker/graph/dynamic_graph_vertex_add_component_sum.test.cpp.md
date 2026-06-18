---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: DataStructure/DisjointSet.hpp
    title: Disjoint Set Union (DSU)
  - icon: ':question:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
  bundledCode: "#line 1 \"test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <bits/stdc++.h>\n#line 3 \"test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp\"\
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
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    std::vector<long long> arr(n);\n    for\
    \ (long long &i : arr)\n        std::cin >> i;\n    DisjointSet<long long, true>\
    \ djs(arr);\n    std::vector<std::vector<std::array<int, 3>>> event(q << 2);\n\
    \n    auto add_event = [&](auto self, int L, int R, int l, int r, int rt, const\
    \ std::array<int, 3> &e) -> void {\n        if (L <= l && R >= r)\n          \
    \  return event[rt].push_back(e);\n        int mid = (l + r) >> 1;\n        if\
    \ (L <= mid) self(self, L, R, l, mid, rt << 1, e);\n        if (R > mid) self(self,\
    \ L, R, mid + 1, r, rt << 1 | 1, e);\n    };\n\n    std::vector<long long> ans;\n\
    \    std::map<std::pair<int, int>, int> vis;\n    for (int i = 0; i < q; ++i)\
    \ {\n        int type;\n        std::cin >> type;\n        if (type == 0) {\n\
    \            int u, v;\n            std::cin >> u >> v;\n            if (u > v)\
    \ std::swap(u, v);\n            vis[std::pair<int, int>(u, v)] = i;\n        }\n\
    \        else if (type == 1) {\n            int u, v;\n            std::cin >>\
    \ u >> v;\n            if (u > v) std::swap(u, v);\n            add_event(add_event,\
    \ vis[std::pair<int, int>(u, v)], i - 1, 0, q - 1, 1, std::array<int, 3>{0, u,\
    \ v});\n            vis.erase(std::pair<int, int>(u, v));\n        }\n       \
    \ else if (type == 2) {\n            int v, x;\n            std::cin >> v >> x;\n\
    \            add_event(add_event, i, q - 1, 0, q - 1, 1, std::array<int, 3>{1,\
    \ v, x});\n        }\n        else {\n            int v;\n            std::cin\
    \ >> v;\n            add_event(add_event, i, i, 0, q - 1, 1, std::array<int, 3>{2,\
    \ v, int(ans.size())});\n            ans.push_back(0);\n        }\n    }\n   \
    \ for (auto [p, t] : vis)\n        add_event(add_event, t, q - 1, 0, q - 1, 1,\
    \ std::array<int, 3>{0, p.first, p.second});\n\n    auto dq = [&](auto self, int\
    \ l, int r, int rt) -> void {\n        auto version = djs.version();\n       \
    \ std::vector<std::pair<int, int>> ask;\n        for (auto [type, a, b] : event[rt])\n\
    \            if (type == 0)\n                djs.merge(a, b);\n            else\
    \ if (type == 1)\n                djs.data_transform(a, [&](long long &x) {\n\
    \                    x += b; \n                });\n            else\n       \
    \         ask.emplace_back(a, b);\n        if (l == r) {\n            for (auto\
    \ [v, qid] : ask)\n                ans[qid] = djs.getdata(v);\n        }\n   \
    \     else {\n            int mid = (l + r) >> 1;\n            self(self, l, mid,\
    \ rt << 1);\n            self(self, mid + 1, r, rt << 1 | 1);\n        }\n   \
    \     djs.undo(version);\n    };\n    dq(dq, 0, q - 1, 1);\n    for (long long\
    \ &i : ans)\n        std::cout << i << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum\"\
    \n#include \"assumption.hpp\"\n\n#include \"DataStructure/DisjointSet.hpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n\
    \    std::cin >> n >> q;\n    std::vector<long long> arr(n);\n    for (long long\
    \ &i : arr)\n        std::cin >> i;\n    DisjointSet<long long, true> djs(arr);\n\
    \    std::vector<std::vector<std::array<int, 3>>> event(q << 2);\n\n    auto add_event\
    \ = [&](auto self, int L, int R, int l, int r, int rt, const std::array<int, 3>\
    \ &e) -> void {\n        if (L <= l && R >= r)\n            return event[rt].push_back(e);\n\
    \        int mid = (l + r) >> 1;\n        if (L <= mid) self(self, L, R, l, mid,\
    \ rt << 1, e);\n        if (R > mid) self(self, L, R, mid + 1, r, rt << 1 | 1,\
    \ e);\n    };\n\n    std::vector<long long> ans;\n    std::map<std::pair<int,\
    \ int>, int> vis;\n    for (int i = 0; i < q; ++i) {\n        int type;\n    \
    \    std::cin >> type;\n        if (type == 0) {\n            int u, v;\n    \
    \        std::cin >> u >> v;\n            if (u > v) std::swap(u, v);\n      \
    \      vis[std::pair<int, int>(u, v)] = i;\n        }\n        else if (type ==\
    \ 1) {\n            int u, v;\n            std::cin >> u >> v;\n            if\
    \ (u > v) std::swap(u, v);\n            add_event(add_event, vis[std::pair<int,\
    \ int>(u, v)], i - 1, 0, q - 1, 1, std::array<int, 3>{0, u, v});\n           \
    \ vis.erase(std::pair<int, int>(u, v));\n        }\n        else if (type == 2)\
    \ {\n            int v, x;\n            std::cin >> v >> x;\n            add_event(add_event,\
    \ i, q - 1, 0, q - 1, 1, std::array<int, 3>{1, v, x});\n        }\n        else\
    \ {\n            int v;\n            std::cin >> v;\n            add_event(add_event,\
    \ i, i, 0, q - 1, 1, std::array<int, 3>{2, v, int(ans.size())});\n           \
    \ ans.push_back(0);\n        }\n    }\n    for (auto [p, t] : vis)\n        add_event(add_event,\
    \ t, q - 1, 0, q - 1, 1, std::array<int, 3>{0, p.first, p.second});\n\n    auto\
    \ dq = [&](auto self, int l, int r, int rt) -> void {\n        auto version =\
    \ djs.version();\n        std::vector<std::pair<int, int>> ask;\n        for (auto\
    \ [type, a, b] : event[rt])\n            if (type == 0)\n                djs.merge(a,\
    \ b);\n            else if (type == 1)\n                djs.data_transform(a,\
    \ [&](long long &x) {\n                    x += b; \n                });\n   \
    \         else\n                ask.emplace_back(a, b);\n        if (l == r) {\n\
    \            for (auto [v, qid] : ask)\n                ans[qid] = djs.getdata(v);\n\
    \        }\n        else {\n            int mid = (l + r) >> 1;\n            self(self,\
    \ l, mid, rt << 1);\n            self(self, mid + 1, r, rt << 1 | 1);\n      \
    \  }\n        djs.undo(version);\n    };\n    dq(dq, 0, q - 1, 1);\n    for (long\
    \ long &i : ans)\n        std::cout << i << \"\\n\";\n}\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/DisjointSet.hpp
  isVerificationFile: true
  path: test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
  requiredBy: []
  timestamp: '2026-06-18 22:20:51+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
- /verify/test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp.html
title: test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
---
