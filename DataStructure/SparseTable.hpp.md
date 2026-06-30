---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/Doubling.hpp
    title: Doubling
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
    title: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/SparseTable.hpp\"\n\n#line 2 \"DataStructure/Doubling.hpp\"\
    \n\n#line 2 \"Algebra/ValidOperation.hpp\"\n\ntemplate <typename A, typename B>\n\
    concept Addable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a + b; };\n\ntemplate <typename A, typename B>\nconcept Subtractable =\
    \ !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a - b; };\n\
    \ntemplate <typename A, typename B>\nconcept Multiplicable = !std::is_void_v<A>\
    \ && !std::is_void_v<B> && requires(A a, B b) { a * b; };\n#line 4 \"DataStructure/Doubling.hpp\"\
    \n\ntemplate<class Value, bool ImplicitJump = false>\nclass Doubling {\n    struct\
    \ Empty {};\n    static constexpr bool hasValue = Addable<Value, Value>;\n   \
    \ static_assert(hasValue || !ImplicitJump);\n    inline int get_nxt(int j, int\
    \ i) const {\n        if constexpr (ImplicitJump) return std::min(n - 1, i + (1\
    \ << j));\n        else return nxt[j][i];\n    }\n    void build() {\n       \
    \ for (int j = 1; j < max_log; ++j)\n            for (int i = 0; i < n; ++i) {\n\
    \                if constexpr (!ImplicitJump) nxt[j][i] = nxt[j - 1][nxt[j - 1][i]];\n\
    \                if constexpr (hasValue) val[j][i] = val[j - 1][i] + val[j - 1][get_nxt(j\
    \ - 1, i)]; \n            }\n    }\npublic:\n    int n, max_log;\n    [[no_unique_address]]\
    \ std::conditional_t<ImplicitJump, Empty, std::vector<std::vector<int>>> nxt;\n\
    \    [[no_unique_address]] std::conditional_t<hasValue, std::vector<std::vector<Value>>,\
    \ Empty> val; \n    Doubling() : n(0), max_log(0) {}\n    Doubling(int _n, const\
    \ std::ranges::range auto &init_nxt) requires (!hasValue && !ImplicitJump) : n(_n),\
    \ max_log(std::bit_width(static_cast<unsigned int>(n)) + 1) { \n        nxt.assign(max_log,\
    \ std::vector<int>(n)); \n        std::ranges::copy(init_nxt, nxt[0].begin());\n\
    \        build(); \n    }\n    Doubling(int _n, const std::ranges::range auto\
    \ &init_val) requires (hasValue && ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned\
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
    \        return u;\n    }\n};\n#line 4 \"DataStructure/SparseTable.hpp\"\n\ntemplate<typename\
    \ Value = int>\nclass SparseTable {\n    int n;\n    Doubling<Value, true> table;\n\
    public:\n    SparseTable(const std::ranges::range auto &data) : n(data.size()),\
    \ table(n, data) {} \n    Value range_prod(int l, int r) {\n        assert(0 <=\
    \ l && r <= n);\n        assert(l <= r);\n        if (l == r) return Value();\n\
    \        int lg = std::__lg(r - l);\n        return table.val[lg][l] + table.val[lg][r\
    \ - (1 << lg)];\n    }\n};\n"
  code: "#pragma once\n\n#include \"DataStructure/Doubling.hpp\"\n\ntemplate<typename\
    \ Value = int>\nclass SparseTable {\n    int n;\n    Doubling<Value, true> table;\n\
    public:\n    SparseTable(const std::ranges::range auto &data) : n(data.size()),\
    \ table(n, data) {} \n    Value range_prod(int l, int r) {\n        assert(0 <=\
    \ l && r <= n);\n        assert(l <= r);\n        if (l == r) return Value();\n\
    \        int lg = std::__lg(r - l);\n        return table.val[lg][l] + table.val[lg][r\
    \ - (1 << lg)];\n    }\n};\n"
  dependsOn:
  - DataStructure/Doubling.hpp
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: DataStructure/SparseTable.hpp
  requiredBy: []
  timestamp: '2026-06-30 17:03:55+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
documentation_of: DataStructure/SparseTable.hpp
layout: document
title: Sparse Table
---

A Sparse Table that supports static range queries in $O(1)$ time with $O(N \log N)$ preprocessing. Typically used for idempotent operations like Range Minimum Query (RMQ).

## Template Parameters

```cpp
template<typename Value = int>
class SparseTable;
```

* `Value`: The type of elements.
    * Must support idempotent `operator+` for merging two `Value` objects. 

---

## Constructor

```cpp
SparseTable(const std::vector<Value> &data);
```

* $O(N \log N)$ time

Constructs a Sparse Table from an existing array.

---

## range_prod

```cpp
Value range_prod(int l, int r);
```

* `l` and `r` are $0$-indexed, representing the half-open interval `[l, r)`.
* $O(1)$ time

Returns the product (aggregation) of the range `[l, r)`. Returns `Value()` if `l == r`.
