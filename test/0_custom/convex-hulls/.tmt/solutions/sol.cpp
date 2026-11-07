#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using Point = std::pair<long long, long long>;
using Chain = std::vector<Point>;

long long turn(Point a, Point b, Point c) {
    return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

Chain chain(const Chain &points, bool upper, bool keepCollinear) {
    Chain result;
    for (Point point : points) {
        while (result.size() >= 2) {
            long long cross = turn(result[result.size() - 2], result.back(), point);
            if (upper) {
                cross = -cross;
            }
            if (cross > 0 || (keepCollinear && cross == 0)) {
                break;
            }
            result.pop_back();
        }
        result.push_back(point);
    }
    return result;
}

Chain join(const Chain &lower, const Chain &upper) {
    Chain result = lower;
    // Both chains run from S to T. Return along the upper chain without endpoints.
    for (int i = static_cast<int>(upper.size()) - 2; i >= 1; --i) {
        result.push_back(upper[static_cast<std::size_t>(i)]);
    }
    return result;
}

void print(const Chain &points) {
    std::cout << points.size() << '\n';
    for (auto [x, y] : points) {
        std::cout << x << ' ' << y << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    Chain points(static_cast<std::size_t>(n));
    for (auto &[x, y] : points) {
        std::cin >> x >> y;
    }
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());
    Chain lower = chain(points, false, false);
    Chain upper = chain(points, true, false);
    Chain hull = join(lower, upper);
    Chain boundary = join(chain(points, false, true), chain(points, true, true));
    print(hull);
    print(boundary);
    print(lower);
    print(upper);
}
