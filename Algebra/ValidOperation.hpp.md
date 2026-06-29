---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: DataStructure/LeftistTree.hpp
    title: Leftist Tree
  - icon: ':heavy_check_mark:'
    path: Graph/UnifiedWeight.hpp
    title: Graph/UnifiedWeight.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/minimum_arborescence.hpp
    title: Graph/minimum_arborescence.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/CentroidDS/DistanceSolver.hpp
    title: Tree/CentroidDS/DistanceSolver.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/CentroidTree.hpp
    title: Tree/CentroidTree.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/HeavyLightDecomposition.hpp
    title: Tree/HeavyLightDecomposition.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/Tree.hpp
    title: Tree/Tree.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/TreeTools.hpp
    title: Tree/TreeTools.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/all_direction_composition.hpp
    title: Tree/all_direction_composition.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/centroid_divide_and_conquer.hpp
    title: Tree/centroid_divide_and_conquer.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/directedmst.test.cpp
    title: test/1_library_checker/graph/directedmst.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
    title: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/jump_on_tree.test.cpp
    title: test/1_library_checker/tree/jump_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/lca.test.cpp
    title: test/1_library_checker/tree/lca.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
    title: test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/tree_diameter.test.cpp
    title: test/1_library_checker/tree/tree_diameter.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/tree_path_composite_sum.test.cpp
    title: test/1_library_checker/tree/tree_path_composite_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
    title: test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
    title: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
    title: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: '#line 2 "Algebra/ValidOperation.hpp"


    template<typename T, typename Fallback>

    using ReplaceVoid = std::conditional_t<std::same_as<T, void>, Fallback, T>;


    template <typename A, typename B>

    concept ValidAddableState = requires(A a, B b) { a + b; };


    template <typename A, typename B>

    concept ValidSubtractableState = requires(A a, B b) { a - b; };

    '
  code: '#pragma once


    template<typename T, typename Fallback>

    using ReplaceVoid = std::conditional_t<std::same_as<T, void>, Fallback, T>;


    template <typename A, typename B>

    concept ValidAddableState = requires(A a, B b) { a + b; };


    template <typename A, typename B>

    concept ValidSubtractableState = requires(A a, B b) { a - b; };

    '
  dependsOn: []
  isVerificationFile: false
  path: Algebra/ValidOperation.hpp
  requiredBy:
  - Graph/minimum_arborescence.hpp
  - Graph/UnifiedWeight.hpp
  - Tree/Tree.hpp
  - Tree/centroid_divide_and_conquer.hpp
  - Tree/all_direction_composition.hpp
  - Tree/CentroidTree.hpp
  - Tree/HeavyLightDecomposition.hpp
  - Tree/CentroidDS/DistanceSolver.hpp
  - Tree/TreeTools.hpp
  - DataStructure/LeftistTree.hpp
  timestamp: '2026-06-29 20:34:17+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
  - test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
  - test/1_library_checker/tree/lca.test.cpp
  - test/1_library_checker/tree/vertex_set_path_composite.test.cpp
  - test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
  - test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
  - test/1_library_checker/tree/tree_diameter.test.cpp
  - test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - test/1_library_checker/tree/jump_on_tree.test.cpp
  - test/1_library_checker/tree/tree_path_composite_sum.test.cpp
  - test/1_library_checker/graph/directedmst.test.cpp
documentation_of: Algebra/ValidOperation.hpp
layout: document
redirect_from:
- /library/Algebra/ValidOperation.hpp
- /library/Algebra/ValidOperation.hpp.html
title: Algebra/ValidOperation.hpp
---
