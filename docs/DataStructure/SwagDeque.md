---
title: SWAG Deque
documentation_of: ../../DataStructure/SwagDeque.hpp
---

A $0$-based Sliding Window Aggregation (SWAG) Deque that supports double-ended operations and range product (aggregation) in amortized $O(1)$ time.

## Template Parameters

```cpp
template<typename T>
class SwagDeque;
```

* `T`: The type of elements.
    * Must support associative property `operator+` for aggregation.
    * Must have a default constructor `T()` acting as the identity element.

---

## Constructor

```cpp
SwagDeque();
```

* $O(1)$ time

Constructs an empty SWAG Deque.

---

## size

```cpp
int size();
```

Returns the number of elements in the deque.

---

## push_back

```cpp
void push_back(T x);
```

* Amortized $O(1)$ time

Adds an element `x` to the back of the deque.

---

## push_front

```cpp
void push_front(T x);
```

* Amortized $O(1)$ time

Adds an element `x` to the front of the deque.

---

## pop_back

```cpp
void pop_back();
```

* Amortized $O(1)$ time

Removes an element from the back of the deque.

---

## pop_front

```cpp
void pop_front();
```

* Amortized $O(1)$ time

Removes an element from the front of the deque.

---

## front

```cpp
T front();
```

Returns the first element of the deque.

---

## clear

```cpp
void clear();
```

Clears the deque.

---

## prod

```cpp
T prod();
```

* $O(1)$ time

Returns the product (aggregation) of all elements currently in the deque.

---

## lprod & rprod

```cpp
T lprod();
T rprod();
```

Returns the partial product of the left (front) and right (back) stacks respectively. `prod()` is defined as `lprod() + rprod()`.
