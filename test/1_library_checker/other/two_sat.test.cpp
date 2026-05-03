#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"
#include "default_code.hpp"

#include "Misc/2sat.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    string p, cnt;
    int n, m;
    cin >> p >> cnt >> n >> m;
    SAT sat(n);
    while (m--) {
        int a, b, z;
        cin >> a >> b >> z;
        if (a < 0) a = sat.rv(-a - 1);
        else --a;
        if (b < 0) b = sat.rv(-b - 1);
        else --b;
        sat.add_clause(a, b);
    }
    if (!sat.solve())
        cout << "s UNSATISFIABLE\n";
    else {
        cout << "s SATISFIABLE\nv ";
        for (int i = 0; i < n; ++i)
            if (sat.istrue[i])
                cout << i + 1 << " ";
            else
                cout << -(i + 1) << " ";
        cout << "0\n";
    }
}
