#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"
#include "assumption.hpp"

#include "DataStructure/PartitionTree.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> arr(n);
    for (int &i : arr) std::cin >> i;
    PartitionTree<int> tree(arr);
    while (q--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << tree.kth_smallest(l, r, k + 1) << "\n";
    }
}
