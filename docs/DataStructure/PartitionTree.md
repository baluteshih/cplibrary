---
title: Partition Tree
documentation_of: ../../DataStructure/PartitionTree.hpp
---

A static data structure (similar to a Wavelet Matrix / Merge Sort Tree) that partitions an array by medians at each level of recursion. It answers range $k$-th smallest/largest queries and range sum of the $k$ smallest/largest elements in $O(\log N)$ time with $O(N \log N)$ time and space preprocessing.

## Template Parameters

```cpp
template <typename T = int, typename Value = void>
class PartitionTree;
```

* `T`: The type of elements in the array. Defaults to `int`.
    * Must support `operator<` and `operator==` for sorting and median partitioning.
* `Value`: The type used for aggregating sums of elements. Defaults to `void` if sum queries are not needed.
    * If not `void`, `Value` must support `operator+` (`Addable<Value, Value>`), `operator-` (`Subtractable<Value, Value>`), `Value + T`, and default initialization `Value{}` acting as the additive identity.

---

## Constructor

```cpp
PartitionTree();
PartitionTree(const std::vector<T>& a);
```

* $O(N \log N)$ time and $O(N \log N)$ space

Constructs a `PartitionTree` from the $0$-based array `a`.

---

## kth_smallest

```cpp
T kth_smallest(int ql, int qr, int k) const;
```

* `0 <= ql < qr <= n`
* `1 <= k <= qr - ql` ($1$-indexed)
* $O(\log N)$ time

Returns the $k$-th smallest element in the half-open subarray `[ql, qr)`.

---

## kth_largest

```cpp
T kth_largest(int ql, int qr, int k) const;
```

* `0 <= ql < qr <= n`
* `1 <= k <= qr - ql` ($1$-indexed)
* $O(\log N)$ time

Returns the $k$-th largest element in the half-open subarray `[ql, qr)`.

---

## sum_k_smallest

```cpp
Value sum_k_smallest(int ql, int qr, int k) const requires (!std::is_void_v<Value>);
```

* Requires `Value` not to be `void`.
* `0 <= ql <= qr <= n`
* $O(\log N)$ time

Returns the sum of the $k$ smallest elements in the half-open subarray `[ql, qr)`.
* If `k <= 0` or `ql == qr`, returns `Value{}`.
* If `k > qr - ql`, returns the sum of all elements in `[ql, qr)`.

---

## sum_k_largest

```cpp
Value sum_k_largest(int ql, int qr, int k) const requires (!std::is_void_v<Value>);
```

* Requires `Value` not to be `void`.
* `0 <= ql <= qr <= n`
* $O(\log N)$ time

Returns the sum of the $k$ largest elements in the half-open subarray `[ql, qr)`.
* If `k <= 0` or `ql == qr`, returns `Value{}`.
* If `k > qr - ql`, returns the sum of all elements in `[ql, qr)`.
