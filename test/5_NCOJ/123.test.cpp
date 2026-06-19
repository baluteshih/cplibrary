#define PROBLEM "https://oj.ntucpc.org/problems/123"
#define IGNORE
#include "assumption.hpp"

#include "Geometry/rotating_sweepline.hpp"

using Point = Pt<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<Point> arr(n);
    for (auto &p : arr)
        std::cin >> p;
    std::vector<int> num;
    int cur = 0;
    Point last(1, 2e9);
    rotating_sweepline<Point, false>(arr, [&](const std::vector<int> &ord) {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (ord[i] > ord[j])
                    ++cur;
    }, [&](const std::vector<int> &ord, int i) {
        if (!sameDirection(last, arr[ord[i + 1]] - arr[ord[i]]))
            num.push_back(cur);
        last = arr[ord[i + 1]] - arr[ord[i]];
        if (ord[i] > ord[i + 1]) --cur;
        else ++cur;
    });
    std::ranges::sort(num, std::greater<int>());
    int q;
    std::cin >> q;
    while (q--) {
        int k;
        std::cin >> k;
        std::cout << num[k - 1] << "\n";
    }
}
