---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Sequence/better_position.hpp
    title: Sequence/better_position.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 1 \"test/1_library_checker/tree/cartesian_tree.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n#line 2 \"\
    assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3 \"test/1_library_checker/tree/cartesian_tree.test.cpp\"\
    \n\n#line 2 \"Sequence/better_position.hpp\"\n\ntemplate<bool equal = false, typename\
    \ T, typename Compare = std::less<T>>\nstd::vector<int> left_better_position(const\
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
    \ comp));\n}\n#line 5 \"test/1_library_checker/tree/cartesian_tree.test.cpp\"\n\
    \nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n;\n\
    \    std::cin >> n;\n    std::vector<int> arr(n);\n    for (int &i : arr)\n  \
    \      std::cin >> i;\n    auto [lft, rgt] = better_position(arr);\n    std::vector<int>\
    \ ans(n);\n    for (int i = 0; i < n; ++i)\n        if (lft[i] == -1 && rgt[i]\
    \ == n) ans[i] = i;\n        else if (lft[i] == -1) ans[i] = rgt[i];\n       \
    \ else if (rgt[i] == n) ans[i] = lft[i];\n        else ans[i] = arr[lft[i]] <\
    \ arr[rgt[i]] ? rgt[i] : lft[i];\n    for (int i = 0; i < n; ++i)\n        std::cout\
    \ << ans[i] << \" \\n\"[i + 1 == n];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n#include\
    \ \"assumption.hpp\"\n\n#include \"Sequence/better_position.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n;\n    std::cin\
    \ >> n;\n    std::vector<int> arr(n);\n    for (int &i : arr)\n        std::cin\
    \ >> i;\n    auto [lft, rgt] = better_position(arr);\n    std::vector<int> ans(n);\n\
    \    for (int i = 0; i < n; ++i)\n        if (lft[i] == -1 && rgt[i] == n) ans[i]\
    \ = i;\n        else if (lft[i] == -1) ans[i] = rgt[i];\n        else if (rgt[i]\
    \ == n) ans[i] = lft[i];\n        else ans[i] = arr[lft[i]] < arr[rgt[i]] ? rgt[i]\
    \ : lft[i];\n    for (int i = 0; i < n; ++i)\n        std::cout << ans[i] << \"\
    \ \\n\"[i + 1 == n];\n}\n"
  dependsOn:
  - assumption.hpp
  - Sequence/better_position.hpp
  isVerificationFile: true
  path: test/1_library_checker/tree/cartesian_tree.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 13:11:38+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/tree/cartesian_tree.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/tree/cartesian_tree.test.cpp
- /verify/test/1_library_checker/tree/cartesian_tree.test.cpp.html
title: test/1_library_checker/tree/cartesian_tree.test.cpp
---
