---
title: Discretization
documentation_of: ../../DataStructure/Discretization.hpp
---

A utility class for coordinate compression (discretization), allowing efficient mapping from values to $0$-indexed ranks and queries for intervals.

## Template Parameters

```cpp
template<typename T>
class Discretization;
```

* `T`: The type of elements being discretized.
    * Must support comparison operators like `<` and `==`.

---

## Constructor

```cpp
Discretization(const std::ranges::range auto &_vals);
```

* $O(N \log N)$ time, where $N$ is the number of elements in `_vals`.

Constructs a discretization object from a range of values. It sorts the range and removes duplicate elements.

---

## idx

```cpp
int idx(int x);
```

* $O(\log N)$ time

Returns the discretized index (rank) of the value `x`. Returns `-1` if `x` does not exist in the discretized values.

---

## safe_idx

```cpp
int safe_idx(int x);
```

* $O(\log N)$ time

Returns the discretized index of `x`. Triggers an assertion failure if `x` is not found.

---

## left_close

```cpp
int left_close(T x);
```

* $O(\log N)$ time

Returns the first index `i` such that `vals[i] >= x`. Corresponds to the starting index when dealing with a closed left interval `[x, ...)`.

---

## left_open

```cpp
int left_open(T x);
```

* $O(\log N)$ time

Returns the last index `i` such that `vals[i] <= x`. Corresponds to the starting index when dealing with a closed left interval `(x, ...)`.

---

## right_close

```cpp
int right_close(T x);
```

* $O(\log N)$ time

Returns the last index `i` such that `vals[i] <= x`. Corresponds to the ending index when dealing with a closed right interval `(..., x]`.

---

## right_open

```cpp
int right_open(T x);
```

* $O(\log N)$ time

Returns the first index `i` such that `vals[i] >= x`. Corresponds to the ending index when dealing with an open right interval `(..., x)`.

---

## operator[]

```cpp
const T& operator[](size_t index) const;
```

* $O(1)$ time

Returns the original value at the given discretized index.
