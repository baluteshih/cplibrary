---
title: Xor Basis
documentation_of: ../../DataStructure/XorBasis.hpp
---

A linear basis over $\mathbb{F}_2$ (XOR basis) supporting element insertion, minimum/maximum XOR queries, $k$-th smallest XOR sum queries via Reduced Row Echelon Form (RREF), range maximum XOR queries (sliding window / timestamp tracking), and essential element (bridge) identification via bitmask tracing.

## Template Parameters

```cpp
template <typename T, int MAX_BIT, bool MaintainPos = false, bool MaintainTrace = false>
struct XorBasis;

using Basis32 = XorBasis<uint32_t, 32>;
using Basis64 = XorBasis<uint64_t, 64>;
```

* `T`: Data type (typically `unsigned int`, `unsigned long long`, `uint32_t`, `uint64_t`, or `std::bitset<MAX_BIT>`).
* `MAX_BIT`: Maximum number of bits (e.g., `32` for 32-bit integers, `64` for 64-bit integers).
* `MaintainPos`: If `true`, enables timestamp/position tracking for sliding window (range) queries.
* `MaintainTrace`: If `true`, enables tracing to identify which original elements form each basis vector and whether an element is essential (a bridge) to maintain the current rank.
    * Automatically deduces the optimal mask type `TraceMask`: `uint32_t` if `MAX_BIT <= 32`, `uint64_t` if `MAX_BIT <= 64`, or `std::bitset<MAX_BIT>` otherwise.

---

## Member Variables

```cpp
std::array<T, MAX_BIT> basis{};
std::vector<T> rref;
std::array<int, MAX_BIT> pos{};         // Present only if MaintainPos is true
std::array<TraceMask, MAX_BIT> trace{}; // Present only if MaintainTrace is true
TraceMask non_basis_used_mask{};        // Present only if MaintainTrace is true
int sz = 0;
bool has_zero = false;
bool is_rebuilt = false;
```

* `basis`: Stores the basis vectors indexed by their highest set bit.
* `rref`: Stores the Reduced Row Echelon Form of the basis, populated on demand by `rebuild()` and used for `kth()` queries.
* `pos`: (When `MaintainPos` is `true`) Stores the index/timestamp of the element providing each basis bit, initialized to `-1`.
* `trace`: (When `MaintainTrace` is `true`) Tracks which original elements (by ID) XOR together to form each basis element.
* `non_basis_used_mask`: (When `MaintainTrace` is `true`) Tracks the bitwise OR union of traces from all non-basis elements that were reduced to `0` (marking those basis elements as replaceable).
* `sz`: Number of linearly independent elements currently in the basis.
* `has_zero`: `true` if any non-empty subset of inserted elements XORs to `0` (i.e., linearly dependent elements exist).
* `is_rebuilt`: Indicates whether `rref` is currently up-to-date.

---

## Constructor

```cpp
XorBasis();
```

* $O(\text{MAX\_BIT})$ time

Constructs an empty `XorBasis`. Initializes `basis` to `0`, `pos` to `-1` (if `MaintainPos` is `true`), and `trace` / `non_basis_used_mask` to `0` (if `MaintainTrace` is `true`).

---

## insert

```cpp
bool insert(T x, int p = 0, int id = -1);
```

* `x`: The value to insert.
* `p`: Position/timestamp of the element (used when `MaintainPos` is `true`).
* `id`: Unique identifier from `0` to `MAX_BIT - 1` (required when `MaintainTrace` is `true`).
* $O(\text{MAX\_BIT})$ time (or $O(\text{MAX\_BIT}^2 / w)$ when using `std::bitset`)

Inserts `x` into the XOR basis and invalidates any cached RREF state (`is_rebuilt = false`).
* Returns `true` if `x` is linearly independent and added to the basis; returns `false` if `x` can already be represented by existing basis elements (which sets `has_zero = true`).
* If `MaintainPos` is `true`, greedily swaps and keeps the element with the latest position/timestamp at higher bits so that suffix/range queries remain valid.
* If `MaintainTrace` is `true` and `x` reduces to `0`, all basis elements used to represent `x` are marked in `non_basis_used_mask` as replaceable.

---

## reduce

```cpp
T reduce(T x) const;
```

* $O(\text{MAX\_BIT})$ time

Returns the minimum value `x` can be reduced to by XORing with elements in the basis. If it returns `T{}` (`0`), `x` can be represented by the basis.

---

## can_represent

```cpp
bool can_represent(T x) const;
```

* $O(\text{MAX\_BIT})$ time

Returns `true` if `x` can be formed as the XOR sum of a subset of elements in the basis (i.e., `reduce(x) == T{}`).

---

## max_xor

```cpp
T max_xor(T initial = T{}) const;
```

* $O(\text{MAX\_BIT})$ time

Greedily finds and returns the maximum XOR sum achievable by XORing `initial` with a subset of the basis.

---

## max_xor_range

```cpp
T max_xor_range(int L, T initial = T{}) const requires (MaintainPos);
```

* Requires `MaintainPos` to be `true`.
* $O(\text{MAX\_BIT})$ time

Greedily finds and returns the maximum XOR sum achievable by XORing `initial` with a subset of elements added at or after position/timestamp `L` (`pos[i] >= L`).

---

## min_xor

```cpp
T min_xor() const;
```

* $O(\text{MAX\_BIT})$ time

Returns the minimum XOR sum achievable by a non-empty subset of the inserted elements.
* Returns `T{}` (`0`) if `has_zero` is `true` (linearly dependent elements exist) or if the basis is empty; otherwise returns the smallest basis vector.

---

## rebuild

```cpp
void rebuild();
```

* $O(\text{MAX\_BIT}^2)$ time

Converts `basis` into Reduced Row Echelon Form (RREF) and populates the `rref` vector in increasing order of pivot bits for `kth()` queries. Does nothing if `is_rebuilt` is already `true`.

---

## kth

```cpp
T kth(long long k);
```

* $O(\text{MAX\_BIT}^2)$ time on the first call after insertion (`rebuild()`), $O(\text{MAX\_BIT})$ time on subsequent calls.

Finds and returns the $k$-th smallest distinct XOR sum ($1$-indexed) achievable by a non-empty subset of inserted elements.
* If `has_zero` is `true` (i.e., `0` can be formed by a non-empty subset), `0` is considered the $1$-st smallest.
* Returns `T(-1)` if `k` is out of bounds.

---

## is_essential

```cpp
bool is_essential(int id) const requires (MaintainTrace);
```

* Requires `MaintainTrace` to be `true`.
* $O(\text{MAX\_BIT})$ time

Checks whether the original element with identifier `id` is strictly necessary (an unreplaceable bridge) to maintain the current rank (`sz`) of the basis.
* Returns `true` if `id` corresponds to a basis element that has never been used to reduce any non-basis element to `0`; returns `false` otherwise.

---

## Merge Operators (`operator+=`, `operator+`)

```cpp
XorBasis& operator+=(const XorBasis& rhs);
friend XorBasis operator+(XorBasis lhs, const XorBasis& rhs);
```

* $O(\text{MAX\_BIT}^2)$ time

Merges another `XorBasis` `rhs` into this basis by inserting all basis vectors of `rhs` and combining `has_zero`.
* *Note: Merging uses standard insertion (`insert(rhs.basis[i])`), so individual `pos` and `id` semantics from `rhs` are not preserved unless managed separately.*
