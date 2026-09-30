---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Algebra/Acted_Monoid/min_v-add.hpp
    title: Algebra/Acted_Monoid/min_v-add.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_add_range_min_zkw.test.cpp
    title: test/1_library_checker/data_structure/range_add_range_min_zkw.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_add_range_min_zkw2.test.cpp
    title: test/1_library_checker/data_structure/range_add_range_min_zkw2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Tag/add_tag.hpp\"\n\ntemplate<typename T>\nstruct\
    \ add_tag {\n    T a;\n    add_tag(T _a = 0): a(_a) {}\n    add_tag operator+(const\
    \ add_tag &rhs) const {\n        return add_tag(a + rhs.a);\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nstruct add_tag {\n    T a;\n    add_tag(T\
    \ _a = 0): a(_a) {}\n    add_tag operator+(const add_tag &rhs) const {\n     \
    \   return add_tag(a + rhs.a);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/Tag/add_tag.hpp
  requiredBy:
  - Algebra/Acted_Monoid/min_v-add.hpp
  timestamp: '2026-09-30 16:19:43+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/range_add_range_min_zkw2.test.cpp
  - test/1_library_checker/data_structure/range_add_range_min_zkw.test.cpp
documentation_of: Algebra/Tag/add_tag.hpp
layout: document
redirect_from:
- /library/Algebra/Tag/add_tag.hpp
- /library/Algebra/Tag/add_tag.hpp.html
title: Algebra/Tag/add_tag.hpp
---
