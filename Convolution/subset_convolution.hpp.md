---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Convolution/bitwise_transform.hpp
    title: Convolution/bitwise_transform.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/1_library_checker/set_power_series/subset_convolution.test.cpp
    title: test/1_library_checker/set_power_series/subset_convolution.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Convolution/subset_convolution.hpp\"\n\n#line 2 \"Convolution/bitwise_transform.hpp\"\
    \n\nnamespace bitwise_transform {\n    // popcount: res[j] = sum_i (-1)^{popcount(i\
    \ & j)}arr[i], ignore type\n    enum target { subset, superset, popcount };\n\
    \    enum type { zeta, mobius };\n    template<target tar, type tp = zeta, typename\
    \ T = long long>\n    void transform(std::vector<T> &arr) {\n        int n = arr.size();\
    \  \n        assert((n & (n - 1)) == 0);\n        for (int L = 2; L <= n; L <<=\
    \ 1)\n            for (int i = 0; i < n; i += L)\n                for (int j =\
    \ i; j < i + (L >> 1); ++j) {\n                    if constexpr (tar == subset)\
    \ {\n                        if constexpr (tp == zeta) arr[j + (L >> 1)] += arr[j];\n\
    \                        else arr[j + (L >> 1)] -= arr[j];\n                 \
    \   }\n                    else if constexpr (tar == superset) {\n           \
    \             if constexpr (tp == zeta) arr[j] += arr[j + (L >> 1)];\n       \
    \                 else arr[j] -= arr[j + (L >> 1)];\n                    }\n \
    \                   else std::tie(arr[j], arr[j + (L >> 1)]) = std::make_pair(arr[j]\
    \ + arr[j + (L >> 1)], arr[j] - arr[j + (L >> 1)]);\n                }\n    }\n\
    \    template<typename T>\n    std::vector<std::vector<T>> ranked_zeta(const std::vector<T>\
    \ &arr) {\n        int n = arr.size(), lg = std::__lg(n);\n        assert((n &\
    \ (n - 1)) == 0);\n        std::vector<std::vector<T>> res(lg + 1, std::vector<T>(n));\n\
    \        for (int i = 0; i < n; ++i)\n            res[std::popcount(static_cast<unsigned\
    \ int>(i))][i] = arr[i];\n        for (int i = 0; i <= lg; ++i)\n            transform<subset,\
    \ zeta>(res[i]);\n        return res;\n    }\n    template<typename T>\n    std::vector<T>\
    \ ranked_mobius(std::vector<std::vector<T>> arr) {\n        int n = arr[0].size(),\
    \ lg = arr.size() - 1;\n        assert((n & (n - 1)) == 0);\n        std::vector<T>\
    \ res(n);\n        for (int i = 0; i <= lg; ++i)\n            transform<subset,\
    \ mobius>(arr[i]);\n        for (int i = 0; i < n; ++i)\n            res[i] =\
    \ arr[std::popcount(static_cast<unsigned int>(i))][i];\n        return res;\n\
    \    }\n}\n#line 4 \"Convolution/subset_convolution.hpp\"\n\ntemplate<typename\
    \ T>\nstd::vector<T> subset_convolution(std::vector<T> a, std::vector<T> b) {\n\
    \    assert(a.size() == b.size());\n    auto ra = bitwise_transform::ranked_zeta(a);\n\
    \    auto rb = a == b ? ra : bitwise_transform::ranked_zeta(b);\n    int n = a.size(),\
    \ lg = std::__lg(n);\n    std::vector<std::vector<T>> store(lg + 1, std::vector<T>(n));\n\
    \    for (int i = 0; i <= lg; ++i)\n        for (int j = 0; j <= i; ++j)\n   \
    \         for (int x = 0; x < n; ++x)\n                store[i][x] += ra[j][x]\
    \ * rb[i - j][x]; \n    return bitwise_transform::ranked_mobius(store);\n}\n"
  code: "#pragma once\n\n#include \"Convolution/bitwise_transform.hpp\"\n\ntemplate<typename\
    \ T>\nstd::vector<T> subset_convolution(std::vector<T> a, std::vector<T> b) {\n\
    \    assert(a.size() == b.size());\n    auto ra = bitwise_transform::ranked_zeta(a);\n\
    \    auto rb = a == b ? ra : bitwise_transform::ranked_zeta(b);\n    int n = a.size(),\
    \ lg = std::__lg(n);\n    std::vector<std::vector<T>> store(lg + 1, std::vector<T>(n));\n\
    \    for (int i = 0; i <= lg; ++i)\n        for (int j = 0; j <= i; ++j)\n   \
    \         for (int x = 0; x < n; ++x)\n                store[i][x] += ra[j][x]\
    \ * rb[i - j][x]; \n    return bitwise_transform::ranked_mobius(store);\n}\n"
  dependsOn:
  - Convolution/bitwise_transform.hpp
  isVerificationFile: false
  path: Convolution/subset_convolution.hpp
  requiredBy: []
  timestamp: '2026-06-14 15:20:09+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/1_library_checker/set_power_series/subset_convolution.test.cpp
documentation_of: Convolution/subset_convolution.hpp
layout: document
redirect_from:
- /library/Convolution/subset_convolution.hpp
- /library/Convolution/subset_convolution.hpp.html
title: Convolution/subset_convolution.hpp
---
