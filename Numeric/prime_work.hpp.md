---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Convolution/gcd_convolution.hpp
    title: Convolution/gcd_convolution.hpp
  - icon: ':heavy_check_mark:'
    path: Convolution/lcm_convolution.hpp
    title: Convolution/lcm_convolution.hpp
  - icon: ':heavy_check_mark:'
    path: Numeric/factor_transform.hpp
    title: Numeric/factor_transform.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/gcd_convolution.test.cpp
    title: test/1_library_checker/convolution/gcd_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/convolution/lcm_convolution.test.cpp
    title: test/1_library_checker/convolution/lcm_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Numeric/prime_work.hpp\"\n\nnamespace prime_work {\n   \
    \ int limit = 2;\n    std::vector<int> min_factor({0, 0, 2}); // min_factor[i]\
    \ := min prime factor of i, min_factor[0] = min_factor[1] = 0\n    std::vector<int>\
    \ list({2}); // prime list\n    void ensure_upper_bound(int n) {\n        if (limit\
    \ < n) {\n            limit = n;\n            std::vector<int>(n + 1, 0).swap(min_factor);\n\
    \            std::vector<int>().swap(list);\n            for (int i = 2; i <=\
    \ n; ++i) {\n                if (min_factor[i] == 0) {\n                    min_factor[i]\
    \ = i;\n                    list.push_back(i);\n                }\n          \
    \      for (int j : list) {\n                    if (i * j > n) break;\n     \
    \               min_factor[i * j] = j;\n                    if (i % j == 0) break;\n\
    \                }\n            }\n        }\n    }\n    std::vector<int> prime_list(int\
    \ n) {\n        ensure_upper_bound(n);\n        return std::vector<int>(list.begin(),\
    \ std::ranges::upper_bound(list, n));\n    }\n};\n"
  code: "#pragma once\n\nnamespace prime_work {\n    int limit = 2;\n    std::vector<int>\
    \ min_factor({0, 0, 2}); // min_factor[i] := min prime factor of i, min_factor[0]\
    \ = min_factor[1] = 0\n    std::vector<int> list({2}); // prime list\n    void\
    \ ensure_upper_bound(int n) {\n        if (limit < n) {\n            limit = n;\n\
    \            std::vector<int>(n + 1, 0).swap(min_factor);\n            std::vector<int>().swap(list);\n\
    \            for (int i = 2; i <= n; ++i) {\n                if (min_factor[i]\
    \ == 0) {\n                    min_factor[i] = i;\n                    list.push_back(i);\n\
    \                }\n                for (int j : list) {\n                   \
    \ if (i * j > n) break;\n                    min_factor[i * j] = j;\n        \
    \            if (i % j == 0) break;\n                }\n            }\n      \
    \  }\n    }\n    std::vector<int> prime_list(int n) {\n        ensure_upper_bound(n);\n\
    \        return std::vector<int>(list.begin(), std::ranges::upper_bound(list,\
    \ n));\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Numeric/prime_work.hpp
  requiredBy:
  - Numeric/factor_transform.hpp
  - Convolution/lcm_convolution.hpp
  - Convolution/gcd_convolution.hpp
  timestamp: '2026-06-18 21:28:00+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/convolution/gcd_convolution.test.cpp
  - test/1_library_checker/convolution/lcm_convolution.test.cpp
documentation_of: Numeric/prime_work.hpp
layout: document
redirect_from:
- /library/Numeric/prime_work.hpp
- /library/Numeric/prime_work.hpp.html
title: Numeric/prime_work.hpp
---
