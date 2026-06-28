#pragma once

#include "Numeric/internal_math.hpp"

template<class T>
requires std::derived_from<T, internal::modint_base>
class Combination {
    inline static int N = 1;
public:
    inline static std::vector<T> fac = {T(1)};
    inline static std::vector<T> ifac = {T(1)};
    Combination(int n) { ensure_upper_bound(n); }
    T C(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac[n] * ifac[m] * ifac[n - m];
    }
    T invC(int n, int m) {
        assert(n >= m && m >= 0);
        return ifac[n] * fac[m] * fac[n - m];
    }
    T P(int n, int m) {
        if (n < m) return 0;
        return fac[n] * ifac[n - m];
    }
    T H(int n, int m) {
        return C(n + m - 1, m);
    }
    // a - b <= k and all non-empty proper prefix have a - b < k
    T extend_catalan(int a, int b, int k) {
        if (a - b == k) return C(a + b - 1, a - 1) - C(a + b - 1, b + k);
        return C(a + b, a) - C(a + b, b + k); 
    }
    void ensure_upper_bound(int n) {
        if (N >= n) return;
        fac.resize(n), ifac.resize(n);
        for (int i = N; i < n; ++i)
            fac[i] = fac[i - 1] * i;
        ifac.back() = fac.back().inv();
        for (int i = n - 2; i >= N; --i)
            ifac[i] = ifac[i + 1] * (i + 1);
        N = n;
    }
};
namespace CombFunc {
template<class T>
std::vector<T> power(T base, int n) {
    std::vector<T> res(n + 1, 1);
    for (int i = 1; i <= n; ++i)
        res[i] = res[i - 1] * base;
    return res;
}
template<class T>
std::vector<T> ipower(T base, int n) {
    return power(base.inv(), n);
}
template<class T>
std::vector<T> linear_inverse(int n) {
    std::vector<T> res(n + 1, 1);
    int MOD = T().mod();
    for (int i = 2; i <= n; ++i) {
        res[i] = res[MOD % i] * (MOD - MOD / i); 
    }
    return res;
}
}
