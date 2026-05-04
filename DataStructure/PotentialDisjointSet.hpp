#pragma once

#include "DataStructure/DisjointSet.hpp"

template<typename P, typename T = void>
class PotentialDisjointSet : public DisjointSet<T> {
    using Super = DisjointSet<T>;
    std::vector<P> potential;
public:
    PotentialDisjointSet(int n_): Super(n_), potential(this->n) {}
    PotentialDisjointSet(const std::vector<T> &data_) requires (Super::hasT) : Super(data_), potential(this->n) {}
    int leader(int u) override {
        if (this->boss[u] == u) return u;
        int org = this->boss[u];
        int res = leader(org);
        this->boss[u] = res;
        potential[u] = potential[u] + potential[org];
        return res;
    }
    // p[u] - p[v] = pot
    bool merge(int u, int v, P pot, bool force = false) {
        int ru = leader(u);
        int rv = leader(v);
        if (ru == rv) return false;
        if (this->sz[ru] < this->sz[rv] && !force) { 
            std::swap(ru, rv);
            std::swap(u, v);
            pot = P() - pot;
        }
        this->boss[rv] = ru;
        this->sz[ru] += this->sz[rv];
        if constexpr (Super::hasT) {
            this->data[ru] = this->data[ru] + this->data[rv]; 
        }
        potential[rv] = P() - potential[v] - pot + potential[u]; 
        return true;
    }
    // return p[u] - p[v]
    P diff(int u, int v) {
        assert(this->same(u, v));
        return potential[u] - potential[v];
    }
};
