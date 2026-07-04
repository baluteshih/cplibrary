#pragma once

#include "DataStructure/DynamicBitset.hpp"

class MatrixF2 : public std::vector<DynamicBitset> {
public:
    int n() const { return (int)this->size(); }
    int m() const { return n() ? (int)(*this)[0].size() : 0; }
    MatrixF2(int _n, int _m): std::vector<DynamicBitset>(_n, DynamicBitset(_m)) {}
    MatrixF2(int _n): MatrixF2(_n, _n) {}
    MatrixF2(const DynamicBitset &vec): MatrixF2(1, vec.size()) {
        (*this)[0] = vec;
    }
    MatrixF2 transpose() const {
        MatrixF2 res(m(), n());
        for (int i = 0; i < m(); ++i)
            for (int j = 0; j < n(); ++j)
                res[i][j] = (*this)[j][i];
        return res;
    }
    MatrixF2& operator*=(const MatrixF2 &rhs) {
        assert(m() == rhs.n());
        MatrixF2 res(n(), rhs.m());
        for (int i = 0; i < n(); ++i)
            for (int k = (*this)[i]._Find_first(); k < rhs.n(); k = (*this)[i]._Find_next(k))
                res[i] ^= rhs[k];
        *this = std::move(res);
        return *this;
    }
    MatrixF2& operator+=(const MatrixF2 &rhs) {
        assert(n() == rhs.n());
        assert(m() == rhs.m());
        for (int i = 0; i < n(); ++i)
            (*this)[i] ^= rhs[i];
        return *this;
    }
    MatrixF2 operator*(const MatrixF2 &rhs) const { return MatrixF2(*this) *= rhs; }
    MatrixF2 operator+(const MatrixF2 &rhs) const { return MatrixF2(*this) += rhs; }
    static MatrixF2 identity(int n) {
        MatrixF2 res(n, n);
        for (int i = 0; i < n; ++i) res[i].set(i);
        return res;
    }
    MatrixF2 pow(long long k) const {
        MatrixF2 res(identity(n()));
        MatrixF2 base(*this);
        for (; k; k >>= 1, base = base * base)
            if (k & 1)
                res = res * base;
        return res;
    }
};
