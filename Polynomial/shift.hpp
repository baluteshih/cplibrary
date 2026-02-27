#pragma once

#include "Polynomial/Polynomial.hpp"
#include "Numeric/Combination.hpp"

template<class T>
Poly<T>& Poly<T>::shift(T c) { // f(x + c), 5e5/149ms
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
