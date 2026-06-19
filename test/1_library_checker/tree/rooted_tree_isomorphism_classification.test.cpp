#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"
#include "assumption.hpp"

#include "Tree/Tree.hpp"
#include "DataStructure/Discretization.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    Tree tree(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        tree.add_edge(p, i);
    }
    auto res = tree.hash_values();
    Discretization val(res);
    std::cout << val.size() << "\n";
    for (int i = 0; i < n; ++i)
        std::cout << val.idx(res[i]) << " \n"[i + 1 == n];
}
