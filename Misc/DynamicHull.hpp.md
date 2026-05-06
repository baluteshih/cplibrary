---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/line_add_get_min.test.cpp
    title: test/1_library_checker/data_structure/line_add_get_min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Misc/DynamicHull.hpp\"\n\n// only works for integer coordinates!!\
    \ maintain max\ntemplate<typename T>\nstruct Line {\n    mutable T a, b, p;\n\
    \    bool operator<(const Line &rhs) const { return a < rhs.a; }\n    bool operator<(T\
    \ x) const { return p < x; }\n};\ntemplate<typename T, T kInf = 1'000'000'000'000'000'000LL>\n\
    struct DynamicHull : multiset<Line<T>, less<>> {\n    using iterator = multiset<Line<T>,\
    \ less<>>::iterator; \n    T Div(T a, T b) { return a / b - ((a ^ b) < 0 && a\
    \ % b); }\n    bool isect(iterator x, iterator y) {\n        if (y == this->end())\
    \ { x->p = kInf; return 0; }\n        if (x->a == y->a) x->p = x->b > y->b ? kInf\
    \ : -kInf;\n        else x->p = Div(y->b - x->b, x->a - y->a);\n        return\
    \ x->p >= y->p;\n    }\n    void addline(T a, T b) {\n        auto z = this->emplace(a,\
    \ b, 0), y = z++, x = y;\n        while (isect(y, z)) z = this->erase(z);\n  \
    \      if (x != this->begin() && isect(--x, y)) isect(x, y = this->erase(y));\n\
    \        while ((y = x) != this->begin() && (--x)->p >= y->p) isect(x, this->erase(y));\n\
    \    }\n    T query(T x) {\n        auto l = *this->lower_bound(x);\n        return\
    \ l.a * x + l.b;\n    }\n};\n"
  code: "#pragma once\n\n// only works for integer coordinates!! maintain max\ntemplate<typename\
    \ T>\nstruct Line {\n    mutable T a, b, p;\n    bool operator<(const Line &rhs)\
    \ const { return a < rhs.a; }\n    bool operator<(T x) const { return p < x; }\n\
    };\ntemplate<typename T, T kInf = 1'000'000'000'000'000'000LL>\nstruct DynamicHull\
    \ : multiset<Line<T>, less<>> {\n    using iterator = multiset<Line<T>, less<>>::iterator;\
    \ \n    T Div(T a, T b) { return a / b - ((a ^ b) < 0 && a % b); }\n    bool isect(iterator\
    \ x, iterator y) {\n        if (y == this->end()) { x->p = kInf; return 0; }\n\
    \        if (x->a == y->a) x->p = x->b > y->b ? kInf : -kInf;\n        else x->p\
    \ = Div(y->b - x->b, x->a - y->a);\n        return x->p >= y->p;\n    }\n    void\
    \ addline(T a, T b) {\n        auto z = this->emplace(a, b, 0), y = z++, x = y;\n\
    \        while (isect(y, z)) z = this->erase(z);\n        if (x != this->begin()\
    \ && isect(--x, y)) isect(x, y = this->erase(y));\n        while ((y = x) != this->begin()\
    \ && (--x)->p >= y->p) isect(x, this->erase(y));\n    }\n    T query(T x) {\n\
    \        auto l = *this->lower_bound(x);\n        return l.a * x + l.b;\n    }\n\
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: Misc/DynamicHull.hpp
  requiredBy: []
  timestamp: '2026-05-04 13:57:29+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/line_add_get_min.test.cpp
documentation_of: Misc/DynamicHull.hpp
layout: document
redirect_from:
- /library/Misc/DynamicHull.hpp
- /library/Misc/DynamicHull.hpp.html
title: Misc/DynamicHull.hpp
---
