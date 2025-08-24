#ifndef __POLYNOMIAL__
#define __POLYNOMIAL__
template<class T>
class Poly : public vector<T> {
    using vector<T>::vector;
    static NTT<T> ntt;
    int n() const { return (int)this->size(); } // n() >= 1
public:
    Poly(const Poly &p, int m) : vector<T>(m) {
        copy_n(p.data(), min(p.n(), m), this->data()); 
    }
    Poly(const vector<T> &v) : vector<T>(move(v)) {}
    Poly& irev() { return reverse(this->data(), this->data() + n()), *this; }
    Poly& isz(int m) { return this->resize(m), *this; }
    Poly operator+(const Poly &rhs) const { // n() == rhs.n()
        Poly res(*this);
        for (int i = 0; i < n(); ++i)
            res[i] += rhs[i];
        return res;
    }
    Poly operator*(const T &rhs) const {
        Poly res(*this); 
        for (int i = 0; i < n(); ++i)
            res[i] *= rhs;
        return res;
    }
    Poly operator*(const Poly &rhs) const { // 5e5/185ms
        return ntt.convolution(*this, rhs); 
    }
    Poly Inv() const { // (*this)[0] != 0, 5e5/212ms
        if (n() == 1) return {(*this)[0].inv()};
        int m = 1;
        while (m < n() * 2) m <<= 1;
        Poly Xi = Poly(*this, (n() + 1) / 2).Inv().isz(m);
        Poly Y(*this, m);
        ntt.ntt(Xi), ntt.ntt(Y);
        for (int i = 0; i < m; ++i)
            Xi[i] *= (2 - Xi[i] * Y[i]);
        ntt.ntt(Xi, true);
        return Xi.isz(n());
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
        for (int i = 0; i < n(); ++i)
            Y[i] = (*this)[i] - Y[i];
        return (X * Y).isz(n());
    }
    // M := P(P - 1). If k >= M, k := k % M + M.
    Poly Pow(ll k) const { // 5e5/1195ms
        int nz = 0;
        while (nz < n() && (*this)[nz] == 0) ++nz;
        if (nz * min(k, (ll)n()) >= n()) return Poly(n());
        if (!k) return Poly(Poly {1}, n());
        Poly X(this->data() + nz, this->data() + nz + n() - nz * k);
        return ((X.Ln() * T(k)).Exp() * X[0].pow(k)).irev().isz(n()).irev();
    }
    Poly Sqrt() const { // has_sqrt() is true, 5e5/491ms
        if (n() == 1) { 
            bool succ;
            return { QuadraticResidue((*this)[0], succ) };
        }
        if ((*this)[0] == 0) {
            int cnt = 0;
            while (cnt < n() && (*this)[cnt] == 0) ++cnt;
            if (cnt == n()) return *this;
            Poly X(*this);
            X = X.irev().isz(n() - cnt).irev().Sqrt();
            return X.irev().isz(X.n() + cnt / 2).irev().isz(n());
        }
        Poly X = Poly(*this, (n() + 1) / 2).Sqrt().isz(n());
        return (X + ((*this) * X.Inv()).isz(n())) * (T::mod() / 2 + 1);
    }
    bool has_sqrt() {
        int cnt = 0;
        while (cnt < n() && (*this)[cnt] == 0) ++cnt;
        if (cnt == n()) return true;
        if (cnt % 2 != 0) return false;
        int jc = Jacobi((*this)[cnt].val(), T::mod());
        return jc == 1;
    }
    Poly _tmul(int nn, const Poly &rhs) const {
        Poly Y = ((*this) * rhs).isz(n() + nn - 1);
        return Poly(Y.data() + n() - 1, Y.data() + Y.n());
    }
    vector<ll> _eval(const vector<ll> &x, const vector<Poly> &up) const {
        const int m = (int)x.size();
        if (!m) return {};
        vector<Poly> down(m * 2);
        down[1] = Poly(up[1]).irev().isz(n()).Inv().irev()._tmul(m, *this);
        for (int i = 2; i < m * 2; ++i)
            down[i] = up[i ^ 1]._tmul(up[i].n() - 1, down[i / 2]);
        vector<T> y(m);
        for (int i = 0; i < m; ++i) y[i] = down[m + i][0];
        return y;
    }
    static vector<Poly> _tree1(const vector<T> &x) {
        const int m = (int)x.size();
        vector<Poly> up(m * 2);
        for (int i = 0; i < m; ++i)
            up[m + i] = {-x[i], 1};
        for (int i = m - 1; i > 0; --i) 
            up[i] = up[i * 2] * up[i * 2 + 1];
        return up;
    }
    vector<T> Eval(const vector<T> &x) const { // 5e5/???ms
        auto up = _tree1(x); return _eval(x, up);
    }
    pair<Poly, Poly> DivMod(const Poly &rhs) const { // rhs.back() != 0
        if (n() < rhs.n()) return {{0}, *this};
        const int m = n() - rhs.n() + 1;
        Poly X(rhs); X.irev().isz(m);
        Poly Y(*this); Y.irev().isz(m);
        Poly Q = (Y * X.Inv()).isz(m).irev();
        X = rhs * Q, Y = *this;
        for (int i = 0; i < n(); ++i)
            Y[i] -= X[i];
        return {Q, Y.isz(max(1, rhs.n() - 1))};
    }
};
using Poly_t = Poly<modint998244353>;
const int MAXL = 1 << 19;
template<> decltype(Poly_t::ntt) Poly_t::ntt = NTT<modint998244353>(MAXL * 2, 3);
#endif // __POLYNOMIAL__
