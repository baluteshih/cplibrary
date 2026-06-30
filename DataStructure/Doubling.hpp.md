---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/Monoid/concept.hpp
    title: Algebra/Monoid/concept.hpp
  - icon: ':question:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: DataStructure/SparseTable.hpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: Tree/TreeTools.hpp
    title: Tree/TreeTools.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
    title: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/jump_on_tree.test.cpp
    title: test/1_library_checker/tree/jump_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/lca.test.cpp
    title: test/1_library_checker/tree/lca.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/Doubling.hpp\"\n\n#line 2 \"Algebra/Monoid/concept.hpp\"\
    \n\n#line 2 \"Algebra/ValidOperation.hpp\"\n\ntemplate <typename A, typename B>\n\
    concept Addable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a + b; };\n\ntemplate <typename A, typename B>\nconcept Subtractable =\
    \ !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a - b; };\n\
    \ntemplate <typename A, typename B>\nconcept Multiplicable = !std::is_void_v<A>\
    \ && !std::is_void_v<B> && requires(A a, B b) { a * b; };\n#line 4 \"Algebra/Monoid/concept.hpp\"\
    \n\ntemplate<typename T>\nconcept isMonoid = Addable<T, T> && std::default_initializable<T>;\n\
    \ntemplate<typename T>\nconcept isCommutativeMonoid = isMonoid<T>;\n#line 4 \"\
    DataStructure/Doubling.hpp\"\n\ntemplate<class Value, bool ImplicitJump = false>\n\
    class Doubling {\n    struct Empty {};\n    static constexpr bool hasValue = isMonoid<Value>;\n\
    \    static_assert(hasValue || !ImplicitJump);\n    inline int get_nxt(int j,\
    \ int i) const {\n        if constexpr (ImplicitJump) return std::min(n - 1, i\
    \ + (1 << j));\n        else return nxt[j][i];\n    }\n    void build() {\n  \
    \      for (int j = 1; j < max_log; ++j)\n            for (int i = 0; i < n; ++i)\
    \ {\n                if constexpr (!ImplicitJump) nxt[j][i] = nxt[j - 1][nxt[j\
    \ - 1][i]];\n                if constexpr (hasValue) val[j][i] = val[j - 1][i]\
    \ + val[j - 1][get_nxt(j - 1, i)]; \n            }\n    }\npublic:\n    int n,\
    \ max_log;\n    [[no_unique_address]] std::conditional_t<ImplicitJump, Empty,\
    \ std::vector<std::vector<int>>> nxt;\n    [[no_unique_address]] std::conditional_t<hasValue,\
    \ std::vector<std::vector<Value>>, Empty> val; \n    Doubling() : n(0), max_log(0)\
    \ {}\n    Doubling(int _n, const std::ranges::range auto &init_nxt) requires (!hasValue\
    \ && !ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned int>(n))\
    \ + 1) { \n        nxt.assign(max_log, std::vector<int>(n)); \n        std::ranges::copy(init_nxt,\
    \ nxt[0].begin());\n        build(); \n    }\n    Doubling(int _n, const std::ranges::range\
    \ auto &init_val) requires (hasValue && ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned\
    \ int>(n)) + 1) { \n        val.assign(max_log, std::vector<Value>(n)); \n   \
    \     std::ranges::copy(init_val, val[0].begin());\n        build(); \n    }\n\
    \    Doubling(int _n, const std::ranges::range auto &init_nxt, const std::ranges::range\
    \ auto &init_val) requires (hasValue && !ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned\
    \ int>(n)) + 1) { \n        nxt.assign(max_log, std::vector<int>(n)); \n     \
    \   val.assign(max_log, std::vector<Value>(n)); \n        std::ranges::copy(init_nxt,\
    \ nxt[0].begin());\n        std::ranges::copy(init_val, val[0].begin());\n   \
    \     build(); \n    }\n    template<typename F_cond>\n    int maximal_prefix(int\
    \ u, F_cond cond) {\n        if (!cond(u)) return -1;\n        for (int i = max_log\
    \ - 1; i >= 0; --i)\n            if (cond(get_nxt(i, u)))\n                u =\
    \ get_nxt(i, u);\n        return u;\n    }\n    template<typename F_cond>\n  \
    \  auto maximal_prefix_prod(int u, F_cond cond) requires (hasValue) {\n      \
    \  if (!cond(u)) return std::make_pair(Value(), -1);\n        Value res = Value();\n\
    \        for (int i = max_log - 1; i >= 0; --i)\n            if (cond(get_nxt(i,\
    \ u))) {\n                res = res + val[i][u];\n                u = get_nxt(i,\
    \ u);\n            }\n        return std::make_pair(res, u);\n    }\n    int step(int\
    \ u, int d) {\n        for (; d; d -= d & -d) u = get_nxt(std::__lg(d & -d), u);\n\
    \        return u;\n    }\n};\n"
  code: "#pragma once\n\n#include \"Algebra/Monoid/concept.hpp\"\n\ntemplate<class\
    \ Value, bool ImplicitJump = false>\nclass Doubling {\n    struct Empty {};\n\
    \    static constexpr bool hasValue = isMonoid<Value>;\n    static_assert(hasValue\
    \ || !ImplicitJump);\n    inline int get_nxt(int j, int i) const {\n        if\
    \ constexpr (ImplicitJump) return std::min(n - 1, i + (1 << j));\n        else\
    \ return nxt[j][i];\n    }\n    void build() {\n        for (int j = 1; j < max_log;\
    \ ++j)\n            for (int i = 0; i < n; ++i) {\n                if constexpr\
    \ (!ImplicitJump) nxt[j][i] = nxt[j - 1][nxt[j - 1][i]];\n                if constexpr\
    \ (hasValue) val[j][i] = val[j - 1][i] + val[j - 1][get_nxt(j - 1, i)]; \n   \
    \         }\n    }\npublic:\n    int n, max_log;\n    [[no_unique_address]] std::conditional_t<ImplicitJump,\
    \ Empty, std::vector<std::vector<int>>> nxt;\n    [[no_unique_address]] std::conditional_t<hasValue,\
    \ std::vector<std::vector<Value>>, Empty> val; \n    Doubling() : n(0), max_log(0)\
    \ {}\n    Doubling(int _n, const std::ranges::range auto &init_nxt) requires (!hasValue\
    \ && !ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned int>(n))\
    \ + 1) { \n        nxt.assign(max_log, std::vector<int>(n)); \n        std::ranges::copy(init_nxt,\
    \ nxt[0].begin());\n        build(); \n    }\n    Doubling(int _n, const std::ranges::range\
    \ auto &init_val) requires (hasValue && ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned\
    \ int>(n)) + 1) { \n        val.assign(max_log, std::vector<Value>(n)); \n   \
    \     std::ranges::copy(init_val, val[0].begin());\n        build(); \n    }\n\
    \    Doubling(int _n, const std::ranges::range auto &init_nxt, const std::ranges::range\
    \ auto &init_val) requires (hasValue && !ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned\
    \ int>(n)) + 1) { \n        nxt.assign(max_log, std::vector<int>(n)); \n     \
    \   val.assign(max_log, std::vector<Value>(n)); \n        std::ranges::copy(init_nxt,\
    \ nxt[0].begin());\n        std::ranges::copy(init_val, val[0].begin());\n   \
    \     build(); \n    }\n    template<typename F_cond>\n    int maximal_prefix(int\
    \ u, F_cond cond) {\n        if (!cond(u)) return -1;\n        for (int i = max_log\
    \ - 1; i >= 0; --i)\n            if (cond(get_nxt(i, u)))\n                u =\
    \ get_nxt(i, u);\n        return u;\n    }\n    template<typename F_cond>\n  \
    \  auto maximal_prefix_prod(int u, F_cond cond) requires (hasValue) {\n      \
    \  if (!cond(u)) return std::make_pair(Value(), -1);\n        Value res = Value();\n\
    \        for (int i = max_log - 1; i >= 0; --i)\n            if (cond(get_nxt(i,\
    \ u))) {\n                res = res + val[i][u];\n                u = get_nxt(i,\
    \ u);\n            }\n        return std::make_pair(res, u);\n    }\n    int step(int\
    \ u, int d) {\n        for (; d; d -= d & -d) u = get_nxt(std::__lg(d & -d), u);\n\
    \        return u;\n    }\n};\n"
  dependsOn:
  - Algebra/Monoid/concept.hpp
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: DataStructure/Doubling.hpp
  requiredBy:
  - Tree/TreeTools.hpp
  - DataStructure/SparseTable.hpp
  timestamp: '2026-06-30 17:38:58+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/tree/lca.test.cpp
  - test/1_library_checker/tree/jump_on_tree.test.cpp
  - test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
