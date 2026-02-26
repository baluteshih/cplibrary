#pragma once

#include "Polynomial/Polynomial.hpp"
#include "Numeric/quadratic_residue.hpp"

template<class T>
Poly<T> Poly<T>::Sqrt() const { // has_sqrt() is true, 5e5/491ms
    if (n() == 1) { 
        bool succ;
        return { quadratic_residue((*this)[0], succ) };
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
template<class T>
bool Poly<T>::has_sqrt() const {
    int cnt = 0;
    while (cnt < n() && (*this)[cnt] == 0) ++cnt;
    if (cnt == n()) return true;
    if (cnt % 2 != 0) return false;
    int jc = jacobi((*this)[cnt].val(), T::mod());
    return jc == 1;
}
