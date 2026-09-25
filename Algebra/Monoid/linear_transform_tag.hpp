#pragma once

#include "Algebra/Monoid/sum_and_size.hpp"

template<typename T>
struct linear_transform_tag {
    T a, b;
    linear_transform_tag(T _a = 1, T _b = 0): a(_a), b(_b) {}
    linear_transform_tag operator+(const linear_transform_tag &rhs) const {
        return linear_transform_tag(a * rhs.a, rhs.a * b + rhs.b);
    }
};

template<typename T, typename size_value>
sum_and_size<T, size_value> operator+(const sum_and_size<T, size_value> &lhs, const linear_transform_tag<T> &rhs) {
    return sum_and_size<T, size_value>(lhs.val * rhs.a + lhs.sz * rhs.b, lhs.sz);  
}
