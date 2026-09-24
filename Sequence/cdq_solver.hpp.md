---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/point_add_rectangle_sum.test.cpp
    title: test/1_library_checker/data_structure/point_add_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp
    title: test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Sequence/cdq_solver.hpp\"\n\ntemplate<typename E, typename\
    \ F_Add, typename F_Query, typename F_Undo>\nvoid cdq_solver(const std::vector<E>\
    \ &elements, F_Add add, F_Query query, F_Undo undo) {\n    if (elements.empty())\
    \ return;\n    std::vector<int> idx(elements.size()), temp(elements.size());\n\
    \    std::iota(idx.begin(), idx.end(), 0);\n    auto solve = [&](auto self, int\
    \ l, int r) -> void {\n        if (l == r) return;\n        int mid = (l + r)\
    \ >> 1;\n        self(self, l, mid), self(self, mid + 1, r);\n        int i =\
    \ l, j = mid + 1, k = l;\n        while (i <= mid && j <= r) {\n            if\
    \ (elements[idx[i]] < elements[idx[j]]) add(elements[temp[k++] = idx[i++]]);\n\
    \            else query(elements[temp[k++] = idx[j++]]);\n        }\n        while\
    \ (j <= r) query(elements[temp[k++] = idx[j++]]);\n        std::copy(idx.begin()\
    \ + i, idx.begin() + mid + 1, temp.begin() + k);\n        while (i > l) undo(elements[idx[--i]]);\n\
    \        std::copy(temp.begin() + l, temp.begin() + r + 1, idx.begin() + l);\n\
    \    };\n    solve(solve, 0, elements.size() - 1);\n}\n"
  code: "#pragma once\n\ntemplate<typename E, typename F_Add, typename F_Query, typename\
    \ F_Undo>\nvoid cdq_solver(const std::vector<E> &elements, F_Add add, F_Query\
    \ query, F_Undo undo) {\n    if (elements.empty()) return;\n    std::vector<int>\
    \ idx(elements.size()), temp(elements.size());\n    std::iota(idx.begin(), idx.end(),\
    \ 0);\n    auto solve = [&](auto self, int l, int r) -> void {\n        if (l\
    \ == r) return;\n        int mid = (l + r) >> 1;\n        self(self, l, mid),\
    \ self(self, mid + 1, r);\n        int i = l, j = mid + 1, k = l;\n        while\
    \ (i <= mid && j <= r) {\n            if (elements[idx[i]] < elements[idx[j]])\
    \ add(elements[temp[k++] = idx[i++]]);\n            else query(elements[temp[k++]\
    \ = idx[j++]]);\n        }\n        while (j <= r) query(elements[temp[k++] =\
    \ idx[j++]]);\n        std::copy(idx.begin() + i, idx.begin() + mid + 1, temp.begin()\
    \ + k);\n        while (i > l) undo(elements[idx[--i]]);\n        std::copy(temp.begin()\
    \ + l, temp.begin() + r + 1, idx.begin() + l);\n    };\n    solve(solve, 0, elements.size()\
    \ - 1);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Sequence/cdq_solver.hpp
  requiredBy: []
  timestamp: '2026-09-24 21:34:44+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/point_add_rectangle_sum.test.cpp
  - test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp
documentation_of: Sequence/cdq_solver.hpp
layout: document
redirect_from:
- /library/Sequence/cdq_solver.hpp
- /library/Sequence/cdq_solver.hpp.html
title: Sequence/cdq_solver.hpp
---
