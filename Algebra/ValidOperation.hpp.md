---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: Graph/UnifiedWeight.hpp
    title: Graph/UnifiedWeight.hpp
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
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/tree_path_composite_sum.test.cpp
    title: test/1_library_checker/tree/tree_path_composite_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
    title: test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
    title: test/1_library_checker/tree/vertex_set_path_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"Algebra/ValidOperation.hpp\"\n\ntemplate<typename T, typename\
    \ Fallback>\nusing ReplaceVoid = std::conditional_t<std::same_as<T, void>, Fallback,\
    \ T>;\n\ntemplate <typename A, typename B>\nconcept ValidAddableState =\n    (!std::same_as<A,\
    \ void> || !std::same_as<B, void>) ||\n    requires(const ReplaceVoid<A, B>& a,\
    \ \n             const ReplaceVoid<B, A>& b) {\n        a + b;\n    };\n\ntemplate\
    \ <typename A, typename B>\nconcept ValidSubtractableState = \n    (!std::same_as<A,\
    \ void> || !std::same_as<B, void>) ||\n    requires(const ReplaceVoid<A, B>& a,\
    \ \n             const ReplaceVoid<B, A>& b) {\n        a - b;\n    };\n"
  code: "#pragma once\n\ntemplate<typename T, typename Fallback>\nusing ReplaceVoid\
    \ = std::conditional_t<std::same_as<T, void>, Fallback, T>;\n\ntemplate <typename\
    \ A, typename B>\nconcept ValidAddableState =\n    (!std::same_as<A, void> ||\
    \ !std::same_as<B, void>) ||\n    requires(const ReplaceVoid<A, B>& a, \n    \
    \         const ReplaceVoid<B, A>& b) {\n        a + b;\n    };\n\ntemplate <typename\
    \ A, typename B>\nconcept ValidSubtractableState = \n    (!std::same_as<A, void>\
    \ || !std::same_as<B, void>) ||\n    requires(const ReplaceVoid<A, B>& a, \n \
    \            const ReplaceVoid<B, A>& b) {\n        a - b;\n    };\n"
  dependsOn: []
  isVerificationFile: false
  path: Algebra/ValidOperation.hpp
  requiredBy:
  - Tree/Tree.hpp
  - Tree/HeavyLightDecomposition.hpp
  - Tree/TreeTools.hpp
  - Tree/all_direction_composition.hpp
  - Graph/UnifiedWeight.hpp
  timestamp: '2026-05-06 14:22:55+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/tree/vertex_add_path_sum.test.cpp
  - test/1_library_checker/tree/tree_path_composite_sum.test.cpp
  - test/1_library_checker/tree/lca.test.cpp
  - test/1_library_checker/tree/vertex_set_path_composite.test.cpp
  - test/1_library_checker/tree/tree_diameter.test.cpp
  - test/1_library_checker/tree/jump_on_tree.test.cpp
  - test/1_library_checker/tree/rooted_tree_isomorphism_classification.test.cpp
  - test/1_library_checker/tree/vertex_add_subtree_sum.test.cpp
documentation_of: Algebra/ValidOperation.hpp
layout: document
redirect_from:
- /library/Algebra/ValidOperation.hpp
- /library/Algebra/ValidOperation.hpp.html
title: Algebra/ValidOperation.hpp
---
