---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Sequence/SMAWK.hpp
    title: Sequence/SMAWK.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex
    links:
    - https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex
  bundledCode: "#line 1 \"test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex\"\
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
    }\n#line 3 \"test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp\"\
    \n\n#line 2 \"Sequence/SMAWK.hpp\"\n\n// source: https://github.com/abc864197532/std_abs/blob/main/codebook/Else/Smawk.cpp\n\
    \n// For all 2x2 submatrix of f(i, j):\n// If M[1][0] < M[1][1], M[0][0] < M[0][1]\n\
    // If M[1][0] == M[1][1], M[0][0] <= M[0][1]\n// M[i][ans_i] is the best value\
    \ in the i-th row\nstd::vector<int> SMAWK(int _n, int _m, auto &&f) {\n    auto\
    \ select = [&](int r, int u, int v) {\n        // if f(r, v) is better than f(r,\
    \ u), return true\n        return f(r, u) > f(r, v);\n    };\n    auto solve =\
    \ [&](auto self, std::vector<int> &r, std::vector<int> &c) -> std::vector<int>\
    \ {\n        const int n = r.size();\n        if (n == 0) return {};\n       \
    \ std::vector <int> c2;\n        for (const int &i : c) {\n            while (!c2.empty()\
    \ && select(r[c2.size() - 1], c2.back(), i)) c2.pop_back();\n            if (int(c2.size())\
    \ < n) c2.push_back(i);\n        }\n        std::vector <int> r2;\n        for\
    \ (int i = 1; i < n; i += 2) r2.push_back(r[i]);\n        const auto a2 = self(self,\
    \ r2, c2);\n        std::vector <int> ans(n);\n        for (int i = 0; i < int(a2.size());\
    \ ++i)\n            ans[i * 2 + 1] = a2[i];\n        int j = 0;\n        for (int\
    \ i = 0; i < n; i += 2) {\n            ans[i] = c2[j];\n            const int\
    \ end = i + 1 == n ? c2.back() : ans[i + 1];\n            while (c2[j] != end)\
    \ {\n                j++;\n                if (select(r[i], ans[i], c2[j])) ans[i]\
    \ = c2[j];\n            }\n        }\n        return ans;\n    };\n    std::vector<int>\
    \ row(_n), col(_m);\n    std::iota(row.begin(), row.end(), 0), std::iota(col.begin(),\
    \ col.end(), 0);\n    return solve(solve, row, col);\n}\n\n#line 5 \"test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp\"\
    \n\nint main() {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, m;\n  \
    \  cin >> n >> m;\n    vector<int> a(n), b(m);\n    for (int &i : a)\n       \
    \ cin >> i;\n    for (int &i : b)\n        cin >> i;\n    auto f = [&](int i,\
    \ int j) {\n        if (0 <= i - j && i - j < n)\n            return b[j] + a[i\
    \ - j];\n        return 2100000000 + (i - j); \n    };\n    auto c = SMAWK(n +\
    \ m - 1, m, f);\n    for (int i = 0; i < SZ(c); ++i)\n        cout << f(i, c[i])\
    \ << \" \\n\"[i + 1 == SZ(c)];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex\"\
    \n#include \"default_code.hpp\"\n\n#include \"Sequence/SMAWK.hpp\"\n\nint main()\
    \ {\n    ios::sync_with_stdio(0), cin.tie(0);\n    int n, m;\n    cin >> n >>\
    \ m;\n    vector<int> a(n), b(m);\n    for (int &i : a)\n        cin >> i;\n \
    \   for (int &i : b)\n        cin >> i;\n    auto f = [&](int i, int j) {\n  \
    \      if (0 <= i - j && i - j < n)\n            return b[j] + a[i - j];\n   \
    \     return 2100000000 + (i - j); \n    };\n    auto c = SMAWK(n + m - 1, m,\
    \ f);\n    for (int i = 0; i < SZ(c); ++i)\n        cout << f(i, c[i]) << \" \\\
    n\"[i + 1 == SZ(c)];\n}\n"
  dependsOn:
  - default_code.hpp
  - Sequence/SMAWK.hpp
  isVerificationFile: true
  path: test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
  requiredBy: []
  timestamp: '2026-05-06 18:14:23+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
- /verify/test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp.html
title: test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
---
