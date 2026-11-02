---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_kth_smallest.test.cpp
    title: test/1_library_checker/data_structure/range_kth_smallest.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/PartitionTree.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate <typename A, typename B>\nconcept Addable = !std::is_void_v<A> &&\
    \ !std::is_void_v<B> && requires(A a, B b) { a + b; };\n\ntemplate <typename A,\
    \ typename B>\nconcept Subtractable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a - b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a * b; };\n\ntemplate <typename A, typename B>\nconcept AssignAddable =\
    \ !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a += b; };\n\
    \ntemplate <typename A, typename B>\nconcept AssignSubtractable = !std::is_void_v<A>\
    \ && !std::is_void_v<B> && requires(A a, B b) { a -= b; };\n#line 4 \"DataStructure/PartitionTree.hpp\"\
    \n\ntemplate <typename T = int, typename Value = void>\nclass PartitionTree {\n\
    private:\n    static constexpr bool hasValue = !std::is_void_v<Value>;\n    struct\
    \ Empty {};\n    using ValueType = std::conditional_t<hasValue, Value, Empty>;\n\
    \    static_assert(!hasValue || (Addable<Value, Value> && Subtractable<Value,\
    \ Value>));\n    int n, max_depth;\n    std::vector<T> sorted;\n    std::vector<std::vector<T>>\
    \ val;\n    std::vector<std::vector<int>> to_l;\n    [[no_unique_address]] std::conditional_t<hasValue,\
    \ std::vector<std::vector<ValueType>>, Empty> sum_l{};\n    void build(int d,\
    \ int l, int r) {\n        if (r - l <= 1) return;\n        int mid = l + (r -\
    \ l) / 2;\n        T median = sorted[mid];\n        int same = mid - l;\n    \
    \    for (int i = l; i < r; ++i)\n            if (val[d][i] < median)\n      \
    \          --same;\n        int lpos = l, rpos = mid;\n        for (int i = l;\
    \ i < r; ++i) {\n            to_l[d][i] = (i == l ? 0 : to_l[d][i - 1]);\n   \
    \         if constexpr (hasValue) sum_l[d][i] = (i == l ? ValueType{} : sum_l[d][i\
    \ - 1]);\n            bool go_left = false;\n            if (val[d][i] < median)\
    \ go_left = true;\n            else if (val[d][i] == median && same > 0) go_left\
    \ = true, --same;\n            if (go_left) {\n                val[d + 1][lpos++]\
    \ = val[d][i];\n                to_l[d][i]++;\n                if constexpr (hasValue)\
    \ sum_l[d][i] = sum_l[d][i] + val[d][i];\n            }\n            else val[d\
    \ + 1][rpos++] = val[d][i];\n        }\n        build(d + 1, l, mid);\n      \
    \  build(d + 1, mid, r);\n    }\n    T query_kth(int d, int l, int r, int ql,\
    \ int qr, int k) const {\n        if (r - l <= 1) return val[d][l];\n        int\
    \ mid = l + (r - l) / 2;\n        int cnt_prev = (ql == l ? 0 : to_l[d][ql - 1]);\n\
    \        int cnt_in = to_l[d][qr - 1] - cnt_prev;\n        if (k <= cnt_in) {\n\
    \            int next_l = l + cnt_prev;\n            int next_r = l + cnt_prev\
    \ + cnt_in;\n            return query_kth(d + 1, l, mid, next_l, next_r, k);\n\
    \        }\n        else {\n            int next_l = mid + (ql - l - cnt_prev);\n\
    \            int next_r = mid + (qr - l - cnt_prev - cnt_in);\n            return\
    \ query_kth(d + 1, mid, r, next_l, next_r, k - cnt_in);\n        }\n    }\n  \
    \  ValueType query_sum(int d, int l, int r, int ql, int qr, int k) const requires\
    \ (hasValue) {\n        if (k == 0) return ValueType{};\n        if (r - l <=\
    \ 1) return val[d][l];\n        int mid = l + (r - l) / 2;\n        int cnt_prev\
    \ = (ql == l ? 0 : to_l[d][ql - 1]);\n        int cnt_in = to_l[d][qr - 1] - cnt_prev;\n\
    \        if (k <= cnt_in) {\n            int next_l = l + cnt_prev;\n        \
    \    int next_r = l + cnt_prev + cnt_in;\n            return query_sum(d + 1,\
    \ l, mid, next_l, next_r, k);\n        }\n        else {\n            ValueType\
    \ sum_in = ValueType{};\n            if constexpr (hasValue) sum_in = sum_l[d][qr\
    \ - 1] - (ql == l ? ValueType{} : sum_l[d][ql - 1]);\n            int next_l =\
    \ mid + (ql - l - cnt_prev);\n            int next_r = mid + (qr - l - cnt_prev\
    \ - cnt_in);\n            return sum_in + query_sum(d + 1, mid, r, next_l, next_r,\
    \ k - cnt_in);\n        }\n    }\npublic:\n    PartitionTree() : n(0), max_depth(0)\
    \ {}\n    PartitionTree(const std::vector<T>& a) {\n        n = a.size();\n  \
    \      if (n == 0) return;\n        max_depth = std::__lg(n) + 2;\n        sorted\
    \ = a;\n        std::sort(sorted.begin(), sorted.end());\n        val.assign(max_depth,\
    \ std::vector<T>(n));\n        to_l.assign(max_depth, std::vector<int>(n, 0));\n\
    \        if constexpr (hasValue) sum_l.assign(max_depth, std::vector<ValueType>(n,\
    \ 0));\n        val[0] = a;\n        build(0, 0, n);\n    }\n    T kth_smallest(int\
    \ ql, int qr, int k) const {\n        assert(ql >= 0 && qr <= n && ql < qr);\n\
    \        assert(k >= 1 && k <= qr - ql);\n        return query_kth(0, 0, n, ql,\
    \ qr, k);\n    }\n    T kth_largest(int ql, int qr, int k) const {\n        int\
    \ total = qr - ql;\n        return kth_smallest(ql, qr, total - k + 1);\n    }\n\
    \    ValueType sum_k_smallest(int ql, int qr, int k) const requires (hasValue)\
    \ {\n        assert(ql >= 0 && qr <= n && ql <= qr);\n        if (k <= 0 || ql\
    \ == qr) return ValueType{};\n        k = std::min(k, qr - ql);\n        return\
    \ query_sum(0, 0, n, ql, qr, k);\n    }\n    ValueType sum_k_largest(int ql, int\
    \ qr, int k) const requires (hasValue) {\n        assert(ql >= 0 && qr <= n &&\
    \ ql <= qr);\n        if (k <= 0 || ql == qr) return ValueType{};\n        k =\
    \ std::min(k, qr - ql);\n        int total = qr - ql;\n        ValueType total_sum\
    \ = sum_k_smallest(ql, qr, total);\n        if (k == total) return total_sum;\n\
    \        return total_sum - sum_k_smallest(ql, qr, total - k);\n    }\n};\n"
  code: "#pragma once\n\n#include \"Algebra/ValidOperation.hpp\"\n\ntemplate <typename\
    \ T = int, typename Value = void>\nclass PartitionTree {\nprivate:\n    static\
    \ constexpr bool hasValue = !std::is_void_v<Value>;\n    struct Empty {};\n  \
    \  using ValueType = std::conditional_t<hasValue, Value, Empty>;\n    static_assert(!hasValue\
    \ || (Addable<Value, Value> && Subtractable<Value, Value>));\n    int n, max_depth;\n\
    \    std::vector<T> sorted;\n    std::vector<std::vector<T>> val;\n    std::vector<std::vector<int>>\
    \ to_l;\n    [[no_unique_address]] std::conditional_t<hasValue, std::vector<std::vector<ValueType>>,\
    \ Empty> sum_l{};\n    void build(int d, int l, int r) {\n        if (r - l <=\
    \ 1) return;\n        int mid = l + (r - l) / 2;\n        T median = sorted[mid];\n\
    \        int same = mid - l;\n        for (int i = l; i < r; ++i)\n          \
    \  if (val[d][i] < median)\n                --same;\n        int lpos = l, rpos\
    \ = mid;\n        for (int i = l; i < r; ++i) {\n            to_l[d][i] = (i ==\
    \ l ? 0 : to_l[d][i - 1]);\n            if constexpr (hasValue) sum_l[d][i] =\
    \ (i == l ? ValueType{} : sum_l[d][i - 1]);\n            bool go_left = false;\n\
    \            if (val[d][i] < median) go_left = true;\n            else if (val[d][i]\
    \ == median && same > 0) go_left = true, --same;\n            if (go_left) {\n\
    \                val[d + 1][lpos++] = val[d][i];\n                to_l[d][i]++;\n\
    \                if constexpr (hasValue) sum_l[d][i] = sum_l[d][i] + val[d][i];\n\
    \            }\n            else val[d + 1][rpos++] = val[d][i];\n        }\n\
    \        build(d + 1, l, mid);\n        build(d + 1, mid, r);\n    }\n    T query_kth(int\
    \ d, int l, int r, int ql, int qr, int k) const {\n        if (r - l <= 1) return\
    \ val[d][l];\n        int mid = l + (r - l) / 2;\n        int cnt_prev = (ql ==\
    \ l ? 0 : to_l[d][ql - 1]);\n        int cnt_in = to_l[d][qr - 1] - cnt_prev;\n\
    \        if (k <= cnt_in) {\n            int next_l = l + cnt_prev;\n        \
    \    int next_r = l + cnt_prev + cnt_in;\n            return query_kth(d + 1,\
    \ l, mid, next_l, next_r, k);\n        }\n        else {\n            int next_l\
    \ = mid + (ql - l - cnt_prev);\n            int next_r = mid + (qr - l - cnt_prev\
    \ - cnt_in);\n            return query_kth(d + 1, mid, r, next_l, next_r, k -\
    \ cnt_in);\n        }\n    }\n    ValueType query_sum(int d, int l, int r, int\
    \ ql, int qr, int k) const requires (hasValue) {\n        if (k == 0) return ValueType{};\n\
    \        if (r - l <= 1) return val[d][l];\n        int mid = l + (r - l) / 2;\n\
    \        int cnt_prev = (ql == l ? 0 : to_l[d][ql - 1]);\n        int cnt_in =\
    \ to_l[d][qr - 1] - cnt_prev;\n        if (k <= cnt_in) {\n            int next_l\
    \ = l + cnt_prev;\n            int next_r = l + cnt_prev + cnt_in;\n         \
    \   return query_sum(d + 1, l, mid, next_l, next_r, k);\n        }\n        else\
    \ {\n            ValueType sum_in = ValueType{};\n            if constexpr (hasValue)\
    \ sum_in = sum_l[d][qr - 1] - (ql == l ? ValueType{} : sum_l[d][ql - 1]);\n  \
    \          int next_l = mid + (ql - l - cnt_prev);\n            int next_r = mid\
    \ + (qr - l - cnt_prev - cnt_in);\n            return sum_in + query_sum(d + 1,\
    \ mid, r, next_l, next_r, k - cnt_in);\n        }\n    }\npublic:\n    PartitionTree()\
    \ : n(0), max_depth(0) {}\n    PartitionTree(const std::vector<T>& a) {\n    \
    \    n = a.size();\n        if (n == 0) return;\n        max_depth = std::__lg(n)\
    \ + 2;\n        sorted = a;\n        std::sort(sorted.begin(), sorted.end());\n\
    \        val.assign(max_depth, std::vector<T>(n));\n        to_l.assign(max_depth,\
    \ std::vector<int>(n, 0));\n        if constexpr (hasValue) sum_l.assign(max_depth,\
    \ std::vector<ValueType>(n, 0));\n        val[0] = a;\n        build(0, 0, n);\n\
    \    }\n    T kth_smallest(int ql, int qr, int k) const {\n        assert(ql >=\
    \ 0 && qr <= n && ql < qr);\n        assert(k >= 1 && k <= qr - ql);\n       \
    \ return query_kth(0, 0, n, ql, qr, k);\n    }\n    T kth_largest(int ql, int\
    \ qr, int k) const {\n        int total = qr - ql;\n        return kth_smallest(ql,\
    \ qr, total - k + 1);\n    }\n    ValueType sum_k_smallest(int ql, int qr, int\
    \ k) const requires (hasValue) {\n        assert(ql >= 0 && qr <= n && ql <= qr);\n\
    \        if (k <= 0 || ql == qr) return ValueType{};\n        k = std::min(k,\
    \ qr - ql);\n        return query_sum(0, 0, n, ql, qr, k);\n    }\n    ValueType\
    \ sum_k_largest(int ql, int qr, int k) const requires (hasValue) {\n        assert(ql\
    \ >= 0 && qr <= n && ql <= qr);\n        if (k <= 0 || ql == qr) return ValueType{};\n\
    \        k = std::min(k, qr - ql);\n        int total = qr - ql;\n        ValueType\
    \ total_sum = sum_k_smallest(ql, qr, total);\n        if (k == total) return total_sum;\n\
    \        return total_sum - sum_k_smallest(ql, qr, total - k);\n    }\n};\n"
  dependsOn:
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: DataStructure/PartitionTree.hpp
  requiredBy: []
  timestamp: '2026-11-02 12:47:57+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/range_kth_smallest.test.cpp
