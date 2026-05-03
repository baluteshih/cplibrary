#pragma once

template<typename Value = int>
class SparseTable {
    int n;
    std::vector<std::vector<Value>> table;
public:
    SparseTable(const std::vector<Value> &data): n(data.size()), table(std::__lg(data.size()) + 1, std::vector<Value>(data.size())) { 
        int L = std::__lg(n);
        table[0] = data;
        for (int i = 1; i <= L; ++i)
            for (int j = 0; j + (1 << i) <= n; ++j)
                table[i][j] = table[i - 1][j] + table[i - 1][j + (1 << (i - 1))];
    }
    Value range_prod(int l, int r) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return Value();
        int lg = std::__lg(r - l);
        return table[lg][l] + table[lg][r - (1 << lg)];
    }
};
