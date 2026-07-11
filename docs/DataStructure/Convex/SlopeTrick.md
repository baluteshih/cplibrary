---
title: Slope Trick
documentation_of: ../../../DataStructure/Convex/SlopeTrick.hpp
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

Translates the function horizontally: $f(x) \leftarrow f(x - a)$.

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
