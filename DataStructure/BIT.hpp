#pragma once

template<class T>
class BIT { // 0-base
    int n;
    T total_;
    vector<T> bit;
public:
    BIT(int _n): n(_n), total_(), bit(n + 1) {}
    void initialize(const std::vector<T> &arr) {
        for (int x = 1; x <= n; ++x) {
            bit[x] = arr[x - 1];
            int y = x - (x & -x);
            for (int i = x - 1; i > y; i -= i & -i)
                bit[x] = bit[x] + bit[i];
        }
    }
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
    T suffix(int x) requires requires(T x, T y) { x - y; } {
        return total_ - prefix(x);
    }
    T range(int l, int r) requires requires(T x, T y) { x - y; } { // [l, r)
        if (l >= r) return T();
        T res = prefix(r - 1) - prefix(l - 1);
        return res;
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
