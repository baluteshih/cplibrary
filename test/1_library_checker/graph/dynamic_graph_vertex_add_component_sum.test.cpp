#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"
#include "default_code.hpp"

#include "DataStructure/DisjointSet.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    std::vector<ll> arr(n);
    for (ll &i : arr)
        cin >> i;
    DisjointSet<ll, true> djs(arr);
    vector<vector<array<int, 3>>> event(q << 2);

    auto add_event = [&](auto self, int L, int R, int l, int r, int rt, const array<int, 3> &e) -> void {
        if (L <= l && R >= r)
            return event[rt].push_back(e);
        int mid = (l + r) >> 1;
        if (L <= mid) self(self, L, R, l, mid, rt << 1, e);
        if (R > mid) self(self, L, R, mid + 1, r, rt << 1 | 1, e);
    };

    vector<ll> ans;
    map<pii, int> vis;
    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 0) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            vis[pii(u, v)] = i;
        }
        else if (type == 1) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            add_event(add_event, vis[pii(u, v)], i - 1, 0, q - 1, 1, array<int, 3>{0, u, v});
            vis.erase(pii(u, v));
        }
        else if (type == 2) {
            int v, x;
            cin >> v >> x;
            add_event(add_event, i, q - 1, 0, q - 1, 1, array<int, 3>{1, v, x});
        }
        else {
            int v;
            cin >> v;
            add_event(add_event, i, i, 0, q - 1, 1, array<int, 3>{2, v, int(ans.size())});
            ans.push_back(0);
        }
    }
    for (auto [p, t] : vis)
        add_event(add_event, t, q - 1, 0, q - 1, 1, array<int, 3>{0, p.first, p.second});

    auto dq = [&](auto self, int l, int r, int rt) -> void {
        auto version = djs.version();
        vector<pii> ask;
        for (auto [type, a, b] : event[rt])
            if (type == 0)
                djs.merge(a, b);
            else if (type == 1)
                djs.data_transform(a, [&](ll &x) {
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
    for (ll &i : ans)
        cout << i << "\n";
}
