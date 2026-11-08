#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>

using Wide = __int128;
using Point = std::array<long long, 3>;
using Vector = std::array<Wide, 3>;
using Plane = std::array<Wide, 4>;

Vector difference(const Point &a, const Point &b) {
    return {Wide(a[0]) - b[0], Wide(a[1]) - b[1], Wide(a[2]) - b[2]};
}
Vector cross(const Vector &a, const Vector &b) {
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]};
}
Wide dot(const Vector &a, const Vector &b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
bool zero(const Vector &a) {
    return a[0] == 0 && a[1] == 0 && a[2] == 0;
}
Wide gcd_wide(Wide a, Wide b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        Wide next = a % b;
        a = b;
        b = next;
    }
    return a;
}
Plane plane(const Point &a, const Point &b, const Point &c) {
    auto normal = cross(difference(b, a), difference(c, a));
    Wide g = gcd_wide(gcd_wide(normal[0], normal[1]), normal[2]);
    assert(g != 0);
    for (auto &x : normal) x /= g;
    return {normal[0], normal[1], normal[2], normal[0] * a[0] + normal[1] * a[1] + normal[2] * a[2]};
}
Wide side(const Plane &f, const Point &p) {
    return f[0] * p[0] + f[1] * p[1] + f[2] * p[2] - f[3];
}
bool dimension_three(const std::vector<Point> &p) {
    int n = int(p.size()), b = 1, c = 1;
    while (b < n && p[b] == p[0]) ++b;
    if (b == n) return false;
    while (c < n && zero(cross(difference(p[b], p[0]), difference(p[c], p[0])))) ++c;
    if (c == n) return false;
    auto f = plane(p[0], p[b], p[c]);
    for (const auto &x : p) if (side(f, x) != 0) return true;
    return false;
}
std::string decimal(Wide x) {
    if (x == 0) return "0";
    bool negative = x < 0;
    unsigned __int128 value = negative ? 0 - static_cast<unsigned __int128>(x) : static_cast<unsigned __int128>(x);
    std::string result;
    while (value != 0) {
        result.push_back(char('0' + value % 10));
        value /= 10;
    }
    if (negative) result.push_back('-');
    std::reverse(result.begin(), result.end());
    return result;
}
bool parse_integer(const std::string &s, Wide &result) {
    if (s.empty()) return false;
    std::size_t i = s[0] == '-' || s[0] == '+' ? 1 : 0;
    if (i == s.size()) return false;
    bool negative = s[0] == '-';
    unsigned __int128 limit = (static_cast<unsigned __int128>(1) << 127) - (negative ? 0 : 1);
    unsigned __int128 value = 0;
    for (; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9') return false;
        unsigned digit = unsigned(s[i] - '0');
        if (value > (limit - digit) / 10) return false;
        value = value * 10 + digit;
    }
    result = negative && value != 0 ? -Wide(value - 1) - 1 : Wide(value);
    return true;
}
