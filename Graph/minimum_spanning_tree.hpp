#pragma once

#include "Graph/base.hpp"
#include "DataStructure/DisjointSet.hpp"

template<typename Edge = int, typename Vertex = void>
std::vector<int> minimum_spanning_tree(const UndirectedGraph<Edge, Vertex> &graph) {
    std::vector<int> idx(graph.m());
    std::iota(idx.begin(), idx.end(), 0);
    std::ranges::sort(idx.begin(), idx.end(), [&](int a, int b) {
        return graph.edge(a).weight < graph.edge(b).weight; 
    });
    DisjointSet dsu(graph.n());
    std::vector<int> res;
    for (int i : idx)
        if (dsu.merge(graph.edge(i).from, graph.edge(i).to))
            res.push_back(i);
    return res;
}