documentation_of: DataStructure/Doubling.hpp
layout: document
title: Doubling
---

The Doubling technique, also known as binary lifting, is a powerful method for efficiently answering queries about paths in a graph or sequences, especially when those queries involve "jumping" a certain number of steps. It precomputes jumps of powers of two to answer arbitrary jumps in logarithmic time.

## Template Parameters

```cpp
template<class Value, bool ImplicitJump = false>
class Doubling;
```

* `Value`: The type of value to be accumulated during jumps.
    * Use `void` for state-only usage.
    * Must support `operator+` for combining values and have a default constructor `Value()` representing an identity element.
* `ImplicitJump`: If `true`, the `nxt` (next state) array is not explicitly stored, and the jump is implicitly defined as `i + (1 << j)`. This is useful for problems where the next state is simply a fixed increment (e.g., jumping `k` steps forward in a sequence).

---

## Constructors

```cpp
Doubling(int n, const std::ranges::range auto &init_nxt); // Explicit Jumps, No Value
Doubling(int n, const std::ranges::range auto &init_val); // Implicit Jumps, With Value
Doubling(int n, const std::ranges::range auto &init_nxt, const std::ranges::range auto &init_val); // Explicit Jumps, With Value
```

* `n`: The number of states.
* `init_nxt`: A range (e.g., `std::vector<int>`) representing the next state for each `i` after 1 step. `init_nxt[i]` is the state after 1 jump from `i`.
* `init_val`: A range representing the value associated with a 1-step jump from each `i`.
* $O(N \log N)$ time for precomputation.

