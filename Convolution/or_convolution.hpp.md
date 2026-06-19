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
  bundledCode: "#line 2 \"Convolution/or_convolution.hpp\"\n\n#line 2 \"Convolution/bitwise_transform.hpp\"\
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
    \    }\n}\n#line 4 \"Convolution/or_convolution.hpp\"\n\ntemplate<typename T>\n\
    std::vector<T> or_convolution(std::vector<T> a, std::vector<T> b) {\n    assert(a.size()\
    \ == b.size());\n    if (a == b)\n        bitwise_transform::transform<bitwise_transform::subset,\
    \ bitwise_transform::zeta>(a), b = a; \n    else {\n        bitwise_transform::transform<bitwise_transform::subset,\
    \ bitwise_transform::zeta>(a);  \n        bitwise_transform::transform<bitwise_transform::subset,\
    \ bitwise_transform::zeta>(b);\n    }\n    int n = a.size();\n    for (int i =\
    \ 0; i < n; ++i) a[i] *= b[i];\n    bitwise_transform::transform<bitwise_transform::subset,\
    \ bitwise_transform::mobius>(a);\n    return a;\n}\n"
  code: "#pragma once\n\n#include \"Convolution/bitwise_transform.hpp\"\n\ntemplate<typename\
    \ T>\nstd::vector<T> or_convolution(std::vector<T> a, std::vector<T> b) {\n  \
    \  assert(a.size() == b.size());\n    if (a == b)\n        bitwise_transform::transform<bitwise_transform::subset,\
    \ bitwise_transform::zeta>(a), b = a; \n    else {\n        bitwise_transform::transform<bitwise_transform::subset,\
    \ bitwise_transform::zeta>(a);  \n        bitwise_transform::transform<bitwise_transform::subset,\
    \ bitwise_transform::zeta>(b);\n    }\n    int n = a.size();\n    for (int i =\
    \ 0; i < n; ++i) a[i] *= b[i];\n    bitwise_transform::transform<bitwise_transform::subset,\
    \ bitwise_transform::mobius>(a);\n    return a;\n}\n"
  dependsOn:
  - Convolution/bitwise_transform.hpp
  isVerificationFile: false
  path: Convolution/or_convolution.hpp
  requiredBy: []
  timestamp: '2026-06-14 22:25:05+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Convolution/or_convolution.hpp
layout: document
redirect_from:
- /library/Convolution/or_convolution.hpp
- /library/Convolution/or_convolution.hpp.html
title: Convolution/or_convolution.hpp
---
