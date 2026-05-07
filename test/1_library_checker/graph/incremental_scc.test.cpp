#define PROBLEM "https://judge.yosupo.jp/problem/incremental_scc"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"
#include "Graph/incremental_scc.hpp"
#include "DataStructure/DisjointSet.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<mint> arr(n);
    for (auto &i : arr)
        cin >> i;
    Graph G(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        G.add_edge(u, v);
    }
    auto res = incremental_scc(G);
    DisjointSet<mint> djs(arr);
    vector<int> idx(m);
    iota(idx.begin(), idx.end(), 0);
    ranges::sort(idx, [&](int a, int b) {
        return res[a] < res[b]; 
    });
    vector<mint> ans(m);
    for (int i : idx) {
        if (res[i] == m) break;
        mint lft = djs.getdata(G.edge(i).from);
        mint rgt = djs.getdata(G.edge(i).to);
        if (djs.merge(G.edge(i).from, G.edge(i).to))
            ans[res[i]] += lft * rgt;
    }
    partial_sum(ans.begin(), ans.end(), ans.begin());
    for (auto &i : ans)
        cout << i << "\n";
}
