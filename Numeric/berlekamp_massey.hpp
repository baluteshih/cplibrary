#pragma once

template <typename T>
std::vector<T> berlekamp_massey(const std::vector<T> &output) {
    std::vector<T> d(output.size() + 1), me, he;
    for (int f = 0, i = 1; i <= int(output.size()); ++i) {
        for (int j = 0; j < int(me.size()); ++j)
            d[i] += output[i - j - 2] * me[j];
        if ((d[i] -= output[i - 1]) == 0) continue;
        if (me.empty()) {
            me.resize(f = i);
            continue;
        }
        std::vector<T> o(i - f - 1);
        T k = -d[i] / d[f];
        o.push_back(-k);
        for (T x : he) o.push_back(x * k);
        if (o.size() < me.size()) o.resize(me.size());
        for (int j = 0; j < int(me.size()); ++j) o[j] += me[j];
        if (i - f + int(he.size()) >= int(me.size())) he = me, f = i;
        me = o;
    }
    return me;
}
