#define PROBLEM "https://loj.ac/p/2302"
#define IGNORE
#include "assumption.hpp"

#include "Misc/trygub_number.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, t1, t2, t3;
    std::cin >> n >> t1 >> t2 >> t3;
    trygub_number<long long, 1 << 30> num;
    while (n--) {
        int type;
        std::cin >> type;
        if (type == 1) {
            long long a, b;
            std::cin >> a >> b;
            a <<= b % 30;
            num.add(a, b / 30);
        }
        else {
            int k;
            std::cin >> k;
            std::cout << (num.get(k / 30) >> (k % 30) & 1) << "\n";
        }
    }
    
}
