---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: String/sais.hpp
    title: String/sais.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"test/1_library_checker/string/suffixarray.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n#line 2 \"assumption.hpp\"\
    \n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3 \"test/1_library_checker/string/suffixarray.test.cpp\"\
    \n\n#line 2 \"String/sais.hpp\"\n\n/*\n0-base\nThe input string should not contain\
    \ 0\nsa[i]: sa[i]-th suffix is the i-th lexicographically smallest suffix.\nhi[i]:\
    \ LCP of suffix sa[i] and suffix sa[i - 1].\nra[i]: the rank of the i-th suffix\n\
    */\nstruct Suffix {\n    int n; std::vector<int> sa, hi, ra;\n    Suffix(const\
    \ auto &_s, int _n) : n(_n), hi(n), ra(n) {\n        for (const auto &c : _s)\
    \ assert(c != 0);\n        std::vector<int> s(_s.begin(), _s.end());\n       \
    \ s.push_back(0);\n        sa = sais(s); sa.erase(sa.begin());\n        for (int\
    \ i = 0; i < n; ++i) ra[sa[i]] = i;\n        for (int i = 0, h = 0; i < n; ++i)\
    \ {\n            if (!ra[i]) { h = 0; continue; }\n            for (int j = sa[ra[i]\
    \ - 1]; std::max(i, j) + h < n && s[i + h] == s[j + h];) ++h;\n            hi[ra[i]]\
    \ = h ? h-- : 0;\n        }\n    }\n    Suffix(const auto &_s) : Suffix(_s, (int)_s.size())\
    \ {}\n    static auto sais(const auto &s) {\n        const int n = s.size(), z\
    \ = std::ranges::max(s) + 1;\n        if (n == 1) return std::vector{0};\n   \
    \     std::vector<int> c(z); for (int x : s) ++c[x];\n        std::partial_sum(c.begin(),\
    \ c.end(), c.begin());\n        std::vector<int> sa(n);\n        auto I = std::views::iota(0,\
    \ n);\n        std::vector<bool> t(n, true);\n        for (int i = n - 2; i >=\
    \ 0; --i)\n            t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);\n\
    \        auto is_lms = std::views::filter([&t](int x) { \n            return x\
    \ && t[x] && !t[x - 1];\n        });\n        auto induce = [&] {\n          \
    \  for (auto x = c; int y : sa)\n                if (y--) if (!t[y]) sa[x[s[y]\
    \ - 1]++] = y;\n            for (auto x = c; int y : sa | std::views::reverse)\n\
    \                if (y--) if (t[y]) sa[--x[s[y]]] = y;\n        };\n        std::vector<int>\
    \ lms, q(n);\n        lms.reserve(n);\n        for (auto x = c; int i : I | is_lms)\n\
    \            q[i] = lms.size(), lms.push_back(sa[--x[s[i]]] = i);\n        induce();\n\
    \        std::vector<int> ns(lms.size());\n        for (int j = -1, nz = 0; int\
    \ i : sa | is_lms) {\n            if (j >= 0) {\n                int len = std::min({n\
    \ - i, n - j, lms[q[i] + 1] - i});\n                ns[q[i]] = nz += std::lexicographical_compare(std::begin(s)\
    \ + j, std::begin(s) + j + len, std::begin(s) + i, std::begin(s) + i + len);\n\
    \            }\n            j = i;\n        }\n        std::ranges::fill(sa, 0);\n\
    \        auto nsa = sais(ns);\n        for (auto x = c; int y : nsa | std::views::reverse)\n\
    \            y = lms[y], sa[--x[s[y]]] = y;\n        return induce(), sa;\n  \
    \  }\n};\n#line 5 \"test/1_library_checker/string/suffixarray.test.cpp\"\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    std::string\
    \ s;\n    std::cin >> s;\n    auto suffix = Suffix(s);\n    for (int i = 0; i\
    \ < int(s.size()); ++i)\n        std::cout << suffix.sa[i] << \" \\n\"[i + 1 ==\
    \ int(s.size())];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n#include\
    \ \"assumption.hpp\"\n\n#include \"String/sais.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    std::string s;\n    std::cin >> s;\n    auto suffix =\
    \ Suffix(s);\n    for (int i = 0; i < int(s.size()); ++i)\n        std::cout <<\
    \ suffix.sa[i] << \" \\n\"[i + 1 == int(s.size())];\n}\n"
  dependsOn:
  - assumption.hpp
  - String/sais.hpp
  isVerificationFile: true
  path: test/1_library_checker/string/suffixarray.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 13:39:32+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/string/suffixarray.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/string/suffixarray.test.cpp
- /verify/test/1_library_checker/string/suffixarray.test.cpp.html
title: test/1_library_checker/string/suffixarray.test.cpp
---
