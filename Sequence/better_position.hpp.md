---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/cartesian_tree.test.cpp
    title: test/1_library_checker/tree/cartesian_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Sequence/better_position.hpp\"\n\ntemplate<bool equal =\
    \ false, typename T, typename Compare = std::less<T>>\nstd::vector<int> left_better_position(const\
    \ std::vector<T> &seq, Compare comp = Compare()) {\n    int n = seq.size();\n\
    \    std::vector<int> res(n), stk;\n    auto valid = [&](int a, int b) { // b\
    \ is valid w.r.t. a\n        if constexpr (equal) return !comp(seq[a], seq[b]);\n\
    \        else return comp(seq[b], seq[a]);\n    };\n    for (int i = 0; i < n;\
    \ ++i) {\n        while (!stk.empty() && !valid(i, stk.back())) stk.pop_back();\n\
    \        if (stk.empty()) res[i] = -1;\n        else res[i] = stk.back();\n  \
    \      stk.push_back(i);\n    }\n    return res;\n}\n\ntemplate<bool equal = false,\
    \ typename T, typename Compare = std::less<T>>\nstd::vector<int> right_better_position(const\
    \ std::vector<T> &seq, Compare comp = Compare()) {\n    int n = seq.size();\n\
    \    std::vector<int> res(n), stk;\n    auto valid = [&](int a, int b) { // b\
    \ is valid w.r.t. a\n        if constexpr (equal) return !comp(seq[a], seq[b]);\n\
    \        else return comp(seq[b], seq[a]);\n    };\n    for (int i = n - 1; i\
    \ >= 0; --i) {\n        while (!stk.empty() && !valid(i, stk.back())) stk.pop_back();\n\
    \        if (stk.empty()) res[i] = n;\n        else res[i] = stk.back();\n   \
    \     stk.push_back(i);\n    }\n    return res;\n}\n\ntemplate<bool left_equal\
    \ = false, bool right_equal = false, typename T, typename Compare = std::less<T>>\n\
    std::pair<std::vector<int>, std::vector<int>> better_position(const std::vector<T>\
    \ &seq, Compare comp = Compare()) {\n    return std::make_pair(left_better_position<left_equal,\
    \ T, Compare>(seq, comp), right_better_position<right_equal, T, Compare>(seq,\
    \ comp));\n}\n"
  code: "#pragma once\n\ntemplate<bool equal = false, typename T, typename Compare\
    \ = std::less<T>>\nstd::vector<int> left_better_position(const std::vector<T>\
    \ &seq, Compare comp = Compare()) {\n    int n = seq.size();\n    std::vector<int>\
    \ res(n), stk;\n    auto valid = [&](int a, int b) { // b is valid w.r.t. a\n\
    \        if constexpr (equal) return !comp(seq[a], seq[b]);\n        else return\
    \ comp(seq[b], seq[a]);\n    };\n    for (int i = 0; i < n; ++i) {\n        while\
    \ (!stk.empty() && !valid(i, stk.back())) stk.pop_back();\n        if (stk.empty())\
    \ res[i] = -1;\n        else res[i] = stk.back();\n        stk.push_back(i);\n\
    \    }\n    return res;\n}\n\ntemplate<bool equal = false, typename T, typename\
    \ Compare = std::less<T>>\nstd::vector<int> right_better_position(const std::vector<T>\
    \ &seq, Compare comp = Compare()) {\n    int n = seq.size();\n    std::vector<int>\
    \ res(n), stk;\n    auto valid = [&](int a, int b) { // b is valid w.r.t. a\n\
    \        if constexpr (equal) return !comp(seq[a], seq[b]);\n        else return\
    \ comp(seq[b], seq[a]);\n    };\n    for (int i = n - 1; i >= 0; --i) {\n    \
    \    while (!stk.empty() && !valid(i, stk.back())) stk.pop_back();\n        if\
    \ (stk.empty()) res[i] = n;\n        else res[i] = stk.back();\n        stk.push_back(i);\n\
    \    }\n    return res;\n}\n\ntemplate<bool left_equal = false, bool right_equal\
    \ = false, typename T, typename Compare = std::less<T>>\nstd::pair<std::vector<int>,\
    \ std::vector<int>> better_position(const std::vector<T> &seq, Compare comp =\
    \ Compare()) {\n    return std::make_pair(left_better_position<left_equal, T,\
    \ Compare>(seq, comp), right_better_position<right_equal, T, Compare>(seq, comp));\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: Sequence/better_position.hpp
  requiredBy: []
  timestamp: '2026-05-06 17:34:12+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/tree/cartesian_tree.test.cpp
documentation_of: Sequence/better_position.hpp
layout: document
redirect_from:
- /library/Sequence/better_position.hpp
- /library/Sequence/better_position.hpp.html
title: Sequence/better_position.hpp
---
