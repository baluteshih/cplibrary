---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Misc/DynamicHull.hpp
    title: Misc/DynamicHull.hpp
  - icon: ':question:'
    path: default_code.hpp
    title: default_code.hpp
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
    \ 2 \"default_code.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace std;\ntypedef\
    \ long long ll;\ntypedef pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n#define\
    \ X first\n#define Y second\n#define SZ(a) ((int)a.size())\n#define ALL(v) v.begin(),\
    \ v.end()\ntemplate<class A, class B>\nostream& operator<<(ostream& os, const\
    \ pair<A, B> &a) {\n    os << \"(\" << a.first << \", \" << a.second << \")\"\
    ;\n    return os;\n}\ntemplate <typename T>\nconcept PrintableContainer = requires(T&\
    \ a) {\n    a.begin();\n    a.end();\n} && !std::same_as<std::remove_cvref_t<T>,\
    \ std::string> &&\n     !std::same_as<std::remove_cvref_t<T>, std::string_view>\
    \ &&\n     !std::is_convertible_v<T, const char*>;\ntemplate <PrintableContainer\
    \ T>\nstd::ostream& operator<<(std::ostream& os, const T& a) {\n    os << \"[\
    \ \";\n    bool first = true;\n    for (const auto& item : a) {\n        if (!first)\
    \ os << \", \";\n        os << item;\n        first = false;\n    }\n    return\
    \ os << \" ]\";\n}\n#ifdef bbq\n#include <experimental/iterator>\n#define safe\
    \ cerr<<__PRETTY_FUNCTION__<<\" line \"<<__LINE__<<\" safe\\n\"\n#define sepline\
    \ sepline_() \n#define debug(a...) debug_(#a, a)\n#define orange(a...) orange_(#a,\
    \ a)\nvoid debug_(auto s, auto ...a) {\n    cerr << \"\\e[1;32m(\" << s << \"\
    ) = (\";\n    int f = 0;\n    (..., (cerr << (f++ ? \", \" : \"\") << a));\n \
    \   cerr << \")\\e[0m\\n\";\n}\nvoid orange_(auto s, auto L, auto R) {\n    cerr\
    \ << \"\\e[1;33m[ \" << s << \" ] = [ \";\n    using namespace experimental;\n\
    \    copy(L, R, make_ostream_joiner(cerr, \", \"));\n    cerr << \" ]\\e[0m\\\
    n\";\n}\nvoid sepline_(int length = 50) {\n    cerr << \"\\e[1;35m\";\n    cerr\
    \ << string(length, '=');\n    cerr << \"\\e[0m\\n\";\n}\n#else\n#define safe\
    \ ((void)0)\n#define sepline safe\n#define debug(...) safe\n#define orange(...)\
    \ safe\n#endif\n\nvoid chmax(auto &x, auto val) {\n    x = max(x, val);\n}\n\n\
    void chmin(auto &x, auto val) {\n    x = min(x, val);\n}\n\nvector<int> count_array(const\
    \ auto &container, int sz = -1) {\n    if (sz == -1) sz = *ranges::max_element(container)\
    \ + 1;\n    vector<int> res(sz);\n    for (auto x : container) ++res[x];\n   \
    \ return res;\n}\n\ntemplate<class T>\nvoid discretization(vector<T> &vals) {\n\
    \    ranges::sort(vals);\n    vals.erase(ranges::unique(vals).begin(), vals.end());\n\
    }\n#line 3 \"test/1_library_checker/data_structure/line_add_get_min.test.cpp\"\
    \n\n#line 2 \"Misc/DynamicHull.hpp\"\n\n// only works for integer coordinates!!\
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
    \ l.a * x + l.b;\n    }\n};\n#line 5 \"test/1_library_checker/data_structure/line_add_get_min.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n  \
    \  cin >> n >> q;\n    DynamicHull<ll> hull;\n    for (int i = 0; i < n; ++i)\
    \ {\n        ll a, b;\n        cin >> a >> b;\n        hull.addline(-a, -b);\n\
    \    }\n    while (q--) {\n        int type;\n        cin >> type;\n        if\
    \ (type == 0) {\n            ll a, b;\n            cin >> a >> b;\n          \
    \  hull.addline(-a, -b);\n        }\n        else {\n            ll p;\n     \
    \       cin >> p;\n            cout << -hull.query(p) << \"\\n\";\n        }\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/line_add_get_min\"\n#include\
    \ \"default_code.hpp\"\n\n#include \"Misc/DynamicHull.hpp\"\n\nint main() {\n\
    \    ios::sync_with_stdio(0), cin.tie(0);\n    int n, q;\n    cin >> n >> q;\n\
    \    DynamicHull<ll> hull;\n    for (int i = 0; i < n; ++i) {\n        ll a, b;\n\
    \        cin >> a >> b;\n        hull.addline(-a, -b);\n    }\n    while (q--)\
    \ {\n        int type;\n        cin >> type;\n        if (type == 0) {\n     \
    \       ll a, b;\n            cin >> a >> b;\n            hull.addline(-a, -b);\n\
    \        }\n        else {\n            ll p;\n            cin >> p;\n       \
    \     cout << -hull.query(p) << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - default_code.hpp
  - Misc/DynamicHull.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/line_add_get_min.test.cpp
  requiredBy: []
  timestamp: '2026-05-04 13:57:29+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/line_add_get_min.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/line_add_get_min.test.cpp
- /verify/test/1_library_checker/data_structure/line_add_get_min.test.cpp.html
title: test/1_library_checker/data_structure/line_add_get_min.test.cpp
---
