---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/8_luogu/P3835_pool.test.cpp
    title: test/8_luogu/P3835_pool.test.cpp
  - icon: ':x:'
    path: test/8_luogu/P5055.test.cpp
    title: test/8_luogu/P5055.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/PoolAllocator.hpp\"\n\n#ifndef POOL_SIZE\n\
    \    #define POOL_SIZE 10000000\n#endif\n\ntemplate<typename T, int _POOL_SIZE\
    \ = POOL_SIZE>\nstruct PoolAllocator {\n    static T pool[_POOL_SIZE];\n    static\
    \ int ptr;\n    template<typename... Args>\n    static T* allocate(Args&&... args)\
    \ { \n        T* p = &pool[ptr++];\n        return new (p) T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) {}\n    static void reset() { ptr = 0;\
    \ }\n};\n\ntemplate<typename T, int _POOL_SIZE>\nT PoolAllocator<T, _POOL_SIZE>::pool[_POOL_SIZE];\n\
    \ntemplate<typename T, int _POOL_SIZE>\nint PoolAllocator<T, _POOL_SIZE>::ptr\
    \ = 0;\n"
  code: "#pragma once\n\n#ifndef POOL_SIZE\n    #define POOL_SIZE 10000000\n#endif\n\
    \ntemplate<typename T, int _POOL_SIZE = POOL_SIZE>\nstruct PoolAllocator {\n \
    \   static T pool[_POOL_SIZE];\n    static int ptr;\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        T* p = &pool[ptr++];\n\
    \        return new (p) T(std::forward<Args>(args)...);\n    }\n    static void\
    \ deallocate(T* p) {}\n    static void reset() { ptr = 0; }\n};\n\ntemplate<typename\
    \ T, int _POOL_SIZE>\nT PoolAllocator<T, _POOL_SIZE>::pool[_POOL_SIZE];\n\ntemplate<typename\
    \ T, int _POOL_SIZE>\nint PoolAllocator<T, _POOL_SIZE>::ptr = 0;\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/PoolAllocator.hpp
  requiredBy: []
  timestamp: '2026-05-05 22:01:14+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/8_luogu/P5055.test.cpp
  - test/8_luogu/P3835_pool.test.cpp
documentation_of: DataStructure/PoolAllocator.hpp
layout: document
redirect_from:
- /library/DataStructure/PoolAllocator.hpp
- /library/DataStructure/PoolAllocator.hpp.html
title: DataStructure/PoolAllocator.hpp
---
