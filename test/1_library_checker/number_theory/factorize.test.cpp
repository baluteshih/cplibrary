#define PROBLEM "https://judge.yosupo.jp/problem/factorize"
#include "default_code.hpp"

#include "Numeric/pollard_rho.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int q;
    cin >> q;
    while (q--) {
        ll x;
        cin >> x;
        vector<ll> ans = pollard_rho(x);
        ranges::sort(ans);
        cout << SZ(ans);
        for (ll i : ans)
            cout << " " << i;
        cout << "\n";
    }
}
