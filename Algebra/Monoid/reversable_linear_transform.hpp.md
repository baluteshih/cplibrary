---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: Algebra/Monoid/linear_transform.hpp
    title: Algebra/Monoid/linear_transform.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/1_library_checker/tree/dynamic_tree_vertex_set_path_composite.test.cpp
    title: test/1_library_checker/tree/dynamic_tree_vertex_set_path_composite.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Monoid/reversable_linear_transform.hpp\"\n\n#line\
    \ 2 \"Algebra/Monoid/linear_transform.hpp\"\n\ntemplate<typename T>\nstruct linear_transform\
    \ {\n    T a, b;\n    linear_transform(T _a = 1, T _b = 0) : a(_a), b(_b) {}\n\
    \    linear_transform operator+(const linear_transform &rhs) const {\n       \
    \ return linear_transform(a * rhs.a, rhs.a * b + rhs.b);\n    }\n    T eval(T\
    \ x) {\n        return a * x + b;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, linear_transform &v) {\n        is >> v.a >> v.b;\n        return is;\n\
    \    }\n};\n#line 4 \"Algebra/Monoid/reversable_linear_transform.hpp\"\n\ntemplate<typename\
    \ T>\nstruct reversable_linear_transform {\n    T a_f = 1, b_f = 0, a_b = 1, b_b\
    \ = 0;\n    reversable_linear_transform(T _a_f = 1, T _b_f = 0, T _a_b = 1, T\
    \ _b_b = 0) : a_f(_a_f), b_f(_b_f), a_b(_a_b), b_b(_b_b) {}\n    reversable_linear_transform(const\
    \ linear_transform<T> &v) : a_f(v.a), b_f(v.b), a_b(v.a), b_b(v.b) {}\n    reversable_linear_transform\
    \ operator+(const reversable_linear_transform<T> &rhs) const {\n        return\
    \ reversable_linear_transform(rhs.a_f * a_f, rhs.a_f * b_f + rhs.b_f, a_b * rhs.a_b,\
    \ a_b * rhs.b_b + b_b);\n    }\n    void reverse() {\n        std::swap(a_f, a_b);\n\
    \        std::swap(b_f, b_b);\n    }\n    T eval(T x) {\n        return a_f *\
    \ x + b_f;\n    }\n};\n"
  code: "#pragma once\n\n#include \"Algebra/Monoid/linear_transform.hpp\"\n\ntemplate<typename\
    \ T>\nstruct reversable_linear_transform {\n    T a_f = 1, b_f = 0, a_b = 1, b_b\
    \ = 0;\n    reversable_linear_transform(T _a_f = 1, T _b_f = 0, T _a_b = 1, T\
    \ _b_b = 0) : a_f(_a_f), b_f(_b_f), a_b(_a_b), b_b(_b_b) {}\n    reversable_linear_transform(const\
    \ linear_transform<T> &v) : a_f(v.a), b_f(v.b), a_b(v.a), b_b(v.b) {}\n    reversable_linear_transform\
    \ operator+(const reversable_linear_transform<T> &rhs) const {\n        return\
    \ reversable_linear_transform(rhs.a_f * a_f, rhs.a_f * b_f + rhs.b_f, a_b * rhs.a_b,\
    \ a_b * rhs.b_b + b_b);\n    }\n    void reverse() {\n        std::swap(a_f, a_b);\n\
    \        std::swap(b_f, b_b);\n    }\n    T eval(T x) {\n        return a_f *\
    \ x + b_f;\n    }\n};\n"
  dependsOn:
  - Algebra/Monoid/linear_transform.hpp
  isVerificationFile: false
  path: Algebra/Monoid/reversable_linear_transform.hpp
  requiredBy: []
  timestamp: '2026-10-03 12:08:22+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/1_library_checker/tree/dynamic_tree_vertex_set_path_composite.test.cpp
documentation_of: Algebra/Monoid/reversable_linear_transform.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/reversable_linear_transform.hpp
- /library/Algebra/Monoid/reversable_linear_transform.hpp.html
title: Algebra/Monoid/reversable_linear_transform.hpp
---
