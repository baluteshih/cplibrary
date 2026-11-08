#define PROBLEM "convex-hull-3d-distance"
#include "assumption.hpp"

#include "Geometry/convexHull3D.hpp"
#include "Misc/i128.hpp"

using Point = Pt3<__int128>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<Point> arr(n);
    for (auto &p : arr)
        std::cin >> p;
    convexHull3D convex(arr);
    auto faces = convex.get_faces();
    std::vector<std::array<__int128, 4>> planes;
    std::map<std::array<__int128, 3>, convexHull3D<__int128>::Face> mp;
    for (auto f : faces) {
        auto [a, b, c, d] = convex.get_plane(f);
        mp[{a, b, c}] = f;
    }
    std::cout << std::fixed << std::setprecision(12);
    while (q--) {
        __int128 a, b, c;
        Point p;
        std::cin >> a >> b >> c >> p;
        std::cout << convex.get_dis(p, mp[{a, b, c}]) << "\n";
    }
}
