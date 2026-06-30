---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/Field/concept.hpp
    title: Algebra/Field/concept.hpp
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
  bundledCode: "#line 2 \"Matrix/Vector.hpp\"\n\n#line 2 \"Algebra/Field/concept.hpp\"\
    \n\n#line 2 \"Algebra/ValidOperation.hpp\"\n\ntemplate <typename A, typename B>\n\
    concept Addable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a + b; };\n\ntemplate <typename A, typename B>\nconcept Subtractable =\
    \ !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a - b; };\n\
    \ntemplate <typename A, typename B>\nconcept Multiplicable = !std::is_void_v<A>\
    \ && !std::is_void_v<B> && requires(A a, B b) { a * b; };\n#line 4 \"Algebra/Field/concept.hpp\"\
    \n\ntemplate<typename T>\nconcept isField = Addable<T, T> && Multiplicable<T,\
    \ T> && std::default_initializable<T>;\n#line 4 \"Matrix/Vector.hpp\"\n\ntemplate<typename\
    \ T, class Allocator = std::allocator<T>>\nrequires isField<T>\nclass Vector :\
    \ public std::vector<T, Allocator> {\n    int n() const { return (int)this->size();\
    \ }\npublic:\n    Vector(int _n): std::vector<T, Allocator>(_n) {}\n    Vector&\
    \ operator*=(const T &v) {\n        for (int i = 0; i < n(); ++i)\n          \
    \  (*this)[i] = (*this)[i] * v;\n        return *this;\n    }\n    Vector& operator/=(const\
    \ T &v) {\n        for (int i = 0; i < n(); ++i)\n            (*this)[i] = (*this)[i]\
    \ / v;\n        return *this;\n    }\n    Vector& operator+=(const Vector &rhs)\
    \ {\n        assert(n() == rhs.n());\n        for (int i = 0; i < n(); ++i)\n\
    \            (*this)[i] = (*this)[i] + rhs[i];\n        return *this;\n    }\n\
    \    Vector& operator-=(const Vector &rhs) {\n        assert(n() == rhs.n());\n\
    \        for (int i = 0; i < n(); ++i)\n            (*this)[i] = (*this)[i] -\
    \ rhs[i];\n        return *this;\n    }\n    T operator*(const Vector &rhs) const\
    \ {\n        assert(n() == rhs.n());\n        T res = T();\n        for (int i\
    \ = 0; i < n(); ++i)\n            res = res + (*this)[i] * rhs[i];\n        return\
    \ res;\n    }\n    Vector& operator|=(Vector const& rhs) {\n        this->insert(this->end(),\
    \ rhs.begin(), rhs.end());\n        return *this;\n    }\n    Vector operator*(const\
    \ T &v) const { return Vector(*this) *= v; }\n    Vector operator/(const T &v)\
    \ const { return Vector(*this) /= v; }\n    Vector operator+(const Vector &rhs)\
    \ const { return Vector(*this) += rhs; }\n    Vector operator-(const Vector &rhs)\
    \ const { return Vector(*this) -= rhs; }\n    Vector operator|(Vector const& rhs)\
    \ const { return Vector(*this) |= rhs; }\n    int find_pivot() {\n        int\
    \ pivot = 0;\n        while (pivot < n() && (*this)[pivot] == T(0)) ++pivot;\n\
    \        return pivot;\n    }\n};\n"
  code: "#pragma once\n\n#include \"Algebra/Field/concept.hpp\"\n\ntemplate<typename\
    \ T, class Allocator = std::allocator<T>>\nrequires isField<T>\nclass Vector :\
    \ public std::vector<T, Allocator> {\n    int n() const { return (int)this->size();\
    \ }\npublic:\n    Vector(int _n): std::vector<T, Allocator>(_n) {}\n    Vector&\
    \ operator*=(const T &v) {\n        for (int i = 0; i < n(); ++i)\n          \
    \  (*this)[i] = (*this)[i] * v;\n        return *this;\n    }\n    Vector& operator/=(const\
    \ T &v) {\n        for (int i = 0; i < n(); ++i)\n            (*this)[i] = (*this)[i]\
    \ / v;\n        return *this;\n    }\n    Vector& operator+=(const Vector &rhs)\
    \ {\n        assert(n() == rhs.n());\n        for (int i = 0; i < n(); ++i)\n\
    \            (*this)[i] = (*this)[i] + rhs[i];\n        return *this;\n    }\n\
    \    Vector& operator-=(const Vector &rhs) {\n        assert(n() == rhs.n());\n\
    \        for (int i = 0; i < n(); ++i)\n            (*this)[i] = (*this)[i] -\
    \ rhs[i];\n        return *this;\n    }\n    T operator*(const Vector &rhs) const\
    \ {\n        assert(n() == rhs.n());\n        T res = T();\n        for (int i\
    \ = 0; i < n(); ++i)\n            res = res + (*this)[i] * rhs[i];\n        return\
    \ res;\n    }\n    Vector& operator|=(Vector const& rhs) {\n        this->insert(this->end(),\
    \ rhs.begin(), rhs.end());\n        return *this;\n    }\n    Vector operator*(const\
    \ T &v) const { return Vector(*this) *= v; }\n    Vector operator/(const T &v)\
    \ const { return Vector(*this) /= v; }\n    Vector operator+(const Vector &rhs)\
    \ const { return Vector(*this) += rhs; }\n    Vector operator-(const Vector &rhs)\
    \ const { return Vector(*this) -= rhs; }\n    Vector operator|(Vector const& rhs)\
    \ const { return Vector(*this) |= rhs; }\n    int find_pivot() {\n        int\
    \ pivot = 0;\n        while (pivot < n() && (*this)[pivot] == T(0)) ++pivot;\n\
    \        return pivot;\n    }\n};\n"
  dependsOn:
  - Algebra/Field/concept.hpp
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: Matrix/Vector.hpp
  requiredBy:
  - Graph/count_spanning_tree.hpp
  - Matrix/Matrix.hpp
  timestamp: '2026-06-30 17:38:58+08:00'
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
documentation_of: Matrix/Vector.hpp
layout: document
redirect_from:
- /library/Matrix/Vector.hpp
- /library/Matrix/Vector.hpp.html
title: Matrix/Vector.hpp
---
