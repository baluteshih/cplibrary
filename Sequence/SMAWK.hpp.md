---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
    title: test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://github.com/abc864197532/std_abs/blob/main/codebook/Else/Smawk.cpp
  bundledCode: "#line 2 \"Sequence/SMAWK.hpp\"\n\n// source: https://github.com/abc864197532/std_abs/blob/main/codebook/Else/Smawk.cpp\n\
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
    \ col.end(), 0);\n    return solve(solve, row, col);\n}\n\n"
  code: "#pragma once\n\n// source: https://github.com/abc864197532/std_abs/blob/main/codebook/Else/Smawk.cpp\n\
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
    \ col.end(), 0);\n    return solve(solve, row, col);\n}\n\n"
  dependsOn: []
  isVerificationFile: false
  path: Sequence/SMAWK.hpp
  requiredBy: []
  timestamp: '2026-05-06 18:14:23+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/convolution/min_plus_convolution_convex_convex.test.cpp
documentation_of: Sequence/SMAWK.hpp
layout: document
redirect_from:
- /library/Sequence/SMAWK.hpp
- /library/Sequence/SMAWK.hpp.html
title: Sequence/SMAWK.hpp
---
