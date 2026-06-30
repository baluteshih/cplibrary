---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: DataStructure/LeftistTree.hpp
    title: Leftist Tree
  - icon: ':heavy_check_mark:'
    path: DataStructure/Treap.hpp
    title: Treap
  - icon: ':x:'
    path: Graph/minimum_arborescence.hpp
    title: Graph/minimum_arborescence.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp
    title: test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set_treap.test.cpp
    title: test/1_library_checker/data_structure/ordered_set_treap.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_reverse_range_sum.test.cpp
    title: test/1_library_checker/data_structure/range_reverse_range_sum.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/graph/directedmst.test.cpp
    title: test/1_library_checker/graph/directedmst.test.cpp
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
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/size_value.hpp\"\n\nstruct size_v {\n    int sz;\n\
    \    size_v(int sz_ = 0): sz(sz_) {}\n    size_v operator+(const size_v &rhs)\
    \ const {\n        return size_v(sz + rhs.sz);\n    }\n    int size() const {\n\
    \        return sz; \n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const size_v &v) {\n        os << v.sz;\n        return os;\n    }\n};\n"
  code: "#pragma once\n\nstruct size_v {\n    int sz;\n    size_v(int sz_ = 0): sz(sz_)\
    \ {}\n    size_v operator+(const size_v &rhs) const {\n        return size_v(sz\
    \ + rhs.sz);\n    }\n    int size() const {\n        return sz; \n    }\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const size_v &v) {\n        os <<\
    \ v.sz;\n        return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/size_value.hpp
  requiredBy:
  - Graph/minimum_arborescence.hpp
  - DataStructure/LeftistTree.hpp
  - DataStructure/Treap.hpp
  timestamp: '2026-06-18 22:20:51+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/1_library_checker/data_structure/range_reverse_range_sum.test.cpp
  - test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum.test.cpp
  - test/1_library_checker/data_structure/ordered_set_treap.test.cpp
  - test/1_library_checker/graph/directedmst.test.cpp
  - test/8_luogu/P3835_pool.test.cpp
  - test/8_luogu/P3835.test.cpp
  - test/8_luogu/P5055.test.cpp
  - test/3_qoj/17153.test.cpp
documentation_of: Algebra/size_value.hpp
layout: document
redirect_from:
- /library/Algebra/size_value.hpp
- /library/Algebra/size_value.hpp.html
title: Algebra/size_value.hpp
---
