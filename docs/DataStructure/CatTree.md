---
title: Cat Tree
documentation_of: ../../DataStructure/CatTree.hpp
---

A $0$-based Cat Tree that supports static range queries in $O(1)$ time with $O(N \log N)$ preprocessing.

## Template Parameters

```cpp
template<typename Value = int>
class CatTree;
```

* `Value`: The type of elements stored in the tree.
    * Must support associative property `operator+` for merging two `Value` objects.
    * Must have a default constructor `Value()`.

---

## Constructor (Size)

```cpp
CatTree(int size);
```

* $O(N \log N)$ time, where $N$ is the smallest power of 2 greater than or equal to `size`.

Constructs a Cat Tree of given size, initialized with `Value()`.

---

## Constructor (Range)

```cpp
CatTree(const std::ranges::range auto &data);
```

* $O(N \log N)$ time

Constructs a Cat Tree from an existing range.

---

## range_prod

```cpp
Value range_prod(int l, int r);
```

* `l` and `r` are $0$-indexed, representing the half-open interval `[l, r)`.
* $O(1)$ time

Returns the product (sum) of the range `[l, r)`. Returns `Value()` if `l == r`.
