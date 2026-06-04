---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/BIT.hpp
    title: Binary Indexed Tree (BIT)
  - icon: ':heavy_check_mark:'
    path: DataStructure/Discretization.hpp
    title: Discretization
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set.test.cpp
    title: test/1_library_checker/data_structure/ordered_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/OrderedSet.hpp\"\n\n#line 2 \"DataStructure/Discretization.hpp\"\
    \n\ntemplate<typename T>\nclass Discretization {\n    std::vector<T> vals;\n \
    \   static std::vector<T> sort_and_unique(std::vector<T> _vals) {\n        std::ranges::sort(_vals);\n\
    \        _vals.erase(std::ranges::unique(_vals).begin(), _vals.end());\n     \
    \   return _vals;\n    }\npublic:\n    int idx(int x) {\n        auto it = ranges::lower_bound(vals,\
    \ x);\n        if (it == vals.end() || *it != x) return -1;\n        return it\
    \ - vals.begin();\n    }\n    int safe_idx(int x) {\n        int res = idx(x);\n\
    \        assert(res != -1);\n        return res;\n    }\n    Discretization(const\
    \ std::vector<T> &_vals): vals(sort_and_unique(_vals)) {}\n    int left_close(T\
    \ x) {\n        return std::ranges::lower_bound(vals, x) - vals.begin();\n   \
    \ }\n    int left_open(T x) {\n        return std::ranges::upper_bound(vals, x)\
    \ - vals.begin() - 1;\n    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(vals,\
    \ x) - vals.begin();\n    }\n    const T& operator[](size_t index) const {\n \
    \       return vals[index];\n    } \n};\n#line 2 \"DataStructure/BIT.hpp\"\n\n\
    template<class T>\nclass BIT { // 0-base\npublic:\n    int n;\n    T total_;\n\
    \    std::vector<T> bit;\n    BIT(int _n) : n(_n), total_(), bit(n + 1) {}\n \
    \   template<typename U>\n    BIT(const std::vector<U> &arr) : n(arr.size()),\
    \ total_(std::accumulate(arr.begin(), arr.end(), T())), bit(n + 1) {\n       \
    \ for (int x = 1; x <= n; ++x) {\n            bit[x] = arr[x - 1];\n         \
    \   int y = x - (x & -x);\n            for (int i = x - 1; i > y; i -= i & -i)\n\
    \                bit[x] = bit[x] + bit[i];\n        }\n    }\n    void modify(int\
    \ x, T v) {\n        total_ = total_ + v;\n        for (++x; x <= n; x += x &\
    \ -x)\n            bit[x] = bit[x] + v;\n    }\n    T prefix(int x) {\n      \
    \  T res = T();\n        for (++x; x; x -= x & -x)\n            res = res + bit[x];\n\
    \        return res;\n    }\n    T suffix(int x) requires requires(T x, T y) {\
    \ x - y; } {\n        return total_ - prefix(x - 1);\n    }\n    T range(int l,\
    \ int r) requires requires(T x, T y) { x - y; } { // [l, r)\n        if (l >=\
    \ r) return T();\n        T res = prefix(r - 1) - prefix(l - 1);\n        return\
    \ res;\n    }\n    int kth(int k) { // 0-base query\n        assert((n & (n -\
    \ 1)) == 0);\n        ++k;\n        int res = 0;\n        for (int i = n >> 1;\
    \ i >= 1; i >>= 1) {\n            if (bit[res + i] < k)\n                k -=\
    \ bit[res += i];\n        }\n        return res;\n    }\n    T total() {\n   \
    \     return total_;\n    }\n};\n#line 5 \"DataStructure/OrderedSet.hpp\"\n\n\
    template<class T>\nclass OrderedSet : public Discretization<T> {\n    std::vector<bool>\
    \ vis;\n    BIT<int> bit;\npublic:\n    OrderedSet(const std::vector<T> &_vals):\
    \ Discretization<T>(_vals), vis(_vals.size()), bit(std::bit_ceil(_vals.size()))\
    \ {}\n    bool insert(T x) {\n        x = this->safe_idx(x);\n        if (vis[x])\
    \ return false;\n        vis[x] = true;\n        bit.modify(x, 1);\n        return\
    \ true;\n    }\n    bool erase(T x) {\n        x = this->safe_idx(x);\n      \
    \  if (!vis[x]) return false;\n        vis[x] = false;\n        bit.modify(x,\
    \ -1);\n        return true;\n    }\n    bool exists(T x) {\n        x = this->idx(x);\n\
    \        if (x == -1) return false;\n        return vis[x]; \n    }\n    int size()\
    \ {\n        return bit.total();\n    }\n    int lt_count(T x) {\n        return\
    \ bit.prefix(this->right_open(x) - 1);\n    }\n    int leq_count(T x) {\n    \
    \    return bit.prefix(this->right_close(x));\n    }\n    int order(T x) {\n \
    \       return leq_count(x);\n    }\n    int kth(int k) { // 0-base query, return\
    \ 0-base index\n        if (size() <= k) return -1;\n        int res = bit.kth(k);\n\
    \        return res;\n    }\n    int leq(T x) { // return 0-base index\n     \
    \   int res = leq_count(x);\n        return res == 0 ? -1 : kth(res - 1);\n  \
    \  }\n    int geq(T x) { // return 0-base index\n        int res = lt_count(x);\n\
    \        return res == size() ? -1 : kth(res);\n    }\n};\n"
  code: "#pragma once\n\n#include \"DataStructure/Discretization.hpp\"\n#include \"\
    DataStructure/BIT.hpp\"\n\ntemplate<class T>\nclass OrderedSet : public Discretization<T>\
    \ {\n    std::vector<bool> vis;\n    BIT<int> bit;\npublic:\n    OrderedSet(const\
    \ std::vector<T> &_vals): Discretization<T>(_vals), vis(_vals.size()), bit(std::bit_ceil(_vals.size()))\
    \ {}\n    bool insert(T x) {\n        x = this->safe_idx(x);\n        if (vis[x])\
    \ return false;\n        vis[x] = true;\n        bit.modify(x, 1);\n        return\
    \ true;\n    }\n    bool erase(T x) {\n        x = this->safe_idx(x);\n      \
    \  if (!vis[x]) return false;\n        vis[x] = false;\n        bit.modify(x,\
    \ -1);\n        return true;\n    }\n    bool exists(T x) {\n        x = this->idx(x);\n\
    \        if (x == -1) return false;\n        return vis[x]; \n    }\n    int size()\
    \ {\n        return bit.total();\n    }\n    int lt_count(T x) {\n        return\
    \ bit.prefix(this->right_open(x) - 1);\n    }\n    int leq_count(T x) {\n    \
    \    return bit.prefix(this->right_close(x));\n    }\n    int order(T x) {\n \
    \       return leq_count(x);\n    }\n    int kth(int k) { // 0-base query, return\
    \ 0-base index\n        if (size() <= k) return -1;\n        int res = bit.kth(k);\n\
    \        return res;\n    }\n    int leq(T x) { // return 0-base index\n     \
    \   int res = leq_count(x);\n        return res == 0 ? -1 : kth(res - 1);\n  \
    \  }\n    int geq(T x) { // return 0-base index\n        int res = lt_count(x);\n\
    \        return res == size() ? -1 : kth(res);\n    }\n};\n"
  dependsOn:
  - DataStructure/Discretization.hpp
  - DataStructure/BIT.hpp
  isVerificationFile: false
  path: DataStructure/OrderedSet.hpp
  requiredBy: []
  timestamp: '2026-06-04 15:34:47+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/ordered_set.test.cpp
