#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

struct Point { long long x, y; };
std::string decimal(__int128 value) {
    if (value == 0) return "0";
    bool negative = value < 0;
    if (negative) value = -value;
    std::string result;
    while (value != 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    if (negative) result.push_back('-');
    std::reverse(result.begin(), result.end());
    return result;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<Point> points(n);
    for (auto &p : points) std::cin >> p.x >> p.y;
    auto normalize = [&](long long i) {
#ifdef UNSIGNED_INDEX
        return int(static_cast<std::uint64_t>(i) % static_cast<unsigned>(n));
#else
        return int((i % n + n) % n);
#endif
    };
    while (q-- != 0) {
        char operation;
        std::cin >> operation;
        if (operation == 'A') {
            __int128 area = 0;
            int count = n;
#ifdef OMIT_CLOSING
            --count;
#endif
            for (int i = 0; i < count; ++i) {
                const auto &a = points[i];
                const auto &next = points[(i + 1) % n];
                area += __int128(a.x - next.x) * (a.y + next.y);
            }
#ifdef ABSOLUTE_AREA
            if (area < 0) area = -area;
#endif
#ifdef HALF_AREA
            area /= 2;
#endif
#ifdef NARROW_AREA
            area = static_cast<long long>(area);
#endif
            int sign = (area > 0) - (area < 0);
            std::cout << decimal(area) << ' ' << sign << '\n';
        }
        else {
            long long i;
            std::cin >> i;
            int j = normalize(i);
            if (operation == 'S') std::cin >> points[j].x >> points[j].y;
            else if (operation == 'V') std::cout << points[j].x << ' ' << points[j].y << '\n';
            else {
                int k = (j + 1) % n;
#ifdef REVERSE_EDGE
                std::swap(j, k);
#endif
                std::cout << points[j].x << ' ' << points[j].y << ' '
                          << points[k].x << ' ' << points[k].y << '\n';
            }
        }
    }
}
