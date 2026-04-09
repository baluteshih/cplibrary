#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"
#include "default_code.hpp"

#include "Tree/Tree.cpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    Tree tree(n);
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        tree.add_edge(p, i);
    }
    auto res = tree.hash_values();
    auto val = res;
    discretization(val);
    cout << val.size() << "\n";
    for (int i = 0; i < n; ++i)
        cout << std::ranges::lower_bound(val, res[i]) - val.begin() << " \n"[i + 1 == n];
}
