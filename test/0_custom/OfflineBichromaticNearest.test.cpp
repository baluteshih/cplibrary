#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"
#include "assumption.hpp"

#include "Geometry/OfflineBichromaticNearest.hpp"
#include "Misc/i256.hpp"

using Point = Pt<long long>;

Point gen_point(int MAXC) {
    static std::mt19937 rng(880301);
    Point res;
    res.x = int(rng() % (2 * MAXC + 1)) - MAXC; 
    res.y = int(rng() % (2 * MAXC + 1)) - MAXC; 
    return res;
}

void test() {
    std::vector<int> sz{1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 5, 10, 100, 1000, 2000};
    std::vector<int> maxc{10, 1000, 1'000'000'000};
    for (int MAXC : maxc)
        for (int n : sz) {
            std::vector<Point> arr(n);
            for (auto &p : arr) p = gen_point(MAXC);
            OfflineBichromaticNearest<Point, true, long long, __int128, i256> solver(arr);
            for (int m : sz) {
                std::vector<Point> qry(m);
                for (auto &p : qry) p = gen_point(MAXC);
                std::vector<std::pair<long long, int>> ans(m, std::make_pair(9ll * MAXC * MAXC, 0));
                for (int i = 0; i < m; ++i)
                    for (auto &p : arr) {
                        if (dist2(p, qry[i]) < ans[i].first)
                            ans[i] = std::make_pair(dist2(p, qry[i]), 1);
                        else if (dist2(p, qry[i]) == ans[i].first)
                            ++ans[i].second;
                    }
                auto res = solver.query(qry);
                for (int i = 0; i < m; ++i) {
                    assert(res[i].dist2 == ans[i].first);
                    assert(res[i].count == ans[i].second);
                }
            }
        }
}

int main() {
    test();
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b << "\n";
}
