---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: DataStructure/OrderedSet.hpp
    title: Ordered Set
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set.test.cpp
    title: test/1_library_checker/data_structure/ordered_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_range_mode_query.test.cpp
    title: test/1_library_checker/data_structure/static_range_mode_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
    title: test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/Discretization.hpp\"\n\ntemplate<typename\
    \ T>\nclass Discretization {\n    std::vector<T> vals;\n    static std::vector<T>\
    \ sort_and_unique(std::vector<T> _vals) {\n        std::ranges::sort(_vals);\n\
    \        _vals.erase(std::ranges::unique(_vals).begin(), _vals.end());\n     \
    \   return _vals;\n    }\npublic:\n    int idx(T x) {\n        auto it = std::ranges::lower_bound(vals,\
    \ x);\n        if (it == vals.end() || *it != x) return -1;\n        return it\
    \ - vals.begin();\n    }\n    int safe_idx(T x) {\n        int res = idx(x);\n\
    \        assert(res != -1);\n        return res;\n    }\n    Discretization(const\
    \ std::vector<T> &_vals): vals(sort_and_unique(_vals)) {}\n    int left_close(T\
    \ x) {\n        return std::ranges::lower_bound(vals, x) - vals.begin();\n   \
    \ }\n    int left_open(T x) {\n        return std::ranges::upper_bound(vals, x)\
    \ - vals.begin() - 1;\n    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(vals,\
    \ x) - vals.begin();\n    }\n    const T& operator[](size_t index) const {\n \
    \       return vals[index];\n    }\n    int size() {\n        return vals.size();\n\
    \    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nclass Discretization {\n    std::vector<T>\
    \ vals;\n    static std::vector<T> sort_and_unique(std::vector<T> _vals) {\n \
    \       std::ranges::sort(_vals);\n        _vals.erase(std::ranges::unique(_vals).begin(),\
    \ _vals.end());\n        return _vals;\n    }\npublic:\n    int idx(T x) {\n \
    \       auto it = std::ranges::lower_bound(vals, x);\n        if (it == vals.end()\
    \ || *it != x) return -1;\n        return it - vals.begin();\n    }\n    int safe_idx(T\
    \ x) {\n        int res = idx(x);\n        assert(res != -1);\n        return\
    \ res;\n    }\n    Discretization(const std::vector<T> &_vals): vals(sort_and_unique(_vals))\
    \ {}\n    int left_close(T x) {\n        return std::ranges::lower_bound(vals,\
    \ x) - vals.begin();\n    }\n    int left_open(T x) {\n        return std::ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(vals,\
    \ x) - vals.begin();\n    }\n    const T& operator[](size_t index) const {\n \
    \       return vals[index];\n    }\n    int size() {\n        return vals.size();\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/Discretization.hpp
  requiredBy:
  - DataStructure/OrderedSet.hpp
  timestamp: '2026-06-19 13:11:38+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
  - test/1_library_checker/data_structure/static_range_mode_query.test.cpp
  - test/1_library_checker/data_structure/ordered_set.test.cpp
documentation_of: DataStructure/Discretization.hpp
layout: document
title: Discretization
---

A utility class for coordinate compression (discretization), allowing efficient mapping from values to $0$-indexed ranks and queries for intervals.

## Template Parameters

```cpp
template<typename T>
class Discretization;
```

* `T`: The type of elements being discretized.
    * Must support comparison operators like `<` and `==`.

---

## Constructor

```cpp
Discretization(const std::vector<T> &_vals);
```

* $O(N \log N)$ time, where $N$ is the number of elements in `_vals`.

Constructs a discretization object from an array of values. It sorts the array and removes duplicate elements.

---

## idx

```cpp
int idx(int x);
```

* $O(\log N)$ time

Returns the discretized index (rank) of the value `x`. Returns `-1` if `x` does not exist in the discretized values.

---

## safe_idx

```cpp
int safe_idx(int x);
```

* $O(\log N)$ time

Returns the discretized index of `x`. Triggers an assertion failure if `x` is not found.

---

## left_close

```cpp
int left_close(T x);
```

* $O(\log N)$ time

Returns the first index `i` such that `vals[i] >= x`. Corresponds to the starting index when dealing with a closed left interval `[x, ...)`.

---

## left_open

```cpp
int left_open(T x);
```

* $O(\log N)$ time

Returns the last index `i` such that `vals[i] <= x`. Corresponds to the starting index when dealing with a closed left interval `(x, ...)`.

---

## right_close

```cpp
int right_close(T x);
```

* $O(\log N)$ time

Returns the last index `i` such that `vals[i] <= x`. Corresponds to the ending index when dealing with a closed right interval `(..., x]`.

---

## right_open

```cpp
int right_open(T x);
```

* $O(\log N)$ time

Returns the first index `i` such that `vals[i] >= x`. Corresponds to the ending index when dealing with an open right interval `(..., x)`.

---

## operator[]

```cpp
const T& operator[](size_t index) const;
```

* $O(1)$ time

Returns the original value at the given discretized index.
