#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"
#include "assumption.hpp"

#include "DataStructure/SegmentTree.hpp"

const long long INF = 1e18;

struct Tag {
    long long lazymax, lazymin, lazyadd;
    Tag(long long _mx = -INF, long long _mn = INF, long long _add = 0): lazymax(_mx), lazymin(_mn), lazyadd(_add) {}
    Tag operator+(const Tag &rhs) const {
        Tag res(*this);
        res.lazyadd += rhs.lazyadd;
        if (res.lazymax != -INF) res.lazymax += rhs.lazyadd;
        if (res.lazymin != INF) res.lazymin += rhs.lazyadd;
        if (rhs.lazymin != INF) { 
            res.lazymin = std::min(res.lazymin, rhs.lazymin);
            res.lazymax = std::min(res.lazymax, rhs.lazymin);
        }
        if (rhs.lazymax != -INF) res.lazymax = std::max(res.lazymax, rhs.lazymax);
        return res;
    }
};

struct Value {
    long long sum;
    long long mx, mxcnt, smx;
    long long mi, micnt, smi;
    int sz;
    Value(long long _v = 0, int _sz = 0): sum(_v), mx(_v), mxcnt(1), smx(-INF), mi(_v), micnt(1), smi(INF), sz(_sz) {}
    Value operator+(const Value &rhs) const {
        Value res;
        res.sum = sum + rhs.sum;
        res.mx = std::max(mx, rhs.mx);
        res.mi = std::min(mi, rhs.mi);
        if (mx == rhs.mx) {
            res.mxcnt = mxcnt + rhs.mxcnt;
            res.smx = std::max(smx, rhs.smx);
        }
        else if (mx > rhs.mx) {
            res.mxcnt = mxcnt;
            res.smx = std::max(smx, rhs.mx);
        }
        else {
            res.mxcnt = rhs.mxcnt;
            res.smx = std::max(mx, rhs.smx);
        }
        if (mi == rhs.mi) {
            res.micnt = micnt + rhs.micnt;
            res.smi = std::min(smi, rhs.smi);
        }
        else if (mi < rhs.mi) {
            res.micnt = micnt;
            res.smi = std::min(smi, rhs.mi);
        }
        else {
            res.micnt = rhs.micnt;
            res.smi = std::min(mi, rhs.smi);
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
    friend std::ostream& operator<<(std::ostream& os, const Value &v) {
        os << v.sum;
        return os;
    }
};

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    std::vector<Value> val(n);
    for (int i = 0; i < n; ++i) {
        long long x;
        std::cin >> x;
        val[i] = Value(x, 1);
    }
    SegmentTree<Value, Tag> seg(val);
    while (m--) {
        int k, x, y;
        long long t;
        std::cin >> k >> x >> y;
        if (k == 0)
            std::cin >> t, seg.range_transform_beats(x, y, Tag(-INF, t, 0), [&](const Value &v) {
                return t > v.smx; 
            });
        else if (k == 1)
            std::cin >> t, seg.range_transform_beats(x, y, Tag(t, INF, 0), [&](const Value &v) {
                return t < v.smi;
            });
        else if (k == 2)
            std::cin >> t, seg.range_transform(x, y, Tag(-INF, INF, t));
        else
            std::cout << seg.range_prod(x, y) << "\n";
    }
}
