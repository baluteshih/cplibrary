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
  bundledCode: "#line 2 \"Algebra/Tag/linear_transform_tag.hpp\"\n\ntemplate<typename\
    \ T>\nstruct linear_transform_tag {\n    T a, b;\n    linear_transform_tag(T _a\
    \ = 1, T _b = 0): a(_a), b(_b) {}\n    linear_transform_tag operator+(const linear_transform_tag\
    \ &rhs) const {\n        return linear_transform_tag(a * rhs.a, rhs.a * b + rhs.b);\n\
    \    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nstruct linear_transform_tag {\n   \
    \ T a, b;\n    linear_transform_tag(T _a = 1, T _b = 0): a(_a), b(_b) {}\n   \
    \ linear_transform_tag operator+(const linear_transform_tag &rhs) const {\n  \
    \      return linear_transform_tag(a * rhs.a, rhs.a * b + rhs.b);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/Tag/linear_transform_tag.hpp
  requiredBy:
  - Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
  timestamp: '2026-09-30 16:19:43+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
documentation_of: Algebra/Tag/linear_transform_tag.hpp
layout: document
redirect_from:
- /library/Algebra/Tag/linear_transform_tag.hpp
- /library/Algebra/Tag/linear_transform_tag.hpp.html
title: Algebra/Tag/linear_transform_tag.hpp
---
