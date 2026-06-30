---
title: Disjoint Set Union (DSU)
documentation_of: ../../DataStructure/DisjointSet.hpp
---

A Disjoint Set Union (DSU) implementation with optional data storage and undo (roll-back) support.

## Template Parameters

```cpp
template<typename T = void, bool undo_tag = false>
class DisjointSet;
```

* `T`: The type of data stored in each component. Use `void` if no data is needed.
    * If provided, `T` must support commutative `operator+` for merging data of two components.
* `undo_tag`: If `true`, enables undo (roll-back) operations using a stack. Note that path compression is disabled when `undo_tag` is `true` to allow efficient roll-back.

---

## Constructor (Size)

```cpp
DisjointSet(int n);
```

* $O(N)$ time

Constructs a DSU with `n` elements, each in its own component.

---

## Constructor (Range)

```cpp
DisjointSet(const std::ranges::range auto &data);
```

* Requires `T` not to be `void`.
* $O(N)$ time

Constructs a DSU from an initial data range.

---

## leader

```cpp
int leader(int u);
```

* $O(\alpha(N))$ time (amortized) or $O(\log N)$ if `undo_tag` is `true`.

Returns the representative (leader) of the component containing `u`.

---

## size

```cpp
int size(int u);
```

* $O(\alpha(N))$ or $O(\log N)$ time.

Returns the number of elements in the component containing `u`.

---

## same

```cpp
bool same(int u, int v);
```

Returns `true` if `u` and `v` belong to the same component.

---

## merge

```cpp
bool merge(int u, int v, bool force = false);
```

Merges the components containing `u` and `v`. Returns `false` if they are already in the same component.  
If `T` is not `void`, the data is merged using `data[u] = data[u] + data[v]`.  
If `force` is `true`, the leader of the component of $v$ will be forced assigned to the leader of $u$.
* *Note: This will cause the complexity of path compression to degenerate to $O(1 + \log_{2 + m/n} n)$.*

---

## version & undo

```cpp
auto version();
void undo(auto req_version);
```

* Requires `undo_tag` to be `true`.

`version()` returns the current state version. `undo(req_version)` rolls back the DSU to the specified version.
* *Note: Currently, the return value is not fixed depending on whether `T` is `void`. Please use `auto` to capture the return value.*

---

## getdata

```cpp
auto& getdata(int u);
```

* Requires `T` not to be `void`.

Returns the data associated with the component containing `u`.

---

## data_transform

```cpp
void data_transform(int u, auto func);
```

* Requires `T` not to be `void`.
* `func` is a callable (e.g., lambda) that takes a `T&`.

Applies `func` to the data of the component containing `u`. If `undo_tag` is `true`, the operation is recorded for roll-back.

---

## groups

```cpp
std::vector<std::vector<int>> groups();
```

Returns all components as a list of lists of elements.
