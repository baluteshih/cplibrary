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
  bundledCode: "#line 1 \"template/treap_value.hpp\"\nstruct treap_v {\n    int sz;\n\
    \    treap_v(int sz_ = 0): sz(sz_) {}\n    treap_v operator+(const treap_v &rhs)\
    \ const {\n        return treap_v(sz + rhs.sz);\n    }\n    int size() const {\n\
    \        return sz; \n    }\n    friend ostream& operator<<(ostream& os, const\
    \ treap_v &v) {\n        os << v.sz;\n        return os;\n    }\n};\n"
  code: "struct treap_v {\n    int sz;\n    treap_v(int sz_ = 0): sz(sz_) {}\n   \
    \ treap_v operator+(const treap_v &rhs) const {\n        return treap_v(sz + rhs.sz);\n\
    \    }\n    int size() const {\n        return sz; \n    }\n    friend ostream&\
    \ operator<<(ostream& os, const treap_v &v) {\n        os << v.sz;\n        return\
    \ os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: template/treap_value.hpp
  requiredBy: []
  timestamp: '2026-06-30 16:12:09+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: template/treap_value.hpp
layout: document
redirect_from:
- /library/template/treap_value.hpp
- /library/template/treap_value.hpp.html
title: template/treap_value.hpp
---
