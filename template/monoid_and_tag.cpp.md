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
  bundledCode: "#line 1 \"template/monoid_and_tag.cpp\"\nstruct Tag {\n    int a;\n\
    \    Tag(int _a = 0): a(_a) {}\n    Tag operator+(const Tag &rhs) {\n        return\
    \ Tag(a + rhs.a);\n    }\n};\n\nstruct Value {\n    int val;\n    Value(int _val\
    \ = 0): val(_val) {}\n    Value operator+(const Value &rhs) {\n        return\
    \ Value(min(val, rhs.val));\n    }\n    Value operator+(const Tag &tag) {\n  \
    \      return Value(val + tag.a);\n    }\n    friend ostream& operator<<(ostream&\
    \ os, const Value &v) {\n        os << v.val;\n        return os;\n    }\n   \
    \ friend istream& operator>>(istream& is, Value &v) {\n        is >> v.val;\n\
    \        return is;\n    }\n};\n"
  code: "struct Tag {\n    int a;\n    Tag(int _a = 0): a(_a) {}\n    Tag operator+(const\
    \ Tag &rhs) {\n        return Tag(a + rhs.a);\n    }\n};\n\nstruct Value {\n \
    \   int val;\n    Value(int _val = 0): val(_val) {}\n    Value operator+(const\
    \ Value &rhs) {\n        return Value(min(val, rhs.val));\n    }\n    Value operator+(const\
    \ Tag &tag) {\n        return Value(val + tag.a);\n    }\n    friend ostream&\
    \ operator<<(ostream& os, const Value &v) {\n        os << v.val;\n        return\
    \ os;\n    }\n    friend istream& operator>>(istream& is, Value &v) {\n      \
    \  is >> v.val;\n        return is;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: template/monoid_and_tag.cpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: template/monoid_and_tag.cpp
layout: document
redirect_from:
- /library/template/monoid_and_tag.cpp
- /library/template/monoid_and_tag.cpp.html
title: template/monoid_and_tag.cpp
---
