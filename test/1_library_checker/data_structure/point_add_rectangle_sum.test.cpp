#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include "assumption.hpp"

#include "Sequence/cdq_solver.hpp"
#include "DataStructure/BIT.hpp"
#include "DataStructure/Discretization.hpp"

struct Element {
    int x;
    int l, r;
    int val;
    bool operator<(const Element &rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return r > rhs.r;
    }
};

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<Element> arr(n);
    for (auto &[x, l, r, val] : arr)
        std::cin >> x >> l >> val, r = -1;
    int qcnt = 0;
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 0) {
            int x, y, w;
            std::cin >> x >> y >> w;
            arr.push_back(Element{x, y, -1, w});
        }
        else {
            int l, d, r, u;
            std::cin >> l >> d >> r >> u;
            ++qcnt;
            arr.push_back(Element{l, d, u, -qcnt});
            arr.push_back(Element{r, d, u, qcnt});

        }
    }
    Discretization<int> val;
    for (auto &[x, l, r, v] : arr) {
        val.push_back(l);
        if (r != -1) val.push_back(r);
    }
    val.build();
    for (auto &[x, l, r, v] : arr) {
        l = val.idx(l);
        if (r != -1) r = val.idx(r);
    }
    std::vector<long long> ans(qcnt);
    BIT<long long> bit(val.size());
    cdq_solver(arr,
        [&](const Element &e) {
            if (e.r == -1) bit.modify(e.l, e.val);
        },
        [&](const Element &e) {
            if (e.r != -1) {
                long long res = bit.range(e.l, e.r);
                if (e.val > 0) ans[e.val - 1] += res;
                else ans[-e.val - 1] -= res;
            }
        },
        [&](const Element &e) {
            if (e.r == -1) bit.modify(e.l, -e.val);
        }
    );
    for (int i = 0; i < qcnt; ++i)
        std::cout << ans[i] << "\n";
}
