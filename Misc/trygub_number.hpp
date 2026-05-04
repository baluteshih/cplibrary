#pragma once

// source: https://codeforces.com/blog/entry/115626
template<typename T, T base = 2>
class trygub_number {
public:
    std::map<int, T> digs;
    // += a * base ** b
    void add(T a, int b) {
        digs[b] += a;
        int t;
        do {
            t = digs[b] / base;
            digs[b + 1] += t;
            digs[b] -= t * base;
            if (digs[b] == 0) digs.erase(b);
            b++;
        } while(t);
        if (digs[b] == 0)
            digs.erase(b);
    }
    // get the k-th bit
    T get(int k) {
        auto it = digs.lower_bound(k);
        T ans = it == std::end(digs) || it->first > k ? 0 : it->second;
        if(it != std::begin(digs) && std::prev(it)->second < 0)
            ans--;
        return (ans + base) % base;
    }
};
