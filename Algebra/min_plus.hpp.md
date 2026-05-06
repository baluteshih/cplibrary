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
  bundledCode: "#line 2 \"Algebra/min_plus.hpp\"\n\ntemplate<typename T>\nstruct min_plus\
    \ {\n    T a;\n    min_plus(T _a = std::numeric_limits<T>::max() / 2): a(std::min(_a,\
    \ std::numeric_limits<T>::max() / 2)) {}\n    min_plus operator+(const min_plus\
    \ &rhs) const {\n        return min_plus(std::min(a, rhs.a));\n    }\n    min_plus\
    \ operator*(const min_plus &rhs) const {\n        return min_plus(a + rhs.a);\n\
    \    }\n    auto operator<=>(const min_plus &) const = default;\n    friend ostream&\
    \ operator<<(ostream& os, const min_plus &v) {\n        os << v.a;\n        return\
    \ os;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nstruct min_plus {\n    T a;\n    min_plus(T\
    \ _a = std::numeric_limits<T>::max() / 2): a(std::min(_a, std::numeric_limits<T>::max()\
    \ / 2)) {}\n    min_plus operator+(const min_plus &rhs) const {\n        return\
    \ min_plus(std::min(a, rhs.a));\n    }\n    min_plus operator*(const min_plus\
    \ &rhs) const {\n        return min_plus(a + rhs.a);\n    }\n    auto operator<=>(const\
    \ min_plus &) const = default;\n    friend ostream& operator<<(ostream& os, const\
    \ min_plus &v) {\n        os << v.a;\n        return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/min_plus.hpp
  requiredBy: []
  timestamp: '2026-05-05 22:01:14+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Algebra/min_plus.hpp
layout: document
redirect_from:
- /library/Algebra/min_plus.hpp
- /library/Algebra/min_plus.hpp.html
title: Algebra/min_plus.hpp
---
