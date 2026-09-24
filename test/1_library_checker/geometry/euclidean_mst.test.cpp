#define PROBLEM "https://judge.yosupo.jp/problem/euclidean_mst"
#include "assumption.hpp"
#include "default_code.hpp"

#include "Geometry/DelaunayTriangulation.hpp"
#include "Graph/minimum_spanning_tree.hpp"
#include "Sequence/same_position.hpp"

using Point = Pt<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<Point> vec(n);
    for (auto &p : vec)
        std::cin >> p;
    auto res = DelaunayTriangulation<Point, long long>(vec);
    auto edges = res.get_edges();
    UndirectedGraph<int> G(n);
    for (auto [u, v] : edges)
        G.add_edge(u, v, dist2(vec[u], vec[v]));
    auto prev = previous_same_position(vec);
    for (int i = 0; i < n; ++i)
        if (prev[i] != -1)
            G.add_edge(i, prev[i], 0);
    auto ans = minimum_spanning_tree(G);
    for (int e : ans)
        std::cout << G.edge(e).from << " " << G.edge(e).to << "\n";
}
