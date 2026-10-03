---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/min_v.hpp
    title: Algebra/Monoid/min_v.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/Tag/add_tag.hpp
    title: Algebra/Tag/add_tag.hpp
  - icon: ':question:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  _extendedRequiredBy: []
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
  bundledCode: "#line 2 \"Algebra/Acted_Monoid/min_v-add.hpp\"\n\n#line 2 \"Algebra/Monoid/min_v.hpp\"\
    \n\ntemplate<typename T, T inf = std::numeric_limits<T>::max()>\nstruct min_v\
    \ {\n    T val;\n    min_v(T _val = inf): val(_val) {}\n    min_v operator+(const\
    \ min_v &rhs) const {\n        return min_v(std::min(val, rhs.val));\n    }\n\
    \    friend std::ostream& operator<<(std::ostream& os, const min_v &v) {\n   \
    \     os << v.val;\n        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, min_v &v) {\n        is >> v.val;\n        return is;\n    }\n};\n#line\
    \ 2 \"Algebra/Tag/add_tag.hpp\"\n\ntemplate<typename T>\nstruct add_tag {\n  \
    \  T a;\n    add_tag(T _a = 0): a(_a) {}\n    add_tag operator+(const add_tag\
    \ &rhs) const {\n        return add_tag(a + rhs.a);\n    }\n    add_tag operator-()\
    \ const {\n        return add_tag(-a);\n    }\n};\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate <typename A, typename B>\nconcept Addable = !std::is_void_v<A> &&\
    \ !std::is_void_v<B> && requires(A a, B b) { a + b; };\n\ntemplate <typename A,\
    \ typename B>\nconcept Subtractable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a - b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a * b; };\n#line 6 \"Algebra/Acted_Monoid/min_v-add.hpp\"\n\ntemplate<typename\
    \ T, typename U>\nmin_v<T> operator+(const min_v<T> &lhs, const add_tag<U> &rhs)\
    \ {\n    return min_v<T>(lhs.val + rhs.a);  \n}\n\ntemplate<typename T, typename\
    \ U>\nmin_v<T> operator-(const min_v<T> &lhs, const add_tag<U> &rhs) requires\
    \ (Subtractable<T, U>) {\n    return min_v<T>(lhs.val - rhs.a);  \n}\n"
  code: "#pragma once\n\n#include \"Algebra/Monoid/min_v.hpp\"\n#include \"Algebra/Tag/add_tag.hpp\"\
    \n#include \"Algebra/ValidOperation.hpp\"\n\ntemplate<typename T, typename U>\n\
    min_v<T> operator+(const min_v<T> &lhs, const add_tag<U> &rhs) {\n    return min_v<T>(lhs.val\
    \ + rhs.a);  \n}\n\ntemplate<typename T, typename U>\nmin_v<T> operator-(const\
    \ min_v<T> &lhs, const add_tag<U> &rhs) requires (Subtractable<T, U>) {\n    return\
    \ min_v<T>(lhs.val - rhs.a);  \n}\n"
  dependsOn:
  - Algebra/Monoid/min_v.hpp
  - Algebra/Tag/add_tag.hpp
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: Algebra/Acted_Monoid/min_v-add.hpp
  requiredBy: []
  timestamp: '2026-10-03 12:08:22+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/range_add_range_min_zkw2.test.cpp
  - test/1_library_checker/data_structure/range_add_range_min_zkw.test.cpp
documentation_of: Algebra/Acted_Monoid/min_v-add.hpp
layout: document
redirect_from:
- /library/Algebra/Acted_Monoid/min_v-add.hpp
- /library/Algebra/Acted_Monoid/min_v-add.hpp.html
title: Algebra/Acted_Monoid/min_v-add.hpp
---
