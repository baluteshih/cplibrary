#define PROBLEM "https://judge.yosupo.jp/problem/tree_path_composite_sum"
#include "assumption.hpp"

#include "Numeric/Modint.hpp"
#include "Tree/all_direction_composition.hpp"

using mint = modint998244353;

struct EdgeWeight {
    mint a, b;
    EdgeWeight(mint _a = 0, mint _b = 0): a(_a), b(_b) {}
    friend std::istream& operator>>(std::istream& is, EdgeWeight &v) {
        is >> v.a >> v.b;
        return is;
    }
};

struct VertexWeight {
    mint val, sz;
    VertexWeight(mint _v = 0, mint _sz = 0): val(_v), sz(_sz) {}
    VertexWeight operator+(const EdgeWeight &rhs) const {
        return VertexWeight(rhs.a * val + rhs.b * sz, sz);
    }
    VertexWeight operator+(const VertexWeight &rhs) const {
        return VertexWeight(val + rhs.val, sz + rhs.sz);
    }
    friend std::ostream& operator<<(std::ostream& os, const VertexWeight &v) {
        os << v.val;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, VertexWeight &v) {
        is >> v.val;
        v.sz = 1;
        return is;
    }
};

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    Tree<EdgeWeight, VertexWeight> tree(n);
    std::vector<VertexWeight> arr(n);
    for (auto &v : arr)
        std::cin >> v;
    tree.set_vertex_weight(arr);
    for (int i = 1; i < n; ++i) {
        int u, v;
        EdgeWeight w;
        std::cin >> u >> v >> w;
        tree.add_edge(u, v, w);
    }
    auto res = all_direction_composition(tree);
    for (int i = 0; i < n; ++i)
        std::cout << res[i] << " \n"[i + 1 == n];
}
