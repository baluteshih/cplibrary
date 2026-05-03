#pragma once

namespace std {
    ostream &operator<<(ostream &os, const __int128 &x) {
        if (x < 0) return os << '-' << -x;
        if (x < 10) return os << int(x % 10);
        return os << x / 10 << int(x % 10);
    }
}
