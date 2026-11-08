#define PROBLEM "convex-hull-3d"
#include "assumption.hpp"

#include "Geometry/convexHull3D.hpp"
#include "Misc/i128.hpp"

using Point = Pt3<long long, 0, __int128>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<Point> arr(n);
    for (auto &p : arr)
        std::cin >> p;
    convexHull3D convex(arr);
    auto faces = convex.get_faces();
    std::cout << faces.size() << " " << convex.get_volume() << "\n";
    std::vector<std::array<__int128, 4>> planes;
    for (auto f : faces)
        planes.push_back(convex.get_plane(f));
    std::ranges::sort(planes);
    for (auto [a, b, c, d] : planes)
        std::cout << a << " " << b << " " << c << " " << d << "\n";
}
