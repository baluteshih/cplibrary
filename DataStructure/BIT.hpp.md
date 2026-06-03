---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: DataStructure/OrderedSet.hpp
    title: DataStructure/OrderedSet.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/PointInAngle.hpp
    title: Geometry/PointInAngle.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set.test.cpp
    title: test/1_library_checker/data_structure/ordered_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/geometry/count_points_in_triangle.test.cpp
    title: test/1_library_checker/geometry/count_points_in_triangle.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
    title: test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
    title: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/BIT.hpp\"\n\ntemplate<class T>\nclass BIT\
    \ { // 0-base\npublic:\n    int n;\n    T total_;\n    std::vector<T> bit;\n \
    \   BIT(int _n) : n(_n), total_(), bit(n + 1) {}\n    template<typename U>\n \
    \   BIT(const std::vector<U> &arr) : n(arr.size()), total_(std::accumulate(arr.begin(),\
    \ arr.end(), T())), bit(n + 1) {\n        for (int x = 1; x <= n; ++x) {\n   \
    \         bit[x] = arr[x - 1];\n            int y = x - (x & -x);\n          \
    \  for (int i = x - 1; i > y; i -= i & -i)\n                bit[x] = bit[x] +\
    \ bit[i];\n        }\n    }\n    void modify(int x, T v) {\n        total_ = total_\
    \ + v;\n        for (++x; x <= n; x += x & -x)\n            bit[x] = bit[x] +\
    \ v;\n    }\n    T prefix(int x) {\n        T res = T();\n        for (++x; x;\
    \ x -= x & -x)\n            res = res + bit[x];\n        return res;\n    }\n\
    \    T suffix(int x) requires requires(T x, T y) { x - y; } {\n        return\
    \ total_ - prefix(x - 1);\n    }\n    T range(int l, int r) requires requires(T\
    \ x, T y) { x - y; } { // [l, r)\n        if (l >= r) return T();\n        T res\
    \ = prefix(r - 1) - prefix(l - 1);\n        return res;\n    }\n    int kth(int\
    \ k) { // 0-base query\n        assert((n & (n - 1)) == 0);\n        ++k;\n  \
    \      int res = 0;\n        for (int i = n >> 1; i >= 1; i >>= 1) {\n       \
    \     if (bit[res + i] < k)\n                k -= bit[res += i];\n        }\n\
    \        return res;\n    }\n    T total() {\n        return total_;\n    }\n\
    };\n"
  code: "#pragma once\n\ntemplate<class T>\nclass BIT { // 0-base\npublic:\n    int\
    \ n;\n    T total_;\n    std::vector<T> bit;\n    BIT(int _n) : n(_n), total_(),\
    \ bit(n + 1) {}\n    template<typename U>\n    BIT(const std::vector<U> &arr)\
    \ : n(arr.size()), total_(std::accumulate(arr.begin(), arr.end(), T())), bit(n\
    \ + 1) {\n        for (int x = 1; x <= n; ++x) {\n            bit[x] = arr[x -\
    \ 1];\n            int y = x - (x & -x);\n            for (int i = x - 1; i >\
    \ y; i -= i & -i)\n                bit[x] = bit[x] + bit[i];\n        }\n    }\n\
    \    void modify(int x, T v) {\n        total_ = total_ + v;\n        for (++x;\
    \ x <= n; x += x & -x)\n            bit[x] = bit[x] + v;\n    }\n    T prefix(int\
    \ x) {\n        T res = T();\n        for (++x; x; x -= x & -x)\n            res\
    \ = res + bit[x];\n        return res;\n    }\n    T suffix(int x) requires requires(T\
    \ x, T y) { x - y; } {\n        return total_ - prefix(x - 1);\n    }\n    T range(int\
    \ l, int r) requires requires(T x, T y) { x - y; } { // [l, r)\n        if (l\
    \ >= r) return T();\n        T res = prefix(r - 1) - prefix(l - 1);\n        return\
    \ res;\n    }\n    int kth(int k) { // 0-base query\n        assert((n & (n -\
    \ 1)) == 0);\n        ++k;\n        int res = 0;\n        for (int i = n >> 1;\
    \ i >= 1; i >>= 1) {\n            if (bit[res + i] < k)\n                k -=\
    \ bit[res += i];\n        }\n        return res;\n    }\n    T total() {\n   \
    \     return total_;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/BIT.hpp
  requiredBy:
  - DataStructure/OrderedSet.hpp
  - Geometry/PointInAngle.hpp
  timestamp: '2026-06-03 13:51:43+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/ordered_set.test.cpp
  - test/1_library_checker/geometry/count_points_in_triangle.test.cpp
  - test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
  - test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
  - test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
documentation_of: DataStructure/BIT.hpp
layout: document
title: Binary Indexed Tree (BIT)
---

A generic, $0$-based Binary Indexed Tree (Fenwick Tree) supporting point modifications, range queries, and binary lifting.

## Template Parameters

```cpp
template <class T>
class BIT;
```

* `T`: The type of elements stored in the BIT.
    * Must support commutative `operator+`.
    * Must have a default constructor `T()` (acting as the identity element, usually `0`).
    * To use `suffix()` and `range()`, `T` must also support `operator-`.
    * To use `kth()`, `T` must be a numeric type supporting `operator<` compared to `int`.

---

## Constructor (Size)

```cpp
BIT(int n);
```

* `n` is the size of the array.
* $O(N)$ time

Constructs an empty BIT of size `n` initialized with the default value of type `T` (usually `0`).

---

## Constructor (Array)

```cpp
template<typename U>
BIT(const std::vector<U> &arr);
```

* $O(N)$ time

Constructs a BIT from an existing array using an optimized linear-time build algorithm.

---

## modify

```cpp
void modify(int x, T v);
```

* `x` is specified as $0$-indexed.
* $O(\log N)$ time

Adds the value `v` to the element at index `x`. This also automatically updates the cached total sum.

---

## prefix

```cpp
T prefix(int x);
```

* `x` is specified as $0$-indexed.
* $O(\log N)$ time

Returns the prefix sum of `[0, x]`.

---

## suffix

```cpp
T suffix(int x);
```

* `x` is specified as $0$-indexed.
* $O(\log N)$ time

Returns the suffix sum of `[x, n-1]`.
*Note: Requires type `T` to support `operator-`.*

---

## range

```cpp
T range(int l, int r);
```

* `l` and `r` are specified as $0$-indexed.
* $O(\log N)$ time

Returns the sum of the half-open interval `[l, r)`. If $l \ge r$, it returns `T()`.
*Note: Requires type `T` to support `operator-`.*

---

## kth

```cpp
int kth(int k);
```

* `k` is specified as $0$-indexed (i.e., pass $k$ to query the $(k+1)$-th smallest value).
* $O(\log N)$ time

Finds the largest index whose prefix sum is less than or equal to `k` using binary lifting.
*Note: The initial size `n` must be a power of 2.*

---

## total

```cpp
T total();
```

* $O(1)$ time

Returns the sum of all elements currently in the BIT.
