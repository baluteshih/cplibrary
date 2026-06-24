---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/SparseTable.hpp
    title: Sparse Table
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
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#line 2 \"assumption.hpp\"\
    \n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3 \"test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp\"\
    \n\n#line 2 \"DataStructure/SparseTable.hpp\"\n\ntemplate<typename Value = int>\n\
    class SparseTable {\n    int n;\n    std::vector<std::vector<Value>> table;\n\
    public:\n    SparseTable(const std::vector<Value> &data): n(data.size()), table(std::__lg(data.size())\
    \ + 1, std::vector<Value>(data.size())) { \n        int L = std::__lg(n);\n  \
    \      table[0] = data;\n        for (int i = 1; i <= L; ++i)\n            for\
    \ (int j = 0; j + (1 << i) <= n; ++j)\n                table[i][j] = table[i -\
    \ 1][j] + table[i - 1][j + (1 << (i - 1))];\n    }\n    Value range_prod(int l,\
    \ int r) {\n        assert(0 <= l && r <= n);\n        assert(l <= r);\n     \
    \   if (l == r) return Value();\n        int lg = std::__lg(r - l);\n        return\
    \ table[lg][l] + table[lg][r - (1 << lg)];\n    }\n};\n#line 5 \"test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp\"\
    \n\nstruct Value {\n    int val;\n    Value(int _v = 2'000'000'000): val(_v) {}\n\
    \    Value operator+(const Value &rhs) {\n        return Value(std::min(val, rhs.val));\n\
    \    }\n    friend std::ostream& operator<<(std::ostream& os, const Value &v)\
    \ {\n        os << v.val;\n        return os;\n    }\n    friend std::istream&\
    \ operator>>(std::istream& is, Value &v) {\n        is >> v.val;\n        return\
    \ is;\n    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<Value> arr(n);\n    for\
    \ (auto &i : arr)\n        std::cin >> i;\n    SparseTable table(arr);\n    while\
    \ (q--) {\n        int l, r;\n        std::cin >> l >> r;\n        std::cout <<\
    \ table.range_prod(l, r) << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#include \"\
    assumption.hpp\"\n\n#include \"DataStructure/SparseTable.hpp\"\n\nstruct Value\
    \ {\n    int val;\n    Value(int _v = 2'000'000'000): val(_v) {}\n    Value operator+(const\
    \ Value &rhs) {\n        return Value(std::min(val, rhs.val));\n    }\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const Value &v) {\n        os <<\
    \ v.val;\n        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, Value &v) {\n        is >> v.val;\n        return is;\n    }\n};\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n\
    \    std::cin >> n >> q;\n    std::vector<Value> arr(n);\n    for (auto &i : arr)\n\
    \        std::cin >> i;\n    SparseTable table(arr);\n    while (q--) {\n    \
    \    int l, r;\n        std::cin >> l >> r;\n        std::cout << table.range_prod(l,\
    \ r) << \"\\n\";\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/SparseTable.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
  requiredBy: []
  timestamp: '2026-06-19 18:28:09+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
- /verify/test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp.html
title: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
---
