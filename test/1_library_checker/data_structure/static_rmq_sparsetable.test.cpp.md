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
    path: DataStructure/Doubling.hpp
    title: Doubling
  - icon: ':heavy_check_mark:'
    path: DataStructure/SparseTable.hpp
    title: Sparse Table
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
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#line 2 \"assumption.hpp\"\
    \n\n#include <cassert>\n#include <bits/stdc++.h>\n#line 3 \"test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp\"\
    \n\n#line 2 \"DataStructure/SparseTable.hpp\"\n\n#line 2 \"DataStructure/Doubling.hpp\"\
    \n\n#line 2 \"Algebra/Monoid/concept.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate <typename A, typename B>\nconcept Addable = !std::is_void_v<A> &&\
    \ !std::is_void_v<B> && requires(A a, B b) { a + b; };\n\ntemplate <typename A,\
    \ typename B>\nconcept Subtractable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a - b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a * b; };\n#line 4 \"Algebra/Monoid/concept.hpp\"\n\ntemplate<typename\
    \ T>\nconcept isMonoid = Addable<T, T> && std::default_initializable<T>;\n\ntemplate<typename\
    \ T>\nconcept isCommutativeMonoid = isMonoid<T>;\n#line 4 \"DataStructure/Doubling.hpp\"\
    \n\ntemplate<class Value, bool ImplicitJump = false>\nclass Doubling {\n    struct\
    \ Empty {};\n    static constexpr bool hasValue = isMonoid<Value>;\n    static_assert(hasValue\
    \ || !ImplicitJump);\n    inline int get_nxt(int j, int i) const {\n        if\
    \ constexpr (ImplicitJump) return std::min(n - 1, i + (1 << j));\n        else\
    \ return nxt[j][i];\n    }\n    void build() {\n        for (int j = 1; j < max_log;\
    \ ++j)\n            for (int i = 0; i < n; ++i) {\n                if constexpr\
    \ (!ImplicitJump) nxt[j][i] = nxt[j - 1][nxt[j - 1][i]];\n                if constexpr\
    \ (hasValue) val[j][i] = val[j - 1][i] + val[j - 1][get_nxt(j - 1, i)]; \n   \
    \         }\n    }\npublic:\n    int n, max_log;\n    [[no_unique_address]] std::conditional_t<ImplicitJump,\
    \ Empty, std::vector<std::vector<int>>> nxt;\n    [[no_unique_address]] std::conditional_t<hasValue,\
    \ std::vector<std::vector<Value>>, Empty> val; \n    Doubling() : n(0), max_log(0)\
    \ {}\n    Doubling(int _n, const std::ranges::range auto &init_nxt) requires (!hasValue\
    \ && !ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned int>(n))\
    \ + 1) { \n        nxt.assign(max_log, std::vector<int>(n)); \n        std::ranges::copy(init_nxt,\
    \ nxt[0].begin());\n        build(); \n    }\n    Doubling(int _n, const std::ranges::range\
    \ auto &init_val) requires (hasValue && ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned\
    \ int>(n)) + 1) { \n        val.assign(max_log, std::vector<Value>(n)); \n   \
    \     std::ranges::copy(init_val, val[0].begin());\n        build(); \n    }\n\
    \    Doubling(int _n, const std::ranges::range auto &init_nxt, const std::ranges::range\
    \ auto &init_val) requires (hasValue && !ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned\
    \ int>(n)) + 1) { \n        nxt.assign(max_log, std::vector<int>(n)); \n     \
    \   val.assign(max_log, std::vector<Value>(n)); \n        std::ranges::copy(init_nxt,\
    \ nxt[0].begin());\n        std::ranges::copy(init_val, val[0].begin());\n   \
    \     build(); \n    }\n    template<typename F_cond>\n    int maximal_prefix(int\
    \ u, F_cond cond) {\n        if (!cond(u)) return -1;\n        for (int i = max_log\
    \ - 1; i >= 0; --i)\n            if (cond(get_nxt(i, u)))\n                u =\
    \ get_nxt(i, u);\n        return u;\n    }\n    template<typename F_cond>\n  \
    \  auto maximal_prefix_prod(int u, F_cond cond) requires (hasValue) {\n      \
    \  if (!cond(u)) return std::make_pair(Value(), -1);\n        Value res = Value();\n\
    \        for (int i = max_log - 1; i >= 0; --i)\n            if (cond(get_nxt(i,\
    \ u))) {\n                res = res + val[i][u];\n                u = get_nxt(i,\
    \ u);\n            }\n        return std::make_pair(res, u);\n    }\n    int step(int\
    \ u, int d) {\n        for (; d; d -= d & -d) u = get_nxt(std::__lg(d & -d), u);\n\
    \        return u;\n    }\n};\n#line 4 \"DataStructure/SparseTable.hpp\"\n\ntemplate<typename\
    \ Value = int>\nclass SparseTable {\n    int n;\n    Doubling<Value, true> table;\n\
    public:\n    SparseTable(const std::ranges::range auto &data) : n(data.size()),\
    \ table(n, data) {} \n    Value range_prod(int l, int r) {\n        assert(0 <=\
    \ l && r <= n);\n        assert(l <= r);\n        if (l == r) return Value();\n\
    \        int lg = std::__lg(r - l);\n        return table.val[lg][l] + table.val[lg][r\
    \ - (1 << lg)];\n    }\n};\n#line 5 \"test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp\"\
    \n\nstruct Value {\n    int val;\n    Value(int _v = 2'000'000'000): val(_v) {}\n\
    \    Value operator+(const Value &rhs) const {\n        return Value(std::min(val,\
    \ rhs.val));\n    }\n    friend std::ostream& operator<<(std::ostream& os, const\
    \ Value &v) {\n        os << v.val;\n        return os;\n    }\n    friend std::istream&\
    \ operator>>(std::istream& is, Value &v) {\n        is >> v.val;\n        return\
    \ is;\n    }\n};\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<Value> arr(n);\n    for\
    \ (auto &i : arr)\n        std::cin >> i;\n    SparseTable<Value> table(arr);\n\
    \    while (q--) {\n        int l, r;\n        std::cin >> l >> r;\n        std::cout\
    \ << table.range_prod(l, r) << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#include \"\
    assumption.hpp\"\n\n#include \"DataStructure/SparseTable.hpp\"\n\nstruct Value\
    \ {\n    int val;\n    Value(int _v = 2'000'000'000): val(_v) {}\n    Value operator+(const\
    \ Value &rhs) const {\n        return Value(std::min(val, rhs.val));\n    }\n\
    \    friend std::ostream& operator<<(std::ostream& os, const Value &v) {\n   \
    \     os << v.val;\n        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, Value &v) {\n        is >> v.val;\n        return is;\n    }\n};\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n\
    \    std::cin >> n >> q;\n    std::vector<Value> arr(n);\n    for (auto &i : arr)\n\
    \        std::cin >> i;\n    SparseTable<Value> table(arr);\n    while (q--) {\n\
    \        int l, r;\n        std::cin >> l >> r;\n        std::cout << table.range_prod(l,\
    \ r) << \"\\n\";\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/SparseTable.hpp
  - DataStructure/Doubling.hpp
  - Algebra/Monoid/concept.hpp
  - Algebra/ValidOperation.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
  requiredBy: []
  timestamp: '2026-06-30 17:38:58+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
- /verify/test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp.html
title: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
---
