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
    \ T>\nclass Discretization : public std::vector<T> {\npublic:\n    using std::vector<T>::vector;\n\
    \    virtual void build() {\n        std::ranges::sort(*this);\n        auto [first,\
    \ last] = std::ranges::unique(*this);\n        this->erase(first, last);\n   \
    \ }\n    int idx(T x) {\n        auto it = std::ranges::lower_bound(*this, x);\n\
    \        if (it == this->end() || *it != x) return -1;\n        return it - this->begin();\n\
    \    }\n    int safe_idx(T x) {\n        int res = idx(x);\n        assert(res\
    \ != -1);\n        return res;\n    }\n    int left_close(T x) {\n        return\
    \ std::ranges::lower_bound(*this, x) - this->begin();\n    }\n    int left_open(T\
    \ x) {\n        return std::ranges::upper_bound(*this, x) - this->begin() - 1;\n\
    \    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(*this,\
    \ x) - this->begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(*this,\
    \ x) - this->begin();\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nclass Discretization : public std::vector<T>\
    \ {\npublic:\n    using std::vector<T>::vector;\n    virtual void build() {\n\
    \        std::ranges::sort(*this);\n        auto [first, last] = std::ranges::unique(*this);\n\
    \        this->erase(first, last);\n    }\n    int idx(T x) {\n        auto it\
    \ = std::ranges::lower_bound(*this, x);\n        if (it == this->end() || *it\
    \ != x) return -1;\n        return it - this->begin();\n    }\n    int safe_idx(T\
    \ x) {\n        int res = idx(x);\n        assert(res != -1);\n        return\
    \ res;\n    }\n    int left_close(T x) {\n        return std::ranges::lower_bound(*this,\
    \ x) - this->begin();\n    }\n    int left_open(T x) {\n        return std::ranges::upper_bound(*this,\
    \ x) - this->begin() - 1;\n    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(*this,\
    \ x) - this->begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(*this,\
    \ x) - this->begin();\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/Discretization.hpp
  requiredBy:
  - DataStructure/OrderedSet.hpp
  timestamp: '2026-09-13 13:55:16+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/ordered_set.test.cpp
  - test/1_library_checker/data_structure/static_range_mode_query.test.cpp
  - test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
documentation_of: DataStructure/Discretization.hpp
layout: document
title: Discretization
---

A utility class for coordinate compression (discretization), allowing efficient mapping from values to $0$-indexed ranks and queries for intervals.

## Inheritance

`Discretization<T>` inherits publicly from `std::vector<T>`.

## Template Parameters

```cpp
template<typename T>
class Discretization : public std::vector<T>;
```

* `T`: The type of elements being discretized.
    * Must support comparison operators like `<` and `==`.

---

## Constructors

```cpp
using std::vector<T>::vector;
```

Constructors are inherited from `std::vector<T>`. Elements can be initialized using any `std::vector` constructor (e.g. range iterator constructor, default constructor, initializer list) or pushed directly into the container before calling `build()`.

---

## build

```cpp
virtual void build();
```

* $O(N \log N)$ time, where $N$ is the number of elements in the container.

Sorts the underlying elements (`std::ranges::sort`) and removes duplicates (`std::ranges::unique`). Must be called after populating elements and prior to performing any discretization queries.

---

## idx

```cpp
int idx(T x);
```

* $O(\log N)$ time

Returns the discretized index (rank) of the value `x`. Returns `-1` if `x` does not exist in the discretized values.

---

## safe_idx

```cpp
int safe_idx(T x);
```

* $O(\log N)$ time

Returns the discretized index of `x`. Triggers an assertion failure if `x` is not found.

---

## left_close

```cpp
int left_close(T x);
```

* $O(\log N)$ time

Returns the first index `i` such that `(*this)[i] >= x`. Corresponds to the starting index when dealing with a closed left interval `[x, ...)`.

---

## left_open

```cpp
int left_open(T x);
```

* $O(\log N)$ time

Returns the last index `i` such that `(*this)[i] <= x`. Corresponds to the starting index when dealing with an open left interval `(x, ...)`.

---

## right_close

```cpp
int right_close(T x);
```

* $O(\log N)$ time

Returns the last index `i` such that `(*this)[i] <= x`. Corresponds to the ending index when dealing with a closed right interval `(..., x]`.

---

## right_open

```cpp
int right_open(T x);
```

* $O(\log N)$ time

Returns the first index `i` such that `(*this)[i] >= x`. Corresponds to the ending index when dealing with an open right interval `(..., x)`.

---

## Inherited std::vector Methods

Because `Discretization<T>` inherits from `std::vector<T>`, all standard `std::vector` member functions (e.g., `operator[]`, `size()`, `push_back()`, `empty()`, iterators) are directly accessible.

