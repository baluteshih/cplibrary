---
title: Dynamic Convex Hull
documentation_of: ../../../DataStructure/Convex/DynamicHull.hpp
---

A dynamic convex hull (often referred to as a line container or envelope) data structure. It maintains a set of linear functions $y = ax + b$ and supports adding new lines and querying the maximum value at a given $x$-coordinate:

$$f(x) = \max_i (a_i x + b_i)$$

*Note: This implementation only works for integer coordinates and coefficients.*

## Template Parameters

```cpp
template<typename T, T kInf = std::numeric_limits<T>::max() / 2>
struct DynamicHull;
```

* `T`: The coordinate and coefficient type (must be an integer type).
* `kInf`: A value representing infinity. Defaults to `std::numeric_limits<T>::max() / 2`).

---

## Nested Struct: Line<T>

```cpp
struct Line {
    mutable T a, b, p;
    bool operator<(const Line &rhs) const;
    bool operator<(T x) const;
};
```

Represents a line $y = ax + b$ inside the hull.
* `a`: The slope of the line.
* `b`: The y-intercept of the line.
* `p`: The intersection point (x-coordinate) up to which this line is the optimal (maximum) line.
* `operator<(const Line &rhs)`: Compares two lines by their slope `a`.
* `operator<(T x)`: Compares a line's intersection point `p` with an x-coordinate. Used internally for search.

---

## addline

```cpp
void addline(T a, T b);
```

* $O(\log N)$ amortized time, where $N$ is the number of lines.

Inserts a new line $y = ax + b$ into the convex hull, automatically removing any lines that become redundant or dominated by others.

---

## query

```cpp
T query(T x);
```

* $O(\log N)$ time, where $N$ is the number of lines.

Returns the maximum value $ax + b$ among all lines currently in the hull at the given integer coordinate $x$.
