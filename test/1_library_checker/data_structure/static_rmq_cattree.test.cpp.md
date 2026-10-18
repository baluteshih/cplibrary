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
    path: DataStructure/CatTree.hpp
    title: Cat Tree
  - icon: ':heavy_check_mark:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/static_rmq_cattree.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#line 2 \"assumption.hpp\"\
    \n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3 \"test/1_library_checker/data_structure/static_rmq_cattree.test.cpp\"\
    \n\n#line 2 \"DataStructure/CatTree.hpp\"\n\n#line 2 \"Algebra/Monoid/concept.hpp\"\
    \n\n#line 2 \"Algebra/ValidOperation.hpp\"\n\ntemplate <typename A, typename B>\n\
    concept Addable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a + b; };\n\ntemplate <typename A, typename B>\nconcept Subtractable =\
    \ !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a - b; };\n\
    \ntemplate <typename A, typename B>\nconcept Multiplicable = !std::is_void_v<A>\
    \ && !std::is_void_v<B> && requires(A a, B b) { a * b; };\n#line 4 \"Algebra/Monoid/concept.hpp\"\
    \n\ntemplate<typename T>\nconcept isMonoid = Addable<T, T> && std::default_initializable<T>;\n\
    \ntemplate<typename T>\nconcept isCommutativeMonoid = isMonoid<T>;\n#line 4 \"\
    DataStructure/CatTree.hpp\"\n\ntemplate<typename Value = int>\nrequires isMonoid<Value>\n\
    class CatTree {\n    int n;\n    std::vector<int> mid;\n    std::vector<std::vector<Value>>\
    \ lft, rgt;\n    void initialize(int l, int r, int rt, const std::vector<Value>\
    \ &data) {\n        if (r - l == 1) {\n            lft[rt].push_back(data[l]);\n\
    \            return;\n        }\n        mid[rt] = (l + r) >> 1;\n        lft[rt].resize(mid[rt]\
    \ - l);\n        rgt[rt].resize(r - mid[rt]);\n        for (int i = mid[rt] -\
    \ 1; i >= l; --i) {\n            lft[rt][mid[rt] - i - 1] = i < std::ssize(data)\
    \ ? data[i] : Value();\n            if (mid[rt] - i - 1 > 0)\n               \
    \ lft[rt][mid[rt] - i - 1] = lft[rt][mid[rt] - i - 1] + lft[rt][mid[rt] - i -\
    \ 2];\n        }\n        for (int i = mid[rt]; i < r; ++i) {\n            rgt[rt][i\
    \ - mid[rt]] = i < std::ssize(data) ? data[i] : Value();\n            if (i -\
    \ mid[rt] > 0)\n                rgt[rt][i - mid[rt]] = rgt[rt][i - mid[rt] - 1]\
    \ + rgt[rt][i - mid[rt]];\n        }\n        initialize(l, mid[rt], rt << 1,\
    \ data);\n        initialize(mid[rt], r, rt << 1 | 1, data);\n    }\npublic:\n\
    \    CatTree(const std::ranges::range auto &data): n(std::bit_ceil(static_cast<std::size_t>(std::ranges::distance(data)))),\
    \ mid(n), lft(n << 1), rgt(n) { \n        initialize(0, n, 1, data);\n    }\n\
    \    CatTree(int size): CatTree(std::vector<Value>(size)) {}\n    Value range_prod(int\
    \ l, int r) {\n        assert(0 <= l && r <= n);\n        assert(l <= r);\n  \
    \      if (l == r) return Value();\n        --r;\n        l += n, r += n;\n  \
    \      if (l == r) return lft[l][0];\n        int lca = l >> (std::__lg(l ^ r)\
    \ + 1);\n        l -= n, r -= n;\n        return lft[lca][mid[lca] - l - 1] +\
    \ rgt[lca][r - mid[lca]];\n    }\n};\n#line 5 \"test/1_library_checker/data_structure/static_rmq_cattree.test.cpp\"\
    \n\nstruct Value {\n    int val;\n    Value(int _v = 2e9): val(_v) {}\n    Value\
    \ operator+(const Value &a) const {\n        return Value(std::min(val, a.val));\n\
    \    }\n    friend std::ostream& operator<<(std::ostream& os, const Value &v)\
    \ {\n        os << v.val;\n        return os;\n    }\n    friend std::istream&\
    \ operator>>(std::istream& is, Value &v) {\n        is >> v.val;\n        return\
    \ is;\n    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<Value> arr(n);\n    for\
    \ (auto &v : arr)\n        std::cin >> v;\n    CatTree<Value> seg(arr);\n    while\
    \ (q--) {\n        int l, r;\n        std::cin >> l >> r;\n        std::cout <<\
    \ seg.range_prod(l, r) << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#include \"\
    assumption.hpp\"\n\n#include \"DataStructure/CatTree.hpp\"\n\nstruct Value {\n\
    \    int val;\n    Value(int _v = 2e9): val(_v) {}\n    Value operator+(const\
    \ Value &a) const {\n        return Value(std::min(val, a.val));\n    }\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const Value &v) {\n        os <<\
    \ v.val;\n        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, Value &v) {\n        is >> v.val;\n        return is;\n    }\n};\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n\
    \    std::cin >> n >> q;\n    std::vector<Value> arr(n);\n    for (auto &v : arr)\n\
    \        std::cin >> v;\n    CatTree<Value> seg(arr);\n    while (q--) {\n   \
    \     int l, r;\n        std::cin >> l >> r;\n        std::cout << seg.range_prod(l,\
    \ r) << \"\\n\";\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/CatTree.hpp
  - Algebra/Monoid/concept.hpp
  - Algebra/ValidOperation.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
  requiredBy: []
  timestamp: '2026-06-30 17:38:58+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
- /verify/test/1_library_checker/data_structure/static_rmq_cattree.test.cpp.html
title: test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
---
