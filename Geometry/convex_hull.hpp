#include "Geometry/base.hpp"

template <typename Point>
std::vector<Point> convex_hull(vector<Point> dots, bool sort_and_unique = true) {
    if (sort_and_unique) {
        std::ranges::sort(dots);
        dots.erase(ranges::unique(dots).begin(), dots.end());
    }
    int n = dots.size();
    if (n <= 1) { return dots; }
    std::vector<Point> res(2 * n);
    int j = 0;
    for (int i = 0; i < n; res[j++] = dots[i++]) {
        while (j >= 2 && side(res[j - 2], res[j - 1], dots[i]) <= 0) { j--; }
    }
    for (int i = n - 2, k = j; i >= 0; res[j++] = dots[i--]) {
        while (j > k && side(res[j - 2], res[j - 1], dots[i]) <= 0) { j--; }
    }
    res.resize(j - 1);
    return res;
}
