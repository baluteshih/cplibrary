---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: Sequence/same_position.hpp
    title: Sequence/same_position.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
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
  - Sequence/same_position.hpp
  timestamp: '2026-06-29 20:59:50+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: Algebra/IterableOf.hpp
layout: document
redirect_from:
- /library/Algebra/IterableOf.hpp
- /library/Algebra/IterableOf.hpp.html
title: Algebra/IterableOf.hpp
---
