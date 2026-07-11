---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/Convex/SlopeTrick.hpp
    title: Slope Trick
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/3_yukicoder/2114.test.cpp
    title: test/3_yukicoder/2114.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - "https://maspypy.com/slope-trick-3-slope-trick-\u306E\u51F8\u5171\u5F79"
  bundledCode: "#line 2 \"DataStructure/Convex/ConjugateSlopeTrick.hpp\"\n\n#line\
    \ 2 \"DataStructure/Convex/SlopeTrick.hpp\"\n\n/*\nreference: https://maspypy.com/slope-trick-1-\u89E3\
    \u8AAC\u7DE8\n*/\n\ntemplate<typename T, T INF = std::numeric_limits<T>::max()\
    \ / 2>\nclass SlopeTrick {\n    using min_heap = std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>>;\n    using max_heap = std::priority_queue<T>;\n    max_heap\
    \ pq_l;\n    min_heap pq_r;\n    T min_f;\n    T top_l() const { return pq_l.empty()\
    \ ? -INF : pq_l.top() + add_l; }\n    T top_r() const { return pq_r.empty() ?\
    \ INF : pq_r.top() + add_r; }\n    T pop_l() { T res = top_l(); if (!pq_l.empty())\
    \ pq_l.pop(); return res; }\n    T pop_r() { T res = top_r(); if (!pq_r.empty())\
    \ pq_r.pop(); return res; }\n    void push_l(T a) { pq_l.push(a - add_l); }\n\
    \    void push_r(T a) { pq_r.push(a - add_r); }\nprotected:\n    T add_l, add_r;\
    \ \npublic:\n    SlopeTrick() : min_f(), add_l(), add_r() {}\n    bool is_inf(T\
    \ v) { return v >= INF || v <= -INF; }\n    int size_l() { return pq_l.size();\
    \ }\n    int size_r() { return pq_r.size(); }\n    int size() { return size_l()\
    \ + size_r(); }\n    T top() { return min_f; }\n    std::pair<T, T> top_interval()\
    \ { return {top_l(), top_r()}; }\n    SlopeTrick& add_const(T a) { return min_f\
    \ += a, *this; }\n    SlopeTrick& add_x_minus_a(T a) {\n        min_f += std::max(T(0),\
    \ top_l() - a);\n        push_l(a), push_r(pop_l());\n        return *this;\n\
    \    }\n    SlopeTrick& add_a_minus_x(T a) {\n        min_f += std::max(T(0),\
    \ a - top_r());\n        push_r(a), push_l(pop_r());\n        return *this;\n\
    \    }\n    SlopeTrick& add_abs(T a) { return add_x_minus_a(a).add_a_minus_x(a);\
    \ } \n    SlopeTrick& add_linear(int a, T b) {\n        for (min_f += b; a > 0;\
    \ --a) {\n            T x = pop_l();\n            min_f += x, push_r(x);\n   \
    \     }\n        for (; a < 0; ++a) {\n            T x = pop_r();\n          \
    \  min_f -= x, push_l(x);\n        }\n        return *this;\n    }\n    SlopeTrick&\
    \ shift(T a) { return add_l += a, add_r += a, *this; }\n    SlopeTrick& sliding_window_minimum(T\
    \ a, T b) {\n        assert(a <= b);\n        add_l += a, add_r += b;\n      \
    \  return *this;\n    }\n    SlopeTrick& prefix_min() { return min_heap().swap(pq_r),\
    \ *this; }\n    SlopeTrick& suffix_min() { return max_heap().swap(pq_l), *this;\
    \ }\n    T eval(T x) {\n        T res = min_f;\n        auto tl = pq_l; auto tr\
    \ = pq_r;\n        for (; !tl.empty(); tl.pop()) res += std::max(T(0), (tl.top()\
    \ + add_l) - x);\n        for (; !tr.empty(); tr.pop()) res += std::max(T(0),\
    \ x - (tr.top() + add_r));\n        return res;\n    }\n};\n#line 4 \"DataStructure/Convex/ConjugateSlopeTrick.hpp\"\
    \n\n/*\nreference: https://maspypy.com/slope-trick-3-slope-trick-\u306E\u51F8\u5171\
    \u5F79 \n*/\n\ntemplate<typename T, T INF = std::numeric_limits<T>::max() / 2>\n\
    class ConjugateSlopeTrick : private SlopeTrick<T, INF> {\n    using super = SlopeTrick<T,\
    \ INF>;\npublic:\n    ConjugateSlopeTrick() : super() {}\n    using super::is_inf;\n\
    \    T f0() { return -super::top(); }\n    ConjugateSlopeTrick& add_const(T a)\
    \ { super::add_const(a); }\n    ConjugateSlopeTrick& add_x_minus_a(T c, T a =\
    \ 0) {\n        if (a) shift(-a);\n        if (c > 0) super::add_r += c;\n   \
    \     if (c < 0) super::add_l += c;\n        if (a) shift(a);\n        return\
    \ *this;\n    }\n    ConjugateSlopeTrick& add_abs(T c, T a = 0) { return add_x_minus_a(c,\
    \ a).add_x_minus_a(-c, a); }\n    ConjugateSlopeTrick& add_linear(T a, T b = 0)\
    \ { return super::shift(a).add_const(b), *this; }\n    ConjugateSlopeTrick& shift(int\
    \ a) { return super::add_linear(a, 0), *this; }\n    ConjugateSlopeTrick& sliding_window_minimum(T\
    \ a, T b) {\n        assert(a <= b);\n        shift(a);\n        for (int i =\
    \ 0; i < b - a; ++i) super::add_x_minus_a(0);\n        return *this;\n    }\n\
    \    ConjugateSlopeTrick& convolve(const std::vector<T>& g, int base = 0) {\n\
    \        for (int i = 1; i < int(g.size()); ++i) super::add_x_minus_a(g[i] - g[i\
    \ - 1]);\n        if (base != 0) shift(-base);\n        return *this;\n    }\n\
    \    ConjugateSlopeTrick& clear_left() { return super::suffix_min(), *this; }\n\
    \    ConjugateSlopeTrick& clear_right() { return super::prefix_min(), *this; }\n\
    \    T min_val(T p = 0) {\n        return -super::eval(p);\n    }\n};\n"
  code: "#pragma once\n\n#include \"DataStructure/Convex/SlopeTrick.hpp\"\n\n/*\n\
    reference: https://maspypy.com/slope-trick-3-slope-trick-\u306E\u51F8\u5171\u5F79\
    \ \n*/\n\ntemplate<typename T, T INF = std::numeric_limits<T>::max() / 2>\nclass\
    \ ConjugateSlopeTrick : private SlopeTrick<T, INF> {\n    using super = SlopeTrick<T,\
    \ INF>;\npublic:\n    ConjugateSlopeTrick() : super() {}\n    using super::is_inf;\n\
    \    T f0() { return -super::top(); }\n    ConjugateSlopeTrick& add_const(T a)\
    \ { super::add_const(a); }\n    ConjugateSlopeTrick& add_x_minus_a(T c, T a =\
    \ 0) {\n        if (a) shift(-a);\n        if (c > 0) super::add_r += c;\n   \
    \     if (c < 0) super::add_l += c;\n        if (a) shift(a);\n        return\
    \ *this;\n    }\n    ConjugateSlopeTrick& add_abs(T c, T a = 0) { return add_x_minus_a(c,\
    \ a).add_x_minus_a(-c, a); }\n    ConjugateSlopeTrick& add_linear(T a, T b = 0)\
    \ { return super::shift(a).add_const(b), *this; }\n    ConjugateSlopeTrick& shift(int\
    \ a) { return super::add_linear(a, 0), *this; }\n    ConjugateSlopeTrick& sliding_window_minimum(T\
    \ a, T b) {\n        assert(a <= b);\n        shift(a);\n        for (int i =\
    \ 0; i < b - a; ++i) super::add_x_minus_a(0);\n        return *this;\n    }\n\
    \    ConjugateSlopeTrick& convolve(const std::vector<T>& g, int base = 0) {\n\
    \        for (int i = 1; i < int(g.size()); ++i) super::add_x_minus_a(g[i] - g[i\
    \ - 1]);\n        if (base != 0) shift(-base);\n        return *this;\n    }\n\
    \    ConjugateSlopeTrick& clear_left() { return super::suffix_min(), *this; }\n\
    \    ConjugateSlopeTrick& clear_right() { return super::prefix_min(), *this; }\n\
    \    T min_val(T p = 0) {\n        return -super::eval(p);\n    }\n};\n"
  dependsOn:
  - DataStructure/Convex/SlopeTrick.hpp
  isVerificationFile: false
  path: DataStructure/Convex/ConjugateSlopeTrick.hpp
  requiredBy: []
  timestamp: '2026-07-12 01:44:14+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/3_yukicoder/2114.test.cpp
