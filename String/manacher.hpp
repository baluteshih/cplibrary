#pragma once

std::vector<int> manacher(const string &tmp) {
    std::string s = "%";
    int l = 0, r = 0;
    for (char c : tmp) s.push_back(c), s.push_back('%');
    std::vector<int> z(s.size());
    for (int i = 0; i < std::ssize(s); ++i) {
        z[i] = r > i ? std::min(z[2 * l - i], r - i) : 1;
        while (i - z[i] >= 0 && i + z[i] < std::ssize(s) && s[i + z[i]] == s[i - z[i]]) ++z[i];
        if (z[i] + i > r) r = z[i] + i, l = i;
    }
    return z;
}
/*
get the radius of center i, 0-base
for example, aba has radius 2
*/
int get_radius_odd(const std::vector<int> &z, int i) {
    return z[i * 2 + 1] / 2;
}
/*
get the radius of center i, i + 1, 0-base
for example, abba has radius 2
*/
int get_radius_even(const std::vector<int> &z, int i) {
    return z[i * 2 + 2] / 2;
}
