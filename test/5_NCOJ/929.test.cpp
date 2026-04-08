#define PROBLEM "https://oj.ntucpc.org/problems/929"
#define IGNORE
#include "default_code.hpp"

#include "Geometry/rotating_sweepline.hpp"
#include "Numeric/Modint.hpp"

using Point = Pt<ll>;
using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<Point> arr(n);
    for (auto &p : arr)
        cin >> p;
    mint ans = 0;
    rotating_sweepline(arr, []([[maybe_unused]] const vector<int> &ord){}, [&](const vector<int> &ord, int l, int r) {
        for (int i = l; i < r; ++i)
            for (int j = i + 1; j <= r; ++j) {
                ll mi = 1e18;
                if (l > 0) chmin(mi, -cross(arr[ord[i]], arr[ord[j]], arr[ord[l - 1]]));
                if (r + 1 < n) chmin(mi, cross(arr[ord[i]], arr[ord[j]], arr[ord[r + 1]]));
                ans += mi;
            }
    });
    cout << ans / 2 << "\n";
}
