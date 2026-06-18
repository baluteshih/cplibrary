---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Convolution/and_convolution.hpp
    title: Convolution/and_convolution.hpp
  - icon: ':warning:'
    path: Convolution/or_convolution.hpp
    title: Convolution/or_convolution.hpp
  - icon: ':x:'
    path: Convolution/subset_convolution.hpp
    title: Convolution/subset_convolution.hpp
  - icon: ':heavy_check_mark:'
    path: Convolution/xor_convolution.hpp
    title: Convolution/xor_convolution.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/bitwise_and_convolution.test.cpp
    title: test/1_library_checker/convolution/bitwise_and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/bitwise_xor_convolution.test.cpp
    title: test/1_library_checker/convolution/bitwise_xor_convolution.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/set_power_series/subset_convolution.test.cpp
    title: test/1_library_checker/set_power_series/subset_convolution.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Convolution/bitwise_transform.hpp\"\n\nnamespace bitwise_transform\
    \ {\n    // popcount: res[j] = sum_i (-1)^{popcount(i & j)}arr[i], ignore type\n\
    \    enum target { subset, superset, popcount };\n    enum type { zeta, mobius\
    \ };\n    template<target tar, type tp = zeta, typename T = long long>\n    void\
    \ transform(std::vector<T> &arr) {\n        int n = arr.size();  \n        assert((n\
    \ & (n - 1)) == 0);\n        for (int L = 2; L <= n; L <<= 1)\n            for\
    \ (int i = 0; i < n; i += L)\n                for (int j = i; j < i + (L >> 1);\
    \ ++j) {\n                    if constexpr (tar == subset) {\n               \
    \         if constexpr (tp == zeta) arr[j + (L >> 1)] += arr[j];\n           \
    \             else arr[j + (L >> 1)] -= arr[j];\n                    }\n     \
    \               else if constexpr (tar == superset) {\n                      \
    \  if constexpr (tp == zeta) arr[j] += arr[j + (L >> 1)];\n                  \
    \      else arr[j] -= arr[j + (L >> 1)];\n                    }\n            \
    \        else std::tie(arr[j], arr[j + (L >> 1)]) = std::make_pair(arr[j] + arr[j\
    \ + (L >> 1)], arr[j] - arr[j + (L >> 1)]);\n                }\n    }\n    template<typename\
    \ T>\n    std::vector<std::vector<T>> ranked_zeta(const std::vector<T> &arr) {\n\
    \        int n = arr.size(), lg = std::__lg(n);\n        assert((n & (n - 1))\
    \ == 0);\n        std::vector<std::vector<T>> res(lg + 1, std::vector<T>(n));\n\
    \        for (int i = 0; i < n; ++i)\n            res[std::popcount(static_cast<unsigned\
    \ int>(i))][i] = arr[i];\n        for (int i = 0; i <= lg; ++i)\n            transform<subset,\
    \ zeta>(res[i]);\n        return res;\n    }\n    template<typename T>\n    std::vector<T>\
    \ ranked_mobius(std::vector<std::vector<T>> arr) {\n        int n = arr[0].size(),\
    \ lg = arr.size() - 1;\n        assert((n & (n - 1)) == 0);\n        std::vector<T>\
    \ res(n);\n        for (int i = 0; i <= lg; ++i)\n            transform<subset,\
    \ mobius>(arr[i]);\n        for (int i = 0; i < n; ++i)\n            res[i] =\
    \ arr[std::popcount(static_cast<unsigned int>(i))][i];\n        return res;\n\
    \    }\n}\n"
  code: "#pragma once\n\nnamespace bitwise_transform {\n    // popcount: res[j] =\
    \ sum_i (-1)^{popcount(i & j)}arr[i], ignore type\n    enum target { subset, superset,\
    \ popcount };\n    enum type { zeta, mobius };\n    template<target tar, type\
    \ tp = zeta, typename T = long long>\n    void transform(std::vector<T> &arr)\
    \ {\n        int n = arr.size();  \n        assert((n & (n - 1)) == 0);\n    \
    \    for (int L = 2; L <= n; L <<= 1)\n            for (int i = 0; i < n; i +=\
    \ L)\n                for (int j = i; j < i + (L >> 1); ++j) {\n             \
    \       if constexpr (tar == subset) {\n                        if constexpr (tp\
    \ == zeta) arr[j + (L >> 1)] += arr[j];\n                        else arr[j +\
    \ (L >> 1)] -= arr[j];\n                    }\n                    else if constexpr\
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
    \    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: Convolution/bitwise_transform.hpp
  requiredBy:
  - Convolution/xor_convolution.hpp
  - Convolution/or_convolution.hpp
  - Convolution/and_convolution.hpp
  - Convolution/subset_convolution.hpp
  timestamp: '2026-06-14 15:20:09+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/1_library_checker/set_power_series/subset_convolution.test.cpp
  - test/1_library_checker/convolution/bitwise_xor_convolution.test.cpp
  - test/1_library_checker/convolution/bitwise_and_convolution.test.cpp
documentation_of: Convolution/bitwise_transform.hpp
layout: document
redirect_from:
- /library/Convolution/bitwise_transform.hpp
- /library/Convolution/bitwise_transform.hpp.html
title: Convolution/bitwise_transform.hpp
---