documentation_of: DataStructure/Convex/ConjugateSlopeTrick.hpp
layout: document
title: Conjugate Slope Trick
---

Conjugate Slope Trick maintains a convex function $f(x)$ using its convex conjugate (Fenchel conjugate) $f^*(p) = \sup_x (px - f(x))$. The conjugate function $f^*(p)$ is internally maintained using a standard `SlopeTrick`. 

This enables efficient operations like min-convolution (which corresponds to addition in the conjugate domain) and additions of certain functions like $c(x-a)_+$ or $c\lvert x-a\rvert$ in $O(1)$ time.

## Template Parameters

```cpp
template<typename T, T INF = std::numeric_limits<T>::max() / 2>
class ConjugateSlopeTrick;
```

* `T`: The coordinate and value type of the function (typically integer types like `long long` or floating-point types).
* `INF`: A value representing infinity. Defaults to `std::numeric_limits<T>::max() / 2`.

---

## Constructor

```cpp
ConjugateSlopeTrick();
```

* $O(1)$ time

Constructs an empty `ConjugateSlopeTrick` object.

---

## is_inf

```cpp
bool is_inf(T v);
```

* $O(1)$ time

Checks if a value `v` is infinity (either greater than or equal to `INF` or less than or equal to `-INF`).

---

## f0

