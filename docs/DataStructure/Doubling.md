---
title: Doubling
documentation_of: ../../DataStructure/Doubling.hpp
---

The Doubling technique, also known as binary lifting, is a powerful method for efficiently answering queries about paths in a graph or sequences, especially when those queries involve "jumping" a certain number of steps. It precomputes jumps of powers of two to answer arbitrary jumps in logarithmic time.

## Template Parameters

```cpp
template<class Value, bool ImplicitJump = false>
class Doubling;
```

* `Value`: The type of value to be accumulated during jumps.
    * Use `void` for state-only usage.
    * Must support `operator+` for combining values and have a default constructor `Value()` representing an identity element.
* `ImplicitJump`: If `true`, the `nxt` (next state) array is not explicitly stored, and the jump is implicitly defined as `i + (1 << j)`. This is useful for problems where the next state is simply a fixed increment (e.g., jumping `k` steps forward in a sequence).

---

## Constructors

```cpp
Doubling(int n, const std::ranges::range auto &init_nxt); // Explicit Jumps, No Value
Doubling(int n, const std::ranges::range auto &init_val); // Implicit Jumps, With Value
Doubling(int n, const std::ranges::range auto &init_nxt, const std::ranges::range auto &init_val); // Explicit Jumps, With Value
```

* `n`: The number of states.
* `init_nxt`: A range (e.g., `std::vector<int>`) representing the next state for each `i` after 1 step. `init_nxt[i]` is the state after 1 jump from `i`.
* `init_val`: A range representing the value associated with a 1-step jump from each `i`.
* $O(N \log N)$ time for precomputation.

Initializes the Doubling structure.

---

## Methods

### step

```cpp
int step(int u, int d);
```

* `u`: The starting state.
* `d`: The number of steps to jump.
* $O(\log d)$ time

Returns the state reached by jumping `d` steps from `u`.

---

### maximal_prefix

```cpp
template<typename F_cond>
int maximal_prefix(int u, F_cond cond);
```

* `u`: The starting state.
* `cond`: A callable (e.g., lambda) that takes an `int` (state) and returns `bool`. It should return `true` if the condition is met for that state, and `false` otherwise. The `cond` must be monotonic (if `cond(x)` is true, then `cond(previous_state_from_x)` is also true).
* $O(\log N)$ time

Finds the furthest state `v` reachable from `u` such that `cond(v)` is true. If `cond(u)` is false, returns -1.

---

### maximal_prefix_prod

```cpp
template<typename F_cond>
std::pair<Value, int> maximal_prefix_prod(int u, F_cond cond);
```

* `u`: The starting state.
* `cond`: A callable (e.g., lambda) that takes an `int` (state) and returns `bool`. The condition must be monotonic.
* $O(\log N)$ time

Similar to `maximal_prefix`, but also returns the accumulated `Value` along the path to the furthest state `v` for which `cond(v)` is true. Returns a `std::pair<Value, int>` where the `Value` is the accumulated value and the `int` is the final state. If `cond(u)` is false, returns `std::make_pair(Value(), -1)`.
