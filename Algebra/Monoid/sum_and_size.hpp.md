---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
    title: Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
    title: test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Monoid/sum_and_size.hpp\"\n\ntemplate<typename T,\
    \ typename size_type = int>\nstruct sum_and_size {\n    T val;\n    size_type\
    \ sz;\n    sum_and_size(T _val = 0, size_type _sz = 0): val(_val), sz(_sz) {}\n\
    \    sum_and_size operator+(const sum_and_size &rhs) const {\n        return sum_and_size(val\
    \ + rhs.val, sz + rhs.sz);\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const sum_and_size &v) {\n        os << v.val;\n        return os;\n   \
    \ }\n    friend std::istream& operator>>(std::istream& is, sum_and_size &v) {\n\
    \        is >> v.val;\n        v.sz = 1;\n        return is;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T, typename size_type = int>\nstruct sum_and_size\
    \ {\n    T val;\n    size_type sz;\n    sum_and_size(T _val = 0, size_type _sz\
    \ = 0): val(_val), sz(_sz) {}\n    sum_and_size operator+(const sum_and_size &rhs)\
    \ const {\n        return sum_and_size(val + rhs.val, sz + rhs.sz);\n    }\n \
    \   friend std::ostream& operator<<(std::ostream& os, const sum_and_size &v) {\n\
    \        os << v.val;\n        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, sum_and_size &v) {\n        is >> v.val;\n        v.sz = 1;\n        return\
    \ is;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/Monoid/sum_and_size.hpp
  requiredBy:
  - Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
  timestamp: '2026-09-25 22:41:03+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
documentation_of: Algebra/Monoid/sum_and_size.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/sum_and_size.hpp
- /library/Algebra/Monoid/sum_and_size.hpp.html
title: Algebra/Monoid/sum_and_size.hpp
---
