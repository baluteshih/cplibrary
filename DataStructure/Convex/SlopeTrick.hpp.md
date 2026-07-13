---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: DataStructure/Convex/ConjugateSlopeTrick.hpp
    title: Conjugate Slope Trick
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/3_yukicoder/1077.test.cpp
    title: test/3_yukicoder/1077.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/3_yukicoder/2114.test.cpp
    title: test/3_yukicoder/2114.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - "https://maspypy.com/slope-trick-1-\u89E3\u8AAC\u7DE8"
  bundledCode: "#line 2 \"DataStructure/Convex/SlopeTrick.hpp\"\n\n/*\nreference:\
    \ https://maspypy.com/slope-trick-1-\u89E3\u8AAC\u7DE8\n*/\n\ntemplate<typename\
    \ T, T INF = std::numeric_limits<T>::max() / 2>\nclass SlopeTrick {\n    using\
    \ min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;\n    using\
    \ max_heap = std::priority_queue<T>;\n    max_heap pq_l;\n    min_heap pq_r;\n\
    \    T min_f;\nprotected:\n    T top_l() const { return pq_l.empty() ? -INF :\
    \ pq_l.top() + add_l; }\n    T top_r() const { return pq_r.empty() ? INF : pq_r.top()\
    \ + add_r; }\n    T pop_l() { T res = top_l(); if (!pq_l.empty()) pq_l.pop();\
    \ return res; }\n    T pop_r() { T res = top_r(); if (!pq_r.empty()) pq_r.pop();\
    \ return res; }\n    void push_l(T a) { pq_l.push(a - add_l); }\n    void push_r(T\
    \ a) { pq_r.push(a - add_r); }\n    T add_l, add_r; \npublic:\n    SlopeTrick()\
    \ : min_f(), add_l(), add_r() {}\n    bool is_inf(T v) { return v >= INF || v\
    \ <= -INF; }\n    int size_l() { return pq_l.size(); }\n    int size_r() { return\
    \ pq_r.size(); }\n    int size() { return size_l() + size_r(); }\n    T top()\
    \ { return min_f; }\n    std::pair<T, T> top_interval() { return {top_l(), top_r()};\
    \ }\n    SlopeTrick& add_const(T a) { return min_f += a, *this; }\n    SlopeTrick&\
    \ add_x_minus_a(T a) {\n        min_f += std::max(T(0), top_l() - a);\n      \
    \  push_l(a), push_r(pop_l());\n        return *this;\n    }\n    SlopeTrick&\
    \ add_a_minus_x(T a) {\n        min_f += std::max(T(0), a - top_r());\n      \
    \  push_r(a), push_l(pop_r());\n        return *this;\n    }\n    SlopeTrick&\
    \ add_abs(T a) { return add_x_minus_a(a).add_a_minus_x(a); } \n    SlopeTrick&\
    \ add_linear(int a, T b) {\n        for (min_f += b; a > 0; --a) {\n         \
    \   T x = pop_l();\n            min_f += x, push_r(x);\n        }\n        for\
    \ (; a < 0; ++a) {\n            T x = pop_r();\n            min_f -= x, push_l(x);\n\
    \        }\n        return *this;\n    }\n    SlopeTrick& shift(T a) { return\
    \ add_l += a, add_r += a, *this; }\n    SlopeTrick& sliding_window_minimum(T a,\
    \ T b) {\n        assert(a <= b);\n        add_l += a, add_r += b;\n        return\
    \ *this;\n    }\n    SlopeTrick& prefix_min() { return min_heap().swap(pq_r),\
    \ *this; }\n    SlopeTrick& suffix_min() { return max_heap().swap(pq_l), *this;\
    \ }\n    T eval(T x) {\n        T res = min_f;\n        auto tl = pq_l; auto tr\
    \ = pq_r;\n        for (; !tl.empty(); tl.pop()) res += std::max(T(0), (tl.top()\
    \ + add_l) - x);\n        for (; !tr.empty(); tr.pop()) res += std::max(T(0),\
    \ x - (tr.top() + add_r));\n        return res;\n    }\n};\n"
  code: "#pragma once\n\n/*\nreference: https://maspypy.com/slope-trick-1-\u89E3\u8AAC\
    \u7DE8\n*/\n\ntemplate<typename T, T INF = std::numeric_limits<T>::max() / 2>\n\
    class SlopeTrick {\n    using min_heap = std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>>;\n    using max_heap = std::priority_queue<T>;\n    max_heap\
    \ pq_l;\n    min_heap pq_r;\n    T min_f;\nprotected:\n    T top_l() const { return\
    \ pq_l.empty() ? -INF : pq_l.top() + add_l; }\n    T top_r() const { return pq_r.empty()\
    \ ? INF : pq_r.top() + add_r; }\n    T pop_l() { T res = top_l(); if (!pq_l.empty())\
    \ pq_l.pop(); return res; }\n    T pop_r() { T res = top_r(); if (!pq_r.empty())\
    \ pq_r.pop(); return res; }\n    void push_l(T a) { pq_l.push(a - add_l); }\n\
    \    void push_r(T a) { pq_r.push(a - add_r); }\n    T add_l, add_r; \npublic:\n\
    \    SlopeTrick() : min_f(), add_l(), add_r() {}\n    bool is_inf(T v) { return\
    \ v >= INF || v <= -INF; }\n    int size_l() { return pq_l.size(); }\n    int\
    \ size_r() { return pq_r.size(); }\n    int size() { return size_l() + size_r();\
    \ }\n    T top() { return min_f; }\n    std::pair<T, T> top_interval() { return\
    \ {top_l(), top_r()}; }\n    SlopeTrick& add_const(T a) { return min_f += a, *this;\
    \ }\n    SlopeTrick& add_x_minus_a(T a) {\n        min_f += std::max(T(0), top_l()\
    \ - a);\n        push_l(a), push_r(pop_l());\n        return *this;\n    }\n \
    \   SlopeTrick& add_a_minus_x(T a) {\n        min_f += std::max(T(0), a - top_r());\n\
    \        push_r(a), push_l(pop_r());\n        return *this;\n    }\n    SlopeTrick&\
    \ add_abs(T a) { return add_x_minus_a(a).add_a_minus_x(a); } \n    SlopeTrick&\
    \ add_linear(int a, T b) {\n        for (min_f += b; a > 0; --a) {\n         \
    \   T x = pop_l();\n            min_f += x, push_r(x);\n        }\n        for\
    \ (; a < 0; ++a) {\n            T x = pop_r();\n            min_f -= x, push_l(x);\n\
    \        }\n        return *this;\n    }\n    SlopeTrick& shift(T a) { return\
    \ add_l += a, add_r += a, *this; }\n    SlopeTrick& sliding_window_minimum(T a,\
    \ T b) {\n        assert(a <= b);\n        add_l += a, add_r += b;\n        return\
    \ *this;\n    }\n    SlopeTrick& prefix_min() { return min_heap().swap(pq_r),\
    \ *this; }\n    SlopeTrick& suffix_min() { return max_heap().swap(pq_l), *this;\
    \ }\n    T eval(T x) {\n        T res = min_f;\n        auto tl = pq_l; auto tr\
    \ = pq_r;\n        for (; !tl.empty(); tl.pop()) res += std::max(T(0), (tl.top()\
    \ + add_l) - x);\n        for (; !tr.empty(); tr.pop()) res += std::max(T(0),\
    \ x - (tr.top() + add_r));\n        return res;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/Convex/SlopeTrick.hpp
  requiredBy:
  - DataStructure/Convex/ConjugateSlopeTrick.hpp
  timestamp: '2026-07-12 18:12:29+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/3_yukicoder/2114.test.cpp
  - test/3_yukicoder/1077.test.cpp
