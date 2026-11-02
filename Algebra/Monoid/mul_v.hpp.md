---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/Monoid/mul_v.hpp\"\n\ntemplate<typename T>\nstruct\
    \ mul_v {\n    T val;\n    mul_v(T _val = 1): val(_val) {}\n    mul_v operator+(const\
    \ mul_v &rhs) const {\n        return mul_v(val * rhs.val);\n    }\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const mul_v &v) {\n        os <<\
    \ v.val;\n        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, mul_v &v) {\n        is >> v.val;\n        return is;\n    }\n    operator\
    \ T() const {\n        return val;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nstruct mul_v {\n    T val;\n    mul_v(T\
    \ _val = 1): val(_val) {}\n    mul_v operator+(const mul_v &rhs) const {\n   \
    \     return mul_v(val * rhs.val);\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const mul_v &v) {\n        os << v.val;\n        return os;\n    }\n   \
    \ friend std::istream& operator>>(std::istream& is, mul_v &v) {\n        is >>\
    \ v.val;\n        return is;\n    }\n    operator T() const {\n        return\
    \ val;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/Monoid/mul_v.hpp
  requiredBy: []
  timestamp: '2026-11-02 10:23:25+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Algebra/Monoid/mul_v.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/mul_v.hpp
- /library/Algebra/Monoid/mul_v.hpp.html
title: Algebra/Monoid/mul_v.hpp
---
