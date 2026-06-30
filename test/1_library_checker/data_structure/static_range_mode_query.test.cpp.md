---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/NullFunc.hpp
    title: Algebra/NullFunc.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/Discretization.hpp
    title: Discretization
  - icon: ':heavy_check_mark:'
    path: Sequence/mo_solver.hpp
    title: Sequence/mo_solver.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_mode_query
    links:
    - https://judge.yosupo.jp/problem/static_range_mode_query
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/static_range_mode_query.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_mode_query\"\n\
    #line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/data_structure/static_range_mode_query.test.cpp\"\
    \n\n#line 2 \"Sequence/mo_solver.hpp\"\n\n#line 2 \"Algebra/NullFunc.hpp\"\n\n\
    struct NullFunc {\n    constexpr void operator()(auto&&...) const {}\n};\n#line\
    \ 4 \"Sequence/mo_solver.hpp\"\n\n/*\nintervals are [l, r)\nquery(idx): answer\
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
    \ remove_left(--cur_r);\n        query(i);\n    }\n}\n#line 2 \"DataStructure/Discretization.hpp\"\
    \n\ntemplate<typename T>\nclass Discretization {\n    std::vector<T> vals;\n \
    \   static std::vector<T> sort_and_unique(std::ranges::range auto &&_vals) {\n\
    \        std::vector<T> res;\n        std::ranges::copy(_vals, std::back_inserter(res));\n\
    \        std::ranges::sort(res);\n        auto [first, last] = std::ranges::unique(res);\n\
    \        res.erase(first, last);\n        return res;\n    }\npublic:\n    int\
    \ idx(T x) {\n        auto it = std::ranges::lower_bound(vals, x);\n        if\
    \ (it == vals.end() || *it != x) return -1;\n        return it - vals.begin();\n\
    \    }\n    int safe_idx(T x) {\n        int res = idx(x);\n        assert(res\
    \ != -1);\n        return res;\n    }\n    Discretization(std::ranges::range auto\
    \ &&_vals) : vals(sort_and_unique(std::forward<decltype(_vals)>(_vals))) {}\n\
    \    int left_close(T x) {\n        return std::ranges::lower_bound(vals, x) -\
    \ vals.begin();\n    }\n    int left_open(T x) {\n        return std::ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(vals,\
    \ x) - vals.begin();\n    }\n    const T& operator[](size_t index) const {\n \
    \       return vals[index];\n    }\n    int size() {\n        return vals.size();\n\
    \    }\n};\n\ntemplate <std::ranges::range R>\nDiscretization(R&&) -> Discretization<std::ranges::range_value_t<R>>;\n\
    #line 6 \"test/1_library_checker/data_structure/static_range_mode_query.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    std::vector<int> arr(n);\n    for (auto\
    \ &i : arr)\n        std::cin >> i;\n    std::vector<std::pair<int, int>> querys(q);\n\
    \    for (auto &[l, r] : querys)\n        std::cin >> l >> r;\n    Discretization\
    \ val(arr);\n    for (auto &i : arr)\n        i = val.idx(i);\n    std::vector<int>\
    \ cnt(val.size()), cnt2(n + 1), pl(val.size());\n    std::vector<std::vector<int>>\
    \ pool(n + 1);\n    std::iota(pl.begin(), pl.end(), 0);\n    pool[0] = pl;\n \
    \   std::vector<std::pair<int, int>> ans(q);\n\n    auto pop = [&](int x) {\n\
    \        std::swap(pool[cnt[x]][pl[x]], pool[cnt[x]].back());\n        pl[pool[cnt[x]][pl[x]]]\
    \ = pl[x];\n        pool[cnt[x]].pop_back();\n    };\n\n    auto push = [&](int\
    \ x) {\n        pl[x] = pool[cnt[x]].size();\n        pool[cnt[x]].push_back(x);\n\
    \    };\n\n    int mx = 0;\n    cnt2[0] = val.size();\n    mo_solver(querys, [&](int\
    \ qid) {\n        ans[qid] = std::make_pair(val[pool[mx].back()], mx);\n    },\
    \ [&](int l) {\n        --cnt2[cnt[arr[l]]], pop(arr[l]); \n        if (cnt[arr[l]]\
    \ == mx) ++mx;\n        ++cnt2[++cnt[arr[l]]], push(arr[l]);\n    }, [&](int l)\
    \ {\n        --cnt2[cnt[arr[l]]], pop(arr[l]); \n        if (cnt2[mx] == 0) --mx;\n\
    \        ++cnt2[--cnt[arr[l]]], push(arr[l]);\n    });\n    for (auto [v, c] :\
    \ ans)\n        std::cout << v << \" \" << c << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_mode_query\"\
    \n#include \"assumption.hpp\"\n\n#include \"Sequence/mo_solver.hpp\"\n#include\
    \ \"DataStructure/Discretization.hpp\"\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<int>\
    \ arr(n);\n    for (auto &i : arr)\n        std::cin >> i;\n    std::vector<std::pair<int,\
    \ int>> querys(q);\n    for (auto &[l, r] : querys)\n        std::cin >> l >>\
    \ r;\n    Discretization val(arr);\n    for (auto &i : arr)\n        i = val.idx(i);\n\
    \    std::vector<int> cnt(val.size()), cnt2(n + 1), pl(val.size());\n    std::vector<std::vector<int>>\
    \ pool(n + 1);\n    std::iota(pl.begin(), pl.end(), 0);\n    pool[0] = pl;\n \
    \   std::vector<std::pair<int, int>> ans(q);\n\n    auto pop = [&](int x) {\n\
    \        std::swap(pool[cnt[x]][pl[x]], pool[cnt[x]].back());\n        pl[pool[cnt[x]][pl[x]]]\
    \ = pl[x];\n        pool[cnt[x]].pop_back();\n    };\n\n    auto push = [&](int\
    \ x) {\n        pl[x] = pool[cnt[x]].size();\n        pool[cnt[x]].push_back(x);\n\
    \    };\n\n    int mx = 0;\n    cnt2[0] = val.size();\n    mo_solver(querys, [&](int\
    \ qid) {\n        ans[qid] = std::make_pair(val[pool[mx].back()], mx);\n    },\
    \ [&](int l) {\n        --cnt2[cnt[arr[l]]], pop(arr[l]); \n        if (cnt[arr[l]]\
    \ == mx) ++mx;\n        ++cnt2[++cnt[arr[l]]], push(arr[l]);\n    }, [&](int l)\
    \ {\n        --cnt2[cnt[arr[l]]], pop(arr[l]); \n        if (cnt2[mx] == 0) --mx;\n\
    \        ++cnt2[--cnt[arr[l]]], push(arr[l]);\n    });\n    for (auto [v, c] :\
    \ ans)\n        std::cout << v << \" \" << c << \"\\n\";\n}\n"
  dependsOn:
  - assumption.hpp
  - Sequence/mo_solver.hpp
  - Algebra/NullFunc.hpp
  - DataStructure/Discretization.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/static_range_mode_query.test.cpp
  requiredBy: []
  timestamp: '2026-06-30 17:54:41+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/static_range_mode_query.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/static_range_mode_query.test.cpp
- /verify/test/1_library_checker/data_structure/static_range_mode_query.test.cpp.html
title: test/1_library_checker/data_structure/static_range_mode_query.test.cpp
---