documentation_of: DataStructure/Convex/SlopeTrick.hpp
layout: document
title: Slope Trick
---

A data structure that maintains a continuous, convex, piecewise linear function $f(x)$ whose slopes are integers. It supports operations like adding absolute value functions $\lvert x-a\rvert$, adding $\max(0, x-a)$ or $\max(0, a-x)$, shifting the function, and finding the minimum value.

The function is represented as:

$$f(x) = f_{\text{min}} + \sum_{l \in L} (l - x)_+ + \sum_{r \in R} (x - r)_+$$

where $L$ and $R$ are multisets of slope change points, implemented as a max-heap and a min-heap respectively.

## Template Parameters

```cpp
template<typename T, T INF = std::numeric_limits<T>::max() / 2>
class SlopeTrick;
```

* `T`: The coordinate and value type of the function (typically integer types like `long long` or floating-point types).
* `INF`: A value representing infinity. Defaults to `std::numeric_limits<T>::max() / 2`.

---

## Constructor

```cpp
SlopeTrick();
```

* $O(1)$ time

Constructs an empty `SlopeTrick` object representing the constant function $f(x) = 0$.

---

## is_inf

```cpp
bool is_inf(T v);
```

* $O(1)$ time

Checks if a value `v` is infinity (either greater than or equal to `INF` or less than or equal to `-INF`).

