#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"
#include "default_code.hpp"

#include "DataStructure/SegmentTree.hpp"

const ll INF = 1e18;

struct Tag {
    ll lazymax, lazymin, lazyadd;
    Tag(ll _mx = -INF, ll _mn = INF, ll _add = 0): lazymax(_mx), lazymin(_mn), lazyadd(_add) {}
    Tag operator+(const Tag &rhs) const {
        Tag res(*this);
        res.lazyadd += rhs.lazyadd;
        if (res.lazymax != -INF) res.lazymax += rhs.lazyadd;
        if (res.lazymin != INF) res.lazymin += rhs.lazyadd;
        if (rhs.lazymin != INF) { 
            chmin(res.lazymin, rhs.lazymin);
            chmin(res.lazymax, rhs.lazymin);
        }
        if (rhs.lazymax != -INF) chmax(res.lazymax, rhs.lazymax);
        return res;
    }
};

struct Value {
    ll sum;
    ll mx, mxcnt, smx;
    ll mi, micnt, smi;
    int sz;
    Value(ll _v = 0, int _sz = 0): sum(_v), mx(_v), mxcnt(1), smx(-INF), mi(_v), micnt(1), smi(INF), sz(_sz) {}
    Value operator+(const Value &rhs) const {
        Value res;
        res.sum = sum + rhs.sum;
        res.mx = max(mx, rhs.mx);
        res.mi = min(mi, rhs.mi);
        if (mx == rhs.mx) {
            res.mxcnt = mxcnt + rhs.mxcnt;
            res.smx = max(smx, rhs.smx);
        }
        else if (mx > rhs.mx) {
            res.mxcnt = mxcnt;
            res.smx = max(smx, rhs.mx);
        }
        else {
            res.mxcnt = rhs.mxcnt;
            res.smx = max(mx, rhs.smx);
        }
        if (mi == rhs.mi) {
            res.micnt = micnt + rhs.micnt;
            res.smi = min(smi, rhs.smi);
        }
        else if (mi < rhs.mi) {
            res.micnt = micnt;
            res.smi = min(smi, rhs.mi);
        }
        else {
            res.micnt = rhs.micnt;
            res.smi = min(mi, rhs.smi);
        }
        res.sz = sz + rhs.sz;
        return res;
    }
    Value operator+(const Tag &tag) const {
        Value res(*this);
        res.mx += tag.lazyadd;
        if (res.smx != -INF) res.smx += tag.lazyadd;
        res.mi += tag.lazyadd;
        if (res.smi != INF) res.smi += tag.lazyadd;
        res.sum += tag.lazyadd * sz;
        if (tag.lazymin < res.mx) {
            assert(tag.lazymin > res.smx);
            res.sum += res.mxcnt * (tag.lazymin - res.mx);
            if (res.mx == res.smi) res.smi = tag.lazymin;
            if (res.mx == res.mi) res.mi = tag.lazymin;
            res.mx = tag.lazymin;
        }
        if (tag.lazymax > res.mi) {   
            assert(tag.lazymax < res.smi);
            res.sum += res.micnt * (tag.lazymax - res.mi);
            if (res.mi == res.smx) res.smx = tag.lazymax;
            if (res.mi == res.mx) res.mx = tag.lazymax;
            res.mi = tag.lazymax;
        }
        return res;
    }
    friend ostream& operator<<(ostream& os, const Value &v) {
        os << v.sum;
        return os;
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<Value> val(n);
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        val[i] = Value(x, 1);
    }
    SegmentTree<Value, Tag> seg(val);
    while (m--) {
        int k, x, y;
        ll t;
        cin >> k >> x >> y;
        if (k == 0)
            cin >> t, seg.range_transform_beats(x, y, Tag(-INF, t, 0), [&](Value &v) {
                return t > v.smx; 
            });
        else if (k == 1)
            cin >> t, seg.range_transform_beats(x, y, Tag(t, INF, 0), [&](Value &v) {
                return t < v.smi;
            });
        else if (k == 2)
            cin >> t, seg.range_transform(x, y, Tag(-INF, INF, t));
        else
            cout << seg.range_prod(x, y) << "\n";
    }
}