documentation_of: DataStructure/OrderedSet.hpp
layout: document
title: Ordered Set
---

An ordered set data structure that leverages offline discretization and a Binary Indexed Tree (BIT) to provide efficient element queries (such as counting, kth element, lower/upper bounds). It only supports elements present in the initial discretization list.

## Inheritance

`OrderedSet<T>` inherits from `Discretization<T>`.

## Template Parameters

```cpp
template<class T>
class OrderedSet : public Discretization<T>;
```

* `T`: The type of elements. Must satisfy the requirements of `Discretization<T>`.

---

## Constructor

```cpp
OrderedSet(const std::vector<T> &_vals);
```

* $O(N \log N)$ time, where $N$ is the number of elements in `_vals`.

Constructs an empty ordered set using the given array `_vals` as the universe of possible elements to be inserted later.

---

## insert

```cpp
bool insert(T x);
```

* $O(\log N)$ time

Inserts the value `x` into the set. Returns `true` if `x` was successfully inserted, or `false` if `x` was already present. `x` must exist in the original array `_vals`.

---

## erase

```cpp
bool erase(T x);
```

* $O(\log N)$ time

Erases the value `x` from the set. Returns `true` if `x` was successfully erased, or `false` if `x` was not present. `x` must exist in the original array `_vals`.

---

## exists

```cpp
bool exists(T x);
```

* $O(\log N)$ time

Returns `true` if `x` is currently in the set, and `false` otherwise.

---

## size

```cpp
int size();
```

* $O(1)$ time

Returns the number of elements currently in the set.

---

## lt_count

```cpp
int lt_count(T x);
```

* $O(\log N)$ time

Returns the number of elements in the set strictly less than `x`.

---

## leq_count

```cpp
int leq_count(T x);
```

* $O(\log N)$ time

Returns the number of elements in the set less than or equal to `x`.

---

## order

```cpp
int order(T x);
```

* $O(\log N)$ time

An alias for `leq_count(x)`. Returns the 1-based rank/order of `x` if `x` is in the set.

---

## kth

```cpp
int kth(int k);
```

* $O(\log N)$ time

Returns the $0$-based discretized index of the $(k+1)$-th smallest element in the set (i.e., pass $0$ for the minimum). Returns `-1` if $k \ge $ `size()`. To get the original value, use `operator[]` inherited from `Discretization`.

---

## leq

```cpp
int leq(T x);
```

* $O(\log N)$ time

Returns the discretized index of the largest element in the set that is $\le x$. Returns `-1` if no such element exists.

---

## geq

```cpp
int geq(T x);
```

* $O(\log N)$ time

Returns the discretized index of the smallest element in the set that is $\ge x$. Returns `-1` if no such element exists.
