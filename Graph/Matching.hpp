#pragma once

#include "Graph/base.hpp"

/*
match[u] = -1 implies no match
*/
struct Matching : public Graph<false, void, void> { // 0-base
    using super = Graph<false, void, void>;
    std::queue<int> q;
    std::vector<int> fa, s, vis, pre, match;
    int Find(int u)
    { return u == fa[u] ? u : fa[u] = Find(fa[u]); }
    int LCA(int x, int y) {
        static int tk = 0; tk++; x = Find(x); y = Find(y);
        for (;; swap(x, y)) if (x != this->n()) {
            if (vis[x] == tk) return x;
            vis[x] = tk;
            x = Find(pre[match[x]]);
        }
    }
    void Blossom(int x, int y, int l) {
        for (; Find(x) != l; x = pre[y]) {
            pre[x] = y, y = match[x];
            if (s[y] == 1) q.push(y), s[y] = 0;
            for (int z: {x, y}) if (fa[z] == z) fa[z] = l;
        }
    }
    bool Bfs(int r) {
        iota(ALL(fa), 0); fill(ALL(s), -1);
        q = queue<int>(); q.push(r); s[r] = 0;
        for (; !q.empty(); q.pop()) {
            for (int x = q.front(); auto [u, eid] : (*this)[x])
                if (s[u] == -1) {
                    if (pre[u] = x, s[u] = 1, match[u] == this->n()) {
                        for (int a = u, b = x, last; b != this->n(); a = last, b = pre[a])
                            last = match[b], match[b] = a, match[a] = b;
                        return true;
                    }
                    q.push(match[u]); s[match[u]] = 0;
                } else if (!s[u] && Find(u) != Find(x)) {
                    int l = LCA(u, x);
                    Blossom(x, u, l); Blossom(u, x, l);
                }
        }
        return false;
    }
    Matching(int n) : super(n), fa(n + 1), s(n + 1), vis(n + 1), pre(n + 1, n), match(n + 1, n) {}
    int solve() {
        int ans = 0;
        for (int x = 0; x < this->n(); ++x)
            if (match[x] == this->n())
                ans += Bfs(x);
        std::ranges::replace(match, this->n(), -1);
        return ans;
    }
};
