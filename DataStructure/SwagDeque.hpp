#pragma once

template<typename T>
class SwagDeque {
    int sz;
    std::vector<T> data_l, data_r, cum_l, cum_r;
    void rebuild() {
        std::vector<T> X;
        std::ranges::reverse(data_l);
        X.insert(X.end(), data_l.begin(), data_l.end());
        X.insert(X.end(), data_r.begin(), data_r.end());
        clear();
        int m = X.size() / 2;
        for (int i = m - 1; i >= 0; --i) push_front(X[i]);
        for (int i = m; i < int(X.size()); ++i) push_back(X[i]);
    }
public:
    SwagDeque() : sz(0), cum_l(1, T()), cum_r(1, T()) {}
    int size() { return sz; }
    void push_back(T x) {
        ++sz;
        data_r.push_back(x);
        cum_r.push_back(cum_r.back() + x);
    }
    void push_front(T x) {
        ++sz;
        data_l.push_back(x);
        cum_l.push_back(x + cum_l.back());
    }
    void clear() {
        sz = 0;
        data_l.clear(), data_r.clear();
        std::vector<T>(1, T()).swap(cum_l);
        std::vector<T>(1, T()).swap(cum_r);
    }
    void pop_front() {
        if (sz == 1) return clear();
        if (data_l.empty()) rebuild();
        --sz;
        data_l.pop_back();
        cum_l.pop_back();
    }
    void pop_back() {
        if (sz == 1) return clear();
        if (data_r.empty()) rebuild();
        --sz;
        data_r.pop_back();
        cum_r.pop_back();
    }
    T front() {
        if (!data_l.empty()) return data_l.back();
        return data_r[0];
    }
    T lprod() { return cum_l.back(); }
    T rprod() { return cum_r.back(); }
    T prod() { return lprod() + rprod(); }
};
