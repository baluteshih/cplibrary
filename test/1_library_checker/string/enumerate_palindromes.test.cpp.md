---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: String/manacher.hpp
    title: String/manacher.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_palindromes
    links:
    - https://judge.yosupo.jp/problem/enumerate_palindromes
  bundledCode: "#line 1 \"test/1_library_checker/string/enumerate_palindromes.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\n\
    #line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/string/enumerate_palindromes.test.cpp\"\n\n#line\
    \ 2 \"String/manacher.hpp\"\n\nstd::vector<int> manacher(const std::string &tmp)\
    \ {\n    std::string s = \"%\";\n    int l = 0, r = 0;\n    for (char c : tmp)\
    \ s.push_back(c), s.push_back('%');\n    std::vector<int> z(s.size());\n    for\
    \ (int i = 0; i < std::ssize(s); ++i) {\n        z[i] = r > i ? std::min(z[2 *\
    \ l - i], r - i) : 1;\n        while (i - z[i] >= 0 && i + z[i] < std::ssize(s)\
    \ && s[i + z[i]] == s[i - z[i]]) ++z[i];\n        if (z[i] + i > r) r = z[i] +\
    \ i, l = i;\n    }\n    return z;\n}\n/*\nget the radius of center i, 0-base\n\
    for example, aba has radius 2\n*/\nint get_radius_odd(const std::vector<int> &z,\
    \ int i) {\n    return z[i * 2 + 1] / 2;\n}\n/*\nget the radius of center i, i\
    \ + 1, 0-base\nfor example, abba has radius 2\n*/\nint get_radius_even(const std::vector<int>\
    \ &z, int i) {\n    return z[i * 2 + 2] / 2;\n}\n#line 5 \"test/1_library_checker/string/enumerate_palindromes.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    std::string\
    \ s;\n    std::cin >> s;\n    auto z = manacher(s);\n    for (int i = 0; i < int(s.size());\
    \ ++i) {\n        std::cout << get_radius_odd(z, i) * 2 - 1;\n        if (i +\
    \ 1 < int(s.size())) std::cout << \" \" << get_radius_even(z, i) * 2 << \" \"\
    ;\n        else std::cout << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\
    \n#include \"assumption.hpp\"\n\n#include \"String/manacher.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    std::string s;\n\
    \    std::cin >> s;\n    auto z = manacher(s);\n    for (int i = 0; i < int(s.size());\
    \ ++i) {\n        std::cout << get_radius_odd(z, i) * 2 - 1;\n        if (i +\
    \ 1 < int(s.size())) std::cout << \" \" << get_radius_even(z, i) * 2 << \" \"\
    ;\n        else std::cout << \"\\n\";\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - String/manacher.hpp
  isVerificationFile: true
  path: test/1_library_checker/string/enumerate_palindromes.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 14:18:54+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/string/enumerate_palindromes.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/string/enumerate_palindromes.test.cpp
- /verify/test/1_library_checker/string/enumerate_palindromes.test.cpp.html
title: test/1_library_checker/string/enumerate_palindromes.test.cpp
---
