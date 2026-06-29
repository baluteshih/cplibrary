---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: Algebra/IterableOf.hpp
    title: Algebra/IterableOf.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Sequence/same_position.hpp\"\n\n#line 2 \"Algebra/IterableOf.hpp\"\
    \n\ntemplate <typename C, typename T>\nconcept IterableOf = std::ranges::range<C>\
    \ && std::same_as<std::ranges::range_value_t<C>, T>;\n#line 4 \"Sequence/same_position.hpp\"\
    \n\ntemplate<bool indexable_range = false, std::ranges::range C>\nstd::vector<int>\
    \ previous_same_position(const C &arr) {\n    using T = std::ranges::range_value_t<C>;\n\
    \    std::conditional_t<indexable_range, std::vector<int>, std::map<T, int>> prv;\n\
    \    if constexpr (indexable_range) prv.resize(*std::ranges::max_element(arr)\
    \ + 1);\n    std::vector<int> res(arr.size());\n    for (int i = 0; const auto\
    \ &v : arr)\n        res[i] = prv[v] - 1, prv[v] = ++i;\n    return res;\n}\n\n\
    template<bool indexable_range = false, std::ranges::range C>\nstd::vector<int>\
    \ next_same_position(const C &arr) {\n    std::vector<int> res = previous_same_position(arr\
    \ | std::views::reverse);\n    std::ranges::reverse(res);\n    for (int &i : res)\
    \ i = int(arr.size()) - i - 1;\n    return res;\n}\n"
  code: "#pragma once\n\n#include \"Algebra/IterableOf.hpp\"\n\ntemplate<bool indexable_range\
    \ = false, std::ranges::range C>\nstd::vector<int> previous_same_position(const\
    \ C &arr) {\n    using T = std::ranges::range_value_t<C>;\n    std::conditional_t<indexable_range,\
    \ std::vector<int>, std::map<T, int>> prv;\n    if constexpr (indexable_range)\
    \ prv.resize(*std::ranges::max_element(arr) + 1);\n    std::vector<int> res(arr.size());\n\
    \    for (int i = 0; const auto &v : arr)\n        res[i] = prv[v] - 1, prv[v]\
    \ = ++i;\n    return res;\n}\n\ntemplate<bool indexable_range = false, std::ranges::range\
    \ C>\nstd::vector<int> next_same_position(const C &arr) {\n    std::vector<int>\
    \ res = previous_same_position(arr | std::views::reverse);\n    std::ranges::reverse(res);\n\
    \    for (int &i : res) i = int(arr.size()) - i - 1;\n    return res;\n}\n"
  dependsOn:
  - Algebra/IterableOf.hpp
  isVerificationFile: false
  path: Sequence/same_position.hpp
  requiredBy: []
  timestamp: '2026-06-29 20:59:50+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Sequence/same_position.hpp
layout: document
redirect_from:
- /library/Sequence/same_position.hpp
- /library/Sequence/same_position.hpp.html
title: Sequence/same_position.hpp
---
