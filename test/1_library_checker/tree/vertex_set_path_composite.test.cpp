#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"
#include "Tree/HeavyLightDecomposition.hpp"
#include "DataStructure/SegmentTree.hpp"

using mint = modint998244353;

template<bool rv = false>
struct Value {
    mint a, b;
    Value(mint _a = 0, mint _b = 0): a(_a), b(_b) {}
    template<typename Vother>
    Value(const Vother &v): a(v.a), b(v.b) {}
    Value operator+(const Value &rhs) {
        if constexpr (rv) return Value(a * rhs.a, rhs.a * b + rhs.b);
        else return Value(a * rhs.a, a * rhs.b + b);
    }
    mint get_val(mint x) {
        return a * x + b;
    }
    friend ostream& operator<<(ostream& os, const Value &v) {
        os << v.a << " " << v.b;
        return os;
    }
    friend istream& operator>>(istream& is, Value &v) {
        is >> v.a >> v.b;
        return is;
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    HeavyLightDecomposition<> hld(n);
    vector<Value<false>> arr(n);
    for (auto &i : arr)
        cin >> i;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }
    hld.build();
    vector<Value<false>> weight(n);
    for (int i = 0; i < n; ++i)
        weight[i] = arr[hld.preorder[i]];
    vector<Value<true>> rweight(weight.begin(), weight.end());
    SegmentTree<Value<false>> seg(weight);
    SegmentTree<Value<true>> rseg(rweight);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int p;
            Value v;
            cin >> p >> v;
            seg.modify(hld.dfs_in[p], v);
            rseg.modify(hld.dfs_in[p], v);
        }
        else {
            int u, v;
            mint x;
            cin >> u >> v >> x;
            hld.work_path<false>(u, v, [&](int l, int r, bool is_up) {
                if (is_up) x = seg.range_prod(l, r).get_val(x); 
                else x = rseg.range_prod(l, r).get_val(x);
            }); 
            cout << x << "\n";
        }
    }
}
