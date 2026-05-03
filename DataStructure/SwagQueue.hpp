#pragma once

template<typename T>
class SwagQueue {
    int sz = 0;
    std::vector<T> data, cum_l;
    T cum_r;
public:
    SwagQueue() : cum_l(1, T()), cum_r() {}
    int size() { return sz; }
    void push(T x) {
        ++sz;
        cum_r = cum_r + x;
        data.push_back(x);
    }
    void pop() {
        --sz;
        cum_l.pop_back();
        if (cum_l.empty()) {
            cum_l.push_back(T());
            cum_r = T();
            while (int(data.size()) > 1) {
                cum_l.push_back(data.back() + cum_l.back());
                data.pop_back();
            }
            data.pop_back();
        }
    }
    T lprod() { return cum_l.back(); }
    T rprod() { return cum_r; }
    T prod() { return lprod() + rprod(); }
};