Initializes the Doubling structure.

---

## Methods

### step

```cpp
int step(int u, int d);
```

* `u`: The starting state.
* `d`: The number of steps to jump.
* $O(\log d)$ time

Returns the state reached by jumping `d` steps from `u`.

---

### maximal_prefix

```cpp
template<typename F_cond>
int maximal_prefix(int u, F_cond cond);
```

* `u`: The starting state.
* `cond`: A callable (e.g., lambda) that takes an `int` (state) and returns `bool`. It should return `true` if the condition is met for that state, and `false` otherwise. The `cond` must be monotonic (if `cond(x)` is true, then `cond(previous_state_from_x)` is also true).
* $O(\log N)$ time

Finds the furthest state `v` reachable from `u` such that `cond(v)` is true. If `cond(u)` is false, returns -1.

---

### maximal_prefix_prod

```cpp
template<typename F_cond>
std::pair<Value, int> maximal_prefix_prod(int u, F_cond cond);
```

* `u`: The starting state.
* `cond`: A callable (e.g., lambda) that takes an `int` (state) and returns `bool`. The condition must be monotonic.
* $O(\log N)$ time

Similar to `maximal_prefix`, but also returns the accumulated `Value` along the path to the furthest state `v` for which `cond(v)` is true. Returns a `std::pair<Value, int>` where the `Value` is the accumulated value and the `int` is the final state. If `cond(u)` is false, returns `std::make_pair(Value(), -1)`.
