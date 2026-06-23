#define PROBLEM "https://judge.yosupo.jp/problem/double_ended_priority_queue"
#include "assumption.hpp"

#include "DataStructure/MinMaxHeap.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    MinMaxHeap<int> heap;
    while (n--) {
        int x;
        std::cin >> x;
        heap.push(x);
    }
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 0) {
            int x;
            std::cin >> x;
            heap.push(x);
        }
        else if (op == 1) {
            std::cout << heap.top_min() << "\n";
            heap.pop_min();
        }
        else {
            std::cout << heap.top_max() << "\n";
            heap.pop_max();
        }
    }
}
