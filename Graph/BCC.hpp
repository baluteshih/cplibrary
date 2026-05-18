#pragma once

#include "Graph/base.hpp"

template<typename Edge = void, typename Vertex = void>
struct BCC : public Graph<false, Edge, Vertex> { // 0-base
    using super = Graph<false, Edge, Vertex>;
    int dft, nbcc;
    std::vector<int> low, dfn, bln, stk, is_ap;
    std::vector<std::vector<int>> bcc;
    void make_bcc(int u) {
        bcc.emplace_back(1, u); 
        for (; stk.back() != u; stk.pop_back())
            bln[stk.back()] = nbcc, bcc[nbcc].push_back(stk.back());
        stk.pop_back(), bln[u] = nbcc++;
    }
    void dfs(int u, int f) {
        int child = 0;
        low[u] = dfn[u] = ++dft, stk.push_back(u);
        for (auto [v, eid] : this->G[u])
            if (!dfn[v]) {
                dfs(v, u), ++child;
                low[u] = std::min(low[u], low[v]);
                if (dfn[u] <= low[v]) {
                    is_ap[u] = 1, bln[u] = nbcc;
                    make_bcc(v), bcc.back().push_back(u);
                }
            } else if (dfn[v] < dfn[u] && v != f)
                low[u] = std::min(low[u], dfn[v]);
        if (f == -1 && child < 2) is_ap[u] = 0;
        if (f == -1 && child == 0) make_bcc(u);
    }
    BCC(int n) : super(n), dft(), nbcc(), low(n), dfn(n), bln(n), is_ap(n) {}
    BCC(const super &G) : super(G), dft(), nbcc(), low(G.n()), dfn(G.n()), bln(G.n()), is_ap(G.n()) {}
    void solve() {
        for (int i = 0; i < this->n(); ++i)
            if (!dfn[i]) dfs(i, -1);
    }
    /*
    Return std::pair<idx, tree adj matrix>
    idx[u]: the new vertex index of the vertex u belongs to
    */
    std::pair<std::vector<int>, std::vector<std::vector<int>>> block_cut_tree() const {
        int count = nbcc;
        std::vector<int> cir, newbln(bln);
        std::vector<std::vector<int>> nG;
        cir.resize(count);
        for (int i = 0; i < this->n(); ++i)
            if (is_ap[i])
                newbln[i] = count++;
        cir.resize(count, 1), nG.resize(count);
        for (int i = 0; i < count && !cir[i]; ++i)
            for (int j : bcc[i])
                if (is_ap[j])
                    nG[i].push_back(newbln[j]), nG[newbln[j]].push_back(i);
        return {newbln, nG};
    } // up to 2 * n - 2 nodes!! bln[i] for id
};
