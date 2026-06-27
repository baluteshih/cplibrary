---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: Enumerate/subset_enumerate.hpp
    title: Enumerate/subset_enumerate.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Sequence/count_subset_sum.hpp\"\n\n#line 2 \"Enumerate/subset_enumerate.hpp\"\
    \n\ntemplate<typename T>\nstd::vector<T> subset_enumerate(const std::vector<T>\
    \ &arr) {\n    std::vector<T> res;\n    T cur = T();\n    auto dfs = [&](auto\
    \ self, int u) -> void {\n        if (u == int(arr.size())) return res.push_back(cur);\n\
    \        T tmp = cur;\n        cur = cur + arr[u];\n        self(self, u + 1);\n\
    \        cur = tmp;\n        self(self, u + 1);\n    };\n    dfs(dfs, 0);\n  \
    \  return res;\n}\n#line 4 \"Sequence/count_subset_sum.hpp\"\n\n// [lft, rgt)\n\
    template<typename T>\nlong long count_subset_sum(const std::vector<T> &arr, T\
    \ lft, T rgt) {\n    int n = arr.size();\n    if (n == 0) return lft <= 0 && 0\
    \ < rgt;\n    if (n == 1) return (lft <= 0 && 0 < rgt) + (lft <= arr[0] && arr[0]\
    \ < rgt);\n    auto lset = subset_enumerate(std::vector<T>(arr.begin(), arr.begin()\
    \ + n / 2));\n    auto rset = subset_enumerate(std::vector<T>(arr.begin() + n\
    \ / 2, arr.end()));\n    std::ranges::sort(lset, std::greater<T>()), std::ranges::sort(rset);\n\
    \    auto count = [&](T gap) -> long long {\n        long long res = 0;\n    \
    \    for (int i = 0; auto &v : lset) {\n            while (i < int(rset.size())\
    \ && v + rset[i] < gap) ++i;\n            res += i;\n        }\n        return\
    \ res;\n    };\n    long long res = 0;\n    if (lset[0] + rset.back() >= rgt)\
    \ res += count(rgt);\n    else res += (long long)lset.size() * (long long)rset.size();\n\
    \    if (lset.back() + rset[0] < lft) res -= count(lft);\n    return res;\n}\n\
    \n// [lft, rgt)\ntemplate<typename T>\nstd::vector<long long> count_subset_sum_with_count(const\
    \ std::vector<T> &arr, T lft, T rgt) {\n    int n = arr.size();\n    if (n ==\
    \ 0) return {lft <= 0 && 0 < rgt};\n    if (n == 1) return {(lft <= 0 && 0 < rgt),\
    \ (lft <= arr[0] && arr[0] < rgt)};\n    struct Val {\n        T v;\n        int\
    \ cnt;\n        Val(T _v, int _cnt = 1) : v(_v), cnt(_cnt) {}\n        Val() :\
    \ Val(0, 0) {} \n        Val operator+(const Val &rhs) const { return Val(v +\
    \ rhs.v, cnt + rhs.cnt); }\n        auto operator<=>(const Val&) const = default;\n\
    \    };\n    auto lset = subset_enumerate(std::vector<Val>(arr.begin(), arr.begin()\
    \ + n / 2));\n    auto rset = subset_enumerate(std::vector<Val>(arr.begin() +\
    \ n / 2, arr.end()));\n    std::ranges::sort(lset, std::greater<Val>()), std::ranges::sort(rset);\n\
    \    auto count = [&](T gap) -> std::vector<long long> {\n        std::vector<long\
    \ long> res(n + 1), cur(n + 1);\n        for (int i = 0; auto &v : lset) {\n \
    \           while (i < int(rset.size()) && v.v + rset[i].v < gap) ++cur[rset[i++].cnt];\n\
    \            for (int j = 0; j <= n; ++j) res[v.cnt + j] += cur[j];\n        }\n\
    \        return res;\n    };\n    std::vector<long long> res(n + 1);\n    if (lset[0]\
    \ + rset.back() >= rgt) res = count(rgt); \n    else {\n        std::vector<long\
    \ long> lcnt(n + 1), rcnt(n + 1);\n        for (auto &v : lset) ++lcnt[v.cnt];\n\
    \        for (auto &v : rset) ++rcnt[v.cnt];\n        for (int i = 0; i <= n;\
    \ ++i)\n            for (int j = 0; j <= n; ++j)\n                res[i + j] +=\
    \ lcnt[i] * rcnt[j];\n    }\n    if (lset.back() + rset[0] < lft) {\n        auto\
    \ minus = count(lft);\n        for (int i = 0; i <= n; ++i) res[i] -= minus[i];\n\
    \    }\n    return res;\n}\n"
  code: "#pragma once\n\n#include \"Enumerate/subset_enumerate.hpp\"\n\n// [lft, rgt)\n\
    template<typename T>\nlong long count_subset_sum(const std::vector<T> &arr, T\
    \ lft, T rgt) {\n    int n = arr.size();\n    if (n == 0) return lft <= 0 && 0\
    \ < rgt;\n    if (n == 1) return (lft <= 0 && 0 < rgt) + (lft <= arr[0] && arr[0]\
    \ < rgt);\n    auto lset = subset_enumerate(std::vector<T>(arr.begin(), arr.begin()\
    \ + n / 2));\n    auto rset = subset_enumerate(std::vector<T>(arr.begin() + n\
    \ / 2, arr.end()));\n    std::ranges::sort(lset, std::greater<T>()), std::ranges::sort(rset);\n\
    \    auto count = [&](T gap) -> long long {\n        long long res = 0;\n    \
    \    for (int i = 0; auto &v : lset) {\n            while (i < int(rset.size())\
    \ && v + rset[i] < gap) ++i;\n            res += i;\n        }\n        return\
    \ res;\n    };\n    long long res = 0;\n    if (lset[0] + rset.back() >= rgt)\
    \ res += count(rgt);\n    else res += (long long)lset.size() * (long long)rset.size();\n\
    \    if (lset.back() + rset[0] < lft) res -= count(lft);\n    return res;\n}\n\
    \n// [lft, rgt)\ntemplate<typename T>\nstd::vector<long long> count_subset_sum_with_count(const\
    \ std::vector<T> &arr, T lft, T rgt) {\n    int n = arr.size();\n    if (n ==\
    \ 0) return {lft <= 0 && 0 < rgt};\n    if (n == 1) return {(lft <= 0 && 0 < rgt),\
    \ (lft <= arr[0] && arr[0] < rgt)};\n    struct Val {\n        T v;\n        int\
    \ cnt;\n        Val(T _v, int _cnt = 1) : v(_v), cnt(_cnt) {}\n        Val() :\
    \ Val(0, 0) {} \n        Val operator+(const Val &rhs) const { return Val(v +\
    \ rhs.v, cnt + rhs.cnt); }\n        auto operator<=>(const Val&) const = default;\n\
    \    };\n    auto lset = subset_enumerate(std::vector<Val>(arr.begin(), arr.begin()\
    \ + n / 2));\n    auto rset = subset_enumerate(std::vector<Val>(arr.begin() +\
    \ n / 2, arr.end()));\n    std::ranges::sort(lset, std::greater<Val>()), std::ranges::sort(rset);\n\
    \    auto count = [&](T gap) -> std::vector<long long> {\n        std::vector<long\
    \ long> res(n + 1), cur(n + 1);\n        for (int i = 0; auto &v : lset) {\n \
    \           while (i < int(rset.size()) && v.v + rset[i].v < gap) ++cur[rset[i++].cnt];\n\
    \            for (int j = 0; j <= n; ++j) res[v.cnt + j] += cur[j];\n        }\n\
    \        return res;\n    };\n    std::vector<long long> res(n + 1);\n    if (lset[0]\
    \ + rset.back() >= rgt) res = count(rgt); \n    else {\n        std::vector<long\
    \ long> lcnt(n + 1), rcnt(n + 1);\n        for (auto &v : lset) ++lcnt[v.cnt];\n\
    \        for (auto &v : rset) ++rcnt[v.cnt];\n        for (int i = 0; i <= n;\
    \ ++i)\n            for (int j = 0; j <= n; ++j)\n                res[i + j] +=\
    \ lcnt[i] * rcnt[j];\n    }\n    if (lset.back() + rset[0] < lft) {\n        auto\
    \ minus = count(lft);\n        for (int i = 0; i <= n; ++i) res[i] -= minus[i];\n\
    \    }\n    return res;\n}\n"
  dependsOn:
  - Enumerate/subset_enumerate.hpp
  isVerificationFile: false
  path: Sequence/count_subset_sum.hpp
  requiredBy: []
  timestamp: '2026-06-28 02:52:11+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Sequence/count_subset_sum.hpp
layout: document
redirect_from:
- /library/Sequence/count_subset_sum.hpp
- /library/Sequence/count_subset_sum.hpp.html
title: Sequence/count_subset_sum.hpp
---
