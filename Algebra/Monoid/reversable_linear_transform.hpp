#pragma once

#include "Algebra/Monoid/linear_transform.hpp"

template<typename T>
struct reversable_linear_transform {
    T a_f = 1, b_f = 0, a_b = 1, b_b = 0;
    reversable_linear_transform(T _a_f = 1, T _b_f = 0, T _a_b = 1, T _b_b = 0) : a_f(_a_f), b_f(_b_f), a_b(_a_b), b_b(_b_b) {}
    reversable_linear_transform(const linear_transform<T> &v) : a_f(v.a), b_f(v.b), a_b(v.a), b_b(v.b) {}
    reversable_linear_transform operator+(const reversable_linear_transform<T> &rhs) const {
        return reversable_linear_transform(rhs.a_f * a_f, rhs.a_f * b_f + rhs.b_f, a_b * rhs.a_b, a_b * rhs.b_b + b_b);
    }
    void reverse() {
        std::swap(a_f, a_b);
        std::swap(b_f, b_b);
    }
    T eval(T x) {
        return a_f * x + b_f;
    }
};
