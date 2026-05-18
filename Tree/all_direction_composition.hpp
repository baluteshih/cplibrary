#pragma once

#include "Tree/Tree.hpp"
#include "DataStructure/SwagQueue.hpp"

template<typename Edge, typename Vertex>
requires (ValidAddableState<Vertex, Vertex> && ValidAddableState<Vertex, Edge>)
std::vector<UnifiedWeight_t<Edge, Vertex>> all_direction_composition(Tree<Edge, Vertex> &tree) {
    static constexpr bool hasEdgeWeight = Tree<Edge, Vertex>::hasEdgeWeight;
    static constexpr bool hasVertexWeight =  Tree<Edge, Vertex>::hasVertexWeight;
    std::vector<UnifiedWeight_t<Edge, Vertex>> dp(tree.n()), res(tree.n()), recv(tree.n());
    if (tree.current_root == -1) tree.traverse(); 
    tree.postdfs([&](int u) {
        for (auto [v, eid] : tree[u])
            if (v != tree.parent(u)) {
                if constexpr (hasEdgeWeight) dp[v] = dp[v] + tree.edge(eid).weight;
                dp[u] = dp[u] + dp[v];
            }
        if constexpr (hasVertexWeight) dp[u] = dp[u] + tree.vertex(u);
    });
    std::vector<SwagQueue<UnifiedWeight_t<Edge, Vertex>>> swag(tree.n());
    tree.predfs([&](int u) {
        if (tree.parent(u) != u) {
            swag[tree.parent(u)].pop();
            recv[u] = swag[tree.parent(u)].prod();
            if constexpr (hasVertexWeight) recv[u] = recv[u] + tree.vertex(tree.parent(u));
            if constexpr (hasEdgeWeight) recv[u] = recv[u] + tree.parent_edge(u).weight;
            swag[tree.parent(u)].push(dp[u]);
        }
        for (auto [v, eid] : tree[u])
            if (v != tree.parent(u))
                swag[u].push(dp[v]);
        swag[u].push(recv[u]);
        res[u] = swag[u].prod();
        if constexpr (hasVertexWeight) res[u] = res[u] + tree.vertex(u); 
    });
    return res;
}
