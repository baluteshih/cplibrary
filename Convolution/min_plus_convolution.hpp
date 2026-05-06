#pragma once

// a is convex, i.e. a[i + 1] - a[i] <= a[i + 2] - a[i + 1]
template<typename T>
vector<T> min_plus_convolution(vector<T> &a, vector<T> &b) {
    int n = a.size(), m = b.size();
    vector<T> c(n + m - 1, std::numeric_limits<T>::max());
    auto dc = [&](auto self, int l, int r, int jl, int jr) -> void {
        if (l > r) return;
        int mid = (l + r) / 2, from = -1;
        T &best = c[mid];
        for (int j = jl; j <= jr; ++j)
            if (int i = mid - j; i >= 0 && i < n)
                if (best > a[i] + b[j]) 
                    best = a[i] + b[j], from = j;
        self(self, l, mid - 1, jl, from), self(self, mid + 1, r, from, jr);
    };
    return dc(dc, 0, n - 1 + m - 1, 0, m - 1), c;
}
