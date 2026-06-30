---
title: Ordered Set
documentation_of: ../../DataStructure/OrderedSet.hpp
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
OrderedSet(const std::ranges::range auto &_vals);
```

* $O(N \log N)$ time, where $N$ is the number of elements in `_vals`.

Constructs an empty ordered set using the given range `_vals` as the universe of possible elements to be inserted later.

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
