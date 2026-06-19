#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"
#include "assumption.hpp"

#include "Misc/2sat.hpp"

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    std::string p, cnt;
    int n, m;
    std::cin >> p >> cnt >> n >> m;
    SAT sat(n);
    while (m--) {
        int a, b, z;
        std::cin >> a >> b >> z;
        if (a < 0) a = sat.rv(-a - 1);
        else --a;
        if (b < 0) b = sat.rv(-b - 1);
        else --b;
        sat.add_clause(a, b);
    }
    if (!sat.solve())
        std::cout << "s UNSATISFIABLE\n";
    else {
        std::cout << "s SATISFIABLE\nv ";
        for (int i = 0; i < n; ++i)
            if (sat.istrue[i])
                std::cout << i + 1 << " ";
            else
                std::cout << -(i + 1) << " ";
        std::cout << "0\n";
    }
}
