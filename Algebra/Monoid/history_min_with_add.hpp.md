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
  bundledCode: "#line 2 \"Algebra/Monoid/history_min_with_add.hpp\"\n\ntemplate<typename\
    \ T>\nstruct history_min_add_tag {\n    T v, hv;\n    history_min_add_tag() :\
    \ v(), hv() {}\n    history_min_add_tag(T _v, T _hv) : v(_v), hv(_hv) {}\n   \
    \ history_min_add_tag(T _v) : v(_v), hv(std::min(_v, 0)) {}\n    history_min_add_tag\
    \ operator+(const history_min_add_tag &rhs) const {\n        return history_min_add_tag(v\
    \ + rhs.v, std::min(hv, v + rhs.hv));\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const history_min_add_tag &v) {\n        os << v.v << \" \" << v.hv;\n \
    \       return os;\n    }\n};\n\ntemplate<typename T, T inf = std::numeric_limits<T>::max()>\n\
    struct history_min {\n    T val, hval;\n    history_min(T _val = inf, T _hval\
    \ = inf) : val(_val), hval(_hval) {}\n    history_min operator+(const history_min\
    \ &rhs) const {\n        return history_min(std::min(val, rhs.val), std::min(hval,\
    \ rhs.hval));\n    }\n    template<typename U>\n    history_min operator+(const\
    \ history_min_add_tag<U> &tag) const {\n        return history_min(val + tag.v,\
    \ std::min(hval, val + tag.hv));\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const history_min &v) {\n        os << v.hval;\n        return os;\n   \
    \ }\n    friend std::istream& operator>>(std::istream& is, history_min &v) {\n\
    \        is >> v.val;\n        return is;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nstruct history_min_add_tag {\n    T\
    \ v, hv;\n    history_min_add_tag() : v(), hv() {}\n    history_min_add_tag(T\
    \ _v, T _hv) : v(_v), hv(_hv) {}\n    history_min_add_tag(T _v) : v(_v), hv(std::min(_v,\
    \ 0)) {}\n    history_min_add_tag operator+(const history_min_add_tag &rhs) const\
    \ {\n        return history_min_add_tag(v + rhs.v, std::min(hv, v + rhs.hv));\n\
    \    }\n    friend std::ostream& operator<<(std::ostream& os, const history_min_add_tag\
    \ &v) {\n        os << v.v << \" \" << v.hv;\n        return os;\n    }\n};\n\n\
    template<typename T, T inf = std::numeric_limits<T>::max()>\nstruct history_min\
    \ {\n    T val, hval;\n    history_min(T _val = inf, T _hval = inf) : val(_val),\
    \ hval(_hval) {}\n    history_min operator+(const history_min &rhs) const {\n\
    \        return history_min(std::min(val, rhs.val), std::min(hval, rhs.hval));\n\
    \    }\n    template<typename U>\n    history_min operator+(const history_min_add_tag<U>\
    \ &tag) const {\n        return history_min(val + tag.v, std::min(hval, val +\
    \ tag.hv));\n    }\n    friend std::ostream& operator<<(std::ostream& os, const\
    \ history_min &v) {\n        os << v.hval;\n        return os;\n    }\n    friend\
    \ std::istream& operator>>(std::istream& is, history_min &v) {\n        is >>\
    \ v.val;\n        return is;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/Monoid/history_min_with_add.hpp
  requiredBy: []
  timestamp: '2026-07-21 00:35:38+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Algebra/Monoid/history_min_with_add.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/history_min_with_add.hpp
- /library/Algebra/Monoid/history_min_with_add.hpp.html
title: Algebra/Monoid/history_min_with_add.hpp
---
