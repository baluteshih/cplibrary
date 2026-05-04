#pragma once

#include "Numeric/pollard_rho.hpp"
#include "Numeric/mod_pow.hpp"

template<typename T>
T primitive_root(T p) {
    auto pfacs = pollard_rho(p - 1);
    std::ranges::sort(pfacs);
    pfacs.erase(std::ranges::unique(pfacs).begin(), pfacs.end());
    auto check = [&](T g) -> bool {
        for (auto pf : pfacs)
            if (mod_pow(g, (p - 1) / pf, p) == 1) return false;
        return true;
    };
    std::conditional_t<sizeof(T) == 4, std::mt19937, std::mt19937_64> rng(880301);
    while (1) {
        T x = rng() % (p - 1) + 1;
        if (check(x)) return x;
    }
    return -1;
}
