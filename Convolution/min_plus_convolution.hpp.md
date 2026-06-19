---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
    title: test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Convolution/min_plus_convolution.hpp\"\n\n// a is convex,\
    \ i.e. a[i + 1] - a[i] <= a[i + 2] - a[i + 1]\ntemplate<typename T>\nstd::vector<T>\
    \ min_plus_convolution(std::vector<T> &a, std::vector<T> &b) {\n    int n = a.size(),\
    \ m = b.size();\n    std::vector<T> c(n + m - 1, std::numeric_limits<T>::max());\n\
    \    auto dc = [&](auto self, int l, int r, int jl, int jr) -> void {\n      \
    \  if (l > r) return;\n        int mid = (l + r) / 2, from = -1;\n        T &best\
    \ = c[mid];\n        for (int j = jl; j <= jr; ++j)\n            if (int i = mid\
    \ - j; i >= 0 && i < n)\n                if (best > a[i] + b[j]) \n          \
    \          best = a[i] + b[j], from = j;\n        self(self, l, mid - 1, jl, from),\
    \ self(self, mid + 1, r, from, jr);\n    };\n    return dc(dc, 0, n - 1 + m -\
    \ 1, 0, m - 1), c;\n}\n"
  code: "#pragma once\n\n// a is convex, i.e. a[i + 1] - a[i] <= a[i + 2] - a[i +\
    \ 1]\ntemplate<typename T>\nstd::vector<T> min_plus_convolution(std::vector<T>\
    \ &a, std::vector<T> &b) {\n    int n = a.size(), m = b.size();\n    std::vector<T>\
    \ c(n + m - 1, std::numeric_limits<T>::max());\n    auto dc = [&](auto self, int\
    \ l, int r, int jl, int jr) -> void {\n        if (l > r) return;\n        int\
    \ mid = (l + r) / 2, from = -1;\n        T &best = c[mid];\n        for (int j\
    \ = jl; j <= jr; ++j)\n            if (int i = mid - j; i >= 0 && i < n)\n   \
    \             if (best > a[i] + b[j]) \n                    best = a[i] + b[j],\
    \ from = j;\n        self(self, l, mid - 1, jl, from), self(self, mid + 1, r,\
    \ from, jr);\n    };\n    return dc(dc, 0, n - 1 + m - 1, 0, m - 1), c;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Convolution/min_plus_convolution.hpp
  requiredBy: []
  timestamp: '2026-06-19 20:51:50+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
documentation_of: Convolution/min_plus_convolution.hpp
layout: document
redirect_from:
- /library/Convolution/min_plus_convolution.hpp
- /library/Convolution/min_plus_convolution.hpp.html
title: Convolution/min_plus_convolution.hpp
---
