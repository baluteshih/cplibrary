---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/persistent_queue_pool.test.cpp
    title: test/1_library_checker/data_structure/persistent_queue_pool.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/PoolAllocator.hpp\"\n\n#ifndef POOL_SIZE\n\
    \    #define POOL_SIZE 10000000\n#endif\n\ntemplate<typename T, int _POOL_SIZE\
    \ = POOL_SIZE>\nstruct PoolAllocator {\n    static T pool[_POOL_SIZE];\n    static\
    \ int ptr;\n    template<typename... Args>\n    static T* allocate(Args&&... args)\
    \ { \n        T* p = &pool[ptr++];\n        return new (p) T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate([[maybe_unused]] T* p) {}\n    static void\
    \ reset() { ptr = 0; }\n};\n\ntemplate<typename T, int _POOL_SIZE>\nT PoolAllocator<T,\
    \ _POOL_SIZE>::pool[_POOL_SIZE];\n\ntemplate<typename T, int _POOL_SIZE>\nint\
    \ PoolAllocator<T, _POOL_SIZE>::ptr = 0;\n"
  code: "#pragma once\n\n#ifndef POOL_SIZE\n    #define POOL_SIZE 10000000\n#endif\n\
    \ntemplate<typename T, int _POOL_SIZE = POOL_SIZE>\nstruct PoolAllocator {\n \
    \   static T pool[_POOL_SIZE];\n    static int ptr;\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        T* p = &pool[ptr++];\n\
    \        return new (p) T(std::forward<Args>(args)...);\n    }\n    static void\
    \ deallocate([[maybe_unused]] T* p) {}\n    static void reset() { ptr = 0; }\n\
    };\n\ntemplate<typename T, int _POOL_SIZE>\nT PoolAllocator<T, _POOL_SIZE>::pool[_POOL_SIZE];\n\
    \ntemplate<typename T, int _POOL_SIZE>\nint PoolAllocator<T, _POOL_SIZE>::ptr\
    \ = 0;\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/PoolAllocator.hpp
  requiredBy: []
  timestamp: '2026-05-23 21:25:29+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/persistent_queue_pool.test.cpp
documentation_of: DataStructure/PoolAllocator.hpp
layout: document
title: Pool Allocator
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
