---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/sum_and_size.hpp
    title: Algebra/Monoid/sum_and_size.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/Tag/linear_transform_tag.hpp
    title: Algebra/Tag/linear_transform_tag.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp
    title: test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
    title: test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp\"\
    \n\n#line 2 \"Algebra/Monoid/sum_and_size.hpp\"\n\ntemplate<typename T, typename\
    \ size_type = int>\nstruct sum_and_size {\n    T val;\n    size_type sz;\n   \
    \ sum_and_size(T _val = 0, size_type _sz = 0): val(_val), sz(_sz) {}\n    sum_and_size\
    \ operator+(const sum_and_size &rhs) const {\n        return sum_and_size(val\
    \ + rhs.val, sz + rhs.sz);\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const sum_and_size &v) {\n        os << v.val;\n        return os;\n   \
    \ }\n    friend std::istream& operator>>(std::istream& is, sum_and_size &v) {\n\
    \        is >> v.val;\n        v.sz = 1;\n        return is;\n    }\n};\n#line\
    \ 2 \"Algebra/Tag/linear_transform_tag.hpp\"\n\ntemplate<typename T>\nstruct linear_transform_tag\
    \ {\n    T a, b;\n    linear_transform_tag(T _a = 1, T _b = 0): a(_a), b(_b) {}\n\
    \    linear_transform_tag operator+(const linear_transform_tag &rhs) const {\n\
    \        return linear_transform_tag(a * rhs.a, rhs.a * b + rhs.b);\n    }\n \
    \   bool operator==(const linear_transform_tag &rhs) const {\n        return a\
    \ == rhs.a && b == rhs.b;\n    }\n};\n#line 5 \"Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp\"\
    \n\ntemplate<typename T, typename size_value>\nsum_and_size<T, size_value> operator+(const\
    \ sum_and_size<T, size_value> &lhs, const linear_transform_tag<T> &rhs) {\n  \
    \  return sum_and_size<T, size_value>(lhs.val * rhs.a + lhs.sz * rhs.b, lhs.sz);\
    \  \n}\n"
  code: "#pragma once\n\n#include \"Algebra/Monoid/sum_and_size.hpp\"\n#include \"\
    Algebra/Tag/linear_transform_tag.hpp\"\n\ntemplate<typename T, typename size_value>\n\
    sum_and_size<T, size_value> operator+(const sum_and_size<T, size_value> &lhs,\
    \ const linear_transform_tag<T> &rhs) {\n    return sum_and_size<T, size_value>(lhs.val\
    \ * rhs.a + lhs.sz * rhs.b, lhs.sz);  \n}\n"
  dependsOn:
  - Algebra/Monoid/sum_and_size.hpp
  - Algebra/Tag/linear_transform_tag.hpp
  isVerificationFile: false
  path: Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
  requiredBy: []
  timestamp: '2026-10-02 00:18:20+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp
  - test/1_library_checker/data_structure/range_affine_range_sum.test.cpp
documentation_of: Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
layout: document
redirect_from:
- /library/Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
- /library/Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp.html
title: Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
---
