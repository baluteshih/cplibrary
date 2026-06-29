---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/IterableOf.hpp
    title: Algebra/IterableOf.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_range_frequency.test.cpp
    title: test/1_library_checker/data_structure/static_range_frequency.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Sequence/occur_position.hpp\"\n\n#line 2 \"Algebra/IterableOf.hpp\"\
    \n\ntemplate <typename C, typename T>\nconcept IterableOf = std::ranges::range<C>\
    \ && std::same_as<std::ranges::range_value_t<C>, T>;\n#line 4 \"Sequence/occur_position.hpp\"\
    \n\ntemplate<bool indexable_range = false, std::ranges::range C>\nstd::conditional_t<indexable_range,\
    \ std::vector<std::vector<int>>, std::map<std::ranges::range_value_t<C>, std::vector<int>>>\
    \ occur_position(const C &arr) {\n    std::conditional_t<indexable_range, std::vector<std::vector<int>>,\
    \ std::map<std::ranges::range_value_t<C>, std::vector<int>>> res;\n    if constexpr\
    \ (indexable_range) res.resize(*std::ranges::max_element(arr) + 1);\n    for (int\
    \ i = 0; const auto &v : arr)\n        res[v].push_back(i++);\n    return res;\n\
    }\n"
  code: "#pragma once\n\n#include \"Algebra/IterableOf.hpp\"\n\ntemplate<bool indexable_range\
    \ = false, std::ranges::range C>\nstd::conditional_t<indexable_range, std::vector<std::vector<int>>,\
    \ std::map<std::ranges::range_value_t<C>, std::vector<int>>> occur_position(const\
    \ C &arr) {\n    std::conditional_t<indexable_range, std::vector<std::vector<int>>,\
    \ std::map<std::ranges::range_value_t<C>, std::vector<int>>> res;\n    if constexpr\
    \ (indexable_range) res.resize(*std::ranges::max_element(arr) + 1);\n    for (int\
    \ i = 0; const auto &v : arr)\n        res[v].push_back(i++);\n    return res;\n\
    }\n"
  dependsOn:
  - Algebra/IterableOf.hpp
  isVerificationFile: false
  path: Sequence/occur_position.hpp
  requiredBy: []
  timestamp: '2026-06-29 21:10:18+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/static_range_frequency.test.cpp
documentation_of: Sequence/occur_position.hpp
layout: document
redirect_from:
- /library/Sequence/occur_position.hpp
- /library/Sequence/occur_position.hpp.html
title: Sequence/occur_position.hpp
---
