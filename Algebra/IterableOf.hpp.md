---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Sequence/occur_position.hpp
    title: Sequence/occur_position.hpp
  - icon: ':warning:'
    path: Sequence/same_position.hpp
    title: Sequence/same_position.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_range_frequency.test.cpp
    title: test/1_library_checker/data_structure/static_range_frequency.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: '#line 2 "Algebra/IterableOf.hpp"


    template <typename C, typename T>

    concept IterableOf = std::ranges::range<C> && std::same_as<std::ranges::range_value_t<C>,
    T>;

    '
  code: '#pragma once


    template <typename C, typename T>

    concept IterableOf = std::ranges::range<C> && std::same_as<std::ranges::range_value_t<C>,
    T>;

    '
  dependsOn: []
  isVerificationFile: false
  path: Algebra/IterableOf.hpp
  requiredBy:
  - Sequence/occur_position.hpp
  - Sequence/same_position.hpp
  timestamp: '2026-06-29 20:59:50+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/static_range_frequency.test.cpp
documentation_of: Algebra/IterableOf.hpp
layout: document
redirect_from:
- /library/Algebra/IterableOf.hpp
- /library/Algebra/IterableOf.hpp.html
title: Algebra/IterableOf.hpp
---
