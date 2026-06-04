---
title: Stack Pool Allocator
documentation_of: ../../DataStructure/StackPoolAllocator.hpp
---

A memory allocator that uses a pre-allocated static pool and maintains a free list (stack) for recycled memory.

## Template Parameters

```cpp
template<typename T, int _POOL_SIZE = POOL_SIZE>
struct StackPoolAllocator;
```

* `T`: The type of elements to allocate.
* `_POOL_SIZE`: The maximum number of elements that can be allocated. Defaults to a defined value `POOL_SIZE` (with default value $10^7$).
    * To modify the defined value `POOL_SIZE`, define this variable before including header.

---

## allocate

```cpp
template<typename... Args>
static T* allocate(Args&&... args);
```

* $O(1)$ time

Allocates memory for an object of type `T`. It first tries to reuse memory from the free list; if the free list is empty, it allocates from the pool.

---

## deallocate

```cpp
static void deallocate(T* p);
```

* $O(1)$ time

Adds the pointer `p` to the free list for future reuse.

---

## reset

```cpp
static void reset();
```

* $O(1)$ time

Resets the pool pointer and the free list, effectively reclaiming all allocated memory. Existing pointers become invalid.
