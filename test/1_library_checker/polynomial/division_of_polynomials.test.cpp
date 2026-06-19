#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"
#include "assumption.hpp"

#include "Polynomial/Polynomial.hpp"

using mint = modint998244353;

int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    Poly_t f(n), g(m);
    for (auto &i : f)
        std::cin >> i;
    for (auto &i : g)
        std::cin >> i;
    auto [q, r] = f.DivMod(g);
    q.strip(), r.strip();
    std::cout << q.size() << " " << r.size() << "\n";
    for (int i = 0; i < int(q.size()); ++i)
        std::cout << q[i] << " \n"[i + 1 == int(q.size())];
    if (q.empty()) std::cout << "\n";
    for (int i = 0; i < int(r.size()); ++i)
        std::cout << r[i] << " \n"[i + 1 == int(r.size())];
    if (r.empty()) std::cout << "\n";
}
