---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/line_add_get_min.test.cpp
    title: test/1_library_checker/data_structure/line_add_get_min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/Convex/DynamicHull.hpp\"\n\ntemplate<typename\
    \ T>\nstruct Line {\n    mutable T a, b, p;\n    bool operator<(const Line &rhs)\
    \ const { return a < rhs.a; }\n    bool operator<(T x) const { return p < x; }\n\
    };\ntemplate<typename T, T kInf = std::numeric_limits<T>::max() / 2>\nstruct DynamicHull\
    \ : std::multiset<Line<T>, std::less<>> {\n    using iterator = std::multiset<Line<T>,\
    \ std::less<>>::iterator; \n    T Div(T a, T b) { return a / b - ((a ^ b) < 0\
    \ && a % b); }\n    bool isect(iterator x, iterator y) {\n        if (y == this->end())\
    \ { x->p = kInf; return 0; }\n        if (x->a == y->a) x->p = x->b > y->b ? kInf\
    \ : -kInf;\n        else x->p = Div(y->b - x->b, x->a - y->a);\n        return\
    \ x->p >= y->p;\n    }\n    void addline(T a, T b) {\n        auto z = this->emplace(a,\
    \ b, 0), y = z++, x = y;\n        while (isect(y, z)) z = this->erase(z);\n  \
    \      if (x != this->begin() && isect(--x, y)) isect(x, y = this->erase(y));\n\
    \        while ((y = x) != this->begin() && (--x)->p >= y->p) isect(x, this->erase(y));\n\
    \    }\n    T query(T x) {\n        auto l = *this->lower_bound(x);\n        return\
    \ l.a * x + l.b;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nstruct Line {\n    mutable T a, b,\
    \ p;\n    bool operator<(const Line &rhs) const { return a < rhs.a; }\n    bool\
    \ operator<(T x) const { return p < x; }\n};\ntemplate<typename T, T kInf = std::numeric_limits<T>::max()\
    \ / 2>\nstruct DynamicHull : std::multiset<Line<T>, std::less<>> {\n    using\
    \ iterator = std::multiset<Line<T>, std::less<>>::iterator; \n    T Div(T a, T\
    \ b) { return a / b - ((a ^ b) < 0 && a % b); }\n    bool isect(iterator x, iterator\
    \ y) {\n        if (y == this->end()) { x->p = kInf; return 0; }\n        if (x->a\
    \ == y->a) x->p = x->b > y->b ? kInf : -kInf;\n        else x->p = Div(y->b -\
    \ x->b, x->a - y->a);\n        return x->p >= y->p;\n    }\n    void addline(T\
    \ a, T b) {\n        auto z = this->emplace(a, b, 0), y = z++, x = y;\n      \
    \  while (isect(y, z)) z = this->erase(z);\n        if (x != this->begin() &&\
    \ isect(--x, y)) isect(x, y = this->erase(y));\n        while ((y = x) != this->begin()\
    \ && (--x)->p >= y->p) isect(x, this->erase(y));\n    }\n    T query(T x) {\n\
    \        auto l = *this->lower_bound(x);\n        return l.a * x + l.b;\n    }\n\
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/Convex/DynamicHull.hpp
  requiredBy: []
  timestamp: '2026-07-12 01:44:14+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/line_add_get_min.test.cpp
documentation_of: DataStructure/Convex/DynamicHull.hpp
layout: document
title: Dynamic Convex Hull
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
