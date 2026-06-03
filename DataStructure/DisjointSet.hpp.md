---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: DataStructure/PotentialDisjointSet.hpp
    title: DataStructure/PotentialDisjointSet.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/minimum_spanning_tree.hpp
    title: Graph/minimum_spanning_tree.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/unionfind.test.cpp
    title: test/1_library_checker/data_structure/unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/unionfind_with_potential.test.cpp
    title: test/1_library_checker/data_structure/unionfind_with_potential.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
    title: test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
    title: test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/incremental_scc.test.cpp
    title: test/1_library_checker/graph/incremental_scc.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/minimum_spanning_tree.test.cpp
    title: test/1_library_checker/graph/minimum_spanning_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/DisjointSet.hpp\"\n\ntemplate<typename T =\
    \ void, bool undo_tag = false>\nclass DisjointSet {\nprotected:\n    static constexpr\
    \ bool hasT = !std::is_same_v<T, void>;\n    int n;\n    std::vector<int> boss,\
    \ sz;\n    struct Empty {};\n    [[no_unique_address]] std::conditional_t<hasT,\
    \ std::vector<T>, Empty> data;\n    [[no_unique_address]] std::conditional_t<undo_tag,\
    \ std::vector<std::pair<int*, int>>, Empty> cache;\n    [[no_unique_address]]\
    \ std::conditional_t<undo_tag && hasT, std::vector<std::pair<T*, T>>, Empty> data_cache;\n\
    public:\n    DisjointSet(int n_): n(n_), boss(n), sz(n, 1) {\n        std::iota(boss.begin(),\
    \ boss.end(), 0);\n        if constexpr (hasT) data.resize(n);\n    }\n    DisjointSet(const\
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
    \ result;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T = void, bool undo_tag = false>\nclass\
    \ DisjointSet {\nprotected:\n    static constexpr bool hasT = !std::is_same_v<T,\
    \ void>;\n    int n;\n    std::vector<int> boss, sz;\n    struct Empty {};\n \
    \   [[no_unique_address]] std::conditional_t<hasT, std::vector<T>, Empty> data;\n\
    \    [[no_unique_address]] std::conditional_t<undo_tag, std::vector<std::pair<int*,\
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
    \ result;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/DisjointSet.hpp
  requiredBy:
  - DataStructure/PotentialDisjointSet.hpp
  - Graph/minimum_spanning_tree.hpp
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/graph/incremental_scc.test.cpp
  - test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
  - test/1_library_checker/graph/minimum_spanning_tree.test.cpp
  - test/1_library_checker/data_structure/unionfind.test.cpp
  - test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
  - test/1_library_checker/data_structure/unionfind_with_potential.test.cpp
documentation_of: DataStructure/DisjointSet.hpp
layout: document
title: Disjoint Set Union (DSU)
---

A Disjoint Set Union (DSU) implementation with optional data storage and undo (roll-back) support.

## Template Parameters

```cpp
template<typename T = void, bool undo_tag = false>
class DisjointSet;
```

* `T`: The type of data stored in each component. Use `void` if no data is needed.
    * If provided, `T` must support commutative `operator+` for merging data of two components.
* `undo_tag`: If `true`, enables undo (roll-back) operations using a stack. Note that path compression is disabled when `undo_tag` is `true` to allow efficient roll-back.

---

## Constructor (Size)

```cpp
DisjointSet(int n);
```

* $O(N)$ time

Constructs a DSU with `n` elements, each in its own component.

---

## Constructor (Array)

```cpp
DisjointSet(const std::vector<T> &data);
```

* Requires `T` not to be `void`.
* $O(N)$ time

Constructs a DSU from an initial data array.

---

## leader

```cpp
int leader(int u);
```

* $O(\alpha(N))$ time (amortized) or $O(\log N)$ if `undo_tag` is `true`.

Returns the representative (leader) of the component containing `u`.

---

## size

```cpp
int size(int u);
```

* $O(\alpha(N))$ or $O(\log N)$ time.

Returns the number of elements in the component containing `u`.

---

## same

```cpp
bool same(int u, int v);
```

Returns `true` if `u` and `v` belong to the same component.

---

## merge

```cpp
bool merge(int u, int v, bool force = false);
```

Merges the components containing `u` and `v`. Returns `false` if they are already in the same component.  
If `T` is not `void`, the data is merged using `data[u] = data[u] + data[v]`.  
If `force` is `true`, the leader of the component of $v$ will be forced assigned to the leader of $u$.
* *Note: This will cause the complexity of path compression to degenerate to $O(1 + \log_{2 + m/n} n)$.*

---

## version & undo

```cpp
auto version();
void undo(auto req_version);
```

* Requires `undo_tag` to be `true`.

`version()` returns the current state version. `undo(req_version)` rolls back the DSU to the specified version.
* *Note: Currently, the return value is not fixed depending on whether `T` is `void`. Please use `auto` to capture the return value.*

---

## getdata

```cpp
auto& getdata(int u);
```

* Requires `T` not to be `void`.

Returns the data associated with the component containing `u`.

---

## data_transform

```cpp
void data_transform(int u, auto func);
```

* Requires `T` not to be `void`.
* `func` is a callable (e.g., lambda) that takes a `T&`.

Applies `func` to the data of the component containing `u`. If `undo_tag` is `true`, the operation is recorded for roll-back.

---

## groups

```cpp
std::vector<std::vector<int>> groups();
```

Returns all components as a list of lists of elements.
