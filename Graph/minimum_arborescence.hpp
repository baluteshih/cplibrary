#pragma once

#include "Graph/base.hpp"
#include "DataStructure/DisjointSet.hpp"
#include "DataStructure/LeftistTree.hpp"

// Return the index of spanning tree edges, return empty if no solution (takecare of n = 1)
template<typename graph>
std::vector<int> minimum_arborescence(const graph &G, int root) {
    using T = graph::edge_value_type;
    int n = G.n();
    std::vector<LeftistTree<T, T, int>> heap(n * 2);
    for (int i = 0; i < G.m(); ++i)
        heap[G.edge(i).to].push(G.edge(i).weight, i);
    DisjointSet dsu(n * 2);
    std::vector<int> v(n * 2, -1), pa(n * 2, -1), r(n * 2);
    v[root] = n + 1;
    int pc = n;
    for (int i = 0; i < n; ++i)
        if (v[i] == -1) {
            for (int p = i; v[p] == -1 || v[p] == i; p = dsu.leader(G.edge(r[p]).from)) {
                if (v[p] == i) {
                    int q = p; p = pc++;
                    do {
                        heap[q].transform(T(0) - heap[q].top());
                        pa[q] = p, dsu.merge(p, q, true), heap[p].join(heap[q]);
                    } while ((q = dsu.leader(G.edge(r[q]).from)) != p);
                }
                v[p] = i;
                while (!heap[p].empty() && dsu.leader(G.edge(heap[p].topinfo()).from) == p)
                    heap[p].pop();
                if (heap[p].empty()) return {}; // no solution
                r[p] = heap[p].topinfo();
            }
        }
    std::vector<int> ans;
    for (int i = pc - 1; i >= 0; --i)
        if (i != root && v[i] != n) {
            for (int f = G.edge(r[i]).to; ~f && v[f] != n; f = pa[f])
                v[f] = n;
            ans.push_back(r[i]);
        }
    return ans;
}
