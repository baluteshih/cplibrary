---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: Sequence/count_subset_sum.hpp
    title: Sequence/count_subset_sum.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Enumerate/subset_enumerate.hpp\"\n\ntemplate<typename T>\n\
    std::vector<T> subset_enumerate(const std::vector<T> &arr) {\n    std::vector<T>\
    \ res;\n    T cur = T();\n    auto dfs = [&](auto self, int u) -> void {\n   \
    \     if (u == int(arr.size())) return res.push_back(cur);\n        T tmp = cur;\n\
    \        cur = cur + arr[u];\n        self(self, u + 1);\n        cur = tmp;\n\
    \        self(self, u + 1);\n    };\n    dfs(dfs, 0);\n    return res;\n}\n"
  code: "#pragma once\n\ntemplate<typename T>\nstd::vector<T> subset_enumerate(const\
    \ std::vector<T> &arr) {\n    std::vector<T> res;\n    T cur = T();\n    auto\
    \ dfs = [&](auto self, int u) -> void {\n        if (u == int(arr.size())) return\
    \ res.push_back(cur);\n        T tmp = cur;\n        cur = cur + arr[u];\n   \
    \     self(self, u + 1);\n        cur = tmp;\n        self(self, u + 1);\n   \
    \ };\n    dfs(dfs, 0);\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Enumerate/subset_enumerate.hpp
  requiredBy:
  - Sequence/count_subset_sum.hpp
  timestamp: '2026-06-28 02:52:11+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Enumerate/subset_enumerate.hpp
layout: document
redirect_from:
- /library/Enumerate/subset_enumerate.hpp
- /library/Enumerate/subset_enumerate.hpp.html
title: Enumerate/subset_enumerate.hpp
---
