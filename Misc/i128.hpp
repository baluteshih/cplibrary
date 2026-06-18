#pragma once

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
