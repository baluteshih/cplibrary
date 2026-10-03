---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/concept.hpp
    title: Algebra/Monoid/concept.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/BIT.hpp
    title: Binary Indexed Tree (BIT)
  - icon: ':heavy_check_mark:'
    path: DataStructure/Discretization.hpp
    title: Discretization
  - icon: ':heavy_check_mark:'
    path: Sequence/cdq_solver.hpp
    title: Sequence/cdq_solver.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/rectangle_add_point_get
    links:
    - https://judge.yosupo.jp/problem/rectangle_add_point_get
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_add_point_get\"\n\
    #line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp\"\
    \n\n#line 2 \"Sequence/cdq_solver.hpp\"\n\ntemplate<typename E, typename F_Add,\
    \ typename F_Query, typename F_Undo>\nvoid cdq_solver(const std::vector<E> &elements,\
    \ F_Add add, F_Query query, F_Undo undo) {\n    if (elements.empty()) return;\n\
    \    std::vector<int> idx(elements.size()), temp(elements.size());\n    std::iota(idx.begin(),\
    \ idx.end(), 0);\n    auto solve = [&](auto self, int l, int r) -> void {\n  \
    \      if (l == r) return;\n        int mid = (l + r) >> 1;\n        self(self,\
    \ l, mid), self(self, mid + 1, r);\n        int i = l, j = mid + 1, k = l;\n \
    \       while (i <= mid && j <= r) {\n            if (elements[idx[i]] < elements[idx[j]])\
    \ add(elements[temp[k++] = idx[i++]]);\n            else query(elements[temp[k++]\
    \ = idx[j++]]);\n        }\n        while (j <= r) query(elements[temp[k++] =\
    \ idx[j++]]);\n        std::copy(idx.begin() + i, idx.begin() + mid + 1, temp.begin()\
    \ + k);\n        while (i > l) undo(elements[idx[--i]]);\n        std::copy(temp.begin()\
    \ + l, temp.begin() + r + 1, idx.begin() + l);\n    };\n    solve(solve, 0, elements.size()\
    \ - 1);\n}\n#line 2 \"DataStructure/BIT.hpp\"\n\n#line 2 \"Algebra/Monoid/concept.hpp\"\
    \n\n#line 2 \"Algebra/ValidOperation.hpp\"\n\ntemplate <typename A, typename B>\n\
    concept Addable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a + b; };\n\ntemplate <typename A, typename B>\nconcept Subtractable =\
    \ !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a - b; };\n\
    \ntemplate <typename A, typename B>\nconcept Multiplicable = !std::is_void_v<A>\
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
    \    T total() {\n        return total_;\n    }\n};\n#line 2 \"DataStructure/Discretization.hpp\"\
    \n\ntemplate<typename T>\nclass Discretization : public std::vector<T> {\npublic:\n\
    \    using std::vector<T>::vector;\n    virtual void build() {\n        std::ranges::sort(*this);\n\
    \        auto [first, last] = std::ranges::unique(*this);\n        this->erase(first,\
    \ last);\n    }\n    int idx(T x) {\n        auto it = std::ranges::lower_bound(*this,\
    \ x);\n        if (it == this->end() || *it != x) return -1;\n        return it\
    \ - this->begin();\n    }\n    int safe_idx(T x) {\n        int res = idx(x);\n\
    \        assert(res != -1);\n        return res;\n    }\n    int left_close(T\
    \ x) {\n        return std::ranges::lower_bound(*this, x) - this->begin();\n \
    \   }\n    int left_open(T x) {\n        return std::ranges::upper_bound(*this,\
    \ x) - this->begin() - 1;\n    }\n    int right_close(T x) {\n        return std::ranges::upper_bound(*this,\
    \ x) - this->begin() - 1;\n    }\n    int right_open(T x) {\n        return std::ranges::lower_bound(*this,\
    \ x) - this->begin();\n    }\n};\n#line 7 \"test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp\"\
    \n\nstruct Element {\n    int x;\n    int l, r;\n    int val;\n    bool operator<(const\
    \ Element &rhs) const {\n        if (x != rhs.x) return x < rhs.x;\n        return\
    \ r > rhs.r;\n    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<Element> arr(n + n);\n\
    \    for (int i = 0; i < n; ++i) {\n        int l, d, r, u, w;\n        std::cin\
    \ >> l >> d >> r >> u >> w;\n        arr[i * 2] = Element{l, d, u, w};\n     \
    \   arr[i * 2 + 1] = Element{r, d, u, -w};\n    }\n    int qcnt = 0;\n    while\
    \ (q--) {\n        int op;\n        std::cin >> op;\n        if (op == 0) {\n\
    \            int l, d, r, u, w;\n            std::cin >> l >> d >> r >> u >> w;\n\
    \            arr.push_back(Element{l, d, u, w});\n            arr.push_back(Element{r,\
    \ d, u, -w});\n        }\n        else {\n            int x, y;\n            std::cin\
    \ >> x >> y;\n            arr.push_back(Element{x, y, -1, qcnt++});\n        }\n\
    \    }\n    Discretization<int> val;\n    for (auto &[x, l, r, v] : arr) {\n \
    \       val.push_back(l);\n        if (r != -1) val.push_back(r);\n    }\n   \
    \ val.build();\n    for (auto &[x, l, r, v] : arr) {\n        l = val.idx(l);\n\
    \        if (r != -1) r = val.idx(r);\n    }\n    std::vector<long long> ans(qcnt);\n\
    \    BIT<long long> bit(val.size());\n    cdq_solver(arr,\n        [&](const Element\
    \ &e) {\n            if (e.r != -1) {\n                bit.modify(e.l, e.val);\n\
    \                bit.modify(e.r, -e.val);\n            }\n        },\n       \
    \ [&](const Element &e) {\n            if (e.r == -1) ans[e.val] += bit.prefix(e.l);\n\
    \        },\n        [&](const Element &e) {\n            if (e.r != -1) {\n \
    \               bit.modify(e.l, -e.val);\n                bit.modify(e.r, e.val);\n\
    \            }\n        }\n    );\n    for (int i = 0; i < qcnt; ++i)\n      \
    \  std::cout << ans[i] << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_add_point_get\"\
    \n#include \"assumption.hpp\"\n\n#include \"Sequence/cdq_solver.hpp\"\n#include\
    \ \"DataStructure/BIT.hpp\"\n#include \"DataStructure/Discretization.hpp\"\n\n\
    struct Element {\n    int x;\n    int l, r;\n    int val;\n    bool operator<(const\
    \ Element &rhs) const {\n        if (x != rhs.x) return x < rhs.x;\n        return\
    \ r > rhs.r;\n    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<Element> arr(n + n);\n\
    \    for (int i = 0; i < n; ++i) {\n        int l, d, r, u, w;\n        std::cin\
    \ >> l >> d >> r >> u >> w;\n        arr[i * 2] = Element{l, d, u, w};\n     \
    \   arr[i * 2 + 1] = Element{r, d, u, -w};\n    }\n    int qcnt = 0;\n    while\
    \ (q--) {\n        int op;\n        std::cin >> op;\n        if (op == 0) {\n\
    \            int l, d, r, u, w;\n            std::cin >> l >> d >> r >> u >> w;\n\
    \            arr.push_back(Element{l, d, u, w});\n            arr.push_back(Element{r,\
    \ d, u, -w});\n        }\n        else {\n            int x, y;\n            std::cin\
    \ >> x >> y;\n            arr.push_back(Element{x, y, -1, qcnt++});\n        }\n\
    \    }\n    Discretization<int> val;\n    for (auto &[x, l, r, v] : arr) {\n \
    \       val.push_back(l);\n        if (r != -1) val.push_back(r);\n    }\n   \
    \ val.build();\n    for (auto &[x, l, r, v] : arr) {\n        l = val.idx(l);\n\
    \        if (r != -1) r = val.idx(r);\n    }\n    std::vector<long long> ans(qcnt);\n\
    \    BIT<long long> bit(val.size());\n    cdq_solver(arr,\n        [&](const Element\
    \ &e) {\n            if (e.r != -1) {\n                bit.modify(e.l, e.val);\n\
    \                bit.modify(e.r, -e.val);\n            }\n        },\n       \
    \ [&](const Element &e) {\n            if (e.r == -1) ans[e.val] += bit.prefix(e.l);\n\
    \        },\n        [&](const Element &e) {\n            if (e.r != -1) {\n \
    \               bit.modify(e.l, -e.val);\n                bit.modify(e.r, e.val);\n\
    \            }\n        }\n    );\n    for (int i = 0; i < qcnt; ++i)\n      \
    \  std::cout << ans[i] << \"\\n\";\n}\n"
  dependsOn:
  - assumption.hpp
  - Sequence/cdq_solver.hpp
  - DataStructure/BIT.hpp
  - Algebra/Monoid/concept.hpp
  - Algebra/ValidOperation.hpp
  - DataStructure/Discretization.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp
  requiredBy: []
  timestamp: '2026-09-24 21:34:44+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp
- /verify/test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp.html
title: test/1_library_checker/data_structure/rectangle_add_point_get.test.cpp
---
