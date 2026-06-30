---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  _extendedRequiredBy:
  - icon: ':question:'
    path: DataStructure/BIT.hpp
    title: Binary Indexed Tree (BIT)
  - icon: ':heavy_check_mark:'
    path: DataStructure/CatTree.hpp
    title: Cat Tree
  - icon: ':heavy_check_mark:'
    path: DataStructure/DisjointSet.hpp
    title: Disjoint Set Union (DSU)
  - icon: ':heavy_check_mark:'
    path: DataStructure/Doubling.hpp
    title: Doubling
  - icon: ':heavy_check_mark:'
    path: DataStructure/OrderedSet.hpp
    title: Ordered Set
  - icon: ':heavy_check_mark:'
    path: DataStructure/PotentialDisjointSet.hpp
    title: Potential Disjoint Set
  - icon: ':heavy_check_mark:'
    path: DataStructure/SparseTable.hpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: Geometry/PointInAngle.hpp
    title: Geometry/PointInAngle.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/minimum_arborescence.hpp
    title: Graph/minimum_arborescence.hpp
  - icon: ':heavy_check_mark:'
    path: Graph/minimum_spanning_tree.hpp
    title: Graph/minimum_spanning_tree.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/TreeTools.hpp
    title: Tree/TreeTools.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set.test.cpp
    title: test/1_library_checker/data_structure/ordered_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
    title: test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
    title: test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/unionfind.test.cpp
    title: test/1_library_checker/data_structure/unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/unionfind_with_potential.test.cpp
    title: test/1_library_checker/data_structure/unionfind_with_potential.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
    title: test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/geometry/count_points_in_triangle.test.cpp
    title: test/1_library_checker/geometry/count_points_in_triangle.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp
    title: test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/directedmst.test.cpp
    title: test/1_library_checker/graph/directedmst.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
    title: test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/incremental_scc.test.cpp
    title: test/1_library_checker/graph/incremental_scc.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/minimum_spanning_tree.test.cpp
    title: test/1_library_checker/graph/minimum_spanning_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/jump_on_tree.test.cpp
    title: test/1_library_checker/tree/jump_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/lca.test.cpp
    title: test/1_library_checker/tree/lca.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
    title: test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
    title: test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: '#line 2 "Algebra/Monoid/concept.hpp"


    #line 2 "Algebra/ValidOperation.hpp"


    template <typename A, typename B>

    concept Addable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B
    b) { a + b; };


    template <typename A, typename B>

    concept Subtractable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A
    a, B b) { a - b; };


    template <typename A, typename B>

    concept Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A
    a, B b) { a * b; };

    #line 4 "Algebra/Monoid/concept.hpp"


    template<typename T>

    concept isMonoid = Addable<T, T> && std::default_initializable<T>;


    template<typename T>

    concept isCommutativeMonoid = isMonoid<T>;

    '
  code: '#pragma once


    #include "Algebra/ValidOperation.hpp"


    template<typename T>

    concept isMonoid = Addable<T, T> && std::default_initializable<T>;


    template<typename T>

    concept isCommutativeMonoid = isMonoid<T>;

    '
  dependsOn:
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: Algebra/Monoid/concept.hpp
  requiredBy:
  - Graph/minimum_arborescence.hpp
  - Graph/minimum_spanning_tree.hpp
  - Tree/TreeTools.hpp
  - DataStructure/BIT.hpp
  - DataStructure/Doubling.hpp
  - DataStructure/OrderedSet.hpp
  - DataStructure/DisjointSet.hpp
  - DataStructure/SparseTable.hpp
  - DataStructure/CatTree.hpp
  - DataStructure/PotentialDisjointSet.hpp
  - Geometry/PointInAngle.hpp
  timestamp: '2026-06-30 17:38:58+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/1_library_checker/tree/lca.test.cpp
  - test/1_library_checker/tree/vertex_add_range_contour_sum_on_tree.test.cpp
  - test/1_library_checker/tree/vertex_get_range_contour_add_on_tree.test.cpp
  - test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
  - test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - test/1_library_checker/tree/jump_on_tree.test.cpp
  - test/1_library_checker/geometry/count_points_in_triangle.test.cpp
  - test/1_library_checker/data_structure/unionfind.test.cpp
  - test/1_library_checker/data_structure/static_rmq_cattree.test.cpp
  - test/1_library_checker/data_structure/unionfind_with_potential.test.cpp
  - test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
  - test/1_library_checker/data_structure/ordered_set.test.cpp
  - test/1_library_checker/data_structure/static_rmq_sparsetable.test.cpp
  - test/1_library_checker/graph/dynamic_graph_vertex_add_component_sum.test.cpp
  - test/1_library_checker/graph/connected_components_of_complement_graph.test.cpp
  - test/1_library_checker/graph/directedmst.test.cpp
  - test/1_library_checker/graph/minimum_spanning_tree.test.cpp
  - test/1_library_checker/graph/incremental_scc.test.cpp
documentation_of: Algebra/Monoid/concept.hpp
layout: document
redirect_from:
- /library/Algebra/Monoid/concept.hpp
- /library/Algebra/Monoid/concept.hpp.html
title: Algebra/Monoid/concept.hpp
---
