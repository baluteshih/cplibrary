---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/reversable_linear_transform.hpp
    title: Algebra/Monoid/reversable_linear_transform.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/dynamic_tree_vertex_set_path_composite.test.cpp
    title: test/1_library_checker/tree/dynamic_tree_vertex_set_path_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Monoid/linear_transform.hpp\"\n\ntemplate<typename\
    \ T>\nstruct linear_transform {\n    T a, b;\n    linear_transform(T _a = 1, T\
    \ _b = 0) : a(_a), b(_b) {}\n    linear_transform operator+(const linear_transform\
    \ &rhs) const {\n        return linear_transform(a * rhs.a, rhs.a * b + rhs.b);\n\
    \    }\n    T eval(T x) {\n        return a * x + b;\n    }\n    friend std::istream&\
    \ operator>>(std::istream& is, linear_transform &v) {\n        is >> v.a >> v.b;\n\
    \        return is;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nstruct linear_transform {\n    T a,\
    \ b;\n    linear_transform(T _a = 1, T _b = 0) : a(_a), b(_b) {}\n    linear_transform\
    \ operator+(const linear_transform &rhs) const {\n        return linear_transform(a\
    \ * rhs.a, rhs.a * b + rhs.b);\n    }\n    T eval(T x) {\n        return a * x\
    \ + b;\n    }\n    friend std::istream& operator>>(std::istream& is, linear_transform\
    \ &v) {\n        is >> v.a >> v.b;\n        return is;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/Monoid/linear_transform.hpp
  requiredBy:
  - Algebra/Monoid/reversable_linear_transform.hpp
  timestamp: '2026-10-03 12:08:22+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/tree/dynamic_tree_vertex_set_path_composite.test.cpp
documentation_of: Algebra/Monoid/linear_transform.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/linear_transform.hpp
- /library/Algebra/Monoid/linear_transform.hpp.html
title: Algebra/Monoid/linear_transform.hpp
---
