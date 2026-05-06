---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/string/enumerate_palindromes.test.cpp
    title: test/1_library_checker/string/enumerate_palindromes.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"String/manacher.hpp\"\n\nstd::vector<int> manacher(const\
    \ string &tmp) {\n    std::string s = \"%\";\n    int l = 0, r = 0;\n    for (char\
    \ c : tmp) s.push_back(c), s.push_back('%');\n    std::vector<int> z(s.size());\n\
    \    for (int i = 0; i < std::ssize(s); ++i) {\n        z[i] = r > i ? std::min(z[2\
    \ * l - i], r - i) : 1;\n        while (i - z[i] >= 0 && i + z[i] < std::ssize(s)\
    \ && s[i + z[i]] == s[i - z[i]]) ++z[i];\n        if (z[i] + i > r) r = z[i] +\
    \ i, l = i;\n    }\n    return z;\n}\n/*\nget the radius of center i, 0-base\n\
    for example, aba has radius 2\n*/\nint get_radius_odd(const std::vector<int> &z,\
    \ int i) {\n    return z[i * 2 + 1] / 2;\n}\n/*\nget the radius of center i, i\
    \ + 1, 0-base\nfor example, abba has radius 2\n*/\nint get_radius_even(const std::vector<int>\
    \ &z, int i) {\n    return z[i * 2 + 2] / 2;\n}\n"
  code: "#pragma once\n\nstd::vector<int> manacher(const string &tmp) {\n    std::string\
    \ s = \"%\";\n    int l = 0, r = 0;\n    for (char c : tmp) s.push_back(c), s.push_back('%');\n\
    \    std::vector<int> z(s.size());\n    for (int i = 0; i < std::ssize(s); ++i)\
    \ {\n        z[i] = r > i ? std::min(z[2 * l - i], r - i) : 1;\n        while\
    \ (i - z[i] >= 0 && i + z[i] < std::ssize(s) && s[i + z[i]] == s[i - z[i]]) ++z[i];\n\
    \        if (z[i] + i > r) r = z[i] + i, l = i;\n    }\n    return z;\n}\n/*\n\
    get the radius of center i, 0-base\nfor example, aba has radius 2\n*/\nint get_radius_odd(const\
    \ std::vector<int> &z, int i) {\n    return z[i * 2 + 1] / 2;\n}\n/*\nget the\
    \ radius of center i, i + 1, 0-base\nfor example, abba has radius 2\n*/\nint get_radius_even(const\
    \ std::vector<int> &z, int i) {\n    return z[i * 2 + 2] / 2;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: String/manacher.hpp
  requiredBy: []
  timestamp: '2026-02-28 23:10:21+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/string/enumerate_palindromes.test.cpp
documentation_of: String/manacher.hpp
layout: document
redirect_from:
- /library/String/manacher.hpp
- /library/String/manacher.hpp.html
title: String/manacher.hpp
---
