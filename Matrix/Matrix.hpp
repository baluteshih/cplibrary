#ifndef __BALU_MATRIX_HPP__
#define __BALU_MATRIX_HPP__ 

#include "Matrix/Vector.hpp"

template<class T>
class Matrix : public std::vector<Vector<T>> {
    enum gauss_mode {half, full};
public:
    int n() const { return (int)this->size(); }
    int m() const { return n() ? (int)(*this)[0].size() : 0; }
    Matrix(int _n, int _m): std::vector<Vector<T>>(_n, Vector<T>(_m)) {}
    Matrix(int _n): Matrix(_n, _n) {}
    Matrix(const Vector<T> &vec): Matrix(1, (int)vec.size()) {
        (*this)[0] = vec;
    }
    Matrix transpose() const {
        Matrix res(m(), n());
        for (int i = 0; i < m(); ++i)
            for (int j = 0; j < n(); ++j)
                res[i][j] = (*this)[j][i];
        return res;
    }
    Matrix operator*(const Matrix &rhs) const {
        assert(m() == rhs.n());
        Matrix res(n(), rhs.m());
        auto _rhs = rhs.transpose();
        for (int i = 0; i < res.n(); ++i)
            for (int j = 0; j < res.m(); ++j)
                res[i][j] = (*this)[i] * _rhs[j];
        return res;
    }
    Matrix operator*(const T &v) const {
        Matrix res(*this);
        for (int i = 0; i < res.n(); ++i)
            for (int j = 0; j < res.m(); ++j)
                res[i][j] = res[i][j] * v;
        return res;
    }
    Matrix operator/(const Matrix &rhs) const {
        assert(m() == rhs.n());
        return *this * rhs.inv();
    }
    Matrix operator+(const Matrix &rhs) const {
        assert(n() == rhs.n());
        assert(m() == rhs.m());
        Matrix res(n(), m());
        for (int i = 0; i < res.n(); ++i)
            res[i] = (*this)[i] + rhs[i];
        return res;
    }
    Matrix operator|(Matrix const& rhs) const {
        assert(n() == rhs.n());
        Matrix res(n(), m() + rhs.m());
        for (int i = 0; i < n(); ++i)
            res[i] = (*this)[i] | rhs[i];
        return res;
    }
    Matrix rows(int l, int r) const {
        assert(l <= r);
        assert(r <= n());
        Matrix res(r - l, m());
        for (int i = 0; i < r - l; ++i)
            res[i] = (*this)[l + i];
        return res;
    }
    Matrix columns(int l, int r) const {
        if (m() == 0) return Matrix(0, 0);
        assert(l <= r);
        assert(r <= m());
        Matrix res(n(), r - l);
        for (int i = 0; i < n(); ++i)
            std::copy((*this)[i].begin() + l, (*this)[i].begin() + r, res[i].begin());
        return res;
    }
    static Matrix identity(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; ++i)
            res[i][i] = 1;
        return res;
    }
    Matrix pow(long long k) const {
        Matrix res(identity(n()));
        Matrix base(*this);
        for (; k; k >>= 1, base = base * base)
            if (k & 1)
                res = res * base;
        return res;
    }
    Vector<T> apply(const Vector<T> &x) {
        return (*this * Matrix(x).transpose()).transpose()[0];
    }
    template<gauss_mode mode = half>
    void eliminate(int i) {
        int pivot = (*this)[i].find_pivot();
        if (pivot < m()) {
            T pinv = T(1) / (*this)[i][pivot];
            for (int j = (mode == half) * i; j < n(); ++j)
                if (j != i)
                    (*this)[j] += (*this)[i] * (*this)[j][pivot] * pinv * T(-1); 
        }
    }
    template<gauss_mode mode = half>
    Matrix& gauss() {
        for (int i = 0; i < n(); ++i)
            eliminate<mode>(i);
        return *this;
    }
    std::pair<std::vector<int>, std::vector<int>> sort_classify(int lim) {
        int rk = 0;
        std::vector<int> pivots, free;
        for (int j = 0; j < lim; ++j) {
            if (rk < n() && (*this)[rk][j] == T(0)) {
                for (int i = rk + 1; i < n(); ++i) {
                    if ((*this)[i][j] != T(0)) {
                        std::swap((*this)[i], (*this)[rk]);
                        (*this)[rk] *= T(-1);
                    }
                }
            }
            if (rk < n() && (*this)[rk][j] != T(0)) {
                pivots.push_back(j);
                rk++;
            } 
            else {
                free.push_back(j);
            }
        }
        return std::make_pair(pivots, free);
    }
    template<gauss_mode mode = half>
    std::pair<std::vector<int>, std::vector<int>> echelonize(int lim) {
        return gauss<mode>().sort_classify(lim);
    }
    template<gauss_mode mode = half>
    std::pair<std::vector<int>, std::vector<int>> echelonize() {
        return echelonize<mode>(m());
    }
    int rank() const {
        if (n() > m()) return transpose().rank();
        return Matrix(*this).echelonize().first.size();
    }
    T det() const {
        assert(n() == m());
        Matrix cur = *this;
        cur.echelonize();
        T res = T(1);
        for (int i = 0; i < n(); ++i)
            res = res * cur[i][i];
        return res;
    }
    std::pair<T, Matrix> inv() const {
        assert(n() == m());
        Matrix cur = *this | identity(n());
        if ((int)cur.echelonize<full>(n()).first.size() < n())
            return std::make_pair(0, Matrix(0, 0));
        T det = 1;
        for (int i = 0; i < n(); ++i) {
            det = det * cur[i][i];
            cur[i] = cur[i] / cur[i][i];
        }
        return std::make_pair(det, cur.columns(n(), n() + n()));
    }
    Matrix kernel() const {
        Matrix A(*this);
        auto [pivots, free] = A.echelonize<full>();
        Matrix sols((int)free.size(), m());
        for (int j = 0; j < (int)pivots.size(); ++j) {
            T scale = T(1) / A[j][pivots[j]];
            for (int i = 0; i < (int)free.size(); ++i)
                sols[i][pivots[j]] = A[j][free[i]] * scale;
        }
        for (int i = 0; i < (int)free.size(); ++i)
            sols[i][free[i]] = T(-1);
        return sols;
    }
    // return (x, basis)
    // (*this) * (x^T + basis^T) = t^T
    std::optional<std::pair<Matrix, Matrix>> solve(const Matrix &t) const {
        int dimt = t.n();
        Matrix sols = (*this | t.transpose()).kernel();
        if (sols.n() < dimt) return std::nullopt;
        Matrix upper = sols.rows(0, sols.n() - dimt);
        Matrix lower = sols.rows(sols.n() - dimt, sols.n());
        if (lower.columns(m(), lower.m()) != identity(dimt) * T(-1))
            return std::nullopt;
        return std::make_pair(lower.columns(0, m()), upper.columns(0, m()));
    }
};
#endif // __BALU_MATRIX_HPP__
