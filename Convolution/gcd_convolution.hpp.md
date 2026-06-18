---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Numeric/factor_transform.hpp
    title: Numeric/factor_transform.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/prime_work.hpp
    title: Numeric/prime_work.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/gcd_convolution.test.cpp
    title: test/1_library_checker/convolution/gcd_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Convolution/gcd_convolution.hpp\"\n\n#line 2 \"Numeric/factor_transform.hpp\"\
    \n\n#line 2 \"Numeric/prime_work.hpp\"\n\nnamespace prime_work {\n    int limit\
    \ = 2;\n    std::vector<int> min_factor({0, 0, 2}); // min_factor[i] := min prime\
    \ factor of i, min_factor[0] = min_factor[1] = 0\n    std::vector<int> list({2});\
    \ // prime list\n    void ensure_upper_bound(int n) {\n        if (limit < n)\
    \ {\n            limit = n;\n            std::vector<int>(n + 1, 0).swap(min_factor);\n\
    \            std::vector<int>().swap(list);\n            for (int i = 2; i <=\
    \ n; ++i) {\n                if (min_factor[i] == 0) {\n                    min_factor[i]\
    \ = i;\n                    list.push_back(i);\n                }\n          \
    \      for (int j : list) {\n                    if (i * j > n) break;\n     \
    \               min_factor[i * j] = j;\n                    if (i % j == 0) break;\n\
    \                }\n            }\n        }\n    }\n    std::vector<int> prime_list(int\
    \ n) {\n        ensure_upper_bound(n);\n        return std::vector<int>(list.begin(),\
    \ std::ranges::upper_bound(list, n));\n    }\n};\n#line 4 \"Numeric/factor_transform.hpp\"\
    \n\nnamespace factor_transform {\n    enum target { divisor, multiplier };\n \
    \   enum type { zeta, mobius };\n    template<target tar, type tp, typename T>\n\
    \    void transform(std::vector<T> &arr) {\n        int n = arr.size() - 1;\n\
    \        assert(arr[0] == T(0));\n        auto prime_list = prime_work::prime_list(n);\n\
    \        for (auto p : prime_list)\n            if constexpr (int(tar == divisor)\
    \ ^ int(tp == mobius))\n                for (int i = 1; i <= n / p; ++i)\n   \
    \                 if constexpr (tar == divisor) arr[p * i] += arr[i];\n      \
    \              else arr[i] -= arr[p * i];\n            else\n                for\
    \ (int i = n / p; i >= 1; --i)\n                    if constexpr (tar == divisor)\
    \ arr[p * i] -= arr[i];\n                    else arr[i] += arr[p * i];\n    }\n\
    }\n#line 4 \"Convolution/gcd_convolution.hpp\"\n\ntemplate<typename T>\nstd::vector<T>\
    \ gcd_convolution(std::vector<T> a, std::vector<T> b) {\n    assert(a.size() ==\
    \ b.size());\n    if (a == b)\n        factor_transform::transform<factor_transform::multiplier,\
    \ factor_transform::zeta>(a), b = a; \n    else {\n        factor_transform::transform<factor_transform::multiplier,\
    \ factor_transform::zeta>(a);  \n        factor_transform::transform<factor_transform::multiplier,\
    \ factor_transform::zeta>(b);\n    }\n    int n = a.size();\n    for (int i =\
    \ 0; i < n; ++i) a[i] *= b[i];\n    factor_transform::transform<factor_transform::multiplier,\
    \ factor_transform::mobius>(a);\n    return a;\n}\n"
  code: "#pragma once\n\n#include \"Numeric/factor_transform.hpp\"\n\ntemplate<typename\
    \ T>\nstd::vector<T> gcd_convolution(std::vector<T> a, std::vector<T> b) {\n \
    \   assert(a.size() == b.size());\n    if (a == b)\n        factor_transform::transform<factor_transform::multiplier,\
    \ factor_transform::zeta>(a), b = a; \n    else {\n        factor_transform::transform<factor_transform::multiplier,\
    \ factor_transform::zeta>(a);  \n        factor_transform::transform<factor_transform::multiplier,\
    \ factor_transform::zeta>(b);\n    }\n    int n = a.size();\n    for (int i =\
    \ 0; i < n; ++i) a[i] *= b[i];\n    factor_transform::transform<factor_transform::multiplier,\
    \ factor_transform::mobius>(a);\n    return a;\n}\n"
  dependsOn:
  - Numeric/factor_transform.hpp
  - Numeric/prime_work.hpp
  isVerificationFile: false
  path: Convolution/gcd_convolution.hpp
  requiredBy: []
  timestamp: '2026-06-18 21:28:00+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/convolution/gcd_convolution.test.cpp
documentation_of: Convolution/gcd_convolution.hpp
layout: document
redirect_from:
- /library/Convolution/gcd_convolution.hpp
- /library/Convolution/gcd_convolution.hpp.html
title: Convolution/gcd_convolution.hpp
---
