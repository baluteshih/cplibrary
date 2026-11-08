#pragma once
#include <array>
#include <cstdlib>
#include <numeric>

using Key = std::array<long long, 3>;
struct Dual {
    long long a, b, c;
    int id;
};
Dual make_dual(long long x, long long y, long long u, long long v, int id) {
    long long a = v - y, b = x - u;
    return {a, b, a * x + b * y, id};
}
Key key(const Dual &p) {
    long long g = std::gcd(std::gcd(std::abs(p.a), std::abs(p.b)), p.c);
    return {p.a / g, p.b / g, p.c / g};
}
bool less_point(const Dual &p, const Dual &q) {
    __int128 x = __int128(p.a) * q.c - __int128(q.a) * p.c;
    return x != 0 ? x < 0 : __int128(p.b) * q.c < __int128(q.b) * p.c;
}
__int128 determinant(const Dual &p, const Dual &q, const Dual &r) {
    return __int128(p.a) * (__int128(q.b) * r.c - __int128(q.c) * r.b)
         - __int128(p.b) * (__int128(q.a) * r.c - __int128(q.c) * r.a)
         + __int128(p.c) * (__int128(q.a) * r.b - __int128(q.b) * r.a);
}
