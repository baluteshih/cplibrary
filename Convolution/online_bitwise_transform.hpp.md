---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Convolution/bitwise_transform.hpp
    title: Convolution/bitwise_transform.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Convolution/online_bitwise_transform.hpp\"\n\n#line 2 \"\
    Convolution/bitwise_transform.hpp\"\n\nnamespace bitwise_transform {\n    // popcount:\
    \ res[j] = sum_i (-1)^{popcount(i & j)}arr[i], ignore type\n    enum target {\
    \ subset, superset, popcount };\n    enum type { zeta, mobius };\n    template<target\
    \ tar, type tp = zeta, typename T = long long>\n    void transform(std::vector<T>\
    \ &arr) {\n        int n = arr.size();  \n        assert((n & (n - 1)) == 0);\n\
    \        for (int L = 2; L <= n; L <<= 1)\n            for (int i = 0; i < n;\
    \ i += L)\n                for (int j = i; j < i + (L >> 1); ++j) {\n        \
    \            if constexpr (tar == subset) {\n                        if constexpr\
    \ (tp == zeta) arr[j + (L >> 1)] += arr[j];\n                        else arr[j\
    \ + (L >> 1)] -= arr[j];\n                    }\n                    else if constexpr\
    \ (tar == superset) {\n                        if constexpr (tp == zeta) arr[j]\
    \ += arr[j + (L >> 1)];\n                        else arr[j] -= arr[j + (L >>\
    \ 1)];\n                    }\n                    else std::tie(arr[j], arr[j\
    \ + (L >> 1)]) = std::make_pair(arr[j] + arr[j + (L >> 1)], arr[j] - arr[j + (L\
    \ >> 1)]);\n                }\n    }\n    template<typename T>\n    std::vector<std::vector<T>>\
    \ ranked_zeta(const std::vector<T> &arr) {\n        int n = arr.size(), lg = std::__lg(n);\n\
    \        assert((n & (n - 1)) == 0);\n        std::vector<std::vector<T>> res(lg\
    \ + 1, std::vector<T>(n));\n        for (int i = 0; i < n; ++i)\n            res[std::popcount(static_cast<unsigned\
    \ int>(i))][i] = arr[i];\n        for (int i = 0; i <= lg; ++i)\n            transform<subset,\
    \ zeta>(res[i]);\n        return res;\n    }\n    template<typename T>\n    std::vector<T>\
    \ ranked_mobius(std::vector<std::vector<T>> arr) {\n        int n = arr[0].size(),\
    \ lg = arr.size() - 1;\n        assert((n & (n - 1)) == 0);\n        std::vector<T>\
    \ res(n);\n        for (int i = 0; i <= lg; ++i)\n            transform<subset,\
    \ mobius>(arr[i]);\n        for (int i = 0; i < n; ++i)\n            res[i] =\
    \ arr[std::popcount(static_cast<unsigned int>(i))][i];\n        return res;\n\
    \    }\n}\n#line 4 \"Convolution/online_bitwise_transform.hpp\"\n\nnamespace bitwise_transform\
    \ {\n    // Online Bitwise Transform (subset: i = 0 -> 2^lg - 1, superset: i =\
    \ 2^lg - 1 -> 0)\n    template<target tar = subset, type tp = zeta, typename T\
    \ = long long>\n    struct online_transform {\n        static_assert(tar != popcount,\
    \ \"Online transform does not support popcount (FWT).\");\n        int lg, n,\
    \ p;\n        std::vector<T> arr;\n\n        online_transform(int lg_) : lg(lg_),\
    \ n(1 << lg_), p(tar == subset ? 0 : n - 1), arr(n, T{}) {}\n\n        // assume\
    \ a[i] = ai, return transform(a)[i]. does not advance pointer p.\n        T assume(int\
    \ i, T ai = T{}) const {\n            assert(p == i);\n            T sum{};\n\
    \            if constexpr (tar == subset)\n                for (unsigned int m\
    \ = i; m > 0; m &= m - 1)\n                    sum += arr[i ^ (m & -m)];\n   \
    \         else\n                for (unsigned int m = (n - 1) ^ i; m > 0; m &=\
    \ m - 1)\n                    sum += arr[i ^ (m & -m)];\n            if constexpr\
    \ (tp == zeta) return ai + sum;\n            else return ai - sum;\n        }\n\
    \n        // set a[i] = ai, advance pointer p, and return transform(a)[i].\n \
    \       T set(int i, T ai) {\n            assert(p == i);\n            T res =\
    \ assume(i, ai);\n            if constexpr (tar == subset) {\n               \
    \ arr[p++] = (tp == zeta ? ai : res);\n                for (int len = 1; (i &\
    \ len) != 0; len <<= 1)\n                    for (int j = p - len; j < p; ++j)\n\
    \                        arr[j] += arr[j - len];\n            } else {\n     \
    \           arr[p--] = (tp == zeta ? ai : res);\n                for (int len\
    \ = 1; (~i & len) != 0 && (p + 1 + (len << 1) <= n); len <<= 1)\n            \
    \        for (int j = p + 1; j < p + 1 + len; ++j)\n                        arr[j]\
    \ += arr[j + len];\n            }\n            return res;\n        }\n    };\n\
    }\n"
  code: "#pragma once\n\n#include \"Convolution/bitwise_transform.hpp\"\n\nnamespace\
    \ bitwise_transform {\n    // Online Bitwise Transform (subset: i = 0 -> 2^lg\
    \ - 1, superset: i = 2^lg - 1 -> 0)\n    template<target tar = subset, type tp\
    \ = zeta, typename T = long long>\n    struct online_transform {\n        static_assert(tar\
    \ != popcount, \"Online transform does not support popcount (FWT).\");\n     \
    \   int lg, n, p;\n        std::vector<T> arr;\n\n        online_transform(int\
    \ lg_) : lg(lg_), n(1 << lg_), p(tar == subset ? 0 : n - 1), arr(n, T{}) {}\n\n\
    \        // assume a[i] = ai, return transform(a)[i]. does not advance pointer\
    \ p.\n        T assume(int i, T ai = T{}) const {\n            assert(p == i);\n\
    \            T sum{};\n            if constexpr (tar == subset)\n            \
    \    for (unsigned int m = i; m > 0; m &= m - 1)\n                    sum += arr[i\
    \ ^ (m & -m)];\n            else\n                for (unsigned int m = (n - 1)\
    \ ^ i; m > 0; m &= m - 1)\n                    sum += arr[i ^ (m & -m)];\n   \
    \         if constexpr (tp == zeta) return ai + sum;\n            else return\
    \ ai - sum;\n        }\n\n        // set a[i] = ai, advance pointer p, and return\
    \ transform(a)[i].\n        T set(int i, T ai) {\n            assert(p == i);\n\
    \            T res = assume(i, ai);\n            if constexpr (tar == subset)\
    \ {\n                arr[p++] = (tp == zeta ? ai : res);\n                for\
    \ (int len = 1; (i & len) != 0; len <<= 1)\n                    for (int j = p\
    \ - len; j < p; ++j)\n                        arr[j] += arr[j - len];\n      \
    \      } else {\n                arr[p--] = (tp == zeta ? ai : res);\n       \
    \         for (int len = 1; (~i & len) != 0 && (p + 1 + (len << 1) <= n); len\
    \ <<= 1)\n                    for (int j = p + 1; j < p + 1 + len; ++j)\n    \
    \                    arr[j] += arr[j + len];\n            }\n            return\
    \ res;\n        }\n    };\n}\n"
  dependsOn:
  - Convolution/bitwise_transform.hpp
  isVerificationFile: false
  path: Convolution/online_bitwise_transform.hpp
  requiredBy: []
  timestamp: '2026-11-02 10:23:37+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Convolution/online_bitwise_transform.hpp
layout: document
redirect_from:
- /library/Convolution/online_bitwise_transform.hpp
- /library/Convolution/online_bitwise_transform.hpp.html
title: Convolution/online_bitwise_transform.hpp
---
