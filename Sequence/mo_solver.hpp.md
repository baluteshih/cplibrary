---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/NullFunc.hpp
    title: Algebra/NullFunc.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_range_mode_query.test.cpp
    title: test/1_library_checker/data_structure/static_range_mode_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Sequence/mo_solver.hpp\"\n\n#line 2 \"Algebra/NullFunc.hpp\"\
    \n\nstruct NullFunc {\n    constexpr void operator()(auto&&...) const {}\n};\n\
    #line 4 \"Sequence/mo_solver.hpp\"\n\n/*\nintervals are [l, r)\nquery(idx): answer\
    \ the idx-th query\nadd_left(l), remove_left(l)\nadd_right(r), remove_right(r):\
    \ equal to add_left and remove_left if no specify\n*/\ntemplate<typename F_query,\
    \ typename F_add_left, typename F_remove_left, typename F_add_right = NullFunc,\
    \ typename F_remove_right = NullFunc>\nvoid mo_solver(const std::vector<std::pair<int,\
    \ int>> &querys, F_query query, F_add_left add_left, F_remove_left remove_left,\
    \ F_add_right add_right = NullFunc{}, F_remove_right remove_right = NullFunc{})\
    \ {\n    constexpr bool useAddRight = !std::is_same_v<std::decay_t<decltype(add_right)>,\
    \ NullFunc>;\n    constexpr bool useRemoveRight = !std::is_same_v<std::decay_t<decltype(remove_right)>,\
    \ NullFunc>;\n    auto hilbert = [&](int n, int x, int y) {\n        long long\
    \ res = 0;\n        for (int s = n / 2; s; s >>= 1) {\n            int rx = (x\
    \ & s) > 0;\n            int ry = (y & s) > 0;\n            res += s * 1ll * s\
    \ * ((3 * rx) ^ ry);\n            if (ry == 0) {\n                if (rx == 1)\
    \ x = s - 1 - x, y = s - 1 - y;\n                std::swap(x, y);\n          \
    \  }\n        }\n        return res;\n    }; // n = 2^k\n\n    int n = 0;\n  \
    \  for (auto &[l, r] : querys) n = std::max(n, r);\n    n = std::bit_ceil(static_cast<unsigned\
    \ int>(n + 1));\n    std::vector<long long> pos(querys.size());\n    std::vector<int>\
    \ idx(querys.size());\n    for (int i = 0; auto &[l, r] : querys) pos[i++] = hilbert(n,\
    \ l, r);\n    std::iota(idx.begin(), idx.end(), 0);\n    std::ranges::sort(idx,\
    \ [&](int a, int b) { return pos[a] < pos[b]; });\n\n    int cur_l = 0, cur_r\
    \ = 0;\n    for (int i : idx) {\n        auto [l, r] = querys[i];\n        while\
    \ (cur_l > l) add_left(--cur_l);\n        while (cur_r < r) \n            if constexpr\
    \ (useAddRight) add_right(cur_r++);\n            else add_left(cur_r++);\n   \
    \     while (cur_l < l) remove_left(cur_l++);\n        while (cur_r > r)\n   \
    \         if constexpr (useRemoveRight) remove_right(--cur_r);\n            else\
    \ remove_left(--cur_r);\n        query(i);\n    }\n}\n"
  code: "#pragma once\n\n#include \"Algebra/NullFunc.hpp\"\n\n/*\nintervals are [l,\
    \ r)\nquery(idx): answer the idx-th query\nadd_left(l), remove_left(l)\nadd_right(r),\
    \ remove_right(r): equal to add_left and remove_left if no specify\n*/\ntemplate<typename\
    \ F_query, typename F_add_left, typename F_remove_left, typename F_add_right =\
    \ NullFunc, typename F_remove_right = NullFunc>\nvoid mo_solver(const std::vector<std::pair<int,\
    \ int>> &querys, F_query query, F_add_left add_left, F_remove_left remove_left,\
    \ F_add_right add_right = NullFunc{}, F_remove_right remove_right = NullFunc{})\
    \ {\n    constexpr bool useAddRight = !std::is_same_v<std::decay_t<decltype(add_right)>,\
    \ NullFunc>;\n    constexpr bool useRemoveRight = !std::is_same_v<std::decay_t<decltype(remove_right)>,\
    \ NullFunc>;\n    auto hilbert = [&](int n, int x, int y) {\n        long long\
    \ res = 0;\n        for (int s = n / 2; s; s >>= 1) {\n            int rx = (x\
    \ & s) > 0;\n            int ry = (y & s) > 0;\n            res += s * 1ll * s\
    \ * ((3 * rx) ^ ry);\n            if (ry == 0) {\n                if (rx == 1)\
    \ x = s - 1 - x, y = s - 1 - y;\n                std::swap(x, y);\n          \
    \  }\n        }\n        return res;\n    }; // n = 2^k\n\n    int n = 0;\n  \
    \  for (auto &[l, r] : querys) n = std::max(n, r);\n    n = std::bit_ceil(static_cast<unsigned\
    \ int>(n + 1));\n    std::vector<long long> pos(querys.size());\n    std::vector<int>\
    \ idx(querys.size());\n    for (int i = 0; auto &[l, r] : querys) pos[i++] = hilbert(n,\
    \ l, r);\n    std::iota(idx.begin(), idx.end(), 0);\n    std::ranges::sort(idx,\
    \ [&](int a, int b) { return pos[a] < pos[b]; });\n\n    int cur_l = 0, cur_r\
    \ = 0;\n    for (int i : idx) {\n        auto [l, r] = querys[i];\n        while\
    \ (cur_l > l) add_left(--cur_l);\n        while (cur_r < r) \n            if constexpr\
    \ (useAddRight) add_right(cur_r++);\n            else add_left(cur_r++);\n   \
    \     while (cur_l < l) remove_left(cur_l++);\n        while (cur_r > r)\n   \
    \         if constexpr (useRemoveRight) remove_right(--cur_r);\n            else\
    \ remove_left(--cur_r);\n        query(i);\n    }\n}\n"
  dependsOn:
  - Algebra/NullFunc.hpp
  isVerificationFile: false
  path: Sequence/mo_solver.hpp
  requiredBy: []
  timestamp: '2026-06-20 01:10:00+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/static_range_mode_query.test.cpp
documentation_of: Sequence/mo_solver.hpp
layout: document
redirect_from:
- /library/Sequence/mo_solver.hpp
- /library/Sequence/mo_solver.hpp.html
title: Sequence/mo_solver.hpp
---
