#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"
#include "assumption.hpp"

#include "Numeric/quadratic_residue.hpp"
#include "Numeric/DynamicModint.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int t;
    std::cin >> t;
    while (t--) {
        int y, p;
        std::cin >> y >> p;
        dynamic_modint<-1> v;
        v.set_mod(p);
        v = v.raw(y);
        bool succ;
        auto res = quadratic_residue(v, succ);
        if (!succ) std::cout << "-1\n";
        else std::cout << res << "\n";
    }
}
