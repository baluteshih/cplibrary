---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: DataStructure/OrderedSet.hpp
    title: DataStructure/OrderedSet.hpp
  - icon: ':heavy_check_mark:'
    path: Geometry/PointInAngle.hpp
    title: Geometry/PointInAngle.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set.test.cpp
    title: test/1_library_checker/data_structure/ordered_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/geometry/count_points_in_triangle.test.cpp
    title: test/1_library_checker/geometry/count_points_in_triangle.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/BIT.hpp\"\n\ntemplate<class T>\nclass BIT\
    \ { // 0-base\n    int n;\n    T total_;\n    vector<T> bit;\npublic:\n    BIT(int\
    \ _n): n(_n), total_(), bit(n + 1) {}\n    void initialize(const std::vector<T>\
    \ &arr) {\n        for (int x = 1; x <= n; ++x) {\n            bit[x] = arr[x\
    \ - 1];\n            int y = x - (x & -x);\n            for (int i = x - 1; i\
    \ > y; i -= i & -i)\n                bit[x] = bit[x] + bit[i];\n        }\n  \
    \  }\n    void modify(int x, T v) {\n        total_ += v;\n        for (++x; x\
    \ <= n; x += x & -x)\n            bit[x] = bit[x] + v;\n    }\n    T prefix(int\
    \ x) {\n        T res = T();\n        for (++x; x; x -= x & -x)\n            res\
    \ = res + bit[x];\n        return res;\n    }\n    T suffix(int x) requires requires(T\
    \ x, T y) { x - y; } {\n        return total_ - prefix(x);\n    }\n    T range(int\
    \ l, int r) requires requires(T x, T y) { x - y; } { // [l, r)\n        if (l\
    \ >= r) return T();\n        T res = prefix(r - 1) - prefix(l - 1);\n        return\
    \ res;\n    }\n    int kth(int k) { // 0-base query\n        assert((n & (n -\
    \ 1)) == 0);\n        ++k;\n        int res = 0;\n        for (int i = n >> 1;\
    \ i >= 1; i >>= 1) {\n            if (bit[res + i] < k)\n                k -=\
    \ bit[res += i];\n        }\n        return res;\n    }\n    T total() {\n   \
    \     return total_;\n    }\n};\n"
  code: "#pragma once\n\ntemplate<class T>\nclass BIT { // 0-base\n    int n;\n  \
    \  T total_;\n    vector<T> bit;\npublic:\n    BIT(int _n): n(_n), total_(), bit(n\
    \ + 1) {}\n    void initialize(const std::vector<T> &arr) {\n        for (int\
    \ x = 1; x <= n; ++x) {\n            bit[x] = arr[x - 1];\n            int y =\
    \ x - (x & -x);\n            for (int i = x - 1; i > y; i -= i & -i)\n       \
    \         bit[x] = bit[x] + bit[i];\n        }\n    }\n    void modify(int x,\
    \ T v) {\n        total_ += v;\n        for (++x; x <= n; x += x & -x)\n     \
    \       bit[x] = bit[x] + v;\n    }\n    T prefix(int x) {\n        T res = T();\n\
    \        for (++x; x; x -= x & -x)\n            res = res + bit[x];\n        return\
    \ res;\n    }\n    T suffix(int x) requires requires(T x, T y) { x - y; } {\n\
    \        return total_ - prefix(x);\n    }\n    T range(int l, int r) requires\
    \ requires(T x, T y) { x - y; } { // [l, r)\n        if (l >= r) return T();\n\
    \        T res = prefix(r - 1) - prefix(l - 1);\n        return res;\n    }\n\
    \    int kth(int k) { // 0-base query\n        assert((n & (n - 1)) == 0);\n \
    \       ++k;\n        int res = 0;\n        for (int i = n >> 1; i >= 1; i >>=\
    \ 1) {\n            if (bit[res + i] < k)\n                k -= bit[res += i];\n\
    \        }\n        return res;\n    }\n    T total() {\n        return total_;\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/BIT.hpp
  requiredBy:
  - DataStructure/OrderedSet.hpp
  - Geometry/PointInAngle.hpp
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/geometry/count_points_in_triangle.test.cpp
  - test/1_library_checker/data_structure/ordered_set.test.cpp
  - test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
documentation_of: DataStructure/BIT.hpp
layout: document
redirect_from:
- /library/DataStructure/BIT.hpp
- /library/DataStructure/BIT.hpp.html
title: DataStructure/BIT.hpp
---
