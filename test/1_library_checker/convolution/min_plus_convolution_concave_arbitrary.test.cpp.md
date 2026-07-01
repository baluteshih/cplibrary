---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Convolution/min_plus_convolution_concave.hpp
    title: Convolution/min_plus_convolution_concave.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary
    links:
    - https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary
  bundledCode: "#line 1 \"test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp\"\
    \n\n#line 2 \"Convolution/min_plus_convolution_concave.hpp\"\n\n// a is concave,\
    \ i.e. a[i + 1] - a[i] >= a[i + 2] - a[i + 1]\ntemplate<typename T>\nstd::vector<T>\
    \ min_plus_convolution_concave(std::vector<T> &a, std::vector<T> &b) {\n    static\
    \ constexpr T inf = std::numeric_limits<T>::max();\n    int n = a.size(), m =\
    \ b.size();\n    std::vector<T> c(n + m - 1, inf);\n    auto cal_min = [&](int\
    \ k, int l, int r) -> std::pair<int, T> {\n        r = std::min({r, k + 1, m});\n\
    \        l = std::max({l, k - (n - 1), 0});\n        std::pair<int, T> mn{l, inf};\n\
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
    \ jl), jr);\n    };\n    return dc(dc, 0, n + m - 1, 0, m), c;\n}\n#line 5 \"\
    test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, m;\n    std::cin >> n >> m;\n    std::vector<int> a(n), b(m);\n    for (int\
    \ &i : a)\n        std::cin >> i;\n    for (int &i : b)\n        std::cin >> i;\n\
    \    auto c = min_plus_convolution_concave(a, b);\n    for (int i = 0; i < int(c.size());\
    \ ++i)\n        std::cout << c[i] << \" \\n\"[i + 1 == int(c.size())];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary\"\
    \n#include \"assumption.hpp\"\n\n#include \"Convolution/min_plus_convolution_concave.hpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, m;\n    std::cin >> n >> m;\n    std::vector<int> a(n), b(m);\n    for (int\
    \ &i : a)\n        std::cin >> i;\n    for (int &i : b)\n        std::cin >> i;\n\
    \    auto c = min_plus_convolution_concave(a, b);\n    for (int i = 0; i < int(c.size());\
    \ ++i)\n        std::cout << c[i] << \" \\n\"[i + 1 == int(c.size())];\n}\n"
  dependsOn:
  - assumption.hpp
  - Convolution/min_plus_convolution_concave.hpp
  isVerificationFile: true
  path: test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 14:01:32+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp
- /verify/test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp.html
title: test/1_library_checker/convolution/min_plus_convolution_concave_arbitrary.test.cpp
---
