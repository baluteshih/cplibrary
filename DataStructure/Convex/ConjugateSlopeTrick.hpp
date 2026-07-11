#pragma once

#include "DataStructure/Convex/SlopeTrick.hpp"

/*
reference: https://maspypy.com/slope-trick-3-slope-trick-の凸共役 
*/

template<typename T, T INF = std::numeric_limits<T>::max() / 2>
class ConjugateSlopeTrick : private SlopeTrick<T, INF> {
    using super = SlopeTrick<T, INF>;
public:
    ConjugateSlopeTrick() : super() {}
    using super::is_inf;
    T f0() { return -super::top(); }
    ConjugateSlopeTrick& add_const(T a) { super::add_const(a); }
    ConjugateSlopeTrick& add_x_minus_a(T c, T a = 0) {
        if (a) shift(-a);
        if (c > 0) super::add_r += c;
        if (c < 0) super::add_l += c;
        if (a) shift(a);
        return *this;
    }
    ConjugateSlopeTrick& add_abs(T c, T a = 0) { return add_x_minus_a(c, a).add_x_minus_a(-c, a); }
    ConjugateSlopeTrick& add_linear(T a, T b = 0) { return super::shift(a).add_const(b), *this; }
    ConjugateSlopeTrick& shift(int a) { return super::add_linear(a, 0), *this; }
    ConjugateSlopeTrick& sliding_window_minimum(T a, T b) {
        assert(a <= b);
        shift(a);
        for (int i = 0; i < b - a; ++i) super::add_x_minus_a(0);
        return *this;
    }
    ConjugateSlopeTrick& convolve(const std::vector<T>& g, int base = 0) {
        for (int i = 1; i < int(g.size()); ++i) super::add_x_minus_a(g[i] - g[i - 1]);
        if (base != 0) shift(-base);
        return *this;
    }
    ConjugateSlopeTrick& clear_left() { return super::suffix_min(), *this; }
    ConjugateSlopeTrick& clear_right() { return super::prefix_min(), *this; }
    T min_val(T p = 0) {
        return -super::eval(p);
    }
};
