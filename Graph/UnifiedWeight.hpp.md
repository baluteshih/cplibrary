---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  _extendedRequiredBy:
  - icon: ':x:'
    path: Tree/CentroidDS/DistanceSolver.hpp
    title: Tree/CentroidDS/DistanceSolver.hpp
  - icon: ':x:'
    path: Tree/CentroidTree.hpp
    title: Tree/CentroidTree.hpp
  - icon: ':x:'
    path: Tree/HeavyLightDecomposition.hpp
    title: Tree/HeavyLightDecomposition.hpp
  - icon: ':x:'
    path: Tree/Tree.hpp
    title: Tree/Tree.hpp
  - icon: ':x:'
    path: Tree/TreeTools.hpp
    title: Tree/TreeTools.hpp
  - icon: ':x:'
    path: Tree/all_direction_composition.hpp
    title: Tree/all_direction_composition.hpp
  - icon: ':x:'
    path: Tree/centroid_divide_and_conquer.hpp
    title: Tree/centroid_divide_and_conquer.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/1_library_checker/graph/directedmst.test.cpp
    title: test/1_library_checker/graph/directedmst.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
    title: test/1_library_checker/tree/frequency_table_of_tree_distance.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/jump_on_tree.test.cpp
    title: test/1_library_checker/tree/jump_on_tree.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/lca.test.cpp
    title: test/1_library_checker/tree/lca.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
    title: test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/tree_diameter.test.cpp
    title: test/1_library_checker/tree/tree_diameter.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/tree_path_composite_sum.test.cpp
    title: test/1_library_checker/tree/tree_path_composite_sum.test.cpp
  - icon: ':x:'
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
  - icon: ':x:'
    path: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
    title: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Graph/UnifiedWeight.hpp\"\n\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate <typename A, typename B>\nconcept Addable = !std::is_void_v<A> &&\
    \ !std::is_void_v<B> && requires(A a, B b) { a + b; };\n\ntemplate <typename A,\
    \ typename B>\nconcept Subtractable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a - b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a * b; };\n#line 4 \"Graph/UnifiedWeight.hpp\"\n\ntemplate <typename Edge,\
    \ typename Vertex>\nstruct UnifiedWeight {\n    using type = std::conditional_t<std::is_void_v<Vertex>,\
    \ Edge, Vertex>;\n};\n\ntemplate <typename Edge, typename Vertex>\nusing UnifiedWeight_t\
    \ = typename UnifiedWeight<Edge, Vertex>::type;\n\ntemplate <typename Edge, typename\
    \ Vertex>\nconcept ValidAddableUnifiedWeight = \n    (std::is_void_v<Vertex> &&\
    \ Addable<Edge, Edge>) ||\n    (Addable<Vertex, Vertex> && (std::is_void_v<Edge>\
    \ || Addable<Vertex, Edge>));\n"
  code: "#pragma once\n\n#include \"Algebra/ValidOperation.hpp\"\n\ntemplate <typename\
    \ Edge, typename Vertex>\nstruct UnifiedWeight {\n    using type = std::conditional_t<std::is_void_v<Vertex>,\
    \ Edge, Vertex>;\n};\n\ntemplate <typename Edge, typename Vertex>\nusing UnifiedWeight_t\
    \ = typename UnifiedWeight<Edge, Vertex>::type;\n\ntemplate <typename Edge, typename\
    \ Vertex>\nconcept ValidAddableUnifiedWeight = \n    (std::is_void_v<Vertex> &&\
    \ Addable<Edge, Edge>) ||\n    (Addable<Vertex, Vertex> && (std::is_void_v<Edge>\
    \ || Addable<Vertex, Edge>));\n"
  dependsOn:
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: Graph/UnifiedWeight.hpp
  requiredBy:
  - Tree/Tree.hpp
  - Tree/centroid_divide_and_conquer.hpp
  - Tree/all_direction_composition.hpp
  - Tree/CentroidTree.hpp
  - Tree/HeavyLightDecomposition.hpp
  - Tree/CentroidDS/DistanceSolver.hpp
  - Tree/TreeTools.hpp
  timestamp: '2026-06-30 17:03:55+08:00'
  verificationStatus: LIBRARY_ALL_WA
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
documentation_of: Graph/UnifiedWeight.hpp
layout: document
redirect_from:
- /library/Graph/UnifiedWeight.hpp
- /library/Graph/UnifiedWeight.hpp.html
title: Graph/UnifiedWeight.hpp
---
