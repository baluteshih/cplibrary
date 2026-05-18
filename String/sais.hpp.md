---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/string/number_of_substrings.test.cpp
    title: test/1_library_checker/string/number_of_substrings.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/string/suffixarray.test.cpp
    title: test/1_library_checker/string/suffixarray.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"String/sais.hpp\"\n\n/*\n0-base\nThe input string should\
    \ not contain 0\nsa[i]: sa[i]-th suffix is the i-th lexicographically smallest\
    \ suffix.\nhi[i]: LCP of suffix sa[i] and suffix sa[i - 1].\nra[i]: the rank of\
    \ the i-th suffix\n*/\nstruct Suffix {\n    int n; std::vector<int> sa, hi, ra;\n\
    \    Suffix(const auto &_s, int _n) : n(_n), hi(n), ra(n) {\n        for (const\
    \ auto &c : _s) assert(c != 0);\n        std::vector<int> s(_s.begin(), _s.end());\n\
    \        s.push_back(0);\n        sa = sais(s); sa.erase(sa.begin());\n      \
    \  for (int i = 0; i < n; ++i) ra[sa[i]] = i;\n        for (int i = 0, h = 0;\
    \ i < n; ++i) {\n            if (!ra[i]) { h = 0; continue; }\n            for\
    \ (int j = sa[ra[i] - 1]; std::max(i, j) + h < n && s[i + h] == s[j + h];) ++h;\n\
    \            hi[ra[i]] = h ? h-- : 0;\n        }\n    }\n    Suffix(const auto\
    \ &_s) : Suffix(_s, (int)_s.size()) {}\n    static auto sais(const auto &s) {\n\
    \        const int n = SZ(s), z = std::ranges::max(s) + 1;\n        if (n == 1)\
    \ return std::vector{0};\n        std::vector<int> c(z); for (int x : s) ++c[x];\n\
    \        std::partial_sum(c.begin(), c.end(), c.begin());\n        std::vector<int>\
    \ sa(n);\n        auto I = std::views::iota(0, n);\n        std::vector<bool>\
    \ t(n, true);\n        for (int i = n - 2; i >= 0; --i)\n            t[i] = (s[i]\
    \ == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);\n        auto is_lms = std::views::filter([&t](int\
    \ x) { \n            return x && t[x] && !t[x - 1];\n        });\n        auto\
    \ induce = [&] {\n            for (auto x = c; int y : sa)\n                if\
    \ (y--) if (!t[y]) sa[x[s[y] - 1]++] = y;\n            for (auto x = c; int y\
    \ : sa | std::views::reverse)\n                if (y--) if (t[y]) sa[--x[s[y]]]\
    \ = y;\n        };\n        std::vector<int> lms, q(n);\n        lms.reserve(n);\n\
    \        for (auto x = c; int i : I | is_lms)\n            q[i] = lms.size(),\
    \ lms.push_back(sa[--x[s[i]]] = i);\n        induce();\n        std::vector<int>\
    \ ns(lms.size());\n        for (int j = -1, nz = 0; int i : sa | is_lms) {\n \
    \           if (j >= 0) {\n                int len = min({n - i, n - j, lms[q[i]\
    \ + 1] - i});\n                ns[q[i]] = nz += std::lexicographical_compare(std::begin(s)\
    \ + j, std::begin(s) + j + len, std::begin(s) + i, std::begin(s) + i + len);\n\
    \            }\n            j = i;\n        }\n        std::ranges::fill(sa, 0);\n\
    \        auto nsa = sais(ns);\n        for (auto x = c; int y : nsa | std::views::reverse)\n\
    \            y = lms[y], sa[--x[s[y]]] = y;\n        return induce(), sa;\n  \
    \  }\n};\n"
  code: "#pragma once\n\n/*\n0-base\nThe input string should not contain 0\nsa[i]:\
    \ sa[i]-th suffix is the i-th lexicographically smallest suffix.\nhi[i]: LCP of\
    \ suffix sa[i] and suffix sa[i - 1].\nra[i]: the rank of the i-th suffix\n*/\n\
    struct Suffix {\n    int n; std::vector<int> sa, hi, ra;\n    Suffix(const auto\
    \ &_s, int _n) : n(_n), hi(n), ra(n) {\n        for (const auto &c : _s) assert(c\
    \ != 0);\n        std::vector<int> s(_s.begin(), _s.end());\n        s.push_back(0);\n\
    \        sa = sais(s); sa.erase(sa.begin());\n        for (int i = 0; i < n; ++i)\
    \ ra[sa[i]] = i;\n        for (int i = 0, h = 0; i < n; ++i) {\n            if\
    \ (!ra[i]) { h = 0; continue; }\n            for (int j = sa[ra[i] - 1]; std::max(i,\
    \ j) + h < n && s[i + h] == s[j + h];) ++h;\n            hi[ra[i]] = h ? h-- :\
    \ 0;\n        }\n    }\n    Suffix(const auto &_s) : Suffix(_s, (int)_s.size())\
    \ {}\n    static auto sais(const auto &s) {\n        const int n = SZ(s), z =\
    \ std::ranges::max(s) + 1;\n        if (n == 1) return std::vector{0};\n     \
    \   std::vector<int> c(z); for (int x : s) ++c[x];\n        std::partial_sum(c.begin(),\
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
    \ i : sa | is_lms) {\n            if (j >= 0) {\n                int len = min({n\
    \ - i, n - j, lms[q[i] + 1] - i});\n                ns[q[i]] = nz += std::lexicographical_compare(std::begin(s)\
    \ + j, std::begin(s) + j + len, std::begin(s) + i, std::begin(s) + i + len);\n\
    \            }\n            j = i;\n        }\n        std::ranges::fill(sa, 0);\n\
    \        auto nsa = sais(ns);\n        for (auto x = c; int y : nsa | std::views::reverse)\n\
    \            y = lms[y], sa[--x[s[y]]] = y;\n        return induce(), sa;\n  \
    \  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: String/sais.hpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/string/suffixarray.test.cpp
  - test/1_library_checker/string/number_of_substrings.test.cpp
documentation_of: String/sais.hpp
layout: document
redirect_from:
- /library/String/sais.hpp
- /library/String/sais.hpp.html
title: String/sais.hpp
---
