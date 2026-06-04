---
title: Default Allocator
documentation_of: ../../DataStructure/DefaultAllocator.hpp
---

A simple wrapper around `new` and `delete` for memory allocation.

## Template Parameters

```cpp
template<typename T>
struct DefaultAllocator;
```

* `T`: The type of elements to allocate.

---

## allocate

```cpp
template<typename... Args>
static T* allocate(Args&&... args);
```

* $O(1)$ time (average)

Allocates memory for an object of type `T` and constructs it using the provided arguments.

---

## deallocate

```cpp
static void deallocate(T* p);
```

* $O(1)$ time (average)

Destructs the object and deallocates the memory pointed to by `p`.
