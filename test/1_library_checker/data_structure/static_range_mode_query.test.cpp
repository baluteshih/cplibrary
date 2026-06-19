#define PROBLEM "https://judge.yosupo.jp/problem/static_range_mode_query"
#include "assumption.hpp"

#include "Sequence/mo_solver.hpp"
#include "DataStructure/Discretization.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> arr(n);
    for (auto &i : arr)
        std::cin >> i;
    std::vector<std::pair<int, int>> querys(q);
    for (auto &[l, r] : querys)
        std::cin >> l >> r;
    Discretization val(arr);
    for (auto &i : arr)
        i = val.idx(i);
    std::vector<int> cnt(val.size()), cnt2(n + 1), pl(val.size());
    std::vector<std::vector<int>> pool(n + 1);
    std::iota(pl.begin(), pl.end(), 0);
    pool[0] = pl;
    std::vector<std::pair<int, int>> ans(q);

    auto pop = [&](int x) {
        std::swap(pool[cnt[x]][pl[x]], pool[cnt[x]].back());
        pl[pool[cnt[x]][pl[x]]] = pl[x];
        pool[cnt[x]].pop_back();
    };

    auto push = [&](int x) {
        pl[x] = pool[cnt[x]].size();
        pool[cnt[x]].push_back(x);
    };

    int mx = 0;
    cnt2[0] = val.size();
    mo_solver(querys, [&](int qid) {
        ans[qid] = std::make_pair(val[pool[mx].back()], mx);
    }, [&](int l) {
        --cnt2[cnt[arr[l]]], pop(arr[l]); 
        if (cnt[arr[l]] == mx) ++mx;
        ++cnt2[++cnt[arr[l]]], push(arr[l]);
    }, [&](int l) {
        --cnt2[cnt[arr[l]]], pop(arr[l]); 
        if (cnt2[mx] == 0) --mx;
        ++cnt2[--cnt[arr[l]]], push(arr[l]);
    });
    for (auto [v, c] : ans)
        std::cout << v << " " << c << "\n";
}
