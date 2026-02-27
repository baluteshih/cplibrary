#pragma once

template<class T>
class BIT { // 0-base
    int n;
    T total_;
    vector<T> bit;
public:
    BIT(int _n): n(_n), total_(), bit(n + 1) {}
    void modify(int x, T v) {
        total_ += v;
        for (++x; x <= n; x += x & -x)
            bit[x] = bit[x] + v;
    }
    T prefix(int x) {
        T res = T();
        for (++x; x; x -= x & -x)
            res = res + bit[x];
        return res;
    }
    T suffix(int x) {
        return total_ - prefix(x);
    }
    int kth(int k) { // 0-base query
        assert((n & (n - 1)) == 0);
        ++k;
        int res = 0;
        for (int i = n >> 1; i >= 1; i >>= 1) {
            if (bit[res + i] < k)
                k -= bit[res += i];
        }
        return res;
    }
    T total() {
        return total_;
    }
};
