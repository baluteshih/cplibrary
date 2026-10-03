---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/concept.hpp
    title: Algebra/Monoid/concept.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/max_v.hpp
    title: Algebra/Monoid/max_v.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/BIT.hpp
    title: Binary Indexed Tree (BIT)
  - icon: ':heavy_check_mark:'
    path: DataStructure/Discretization.hpp
    title: Discretization
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/other/longest_increasing_subsequence.test.cpp
    title: test/1_library_checker/other/longest_increasing_subsequence.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Sequence/longest_increasing_subsequence.hpp\"\n\n#line 2\
    \ \"DataStructure/Discretization.hpp\"\n\ntemplate<typename T>\nclass Discretization\
    \ : public std::vector<T> {\npublic:\n    using std::vector<T>::vector;\n    virtual\
    \ void build() {\n        std::ranges::sort(*this);\n        auto [first, last]\
    \ = std::ranges::unique(*this);\n        this->erase(first, last);\n    }\n  \
    \  int idx(T x) {\n        auto it = std::ranges::lower_bound(*this, x);\n   \
    \     if (it == this->end() || *it != x) return -1;\n        return it - this->begin();\n\
    \    }\n    int safe_idx(T x) {\n        int res = idx(x);\n        assert(res\
    \ != -1);\n        return res;\n    }\n    int left_close(T x) {\n        return\
    \ std::ranges::lower_bound(*this, x) - this->begin();\n    }\n    int left_open(T\
    \ x) {\n        return std::ranges::upper_bound(*this, x) - this->begin() - 1;\n\
    \    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(*this,\
    \ x) - this->begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(*this,\
    \ x) - this->begin();\n    }\n};\n#line 2 \"DataStructure/BIT.hpp\"\n\n#line 2\
    \ \"Algebra/Monoid/concept.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\n\n\
    template <typename A, typename B>\nconcept Addable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a + b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Subtractable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b)\
    \ { a - b; };\n\ntemplate <typename A, typename B>\nconcept Multiplicable = !std::is_void_v<A>\
    \ && !std::is_void_v<B> && requires(A a, B b) { a * b; };\n#line 4 \"Algebra/Monoid/concept.hpp\"\
    \n\ntemplate<typename T>\nconcept isMonoid = Addable<T, T> && std::default_initializable<T>;\n\
    \ntemplate<typename T>\nconcept isCommutativeMonoid = isMonoid<T>;\n#line 5 \"\
    DataStructure/BIT.hpp\"\n\ntemplate<class T>\nrequires isCommutativeMonoid<T>\n\
    class BIT { // 0-base\npublic:\n    int n;\n    T total_;\n    std::vector<T>\
    \ bit;\n    BIT(int _n = 0) : n(_n), total_(), bit(n + 1) {}\n    BIT(const std::ranges::range\
    \ auto &arr) : n(std::ranges::distance(arr)), total_(std::accumulate(arr.begin(),\
    \ arr.end(), T())), bit(n + 1) {\n        for (int x = 1; x <= n; ++x) {\n   \
    \         bit[x] = arr[x - 1];\n            int y = x - (x & -x);\n          \
    \  for (int i = x - 1; i > y; i -= i & -i)\n                bit[x] = bit[x] +\
    \ bit[i];\n        }\n    }\n    void modify(int x, T v) {\n        total_ = total_\
    \ + v;\n        for (++x; x <= n; x += x & -x)\n            bit[x] = bit[x] +\
    \ v;\n    }\n    T prefix(int x) {\n        T res = T();\n        for (++x; x;\
    \ x -= x & -x)\n            res = res + bit[x];\n        return res;\n    }\n\
    \    T suffix(int x) requires Subtractable<T, T> {\n        return total_ - prefix(x\
    \ - 1);\n    }\n    T range(int l, int r) requires Subtractable<T, T> { // [l,\
    \ r)\n        if (l >= r) return T();\n        T res = prefix(r - 1) - prefix(l\
    \ - 1);\n        return res;\n    }\n    int kth(int k) { // 0-base query\n  \
    \      assert((n & (n - 1)) == 0);\n        ++k;\n        int res = 0;\n     \
    \   for (int i = n >> 1; i >= 1; i >>= 1) {\n            if (bit[res + i] < k)\n\
    \                k -= bit[res += i];\n        }\n        return res;\n    }\n\
    \    T total() {\n        return total_;\n    }\n};\n#line 2 \"Algebra/Monoid/max_v.hpp\"\
    \n\ntemplate<typename T, T neginf = std::numeric_limits<T>::lowest()>\nstruct\
    \ max_v {\n    T val;\n    max_v(T _val = neginf): val(_val) {}\n    max_v operator+(const\
    \ max_v &rhs) const {\n        return max_v(std::max(val, rhs.val));\n    }\n\
    \    friend std::ostream& operator<<(std::ostream& os, const max_v &v) {\n   \
    \     os << v.val;\n        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, max_v &v) {\n        is >> v.val;\n        return is;\n    }\n};\n#line\
    \ 6 \"Sequence/longest_increasing_subsequence.hpp\"\n\ntemplate<bool strict =\
    \ true, typename T = int>\nstd::vector<int> longest_increasing_subsequence(const\
    \ std::vector<T> &arr) {\n    Discretization<T> val(arr.begin(), arr.end());\n\
    \    val.build();\n    BIT<max_v<std::pair<int, int>>> bit(val.size());\n    std::vector<int>\
    \ dp(arr.size()), tr(arr.size());\n    for (int i = 0; i < int(arr.size()); ++i)\
    \ {\n        int cur = val.idx(arr[i]);\n        auto [v, idx] = bit.prefix(cur\
    \ - strict).val;\n        if (v <= 0) dp[i] = 1, tr[i] = -1;\n        else dp[i]\
    \ = v + 1, tr[i] = idx;\n        bit.modify(cur, std::make_pair(dp[i], i));\n\
    \    }\n    std::vector<int> res;\n    for (int mx = std::ranges::max_element(dp)\
    \ - dp.begin(); mx != -1; mx = tr[mx])\n        res.push_back(mx);\n    std::ranges::reverse(res);\n\
    \    return res;\n}\n"
  code: "#pragma once\n\n#include \"DataStructure/Discretization.hpp\"\n#include \"\
    DataStructure/BIT.hpp\"\n#include \"Algebra/Monoid/max_v.hpp\"\n\ntemplate<bool\
    \ strict = true, typename T = int>\nstd::vector<int> longest_increasing_subsequence(const\
    \ std::vector<T> &arr) {\n    Discretization<T> val(arr.begin(), arr.end());\n\
    \    val.build();\n    BIT<max_v<std::pair<int, int>>> bit(val.size());\n    std::vector<int>\
    \ dp(arr.size()), tr(arr.size());\n    for (int i = 0; i < int(arr.size()); ++i)\
    \ {\n        int cur = val.idx(arr[i]);\n        auto [v, idx] = bit.prefix(cur\
    \ - strict).val;\n        if (v <= 0) dp[i] = 1, tr[i] = -1;\n        else dp[i]\
    \ = v + 1, tr[i] = idx;\n        bit.modify(cur, std::make_pair(dp[i], i));\n\
    \    }\n    std::vector<int> res;\n    for (int mx = std::ranges::max_element(dp)\
    \ - dp.begin(); mx != -1; mx = tr[mx])\n        res.push_back(mx);\n    std::ranges::reverse(res);\n\
    \    return res;\n}\n"
  dependsOn:
  - DataStructure/Discretization.hpp
  - DataStructure/BIT.hpp
  - Algebra/Monoid/concept.hpp
  - Algebra/ValidOperation.hpp
  - Algebra/Monoid/max_v.hpp
  isVerificationFile: false
  path: Sequence/longest_increasing_subsequence.hpp
  requiredBy: []
  timestamp: '2026-10-03 12:58:48+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/other/longest_increasing_subsequence.test.cpp
documentation_of: Sequence/longest_increasing_subsequence.hpp
layout: document
redirect_from:
- /library/Sequence/longest_increasing_subsequence.hpp
- /library/Sequence/longest_increasing_subsequence.hpp.html
title: Sequence/longest_increasing_subsequence.hpp
---
