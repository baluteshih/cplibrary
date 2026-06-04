---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/StackPoolAllocator.hpp\"\n\n#ifndef POOL_SIZE\n\
    \    #define POOL_SIZE 10000000\n#endif\n\ntemplate<typename T, int _POOL_SIZE\
    \ = POOL_SIZE>\nstruct StackPoolAllocator {\n    static T pool[_POOL_SIZE];\n\
    \    static T* recycle[_POOL_SIZE];\n    static int ptr, top;\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        T* p;\n        if\
    \ (top > 0) p = recycle[--top];\n        else p = &pool[ptr++];\n        return\
    \ new (p) T(std::forward<Args>(args)...);\n    }\n    static void deallocate(T*\
    \ p) { recycle[top++] = p; }\n    static void reset() { ptr = top = 0; }\n};\n\
    \ntemplate<typename T, int _POOL_SIZE>\nT StackPoolAllocator<T, _POOL_SIZE>::pool[_POOL_SIZE];\n\
    \ntemplate<typename T, int _POOL_SIZE>\nT* StackPoolAllocator<T, _POOL_SIZE>::recycle[_POOL_SIZE];\n\
    \ntemplate<typename T, int _POOL_SIZE>\nint StackPoolAllocator<T, _POOL_SIZE>::ptr\
    \ = 0;\n\ntemplate<typename T, int _POOL_SIZE>\nint StackPoolAllocator<T, _POOL_SIZE>::top\
    \ = 0;\n"
  code: "#pragma once\n\n#ifndef POOL_SIZE\n    #define POOL_SIZE 10000000\n#endif\n\
    \ntemplate<typename T, int _POOL_SIZE = POOL_SIZE>\nstruct StackPoolAllocator\
    \ {\n    static T pool[_POOL_SIZE];\n    static T* recycle[_POOL_SIZE];\n    static\
    \ int ptr, top;\n    template<typename... Args>\n    static T* allocate(Args&&...\
    \ args) { \n        T* p;\n        if (top > 0) p = recycle[--top];\n        else\
    \ p = &pool[ptr++];\n        return new (p) T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { recycle[top++] = p; }\n    static void\
    \ reset() { ptr = top = 0; }\n};\n\ntemplate<typename T, int _POOL_SIZE>\nT StackPoolAllocator<T,\
    \ _POOL_SIZE>::pool[_POOL_SIZE];\n\ntemplate<typename T, int _POOL_SIZE>\nT* StackPoolAllocator<T,\
    \ _POOL_SIZE>::recycle[_POOL_SIZE];\n\ntemplate<typename T, int _POOL_SIZE>\n\
    int StackPoolAllocator<T, _POOL_SIZE>::ptr = 0;\n\ntemplate<typename T, int _POOL_SIZE>\n\
    int StackPoolAllocator<T, _POOL_SIZE>::top = 0;\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/StackPoolAllocator.hpp
  requiredBy: []
  timestamp: '2026-05-05 22:01:14+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: DataStructure/StackPoolAllocator.hpp
layout: document
title: Stack Pool Allocator
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
