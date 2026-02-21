#ifndef __BALU_MATRIX_HPP__
#define __BALU_MATRIX_HPP__ 
template<class T>
class Matrix : public vector<vector<T>> {
    int n() const { return (int)this->size(); }
    int m() const { return (int)(*this)[0].size(); }
public:
    Matrix(int _n, int _m): vector<vector<T>>(_n, vector<T>(_m)) {}
    Matrix transpose() const {
        Matrix res(m(), n());
        for (int i = 0; i < m(); ++i)
            for (int j = 0; j < n(); ++j)
                res[i][j] = (*this)[j][i];
        return res;
    }
    Matrix operator*(const Matrix &_rhs) const {
        assert(m() == _rhs.n());
        Matrix res(n(), _rhs.m());
        auto rhs = _rhs.transpose();
        for (int i = 0; i < res.n(); ++i)
            for (int j = 0; j < res.m(); ++j) {
                T sum = T();
                for (int k = 0; k < m(); ++k)
                    sum = sum + (*this)[i][k] * rhs[j][k];
                res[i][j] = sum;
            }
        return res;
    }
    static Matrix identity(int _n) {
        Matrix res(_n, _n);
        for (int i = 0; i < _n; ++i)
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
};
#endif // __BALU_MATRIX_HPP__
