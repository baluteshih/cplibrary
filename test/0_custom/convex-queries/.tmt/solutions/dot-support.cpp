// Maximizes dot(d,C_i) instead of cross(d,C_i).
#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
    long long x, y;
    Point operator-(Point other) const {
        return {x - other.x, y - other.y};
    }
    bool operator==(const Point &) const = default;
};

long long cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long long turn(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

bool onSegment(Point p, Point a, Point b) {
    return turn(a, b, p) == 0 && std::min(a.x, b.x) <= p.x && p.x <= std::max(a.x, b.x) && std::min(a.y, b.y) <= p.y && p.y <= std::max(a.y, b.y);
}

int location(const std::vector<Point> &polygon, Point point) {
    int n = static_cast<int>(polygon.size());
    if (n == 1) {
        return point == polygon[0] ? 0 : -1;
    }
    if (n == 2) {
        return onSegment(point, polygon[0], polygon[1]) ? 0 : -1;
    }
    long long first = turn(polygon[0], polygon[1], point);
    long long last = turn(polygon[0], polygon[n - 1], point);
    if (first < 0 || last > 0) {
        return -1;
    }
    if (first == 0) {
        return onSegment(point, polygon[0], polygon[1]) ? 0 : -1;
    }
    if (last == 0) {
        return onSegment(point, polygon[0], polygon[n - 1]) ? 0 : -1;
    }
    int left = 1, right = n - 1;
    while (right - left > 1) {
        int middle = (left + right) / 2;
        if (turn(polygon[0], polygon[middle], point) >= 0) {
            left = middle;
        }
        else {
            right = middle;
        }
    }
    long long value = turn(polygon[left], polygon[right], point);
    return (value > 0) - (value < 0);
}

int half(Point point) {
    return point.y < 0 || (point.y == 0 && point.x < 0);
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
    for (Point &point : polygon) {
        std::cin >> point.x >> point.y;
    }
    std::vector<Edge> edges;
    if (n >= 3) {
        for (int i = 0; i < n; ++i) {
            edges.push_back({polygon[(i + 1) % n] - polygon[i], i});
        }
        std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return angleLess(a.direction, b.direction);
        });
    }
    auto minimum = [&](Point direction) {
        if (n <= 2) {
            int best = 0;
            for (int i = 1; i < n; ++i) {
                if (cross(direction, polygon[i]) < cross(direction, polygon[best])) {
                    best = i;
                }
            }
            return best;
        }
        auto it = std::lower_bound(edges.begin(), edges.end(), direction, [](const Edge &edge, Point value) {
            return angleLess(edge.direction, value);
        });
        return (it == edges.end() ? edges.front() : *it).index;
    };
    while (q--) {
        char type;
        Point point;
        std::cin >> type >> point.x >> point.y;
        if (type == 'I') {
            int result = location(polygon, point);
            std::cout << (result > 0 ? "IN" : result == 0 ? "ON" : "OUT") << '\n';
        }
        else if (type == 'D') {
            int best = minimum({-point.y, point.x});
            std::cout << best << '\n';
        }
        else {
            // Three times (an interior triangle centroid minus the external point).
            Point direction = {polygon[0].x + polygon[n / 3].x + polygon[2 * n / 3].x - 3 * point.x,
                               polygon[0].y + polygon[n / 3].y + polygon[2 * n / 3].y - 3 * point.y};
            auto side = [&](int i) {
                return cross(direction, polygon[i] - point);
            };
            int low = minimum(direction);
            int high = minimum({-direction.x, -direction.y});
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
                return (start + right) % n;
            };
            int rising = crossing(low, high, true);
            int falling = crossing(high, low, false);
            int positiveStart = (rising + (side(rising) == 0)) % n;
            int positiveEnd = (falling + n - 1) % n;
            int negativeStart = (falling + (side(falling) == 0)) % n;
            int negativeEnd = (rising + n - 1) % n;
            auto angularExtreme = [&](int start, int finish, bool maximum) {
                int left = 0, right = (finish - start + n) % n;
                while (left < right) {
                    int middle = (left + right) / 2;
                    int i = (start + middle) % n;
                    long long value = cross(polygon[i] - point, polygon[(i + 1) % n] - point);
                    if (maximum ? value > 0 : value < 0) {
                        left = middle + 1;
                    }
                    else {
                        right = middle;
                    }
                }
                return (start + left) % n;
            };
            int first = angularExtreme(negativeStart, negativeEnd, false);
            int second = angularExtreme(positiveStart, positiveEnd, true);
            std::cout << first << ' ' << second << '\n';
        }
    }
}
