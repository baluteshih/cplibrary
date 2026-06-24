#pragma once

#include "Graph/base.hpp"
#include "Matrix/Matrix.hpp"

template<typename T, typename graph>
T count_spanning_tree(const graph &G, int root = 0) {
    Matrix<T> mat(G.n());
    assert(root >= 0 && root < G.n());
    for (auto e : G.edges) {
        if (e.to == e.from) continue;
        mat[e.to][e.to] += T(1);
        mat[e.from][e.to] -= T(1);
        if constexpr (!graph::is_directed) {
            mat[e.from][e.from] += T(1);
            mat[e.to][e.from] -= T(1);
        }
    }
    return mat.minor(root, root).det();
}
