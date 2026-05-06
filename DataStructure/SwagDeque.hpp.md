---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp
    title: test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/SwagDeque.hpp\"\n\ntemplate<typename T>\n\
    class SwagDeque {\n    int sz;\n    std::vector<T> data_l, data_r, cum_l, cum_r;\n\
    \    void rebuild() {\n        std::vector<T> X;\n        std::ranges::reverse(data_l);\n\
    \        X.insert(X.end(), data_l.begin(), data_l.end());\n        X.insert(X.end(),\
    \ data_r.begin(), data_r.end());\n        clear();\n        int m = X.size() /\
    \ 2;\n        for (int i = m - 1; i >= 0; --i) push_front(X[i]);\n        for\
    \ (int i = m; i < int(X.size()); ++i) push_back(X[i]);\n    }\npublic:\n    SwagDeque()\
    \ : sz(0), cum_l(1, T()), cum_r(1, T()) {}\n    int size() { return sz; }\n  \
    \  void push_back(T x) {\n        ++sz;\n        data_r.push_back(x);\n      \
    \  cum_r.push_back(cum_r.back() + x);\n    }\n    void push_front(T x) {\n   \
    \     ++sz;\n        data_l.push_back(x);\n        cum_l.push_back(x + cum_l.back());\n\
    \    }\n    void clear() {\n        sz = 0;\n        data_l.clear(), data_r.clear();\n\
    \        std::vector<T>(1, T()).swap(cum_l);\n        std::vector<T>(1, T()).swap(cum_r);\n\
    \    }\n    void pop_front() {\n        if (sz == 1) return clear();\n       \
    \ if (data_l.empty()) rebuild();\n        --sz;\n        data_l.pop_back();\n\
    \        cum_l.pop_back();\n    }\n    void pop_back() {\n        if (sz == 1)\
    \ return clear();\n        if (data_r.empty()) rebuild();\n        --sz;\n   \
    \     data_r.pop_back();\n        cum_r.pop_back();\n    }\n    T front() {\n\
    \        if (!data_l.empty()) return data_l.back();\n        return data_r[0];\n\
    \    }\n    T lprod() { return cum_l.back(); }\n    T rprod() { return cum_r.back();\
    \ }\n    T prod() { return lprod() + rprod(); }\n};\n"
  code: "#pragma once\n\ntemplate<typename T>\nclass SwagDeque {\n    int sz;\n  \
    \  std::vector<T> data_l, data_r, cum_l, cum_r;\n    void rebuild() {\n      \
    \  std::vector<T> X;\n        std::ranges::reverse(data_l);\n        X.insert(X.end(),\
    \ data_l.begin(), data_l.end());\n        X.insert(X.end(), data_r.begin(), data_r.end());\n\
    \        clear();\n        int m = X.size() / 2;\n        for (int i = m - 1;\
    \ i >= 0; --i) push_front(X[i]);\n        for (int i = m; i < int(X.size()); ++i)\
    \ push_back(X[i]);\n    }\npublic:\n    SwagDeque() : sz(0), cum_l(1, T()), cum_r(1,\
    \ T()) {}\n    int size() { return sz; }\n    void push_back(T x) {\n        ++sz;\n\
    \        data_r.push_back(x);\n        cum_r.push_back(cum_r.back() + x);\n  \
    \  }\n    void push_front(T x) {\n        ++sz;\n        data_l.push_back(x);\n\
    \        cum_l.push_back(x + cum_l.back());\n    }\n    void clear() {\n     \
    \   sz = 0;\n        data_l.clear(), data_r.clear();\n        std::vector<T>(1,\
    \ T()).swap(cum_l);\n        std::vector<T>(1, T()).swap(cum_r);\n    }\n    void\
    \ pop_front() {\n        if (sz == 1) return clear();\n        if (data_l.empty())\
    \ rebuild();\n        --sz;\n        data_l.pop_back();\n        cum_l.pop_back();\n\
    \    }\n    void pop_back() {\n        if (sz == 1) return clear();\n        if\
    \ (data_r.empty()) rebuild();\n        --sz;\n        data_r.pop_back();\n   \
    \     cum_r.pop_back();\n    }\n    T front() {\n        if (!data_l.empty())\
    \ return data_l.back();\n        return data_r[0];\n    }\n    T lprod() { return\
    \ cum_l.back(); }\n    T rprod() { return cum_r.back(); }\n    T prod() { return\
    \ lprod() + rprod(); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: DataStructure/SwagDeque.hpp
  requiredBy: []
  timestamp: '2026-05-04 02:28:30+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/deque_operate_all_composite.test.cpp
documentation_of: DataStructure/SwagDeque.hpp
layout: document
redirect_from:
- /library/DataStructure/SwagDeque.hpp
- /library/DataStructure/SwagDeque.hpp.html
title: DataStructure/SwagDeque.hpp
---
