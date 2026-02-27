#pragma once

#include "Polynomial/Bostan_Mori.hpp"

template<class T>
T linear_recursion(const std::vector<T> &a, const std::vector<T> &coef, long long n) { // a_n = \sum c_j a_(n-j-1), 1e5/1698ms
    const int k = (int)a.size();
    assert((int)coef.size() == k);
    Poly<T> f(a), g(coef);
    g = g * T(-1);
    g.insert(g.begin(), 1);
    f = (f * g).isz(k);
    return Bostan_Mori(f, g, n);
}
