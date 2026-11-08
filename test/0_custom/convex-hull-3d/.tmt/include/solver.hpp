#include "gift_wrapping.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Point> p(n);
    for (auto &q : p) std::cin >> q[0] >> q[1] >> q[2];
#ifdef FIRST_FOUR
    p.resize(4);
    if (!dimension_three(p)) {
        std::cout << "0 0\n";
        return 0;
    }
#endif
    std::sort(p.begin(), p.end());
    p.erase(std::unique(p.begin(), p.end()), p.end());
    Hull result = gift_wrapping(p);
    std::vector<Plane> output;
    for (const auto &[f, vertices] : result.facets) {
        Plane value = f;
#ifdef FLIP_NORMAL
        for (int i = 0; i < 3; ++i) {
            if (value[i] != 0) {
                if (value[i] < 0) for (auto &x : value) x = -x;
                break;
            }
        }
#endif
#ifdef UNNORMALIZED
        for (auto &x : value) x *= 2;
#endif
#ifdef TRIANGLE_COUNT
        for (std::size_t i = 0; i + 2 < vertices.size(); ++i) output.push_back(value);
#else
        output.push_back(value);
#endif
    }
    std::sort(output.begin(), output.end());
#ifdef DIVIDE_SIX
    result.volume6 /= 6;
#endif
#ifdef NARROW_VOLUME
    result.volume6 = static_cast<long long>(result.volume6);
#endif
    std::cout << output.size() << ' ' << decimal(result.volume6) << '\n';
    for (const auto &f : output) {
        for (int j = 0; j < 4; ++j) std::cout << decimal(f[j]) << (j == 3 ? '\n' : ' ');
    }
}
