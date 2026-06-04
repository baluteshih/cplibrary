---
title: SWAG Queue
documentation_of: ../../DataStructure/SwagQueue.hpp
---

A $0$-based Sliding Window Aggregation (SWAG) Queue that supports queue operations and range product (aggregation) in amortized $O(1)$ time.

## Template Parameters

```cpp
template<typename T>
class SwagQueue;
```

* `T`: The type of elements.
    * Must support associative property `operator+` for aggregation.
    * Must have a default constructor `T()` acting as the identity element.

---

## Constructor

```cpp
SwagQueue();
```

* $O(1)$ time

Constructs an empty SWAG Queue.

---

## size

```cpp
int size();
```

Returns the number of elements in the queue.

---

## push

```cpp
void push(T x);
```

* $O(1)$ time

Adds an element `x` to the back of the queue.

---

## pop

```cpp
void pop();
```

* Amortized $O(1)$ time

Removes an element from the front of the queue.

---

## prod

```cpp
T prod();
```

* $O(1)$ time

Returns the product (aggregation) of all elements currently in the queue.

---

## lprod & rprod

```cpp
T lprod();
T rprod();
```

Returns the partial product of the front and back stacks respectively. `prod()` is defined as `lprod() + rprod()`.
