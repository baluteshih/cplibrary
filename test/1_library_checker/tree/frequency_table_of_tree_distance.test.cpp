#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
#include "default_code.hpp"

#include "Tree/centroid_divide_and_conquer.hpp"
#include "Convolution/convolution.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    Tree tree(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        tree.add_edge(u, v);
    }
    vector<int> depth(n);
    vector<ll> ans(n);
    centroid_divide_and_conquer(tree, [&](int u, int f) {
        if (f == -1) depth[u] = 0;
        else depth[u] = depth[f] + 1;
    }, [&](int c, const vector<vector<int>> &groups) {
        (void)c;
        if (groups.empty()) return;
        int mx = 0;
        for (auto &vec : groups)
            for (auto v : vec)
                chmax(mx, depth[v] + 1);
        vector<ll> cnt(mx);
        cnt[0] = 1;
        for (auto &vec : groups)
            for (auto v : vec)
                ++cnt[depth[v]];
        convolution<2>(cnt, cnt).swap(cnt);
        for (int i = 0; i < int(cnt.size()); ++i)
            ans[i] += cnt[i];
        for (auto &vec : groups) {
            mx = 0;
            for (auto v : vec)
                chmax(mx, depth[v] + 1);
            std::vector<ll>(mx).swap(cnt);
            for (auto v : vec)
                ++cnt[depth[v]];
            convolution<2>(cnt, cnt).swap(cnt);
            for (int i = 0; i < int(cnt.size()); ++i)
                ans[i] -= cnt[i];
        }
    });
    for (int i = 1; i < n; ++i)
        cout << ans[i] / 2 << " \n"[i + 1 == n];
}
