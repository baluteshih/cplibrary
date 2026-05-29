---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: Graph/UnifiedWeight.hpp
    title: Graph/UnifiedWeight.hpp
  - icon: ':question:'
    path: Tree/HeavyLightDecomposition.hpp
    title: Tree/HeavyLightDecomposition.hpp
  - icon: ':question:'
    path: Tree/Tree.hpp
    title: Tree/Tree.hpp
  - icon: ':heavy_check_mark:'
    path: Tree/TreeTools.hpp
    title: Tree/TreeTools.hpp
  - icon: ':x:'
    path: Tree/all_direction_composition.hpp
    title: Tree/all_direction_composition.hpp
  - icon: ':warning:'
    path: Tree/centroid_divide_and_conquer.hpp
    title: Tree/centroid_divide_and_conquer.hpp
  _extendedVerifiedWith:
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
  - icon: ':x:'
    path: test/1_library_checker/tree/tree_path_composite_sum.test.cpp
    title: test/1_library_checker/tree/tree_path_composite_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
  - icon: ':x:'
    path: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
    title: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/ValidOperation.hpp\"\n\ntemplate<typename T, typename\
    \ Fallback>\nusing ReplaceVoid = std::conditional_t<std::same_as<T, void>, Fallback,\
    \ T>;\n\ntemplate <typename A, typename B>\nconcept ValidAddableState =\n    requires(const\
    \ ReplaceVoid<A, B>& a, \n             const ReplaceVoid<B, A>& b) {\n       \
    \ a + b;\n    };\n\ntemplate <typename A, typename B>\nconcept ValidSubtractableState\
    \ = \n    requires(const ReplaceVoid<A, B>& a, \n             const ReplaceVoid<B,\
    \ A>& b) {\n        a - b;\n    };\n"
  code: "#pragma once\n\ntemplate<typename T, typename Fallback>\nusing ReplaceVoid\
    \ = std::conditional_t<std::same_as<T, void>, Fallback, T>;\n\ntemplate <typename\
    \ A, typename B>\nconcept ValidAddableState =\n    requires(const ReplaceVoid<A,\
    \ B>& a, \n             const ReplaceVoid<B, A>& b) {\n        a + b;\n    };\n\
    \ntemplate <typename A, typename B>\nconcept ValidSubtractableState = \n    requires(const\
    \ ReplaceVoid<A, B>& a, \n             const ReplaceVoid<B, A>& b) {\n       \
    \ a - b;\n    };\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/ValidOperation.hpp
  requiredBy:
  - Tree/centroid_divide_and_conquer.hpp
  - Tree/Tree.hpp
  - Tree/HeavyLightDecomposition.hpp
  - Tree/all_direction_composition.hpp
  - Tree/TreeTools.hpp
  - Graph/UnifiedWeight.hpp
  timestamp: '2026-05-19 13:54:46+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
  - test/1_library_checker/tree/lca.test.cpp
  - test/1_library_checker/tree/jump_on_tree.test.cpp
  - test/1_library_checker/tree/tree_path_composite_sum.test.cpp
  - test/1_library_checker/tree/vertex_set_path_composite.test.cpp
  - test/1_library_checker/tree/tree_diameter.test.cpp
  - test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
documentation_of: Algebra/ValidOperation.hpp
layout: document
redirect_from:
- /library/Algebra/ValidOperation.hpp
- /library/Algebra/ValidOperation.hpp.html
title: Algebra/ValidOperation.hpp
---
