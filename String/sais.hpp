#pragma once

/*
0-base
The input string should not contain 0
sa[i]: sa[i]-th suffix is the i-th lexicographically smallest suffix.
hi[i]: LCP of suffix sa[i] and suffix sa[i - 1].
ra[i]: the rank of the i-th suffix
*/
struct Suffix {
    int n; std::vector<int> sa, hi, ra;
    Suffix(const auto &_s, int _n) : n(_n), hi(n), ra(n) {
        for (const auto &c : _s) assert(c != 0);
        std::vector<int> s(_s.begin(), _s.end());
        s.push_back(0);
        sa = sais(s); sa.erase(sa.begin());
        for (int i = 0; i < n; ++i) ra[sa[i]] = i;
        for (int i = 0, h = 0; i < n; ++i) {
            if (!ra[i]) { h = 0; continue; }
            for (int j = sa[ra[i] - 1]; std::max(i, j) + h < n && s[i + h] == s[j + h];) ++h;
            hi[ra[i]] = h ? h-- : 0;
        }
    }
    Suffix(const auto &_s) : Suffix(_s, (int)_s.size()) {}
    static auto sais(const auto &s) {
        const int n = SZ(s), z = std::ranges::max(s) + 1;
        if (n == 1) return std::vector{0};
        std::vector<int> c(z); for (int x : s) ++c[x];
        std::partial_sum(c.begin(), c.end(), c.begin());
        std::vector<int> sa(n);
        auto I = std::views::iota(0, n);
        std::vector<bool> t(n, true);
        for (int i = n - 2; i >= 0; --i)
            t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
        auto is_lms = std::views::filter([&t](int x) { 
            return x && t[x] && !t[x - 1];
        });
        auto induce = [&] {
            for (auto x = c; int y : sa)
                if (y--) if (!t[y]) sa[x[s[y] - 1]++] = y;
            for (auto x = c; int y : sa | std::views::reverse)
                if (y--) if (t[y]) sa[--x[s[y]]] = y;
        };
        std::vector<int> lms, q(n);
        lms.reserve(n);
        for (auto x = c; int i : I | is_lms)
            q[i] = lms.size(), lms.push_back(sa[--x[s[i]]] = i);
        induce();
        std::vector<int> ns(lms.size());
        for (int j = -1, nz = 0; int i : sa | is_lms) {
            if (j >= 0) {
                int len = min({n - i, n - j, lms[q[i] + 1] - i});
                ns[q[i]] = nz += std::lexicographical_compare(std::begin(s) + j, std::begin(s) + j + len, std::begin(s) + i, std::begin(s) + i + len);
            }
            j = i;
        }
        std::ranges::fill(sa, 0);
        auto nsa = sais(ns);
        for (auto x = c; int y : nsa | std::views::reverse)
            y = lms[y], sa[--x[s[y]]] = y;
        return induce(), sa;
    }
};
