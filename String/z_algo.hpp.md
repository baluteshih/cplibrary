---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/string/zalgorithm.test.cpp
    title: test/1_library_checker/string/zalgorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"String/z_algo.hpp\"\n\nstd::vector<int> make_z(const std::string\
    \ &s) {\n    std::vector<int> z(s.size());\n    int l = 0, r = 0;\n    z[0] =\
    \ s.size();\n    for (int i = 1; i < std::ssize(s); ++i) {\n        z[i] = std::max(0,\
    \ std::min(r - i + 1, z[i - l]));\n        while (i + z[i] < std::ssize(s) &&\
    \ s[i + z[i]] == s[z[i]]) ++z[i];\n        if (i + z[i] - 1 > r) l = i, r = i\
    \ + z[i] - 1;\n    }\n    return z;\n}\n"
  code: "#pragma once\n\nstd::vector<int> make_z(const std::string &s) {\n    std::vector<int>\
    \ z(s.size());\n    int l = 0, r = 0;\n    z[0] = s.size();\n    for (int i =\
    \ 1; i < std::ssize(s); ++i) {\n        z[i] = std::max(0, std::min(r - i + 1,\
    \ z[i - l]));\n        while (i + z[i] < std::ssize(s) && s[i + z[i]] == s[z[i]])\
    \ ++z[i];\n        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;\n    }\n   \
    \ return z;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: String/z_algo.hpp
  requiredBy: []
  timestamp: '2026-02-28 23:10:21+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/string/zalgorithm.test.cpp
documentation_of: String/z_algo.hpp
layout: document
redirect_from:
- /library/String/z_algo.hpp
- /library/String/z_algo.hpp.html
title: String/z_algo.hpp
---
