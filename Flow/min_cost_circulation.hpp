#pragma once

#include "Graph/base.hpp"
#include "Flow/min_cost_max_flow.hpp"

// source: https://judge.yosupo.jp/submission/194239
template<typename T, typename C = T>
class min_cost_circulation : public Graph<true, CostFlowWeight<T, C>, void> { // 0-base
public:
    using super = Graph<true, CostFlowWeight<T, C>, void>;
    std::vector<int> vis, fa, fae;
    int visc;
    std::vector<C> pi;
    min_cost_circulation(int _n) : super(_n), vis(_n), visc(0), pi(_n) {} 
    C phi(int x) {
        if (fa[x] == -1) return 0;
        if (vis[x] == visc) return pi[x];
        vis[x] = visc;
        return pi[x] = phi(fa[x]) - this->edges[fae[x]].weight.cost;
    }
    int lca(int u, int v) {
        for (; u != -1 || v != -1; swap(u, v))
            if (u != -1) {
                if (vis[u] == visc) return u;
                vis[u] = visc;
                u = fa[u];
            }
        return -1;
    }
    void pushflow(int x) {
        int v = this->edges[x].from, u = this->edges[x].to;
        ++visc;
        if (int w = lca(u, v); w == -1) {
            while (v != -1)
                swap(x ^= 1, fae[v]), swap(u, fa[v]), swap(u, v);
        }
        else {
            int z = u, dir = 0;
            T f = this->edges[x].weight.flow;
            std::vector<int> cyc = {x};
            for (int d : {0, 1})
                for (int i = (d ? u : v); i != w; i = fa[i]) {
                    cyc.push_back(fae[i] ^ d);
                    if (f > this->edges[fae[i] ^ d].weight.flow) {
                        f = this->edges[fae[i] ^ d].weight.flow;
                        z = i, dir = d;
                    }
                }
            for (int i : cyc) {
                this->edges[i].weight.flow -= f;
                this->edges[i ^ 1].weight.flow += f;
            }
            if (dir) x ^= 1, swap(u, v);
            while (u != z)
                swap(x ^= 1, fae[v]), swap(u, fa[v]), swap(u, v);
        }
    }
    void dfs(int u) {
        vis[u] = visc;
        for (auto [v, eid] : this->G[u])
            if (vis[v] != visc && this->edges[eid].weight.flow)
                fa[v] = u, fae[v] = eid, dfs(v);
    }
    void solve() {
        fa.assign(this->n(), -1), fae.assign(this->n(), -1);
        ++visc, dfs(0);
        for (int fail = 0; fail < int(this->edges.size());)
            for (int i = 0; i < int(this->edges.size()); ++i)
                if (this->edges[i].weight.flow && this->edges[i].weight.cost < phi(this->edges[i].from) - phi(this->edges[i].to))
                    fail = 0, pushflow(i), ++visc;
                else
                    ++fail;
    }
    void add_edge(int a, int b, T cap, C cost) {
        super::add_edge(a, b, CostFlowWeight<T, C>(cap, cost, cap));
        super::add_edge(b, a, CostFlowWeight<T, C>(T(0), -cost, T(0)));
    }
    C get_cost() {
        C res = 0;
        for (int i = 0; i < int(this->edges.size()); i += 2)
            res += this->edges[i].weight.cost * (this->edges[i].weight.cap - this->edges[i].weight.flow);
        return res;
    }
    std::vector<T> get_cap() {
        std::vector<T> res;
        for (int i = 0; i < int(this->edges.size()); i += 2)
            res.push_back(this->edges[i].weight.cap - this->edges[i].weight.flow);
        return res;
    }
    std::vector<C> get_potential() {
        std::vector<C> d(this->n());
        std::vector<int> inq(this->n(), true);
        std::queue<int> q;
        for (int i = 0; i < this->n(); ++i)
            q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (auto [v, eid] : this->G[u])
                if (this->edges[eid].weight.flow && d[v] > d[u] + this->edges[eid].weight.cost) {
                    d[v] = d[u] + this->edges[eid].weight.cost;
                    if (!inq[v]) {
                        inq[v] = true;
                        q.push(v);
                    }
                }
        }
        return d;
    }
};
