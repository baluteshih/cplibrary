---
title: Binary Indexed Tree (BIT)
documentation_of: ../../DataStructure/BIT.hpp
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
