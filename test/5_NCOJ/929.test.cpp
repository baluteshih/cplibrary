#define PROBLEM "https://oj.ntucpc.org/problems/929"
#define IGNORE
#include "assumption.hpp"

#include "Geometry/rotating_sweepline.hpp"
#include "Numeric/Modint.hpp"

using Point = Pt<long long>;
using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<Point> arr(n);
    for (auto &p : arr)
        std::cin >> p;
    mint ans = 0;
    rotating_sweepline(arr, []([[maybe_unused]] const std::vector<int> &ord){}, [&](const std::vector<int> &ord, int l, int r) {
        for (int i = l; i < r; ++i)
            for (int j = i + 1; j <= r; ++j) {
                long long mi = 1e18;
                if (l > 0) mi = std::min(mi, -cross(arr[ord[i]], arr[ord[j]], arr[ord[l - 1]]));
                if (r + 1 < n) mi = std::min(mi, cross(arr[ord[i]], arr[ord[j]], arr[ord[r + 1]]));
                ans += mi;
            }
    });
    std::cout << ans / 2 << "\n";
}
