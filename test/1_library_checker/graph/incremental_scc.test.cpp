#define PROBLEM "https://judge.yosupo.jp/problem/incremental_scc"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"
#include "Graph/incremental_scc.hpp"
#include "DataStructure/DisjointSet.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<mint> arr(n);
    for (auto &i : arr)
        std::cin >> i;
    Graph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        G.add_edge(u, v);
    }
    auto res = incremental_scc(G);
    DisjointSet<mint> djs(arr);
    std::vector<int> idx(m);
    std::iota(idx.begin(), idx.end(), 0);
    std::ranges::sort(idx, [&](int a, int b) {
        return res[a] < res[b]; 
    });
    std::vector<mint> ans(m);
    for (int i : idx) {
        if (res[i] == m) break;
        mint lft = djs.getdata(G.edge(i).from);
        mint rgt = djs.getdata(G.edge(i).to);
        if (djs.merge(G.edge(i).from, G.edge(i).to))
            ans[res[i]] += lft * rgt;
    }
    std::partial_sum(ans.begin(), ans.end(), ans.begin());
    for (auto &i : ans)
        std::cout << i << "\n";
}
