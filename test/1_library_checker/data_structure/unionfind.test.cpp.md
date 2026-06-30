---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/Monoid/concept.hpp
    title: Algebra/Monoid/concept.hpp
  - icon: ':question:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/DisjointSet.hpp
    title: Disjoint Set Union (DSU)
  - icon: ':question:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/unionfind.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n#line 2 \"assumption.hpp\"\
    \n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3 \"test/1_library_checker/data_structure/unionfind.test.cpp\"\
    \n\n#line 2 \"DataStructure/DisjointSet.hpp\"\n\n#line 2 \"Algebra/Monoid/concept.hpp\"\
    \n\n#line 2 \"Algebra/ValidOperation.hpp\"\n\ntemplate <typename A, typename B>\n\
    concept Addable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a + b; };\n\ntemplate <typename A, typename B>\nconcept Subtractable =\
    \ !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a - b; };\n\
    \ntemplate <typename A, typename B>\nconcept Multiplicable = !std::is_void_v<A>\
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
    \ result;\n    }\n};\n#line 5 \"test/1_library_checker/data_structure/unionfind.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    DisjointSet djs(n);\n    while (q--) {\n\
    \        int t, u, v;\n        std::cin >> t >> u >> v;\n        if (t == 0)\n\
    \            djs.merge(u, v);\n        else\n            std::cout << djs.same(u,\
    \ v) << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n#include \"\
    assumption.hpp\"\n\n#include \"DataStructure/DisjointSet.hpp\"\n\nint main() {\n\
    \    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    DisjointSet djs(n);\n    while (q--) {\n        int t, u, v;\n\
    \        std::cin >> t >> u >> v;\n        if (t == 0)\n            djs.merge(u,\
    \ v);\n        else\n            std::cout << djs.same(u, v) << \"\\n\";\n   \
    \ }\n}\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/DisjointSet.hpp
  - Algebra/Monoid/concept.hpp
  - Algebra/ValidOperation.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/unionfind.test.cpp
  requiredBy: []
  timestamp: '2026-06-30 17:38:58+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/unionfind.test.cpp
- /verify/test/1_library_checker/data_structure/unionfind.test.cpp.html
title: test/1_library_checker/data_structure/unionfind.test.cpp
---
