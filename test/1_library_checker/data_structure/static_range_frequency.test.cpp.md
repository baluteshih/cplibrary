---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/IterableOf.hpp
    title: Algebra/IterableOf.hpp
  - icon: ':heavy_check_mark:'
    path: Sequence/occur_position.hpp
    title: Sequence/occur_position.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_frequency
    links:
    - https://judge.yosupo.jp/problem/static_range_frequency
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/static_range_frequency.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\n\
    #line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/data_structure/static_range_frequency.test.cpp\"\n\
    \n#line 2 \"Sequence/occur_position.hpp\"\n\n#line 2 \"Algebra/IterableOf.hpp\"\
    \n\ntemplate <typename C, typename T>\nconcept IterableOf = std::ranges::range<C>\
    \ && std::same_as<std::ranges::range_value_t<C>, T>;\n#line 4 \"Sequence/occur_position.hpp\"\
    \n\ntemplate<bool indexable_range = false, std::ranges::range C>\nstd::conditional_t<indexable_range,\
    \ std::vector<std::vector<int>>, std::map<std::ranges::range_value_t<C>, std::vector<int>>>\
    \ occur_position(const C &arr) {\n    std::conditional_t<indexable_range, std::vector<std::vector<int>>,\
    \ std::map<std::ranges::range_value_t<C>, std::vector<int>>> res;\n    if constexpr\
    \ (indexable_range) res.resize(*std::ranges::max_element(arr) + 1);\n    for (int\
    \ i = 0; const auto &v : arr)\n        res[v].push_back(i++);\n    return res;\n\
    }\n#line 5 \"test/1_library_checker/data_structure/static_range_frequency.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    std::vector<int> arr(n);\n    for (int &i\
    \ : arr) std::cin >> i;\n    auto pos = occur_position(arr);\n    while (q--)\
    \ {\n        int l, r, x;\n        std::cin >> l >> r >> x;\n        auto it =\
    \ pos.find(x);\n        if (it == pos.end()) std::cout << \"0\\n\";\n        else\
    \ std::cout << std::ranges::lower_bound(it->second, r) - std::ranges::lower_bound(it->second,\
    \ l) << \"\\n\"; \n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_frequency\"\
    \n#include \"assumption.hpp\"\n\n#include \"Sequence/occur_position.hpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n\
    \    std::cin >> n >> q;\n    std::vector<int> arr(n);\n    for (int &i : arr)\
    \ std::cin >> i;\n    auto pos = occur_position(arr);\n    while (q--) {\n   \
    \     int l, r, x;\n        std::cin >> l >> r >> x;\n        auto it = pos.find(x);\n\
    \        if (it == pos.end()) std::cout << \"0\\n\";\n        else std::cout <<\
    \ std::ranges::lower_bound(it->second, r) - std::ranges::lower_bound(it->second,\
    \ l) << \"\\n\"; \n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Sequence/occur_position.hpp
  - Algebra/IterableOf.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/static_range_frequency.test.cpp
  requiredBy: []
  timestamp: '2026-06-29 21:10:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/static_range_frequency.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/static_range_frequency.test.cpp
- /verify/test/1_library_checker/data_structure/static_range_frequency.test.cpp.html
title: test/1_library_checker/data_structure/static_range_frequency.test.cpp
---
