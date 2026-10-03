---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/sum_and_size.hpp
    title: Algebra/Monoid/sum_and_size.hpp
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
  bundledCode: "#line 2 \"Algebra/Acted_Monoid/sum_and_size-add.hpp\"\n\n#line 2 \"\
    Algebra/Monoid/sum_and_size.hpp\"\n\ntemplate<typename T, typename size_type =\
    \ int>\nstruct sum_and_size {\n    T val;\n    size_type sz;\n    sum_and_size(T\
    \ _val, size_type _sz) : val(_val), sz(_sz) {}\n    sum_and_size(T _val) : sum_and_size(_val,\
    \ 1) {}\n    sum_and_size() : sum_and_size(0, 0) {}\n    sum_and_size operator+(const\
    \ sum_and_size &rhs) const {\n        return sum_and_size(val + rhs.val, sz +\
    \ rhs.sz);\n    }\n    sum_and_size operator-(const sum_and_size &rhs) const {\n\
    \        return sum_and_size(val - rhs.val, sz - rhs.sz);\n    }\n    friend std::ostream&\
    \ operator<<(std::ostream& os, const sum_and_size &v) {\n        os << v.val;\n\
    \        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, sum_and_size &v) {\n        is >> v.val;\n        v.sz = 1;\n        return\
    \ is;\n    }\n};\n#line 2 \"Algebra/Tag/add_tag.hpp\"\n\ntemplate<typename T>\n\
    struct add_tag {\n    T a;\n    add_tag(T _a = 0): a(_a) {}\n    add_tag operator+(const\
    \ add_tag &rhs) const {\n        return add_tag(a + rhs.a);\n    }\n    add_tag\
    \ operator-() const {\n        return add_tag(-a);\n    }\n};\n#line 5 \"Algebra/Acted_Monoid/sum_and_size-add.hpp\"\
    \n\ntemplate<typename T, typename size_value>\nsum_and_size<T, size_value> operator+(const\
    \ sum_and_size<T, size_value> &lhs, const add_tag<T> &rhs) {\n    return sum_and_size<T,\
    \ size_value>(lhs.val + rhs.a * lhs.sz, lhs.sz);  \n}\n"
  code: "#pragma once\n\n#include \"Algebra/Monoid/sum_and_size.hpp\"\n#include \"\
    Algebra/Tag/add_tag.hpp\"\n\ntemplate<typename T, typename size_value>\nsum_and_size<T,\
    \ size_value> operator+(const sum_and_size<T, size_value> &lhs, const add_tag<T>\
    \ &rhs) {\n    return sum_and_size<T, size_value>(lhs.val + rhs.a * lhs.sz, lhs.sz);\
    \  \n}\n"
  dependsOn:
  - Algebra/Monoid/sum_and_size.hpp
  - Algebra/Tag/add_tag.hpp
  isVerificationFile: false
  path: Algebra/Acted_Monoid/sum_and_size-add.hpp
  requiredBy: []
  timestamp: '2026-10-03 12:08:22+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/tree/dynamic_tree_subtree_add_subtree_sum.test.cpp
documentation_of: Algebra/Acted_Monoid/sum_and_size-add.hpp
layout: document
redirect_from:
- /library/Algebra/Acted_Monoid/sum_and_size-add.hpp
- /library/Algebra/Acted_Monoid/sum_and_size-add.hpp.html
title: Algebra/Acted_Monoid/sum_and_size-add.hpp
---
