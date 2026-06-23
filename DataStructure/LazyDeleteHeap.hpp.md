---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: DataStructure/MinMaxHeap.hpp
    title: MinMax Heap
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/LazyDeleteHeap.hpp\"\n\ntemplate <typename\
    \ Container>\nclass LazyDeleteHeap {\nprivate:\n    Container main_q;\n    Container\
    \ del_q;\n    void normalize() {\n        while (!main_q.empty() && !del_q.empty()\
    \ && main_q.top() == del_q.top()) {\n            main_q.pop();\n            del_q.pop();\n\
    \        }\n    }\npublic:\n    using value_type = typename Container::value_type;\n\
    \    void push(const value_type& val) {\n        main_q.push(val);\n    }\n  \
    \  void erase(const value_type& val) {\n        del_q.push(val);\n    }\n    void\
    \ pop() {\n        normalize();\n        assert(!main_q.empty());\n        main_q.pop();\n\
    \    }\n    const value_type& top() {\n        normalize();\n        return main_q.top();\n\
    \    }\n    size_t size() const {\n        return main_q.size() - del_q.size();\n\
    \    }\n    bool empty() const {\n        return size() == 0;\n    }\n    void\
    \ swap(LazyDeleteHeap &other) {\n        main_q.swap(other.main_q);\n        del_q.swap(other.del_q);\n\
    \    }\n    void clear() {\n        Container().swap(main_q); \n        Container().swap(del_q);\
    \ \n    }\n};\n"
  code: "#pragma once\n\ntemplate <typename Container>\nclass LazyDeleteHeap {\nprivate:\n\
    \    Container main_q;\n    Container del_q;\n    void normalize() {\n       \
    \ while (!main_q.empty() && !del_q.empty() && main_q.top() == del_q.top()) {\n\
    \            main_q.pop();\n            del_q.pop();\n        }\n    }\npublic:\n\
    \    using value_type = typename Container::value_type;\n    void push(const value_type&\
    \ val) {\n        main_q.push(val);\n    }\n    void erase(const value_type& val)\
    \ {\n        del_q.push(val);\n    }\n    void pop() {\n        normalize();\n\
    \        assert(!main_q.empty());\n        main_q.pop();\n    }\n    const value_type&\
    \ top() {\n        normalize();\n        return main_q.top();\n    }\n    size_t\
    \ size() const {\n        return main_q.size() - del_q.size();\n    }\n    bool\
    \ empty() const {\n        return size() == 0;\n    }\n    void swap(LazyDeleteHeap\
    \ &other) {\n        main_q.swap(other.main_q);\n        del_q.swap(other.del_q);\n\
    \    }\n    void clear() {\n        Container().swap(main_q); \n        Container().swap(del_q);\
    \ \n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/LazyDeleteHeap.hpp
  requiredBy:
  - DataStructure/MinMaxHeap.hpp
  timestamp: '2026-06-23 22:48:02+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: DataStructure/LazyDeleteHeap.hpp
layout: document
title: Lazy Delete Heap
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
