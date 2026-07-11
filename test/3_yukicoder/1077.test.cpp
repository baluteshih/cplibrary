#define PROBLEM "https://yukicoder.me/problems/no/1077"
#include "assumption.hpp"

#include "DataStructure/Convex/SlopeTrick.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n;
    std::cin >> n;
    SlopeTrick<int> slope;
    while (n--) {
        int x;
        std::cin >> x;
        slope.prefix_min();
        slope.add_abs(x);
    }
    std::cout << slope.top() << "\n";
}
