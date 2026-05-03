#pragma once

#include "Misc/MultiInt.hpp"

template <int base, typename... Ints>
struct RollingHash {
    using Val = MultiInt<Ints...>;
    int sz = 0;
    Val val;
    inline static std::vector<Val> p_pow, p_ipow;
    static void initialize() {
        p_pow = std::vector<Val>{Val(1), Val(base)};
        p_ipow = std::vector<Val>{Val(1), Val(1) / Val(base)};
    }
    static void extend(int sz) {
        if (p_pow.empty()) initialize();
        int cur = p_pow.size();
        if (sz <= cur) return;
        p_pow.resize(sz), p_ipow.resize(sz);
        if (cur < sz) {
            for (int i = cur; i < sz; ++i) {
                p_pow[i] = p_pow[i - 1] * p_pow[1];
                p_ipow[i] = p_ipow[i - 1] * p_ipow[1]; 
            }
        }
    }
    static Val get_pow(int idx) {
        if (idx >= int(p_pow.size())) extend(idx + 1);
        return p_pow[idx];
    }
    static Val get_ipow(int idx) {
        if (idx >= int(p_ipow.size())) extend(idx + 1);
        return p_ipow[idx];
    }
    RollingHash() = default; 
    template <typename T> 
    RollingHash(int _sz, T x) : sz(_sz), val(x) {}
    RollingHash(int _sz, Ints... args) : sz(_sz), val(args...) {}
    RollingHash& operator+=(const RollingHash &rhs) {
        val += rhs.val * get_pow(sz);
        sz += rhs.sz;
        return *this; 
    }
    RollingHash& operator*=(const int &v) {
        if (v > 0) val *= get_pow(v);
        else if (v < 0) val *= get_ipow(-v);
        return *this;
    }
    RollingHash& operator-=(const RollingHash &rhs) {
        val -= rhs.val;
        sz -= rhs.sz;
        return *this; 
    }
    RollingHash operator+(const RollingHash& o) const { auto res = *this; return res += o; }
    RollingHash operator-(const RollingHash& o) const { auto res = *this; return res -= o; }
    RollingHash operator*(const int& o) const { auto res = *this; return res *= o; }
    bool operator==(const RollingHash &rhs) const {
        return sz == rhs.sz && val == rhs.val;
    }
    std::strong_ordering operator<=>(const RollingHash &rhs) const {
        if (sz != rhs.sz) return sz <=> rhs.sz;
        return val <=> rhs.val;
    }
    static std::vector<RollingHash> prefixHash(const auto &a) {
        std::vector<RollingHash> res(a.size());
        extend(a.size());
        for (int i = 0; i < int(a.size()); ++i) {
            res[i] = RollingHash(1, Val(a[i]));
            if (i) res[i] = res[i - 1] + res[i];
        }
        return res;
    }
    static RollingHash rangeHash(const std::vector<RollingHash> &prefix_sum, int l, int r) {
        if (l > r) return RollingHash();
        if (l == 0) return prefix_sum[r - 1];
        return (prefix_sum[r - 1] - prefix_sum[l - 1]) * (-l);
    }
    friend ostream& operator<<(ostream& os, const RollingHash& v) {
        os << v.sz << " | " << v.val; 
        return os;
    }
};
