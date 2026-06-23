---
title: MinMax Heap
documentation_of: ../../DataStructure/MinMaxHeap.hpp
---

A MinMax Heap is a data structure that allows efficient retrieval and removal of both the minimum and maximum elements. It is implemented using two `LazyDeleteHeap` instances: one configured as a max-heap and the other as a min-heap. This structure is useful for maintaining a collection of elements where access to both extremes is frequently needed.

## Template Parameters

```cpp
template<typename T>
class MinMaxHeap;
```

* `T`: The type of elements stored in the heap.
    * Must support `operator<` and `operator==` for comparison (required by `std::priority_queue` and `LazyDeleteHeap`).

---

## Methods

### push

```cpp
void push(const T& val);
```

* $O(\log N)$ time

Inserts an element `val` into both the internal max-heap and min-heap.

---

### erase

```cpp
void erase(const T& val);
```

* $O(\log N)$ time

Marks an element `val` for lazy deletion from both the internal max-heap and min-heap. The element is not immediately removed.

---

### pop_min

```cpp
void pop_min();
```

* Amortized $O(\log N)$ time

Removes the minimum element from the heap.

---

### pop_max

```cpp
void pop_max();
```

* Amortized $O(\log N)$ time

Removes the maximum element from the heap.

---

### top_min

```cpp
const T& top_min();
```

* Amortized $O(\log N)$ time

Returns a reference to the minimum element of the heap without removing it.

---

### top_max

```cpp
const T& top_max();
```

* Amortized $O(\log N)$ time

Returns a reference to the maximum element of the heap without removing it.

---

### size

```cpp
size_t size() const;
```

* $O(1)$ time

Returns the number of active (non-deleted) elements in the heap.

---

### empty

```cpp
bool empty() const;
```

* $O(1)$ time

Returns `true` if the heap contains no active elements, `false` otherwise.

---

### swap

```cpp
void swap(MinMaxHeap &other);
```

* $O(1)$ time

Swaps the contents of this heap with another `MinMaxHeap`.

---

### clear

```cpp
void clear();
```

* Linear time to the size of the container. 

Clears all elements from the heap.
