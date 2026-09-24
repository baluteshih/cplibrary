#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_add_point_get"
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
    std::vector<Element> arr(n + n);
    for (int i = 0; i < n; ++i) {
        int l, d, r, u, w;
        std::cin >> l >> d >> r >> u >> w;
        arr[i * 2] = Element{l, d, u, w};
        arr[i * 2 + 1] = Element{r, d, u, -w};
    }
    int qcnt = 0;
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 0) {
            int l, d, r, u, w;
            std::cin >> l >> d >> r >> u >> w;
            arr.push_back(Element{l, d, u, w});
            arr.push_back(Element{r, d, u, -w});
        }
        else {
            int x, y;
            std::cin >> x >> y;
            arr.push_back(Element{x, y, -1, qcnt++});
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
            if (e.r != -1) {
                bit.modify(e.l, e.val);
                bit.modify(e.r, -e.val);
            }
        },
        [&](const Element &e) {
            if (e.r == -1) ans[e.val] += bit.prefix(e.l);
        },
        [&](const Element &e) {
            if (e.r != -1) {
                bit.modify(e.l, -e.val);
                bit.modify(e.r, e.val);
            }
        }
    );
    for (int i = 0; i < qcnt; ++i)
        std::cout << ans[i] << "\n";
}
