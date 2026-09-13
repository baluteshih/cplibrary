#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"
#include "assumption.hpp"

#include "DataStructure/OrderedSet.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> arr(n);
    for (int &i : arr)
        std::cin >> i;
    OrderedSet<int> ord(arr.begin(), arr.end());
    std::vector<std::pair<int, int>> qry(q);
    for (auto &[t, x] : qry) {
        std::cin >> t >> x;
        if (t == 0 || t == 1)
            ord.push_back(x);
    }
    ord.push_back(0);
    ord.build();
    for (int i : arr)
        ord.insert(i);
    for (auto &[t, x] : qry) {
        if (t == 0) ord.insert(x);
        else if (t == 1) ord.erase(x);
        else if (t == 2) {
            int res = ord.kth(x - 1);
            if (res != -1) res = ord[res]; 
            std::cout << res << "\n";
        }
        else if (t == 3)
            std::cout << ord.leq_count(x) << "\n";
        else if (t == 4) {
            int res = ord.leq(x);
            if (res != -1) res = ord[res]; 
            std::cout << res << "\n";
        }
        else {
            int res = ord.geq(x);
            if (res != -1) res = ord[res]; 
            std::cout << res << "\n";
        }
    }
}
