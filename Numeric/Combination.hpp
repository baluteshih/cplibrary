#pragma once

#include "Numeric/internal_math.hpp"

template<class T>
requires std::derived_from<T, internal::modint_base>
class Combination {
    int N;
    void init() {
        for (int i = 1; i <= N; ++i)
            fac[i] = fac[i - 1] * i;
        ifac.back() = fac.back().inv();
        for (int i = N - 1; i >= 0; --i)
            ifac[i] = ifac[i + 1] * (i + 1);
    }
public:
    vector<T> fac, ifac;
    Combination(int n): N(n), fac(N + 1, 1), ifac(N + 1, 1) {
        init();
    }
    Combination(int n, T base): N(n), fac(N + 1, base.raw(1)), ifac(N + 1, base.raw(1)) {
        init();
    }
    T C(int n, int m) {
        if (n < m) return 0;
        return fac[n] * ifac[m] * ifac[n - m];
    }
    T P(int n, int m) {
        if (n < m) return 0;
        return fac[n] * ifac[n - m];
    }
    T H(int n, int m) {
        return C(n + m - 1, m);
    }
};
namespace CombFunc {
template<class T>
vector<T> power(T base, int n) {
    vector<T> res(n + 1, 1);
    for (int i = 1; i <= n; ++i)
        res[i] = res[i - 1] * base;
    return res;
}
template<class T>
vector<T> ipower(T base, int n) {
    return power(base.inv(), n);
}
template<class T>
vector<T> linear_inverse(int n) {
    vector<T> res(n + 1, 1);
    int MOD = T().mod();
    for (int i = 2; i <= n; ++i) {
        res[i] = res[MOD % i] * (MOD - MOD / i); 
    }
    return res;
}
}
