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
  bundledCode: "#line 2 \"Algebra/max_plus.hpp\"\n\ntemplate<typename T>\nstruct max_plus\
    \ {\n    T a;\n    max_plus(T _a = -std::numeric_limits<T>::max() / 2): a(std::max(_a,\
    \ -std::numeric_limits<T>::max() / 2)) {}\n    max_plus operator+(const max_plus\
    \ &rhs) const {\n        return max_plus(std::max(a, rhs.a));\n    }\n    max_plus\
    \ operator*(const max_plus &rhs) const {\n        return max_plus(a + rhs.a);\n\
    \    }\n    auto operator<=>(const max_plus &) const = default;\n    friend ostream&\
    \ operator<<(ostream& os, const max_plus &v) {\n        os << v.a;\n        return\
    \ os;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nstruct max_plus {\n    T a;\n    max_plus(T\
    \ _a = -std::numeric_limits<T>::max() / 2): a(std::max(_a, -std::numeric_limits<T>::max()\
    \ / 2)) {}\n    max_plus operator+(const max_plus &rhs) const {\n        return\
    \ max_plus(std::max(a, rhs.a));\n    }\n    max_plus operator*(const max_plus\
    \ &rhs) const {\n        return max_plus(a + rhs.a);\n    }\n    auto operator<=>(const\
    \ max_plus &) const = default;\n    friend ostream& operator<<(ostream& os, const\
    \ max_plus &v) {\n        os << v.a;\n        return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/max_plus.hpp
  requiredBy: []
  timestamp: '2026-05-05 22:01:14+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Algebra/max_plus.hpp
layout: document
redirect_from:
- /library/Algebra/max_plus.hpp
- /library/Algebra/max_plus.hpp.html
title: Algebra/max_plus.hpp
---
