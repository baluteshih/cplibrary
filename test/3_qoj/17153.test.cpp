#define PROBLEM "https://qoj.ac/problem/17153"
#define IGNORE
#include "default_code.hpp"

#include "DataStructure/Treap.hpp"

struct Value {
    int mx = 0, mi = 1'000'000'000, sz = 0, inc = 1, rinc = 1;
    Value() = default;
    Value(int k) : mx(k), mi(k), sz(1), inc(1), rinc(1) {}
    Value operator+(const Value &rhs) const {
        Value res;
        res.mx = max(mx, rhs.mx);
        res.mi = min(mi, rhs.mi);
        res.sz = sz + rhs.sz;
        res.inc = inc && rhs.inc && mx < rhs.mi;
        res.rinc = rinc && rhs.rinc && mi > rhs.mx;
        return res;
    }
    void reverse() {
        swap(inc, rinc);
    }
    int size() const {
        return sz;
    }
};

using treap = Treap<int, Value, void, true>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> ans(q, -1);
    vector<vector<pii>> qry(n + 1);
    treap lft, mid, rgt;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        mid.push_back(x, Value(x));
    }
    for (int i = 0; i < q; ++i) {
        int t, b;
        cin >> t >> b;
        if (t > n) continue;
        qry[t].emplace_back(b, i);
    }

    auto operation = [&]() {
        treap nxtlft, nxtmid, nxtrgt;
        lft.reverse();
        nxtrgt = lft;
        int cur = nxtrgt.product().mx;
        while (true) {
            treap a = mid.split_value([&](const Value &src) {
                return src.mx <= cur; 
            });
            a.reverse();
            nxtmid.left_merge(a);
            if (mid.empty()) break;
            treap p = mid.split_size(1);
            cur = p.product().mx;
            nxtrgt.right_merge(p);
        }
        treap b = rgt.split_value([&](const Value &src) {
            return src.mx <= cur; 
        });
        b.reverse();
        nxtlft = b;
        nxtrgt.right_merge(rgt);
        lft.swap(nxtlft), mid.swap(nxtmid), rgt.swap(nxtrgt);
    };

    for (int i = 0; i <= n; ++i) {
        for (auto [b, qid] : qry[i]) {
            if (b <= lft.size()) ans[qid] = lft.kth(b)->key;
            else {
                b -= lft.size();
                if (b <= mid.size()) ans[qid] = mid.kth(b)->key;
                else ans[qid] = rgt.kth(b - mid.size())->key;
            }
        }
        if ((lft.product() + mid.product() + rgt.product()).inc)
            break;
        operation(); 
    }
    for (int i = 0; i < q; ++i)
        cout << ans[i] << "\n";
}
