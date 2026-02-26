#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"
#include "default_code.hpp"

#include "Polynomial/Polynomial.hpp"

using mint = modint998244353;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    Poly_t f(n), g(m);
    for (auto &i : f)
        cin >> i;
    for (auto &i : g)
        cin >> i;
    auto [q, r] = f.DivMod(g);
    q.strip(), r.strip();
    cout << SZ(q) << " " << SZ(r) << "\n";
    for (int i = 0; i < SZ(q); ++i)
        cout << q[i] << " \n"[i + 1 == SZ(q)];
    if (q.empty()) cout << "\n";
    for (int i = 0; i < SZ(r); ++i)
        cout << r[i] << " \n"[i + 1 == SZ(r)];
    if (r.empty()) cout << "\n";
}
