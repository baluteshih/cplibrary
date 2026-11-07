// Forgets the offset when one hull is a singleton.
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using Point = std::pair<long long, long long>;
using Polygon = std::vector<Point>;

Point add(Point a, Point b) {
    return {a.first + b.first, a.second + b.second};
}

Point subtract(Point a, Point b) {
    return {a.first - b.first, a.second - b.second};
}

long long cross(Point a, Point b) {
    return a.first * b.second - a.second * b.first;
}

Polygon hull(Polygon points) {
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());
    if (points.size() <= 1) {
        return points;
    }
    auto chain = [](const Polygon &sequence) {
        Polygon result;
        for (Point point : sequence) {
            while (result.size() >= 2 && cross(subtract(result.back(), result[result.size() - 2]), subtract(point, result.back())) <= 0) {
                result.pop_back();
            }
            result.push_back(point);
        }
        return result;
    };
    Polygon lower = chain(points);
    std::reverse(points.begin(), points.end());
    Polygon upper = chain(points);
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

int half(Point point) {
    return point.second < 0 || (point.second == 0 && point.first < 0);
}

bool angleLess(Point a, Point b) {
    if (half(a) != half(b)) {
        return half(a) < half(b);
    }
    return cross(a, b) > 0;
}

Polygon minkowski(Polygon a, Polygon b) {
    if (a.size() == 1 || b.size() == 1) {
        if (b.size() != 1) {
            std::swap(a, b);
        }
        for (Point &point : a) {
            point = point;
        }
        return a;
    }
    auto prepare = [](Polygon &polygon) {
        auto bottom = std::min_element(polygon.begin(), polygon.end(), [](Point p, Point q) {
            return std::pair(p.second, p.first) < std::pair(q.second, q.first);
        });
        std::rotate(polygon.begin(), bottom, polygon.end());
        Polygon edges;
        for (std::size_t i = 0; i < polygon.size(); ++i) {
            edges.push_back(subtract(polygon[(i + 1) % polygon.size()], polygon[i]));
        }
        return edges;
    };
    Polygon edgesA = prepare(a), edgesB = prepare(b);
    Point current = add(a[0], b[0]);
    Polygon result;
    std::size_t i = 0, j = 0;
    while (i < edgesA.size() || j < edgesB.size()) {
        result.push_back(current);
        Point step;
        if (j == edgesB.size() || (i < edgesA.size() && angleLess(edgesA[i], edgesB[j]))) {
            step = edgesA[i++];
        }
        else if (i == edgesA.size() || angleLess(edgesB[j], edgesA[i])) {
            step = edgesB[j++];
        }
        else {
            step = add(edgesA[i++], edgesB[j++]);
        }
        current = add(current, step);
    }
    auto start = std::min_element(result.begin(), result.end());
    std::rotate(result.begin(), start, result.end());
    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    Polygon a(static_cast<std::size_t>(n)), b(static_cast<std::size_t>(m));
    for (auto &[x, y] : a) {
        std::cin >> x >> y;
    }
    for (auto &[x, y] : b) {
        std::cin >> x >> y;
    }
    Polygon result = minkowski(hull(a), hull(b));
    std::cout << result.size() << '\n';
    for (auto [x, y] : result) {
        std::cout << x << ' ' << y << '\n';
    }
}
