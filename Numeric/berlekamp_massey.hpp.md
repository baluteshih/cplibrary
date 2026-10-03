---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/other/find_linear_recurrence.test.cpp
    title: test/1_library_checker/other/find_linear_recurrence.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/berlekamp_massey.hpp\"\n\ntemplate <typename T>\n\
    std::vector<T> berlekamp_massey(const std::vector<T> &output) {\n    std::vector<T>\
    \ d(output.size() + 1), me, he;\n    for (int f = 0, i = 1; i <= int(output.size());\
    \ ++i) {\n        for (int j = 0; j < int(me.size()); ++j)\n            d[i] +=\
    \ output[i - j - 2] * me[j];\n        if ((d[i] -= output[i - 1]) == 0) continue;\n\
    \        if (me.empty()) {\n            me.resize(f = i);\n            continue;\n\
    \        }\n        std::vector<T> o(i - f - 1);\n        T k = -d[i] / d[f];\n\
    \        o.push_back(-k);\n        for (T x : he) o.push_back(x * k);\n      \
    \  if (o.size() < me.size()) o.resize(me.size());\n        for (int j = 0; j <\
    \ int(me.size()); ++j) o[j] += me[j];\n        if (i - f + int(he.size()) >= int(me.size()))\
    \ he = me, f = i;\n        me = o;\n    }\n    return me;\n}\n"
  code: "#pragma once\n\ntemplate <typename T>\nstd::vector<T> berlekamp_massey(const\
    \ std::vector<T> &output) {\n    std::vector<T> d(output.size() + 1), me, he;\n\
    \    for (int f = 0, i = 1; i <= int(output.size()); ++i) {\n        for (int\
    \ j = 0; j < int(me.size()); ++j)\n            d[i] += output[i - j - 2] * me[j];\n\
    \        if ((d[i] -= output[i - 1]) == 0) continue;\n        if (me.empty())\
    \ {\n            me.resize(f = i);\n            continue;\n        }\n       \
    \ std::vector<T> o(i - f - 1);\n        T k = -d[i] / d[f];\n        o.push_back(-k);\n\
    \        for (T x : he) o.push_back(x * k);\n        if (o.size() < me.size())\
    \ o.resize(me.size());\n        for (int j = 0; j < int(me.size()); ++j) o[j]\
    \ += me[j];\n        if (i - f + int(he.size()) >= int(me.size())) he = me, f\
    \ = i;\n        me = o;\n    }\n    return me;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/berlekamp_massey.hpp
  requiredBy: []
  timestamp: '2026-10-03 13:08:40+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/other/find_linear_recurrence.test.cpp
documentation_of: Numeric/berlekamp_massey.hpp
layout: document
redirect_from:
- /library/Numeric/berlekamp_massey.hpp
- /library/Numeric/berlekamp_massey.hpp.html
title: Numeric/berlekamp_massey.hpp
---
