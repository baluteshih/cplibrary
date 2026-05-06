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
  bundledCode: "#line 1 \"template/treap_value.hpp\"\nstruct size_v {\n    int sz;\n\
    \    size_v(int sz_ = 0): sz(sz_) {}\n    size_v operator+(const size_v &rhs)\
    \ const {\n        return size_v(sz + rhs.sz);\n    }\n    int size() const {\n\
    \        return sz; \n    }\n    friend ostream& operator<<(ostream& os, const\
    \ size_v &v) {\n        os << v.sz;\n        return os;\n    }\n};\n"
  code: "struct size_v {\n    int sz;\n    size_v(int sz_ = 0): sz(sz_) {}\n    size_v\
    \ operator+(const size_v &rhs) const {\n        return size_v(sz + rhs.sz);\n\
    \    }\n    int size() const {\n        return sz; \n    }\n    friend ostream&\
    \ operator<<(ostream& os, const size_v &v) {\n        os << v.sz;\n        return\
    \ os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: template/treap_value.hpp
  requiredBy: []
  timestamp: '2026-05-05 22:01:14+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: template/treap_value.hpp
layout: document
redirect_from:
- /library/template/treap_value.hpp
- /library/template/treap_value.hpp.html
title: template/treap_value.hpp
---
