---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
    title: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/SparseTable.hpp\"\n\ntemplate<typename Value\
    \ = int>\nclass SparseTable {\n    int n;\n    std::vector<std::vector<Value>>\
    \ table;\npublic:\n    SparseTable(const std::vector<Value> &data): n(data.size()),\
    \ table(std::__lg(data.size()) + 1, std::vector<Value>(data.size())) { \n    \
    \    int L = std::__lg(n);\n        table[0] = data;\n        for (int i = 1;\
    \ i <= L; ++i)\n            for (int j = 0; j + (1 << i) <= n; ++j)\n        \
    \        table[i][j] = table[i - 1][j] + table[i - 1][j + (1 << (i - 1))];\n \
    \   }\n    Value range_prod(int l, int r) {\n        assert(0 <= l && r <= n);\n\
    \        assert(l <= r);\n        if (l == r) return Value();\n        int lg\
    \ = std::__lg(r - l);\n        return table[lg][l] + table[lg][r - (1 << lg)];\n\
    \    }\n};\n"
  code: "#pragma once\n\ntemplate<typename Value = int>\nclass SparseTable {\n   \
    \ int n;\n    std::vector<std::vector<Value>> table;\npublic:\n    SparseTable(const\
    \ std::vector<Value> &data): n(data.size()), table(std::__lg(data.size()) + 1,\
    \ std::vector<Value>(data.size())) { \n        int L = std::__lg(n);\n       \
    \ table[0] = data;\n        for (int i = 1; i <= L; ++i)\n            for (int\
    \ j = 0; j + (1 << i) <= n; ++j)\n                table[i][j] = table[i - 1][j]\
    \ + table[i - 1][j + (1 << (i - 1))];\n    }\n    Value range_prod(int l, int\
    \ r) {\n        assert(0 <= l && r <= n);\n        assert(l <= r);\n        if\
    \ (l == r) return Value();\n        int lg = std::__lg(r - l);\n        return\
    \ table[lg][l] + table[lg][r - (1 << lg)];\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/SparseTable.hpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
documentation_of: DataStructure/SparseTable.hpp
layout: document
redirect_from:
- /library/DataStructure/SparseTable.hpp
- /library/DataStructure/SparseTable.hpp.html
title: DataStructure/SparseTable.hpp
---
