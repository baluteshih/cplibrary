---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/7_loj/2302.test.cpp
    title: test/7_loj/2302.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://codeforces.com/blog/entry/115626
  bundledCode: "#line 2 \"Misc/trygub_number.hpp\"\n\n// source: https://codeforces.com/blog/entry/115626\n\
    template<typename T, T base = 2>\nclass trygub_number {\npublic:\n    std::map<int,\
    \ T> digs;\n    // += a * base ** b\n    void add(T a, int b) {\n        digs[b]\
    \ += a;\n        int t;\n        do {\n            t = digs[b] / base;\n     \
    \       digs[b + 1] += t;\n            digs[b] -= t * base;\n            if (digs[b]\
    \ == 0) digs.erase(b);\n            b++;\n        } while(t);\n        if (digs[b]\
    \ == 0)\n            digs.erase(b);\n    }\n    // get the k-th bit\n    T get(int\
    \ k) {\n        auto it = digs.lower_bound(k);\n        T ans = it == std::end(digs)\
    \ || it->first > k ? 0 : it->second;\n        if(it != std::begin(digs) && std::prev(it)->second\
    \ < 0)\n            ans--;\n        return (ans + base) % base;\n    }\n};\n"
  code: "#pragma once\n\n// source: https://codeforces.com/blog/entry/115626\ntemplate<typename\
    \ T, T base = 2>\nclass trygub_number {\npublic:\n    std::map<int, T> digs;\n\
    \    // += a * base ** b\n    void add(T a, int b) {\n        digs[b] += a;\n\
    \        int t;\n        do {\n            t = digs[b] / base;\n            digs[b\
    \ + 1] += t;\n            digs[b] -= t * base;\n            if (digs[b] == 0)\
    \ digs.erase(b);\n            b++;\n        } while(t);\n        if (digs[b] ==\
    \ 0)\n            digs.erase(b);\n    }\n    // get the k-th bit\n    T get(int\
    \ k) {\n        auto it = digs.lower_bound(k);\n        T ans = it == std::end(digs)\
    \ || it->first > k ? 0 : it->second;\n        if(it != std::begin(digs) && std::prev(it)->second\
    \ < 0)\n            ans--;\n        return (ans + base) % base;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Misc/trygub_number.hpp
  requiredBy: []
  timestamp: '2026-05-04 15:02:52+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/7_loj/2302.test.cpp
documentation_of: Misc/trygub_number.hpp
layout: document
redirect_from:
- /library/Misc/trygub_number.hpp
- /library/Misc/trygub_number.hpp.html
title: Misc/trygub_number.hpp
---
