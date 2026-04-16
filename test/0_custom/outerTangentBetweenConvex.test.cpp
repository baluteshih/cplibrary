#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "default_code.hpp"

#include "Geometry/outerTangentBetweenConvex.hpp"

using Point = Pt<ll>;
using polygon = Polygon<ll>;

pair<polygon, polygon> gen_poly(int n, int m, const int maxc) {
    static mt19937 rng(880301);
    Point sep;
    while (sep == Point(0, 0)) {
        sep.x = int(rng() % 11) - 5;
        sep.y = int(rng() % 11) - 5;
    }
    vector<Point> P, Q;
    while (int(P.size()) < n || int(Q.size()) < m) {
        Point pt; 
        pt.x = int(rng() % (2 * maxc + 1)) - maxc;
        pt.y = int(rng() % (2 * maxc + 1)) - maxc;
        int dir = side(Point(0, 0), sep, pt);
        if (dir == 1 && int(P.size()) < n) P.push_back(pt);
        else if (dir == -1 && int(Q.size()) < m) Q.push_back(pt);
    }
    return make_pair(convexHull(P), convexHull(Q));
}

void check(int a, int b, polygon &P, polygon &Q) {
    assert(a >= 0 && a < int(P.size()));
    assert(b >= 0 && b < int(Q.size()));
    for (auto &p : P)
        assert(side(P[a], Q[b], p) >= 0);
    for (auto &p : Q)
        assert(side(P[a], Q[b], p) >= 0);
}

void test() {
    const int MAXC = 1'000'000'000;
    vector<int> sz{1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 5, 10, 100, 1000, 10000, 100000}; 
    for (int n : sz)
        for (int m : sz) {
            auto [P, Q] = gen_poly(n, m, MAXC);
            auto [a, b] = outerTangentBetweenConvex(P, Q);
            check(a, b, P, Q);
        }
}

int main() {
    test();
    int a, b;
    cin >> a >> b;
    cout << a + b << "\n";
}
