---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/sum_v.hpp
    title: Algebra/Monoid/sum_v.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/Tag/add_tag.hpp
    title: Algebra/Tag/add_tag.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/dynamic_tree_subtree_add_subtree_sum.test.cpp
    title: test/1_library_checker/tree/dynamic_tree_subtree_add_subtree_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Acted_Monoid/sum_v-add.hpp\"\n\n#line 2 \"Algebra/Monoid/sum_v.hpp\"\
    \n\ntemplate<typename T>\nstruct sum_v {\n    T val;\n    sum_v(T _val = 0): val(_val)\
    \ {}\n    sum_v operator+(const sum_v &rhs) const {\n        return sum_v(val\
    \ + rhs.val);\n    }\n    friend std::ostream& operator<<(std::ostream& os, const\
    \ sum_v &v) {\n        os << v.val;\n        return os;\n    }\n    friend std::istream&\
    \ operator>>(std::istream& is, sum_v &v) {\n        is >> v.val;\n        return\
    \ is;\n    }\n    operator T() const {\n        return val;\n    }\n};\n#line\
    \ 2 \"Algebra/Tag/add_tag.hpp\"\n\ntemplate<typename T>\nstruct add_tag {\n  \
    \  T a;\n    add_tag(T _a = 0): a(_a) {}\n    add_tag operator+(const add_tag\
    \ &rhs) const {\n        return add_tag(a + rhs.a);\n    }\n    add_tag operator-()\
    \ const {\n        return add_tag(-a);\n    }\n};\n#line 5 \"Algebra/Acted_Monoid/sum_v-add.hpp\"\
    \n\ntemplate<typename T>\nsum_v<T> operator+(const sum_v<T> &lhs, const add_tag<T>\
    \ &rhs) {\n    return sum_v<T>(lhs.val + rhs.a);  \n}\n"
  code: "#pragma once\n\n#include \"Algebra/Monoid/sum_v.hpp\"\n#include \"Algebra/Tag/add_tag.hpp\"\
    \n\ntemplate<typename T>\nsum_v<T> operator+(const sum_v<T> &lhs, const add_tag<T>\
    \ &rhs) {\n    return sum_v<T>(lhs.val + rhs.a);  \n}\n"
  dependsOn:
  - Algebra/Monoid/sum_v.hpp
  - Algebra/Tag/add_tag.hpp
  isVerificationFile: false
  path: Algebra/Acted_Monoid/sum_v-add.hpp
  requiredBy: []
  timestamp: '2026-10-03 12:08:22+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/tree/dynamic_tree_subtree_add_subtree_sum.test.cpp
documentation_of: Algebra/Acted_Monoid/sum_v-add.hpp
layout: document
redirect_from:
- /library/Algebra/Acted_Monoid/sum_v-add.hpp
- /library/Algebra/Acted_Monoid/sum_v-add.hpp.html
title: Algebra/Acted_Monoid/sum_v-add.hpp
---
