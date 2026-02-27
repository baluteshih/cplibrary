#pragma once

#include "Polynomial/NTT.hpp"

template<class T>
class Poly : public std::vector<T> {
    using std::vector<T>::vector;
    int n() const { return (int)this->size(); } // n() >= 1
    static int ceilpow2(int sz) {
        int m = 1;
        while (m < sz) m <<= 1;
        return m;
    }
public:
    Poly(const Poly &p, int m) : std::vector<T>(m) {
        std::copy_n(p.data(), min(p.n(), m), this->data());
    }
    Poly(const std::vector<T> &v) : std::vector<T>(move(v)) {}
    Poly& irev() { return reverse(this->data(), this->data() + n()), *this; }
    Poly& isz(int m) { return this->resize(m), *this; }
    Poly& imul(const Poly &rhs) {
        for (int i = 0; i < n(); ++i)
            (*this)[i] *= rhs[i];
        return *this;
    }
    Poly& strip() {
        while (!this->empty() && this->back() == 0)
            this->pop_back();
        return *this;
    }
    Poly operator+(const Poly &rhs) const { // n() == rhs.n()
        Poly res(*this);
        for (int i = 0; i < n(); ++i)
            res[i] += rhs[i];
        return res;
    }
    Poly operator-(const Poly &rhs) const { // n() == rhs.n()
        Poly res(*this);
        for (int i = 0; i < n(); ++i)
            res[i] -= rhs[i];
        return res;
    }
    Poly operator*(const T &rhs) const {
        Poly res(*this);
        for (int i = 0; i < n(); ++i)
            res[i] *= rhs;
        return res;
    }
    Poly operator*(const Poly &rhs) const { // 5e5/185ms
        return NTT<T>::convolution(*this, rhs);
    }
    Poly &dft(int len) {
        assert((len & (len - 1)) == 0);
        isz(len);
        NTT<T>::ntt(*this);
        return *this;
    }
    Poly &idft(int len) {
        assert((len & (len - 1)) == 0);
        isz(len);
        NTT<T>::ntt(*this, true);
        return *this;
    }
    Poly Inv() const { // (*this)[0] != 0, 5e5/212ms
        if (n() == 1) return {(*this)[0].inv()};
        int m = ceilpow2(n() * 2);
        Poly Xi = Poly(*this, (n() + 1) / 2).Inv().isz(m);
        Poly Y(*this, m);
        Xi.dft(m), Y.dft(m);
        for (int i = 0; i < m; ++i)
            Xi[i] *= (2 - Xi[i] * Y[i]);
        return Xi.idft(m).isz(n());
    }
    Poly Dx() const {
        Poly ret(n() - 1);
        for (int i = 0; i < ret.n(); ++i)
            ret[i] = (i + 1) * (*this)[i + 1];
        return ret.isz(max(1, ret.n()));
    }
    Poly Sx() const {
        Poly ret(n() + 1);
        for (int i = 0; i < n(); ++i)
            ret[i + 1] = T(i + 1).inv() * (*this)[i];
        return ret;
    }
    Poly Ln() const { // (*this)[0] == 1, 5e5/406ms
        return (Dx() * Inv()).Sx().isz(n());
    }
    Poly Exp() const { // (*this)[0] == 0, 5e5/886ms
        if (n() == 1) return {1};
        Poly X = Poly(*this, (n() + 1) / 2).Exp().isz(n());
        Poly Y = X.Ln(); Y[0] = -1;
        return (X * (*this - Y)).isz(n());
    }
    // M := P(P - 1). If k >= M, k := k % M + M, 5e5/1195ms
    Poly Pow(ll k) const {
        int nz = 0;
        while (nz < n() && (*this)[nz] == 0) ++nz;
        if (nz * min(k, (ll)n()) >= n()) return Poly(n());
        if (!k) return Poly(Poly {1}, n());
        Poly X(this->data() + nz, this->data() + nz + n() - nz * k);
        return ((X.Ln() * T(k)).Exp() * X[0].pow(k)).irev().isz(n()).irev();
    }
    Poly _tmul(int nn, const Poly &rhs) const {
        Poly Y = ((*this) * rhs).isz(n() + nn - 1);
        return Poly(Y.data() + n() - 1, Y.data() + Y.n());
    }
    std::vector<T> _eval(const std::vector<T> &x, const std::vector<Poly> &up) const {
        const int m = (int)x.size();
        if (!m) return {};
        std::vector<Poly> down(m * 2);
        down[1] = Poly(up[1]).irev().isz(n()).Inv().irev()._tmul(m, *this);
        for (int i = 2; i < m * 2; ++i)
            down[i] = up[i ^ 1]._tmul(up[i].n() - 1, down[i / 2]);
        std::vector<T> y(m);
        for (int i = 0; i < m; ++i) y[i] = down[m + i][0];
        return y;
    }
    static std::vector<Poly> _tree1(const std::vector<T> &x) {
        const int m = (int)x.size();
        std::vector<Poly> up(m * 2);
        for (int i = 0; i < m; ++i)
            up[m + i] = {-x[i], 1};
        for (int i = m - 1; i > 0; --i) 
            up[i] = up[i * 2] * up[i * 2 + 1];
        return up;
    }
    std::vector<T> Eval(const std::vector<T> &x) const { // 1e5/696ms
        auto up = _tree1(x); return _eval(x, up);
    }
    std::pair<Poly, Poly> DivMod(const Poly &rhs) const { // rhs.back() != 0, 5e5/330ms
        if (n() < rhs.n()) return {{0}, *this};
        const int m = n() - rhs.n() + 1;
        Poly X(rhs); X.irev().isz(m);
        Poly Y(*this); Y.irev().isz(m);
        Poly Q = (Y * X.Inv()).isz(m).irev();
        X = rhs * Q, Y = *this;
        return {Q, (Y - X).isz(max(1, rhs.n() - 1))};
    }
    // should be include additionally
    Poly Sqrt() const;
    bool has_sqrt() const;
    Poly& shift(T c);
};
using Poly_t = Poly<modint998244353>;
