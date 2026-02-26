#pragma once

int Jacobi(int a, int m) {
    int s = 1;
    for (; m > 1; ) {
        a %= m;
        if (a == 0) return 0;
        const int r = std::countr_zero(static_cast<unsigned int>(a));
        if ((r & 1) && ((m + 2) & 4)) s = -s;
        a >>= r;
        if (a & m & 2) s = -s;
        std::swap(a, m);
    }
    return s;
}

#include "Numeric/Modint.hpp"

template<class T>
requires std::derived_from<T, internal::modint_base>
T QuadraticResidue(T a, bool &succ) {
    succ = true;
    if (T::mod() == 2) return a;
    const int jc = Jacobi(a.val(), T::mod());
    if (jc == 0) return 0;
    if (jc == -1) return succ = false, 0;
    T b, d;
    std::mt19937 rng(880301);
    for (; ; ) {
        b = rng() % T::mod();
        d = b * b - a;
        if (Jacobi(d.val(), T::mod()) == -1) break;
    }
    T f0 = b, f1 = 1, g0 = 1, g1 = 0, tmp;
    for (int e = (1LL + T::mod()) >> 1; e; e >>= 1) {
        if (e & 1) {
            tmp = g0 * f0 + d * g1 * f1;
            g1 = g0 * f1 + g1 * f0;
            g0 = tmp;
        }
        tmp = f0 * f0 + d * f1 * f1;
        f1 = f0 * f1 * 2;
        f0 = tmp;
    }
    return g0;
}
