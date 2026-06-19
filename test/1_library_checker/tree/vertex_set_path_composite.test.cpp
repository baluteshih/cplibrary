#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"
#include "assumption.hpp"

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
    friend std::ostream& operator<<(std::ostream& os, const Value &v) {
        os << v.a << " " << v.b;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Value &v) {
        is >> v.a >> v.b;
        return is;
    }
};

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    HeavyLightDecomposition<> hld(n);
    std::vector<Value<false>> arr(n);
    for (auto &i : arr)
        std::cin >> i;
    for (int i = 1; i < n; ++i) {
        int u, v;
        std::cin >> u >> v;
        hld.add_edge(u, v);
    }
    hld.build();
    std::vector<Value<false>> weight(n);
    for (int i = 0; i < n; ++i)
        weight[i] = arr[hld.preorder[i]];
    std::vector<Value<true>> rweight(weight.begin(), weight.end());
    SegmentTree<Value<false>> seg(weight);
    SegmentTree<Value<true>> rseg(rweight);
    while (q--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int p;
            Value v;
            std::cin >> p >> v;
            seg.modify(hld.dfs_in[p], v);
            rseg.modify(hld.dfs_in[p], v);
        }
        else {
            int u, v;
            mint x;
            std::cin >> u >> v >> x;
            hld.work_path<false>(u, v, [&](int l, int r, bool is_up) {
                if (is_up) x = seg.range_prod(l, r).get_val(x); 
                else x = rseg.range_prod(l, r).get_val(x);
            }); 
            std::cout << x << "\n";
        }
    }
}
