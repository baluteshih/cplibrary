#define PROBLEM "half-plan-intersection"
#include "assumption.hpp"

#include "Geometry/half_plane_intersection.hpp"

using Point = Pt<long long>;
using Line = Ln<long long>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, b;
    std::cin >> n >> b;
    std::vector<Line> lines(n);
    std::map<Line, int> mp;
    for (int idx = 0; auto &ln : lines)
        std::cin >> ln, mp[ln] = ++idx;
    auto res = half_plane_intersection<Line, __int128>(lines);
    std::cout << res.size() << "\n";
    for (int i = 0; i < int(res.size()); ++i)
        std::cout << mp[res[i]] << " \n"[i + 1 == int(res.size())];
}
