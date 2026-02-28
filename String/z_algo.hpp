#pragma once

std::vector<int> make_z(const std::string &s) {
    std::vector<int> z(s.size());
    int l = 0, r = 0;
    z[0] = s.size();
    for (int i = 1; i < std::ssize(s); ++i) {
        z[i] = std::max(0, std::min(r - i + 1, z[i - l]));
        while (i + z[i] < std::ssize(s) && s[i + z[i]] == s[z[i]]) ++z[i];
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}
