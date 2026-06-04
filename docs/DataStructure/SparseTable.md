---
title: Sparse Table
documentation_of: ../../DataStructure/SparseTable.hpp
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
