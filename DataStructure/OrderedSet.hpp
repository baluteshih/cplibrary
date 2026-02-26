#pragma once

#include "DataStructure/BIT.hpp"

template<class T>
class OrderedSet {
    vector<T> vals;
    vector<bool> vis;
    BIT<int> bit;
    static vector<T> sort_and_unique(vector<T> _vals) {
        ranges::sort(_vals);
        _vals.erase(ranges::unique(_vals).begin(), _vals.end());
        return _vals;
    }
    int idx(int x) {
        auto it = ranges::lower_bound(vals, x);
        if (it == vals.end() || *it != x) return -1;
        return it - vals.begin();
    }
    int safe_idx(int x) {
        int res = idx(x);
        assert(res != -1);
        return res;
    }
public:
    OrderedSet(vector<T> _vals): vals(sort_and_unique(_vals)), vis(vals.size()), bit(bit_ceil(vals.size())) {}
    bool insert(T x) {
        x = safe_idx(x);
        if (vis[x]) return false;
        vis[x] = true;
        bit.modify(x, 1);
        return true;
    }
    bool erase(T x) {
        x = safe_idx(x);
        if (!vis[x]) return false;
        vis[x] = false;
        bit.modify(x, -1);
        return true;
    }
    bool exists(T x) {
        x = idx(x);
        if (x == -1) return false;
        return vis[x]; 
    }
    int size() {
        return bit.total();
    }
    int lt_count(T x) {
        int idx = ranges::lower_bound(vals, x) - vals.begin() - 1;
        return bit.prefix(idx);
    }
    int leq_count(T x) {
        int idx = ranges::upper_bound(vals, x) - vals.begin() - 1;
        return bit.prefix(idx);
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
    const T& operator[](size_t index) const {
        return vals[index];
    } 
};
