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
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_rmq.test.cpp
    title: test/1_library_checker/data_structure/static_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Monoid/min_v.hpp\"\n\ntemplate<typename T, T inf\
    \ = std::numeric_limits<T>::max()>\nstruct min_v {\n    T val;\n    min_v(T _val\
    \ = inf): val(_val) {}\n    min_v operator+(const min_v &rhs) const {\n      \
    \  return min_v(std::min(val, rhs.val));\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const min_v &v) {\n        os << v.val;\n        return os;\n    }\n   \
    \ friend std::istream& operator>>(std::istream& is, min_v &v) {\n        is >>\
    \ v.val;\n        return is;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T, T inf = std::numeric_limits<T>::max()>\n\
    struct min_v {\n    T val;\n    min_v(T _val = inf): val(_val) {}\n    min_v operator+(const\
    \ min_v &rhs) const {\n        return min_v(std::min(val, rhs.val));\n    }\n\
    \    friend std::ostream& operator<<(std::ostream& os, const min_v &v) {\n   \
    \     os << v.val;\n        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, min_v &v) {\n        is >> v.val;\n        return is;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/Monoid/min_v.hpp
  requiredBy:
  - Algebra/Acted_Monoid/min_v-add.hpp
  timestamp: '2026-07-21 00:35:38+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/range_add_range_min_zkw2.test.cpp
  - test/1_library_checker/data_structure/range_add_range_min_zkw.test.cpp
  - test/1_library_checker/data_structure/static_rmq.test.cpp
documentation_of: Algebra/Monoid/min_v.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/min_v.hpp
- /library/Algebra/Monoid/min_v.hpp.html
title: Algebra/Monoid/min_v.hpp
---
