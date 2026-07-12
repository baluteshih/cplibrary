#pragma once

/*
reference: https://maspypy.com/slope-trick-1-解説編
*/

template<typename T, T INF = std::numeric_limits<T>::max() / 2>
class SlopeTrick {
    using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;
    using max_heap = std::priority_queue<T>;
    max_heap pq_l;
    min_heap pq_r;
    T min_f;
protected:
    T top_l() const { return pq_l.empty() ? -INF : pq_l.top() + add_l; }
    T top_r() const { return pq_r.empty() ? INF : pq_r.top() + add_r; }
    T pop_l() { T res = top_l(); if (!pq_l.empty()) pq_l.pop(); return res; }
    T pop_r() { T res = top_r(); if (!pq_r.empty()) pq_r.pop(); return res; }
    void push_l(T a) { pq_l.push(a - add_l); }
    void push_r(T a) { pq_r.push(a - add_r); }
    T add_l, add_r; 
public:
    SlopeTrick() : min_f(), add_l(), add_r() {}
    bool is_inf(T v) { return v >= INF || v <= -INF; }
    int size_l() { return pq_l.size(); }
    int size_r() { return pq_r.size(); }
    int size() { return size_l() + size_r(); }
    T top() { return min_f; }
    std::pair<T, T> top_interval() { return {top_l(), top_r()}; }
    SlopeTrick& add_const(T a) { return min_f += a, *this; }
    SlopeTrick& add_x_minus_a(T a) {
        min_f += std::max(T(0), top_l() - a);
        push_l(a), push_r(pop_l());
        return *this;
    }
    SlopeTrick& add_a_minus_x(T a) {
        min_f += std::max(T(0), a - top_r());
        push_r(a), push_l(pop_r());
        return *this;
    }
    SlopeTrick& add_abs(T a) { return add_x_minus_a(a).add_a_minus_x(a); } 
    SlopeTrick& add_linear(int a, T b) {
        for (min_f += b; a > 0; --a) {
            T x = pop_l();
            min_f += x, push_r(x);
        }
        for (; a < 0; ++a) {
            T x = pop_r();
            min_f -= x, push_l(x);
        }
        return *this;
    }
    SlopeTrick& shift(T a) { return add_l += a, add_r += a, *this; }
    SlopeTrick& sliding_window_minimum(T a, T b) {
        assert(a <= b);
        add_l += a, add_r += b;
        return *this;
    }
    SlopeTrick& prefix_min() { return min_heap().swap(pq_r), *this; }
    SlopeTrick& suffix_min() { return max_heap().swap(pq_l), *this; }
    T eval(T x) {
        T res = min_f;
        auto tl = pq_l; auto tr = pq_r;
        for (; !tl.empty(); tl.pop()) res += std::max(T(0), (tl.top() + add_l) - x);
        for (; !tr.empty(); tr.pop()) res += std::max(T(0), x - (tr.top() + add_r));
        return res;
    }
};
