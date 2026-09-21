---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Convolution/min_plus_convolution.hpp
    title: Convolution/min_plus_convolution.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
    links:
    - https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
  bundledCode: "#line 1 \"test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp\"\
    \n\n#line 2 \"Convolution/min_plus_convolution.hpp\"\n\n// a is convex, i.e. a[i\
    \ + 1] - a[i] <= a[i + 2] - a[i + 1]\ntemplate<typename T>\nstd::vector<T> min_plus_convolution(std::vector<T>\
    \ &a, std::vector<T> &b) {\n    int n = a.size(), m = b.size();\n    std::vector<T>\
    \ c(n + m - 1, std::numeric_limits<T>::max());\n    auto dc = [&](auto self, int\
    \ l, int r, int jl, int jr) -> void {\n        if (l > r) return;\n        int\
    \ mid = (l + r) / 2, from = -1;\n        T &best = c[mid];\n        for (int j\
    \ = jl; j <= jr; ++j)\n            if (int i = mid - j; i >= 0 && i < n)\n   \
    \             if (best > a[i] + b[j]) \n                    best = a[i] + b[j],\
    \ from = j;\n        self(self, l, mid - 1, jl, from), self(self, mid + 1, r,\
    \ from, jr);\n    };\n    return dc(dc, 0, n - 1 + m - 1, 0, m - 1), c;\n}\n#line\
    \ 5 \"test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, m;\n    std::cin >> n >> m;\n    std::vector<int> a(n), b(m);\n    for (int\
    \ &i : a)\n        std::cin >> i;\n    for (int &i : b)\n        std::cin >> i;\n\
    \    auto c = min_plus_convolution(a, b);\n    for (int i = 0; i < int(c.size());\
    \ ++i)\n        std::cout << c[i] << \" \\n\"[i + 1 == int(c.size())];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary\"\
    \n#include \"assumption.hpp\"\n\n#include \"Convolution/min_plus_convolution.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, m;\n    std::cin >> n >> m;\n    std::vector<int> a(n), b(m);\n    for (int\
    \ &i : a)\n        std::cin >> i;\n    for (int &i : b)\n        std::cin >> i;\n\
    \    auto c = min_plus_convolution(a, b);\n    for (int i = 0; i < int(c.size());\
    \ ++i)\n        std::cout << c[i] << \" \\n\"[i + 1 == int(c.size())];\n}\n"
  dependsOn:
  - assumption.hpp
  - Convolution/min_plus_convolution.hpp
  isVerificationFile: true
  path: test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 20:51:50+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
- /verify/test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp.html
title: test/1_library_checker/convolution/min_plus_convolution_convex_arbitrary.test.cpp
---
