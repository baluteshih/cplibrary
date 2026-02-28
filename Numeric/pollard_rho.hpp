#pragma once

#include "Numeric/miller_rabin.hpp"

/*
return an unsorted prime list
*/
template<typename T>
std::vector<T> pollard_rho(T n) {
    static auto mul = [&](T x, T y, T mod) {
        if constexpr (sizeof(T) == 4) return (long long)x * y % mod;
        else return (__int128)x * y % mod;
    };
    std::vector<T> res;
    auto factorize = [&](auto self, T cur) -> void {
        if (cur == 1) return;
        if (miller_rabin(cur)) return res.push_back(cur);
        if (cur % 2 == 0) {
            int cnt = std::countr_zero(std::make_unsigned_t<T>(cur));
            res.resize(res.size() + cnt, 2);
            return self(self, cur >> cnt);
        }
        T p = 2, q, i = 1, x = 0, y = 0, t = 0, ct = 87;
        #define f(x) ((mul(x, x, cur) + ct) % cur)
        while (t++ % 64 || std::__gcd(p, cur) == 1) {
            if (x == y) x = i++, y = f(x);
            q = mul(p, x < y ? y - x : x - y, cur);
            if (q) p = q;
            if (p == cur) ++ct;
            x = f(x), y = f(f(y));
        }
        T d = std::__gcd(p, cur);
        self(self, cur / d);
        self(self, d);
    };
    factorize(factorize, n);
    return res;
}
