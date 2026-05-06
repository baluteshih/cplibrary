---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Convolution/min_plus_convolution.hpp
    title: Convolution/min_plus_convolution.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
    links:
    - https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
  bundledCode: "#line 1 \"test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary\"\
    \n#line 2 \"default_code.hpp\"\n\n#include <bits/stdc++.h>\nusing namespace std;\n\
    typedef long long ll;\ntypedef pair<int, int> pii;\ntypedef pair<ll, ll> pll;\n\
    #define X first\n#define Y second\n#define SZ(a) ((int)a.size())\n#define ALL(v)\
    \ v.begin(), v.end()\ntemplate<class A, class B>\nostream& operator<<(ostream&\
    \ os, const pair<A, B> &a) {\n    os << \"(\" << a.first << \", \" << a.second\
    \ << \")\";\n    return os;\n}\ntemplate <typename T>\nconcept PrintableContainer\
    \ = requires(T& a) {\n    a.begin();\n    a.end();\n} && !std::same_as<std::remove_cvref_t<T>,\
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
    }\n#line 3 \"test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp\"\
    \n\n#line 2 \"Convolution/min_plus_convolution.hpp\"\n\n// a is convex, i.e. a[i\
    \ + 1] - a[i] <= a[i + 2] - a[i + 1]\ntemplate<typename T>\nvector<T> min_plus_convolution(vector<T>\
    \ &a, vector<T> &b) {\n    int n = a.size(), m = b.size();\n    vector<T> c(n\
    \ + m - 1, std::numeric_limits<T>::max());\n    auto dc = [&](auto Y, int l, int\
    \ r, int jl, int jr) {\n        if (l > r) return;\n        int mid = (l + r)\
    \ / 2, from = -1;\n        T &best = c[mid];\n        for (int j = jl; j <= jr;\
    \ ++j)\n            if (int i = mid - j; i >= 0 && i < n)\n                if\
    \ (best > a[i] + b[j]) \n                    best = a[i] + b[j], from = j;\n \
    \       Y(Y, l, mid - 1, jl, from), Y(Y, mid + 1, r, from, jr);\n    };\n    return\
    \ dc(dc, 0, n - 1 + m - 1, 0, m - 1), c;\n}\n#line 5 \"test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, m;\n  \
    \  cin >> n >> m;\n    vector<int> a(n), b(m);\n    for (int &i : a)\n       \
    \ cin >> i;\n    for (int &i : b)\n        cin >> i;\n    auto c = min_plus_convolution(a,\
    \ b);\n    for (int i = 0; i < SZ(c); ++i)\n        cout << c[i] << \" \\n\"[i\
    \ + 1 == SZ(c)];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary\"\
    \n#include \"default_code.hpp\"\n\n#include \"Convolution/min_plus_convolution.hpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, m;\n  \
    \  cin >> n >> m;\n    vector<int> a(n), b(m);\n    for (int &i : a)\n       \
    \ cin >> i;\n    for (int &i : b)\n        cin >> i;\n    auto c = min_plus_convolution(a,\
    \ b);\n    for (int i = 0; i < SZ(c); ++i)\n        cout << c[i] << \" \\n\"[i\
    \ + 1 == SZ(c)];\n}\n"
  dependsOn:
  - default_code.hpp
  - Convolution/min_plus_convolution.hpp
  isVerificationFile: true
  path: test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
  requiredBy: []
  timestamp: '2026-02-27 19:30:58+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
- /verify/test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp.html
title: test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
---
