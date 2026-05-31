---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: DataStructure/PointerSegmentTree.hpp
    title: DataStructure/PointerSegmentTree.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/Treap.hpp
    title: DataStructure/Treap.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set_treap.test.cpp
    title: test/1_library_checker/data_structure/ordered_set_treap.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp
    title: test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/point_set_range_composite_large_array.test.cpp
    title: test/1_library_checker/data_structure/point_set_range_composite_large_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/point_set_range_composite_pointer.test.cpp
    title: test/1_library_checker/data_structure/point_set_range_composite_pointer.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/point_set_range_frequency.test.cpp
    title: test/1_library_checker/data_structure/point_set_range_frequency.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_affine_range_sum_large_array.test.cpp
    title: test/1_library_checker/data_structure/range_affine_range_sum_large_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_affine_range_sum_pointer.test.cpp
    title: test/1_library_checker/data_structure/range_affine_range_sum_pointer.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_reverse_range_sum.test.cpp
    title: test/1_library_checker/data_structure/range_reverse_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/3_qoj/17153.test.cpp
    title: test/3_qoj/17153.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/8_luogu/P3835.test.cpp
    title: test/8_luogu/P3835.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/8_luogu/P3835_pool.test.cpp
    title: test/8_luogu/P3835_pool.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/8_luogu/P5055.test.cpp
    title: test/8_luogu/P5055.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/DefaultAllocator.hpp\"\n\ntemplate<typename\
    \ T>\nstruct DefaultAllocator {\n    template<typename... Args>\n    static T*\
    \ allocate(Args&&... args) { \n        return new T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { delete p; }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nstruct DefaultAllocator {\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        return new T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { delete p; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/DefaultAllocator.hpp
  requiredBy:
  - DataStructure/PointerSegmentTree.hpp
  - DataStructure/Treap.hpp
  timestamp: '2026-05-05 22:01:14+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/8_luogu/P3835_pool.test.cpp
  - test/8_luogu/P3835.test.cpp
  - test/8_luogu/P5055.test.cpp
  - test/1_library_checker/data_structure/ordered_set_treap.test.cpp
  - test/1_library_checker/data_structure/range_affine_range_sum_pointer.test.cpp
  - test/1_library_checker/data_structure/point_set_range_composite_pointer.test.cpp
  - test/1_library_checker/data_structure/range_affine_range_sum_large_array.test.cpp
  - test/1_library_checker/data_structure/point_set_range_composite_large_array.test.cpp
  - test/1_library_checker/data_structure/point_set_range_frequency.test.cpp
  - test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp
  - test/1_library_checker/data_structure/range_reverse_range_sum.test.cpp
  - test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp
  - test/3_qoj/17153.test.cpp
documentation_of: DataStructure/DefaultAllocator.hpp
layout: document
redirect_from:
- /library/DataStructure/DefaultAllocator.hpp
- /library/DataStructure/DefaultAllocator.hpp.html
title: DataStructure/DefaultAllocator.hpp
---
