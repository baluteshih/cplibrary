---
title: Conjugate Slope Trick
documentation_of: ../../../DataStructure/Convex/ConjugateSlopeTrick.hpp
---

Conjugate Slope Trick maintains a convex function $f(x)$ using its convex conjugate (Fenchel conjugate) $f^*(p) = \sup_x (px - f(x))$. 

The conjugate function $f^*(p)$ is internally maintained using a standard `SlopeTrick`. 

This enables efficient operations like min-convolution (which corresponds to addition in the conjugate domain) and additions of certain functions like $c(x-a)_+$ or $c\lvert x-a\rvert$ in $O(\lvert a \rvert \log n)$ time.

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

Constructs an empty `ConjugateSlopeTrick` object representing the following function:

$$f(x) = \begin{cases} 0 & x = 0 \\ \infty & x \neq 0 \end{cases}$$

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

* $O(\lvert a\rvert\log N)$ time

Adds the function $c(x - a)_+ = \max(0, c(x - a))$ to the function.

---

## add_abs

```cpp
ConjugateSlopeTrick& add_abs(T c, T a = 0);
```

* $O(\lvert a\rvert\log N)$ time

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

Translates the function horizontally: $f(x) \leftarrow f(x - a)$ (shifted by left).

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

---

## eval

```cpp
T eval(T x);
```

* $O(|x| \log N)$ time

Computes the value $f(x)$ at a given point $x$.
