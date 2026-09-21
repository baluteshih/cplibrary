---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/number_theory/enumerate_quotients.test.cpp
    title: test/1_library_checker/number_theory/enumerate_quotients.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/floor_enumerate.hpp\"\n\n/* \ncall (x, l, r) such\
    \ that i in [l, r) having x = floor(n / i)\nx is enumerated from large to small\n\
    */\ntemplate<typename T, typename F>\nvoid floor_enumerate(T n, F func) {\n  \
    \  for (T l = 1, r; l <= n; l = r + 1) {\n        T x = n / l;\n        r = n\
    \ / x;\n        func(x, l, r + 1);\n    }\n}\n"
  code: "#pragma once\n\n/* \ncall (x, l, r) such that i in [l, r) having x = floor(n\
    \ / i)\nx is enumerated from large to small\n*/\ntemplate<typename T, typename\
    \ F>\nvoid floor_enumerate(T n, F func) {\n    for (T l = 1, r; l <= n; l = r\
    \ + 1) {\n        T x = n / l;\n        r = n / x;\n        func(x, l, r + 1);\n\
    \    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/floor_enumerate.hpp
  requiredBy: []
  timestamp: '2026-06-20 01:45:49+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/number_theory/enumerate_quotients.test.cpp
documentation_of: Numeric/floor_enumerate.hpp
layout: document
redirect_from:
- /library/Numeric/floor_enumerate.hpp
- /library/Numeric/floor_enumerate.hpp.html
title: Numeric/floor_enumerate.hpp
---
