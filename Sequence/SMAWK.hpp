#pragma once

// source: https://github.com/abc864197532/std_abs/blob/main/codebook/Else/Smawk.cpp

// For all 2x2 submatrix of f(i, j):
// If M[1][0] < M[1][1], M[0][0] < M[0][1]
// If M[1][0] == M[1][1], M[0][0] <= M[0][1]
// M[i][ans_i] is the best value in the i-th row
std::vector<int> SMAWK(int _n, int _m, auto &&f) {
    auto select = [&](int r, int u, int v) {
        // if f(r, v) is better than f(r, u), return true
        return f(r, u) > f(r, v);
    };
    auto solve = [&](auto self, std::vector<int> &r, std::vector<int> &c) -> std::vector<int> {
        const int n = r.size();
        if (n == 0) return {};
        std::vector <int> c2;
        for (const int &i : c) {
            while (!c2.empty() && select(r[c2.size() - 1], c2.back(), i)) c2.pop_back();
            if (int(c2.size()) < n) c2.push_back(i);
        }
        std::vector <int> r2;
        for (int i = 1; i < n; i += 2) r2.push_back(r[i]);
        const auto a2 = self(self, r2, c2);
        std::vector <int> ans(n);
        for (int i = 0; i < int(a2.size()); ++i)
            ans[i * 2 + 1] = a2[i];
        int j = 0;
        for (int i = 0; i < n; i += 2) {
            ans[i] = c2[j];
            const int end = i + 1 == n ? c2.back() : ans[i + 1];
            while (c2[j] != end) {
                j++;
                if (select(r[i], ans[i], c2[j])) ans[i] = c2[j];
            }
        }
        return ans;
    };
    std::vector<int> row(_n), col(_m);
    std::iota(row.begin(), row.end(), 0), std::iota(col.begin(), col.end(), 0);
    return solve(solve, row, col);
}

