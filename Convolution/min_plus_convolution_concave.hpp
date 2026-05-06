#pragma once

// a is concave, i.e. a[i + 1] - a[i] >= a[i + 2] - a[i + 1]
template<typename T>
vector<T> min_plus_convolution_concave(vector<T> &a, vector<T> &b) {
    static constexpr T inf = std::numeric_limits<T>::max();
    int n = a.size(), m = b.size();
    vector<T> c(n + m - 1, inf);
    auto cal_min = [&](int k, int l, int r) -> std::pair<int, T> {
        r = std::min({r, k + 1, m});
        l = std::max({l, k - (n - 1), 0});
        std::pair<int, T> mn{l, inf};
        for (int i = l; i < r; i++) {
            if (k - i < 0 || k - i >= n) continue;
            if (a[k - i] + b[i] < mn.second)
                mn = {i, a[k - i] + b[i]};
        }
        return mn;
    };
    auto dc = [&](auto self, int l, int r, int jl, int jr) -> void {
        l = std::max(l, jl);
        r = std::min(r, jr + n - 1);
        if (l >= r || jl >= jr) return;
        int mc = (l + r) / 2;
        auto [mb, x] = cal_min(mc, jl, jr);
        if (x == inf) return;
        c[mc] = std::min(c[mc], x);
        
        self(self, l, mc, jl, std::min(mb + 1, mc - (n - 1)));
        self(self, l, std::min(mb, mc), std::max(jl, mc - n), mb);
        self(self, std::max(mb, l), mc, mb, jr);

        self(self, mc + 1, std::min(r, mb + n), std::max(jl, mc - (n - 1)), mb + 1);
        self(self, std::max(mc + 1, mb + n - 1), r, mb, std::min(jr, mc));
        self(self, mc + 1, r, std::max(mc, jl), jr);
    };
    return dc(dc, 0, n + m - 1, 0, m), c;
}
