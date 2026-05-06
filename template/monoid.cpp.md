---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"template/monoid.cpp\"\nstruct Value {\n    int val;\n  \
    \  Value(int _v = 0): val(_v) {}\n    Value operator+(const Value &rhs) {\n  \
    \      return Value(min(val, rhs.val));\n    }\n    friend ostream& operator<<(ostream&\
    \ os, const Value &v) {\n        os << v.val;\n        return os;\n    }\n   \
    \ friend istream& operator>>(istream& is, Value &v) {\n        is >> v.val;\n\
    \        return is;\n    }\n};\n"
  code: "struct Value {\n    int val;\n    Value(int _v = 0): val(_v) {}\n    Value\
    \ operator+(const Value &rhs) {\n        return Value(min(val, rhs.val));\n  \
    \  }\n    friend ostream& operator<<(ostream& os, const Value &v) {\n        os\
    \ << v.val;\n        return os;\n    }\n    friend istream& operator>>(istream&\
    \ is, Value &v) {\n        is >> v.val;\n        return is;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: template/monoid.cpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: template/monoid.cpp
layout: document
redirect_from:
- /library/template/monoid.cpp
- /library/template/monoid.cpp.html
title: template/monoid.cpp
---
