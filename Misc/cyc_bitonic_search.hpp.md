---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: Geometry/convex.hpp
    title: Geometry/convex.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/furthest_pair.hpp
    title: Geometry/furthest_pair.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/outerTangentBetweenConvex.hpp
    title: Geometry/outerTangentBetweenConvex.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/0_custom/outerTangentBetweenConvex.test.cpp
    title: test/0_custom/outerTangentBetweenConvex.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/geometry/furthest_pair.test.cpp
    title: test/1_library_checker/geometry/furthest_pair.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/geometry/static_convex_hull.test.cpp
    title: test/1_library_checker/geometry/static_convex_hull.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/2_aoj/convex_cut.test.cpp
    title: test/2_aoj/convex_cut.test.cpp
  - icon: ':x:'
    path: test/3_qoj/2162.test.cpp
    title: test/3_qoj/2162.test.cpp
  - icon: ':x:'
    path: test/4_codeforces/101242J.test.cpp
    title: test/4_codeforces/101242J.test.cpp
  - icon: ':x:'
    path: test/4_codeforces/104114B.test.cpp
    title: test/4_codeforces/104114B.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Misc/cyc_bitonic_search.hpp\"\n\n/* \n   bool pred(int a,\
    \ int b);\n   a is better than b\n   f(0) ~ f(n - 1) is a cyclic-shift bitonic-function\n\
    \   return idx s.t. pred(x, idx) is false forall x\n*/\nint cyc_bitonic_search(int\
    \ n, auto pred) {\n    if (n == 1) return 0;\n    int l = 0, r = n; bool rv =\
    \ pred(1, 0);\n    while (r - l > 1) {\n        int m = (l + r) / 2;\n       \
    \ if (pred(0, m) ? rv: pred(m, (m + 1) % n)) r = m;\n        else l = m;\n   \
    \ }\n    return pred(l, r % n) ? l : r % n;\n}\n\n/* \n   bool pred(int o, int\
    \ a, int b);\n   a is better than b\n   f(o, 0) ~ f(o, n - 1) is a cyclic-shift\
    \ bitonic-function\n   return idx[o] s.t. pred(o, x, idx[o]) is false forall x\n\
    \   idx should be non-decreasing, and idx[o] != o\n*/\nstd::vector<int> rotating_calipers(int\
    \ n, auto pred) {\n    assert(n >= 2);\n    std::vector<int> res(n, 1);\n    for\
    \ (int i = 2; i < n; ++i)\n        if (pred(0, i, res[0]))\n            res[0]\
    \ = i;\n    for (int i = 1; i < n; ++i) {\n        res[i] = res[i - 1];\n    \
    \    while ((res[i] + 1) % n != i && pred(i, (res[i] + 1) % n, res[i] % n))\n\
    \            ++res[i];\n        res[i] %= n;\n    }\n    return res;\n}\n"
  code: "#pragma once\n\n/* \n   bool pred(int a, int b);\n   a is better than b\n\
    \   f(0) ~ f(n - 1) is a cyclic-shift bitonic-function\n   return idx s.t. pred(x,\
    \ idx) is false forall x\n*/\nint cyc_bitonic_search(int n, auto pred) {\n   \
    \ if (n == 1) return 0;\n    int l = 0, r = n; bool rv = pred(1, 0);\n    while\
    \ (r - l > 1) {\n        int m = (l + r) / 2;\n        if (pred(0, m) ? rv: pred(m,\
    \ (m + 1) % n)) r = m;\n        else l = m;\n    }\n    return pred(l, r % n)\
    \ ? l : r % n;\n}\n\n/* \n   bool pred(int o, int a, int b);\n   a is better than\
    \ b\n   f(o, 0) ~ f(o, n - 1) is a cyclic-shift bitonic-function\n   return idx[o]\
    \ s.t. pred(o, x, idx[o]) is false forall x\n   idx should be non-decreasing,\
    \ and idx[o] != o\n*/\nstd::vector<int> rotating_calipers(int n, auto pred) {\n\
    \    assert(n >= 2);\n    std::vector<int> res(n, 1);\n    for (int i = 2; i <\
    \ n; ++i)\n        if (pred(0, i, res[0]))\n            res[0] = i;\n    for (int\
    \ i = 1; i < n; ++i) {\n        res[i] = res[i - 1];\n        while ((res[i] +\
    \ 1) % n != i && pred(i, (res[i] + 1) % n, res[i] % n))\n            ++res[i];\n\
    \        res[i] %= n;\n    }\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Misc/cyc_bitonic_search.hpp
  requiredBy:
  - Geometry/outerTangentBetweenConvex.hpp
  - Geometry/convex.hpp
  - Geometry/furthest_pair.hpp
  timestamp: '2026-04-07 01:16:28+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/0_custom/outerTangentBetweenConvex.test.cpp
  - test/4_codeforces/101242J.test.cpp
  - test/4_codeforces/104114B.test.cpp
  - test/3_qoj/2162.test.cpp
  - test/2_aoj/convex_cut.test.cpp
  - test/1_library_checker/geometry/static_convex_hull.test.cpp
  - test/1_library_checker/geometry/furthest_pair.test.cpp
documentation_of: Misc/cyc_bitonic_search.hpp
layout: document
redirect_from:
- /library/Misc/cyc_bitonic_search.hpp
- /library/Misc/cyc_bitonic_search.hpp.html
title: Misc/cyc_bitonic_search.hpp
---
