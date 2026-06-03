---
title: Zkw Segment Tree
documentation_of: ../../DataStructure/ZkwSegmentTree.hpp
---

An efficient, non-recursive (Zkw) $0$-based Segment Tree supporting point/range updates and range queries.

## Template Parameters

```cpp
template<typename Value = int, typename Tag = void, bool pushdown = true>
class ZkwSegmentTree;
```

* `Value`: The type of elements.
    * Must support associative property `operator+` for merging two `Value` objects (commutative or non-commutative depending on usage).
    * Must have a default constructor `Value()` acting as the identity element.
* `Tag`: The type of lazy tags. Use `void` if no lazy propagation is needed.
    * Must support `operator+` for tag composition (`Tag + Tag`) and applying to a value (`Value + Tag`).
    * Must have a default constructor `Tag()` acting as the identity tag.
* `pushdown`: If `true`, uses standard lazy propagation. If `false`, uses tag permanentization (requires commutative operations in some cases).

---

## Constructor (Size)

```cpp
ZkwSegmentTree(int size);
```

* $O(N)$ time

Constructs a Zkw Segment Tree of given size.

---

## Constructor (Array)

```cpp
ZkwSegmentTree(const vector<Value> &data);
```

* $O(N)$ time

Constructs a Zkw Segment Tree from an existing array.

---

## get

```cpp
Value get(int x);
```

* $O(\log N)$ if `Tag` is not `void`; $O(1)$ otherwise.

Returns the value at index `x`.

---

## range_prod

```cpp
Value range_prod(int l, int r);
```

* `l` and `r` are $0$-indexed, representing the half-open interval `[l, r)`.
* $O(\log N)$ time

Returns the product of the range `[l, r)`.

---

## modify

```cpp
void modify(int x, Value v);
```

* `x` is $0$-indexed.
* $O(\log N)$ time

Sets the value at index `x` to `v`.

---

## transform

```cpp
void transform(int x, const auto &func);
```

* `x` is $0$-indexed.
* `func` is a callable (e.g., lambda) that takes a `Value&`.
* $O(\log N)$ time

Applies `func` to the leaf node at index `x`.

---

## range_transform

```cpp
void range_transform(int l, int r, const Tag &tag);
```

* Requires `Tag` not to be `void`.
* $O(\log N)$ time

Applies the lazy tag `tag` to the range `[l, r)`.

---

## Debugging Methods

### printinfo
```cpp
void printinfo(int l, int r);
```
Prints detailed information (values and tags) for nodes covering the range `[l, r)`.

### printall
```cpp
void printall();
```
Prints information for all nodes in the Segment Tree.
