#define PROBLEM "https://judge.yosupo.jp/problem/longest_common_substring"
#include "default_code.hpp"

#include "Numeric/Modint.hpp"
#include "String/RollingHash.hpp"

using mint1 = modint998244353;
using mint2 = modint1000000007;
using Hash = RollingHash<307, mint1, mint2>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    string s, t;
    cin >> s >> t;
    auto prefix1 = Hash::prefixHash(s);
    auto prefix2 = Hash::prefixHash(t);
    int anslen = 0, a = 0, b = 0;

    auto check = [&](int len) {
        vector<pair<Hash, int>> val;
        val.reserve(s.size() - len + 1);
        for (int i = 0; i <= int(s.size()) - len; ++i)
            val.emplace_back(Hash::rangeHash(prefix1, i, i + len), i);
        ranges::sort(val);
        for (int i = 0; i <= int(t.size()) - len; ++i) {
            auto v = Hash::rangeHash(prefix2, i, i + len);
            auto it = ranges::lower_bound(val, make_pair(v, 0));
            if (it != val.end() && it->first == v) {
                anslen = len;
                a = it->second;
                b = i;
                return true;
            }
        }
        return false;
    };

    int l = 0, r = min(s.size(), t.size()) + 1;
    while (r - l > 1) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid;
        else r = mid;
    }
    cout << a << " " << a + anslen << " " << b << " " << b + anslen << "\n";
}
