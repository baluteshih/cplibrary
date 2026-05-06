---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
    title: test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/CatTree.hpp\"\n\ntemplate<typename Value =\
    \ int>\nclass CatTree {\n    int n;\n    std::vector<int> mid;\n    std::vector<std::vector<Value>>\
    \ lft, rgt;\n    void initialize(int l, int r, int rt, const vector<Value> &data)\
    \ {\n        if (r - l == 1) {\n            lft[rt].push_back(data[l]);\n    \
    \        return;\n        }\n        mid[rt] = (l + r) >> 1;\n        lft[rt].resize(mid[rt]\
    \ - l);\n        rgt[rt].resize(r - mid[rt]);\n        for (int i = mid[rt] -\
    \ 1; i >= l; --i) {\n            lft[rt][mid[rt] - i - 1] = i < std::ssize(data)\
    \ ? data[i] : Value();\n            if (mid[rt] - i - 1 > 0)\n               \
    \ lft[rt][mid[rt] - i - 1] = lft[rt][mid[rt] - i - 1] + lft[rt][mid[rt] - i -\
    \ 2];\n        }\n        for (int i = mid[rt]; i < r; ++i) {\n            rgt[rt][i\
    \ - mid[rt]] = i < std::ssize(data) ? data[i] : Value();\n            if (i -\
    \ mid[rt] > 0)\n                rgt[rt][i - mid[rt]] = rgt[rt][i - mid[rt] - 1]\
    \ + rgt[rt][i - mid[rt]];\n        }\n        initialize(l, mid[rt], rt << 1,\
    \ data);\n        initialize(mid[rt], r, rt << 1 | 1, data);\n    }\n    static\
    \ int ceilpow2(int sz) {\n        int m = 1;\n        while (m < sz) m <<= 1;\n\
    \        return m;\n    }\npublic:\n    CatTree(const std::vector<Value> &data):\
    \ n(ceilpow2(data.size())), mid(n), lft(n << 1), rgt(n) { \n        initialize(0,\
    \ n, 1, data);\n    }\n    CatTree(int size): CatTree(std::vector<Value>(size))\
    \ {}\n    Value range_prod(int l, int r) {\n        assert(0 <= l && r <= n);\n\
    \        assert(l <= r);\n        if (l == r) return Value();\n        --r;\n\
    \        l += n, r += n;\n        if (l == r) return lft[l][0];\n        int lca\
    \ = l >> (std::__lg(l ^ r) + 1);\n        l -= n, r -= n;\n        return lft[lca][mid[lca]\
    \ - l - 1] + rgt[lca][r - mid[lca]];\n    }\n};\n"
  code: "#pragma once\n\ntemplate<typename Value = int>\nclass CatTree {\n    int\
    \ n;\n    std::vector<int> mid;\n    std::vector<std::vector<Value>> lft, rgt;\n\
    \    void initialize(int l, int r, int rt, const vector<Value> &data) {\n    \
    \    if (r - l == 1) {\n            lft[rt].push_back(data[l]);\n            return;\n\
    \        }\n        mid[rt] = (l + r) >> 1;\n        lft[rt].resize(mid[rt] -\
    \ l);\n        rgt[rt].resize(r - mid[rt]);\n        for (int i = mid[rt] - 1;\
    \ i >= l; --i) {\n            lft[rt][mid[rt] - i - 1] = i < std::ssize(data)\
    \ ? data[i] : Value();\n            if (mid[rt] - i - 1 > 0)\n               \
    \ lft[rt][mid[rt] - i - 1] = lft[rt][mid[rt] - i - 1] + lft[rt][mid[rt] - i -\
    \ 2];\n        }\n        for (int i = mid[rt]; i < r; ++i) {\n            rgt[rt][i\
    \ - mid[rt]] = i < std::ssize(data) ? data[i] : Value();\n            if (i -\
    \ mid[rt] > 0)\n                rgt[rt][i - mid[rt]] = rgt[rt][i - mid[rt] - 1]\
    \ + rgt[rt][i - mid[rt]];\n        }\n        initialize(l, mid[rt], rt << 1,\
    \ data);\n        initialize(mid[rt], r, rt << 1 | 1, data);\n    }\n    static\
    \ int ceilpow2(int sz) {\n        int m = 1;\n        while (m < sz) m <<= 1;\n\
    \        return m;\n    }\npublic:\n    CatTree(const std::vector<Value> &data):\
    \ n(ceilpow2(data.size())), mid(n), lft(n << 1), rgt(n) { \n        initialize(0,\
    \ n, 1, data);\n    }\n    CatTree(int size): CatTree(std::vector<Value>(size))\
    \ {}\n    Value range_prod(int l, int r) {\n        assert(0 <= l && r <= n);\n\
    \        assert(l <= r);\n        if (l == r) return Value();\n        --r;\n\
    \        l += n, r += n;\n        if (l == r) return lft[l][0];\n        int lca\
    \ = l >> (std::__lg(l ^ r) + 1);\n        l -= n, r -= n;\n        return lft[lca][mid[lca]\
    \ - l - 1] + rgt[lca][r - mid[lca]];\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/CatTree.hpp
  requiredBy: []
  timestamp: '2026-03-18 20:28:14+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
documentation_of: DataStructure/CatTree.hpp
layout: document
redirect_from:
- /library/DataStructure/CatTree.hpp
- /library/DataStructure/CatTree.hpp.html
title: DataStructure/CatTree.hpp
---
