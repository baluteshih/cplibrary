#pragma once

#include "Algebra/Monoid/concept.hpp"

template<class Value, bool ImplicitJump = false>
class Doubling {
    struct Empty {};
    static constexpr bool hasValue = isMonoid<Value>;
    static_assert(hasValue || !ImplicitJump);
    inline int get_nxt(int j, int i) const {
        if constexpr (ImplicitJump) return std::min(n - 1, i + (1 << j));
        else return nxt[j][i];
    }
    void build() {
        for (int j = 1; j < max_log; ++j)
            for (int i = 0; i < n; ++i) {
                if constexpr (!ImplicitJump) nxt[j][i] = nxt[j - 1][nxt[j - 1][i]];
                if constexpr (hasValue) val[j][i] = val[j - 1][i] + val[j - 1][get_nxt(j - 1, i)]; 
            }
    }
public:
    int n, max_log;
    [[no_unique_address]] std::conditional_t<ImplicitJump, Empty, std::vector<std::vector<int>>> nxt;
    [[no_unique_address]] std::conditional_t<hasValue, std::vector<std::vector<Value>>, Empty> val; 
    Doubling() : n(0), max_log(0) {}
    Doubling(int _n, const std::ranges::range auto &init_nxt) requires (!hasValue && !ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned int>(n)) + 1) { 
        nxt.assign(max_log, std::vector<int>(n)); 
        std::ranges::copy(init_nxt, nxt[0].begin());
        build(); 
    }
    Doubling(int _n, const std::ranges::range auto &init_val) requires (hasValue && ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned int>(n)) + 1) { 
        val.assign(max_log, std::vector<Value>(n)); 
        std::ranges::copy(init_val, val[0].begin());
        build(); 
    }
    Doubling(int _n, const std::ranges::range auto &init_nxt, const std::ranges::range auto &init_val) requires (hasValue && !ImplicitJump) : n(_n), max_log(std::bit_width(static_cast<unsigned int>(n)) + 1) { 
        nxt.assign(max_log, std::vector<int>(n)); 
        val.assign(max_log, std::vector<Value>(n)); 
        std::ranges::copy(init_nxt, nxt[0].begin());
        std::ranges::copy(init_val, val[0].begin());
        build(); 
    }
    template<typename F_cond>
    int maximal_prefix(int u, F_cond cond) {
        if (!cond(u)) return -1;
        for (int i = max_log - 1; i >= 0; --i)
            if (cond(get_nxt(i, u)))
                u = get_nxt(i, u);
        return u;
    }
    template<typename F_cond>
    auto maximal_prefix_prod(int u, F_cond cond) requires (hasValue) {
        if (!cond(u)) return std::make_pair(Value(), -1);
        Value res = Value();
        for (int i = max_log - 1; i >= 0; --i)
            if (cond(get_nxt(i, u))) {
                res = res + val[i][u];
                u = get_nxt(i, u);
            }
        return std::make_pair(res, u);
    }
    int step(int u, int d) {
        for (; d; d -= d & -d) u = get_nxt(std::__lg(d & -d), u);
        return u;
    }
};
