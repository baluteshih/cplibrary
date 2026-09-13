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
  bundledCode: "#line 2 \"Algebra/Monoid/max_v.hpp\"\n\ntemplate<typename T, T inf\
    \ = std::numeric_limits<T>::max()>\nstruct max_v {\n    T val;\n    max_v(T _val\
    \ = -inf): val(_val) {}\n    max_v operator+(const max_v &rhs) const {\n     \
    \   return max_v(std::max(val, rhs.val));\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const max_v &v) {\n        os << v.val;\n        return os;\n    }\n   \
    \ friend std::istream& operator>>(std::istream& is, max_v &v) {\n        is >>\
    \ v.val;\n        return is;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T, T inf = std::numeric_limits<T>::max()>\n\
    struct max_v {\n    T val;\n    max_v(T _val = -inf): val(_val) {}\n    max_v\
    \ operator+(const max_v &rhs) const {\n        return max_v(std::max(val, rhs.val));\n\
    \    }\n    friend std::ostream& operator<<(std::ostream& os, const max_v &v)\
    \ {\n        os << v.val;\n        return os;\n    }\n    friend std::istream&\
    \ operator>>(std::istream& is, max_v &v) {\n        is >> v.val;\n        return\
    \ is;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/Monoid/max_v.hpp
  requiredBy: []
  timestamp: '2026-07-21 00:35:38+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Algebra/Monoid/max_v.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/max_v.hpp
- /library/Algebra/Monoid/max_v.hpp.html
title: Algebra/Monoid/max_v.hpp
---