```cpp
T f0();
```

* $O(1)$ time

Returns $-f^*(0)$, which is the value of the primal function at $x = 0$ if the conjugate function's minimum value corresponds to $p = 0$.

---

## add_const

```cpp
ConjugateSlopeTrick& add_const(T a);
```

* $O(1)$ time

Adds a constant $a$ to the function: $f(x) \leftarrow f(x) + a$.

---

## add_x_minus_a

```cpp
ConjugateSlopeTrick& add_x_minus_a(T c, T a = 0);
```

* $O(\lvert a\rvert\log n)$ time

Adds the function $c(x - a)_+ = \max(0, c(x - a))$ to the function.

---

## add_abs

```cpp
ConjugateSlopeTrick& add_abs(T c, T a = 0);
```

* $O(\lvert a\rvert\log n)$ time

Adds $c\lvert x - a\rvert$ to the function. Equivalent to `add_x_minus_a(c, a).add_x_minus_a(-c, a)`.

---

## add_linear

```cpp
ConjugateSlopeTrick& add_linear(T a, T b = 0);
```

* $O(1)$ time

Adds a linear term $ax + b$ to the function.

---

## shift

```cpp
ConjugateSlopeTrick& shift(int a);
```

* $O(\lvert a\rvert \log N)$ time, where $N$ is the number of slope changes in the conjugate function.

Translates the function horizontally: $f(x) \leftarrow f(x - a)$.

---

## sliding_window_minimum

```cpp
ConjugateSlopeTrick& sliding_window_minimum(T a, T b);
```

* $O((\lvert a\rvert + \lvert b\rvert) \log N)$ time, where $N$ is the number of slope changes in the conjugate function.

Replaces $f(x)$ with $g(x) = \min_{x - b \le y \le x - a} f(y)$. Requires $a \le b$.

---

## convolve

```cpp
ConjugateSlopeTrick& convolve(const std::vector<T>& g, int base = 0);
```

* $O(\lvert g\rvert \log N)$ time, where $N$ is the number of slope changes in the conjugate function.

Computes the min-convolution $f(x) \leftarrow \min_{i} (f(x + i + \text{base}) + g[i])$. The sequence $g$ must be convex (i.e., $g[i+1] - g[i] \ge g[i] - g[i-1]$).

---

## clear_left

```cpp
ConjugateSlopeTrick& clear_left();
```

* $O(N_L)$ time, where $N_L$ is the number of slope changes on the left.

Clears the slope changes on the left, corresponding to replacing $f(x)$ with $\min_{y \ge x} f(y)$ in the primal domain.

---

## clear_right

```cpp
ConjugateSlopeTrick& clear_right();
```

* $O(N_R)$ time, where $N_R$ is the number of slope changes on the right.

Clears the slope changes on the right, corresponding to replacing $f(x)$ with $\min_{y \le x} f(y)$ in the primal domain.

---

## min_val

```cpp
T min_val(T p = 0);
```

* $O(N \log N)$ time

Computes the minimum value of $f(x) - px$ over all $x$, which is $-f^*(p)$. Note that this operation evaluates the internal SlopeTrick at $p$.
