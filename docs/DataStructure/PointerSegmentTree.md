---
title: Pointer Segment Tree
documentation_of: ../../DataStructure/PointerSegmentTree.hpp
---

A pointer-based Segment Tree that supports dynamic node allocation, persistence, and various optimizations like tag permanentization.

## Template Parameters

```cpp
template<
    typename Value = int, 
    typename Tag = void, 
    bool pushdown = true, 
    template<typename> class Allocator = DefaultAllocator, 
    bool dynamic = false, 
    bool persistent = false
>
class PointerSegmentTree;
```

* `Value`: The type of elements.
    * Must support associative property `operator+` for merging two `Value` objects (commutative or non-commutative depending on usage).
    * Must have a default constructor `Value()` acting as the identity element.
* `Tag`: The type of lazy tags.
    * Must support `operator+` for tag composition (`Tag + Tag`) and applying to a value (`Value + Tag`).
    * Must have a default constructor `Tag()` acting as the identity tag.
* `pushdown`: If `true`, uses standard lazy propagation. If `false`, uses tag permanentization (requires commutative operations in some cases).
* `Allocator`: The allocator used for node management (e.g., `DefaultAllocator`, `PoolAllocator`, `StackPoolAllocator`).
* `dynamic`: If `true`, nodes are allocated only when needed (dynamic Segment Tree).
* `persistent`: If `true`, operations create new nodes to maintain previous versions (persistent Segment Tree).

---

## Constructor

```cpp
PointerSegmentTree(const vector<Value> &data);
PointerSegmentTree(int size); // requires !dynamic
PointerSegmentTree(int size = 0); // requires dynamic || persistent
```

* $O(N)$ for `vector` and `size` (non-dynamic) constructors.
* $O(1)$ for dynamic/persistent constructors.

---

## get

```cpp
Value get(int x);
```

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
void range_transform(int l, int r, const auto &tag);
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
* Return the found index; if not found, returns `r`.
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
* Return the found index; if not found, returns `l`.
* If `l` and `r` are not provided, searches the entire tree.

---

## range_copy

```cpp
void range_copy(int l, int r, PointerSegmentTree &other);
```

* Requires `pushdown && persistent`.
* $O(\log N)$ time

Copies the range `[l, r)` from `other` to this tree by sharing nodes.

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
