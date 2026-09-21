---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: DataStructure/LazyDeleteHeap.hpp
    title: Lazy Delete Heap
  - icon: ':heavy_check_mark:'
    path: DataStructure/MinMaxHeap.hpp
    title: MinMax Heap
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
    PROBLEM: https://judge.yosupo.jp/problem/double_ended_priority_queue
    links:
    - https://judge.yosupo.jp/problem/double_ended_priority_queue
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/double_ended_priority_queue.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/data_structure/double_ended_priority_queue.test.cpp\"\
    \n\n#line 2 \"DataStructure/MinMaxHeap.hpp\"\n\n#line 2 \"DataStructure/LazyDeleteHeap.hpp\"\
    \n\ntemplate <typename Container>\nclass LazyDeleteHeap {\nprivate:\n    Container\
    \ main_q;\n    Container del_q;\n    void normalize() {\n        while (!main_q.empty()\
    \ && !del_q.empty() && main_q.top() == del_q.top()) {\n            main_q.pop();\n\
    \            del_q.pop();\n        }\n    }\npublic:\n    using value_type = typename\
    \ Container::value_type;\n    void push(const value_type& val) {\n        main_q.push(val);\n\
    \    }\n    void erase(const value_type& val) {\n        del_q.push(val);\n  \
    \  }\n    void pop() {\n        normalize();\n        assert(!main_q.empty());\n\
    \        main_q.pop();\n    }\n    const value_type& top() {\n        normalize();\n\
    \        return main_q.top();\n    }\n    size_t size() const {\n        return\
    \ main_q.size() - del_q.size();\n    }\n    bool empty() const {\n        return\
    \ size() == 0;\n    }\n    void swap(LazyDeleteHeap &other) {\n        main_q.swap(other.main_q);\n\
    \        del_q.swap(other.del_q);\n    }\n    void clear() {\n        Container().swap(main_q);\
    \ \n        Container().swap(del_q); \n    }\n};\n#line 4 \"DataStructure/MinMaxHeap.hpp\"\
    \n\ntemplate<typename T>\nclass MinMaxHeap {\nprivate:\n    LazyDeleteHeap<std::priority_queue<T>>\
    \ max_heap;\n    LazyDeleteHeap<std::priority_queue<T, std::vector<T>, std::greater<T>>>\
    \ min_heap;\npublic: \n    void push(const T& val) {\n        max_heap.push(val);\n\
    \        min_heap.push(val);\n    }\n    void erase(const T& val) {\n        max_heap.erase(val);\n\
    \        min_heap.erase(val);\n    }\n    void pop_min() {\n        assert(!min_heap.empty());\n\
    \        max_heap.erase(min_heap.top());\n        min_heap.pop();\n    }\n   \
    \ void pop_max() {\n        assert(!max_heap.empty());\n        min_heap.erase(max_heap.top());\n\
    \        max_heap.pop();\n    }\n    const T& top_min() {\n        return min_heap.top();\n\
    \    }\n    const T& top_max() {\n        return max_heap.top();\n    }\n    size_t\
    \ size() const {\n        return max_heap.size(); \n    }\n    bool empty() const\
    \ {\n        return size() == 0;\n    }\n    void swap(MinMaxHeap &other) {\n\
    \        max_heap.swap(other.max_heap);\n        min_heap.swap(other.min_heap);\n\
    \    }\n    void clear() {\n        max_heap.clear();\n        min_heap.clear();\n\
    \    }\n};\n#line 5 \"test/1_library_checker/data_structure/double_ended_priority_queue.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    MinMaxHeap<int> heap;\n    while (n--) {\n\
    \        int x;\n        std::cin >> x;\n        heap.push(x);\n    }\n    while\
    \ (q--) {\n        int op;\n        std::cin >> op;\n        if (op == 0) {\n\
    \            int x;\n            std::cin >> x;\n            heap.push(x);\n \
    \       }\n        else if (op == 1) {\n            std::cout << heap.top_min()\
    \ << \"\\n\";\n            heap.pop_min();\n        }\n        else {\n      \
    \      std::cout << heap.top_max() << \"\\n\";\n            heap.pop_max();\n\
    \        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/double_ended_priority_queue\"\
    \n#include \"assumption.hpp\"\n\n#include \"DataStructure/MinMaxHeap.hpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n\
    \    std::cin >> n >> q;\n    MinMaxHeap<int> heap;\n    while (n--) {\n     \
    \   int x;\n        std::cin >> x;\n        heap.push(x);\n    }\n    while (q--)\
    \ {\n        int op;\n        std::cin >> op;\n        if (op == 0) {\n      \
    \      int x;\n            std::cin >> x;\n            heap.push(x);\n       \
    \ }\n        else if (op == 1) {\n            std::cout << heap.top_min() << \"\
    \\n\";\n            heap.pop_min();\n        }\n        else {\n            std::cout\
    \ << heap.top_max() << \"\\n\";\n            heap.pop_max();\n        }\n    }\n\
    }\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/MinMaxHeap.hpp
  - DataStructure/LazyDeleteHeap.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/double_ended_priority_queue.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 22:52:51+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/double_ended_priority_queue.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/double_ended_priority_queue.test.cpp
- /verify/test/1_library_checker/data_structure/double_ended_priority_queue.test.cpp.html
title: test/1_library_checker/data_structure/double_ended_priority_queue.test.cpp
---
