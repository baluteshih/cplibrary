#define PROBLEM "https://oj.ntucpc.org/problems/123"
#define IGNORE
#include "default_code.hpp"

#include "Geometry/rotating_sweepline.hpp"

using Point = Pt<ll>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<Point> arr(n);
    for (auto &p : arr)
        cin >> p;
    vector<int> num;
    int cur = 0;
    Point last(1, 2e9);
    rotating_sweepline<Point, false>(arr, [&](const vector<int> &ord) {
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (ord[i] > ord[j])
                    ++cur;
    }, [&](const vector<int> &ord, int i) {
        if (!sameDirection(last, arr[ord[i + 1]] - arr[ord[i]]))
            num.push_back(cur);
        last = arr[ord[i + 1]] - arr[ord[i]];
        if (ord[i] > ord[i + 1]) --cur;
        else ++cur;
    });
    ranges::sort(num, greater<int>());
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        cout << num[k - 1] << "\n";
    }
}
