#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"
#include "assumption.hpp"

#include "DataStructure/DisjointSet.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> arr(n);
    for (long long &i : arr)
        std::cin >> i;
    DisjointSet<long long, true> djs(arr);
    std::vector<std::vector<std::array<int, 3>>> event(q << 2);

    auto add_event = [&](auto self, int L, int R, int l, int r, int rt, const std::array<int, 3> &e) -> void {
        if (L <= l && R >= r)
            return event[rt].push_back(e);
        int mid = (l + r) >> 1;
        if (L <= mid) self(self, L, R, l, mid, rt << 1, e);
        if (R > mid) self(self, L, R, mid + 1, r, rt << 1 | 1, e);
    };

    std::vector<long long> ans;
    std::map<std::pair<int, int>, int> vis;
    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int u, v;
            std::cin >> u >> v;
            if (u > v) std::swap(u, v);
            vis[std::pair<int, int>(u, v)] = i;
        }
        else if (type == 1) {
            int u, v;
            std::cin >> u >> v;
            if (u > v) std::swap(u, v);
            add_event(add_event, vis[std::pair<int, int>(u, v)], i - 1, 0, q - 1, 1, std::array<int, 3>{0, u, v});
            vis.erase(std::pair<int, int>(u, v));
        }
        else if (type == 2) {
            int v, x;
            std::cin >> v >> x;
            add_event(add_event, i, q - 1, 0, q - 1, 1, std::array<int, 3>{1, v, x});
        }
        else {
            int v;
            std::cin >> v;
            add_event(add_event, i, i, 0, q - 1, 1, std::array<int, 3>{2, v, int(ans.size())});
            ans.push_back(0);
        }
    }
    for (auto [p, t] : vis)
        add_event(add_event, t, q - 1, 0, q - 1, 1, std::array<int, 3>{0, p.first, p.second});

    auto dq = [&](auto self, int l, int r, int rt) -> void {
        auto version = djs.version();
        std::vector<std::pair<int, int>> ask;
        for (auto [type, a, b] : event[rt])
            if (type == 0)
                djs.merge(a, b);
            else if (type == 1)
                djs.data_transform(a, [&](long long &x) {
                    x += b; 
                });
            else
                ask.emplace_back(a, b);
        if (l == r) {
            for (auto [v, qid] : ask)
                ans[qid] = djs.getdata(v);
        }
        else {
            int mid = (l + r) >> 1;
            self(self, l, mid, rt << 1);
            self(self, mid + 1, r, rt << 1 | 1);
        }
        djs.undo(version);
    };
    dq(dq, 0, q - 1, 1);
    for (long long &i : ans)
        std::cout << i << "\n";
}
