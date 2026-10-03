---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Algebra/Acted_Monoid/sum_v-add.hpp
    title: Algebra/Acted_Monoid/sum_v-add.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/dynamic_tree_subtree_add_subtree_sum.test.cpp
    title: test/1_library_checker/tree/dynamic_tree_subtree_add_subtree_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Monoid/sum_v.hpp\"\n\ntemplate<typename T>\nstruct\
    \ sum_v {\n    T val;\n    sum_v(T _val = 0): val(_val) {}\n    sum_v operator+(const\
    \ sum_v &rhs) const {\n        return sum_v(val + rhs.val);\n    }\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const sum_v &v) {\n        os <<\
    \ v.val;\n        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, sum_v &v) {\n        is >> v.val;\n        return is;\n    }\n    operator\
    \ T() const {\n        return val;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nstruct sum_v {\n    T val;\n    sum_v(T\
    \ _val = 0): val(_val) {}\n    sum_v operator+(const sum_v &rhs) const {\n   \
    \     return sum_v(val + rhs.val);\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const sum_v &v) {\n        os << v.val;\n        return os;\n    }\n   \
    \ friend std::istream& operator>>(std::istream& is, sum_v &v) {\n        is >>\
    \ v.val;\n        return is;\n    }\n    operator T() const {\n        return\
    \ val;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/Monoid/sum_v.hpp
  requiredBy:
  - Algebra/Acted_Monoid/sum_v-add.hpp
  timestamp: '2026-10-03 12:08:22+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/tree/dynamic_tree_subtree_add_subtree_sum.test.cpp
documentation_of: Algebra/Monoid/sum_v.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/sum_v.hpp
- /library/Algebra/Monoid/sum_v.hpp.html
title: Algebra/Monoid/sum_v.hpp
---
