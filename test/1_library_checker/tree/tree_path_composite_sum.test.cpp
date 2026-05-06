#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"
#include "Tree/all_direction_composition.hpp"

using mint = modint998244353;

struct EdgeWeight {
    mint a, b;
    EdgeWeight(mint _a = 0, mint _b = 0): a(_a), b(_b) {}
    friend istream& operator>>(istream& is, EdgeWeight &v) {
        is >> v.a >> v.b;
        return is;
    }
};

struct VertexWeight {
    mint val, sz;
    VertexWeight(mint _v = 0, mint _sz = 0): val(_v), sz(_sz) {}
    VertexWeight operator+(const EdgeWeight &rhs) {
        return VertexWeight(rhs.a * val + rhs.b * sz, sz);
    }
    VertexWeight operator+(const VertexWeight &rhs) {
        return VertexWeight(val + rhs.val, sz + rhs.sz);
    }
    friend ostream& operator<<(ostream& os, const VertexWeight &v) {
        os << v.val;
        return os;
    }
    friend istream& operator>>(istream& is, VertexWeight &v) {
        is >> v.val;
        v.sz = 1;
        return is;
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    Tree<EdgeWeight, VertexWeight> tree(n);
    vector<VertexWeight> arr(n);
    for (auto &v : arr)
        cin >> v;
    tree.set_vertex_weight(arr);
    for (int i = 1; i < n; ++i) {
        int u, v;
        EdgeWeight w;
        cin >> u >> v >> w;
        tree.add_edge(u, v, w);
    }
    auto res = all_direction_composition(tree);
    for (int i = 0; i < n; ++i)
        cout << res[i] << " \n"[i + 1 == n];
}
