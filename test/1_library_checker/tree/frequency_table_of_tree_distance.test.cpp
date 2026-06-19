#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
#include "assumption.hpp"

#include "Tree/centroid_divide_and_conquer.hpp"
#include "Convolution/convolution.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    Tree tree(n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        tree.add_edge(u, v);
    }
    std::vector<int> depth(n);
    std::vector<long long> ans(n);
    centroid_divide_and_conquer(tree, [&](int u, int f) {
        if (f == -1) depth[u] = 0;
        else depth[u] = depth[f] + 1;
    }, [&](int c, const std::vector<std::vector<int>> &groups) {
        (void)c;
        if (groups.empty()) return;
        int mx = 0;
        for (auto &vec : groups)
            for (auto v : vec)
                mx = std::max(mx, depth[v] + 1);
        std::vector<long long> cnt(mx);
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
                mx = std::max(mx, depth[v] + 1);
            std::vector<long long>(mx).swap(cnt);
            for (auto v : vec)
                ++cnt[depth[v]];
            convolution<2>(cnt, cnt).swap(cnt);
            for (int i = 0; i < int(cnt.size()); ++i)
                ans[i] -= cnt[i];
        }
    });
    for (int i = 1; i < n; ++i)
        std::cout << ans[i] / 2 << " \n"[i + 1 == n];
}
