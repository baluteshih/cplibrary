#define PROBLEM "https://loj.ac/p/2302"
#define IGNORE
#include "default_code.hpp"

#include "Misc/trygub_number.hpp"

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, t1, t2, t3;
    cin >> n >> t1 >> t2 >> t3;
    trygub_number<ll, 1 << 30> num;
    while (n--) {
        int type;
        cin >> type;
        if (type == 1) {
            ll a, b;
            cin >> a >> b;
            a <<= b % 30;
            num.add(a, b / 30);
        }
        else {
            int k;
            cin >> k;
            cout << (num.get(k / 30) >> (k % 30) & 1) << "\n";
        }
    }
    
}
