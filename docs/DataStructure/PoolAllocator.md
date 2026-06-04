---
title: Pool Allocator
documentation_of: ../../DataStructure/PoolAllocator.hpp
---

A fast memory allocator that uses a pre-allocated static pool. Note that `deallocate` does nothing; use `reset` to reclaim all memory.

## Template Parameters

```cpp
template<typename T, int _POOL_SIZE = POOL_SIZE>
struct PoolAllocator;
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

Allocates memory for an object of type `T` from the pool and constructs it using the provided arguments.

---

## deallocate

```cpp
static void deallocate(T* p);
```

* $O(1)$ time

Does nothing.

---

## reset

```cpp
static void reset();
```

* $O(1)$ time

Resets the pool pointer, effectively reclaiming all allocated memory. Existing pointers become invalid.
