---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Sequence/longest_increasing_subsequence.hpp
    title: Sequence/longest_increasing_subsequence.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/other/longest_increasing_subsequence.test.cpp
    title: test/1_library_checker/other/longest_increasing_subsequence.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Monoid/max_v.hpp\"\n\ntemplate<typename T, T neginf\
    \ = std::numeric_limits<T>::lowest()>\nstruct max_v {\n    T val;\n    max_v(T\
    \ _val = neginf): val(_val) {}\n    max_v operator+(const max_v &rhs) const {\n\
    \        return max_v(std::max(val, rhs.val));\n    }\n    friend std::ostream&\
    \ operator<<(std::ostream& os, const max_v &v) {\n        os << v.val;\n     \
    \   return os;\n    }\n    friend std::istream& operator>>(std::istream& is, max_v\
    \ &v) {\n        is >> v.val;\n        return is;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T, T neginf = std::numeric_limits<T>::lowest()>\n\
    struct max_v {\n    T val;\n    max_v(T _val = neginf): val(_val) {}\n    max_v\
    \ operator+(const max_v &rhs) const {\n        return max_v(std::max(val, rhs.val));\n\
    \    }\n    friend std::ostream& operator<<(std::ostream& os, const max_v &v)\
    \ {\n        os << v.val;\n        return os;\n    }\n    friend std::istream&\
    \ operator>>(std::istream& is, max_v &v) {\n        is >> v.val;\n        return\
    \ is;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/Monoid/max_v.hpp
  requiredBy:
  - Sequence/longest_increasing_subsequence.hpp
  timestamp: '2026-10-03 12:58:48+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/other/longest_increasing_subsequence.test.cpp
documentation_of: Algebra/Monoid/max_v.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/max_v.hpp
- /library/Algebra/Monoid/max_v.hpp.html
title: Algebra/Monoid/max_v.hpp
---
