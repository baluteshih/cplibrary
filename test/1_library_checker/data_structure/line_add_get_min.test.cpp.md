---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Misc/DynamicHull.hpp
    title: Misc/DynamicHull.hpp
  - icon: ':heavy_check_mark:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/line_add_get_min
    links:
    - https://judge.yosupo.jp/problem/line_add_get_min
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/line_add_get_min.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n#line\
    \ 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/data_structure/line_add_get_min.test.cpp\"\n\n#line\
    \ 2 \"Misc/DynamicHull.hpp\"\n\n// only works for integer coordinates!! maintain\
    \ max\ntemplate<typename T>\nstruct Line {\n    mutable T a, b, p;\n    bool operator<(const\
    \ Line &rhs) const { return a < rhs.a; }\n    bool operator<(T x) const { return\
    \ p < x; }\n};\ntemplate<typename T, T kInf = 1'000'000'000'000'000'000LL>\nstruct\
    \ DynamicHull : std::multiset<Line<T>, std::less<>> {\n    using iterator = std::multiset<Line<T>,\
    \ std::less<>>::iterator; \n    T Div(T a, T b) { return a / b - ((a ^ b) < 0\
    \ && a % b); }\n    bool isect(iterator x, iterator y) {\n        if (y == this->end())\
    \ { x->p = kInf; return 0; }\n        if (x->a == y->a) x->p = x->b > y->b ? kInf\
    \ : -kInf;\n        else x->p = Div(y->b - x->b, x->a - y->a);\n        return\
    \ x->p >= y->p;\n    }\n    void addline(T a, T b) {\n        auto z = this->emplace(a,\
    \ b, 0), y = z++, x = y;\n        while (isect(y, z)) z = this->erase(z);\n  \
    \      if (x != this->begin() && isect(--x, y)) isect(x, y = this->erase(y));\n\
    \        while ((y = x) != this->begin() && (--x)->p >= y->p) isect(x, this->erase(y));\n\
    \    }\n    T query(T x) {\n        auto l = *this->lower_bound(x);\n        return\
    \ l.a * x + l.b;\n    }\n};\n#line 5 \"test/1_library_checker/data_structure/line_add_get_min.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    DynamicHull<long long> hull;\n    for (int\
    \ i = 0; i < n; ++i) {\n        long long a, b;\n        std::cin >> a >> b;\n\
    \        hull.addline(-a, -b);\n    }\n    while (q--) {\n        int type;\n\
    \        std::cin >> type;\n        if (type == 0) {\n            long long a,\
    \ b;\n            std::cin >> a >> b;\n            hull.addline(-a, -b);\n   \
    \     }\n        else {\n            long long p;\n            std::cin >> p;\n\
    \            std::cout << -hull.query(p) << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n#include\
    \ \"assumption.hpp\"\n\n#include \"Misc/DynamicHull.hpp\"\n\nint main() {\n  \
    \  std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    DynamicHull<long long> hull;\n    for (int i = 0; i < n; ++i)\
    \ {\n        long long a, b;\n        std::cin >> a >> b;\n        hull.addline(-a,\
    \ -b);\n    }\n    while (q--) {\n        int type;\n        std::cin >> type;\n\
    \        if (type == 0) {\n            long long a, b;\n            std::cin >>\
    \ a >> b;\n            hull.addline(-a, -b);\n        }\n        else {\n    \
    \        long long p;\n            std::cin >> p;\n            std::cout << -hull.query(p)\
    \ << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Misc/DynamicHull.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/line_add_get_min.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 20:51:50+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/line_add_get_min.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/line_add_get_min.test.cpp
- /verify/test/1_library_checker/data_structure/line_add_get_min.test.cpp.html
title: test/1_library_checker/data_structure/line_add_get_min.test.cpp
---
