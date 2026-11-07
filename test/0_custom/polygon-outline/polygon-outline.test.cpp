#define PROBLEM "polygon-outline"
#include "assumption.hpp"

#include "Geometry/polygon.hpp"
#include "Misc/i128.hpp"

using Point = Pt<long long, 0, __int128>;
using Poly = Polygon<long long, 0, __int128>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    Poly poly(n);
    for (auto &p : poly)
        std::cin >> p;
    while (q--) {
        char c;
        std::cin >> c;
        if (c == 'V') {
            int i;
            std::cin >> i;
            std::cout << poly.at(i) << "\n";
        }
        else if (c == 'E') {
            int i;
            std::cin >> i;
            std::cout << poly.edge(i) << "\n"; 
        }
        else if (c == 'S') {
            int i;
            Point p;
            std::cin >> i >> p;
            poly.at(i) = p;
        }
        else {
            auto area = poly.area(); 
            std::cout << area << " " << Point::sign(area) << "\n";
        }
    }
}
