---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/NullFunc.hpp
    title: Algebra/NullFunc.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Enumerate/bfs_enumerate.hpp\"\n\n#line 2 \"Algebra/NullFunc.hpp\"\
    \n\nstruct NullFunc {\n    constexpr void operator()(auto&&...) const {}\n};\n\
    #line 4 \"Enumerate/bfs_enumerate.hpp\"\n\ntemplate<typename T, typename F_op>\n\
    std::vector<std::pair<T, int>> bfs_enumerate(const T &start, F_op oper, int dis_upper\
    \ = -1, bool sort_by_dis = true) {\n    std::map<T, int> dis;\n    std::queue<T>\
    \ q;\n    auto relax = [&](const T &u, int d) {\n        auto it = dis.find(u);\n\
    \        if (it != dis.end()) return;\n        dis[u] = d;\n        if (dis_upper\
    \ == -1 || d < dis_upper)\n            q.push(u);\n    };\n    relax(start, 0);\n\
    \    while (!q.empty()) {\n        T u = q.front();\n        q.pop();\n      \
    \  int d = dis[u];\n        for (T v : oper(u))\n            relax(v, d + 1);\n\
    \    }\n    std::vector<std::pair<T, int>> res(dis.begin(), dis.end());\n    if\
    \ (sort_by_dis)\n        std::ranges::sort(res, [&](auto a, auto b) {\n      \
    \      return a.second < b.second; \n        });\n    return res;\n}\n"
  code: "#pragma once\n\n#include \"Algebra/NullFunc.hpp\"\n\ntemplate<typename T,\
    \ typename F_op>\nstd::vector<std::pair<T, int>> bfs_enumerate(const T &start,\
    \ F_op oper, int dis_upper = -1, bool sort_by_dis = true) {\n    std::map<T, int>\
    \ dis;\n    std::queue<T> q;\n    auto relax = [&](const T &u, int d) {\n    \
    \    auto it = dis.find(u);\n        if (it != dis.end()) return;\n        dis[u]\
    \ = d;\n        if (dis_upper == -1 || d < dis_upper)\n            q.push(u);\n\
    \    };\n    relax(start, 0);\n    while (!q.empty()) {\n        T u = q.front();\n\
    \        q.pop();\n        int d = dis[u];\n        for (T v : oper(u))\n    \
    \        relax(v, d + 1);\n    }\n    std::vector<std::pair<T, int>> res(dis.begin(),\
    \ dis.end());\n    if (sort_by_dis)\n        std::ranges::sort(res, [&](auto a,\
    \ auto b) {\n            return a.second < b.second; \n        });\n    return\
    \ res;\n}\n"
  dependsOn:
  - Algebra/NullFunc.hpp
  isVerificationFile: false
  path: Enumerate/bfs_enumerate.hpp
  requiredBy: []
  timestamp: '2026-06-29 20:08:17+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Enumerate/bfs_enumerate.hpp
layout: document
redirect_from:
- /library/Enumerate/bfs_enumerate.hpp
- /library/Enumerate/bfs_enumerate.hpp.html
title: Enumerate/bfs_enumerate.hpp
---
