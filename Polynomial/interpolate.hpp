#pragma once

#include "Polynomial/Polynomial.hpp"

template<class T>
Poly<T> interpolate(const std::vector<T> &x, const std::vector<T> &y) { // 1e5/928ms
    const int m = (int)x.size();
    std::vector<Poly<T>> up = Poly<T>::_tree1(x), down(m * 2);
    std::vector<T> z = up[1].Dx()._eval(x, up);
    for (int i = 0; i < m; ++i) z[i] = y[i] / z[i];
    for (int i = 0; i < m; ++i) down[m + i] = {z[i]};
    for (int i = m - 1; i > 0; --i) down[i] = down[i * 2] * up[i * 2 + 1] + down[i * 2 + 1] * up[i * 2];
    return down[1];
}
