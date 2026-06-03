---
title: Segment Tree
documentation_of: ../../DataStructure/SegmentTree.hpp
---

A versatile, $0$-based Segment Tree supporting point/range updates and various queries including binary search and Segment Tree Beats.

## Template Parameters

```cpp
template<typename Value = int, typename Tag = void, bool pushdown = true>
class SegmentTree;
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
SegmentTree(int size);
```

* `size` is the number of elements.
* $O(N)$ time

Constructs a Segment Tree of given size, initialized with `Value()`.

---

## Constructor (Array)

```cpp
SegmentTree(const vector<Value> &data);
```

* $O(N)$ time

Constructs a Segment Tree from an existing array.

---

## get

```cpp
Value get(int x);
```

* `x` is $0$-indexed.
* $O(\log N)$ time

Returns the value at index `x`.

---

## range_prod

```cpp
Value range_prod(int l, int r);
```

* `l` and `r` are $0$-indexed, representing the half-open interval `[l, r)`.
* $O(\log N)$ time

Returns the product (sum) of the range `[l, r)`. Returns `Value()` if `l == r`.

---

## modify

```cpp
void modify(int x, const Value &v);
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

Applies `func(Value &node)` to the leaf node at index `x`.

---

## range_transform

```cpp
void range_transform(int l, int r, const Tag &tag);
```

* Requires `Tag` not to be `void`.
* $O(\log N)$ time

Applies the lazy tag `tag` to the range `[l, r)`.

---

## range_transform_beats

```cpp
void range_transform_beats(int l, int r, const auto &tag, const auto &tag_condition);
```

* Requires `Tag` not to be `void`.
* `tag_condition`
    * A callable (e.g., lambda) that takes a `Value&`
    * Return value: a `bool` value. `true` if the tag can be directly applied to a node's subtree.
* Amortized $O(\log^2 N)$ or $O(\log N)$ depending on different scenario.

Performs a "Segment Tree Beats" update on the range `[l, r)`.

---

## range_left_search

```cpp
int range_left_search(const auto &condition, int l = -1, int r = -1);
```

* $O(\log N)$ time
* `condition`
    * A callable (e.g., lambda) that takes a `Value&`.
    * Return value: a `bool` value. `true` if the target is located within the node's subtree.

Perform segment tree binary search within the range $[l, r)$ with left half first.
* If not found, returns `r`.
* If `l` and `r` are not provided, searches the entire tree.

---

## range_right_search

```cpp
int range_right_search(const auto &condition, int l = -1, int r = -1);
```

* $O(\log N)$ time
* `condition`
    * A callable (e.g., lambda) that takes a `Value&`.
    * Return value: a `bool` value. `true` if the target is located within the node's subtree.

Perform segment tree binary search within the range $(l, r]$ with right half first.
* If not found, returns `l`.
* If `l` and `r` are not provided, searches the entire tree.

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
