// Outputs one-based rather than zero-based indices.
#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
    long long x, y;
    Point operator-(Point other) const {
        return {x - other.x, y - other.y};
    }
};

long long cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int half(Point a) {
    return a.y < 0 || (a.y == 0 && a.x < 0);
}

bool angleLess(Point a, Point b) {
    if (half(a) != half(b)) {
        return half(a) < half(b);
    }
    return cross(a, b) > 0;
}

struct Edge {
    Point direction;
    int index;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<Point> polygon(static_cast<std::size_t>(n));
    for (auto &point : polygon) {
        std::cin >> point.x >> point.y;
    }
    std::vector<Edge> edges;
    for (int i = 0; i < n; ++i) {
        edges.push_back({polygon[(i + 1) % n] - polygon[i], i});
    }
    std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return angleLess(a.direction, b.direction);
    });
    auto extreme = [&](Point direction) {
        auto it = std::lower_bound(edges.begin(), edges.end(), direction, [](const Edge &edge, Point value) {
            return angleLess(edge.direction, value);
        });
        return (it == edges.end() ? edges.front() : *it).index;
    };
    while (q--) {
        Point a, b;
        std::cin >> a.x >> a.y >> b.x >> b.y;
        Point direction = b - a;
        auto side = [&](int index) {
            return cross(direction, polygon[index] - a);
        };
        int minimum = extreme(direction);
        int maximum = extreme({-direction.x, -direction.y});
        long long low = side(minimum), high = side(maximum);
        if (low > 0 || high < 0) {
            std::cout << "EMPTY\n";
            continue;
        }
        if (low == 0 || high == 0) {
            int vertex = low == 0 ? minimum : maximum;
            int next = (vertex + 1) % n;
            if (side(next) == 0) {
                std::cout << "EDGE " << vertex + 1 << '\n';
            }
            else {
                std::cout << "POINT " << vertex + 1 << '\n';
            }
            continue;
        }
        auto crossing = [&](int start, int finish, bool increasing) {
            int left = 0, right = (finish - start + n) % n;
            while (right - left > 1) {
                int middle = (left + right) / 2;
                long long value = side((start + middle) % n);
                if (increasing ? value < 0 : value > 0) {
                    left = middle;
                }
                else {
                    right = middle;
                }
            }
            int vertex = (start + right) % n;
            return side(vertex) == 0 ? vertex : (start + left) % n;
        };
        int enter = crossing(maximum, minimum, false);
        int leave = crossing(minimum, maximum, true);
        std::cout << "CUT " << enter + 1 << ' ' << leave + 1 << '\n';
    }
}
