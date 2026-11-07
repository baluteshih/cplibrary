// Uses acos of a rounded cosine near tangency, losing small overlap areas.
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

using Real = long double;

struct Circle {
    long long x, y, r;
    int weight;
};

struct Sum {
    Real value = 0, correction = 0;
    void add(Real term) {
        Real adjusted = term - correction;
        Real next = value + adjusted;
        correction = (next - value) - adjusted;
        value = next;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::map<std::tuple<long long, long long, long long>, int> counts;
    long long minX = 10'000, maxX = -10'000, minY = 10'000, maxY = -10'000;
    for (int i = 0; i < n; ++i) {
        long long x, y, r;
        std::cin >> x >> y >> r;
        ++counts[{x, y, r}];
        minX = std::min(minX, x);
        maxX = std::max(maxX, x);
        minY = std::min(minY, y);
        maxY = std::max(maxY, y);
    }
    std::vector<Circle> circles;
    for (auto [key, weight] : counts) {
        auto [x, y, r] = key;
        circles.push_back({x - (minX + maxX) / 2, y - (minY + maxY) / 2, r, weight});
    }
    const Real pi = std::acos(-1.0L);
    const Real tau = 2 * pi;
    std::vector<Sum> difference(static_cast<std::size_t>(n + 2));
    int maximumDepth = 0;
    for (std::size_t i = 0; i < circles.size(); ++i) {
        const auto &a = circles[i];
        int cover = 0;
        std::vector<std::pair<Real, int>> events;
        for (std::size_t j = 0; j < circles.size(); ++j) {
            if (i == j) {
                continue;
            }
            const auto &b = circles[j];
            long long dx = b.x - a.x, dy = b.y - a.y;
            long long distance2 = dx * dx + dy * dy;
            long long radiusSum = a.r + b.r, radiusDifference = a.r - b.r;
            if (b.r >= a.r && distance2 <= radiusDifference * radiusDifference) {
                cover += b.weight;
                continue;
            }
            if (distance2 >= radiusSum * radiusSum || distance2 <= radiusDifference * radiusDifference) {
                continue;
            }
            Real distance = std::sqrt(static_cast<Real>(distance2));
            Real cosine = static_cast<Real>(distance2 + a.r * a.r - b.r * b.r) / (2 * a.r * distance);
            Real half = std::acos(std::clamp(cosine, -1.0L, 1.0L));
            Real center = std::atan2(static_cast<Real>(dy), static_cast<Real>(dx));
            if (center < 0) {
                center += tau;
            }
            Real left = center - half, right = center + half;
            if (left < 0) {
                left += tau;
                cover += b.weight;
            }
            if (right >= tau) {
                right -= tau;
                cover += b.weight;
            }
            events.emplace_back(left, b.weight);
            events.emplace_back(right, -b.weight);
        }
        events.emplace_back(tau, 0);
        std::sort(events.begin(), events.end());
        Real previous = 0;
        for (auto [angle, delta] : events) {
            if (angle > previous) {
                Real width = angle - previous;
                Real middle = (angle + previous) / 2;
                Real sineHalf = std::sin(width / 2);
                Real integral = a.r * (a.r * width / 2 + sineHalf * (a.x * std::cos(middle) + a.y * std::sin(middle)));
                difference[cover + 1].add(integral);
                difference[cover + a.weight + 1].add(-integral);
                maximumDepth = std::max(maximumDepth, cover + a.weight);
            }
            cover += delta;
            previous = angle;
        }
    }
    Sum area;
    std::cout << std::fixed << std::setprecision(15);
    for (int k = 1; k <= n; ++k) {
        area.add(difference[k].value);
        std::cout << (k > maximumDepth ? 0.0L : std::max(0.0L, area.value)) << '\n';
    }
}
