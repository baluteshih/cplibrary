---
title: Lazy Delete Heap
documentation_of: ../../DataStructure/LazyDeleteHeap.hpp
---

A Lazy Delete Heap is a wrapper around a standard heap (e.g. `std::priority_queue`) that allows for efficient removal of elements. Instead of physically removing elements, it "marks" them for deletion, performing the actual removal only when necessary. This can be beneficial for performance when deletions are frequent.

## Template Parameters

```cpp
template <typename Container>
class LazyDeleteHeap;
```

* `Container`: A standard heap container (e.g., `std::priority_queue`).
    * Must support `push`, `pop`, `top`, `empty`, and `size` methods.
    * `value_type` must be accessible (e.g., `typename Container::value_type`).
    * `value_type` must support `operator==` for comparison.

---

## Methods

### push

```cpp
void push(const value_type& val);
```

* $O(\log N)$ time

Inserts an element `val` into the heap.

---

### erase

```cpp
void erase(const value_type& val);
```

* $O(\log N)$ time

Marks an element `val` for lazy deletion from the heap. The element is not immediately removed.

---

### pop

```cpp
void pop();
```

* Amortized $O(\log N)$ time

Removes the top element from the heap. Actual deletions of marked elements occur as needed.

---

### top

```cpp
const value_type& top();
```

* Amortized $O(\log N)$ time

Returns a reference to the top element of the heap without removing it. Actual deletions of marked elements occur as needed.

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
void swap(LazyDeleteHeap &other);
```

* $O(1)$ time

Swaps the contents of this heap with another `LazyDeleteHeap`.

---

### clear

```cpp
void clear();
```

* Linear time to the size of the container. 

Clears all elements from the heap.
