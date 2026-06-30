#pragma once

#include "DataStructure/Doubling.hpp"

template<typename Value = int>
class SparseTable {
    int n;
    Doubling<Value, true> table;
public:
    SparseTable(const std::ranges::range auto &data) : n(data.size()), table(n, data) {} 
    Value range_prod(int l, int r) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return Value();
        int lg = std::__lg(r - l);
        return table.val[lg][l] + table.val[lg][r - (1 << lg)];
    }
};
