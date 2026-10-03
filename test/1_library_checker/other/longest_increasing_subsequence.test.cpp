#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"
#include "assumption.hpp"

#include "Sequence/longest_increasing_subsequence.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int &i : arr) std::cin >> i;
    auto ans = longest_increasing_subsequence(arr);
    std::cout << ans.size() << "\n";
    for (int i = 0; i < int(ans.size()); ++i)
        std::cout << ans[i] << " \n"[i + 1 == int(ans.size())]; 
}
