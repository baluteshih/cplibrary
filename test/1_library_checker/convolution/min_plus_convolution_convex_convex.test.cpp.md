---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Sequence/SMAWK.hpp
    title: Sequence/SMAWK.hpp
  - icon: ':question:'
    path: assumption.hpp
    title: assumption.hpp
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
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp\"\
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
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, m;\n    std::cin >> n >> m;\n    std::vector<int> a(n), b(m);\n    for (int\
    \ &i : a)\n        std::cin >> i;\n    for (int &i : b)\n        std::cin >> i;\n\
    \    auto f = [&](int i, int j) {\n        if (0 <= i - j && i - j < n)\n    \
    \        return b[j] + a[i - j];\n        return 2100000000 + (i - j); \n    };\n\
    \    auto c = SMAWK(n + m - 1, m, f);\n    for (int i = 0; i < int(c.size());\
    \ ++i)\n        std::cout << f(i, c[i]) << \" \\n\"[i + 1 == int(c.size())];\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_convex\"\
    \n#include \"assumption.hpp\"\n\n#include \"Sequence/SMAWK.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, m;\n    std::cin\
    \ >> n >> m;\n    std::vector<int> a(n), b(m);\n    for (int &i : a)\n       \
    \ std::cin >> i;\n    for (int &i : b)\n        std::cin >> i;\n    auto f = [&](int\
    \ i, int j) {\n        if (0 <= i - j && i - j < n)\n            return b[j] +\
    \ a[i - j];\n        return 2100000000 + (i - j); \n    };\n    auto c = SMAWK(n\
    \ + m - 1, m, f);\n    for (int i = 0; i < int(c.size()); ++i)\n        std::cout\
    \ << f(i, c[i]) << \" \\n\"[i + 1 == int(c.size())];\n}\n"
  dependsOn:
  - assumption.hpp
  - Sequence/SMAWK.hpp
  isVerificationFile: true
  path: test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 14:01:32+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
- /verify/test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp.html
title: test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
---
