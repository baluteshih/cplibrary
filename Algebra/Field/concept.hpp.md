---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Graph/count_spanning_tree.hpp
    title: Graph/count_spanning_tree.hpp
  - icon: ':heavy_check_mark:'
    path: Matrix/Matrix.hpp
    title: Matrix/Matrix.hpp
  - icon: ':heavy_check_mark:'
    path: Matrix/Vector.hpp
    title: Matrix/Vector.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
    title: test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/counting_spanning_tree_directed.test.cpp
    title: test/1_library_checker/graph/counting_spanning_tree_directed.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp
    title: test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/inverse_matrix.test.cpp
    title: test/1_library_checker/linear_algebra/inverse_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_det.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_det.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_det_arbitrary_mod.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_det_arbitrary_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_product.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/matrix_rank.test.cpp
    title: test/1_library_checker/linear_algebra/matrix_rank.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/pow_of_matrix.test.cpp
    title: test/1_library_checker/linear_algebra/pow_of_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/linear_algebra/system_of_linear_equations.test.cpp
    title: test/1_library_checker/linear_algebra/system_of_linear_equations.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: '#line 2 "Algebra/Field/concept.hpp"


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

    #line 4 "Algebra/Field/concept.hpp"


    template<typename T>

    concept isField = Addable<T, T> && Multiplicable<T, T> && std::default_initializable<T>;

    '
  code: '#pragma once


    #include "Algebra/ValidOperation.hpp"


    template<typename T>

    concept isField = Addable<T, T> && Multiplicable<T, T> && std::default_initializable<T>;

    '
  dependsOn:
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: Algebra/Field/concept.hpp
  requiredBy:
  - Graph/count_spanning_tree.hpp
  - Matrix/Vector.hpp
  - Matrix/Matrix.hpp
  timestamp: '2026-06-30 17:03:55+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/linear_algebra/pow_of_matrix.test.cpp
  - test/1_library_checker/linear_algebra/inverse_matrix.test.cpp
  - test/1_library_checker/linear_algebra/matrix_det.test.cpp
  - test/1_library_checker/linear_algebra/system_of_linear_equations.test.cpp
  - test/1_library_checker/linear_algebra/matrix_rank.test.cpp
  - test/1_library_checker/linear_algebra/matrix_product.test.cpp
  - test/1_library_checker/linear_algebra/matrix_det_arbitrary_mod.test.cpp
  - test/1_library_checker/data_structure/unionfind_with_potential_non_commutative_group.test.cpp
  - test/1_library_checker/graph/counting_spanning_tree_directed.test.cpp
  - test/1_library_checker/graph/counting_spanning_tree_undirected.test.cpp
documentation_of: Algebra/Field/concept.hpp
layout: document
redirect_from:
- /library/Algebra/Field/concept.hpp
- /library/Algebra/Field/concept.hpp.html
title: Algebra/Field/concept.hpp
---
