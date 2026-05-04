#pragma once

#include "Numeric/internal_math.hpp"
#include "Numeric/primitive_root.hpp"
#include "Numeric/pollard_rho.hpp"
#include "Numeric/mod_inv.hpp"

// source: https://maspypy.github.io/library/mod/binomial.hpp
struct BinomialPrimePower {
    using barrett = internal::barrett;
    int p, e, pp, root, ord;
    std::vector<int> exp, log_fact, power;
    barrett bt_p, bt_pp;
    BinomialPrimePower(int _p, int _e) : p(_p), e(_e), power(e + 1, 1), bt_p(1), bt_pp(1) {
        for (int i = 0; i < e; ++i) power[i + 1] = power[i] * p;
        pp = power[e];
        bt_p = barrett(p), bt_pp = barrett(pp);
        std::vector<int> log;
        if (p == 2) {
            if (e <= 1) { return; }
            root = 5;
            ord = pp / 4;
            exp.assign(ord, 1);
            log.assign(pp, 0);
            for (int i = 0; i < ord - 1; ++i) { exp[i + 1] = (exp[i] * root) & (pp - 1); }
            for (int i = 0; i < ord; ++i) log[exp[i]] = log[pp - exp[i]] = i;
        }
        else {
            root = primitive_root(p);
            ord = pp / p * (p - 1);
            exp.assign(ord, 1);
            log.assign(pp, 0);
            for (int i = 0; i < ord - 1; ++i) { exp[i + 1] = bt_pp.mul(exp[i], root); }
            for (int i = 0; i < ord; ++i) log[exp[i]] = i;
        }
        log_fact.assign(pp, 0);
        for (int i = 1; i < pp; ++i) {
            log_fact[i] = log_fact[i - 1] + log[i];
            if (log_fact[i] >= ord) log_fact[i] -= ord;
        }
    }
    int C(long long n, long long i) {
        assert(n >= 0);
        if (i < 0 || i > n) return 0;
        long long a = i, b = n - i;
        if (pp == 2) { return ((a & b) == 0 ? 1 : 0); }
        int log = 0, cnt_p = 0, sgn = 0;
        if (e > 1) {
            while (n && cnt_p < e) {
                auto [n1, nr1] = bt_pp.divmod(n);
                auto [a1, ar1] = bt_pp.divmod(a);
                auto [b1, br1] = bt_pp.divmod(b);
                log += log_fact[nr1] - log_fact[ar1] - log_fact[br1];
                if (p > 2) sgn += (n1 & 1) + (a1 & 1) + (b1 & 1);
                else sgn += (((nr1 + 1) & 4) + ((ar1 + 1) & 4) + ((br1 + 1) & 4)) / 4;
                n = bt_p.floor(n), a = bt_p.floor(a), b = bt_p.floor(b);
                cnt_p += n - a - b;
            }
        }
        else {
            while (n && cnt_p < e) {
                auto [n1, nr1] = bt_pp.divmod(n);
                auto [a1, ar1] = bt_pp.divmod(a);
                auto [b1, br1] = bt_pp.divmod(b);
                log += log_fact[nr1] - log_fact[ar1] - log_fact[br1];
                if (p > 2)
                    sgn += (n1 & 1) + (a1 & 1) + (b1 & 1);
                else
                    sgn += ((nr1 + 1) >> 2 & 1) + ((ar1 + 1) >> 2 & 1) + ((br1 + 1) >> 2 & 1);
                n = n1, a = a1, b = b1;
                cnt_p += n - a - b;
            }
        }
        if (cnt_p >= e) return 0;
        log %= ord;
        if (log < 0) log += ord;
        int res = exp[log];
        if (sgn & 1) res = pp - res;
        return bt_pp.mul(power[cnt_p], res);
    }
};

struct Binomial {
    using barrett = internal::barrett;
    int mod;
    std::vector<BinomialPrimePower> BPP;
    std::vector<int> crt_coef;
    barrett bt;
    Binomial(int _mod) : mod(_mod), bt(mod) {
        auto pfacs = pollard_rho(mod);
        std::ranges::sort(pfacs);
        for (int i = 0, j = 0; i < int(pfacs.size()); i = j) {
            int pp = 1;
            while (j < int(pfacs.size()) && pfacs[i] == pfacs[j]) ++j, pp *= pfacs[i];
            BPP.emplace_back(pfacs[i], j - i);
            int other = mod / pp;
            crt_coef.push_back((long long)other * mod_inv(other, pp) % mod);
        }
    }
    int C(long long n, long long k) {
        assert(n >= 0);
        if (k < 0 || k > n) return 0;
        int ans = 0;
        for (int s = 0; s < int(crt_coef.size()); ++s)
            ans = bt.modulo(ans + (unsigned long long)(BPP[s].C(n, k)) * crt_coef[s]);
        return ans;
    }
};
