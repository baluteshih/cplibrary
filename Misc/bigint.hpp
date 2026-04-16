#pragma once

#include "Numeric/Modint.hpp"
#include "Polynomial/NTT.hpp"
#include "Numeric/crt.hpp"

// source https://maspypy.github.io/library/bigint/base.hpp 
struct BigInteger {
    static constexpr long long TEN[] = {
        1LL,
        10LL,
        100LL,
        1000LL,
        10000LL,
        100000LL,
        1000000LL,
        10000000LL,
        100000000LL,
        1000000000LL,
        10000000000LL,
        100000000000LL,
        1000000000000LL,
        10000000000000LL,
        100000000000000LL,
        1000000000000000LL,
        10000000000000000LL,
        100000000000000000LL,
        1000000000000000000LL,
    };
    static constexpr int LOG = 9;
    static constexpr int MOD = TEN[LOG];
    using bint = BigInteger;
    int sgn;
    std::vector<int> dat;

    BigInteger() : sgn(0) {}
    BigInteger(__int128 val) {
        if (val == 0) {
            sgn = 0;
            return;
        }
        sgn = 1;
        if (val != 0) {
            if (val < 0) sgn = -1, val = -val;
            while (val > 0) {
                dat.push_back(val % MOD), val /= MOD;
            }
        }
    }
    BigInteger(std::string s) {
        assert(!s.empty());
        sgn = 1;
        if (s[0] == '-') {
            sgn = -1;
            s.erase(s.begin());
            assert(!s.empty());
        }
        if (s[0] == '0') {
            sgn = 0;
            return;
        }
        std::ranges::reverse(s);
        int n = s.size();
        int m = (n + LOG - 1) / LOG;
        dat.assign(m, 0);
        for (int i = 0; i < n; ++i)
            dat[i / LOG] += TEN[i % LOG] * int(s[i] - '0');
    }
    bool operator<(const bint &p) const {
        if (sgn != p.sgn) {
            return sgn < p.sgn;
        }
        if (sgn == 0) return false;
        if (dat.size() != p.dat.size()) {
            if (sgn == 1) return dat.size() < p.dat.size();
            if (sgn == -1) return dat.size() > p.dat.size();
        }
        for (int i = dat.size() - 1; i >= 0; --i) {
            if (dat[i] == p.dat[i]) continue;
            if (sgn == 1) return dat[i] < p.dat[i];
            if (sgn == -1) return dat[i] > p.dat[i];
        }
        return false;
    }
    bool operator>(const bint &p) const { return p < *this; }
    bool operator<=(const bint &p) const { return !(*this > p); }
    bool operator>=(const bint &p) const { return !(*this < p); }
    bint &operator+=(const bint p) {
        if (sgn == 0) {
            return *this = p;
        }
        if (p.sgn == 0) return *this;
        if (sgn != p.sgn) {
            *this -= (-p);
            return *this;
        }
        int n = std::max(dat.size(), p.dat.size());
        dat.resize(n + 1);
        for (int i = 0; i < n; ++i) {
            if (i < int(p.dat.size())) dat[i] += p.dat[i];
            if (dat[i] >= MOD) dat[i] -= MOD, dat[i + 1] += 1;
        }
        while (!dat.empty() && dat.back() == 0) dat.pop_back();
        if (dat.empty()) sgn = 0;
        return *this;
    }
    bint &operator-=(const bint p) {
        if (p.sgn == 0) return *this;
        if (sgn == 0) return *this = (-p);
        if (sgn != p.sgn) {
            *this += (-p);
            return *this;
        }
        if ((sgn == 1 && *this < p) || (sgn == -1 && *this > p)) {
            *this = p - *this;
            sgn = -sgn;
            return *this;
        }
        for (int i = 0; i < int(p.dat.size()); ++i)
            dat[i] -= p.dat[i];
        for (int i = 0; i + 1 < int(dat.size()); ++i) {
            if (dat[i] < 0) dat[i] += MOD, dat[i + 1] -= 1;
        }
        while (!dat.empty() && dat.back() == 0)
            dat.pop_back();
        if (dat.empty()) sgn = 0;
        return *this;
    }
    bint &operator*=(const bint &p) {
        sgn *= p.sgn;
        if (sgn == 0) dat.clear();
        else dat = convolve(dat, p.dat);
        return *this;
    }
    // bint &operator/=(const bint &p) { return *this; }
    bint operator-() const {
        bint p = *this;
        p.sgn *= -1;
        return p;
    }
    bint operator+(const bint &p) const { return bint(*this) += p; }
    bint operator-(const bint &p) const { return bint(*this) -= p; }
    bint operator*(const bint &p) const { return bint(*this) *= p; }
    // bint operator/(const modint &p) const { return modint(*this) /= p; }
    bool operator==(const bint &p) const {
        return (sgn == p.sgn && dat == p.dat);
    }
    bool operator!=(const bint &p) const { return !((*this) == p); }
    void swap(bint &other) {
        std::swap(sgn, other.sgn);
        std::swap(dat, other.dat);
    }
    std::vector<int> convolve(const std::vector<int> &a, const std::vector<int> &b) {
        int n = a.size(), m = b.size();
        if (!n || !m) return {};
        if (std::min(n, m) <= 500) {
            std::vector<int> c(n + m - 1);
            unsigned __int128 x = 0;
            for (int k = 0; k < n + m - 1; ++k) {
                int s = std::max<int>(0, k + 1 - m), t = std::min<int>(k, n - 1);
                for (int i = s; i < t + 1; ++i)
                    x += (unsigned long long)(a[i]) * b[k - i];
                c[k] = x % MOD, x = x / MOD;
            }
            while (x > 0)
                c.push_back(x % MOD), x = x / MOD;
            return c;
        }
        static constexpr int p0 = 167772161;
        static constexpr int p1 = 469762049;
        static constexpr int p2 = 754974721;
        using mint0 = static_modint<p0>;
        using mint1 = static_modint<p1>;
        using mint2 = static_modint<p2>;
        std::vector<mint0> a0(a.begin(), a.end()), b0(b.begin(), b.end());
        std::vector<mint1> a1(a.begin(), a.end()), b1(b.begin(), b.end());
        std::vector<mint2> a2(a.begin(), a.end()), b2(b.begin(), b.end());
        auto c0 = NTT<mint0>::convolution(a0, b0);
        auto c1 = NTT<mint1>::convolution(a1, b1);
        auto c2 = NTT<mint2>::convolution(a2, b2);
        std::vector<int> c(c0.size());
        unsigned __int128 x = 0;
        for (int i = 0; i < n + m - 1; ++i) {
            x += CRT3<unsigned __int128, p0, p1, p2>(c0[i].val(), c1[i].val(), c2[i].val());
            c[i] = x % MOD, x = x / MOD;
        }
        while (x)
            c.push_back(x % MOD), x = x / MOD;
        return c;
    }
    std::string to_string() const {
        if (dat.empty()) return "0";
        std::string s;
        for (int x : dat) {
            for (int i = 0; i < LOG; ++i) {
                s += '0' + (x % 10);
                x = x / 10;
            }
        }
        while (s.back() == '0') s.pop_back();
        if (sgn == -1) s += '-';
        std::ranges::reverse(s);
        return s;
    }
    friend istream& operator>>(istream &is, bint &p) {
        std::string s;
        auto &res = is >> s;
        p = bint(s);
        return res;
    }
    friend ostream& operator<<(ostream &os, const bint &p) { return os << p.to_string(); }
    // ignore overflow 
    ll to_ll() {
        ll x = 0;
        for (int i = dat.size() - 1; i >= 0; --i)
            x = MOD * x + dat[i];
        return sgn * x;
    }
};
