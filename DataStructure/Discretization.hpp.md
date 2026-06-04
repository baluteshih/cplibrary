---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: DataStructure/OrderedSet.hpp
    title: DataStructure/OrderedSet.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set.test.cpp
    title: test/1_library_checker/data_structure/ordered_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/Discretization.hpp\"\n\ntemplate<typename\
    \ T>\nclass Discretization {\n    std::vector<T> vals;\n    static std::vector<T>\
    \ sort_and_unique(std::vector<T> _vals) {\n        std::ranges::sort(_vals);\n\
    \        _vals.erase(std::ranges::unique(_vals).begin(), _vals.end());\n     \
    \   return _vals;\n    }\npublic:\n    int idx(int x) {\n        auto it = ranges::lower_bound(vals,\
    \ x);\n        if (it == vals.end() || *it != x) return -1;\n        return it\
    \ - vals.begin();\n    }\n    int safe_idx(int x) {\n        int res = idx(x);\n\
    \        assert(res != -1);\n        return res;\n    }\n    Discretization(const\
    \ std::vector<T> &_vals): vals(sort_and_unique(_vals)) {}\n    int left_close(T\
    \ x) {\n        return std::ranges::lower_bound(vals, x) - vals.begin();\n   \
    \ }\n    int left_open(T x) {\n        return std::ranges::upper_bound(vals, x)\
    \ - vals.begin() - 1;\n    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(vals,\
    \ x) - vals.begin();\n    }\n    const T& operator[](size_t index) const {\n \
    \       return vals[index];\n    } \n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nclass Discretization {\n    std::vector<T>\
    \ vals;\n    static std::vector<T> sort_and_unique(std::vector<T> _vals) {\n \
    \       std::ranges::sort(_vals);\n        _vals.erase(std::ranges::unique(_vals).begin(),\
    \ _vals.end());\n        return _vals;\n    }\npublic:\n    int idx(int x) {\n\
    \        auto it = ranges::lower_bound(vals, x);\n        if (it == vals.end()\
    \ || *it != x) return -1;\n        return it - vals.begin();\n    }\n    int safe_idx(int\
    \ x) {\n        int res = idx(x);\n        assert(res != -1);\n        return\
    \ res;\n    }\n    Discretization(const std::vector<T> &_vals): vals(sort_and_unique(_vals))\
    \ {}\n    int left_close(T x) {\n        return std::ranges::lower_bound(vals,\
    \ x) - vals.begin();\n    }\n    int left_open(T x) {\n        return std::ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(vals,\
    \ x) - vals.begin();\n    }\n    const T& operator[](size_t index) const {\n \
    \       return vals[index];\n    } \n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/Discretization.hpp
  requiredBy:
  - DataStructure/OrderedSet.hpp
  timestamp: '2026-06-04 15:34:47+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/ordered_set.test.cpp
documentation_of: DataStructure/Discretization.hpp
layout: document
redirect_from:
- /library/DataStructure/Discretization.hpp
- /library/DataStructure/Discretization.hpp.html
title: DataStructure/Discretization.hpp
---
