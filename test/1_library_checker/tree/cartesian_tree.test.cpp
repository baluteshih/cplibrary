#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "default_code.hpp"

#include "Sequence/better_position.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &i : arr)
        cin >> i;
    auto [lft, rgt] = better_position(arr);
    vector<int> ans(n);
    for (int i = 0; i < n; ++i)
        if (lft[i] == -1 && rgt[i] == n) ans[i] = i;
        else if (lft[i] == -1) ans[i] = rgt[i];
        else if (rgt[i] == n) ans[i] = lft[i];
        else ans[i] = arr[lft[i]] < arr[rgt[i]] ? rgt[i] : lft[i];
    for (int i = 0; i < n; ++i)
        cout << ans[i] << " \n"[i + 1 == n];
}
