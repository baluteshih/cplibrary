#pragma once

template<typename Value = int>
class CatTree {
    int n;
    std::vector<int> mid;
    std::vector<std::vector<Value>> lft, rgt;
    void initialize(int l, int r, int rt, const vector<Value> &data) {
        if (r - l == 1) {
            lft[rt].push_back(data[l]);
            return;
        }
        mid[rt] = (l + r) >> 1;
        lft[rt].resize(mid[rt] - l);
        rgt[rt].resize(r - mid[rt]);
        for (int i = mid[rt] - 1; i >= l; --i) {
            lft[rt][mid[rt] - i - 1] = i < std::ssize(data) ? data[i] : Value();
            if (mid[rt] - i - 1 > 0)
                lft[rt][mid[rt] - i - 1] = lft[rt][mid[rt] - i - 1] + lft[rt][mid[rt] - i - 2];
        }
        for (int i = mid[rt]; i < r; ++i) {
            rgt[rt][i - mid[rt]] = i < std::ssize(data) ? data[i] : Value();
            if (i - mid[rt] > 0)
                rgt[rt][i - mid[rt]] = rgt[rt][i - mid[rt] - 1] + rgt[rt][i - mid[rt]];
        }
        initialize(l, mid[rt], rt << 1, data);
        initialize(mid[rt], r, rt << 1 | 1, data);
    }
    static int ceilpow2(int sz) {
        int m = 1;
        while (m < sz) m <<= 1;
        return m;
    }
public:
    CatTree(const std::vector<Value> &data): n(ceilpow2(data.size())), mid(n), lft(n << 1), rgt(n) { 
        initialize(0, n, 1, data);
    }
    CatTree(int size): CatTree(std::vector<Value>(size)) {}
    Value range_prod(int l, int r) {
        assert(0 <= l && r <= n);
        assert(l <= r);
        if (l == r) return Value();
        --r;
        l += n, r += n;
        if (l == r) return lft[l][0];
        int lca = l >> (std::__lg(l ^ r) + 1);
        l -= n, r -= n;
        return lft[lca][mid[lca] - l - 1] + rgt[lca][r - mid[lca]];
    }
};