documentation_of: DataStructure/PartitionTree.hpp
layout: document
title: Partition Tree
---

A static data structure (similar to a Wavelet Matrix / Merge Sort Tree) that partitions an array by medians at each level of recursion. It answers range $k$-th smallest/largest queries and range sum of the $k$ smallest/largest elements in $O(\log N)$ time with $O(N \log N)$ time and space preprocessing.

## Template Parameters

```cpp
template <typename T = int, typename Value = void>
class PartitionTree;
```

* `T`: The type of elements in the array. Defaults to `int`.
    * Must support `operator<` and `operator==` for sorting and median partitioning.
* `Value`: The type used for aggregating sums of elements. Defaults to `void` if sum queries are not needed.
    * If not `void`, `Value` must support `operator+` (`Addable<Value, Value>`), `operator-` (`Subtractable<Value, Value>`), `Value + T`, and default initialization `Value{}` acting as the additive identity.

---

## Constructor

```cpp
PartitionTree();
PartitionTree(const std::vector<T>& a);
```

* $O(N \log N)$ time and $O(N \log N)$ space

Constructs a `PartitionTree` from the $0$-based array `a`.

---

## kth_smallest

```cpp
T kth_smallest(int ql, int qr, int k) const;
```

* `0 <= ql < qr <= n`
* `1 <= k <= qr - ql` ($1$-indexed)
* $O(\log N)$ time

