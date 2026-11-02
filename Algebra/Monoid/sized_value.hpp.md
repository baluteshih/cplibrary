---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp
    title: test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Monoid/sized_value.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate <typename A, typename B>\nconcept Addable = !std::is_void_v<A> &&\
    \ !std::is_void_v<B> && requires(A a, B b) { a + b; };\n\ntemplate <typename A,\
    \ typename B>\nconcept Subtractable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a - b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a * b; };\n\ntemplate <typename A, typename B>\nconcept AssignAddable =\
    \ !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a += b; };\n\
    \ntemplate <typename A, typename B>\nconcept AssignSubtractable = !std::is_void_v<A>\
    \ && !std::is_void_v<B> && requires(A a, B b) { a -= b; };\n#line 4 \"Algebra/Monoid/sized_value.hpp\"\
    \n\ntemplate <typename T, typename size_type = int>\nstruct sized_value {\n  \
    \  T val;\n    size_type sz;\n    sized_value() : val(), sz(0) {}\n    sized_value(T\
    \ v, size_type s = 1) : val(v), sz(s) {}\n    sized_value operator+(const sized_value\
    \ &rhs) const {\n        return sized_value(val + rhs.val, sz + rhs.sz);\n   \
    \ }\n    template <typename Tag>\n    sized_value& operator+=(const Tag &tag)\
    \ {\n        if constexpr (requires { val.apply(tag, sz); }) {\n            val.apply(tag,\
    \ sz);\n        }\n        else if constexpr (AssignAddable<T, Tag>) {\n     \
    \       val += tag;\n        }\n        else {\n            static_assert(!sizeof(Tag*),\
    \ \"Type T must implement either apply(Tag, size_type) or operator+=(Tag)\");\n\
    \        }\n        return *this;\n    }\n    size_type size() const { return\
    \ sz; }\n    friend std::ostream& operator<<(std::ostream& os, const sized_value\
    \ &v) requires requires(std::ostream& out, const T& inner_val) { out << inner_val;\
    \ } {\n        os << v.val << \" \" << v.sz;\n        return os;\n    }\n};\n"
  code: "#pragma once\n\n#include \"Algebra/ValidOperation.hpp\"\n\ntemplate <typename\
    \ T, typename size_type = int>\nstruct sized_value {\n    T val;\n    size_type\
    \ sz;\n    sized_value() : val(), sz(0) {}\n    sized_value(T v, size_type s =\
    \ 1) : val(v), sz(s) {}\n    sized_value operator+(const sized_value &rhs) const\
    \ {\n        return sized_value(val + rhs.val, sz + rhs.sz);\n    }\n    template\
    \ <typename Tag>\n    sized_value& operator+=(const Tag &tag) {\n        if constexpr\
    \ (requires { val.apply(tag, sz); }) {\n            val.apply(tag, sz);\n    \
    \    }\n        else if constexpr (AssignAddable<T, Tag>) {\n            val +=\
    \ tag;\n        }\n        else {\n            static_assert(!sizeof(Tag*), \"\
    Type T must implement either apply(Tag, size_type) or operator+=(Tag)\");\n  \
    \      }\n        return *this;\n    }\n    size_type size() const { return sz;\
    \ }\n    friend std::ostream& operator<<(std::ostream& os, const sized_value &v)\
    \ requires requires(std::ostream& out, const T& inner_val) { out << inner_val;\
    \ } {\n        os << v.val << \" \" << v.sz;\n        return os;\n    }\n};\n"
  dependsOn:
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: Algebra/Monoid/sized_value.hpp
  requiredBy: []
  timestamp: '2026-11-02 10:56:38+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp
documentation_of: Algebra/Monoid/sized_value.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/sized_value.hpp
- /library/Algebra/Monoid/sized_value.hpp.html
title: Algebra/Monoid/sized_value.hpp
---
