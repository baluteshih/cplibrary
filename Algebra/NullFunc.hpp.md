---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: Enumerate/bfs_enumerate.hpp
    title: Enumerate/bfs_enumerate.hpp
  - icon: ':heavy_check_mark:'
    path: Sequence/mo_solver.hpp
    title: Sequence/mo_solver.hpp
  - icon: ':x:'
    path: Tree/CentroidDS/DistanceSolver.hpp
    title: Tree/CentroidDS/DistanceSolver.hpp
  - icon: ':x:'
    path: Tree/CentroidTree.hpp
    title: Tree/CentroidTree.hpp
  - icon: ':x:'
    path: Tree/centroid_divide_and_conquer.hpp
    title: Tree/centroid_divide_and_conquer.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_range_mode_query.test.cpp
    title: test/1_library_checker/data_structure/static_range_mode_query.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
    title: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
    title: test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
    title: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/NullFunc.hpp\"\n\nstruct NullFunc {\n    constexpr\
    \ void operator()(auto&&...) const {}\n};\n"
  code: "#pragma once\n\nstruct NullFunc {\n    constexpr void operator()(auto&&...)\
    \ const {}\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/NullFunc.hpp
  requiredBy:
  - Tree/centroid_divide_and_conquer.hpp
  - Tree/CentroidTree.hpp
  - Tree/CentroidDS/DistanceSolver.hpp
  - Sequence/mo_solver.hpp
  - Enumerate/bfs_enumerate.hpp
  timestamp: '2026-06-18 20:44:31+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
  - test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
  - test/1_library_checker/data_structure/static_range_mode_query.test.cpp
documentation_of: Algebra/NullFunc.hpp
layout: document
redirect_from:
- /library/Algebra/NullFunc.hpp
- /library/Algebra/NullFunc.hpp.html
title: Algebra/NullFunc.hpp
---
