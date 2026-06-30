---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: DataStructure/BIT.hpp
    title: Binary Indexed Tree (BIT)
  - icon: ':question:'
    path: DataStructure/Discretization.hpp
    title: Discretization
  - icon: ':heavy_check_mark:'
    path: DataStructure/OrderedSet.hpp
    title: Ordered Set
  - icon: ':question:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/ordered_set
    links:
    - https://judge.yosupo.jp/problem/ordered_set
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/ordered_set.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n#line 2 \"\
    assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3 \"test/1_library_checker/data_structure/ordered_set.test.cpp\"\
    \n\n#line 2 \"DataStructure/OrderedSet.hpp\"\n\n#line 2 \"DataStructure/Discretization.hpp\"\
    \n\ntemplate<typename T>\nclass Discretization {\n    std::vector<T> vals;\n \
    \   static std::vector<T> sort_and_unique(std::vector<T> _vals) {\n        std::ranges::sort(_vals);\n\
    \        _vals.erase(std::ranges::unique(_vals).begin(), _vals.end());\n     \
    \   return _vals;\n    }\npublic:\n    int idx(T x) {\n        auto it = std::ranges::lower_bound(vals,\
    \ x);\n        if (it == vals.end() || *it != x) return -1;\n        return it\
    \ - vals.begin();\n    }\n    int safe_idx(T x) {\n        int res = idx(x);\n\
    \        assert(res != -1);\n        return res;\n    }\n    Discretization(const\
    \ std::vector<T> &_vals): vals(sort_and_unique(_vals)) {}\n    int left_close(T\
    \ x) {\n        return std::ranges::lower_bound(vals, x) - vals.begin();\n   \
    \ }\n    int left_open(T x) {\n        return std::ranges::upper_bound(vals, x)\
    \ - vals.begin() - 1;\n    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(vals,\
    \ x) - vals.begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(vals,\
    \ x) - vals.begin();\n    }\n    const T& operator[](size_t index) const {\n \
    \       return vals[index];\n    }\n    int size() {\n        return vals.size();\n\
    \    }\n};\n#line 2 \"DataStructure/BIT.hpp\"\n\ntemplate<class T>\nclass BIT\
    \ { // 0-base\npublic:\n    int n;\n    T total_;\n    std::vector<T> bit;\n \
    \   BIT(int _n) : n(_n), total_(), bit(n + 1) {}\n    template<typename U>\n \
    \   BIT(const std::vector<U> &arr) : n(arr.size()), total_(std::accumulate(arr.begin(),\
    \ arr.end(), T())), bit(n + 1) {\n        for (int x = 1; x <= n; ++x) {\n   \
    \         bit[x] = arr[x - 1];\n            int y = x - (x & -x);\n          \
    \  for (int i = x - 1; i > y; i -= i & -i)\n                bit[x] = bit[x] +\
    \ bit[i];\n        }\n    }\n    void modify(int x, T v) {\n        total_ = total_\
    \ + v;\n        for (++x; x <= n; x += x & -x)\n            bit[x] = bit[x] +\
    \ v;\n    }\n    T prefix(int x) {\n        T res = T();\n        for (++x; x;\
    \ x -= x & -x)\n            res = res + bit[x];\n        return res;\n    }\n\
    \    T suffix(int x) requires requires(T x, T y) { x - y; } {\n        return\
    \ total_ - prefix(x - 1);\n    }\n    T range(int l, int r) requires requires(T\
    \ x, T y) { x - y; } { // [l, r)\n        if (l >= r) return T();\n        T res\
    \ = prefix(r - 1) - prefix(l - 1);\n        return res;\n    }\n    int kth(int\
    \ k) { // 0-base query\n        assert((n & (n - 1)) == 0);\n        ++k;\n  \
    \      int res = 0;\n        for (int i = n >> 1; i >= 1; i >>= 1) {\n       \
    \     if (bit[res + i] < k)\n                k -= bit[res += i];\n        }\n\
    \        return res;\n    }\n    T total() {\n        return total_;\n    }\n\
    };\n#line 5 \"DataStructure/OrderedSet.hpp\"\n\ntemplate<class T>\nclass OrderedSet\
    \ : public Discretization<T> {\n    std::vector<bool> vis;\n    BIT<int> bit;\n\
    public:\n    OrderedSet(const std::vector<T> &_vals): Discretization<T>(_vals),\
    \ vis(_vals.size()), bit(std::bit_ceil(_vals.size())) {}\n    bool insert(T x)\
    \ {\n        x = this->safe_idx(x);\n        if (vis[x]) return false;\n     \
    \   vis[x] = true;\n        bit.modify(x, 1);\n        return true;\n    }\n \
    \   bool erase(T x) {\n        x = this->safe_idx(x);\n        if (!vis[x]) return\
    \ false;\n        vis[x] = false;\n        bit.modify(x, -1);\n        return\
    \ true;\n    }\n    bool exists(T x) {\n        x = this->idx(x);\n        if\
    \ (x == -1) return false;\n        return vis[x]; \n    }\n    int size() {\n\
    \        return bit.total();\n    }\n    int lt_count(T x) {\n        return bit.prefix(this->right_open(x)\
    \ - 1);\n    }\n    int leq_count(T x) {\n        return bit.prefix(this->right_close(x));\n\
    \    }\n    int order(T x) {\n        return leq_count(x);\n    }\n    int kth(int\
    \ k) { // 0-base query, return 0-base index\n        if (size() <= k) return -1;\n\
    \        int res = bit.kth(k);\n        return res;\n    }\n    int leq(T x) {\
    \ // return 0-base index\n        int res = leq_count(x);\n        return res\
    \ == 0 ? -1 : kth(res - 1);\n    }\n    int geq(T x) { // return 0-base index\n\
    \        int res = lt_count(x);\n        return res == size() ? -1 : kth(res);\n\
    \    }\n};\n#line 5 \"test/1_library_checker/data_structure/ordered_set.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    std::vector<int> arr(n);\n    for (int &i\
    \ : arr)\n        std::cin >> i;\n    std::vector<int> vals(arr);\n    std::vector<std::pair<int,\
    \ int>> qry(q);\n    for (auto &[t, x] : qry) {\n        std::cin >> t >> x;\n\
    \        if (t == 0 || t == 1)\n            vals.push_back(x);\n    }\n    vals.push_back(0);\n\
    \    OrderedSet<int> ord(vals);\n    for (int i : arr)\n        ord.insert(i);\n\
    \    for (auto &[t, x] : qry) {\n        if (t == 0) ord.insert(x);\n        else\
    \ if (t == 1) ord.erase(x);\n        else if (t == 2) {\n            int res =\
    \ ord.kth(x - 1);\n            if (res != -1) res = ord[res]; \n            std::cout\
    \ << res << \"\\n\";\n        }\n        else if (t == 3)\n            std::cout\
    \ << ord.leq_count(x) << \"\\n\";\n        else if (t == 4) {\n            int\
    \ res = ord.leq(x);\n            if (res != -1) res = ord[res]; \n           \
    \ std::cout << res << \"\\n\";\n        }\n        else {\n            int res\
    \ = ord.geq(x);\n            if (res != -1) res = ord[res]; \n            std::cout\
    \ << res << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n#include\
    \ \"assumption.hpp\"\n\n#include \"DataStructure/OrderedSet.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    std::vector<int> arr(n);\n    for (int &i : arr)\n        std::cin\
    \ >> i;\n    std::vector<int> vals(arr);\n    std::vector<std::pair<int, int>>\
    \ qry(q);\n    for (auto &[t, x] : qry) {\n        std::cin >> t >> x;\n     \
    \   if (t == 0 || t == 1)\n            vals.push_back(x);\n    }\n    vals.push_back(0);\n\
    \    OrderedSet<int> ord(vals);\n    for (int i : arr)\n        ord.insert(i);\n\
    \    for (auto &[t, x] : qry) {\n        if (t == 0) ord.insert(x);\n        else\
    \ if (t == 1) ord.erase(x);\n        else if (t == 2) {\n            int res =\
    \ ord.kth(x - 1);\n            if (res != -1) res = ord[res]; \n            std::cout\
    \ << res << \"\\n\";\n        }\n        else if (t == 3)\n            std::cout\
    \ << ord.leq_count(x) << \"\\n\";\n        else if (t == 4) {\n            int\
    \ res = ord.leq(x);\n            if (res != -1) res = ord[res]; \n           \
    \ std::cout << res << \"\\n\";\n        }\n        else {\n            int res\
    \ = ord.geq(x);\n            if (res != -1) res = ord[res]; \n            std::cout\
    \ << res << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/OrderedSet.hpp
  - DataStructure/Discretization.hpp
  - DataStructure/BIT.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/ordered_set.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 14:18:54+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/ordered_set.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/ordered_set.test.cpp
- /verify/test/1_library_checker/data_structure/ordered_set.test.cpp.html
title: test/1_library_checker/data_structure/ordered_set.test.cpp
---
