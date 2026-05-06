---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp
    title: test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Convolution/min_plus_convolution_concave.hpp\"\n\n// a is\
    \ concave, i.e. a[i + 1] - a[i] >= a[i + 2] - a[i + 1]\ntemplate<typename T>\n\
    vector<T> min_plus_convolution_concave(vector<T> &a, vector<T> &b) {\n    static\
    \ constexpr T inf = std::numeric_limits<T>::max();\n    int n = a.size(), m =\
    \ b.size();\n    vector<T> c(n + m - 1, inf);\n    auto cal_min = [&](int k, int\
    \ l, int r) -> std::pair<int, T> {\n        r = std::min({r, k + 1, m});\n   \
    \     l = std::max({l, k - (n - 1), 0});\n        std::pair<int, T> mn{l, inf};\n\
    \        for (int i = l; i < r; i++) {\n            if (k - i < 0 || k - i >=\
    \ n) continue;\n            if (a[k - i] + b[i] < mn.second)\n               \
    \ mn = {i, a[k - i] + b[i]};\n        }\n        return mn;\n    };\n    auto\
    \ dc = [&](auto self, int l, int r, int jl, int jr) -> void {\n        l = std::max(l,\
    \ jl);\n        r = std::min(r, jr + n - 1);\n        if (l >= r || jl >= jr)\
    \ return;\n        int mc = (l + r) / 2;\n        auto [mb, x] = cal_min(mc, jl,\
    \ jr);\n        if (x == inf) return;\n        c[mc] = std::min(c[mc], x);\n \
    \       \n        self(self, l, mc, jl, std::min(mb + 1, mc - (n - 1)));\n   \
    \     self(self, l, std::min(mb, mc), std::max(jl, mc - n), mb);\n        self(self,\
    \ std::max(mb, l), mc, mb, jr);\n\n        self(self, mc + 1, std::min(r, mb +\
    \ n), std::max(jl, mc - (n - 1)), mb + 1);\n        self(self, std::max(mc + 1,\
    \ mb + n - 1), r, mb, std::min(jr, mc));\n        self(self, mc + 1, r, std::max(mc,\
    \ jl), jr);\n    };\n    return dc(dc, 0, n + m - 1, 0, m), c;\n}\n"
  code: "#pragma once\n\n// a is concave, i.e. a[i + 1] - a[i] >= a[i + 2] - a[i +\
    \ 1]\ntemplate<typename T>\nvector<T> min_plus_convolution_concave(vector<T> &a,\
    \ vector<T> &b) {\n    static constexpr T inf = std::numeric_limits<T>::max();\n\
    \    int n = a.size(), m = b.size();\n    vector<T> c(n + m - 1, inf);\n    auto\
    \ cal_min = [&](int k, int l, int r) -> std::pair<int, T> {\n        r = std::min({r,\
    \ k + 1, m});\n        l = std::max({l, k - (n - 1), 0});\n        std::pair<int,\
    \ T> mn{l, inf};\n        for (int i = l; i < r; i++) {\n            if (k - i\
    \ < 0 || k - i >= n) continue;\n            if (a[k - i] + b[i] < mn.second)\n\
    \                mn = {i, a[k - i] + b[i]};\n        }\n        return mn;\n \
    \   };\n    auto dc = [&](auto self, int l, int r, int jl, int jr) -> void {\n\
    \        l = std::max(l, jl);\n        r = std::min(r, jr + n - 1);\n        if\
    \ (l >= r || jl >= jr) return;\n        int mc = (l + r) / 2;\n        auto [mb,\
    \ x] = cal_min(mc, jl, jr);\n        if (x == inf) return;\n        c[mc] = std::min(c[mc],\
    \ x);\n        \n        self(self, l, mc, jl, std::min(mb + 1, mc - (n - 1)));\n\
    \        self(self, l, std::min(mb, mc), std::max(jl, mc - n), mb);\n        self(self,\
    \ std::max(mb, l), mc, mb, jr);\n\n        self(self, mc + 1, std::min(r, mb +\
    \ n), std::max(jl, mc - (n - 1)), mb + 1);\n        self(self, std::max(mc + 1,\
    \ mb + n - 1), r, mb, std::min(jr, mc));\n        self(self, mc + 1, r, std::max(mc,\
    \ jl), jr);\n    };\n    return dc(dc, 0, n + m - 1, 0, m), c;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Convolution/min_plus_convolution_concave.hpp
  requiredBy: []
  timestamp: '2026-05-06 17:59:51+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp
documentation_of: Convolution/min_plus_convolution_concave.hpp
layout: document
redirect_from:
- /library/Convolution/min_plus_convolution_concave.hpp
- /library/Convolution/min_plus_convolution_concave.hpp.html
title: Convolution/min_plus_convolution_concave.hpp
---
