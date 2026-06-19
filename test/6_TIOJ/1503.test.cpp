#define PROBLEM "https://tioj.ck.tp.edu.tw/problems/1503"
#include "assumption.hpp"
#define IGNORE 

#include "Geometry/circle_cover.hpp"

using Cir = Circle<int>;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, r;
    std::cin >> n >> r;
    std::vector<Cir> arr(n);
    for (auto &p : arr)
        std::cin >> p.o, p.r = r;
    std::cout << std::fixed << std::setprecision(2) << circle_cover(arr)[1] << "\n";
}