Returns the $k$-th smallest element in the half-open subarray `[ql, qr)`.

---

## kth_largest

```cpp
T kth_largest(int ql, int qr, int k) const;
```

* `0 <= ql < qr <= n`
* `1 <= k <= qr - ql` ($1$-indexed)
* $O(\log N)$ time

Returns the $k$-th largest element in the half-open subarray `[ql, qr)`.

---

## sum_k_smallest

```cpp
Value sum_k_smallest(int ql, int qr, int k) const requires (!std::is_void_v<Value>);
```

* Requires `Value` not to be `void`.
* `0 <= ql <= qr <= n`
* $O(\log N)$ time

Returns the sum of the $k$ smallest elements in the half-open subarray `[ql, qr)`.
* If `k <= 0` or `ql == qr`, returns `Value{}`.
* If `k > qr - ql`, returns the sum of all elements in `[ql, qr)`.

---

## sum_k_largest

```cpp
Value sum_k_largest(int ql, int qr, int k) const requires (!std::is_void_v<Value>);
```

* Requires `Value` not to be `void`.
* `0 <= ql <= qr <= n`
* $O(\log N)$ time

Returns the sum of the $k$ largest elements in the half-open subarray `[ql, qr)`.
* If `k <= 0` or `ql == qr`, returns `Value{}`.
* If `k > qr - ql`, returns the sum of all elements in `[ql, qr)`.
