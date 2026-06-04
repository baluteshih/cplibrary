---
title: Potential Disjoint Set
documentation_of: ../../DataStructure/PotentialDisjointSet.hpp
---

An extension of Disjoint Set Union (DSU) that maintains potential (weight) differences between elements.

## Template Parameters

```cpp
template<typename P, typename T = void>
class PotentialDisjointSet;
```

* `P`: The type of potential values. Must support `operator+`, `operator-`, and default constructor `P()` as the zero value.
* `T`: The type of additional data stored in each set (passed to `DisjointSet`).

---

## Constructor

```cpp
PotentialDisjointSet(int n);
```

* $O(N)$ time

Constructs a Potential Disjoint Set with `n` elements, each in its own set with potential $0$.

---

## leader

```cpp
int leader(int u);
```

* Amortized $O(\alpha(N))$ time

Returns the representative of the set containing `u`, performing path compression and potential updates.

---

## merge

```cpp
bool merge(int u, int v, P pot, bool force = false);
```

* `pot`: The desired potential difference $p[u] - p[v] = pot$.
* `force`: If `true`, does not perform union-by-size (use with caution).
* Amortized $O(\alpha(N))$ time

Merges the sets containing `u` and `v` such that $p[u] - p[v] = pot$. Returns `false` if `u` and `v` are already in the same set.

---

## diff

```cpp
P diff(int u, int v);
```

* Amortized $O(\alpha(N))$ time

Returns the potential difference $p[u] - p[v]$. Requires `u` and `v` to be in the same set.

---

## Other Methods

Inherits methods like `same(u, v)` and `size(u)` from `DisjointSet`.
