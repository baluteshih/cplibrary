#pragma once

// only works for integer coordinates!! maintain max
template<typename T>
struct Line {
    mutable T a, b, p;
    bool operator<(const Line &rhs) const { return a < rhs.a; }
    bool operator<(T x) const { return p < x; }
};
template<typename T, T kInf = 1'000'000'000'000'000'000LL>
struct DynamicHull : multiset<Line<T>, less<>> {
    using iterator = multiset<Line<T>, less<>>::iterator; 
    T Div(T a, T b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == this->end()) { x->p = kInf; return 0; }
        if (x->a == y->a) x->p = x->b > y->b ? kInf : -kInf;
        else x->p = Div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }
    void addline(T a, T b) {
        auto z = this->emplace(a, b, 0), y = z++, x = y;
        while (isect(y, z)) z = this->erase(z);
        if (x != this->begin() && isect(--x, y)) isect(x, y = this->erase(y));
        while ((y = x) != this->begin() && (--x)->p >= y->p) isect(x, this->erase(y));
    }
    T query(T x) {
        auto l = *this->lower_bound(x);
        return l.a * x + l.b;
    }
};