---

## size_l / size_r / size

```cpp
int size_l();
int size_r();
int size();
```

* $O(1)$ time

Returns the number of slope changes on the left (slopes $< 0$), on the right (slopes $> 0$), or in total.

---

## top

```cpp
T top();
```

* $O(1)$ time

Returns the minimum value of $f(x)$.

---

## top_interval

```cpp
std::pair<T, T> top_interval();
```

* $O(1)$ time

Returns the interval $[L, R]$ where $f(x)$ achieves its minimum value. If the interval is unbounded on one side, returns `-INF` or `INF` accordingly.

---

## add_const

```cpp
SlopeTrick& add_const(T a);
```

* $O(1)$ time

Adds a constant $a$ to the function: $f(x) \leftarrow f(x) + a$.

---

## add_x_minus_a

```cpp
SlopeTrick& add_x_minus_a(T a);
```

* $O(\log N)$ time

Adds the function $(x - a)_+ = \max(0, x - a)$ to the function.

---

## add_a_minus_x

```cpp
SlopeTrick& add_a_minus_x(T a);
```

* $O(\log N)$ time

Adds the function $(a - x)_+ = \max(0, a - x)$ to the function.

---

## add_abs

```cpp
SlopeTrick& add_abs(T a);
```

* $O(\log N)$ time

Adds the absolute value function $\lvert x - a\rvert$ to the function. This is equivalent to calling `add_x_minus_a(a).add_a_minus_x(a)`.

---

## add_linear

```cpp
SlopeTrick& add_linear(int a, T b);
```

* $O(\lvert a\rvert \log N)$ time

Adds $ax + b$ to the function. Requires `a` to be an integer. It shifts elements between the left and right priority queues depending on the sign of `a`.

---

## shift

```cpp
SlopeTrick& shift(T a);
```

* $O(1)$ time

Translates the function horizontally: $f(x) \leftarrow f(x - a)$ (shifted by right).

---

## sliding_window_minimum

```cpp
SlopeTrick& sliding_window_minimum(T a, T b);
```

* $O(1)$ time

Replaces $f(x)$ with $g(x) = \min_{x - b \le y \le x - a} f(y)$. Requires $a \le b$.

---

## prefix_min

```cpp
SlopeTrick& prefix_min();
```

* $O(N_R)$ time, where $N_R$ is the size of the right heap.

Replaces $f(x)$ with $g(x) = \min_{y \le x} f(y)$. This effectively clears the right priority queue (slope changes for $x > R$).

---

## suffix_min

```cpp
SlopeTrick& suffix_min();
```

* $O(N_L)$ time, where $N_L$ is the size of the left heap.

Replaces $f(x)$ with $g(x) = \min_{y \ge x} f(y)$. This effectively clears the left priority queue (slope changes for $x < L$).

---

## eval

```cpp
T eval(T x);
```

* $O(N \log N)$ time

Computes the value $f(x)$ at a given point $x$. Note that this operation is slow because it copies the internal priority queues and drains them.
