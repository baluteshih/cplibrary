#ifndef __POLYNOMIAL__
#define __POLYNOMIAL__
template<class T>
class Poly : public vector<T> {
    using vector<T>::vector;
    static NTT<T> ntt;
    int n() const { return (int)this->size(); } // n() >= 1
    static int ceilpow2(int sz) {
        int m = 1;
        while (m < sz) m <<= 1;
        return m;
    }
public:
    Poly(const Poly &p, int m) : vector<T>(m) {
        copy_n(p.data(), min(p.n(), m), this->data());
    }
    Poly(const vector<T> &v) : vector<T>(move(v)) {}
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
        return ntt.convolution(*this, rhs);
    }
    Poly &dft(int len) {
        isz(len);
        ntt.ntt(*this);
        return *this;
    }
    Poly &idft(int len) {
        isz(len);
        ntt.ntt(*this, true);
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
    vector<T> _eval(const vector<T> &x, const vector<Poly> &up) const {
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
    vector<T> Eval(const vector<T> &x) const { // 1e5/696ms
        auto up = _tree1(x); return _eval(x, up);
    }
    static Poly Interpolate(const vector<T> &x, const vector<T> &y) { // 1e5/928ms
        const int m = (int)x.size();
        vector<Poly> up = _tree1(x), down(m * 2);
        vector<T> z = up[1].Dx()._eval(x, up);
        for (int i = 0; i < m; ++i) z[i] = y[i] / z[i];
        for (int i = 0; i < m; ++i) down[m + i] = {z[i]};
        for (int i = m - 1; i > 0; --i) down[i] = down[i * 2] * up[i * 2 + 1] + down[i * 2 + 1] * up[i * 2];
        return down[1];
    }
    pair<Poly, Poly> DivMod(const Poly &rhs) const { // rhs.back() != 0, 5e5/330ms
        if (n() < rhs.n()) return {{0}, *this};
        const int m = n() - rhs.n() + 1;
        Poly X(rhs); X.irev().isz(m);
        Poly Y(*this); Y.irev().isz(m);
        Poly Q = (Y * X.Inv()).isz(m).irev();
        X = rhs * Q, Y = *this;
        return {Q, (Y - X).isz(max(1, rhs.n() - 1))};
    }
    static T Bostan_Mori(const Poly &f, const Poly &g, ll k) { // [f(x)/g(x)][x^k]
        assert(f.n() + 1 <= g.n());
        Poly F(f);
        Poly G(g);
        for (; k; k >>= 1) {
            Poly H = G;
            int m = ceilpow2(G.n() * 2);
            for (int i = 1; i < H.n(); i += 2) H[i] = -H[i];
            F.dft(m), G.dft(m), H.dft(m);
            F.imul(H), G.imul(H);
            F.idft(m), G.idft(m);
            for (int i = 0; i * 2 + (k & 1) < F.n(); ++i) F[i] = F[i * 2 + (k & 1)];
            for (int i = 0; i * 2 < G.n(); ++i) G[i] = G[i * 2];
            F.isz((F.n() + 1 - (k & 1)) / 2), G.isz((G.n() + 1) / 2);
        }
        return F[0] / G[0];
    }
    static T LinearRecursion(const vector<T> &a, const vector<T> &coef, ll n) { // a_n = \sum c_j a_(n-j-1), 1e5/1698ms
        const int k = (int)a.size();
        assert((int)coef.size() == k);
        Poly f(a), g(coef);
        g = g * T(-1);
        g.insert(g.begin(), 1);
        f = (f * g).isz(k);
        return Bostan_Mori(f, g, n);
    }
    Poly& shift(T c) { // f(x + c), 5e5/149ms
        if (c == 0) return *this;
        Poly A(*this), B(CombFunc::power(c, n()));
        Combination<T> comb(n());
        A.imul(comb.fac).irev();
        B.imul(comb.ifac);
        auto res = (A * B).isz(n()).irev();
        for (int i = 0; i < n(); ++i)
            (*this)[i] = res[i] * comb.ifac[i];
        return *this;
    }
    // given f(0),...,f(n-1), return f(c + i) for all 0 <= i < m, 5e5/408ms
    // source: https://maspypy.github.io/library/poly/lagrange_interpolate_iota.hpp
    static vector<T> lagrange_interpolate_iota(const vector<T> &f, T c, int m) {
        const int k = f.size();
        Poly a(f);
        Combination<T> comb(k);
        for (int i = 0; i < k; ++i) {
            a[i] *= comb.ifac[i] * comb.ifac[k - i - 1];
            if ((k - i - 1) & 1) a[i] = -a[i];
        }
        Poly b(k + m - 1);
        for (int i = 0; i < k + m - 1; ++i) {
            T v = c + T(i - k + 1);
            if (v == 0) b[i] = 0;
            else b[i] = 1 / v;
        }
        a = a * b;
        vector<T> res(m);
        ll L = 0, R = 0;
        int zero = 0;
        deque<T> prod;
        T prod_v = 1;
        auto push = [&](T x) {
            prod.push_back(x);
            if (x == 0) ++zero;
            else prod_v *= x;
        };
        auto pop = [&]() {
            if (prod[0] == 0) --zero;
            else prod_v /= prod[0];
            prod.pop_front();
        };
        for (int i = 0; i < m; ++i) {
            while (L < i) pop(), ++L;
            while (R - L < k) push(c + T((R++) - k + 1));
            if (zero)
                res[i] = f[(c + i).val()];
            else
                res[i] = a[i + k - 1] * prod_v;
        }
        return res;
    }
};
using Poly_t = Poly<modint998244353>;
const int MAXL = 1 << 19;
template<> decltype(Poly_t::ntt) Poly_t::ntt = NTT<modint998244353>(MAXL * 2, 3);
#endif // __POLYNOMIAL__
