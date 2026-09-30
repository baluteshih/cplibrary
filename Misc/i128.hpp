#pragma once

using i128 = __int128;
using u128 = unsigned __int128;

namespace std {
    std::istream &operator>>(std::istream& is, __int128 &x) {
        std::string s;
        is >> s;
        int sgn = 1;
        if (s[0] == '-') sgn = -1, s.erase(s.begin());
        x = 0;
        for (char c : s)
            x = x * 10 + int(c - '0'); 
        x *= sgn;
        return is;
    }
    std::ostream &operator<<(std::ostream &os, const __int128 &x) {
        if (x < 0) return os << '-' << -x;
        if (x < 10) return os << int(x % 10);
        return os << x / 10 << int(x % 10);
    }
}
inline i128 abs(i128 x) {
    return x < 0 ? -x : x;
}
inline u128 gcd(u128 a, u128 b) {
    while (b) a %= b, std::swap(a, b);
    return a;
}
inline i128 gcd(i128 a, i128 b) {
    return gcd((u128)abs(a), (u128)abs(b));
}
