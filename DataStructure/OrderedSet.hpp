#pragma once

#include "DataStructure/Discretization.hpp"
#include "DataStructure/BIT.hpp"

template<class T>
class OrderedSet : public Discretization<T> {
    std::vector<bool> vis;
    BIT<int> bit;
public:
    OrderedSet(const std::ranges::range auto &_vals): Discretization<T>(_vals), vis(std::ranges::distance(_vals)), bit(std::bit_ceil(vis.size())) {}
    bool insert(T x) {
        x = this->safe_idx(x);
        if (vis[x]) return false;
        vis[x] = true;
        bit.modify(x, 1);
        return true;
    }
    bool erase(T x) {
        x = this->safe_idx(x);
        if (!vis[x]) return false;
        vis[x] = false;
        bit.modify(x, -1);
        return true;
    }
    bool exists(T x) {
        x = this->idx(x);
        if (x == -1) return false;
        return vis[x]; 
    }
    int size() {
        return bit.total();
    }
    int lt_count(T x) {
        return bit.prefix(this->right_open(x) - 1);
    }
    int leq_count(T x) {
        return bit.prefix(this->right_close(x));
    }
    int order(T x) {
        return leq_count(x);
    }
    int kth(int k) { // 0-base query, return 0-base index
        if (size() <= k) return -1;
        int res = bit.kth(k);
        return res;
    }
    int leq(T x) { // return 0-base index
        int res = leq_count(x);
        return res == 0 ? -1 : kth(res - 1);
    }
    int geq(T x) { // return 0-base index
        int res = lt_count(x);
        return res == size() ? -1 : kth(res);
    }
};
