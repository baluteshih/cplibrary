---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/BIT.hpp
    title: DataStructure/BIT.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set.test.cpp
    title: test/1_library_checker/data_structure/ordered_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/OrderedSet.hpp\"\n\n#line 2 \"DataStructure/BIT.hpp\"\
    \n\ntemplate<class T>\nclass BIT { // 0-base\n    int n;\n    T total_;\n    vector<T>\
    \ bit;\npublic:\n    BIT(int _n): n(_n), total_(), bit(n + 1) {}\n    void initialize(const\
    \ std::vector<T> &arr) {\n        for (int x = 1; x <= n; ++x) {\n           \
    \ bit[x] = arr[x - 1];\n            int y = x - (x & -x);\n            for (int\
    \ i = x - 1; i > y; i -= i & -i)\n                bit[x] = bit[x] + bit[i];\n\
    \        }\n    }\n    void modify(int x, T v) {\n        total_ += v;\n     \
    \   for (++x; x <= n; x += x & -x)\n            bit[x] = bit[x] + v;\n    }\n\
    \    T prefix(int x) {\n        T res = T();\n        for (++x; x; x -= x & -x)\n\
    \            res = res + bit[x];\n        return res;\n    }\n    T suffix(int\
    \ x) requires requires(T x, T y) { x - y; } {\n        return total_ - prefix(x);\n\
    \    }\n    T range(int l, int r) requires requires(T x, T y) { x - y; } { //\
    \ [l, r)\n        if (l >= r) return T();\n        T res = prefix(r - 1) - prefix(l\
    \ - 1);\n        return res;\n    }\n    int kth(int k) { // 0-base query\n  \
    \      assert((n & (n - 1)) == 0);\n        ++k;\n        int res = 0;\n     \
    \   for (int i = n >> 1; i >= 1; i >>= 1) {\n            if (bit[res + i] < k)\n\
    \                k -= bit[res += i];\n        }\n        return res;\n    }\n\
    \    T total() {\n        return total_;\n    }\n};\n#line 4 \"DataStructure/OrderedSet.hpp\"\
    \n\ntemplate<class T>\nclass OrderedSet {\n    vector<T> vals;\n    vector<bool>\
    \ vis;\n    BIT<int> bit;\n    static vector<T> sort_and_unique(vector<T> _vals)\
    \ {\n        ranges::sort(_vals);\n        _vals.erase(ranges::unique(_vals).begin(),\
    \ _vals.end());\n        return _vals;\n    }\n    int idx(int x) {\n        auto\
    \ it = ranges::lower_bound(vals, x);\n        if (it == vals.end() || *it != x)\
    \ return -1;\n        return it - vals.begin();\n    }\n    int safe_idx(int x)\
    \ {\n        int res = idx(x);\n        assert(res != -1);\n        return res;\n\
    \    }\npublic:\n    OrderedSet(vector<T> _vals): vals(sort_and_unique(_vals)),\
    \ vis(vals.size()), bit(bit_ceil(vals.size())) {}\n    bool insert(T x) {\n  \
    \      x = safe_idx(x);\n        if (vis[x]) return false;\n        vis[x] = true;\n\
    \        bit.modify(x, 1);\n        return true;\n    }\n    bool erase(T x) {\n\
    \        x = safe_idx(x);\n        if (!vis[x]) return false;\n        vis[x]\
    \ = false;\n        bit.modify(x, -1);\n        return true;\n    }\n    bool\
    \ exists(T x) {\n        x = idx(x);\n        if (x == -1) return false;\n   \
    \     return vis[x]; \n    }\n    int size() {\n        return bit.total();\n\
    \    }\n    int lt_count(T x) {\n        int idx = ranges::lower_bound(vals, x)\
    \ - vals.begin() - 1;\n        return bit.prefix(idx);\n    }\n    int leq_count(T\
    \ x) {\n        int idx = ranges::upper_bound(vals, x) - vals.begin() - 1;\n \
    \       return bit.prefix(idx);\n    }\n    int order(T x) {\n        return leq_count(x);\n\
    \    }\n    int kth(int k) { // 0-base query, return 0-base index\n        if\
    \ (size() <= k) return -1;\n        int res = bit.kth(k);\n        return res;\n\
    \    }\n    int leq(T x) { // return 0-base index\n        int res = leq_count(x);\n\
    \        return res == 0 ? -1 : kth(res - 1);\n    }\n    int geq(T x) { // return\
    \ 0-base index\n        int res = lt_count(x);\n        return res == size() ?\
    \ -1 : kth(res);\n    }\n    const T& operator[](size_t index) const {\n     \
    \   return vals[index];\n    } \n};\n"
  code: "#pragma once\n\n#include \"DataStructure/BIT.hpp\"\n\ntemplate<class T>\n\
    class OrderedSet {\n    vector<T> vals;\n    vector<bool> vis;\n    BIT<int> bit;\n\
    \    static vector<T> sort_and_unique(vector<T> _vals) {\n        ranges::sort(_vals);\n\
    \        _vals.erase(ranges::unique(_vals).begin(), _vals.end());\n        return\
    \ _vals;\n    }\n    int idx(int x) {\n        auto it = ranges::lower_bound(vals,\
    \ x);\n        if (it == vals.end() || *it != x) return -1;\n        return it\
    \ - vals.begin();\n    }\n    int safe_idx(int x) {\n        int res = idx(x);\n\
    \        assert(res != -1);\n        return res;\n    }\npublic:\n    OrderedSet(vector<T>\
    \ _vals): vals(sort_and_unique(_vals)), vis(vals.size()), bit(bit_ceil(vals.size()))\
    \ {}\n    bool insert(T x) {\n        x = safe_idx(x);\n        if (vis[x]) return\
    \ false;\n        vis[x] = true;\n        bit.modify(x, 1);\n        return true;\n\
    \    }\n    bool erase(T x) {\n        x = safe_idx(x);\n        if (!vis[x])\
    \ return false;\n        vis[x] = false;\n        bit.modify(x, -1);\n       \
    \ return true;\n    }\n    bool exists(T x) {\n        x = idx(x);\n        if\
    \ (x == -1) return false;\n        return vis[x]; \n    }\n    int size() {\n\
    \        return bit.total();\n    }\n    int lt_count(T x) {\n        int idx\
    \ = ranges::lower_bound(vals, x) - vals.begin() - 1;\n        return bit.prefix(idx);\n\
    \    }\n    int leq_count(T x) {\n        int idx = ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n        return bit.prefix(idx);\n    }\n    int order(T\
    \ x) {\n        return leq_count(x);\n    }\n    int kth(int k) { // 0-base query,\
    \ return 0-base index\n        if (size() <= k) return -1;\n        int res =\
    \ bit.kth(k);\n        return res;\n    }\n    int leq(T x) { // return 0-base\
    \ index\n        int res = leq_count(x);\n        return res == 0 ? -1 : kth(res\
    \ - 1);\n    }\n    int geq(T x) { // return 0-base index\n        int res = lt_count(x);\n\
    \        return res == size() ? -1 : kth(res);\n    }\n    const T& operator[](size_t\
    \ index) const {\n        return vals[index];\n    } \n};\n"
  dependsOn:
  - DataStructure/BIT.hpp
  isVerificationFile: false
  path: DataStructure/OrderedSet.hpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/ordered_set.test.cpp
documentation_of: DataStructure/OrderedSet.hpp
layout: document
redirect_from:
- /library/DataStructure/OrderedSet.hpp
- /library/DataStructure/OrderedSet.hpp.html
title: DataStructure/OrderedSet.hpp
---
