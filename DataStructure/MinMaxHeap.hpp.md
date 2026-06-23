---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: DataStructure/LazyDeleteHeap.hpp
    title: Lazy Delete Heap
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/MinMaxHeap.hpp\"\n\n#line 2 \"DataStructure/LazyDeleteHeap.hpp\"\
    \n\ntemplate <typename Container>\nclass LazyDeleteHeap {\nprivate:\n    Container\
    \ main_q;\n    Container del_q;\n    void normalize() {\n        while (!main_q.empty()\
    \ && !del_q.empty() && main_q.top() == del_q.top()) {\n            main_q.pop();\n\
    \            del_q.pop();\n        }\n    }\npublic:\n    using value_type = typename\
    \ Container::value_type;\n    void push(const value_type& val) {\n        main_q.push(val);\n\
    \    }\n    void erase(const value_type& val) {\n        del_q.push(val);\n  \
    \  }\n    void pop() {\n        normalize();\n        assert(!main_q.empty());\n\
    \        main_q.pop();\n    }\n    const value_type& top() {\n        normalize();\n\
    \        return main_q.top();\n    }\n    size_t size() const {\n        return\
    \ main_q.size() - del_q.size();\n    }\n    bool empty() const {\n        return\
    \ size() == 0;\n    }\n    void swap(LazyDeleteHeap &other) {\n        main_q.swap(other.main_q);\n\
    \        del_q.swap(other.del_q);\n    }\n    void clear() {\n        Container().swap(main_q);\
    \ \n        Container().swap(del_q); \n    }\n};\n#line 4 \"DataStructure/MinMaxHeap.hpp\"\
    \n\ntemplate<typename T>\nclass MinMaxHeap {\nprivate:\n    LazyDeleteHeap<std::priority_queue<T>>\
    \ max_heap;\n    LazyDeleteHeap<std::priority_queue<T, std::vector<T>, std::greater<T>>>\
    \ min_heap;\npublic: \n    void push(const T& val) {\n        max_heap.push(val);\n\
    \        min_heap.push(val);\n    }\n    void erase(const T& val) {\n        max_heap.erase(val);\n\
    \        min_heap.erase(val);\n    }\n    void pop_min() {\n        assert(!min_heap.empty());\n\
    \        max_heap.erase(min_heap.top());\n        min_heap.pop();\n    }\n   \
    \ void pop_max() {\n        assert(!max_heap.empty());\n        min_heap.erase(max_heap.top());\n\
    \        max_heap.pop();\n    }\n    const T& top_min() {\n        return min_heap.top();\n\
    \    }\n    const T& top_max() {\n        return max_heap.top();\n    }\n    size_t\
    \ size() const {\n        return max_heap.size(); \n    }\n    bool empty() const\
    \ {\n        return size() == 0;\n    }\n    void swap(MinMaxHeap &other) {\n\
    \        max_heap.swap(other.max_heap);\n        min_heap.swap(other.min_heap);\n\
    \    }\n    void clear() {\n        max_heap.clear();\n        min_heap.clear();\n\
    \    }\n};\n"
  code: "#pragma once\n\n#include \"DataStructure/LazyDeleteHeap.hpp\"\n\ntemplate<typename\
    \ T>\nclass MinMaxHeap {\nprivate:\n    LazyDeleteHeap<std::priority_queue<T>>\
    \ max_heap;\n    LazyDeleteHeap<std::priority_queue<T, std::vector<T>, std::greater<T>>>\
    \ min_heap;\npublic: \n    void push(const T& val) {\n        max_heap.push(val);\n\
    \        min_heap.push(val);\n    }\n    void erase(const T& val) {\n        max_heap.erase(val);\n\
    \        min_heap.erase(val);\n    }\n    void pop_min() {\n        assert(!min_heap.empty());\n\
    \        max_heap.erase(min_heap.top());\n        min_heap.pop();\n    }\n   \
    \ void pop_max() {\n        assert(!max_heap.empty());\n        min_heap.erase(max_heap.top());\n\
    \        max_heap.pop();\n    }\n    const T& top_min() {\n        return min_heap.top();\n\
    \    }\n    const T& top_max() {\n        return max_heap.top();\n    }\n    size_t\
    \ size() const {\n        return max_heap.size(); \n    }\n    bool empty() const\
    \ {\n        return size() == 0;\n    }\n    void swap(MinMaxHeap &other) {\n\
    \        max_heap.swap(other.max_heap);\n        min_heap.swap(other.min_heap);\n\
    \    }\n    void clear() {\n        max_heap.clear();\n        min_heap.clear();\n\
    \    }\n};\n"
  dependsOn:
  - DataStructure/LazyDeleteHeap.hpp
  isVerificationFile: false
  path: DataStructure/MinMaxHeap.hpp
  requiredBy: []
  timestamp: '2026-06-23 22:48:02+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: DataStructure/MinMaxHeap.hpp
layout: document
title: MinMax Heap
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
