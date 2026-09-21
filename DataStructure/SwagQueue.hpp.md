---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/queue_operate_all_composite.test.cpp
    title: test/1_library_checker/data_structure/queue_operate_all_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/SwagQueue.hpp\"\n\ntemplate<typename T>\n\
    class SwagQueue {\n    int sz = 0;\n    std::vector<T> data, cum_l;\n    T cum_r;\n\
    public:\n    SwagQueue() : cum_l(1, T()), cum_r() {}\n    int size() { return\
    \ sz; }\n    void push(T x) {\n        ++sz;\n        cum_r = cum_r + x;\n   \
    \     data.push_back(x);\n    }\n    void pop() {\n        --sz;\n        cum_l.pop_back();\n\
    \        if (cum_l.empty()) {\n            cum_l.push_back(T());\n           \
    \ cum_r = T();\n            while (int(data.size()) > 1) {\n                cum_l.push_back(data.back()\
    \ + cum_l.back());\n                data.pop_back();\n            }\n        \
    \    data.pop_back();\n        }\n    }\n    T lprod() { return cum_l.back();\
    \ }\n    T rprod() { return cum_r; }\n    T prod() { return lprod() + rprod();\
    \ }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nclass SwagQueue {\n    int sz = 0;\n\
    \    std::vector<T> data, cum_l;\n    T cum_r;\npublic:\n    SwagQueue() : cum_l(1,\
    \ T()), cum_r() {}\n    int size() { return sz; }\n    void push(T x) {\n    \
    \    ++sz;\n        cum_r = cum_r + x;\n        data.push_back(x);\n    }\n  \
    \  void pop() {\n        --sz;\n        cum_l.pop_back();\n        if (cum_l.empty())\
    \ {\n            cum_l.push_back(T());\n            cum_r = T();\n           \
    \ while (int(data.size()) > 1) {\n                cum_l.push_back(data.back()\
    \ + cum_l.back());\n                data.pop_back();\n            }\n        \
    \    data.pop_back();\n        }\n    }\n    T lprod() { return cum_l.back();\
    \ }\n    T rprod() { return cum_r; }\n    T prod() { return lprod() + rprod();\
    \ }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/SwagQueue.hpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/queue_operate_all_composite.test.cpp
documentation_of: DataStructure/SwagQueue.hpp
layout: document
title: SWAG Queue
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
