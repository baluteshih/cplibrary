#pragma once

#include "Tree/Tree.hpp"

template<typename Edge, typename Vertex>
requires (ValidAddableState<Vertex, Vertex> && ValidAddableState<Vertex, Edge>)
std::vector<Vertex> all_direction_composition(Tree<Edge, Vertex> &tree) {
    static_assert(Tree<Edge, Vertex>::hasEdgeWeight, "Must have edge weight in all_direction_composition");
    static_assert(Tree<Edge, Vertex>::hasVertexWeight, "Must have vertex weight in all_direction_composition");
    std::vector<Vertex> dp(tree.n()), recv(tree.n());
    if (tree.current_root == -1) tree.traverse(); 
    tree.postdfs([&](int u) {
        for (auto [v, eid] : tree[u])
            if (v != tree.parent(u)) {
                dp[v] = dp[v] + tree.edge(eid).weight;
                dp[u] = dp[u] + dp[v];
            }
        dp[u] = dp[u] + tree.vertex(u);
    });
    if constexpr (ValidSubtractableState<Vertex, Vertex>) {
        tree.predfs([&](int u) {
            if (tree.parent(u) != u) {
                recv[u] = recv[tree.parent(u)] - dp[u];
                recv[u] = recv[u] + tree.parent_edge(u).weight;
            }
            for (auto [v, eid] : tree[u])
                if (v != tree.parent(u))
                    recv[u] = recv[u] + dp[v];
            recv[u] = recv[u] + tree.vertex(u); 
        });
    }
    else {
        tree.predfs([&](int u) {
            if (tree.parent(u) != u)
                recv[u] = recv[u] + tree.parent_edge(u).weight;
            recv[u] = recv[u] + tree.vertex(u); 
            for (auto [v, eid] : tree[u])
                if (v != tree.parent(u)) {
                    recv[v] = recv[u];
                    recv[u] = recv[u] + dp[v];
                }
            Vertex sum = Vertex(); 
            for (auto [v, eid] : tree[u] | std::views::reverse)
                if (v != tree.parent(u)) {
                    recv[v] = recv[v] + sum;
                    sum = dp[v] + sum;
                }
        });
    }
    return recv;
}
