#pragma once

#include "Algebra/Monoid/min_v.hpp"
#include "Algebra/Tag/add_tag.hpp"
#include "Algebra/ValidOperation.hpp"

template<typename T, typename U>
min_v<T> operator+(const min_v<T> &lhs, const add_tag<U> &rhs) {
    return min_v<T>(lhs.val + rhs.a);  
}

template<typename T, typename U>
min_v<T> operator-(const min_v<T> &lhs, const add_tag<U> &rhs) requires (Subtractable<T, U>) {
    return min_v<T>(lhs.val - rhs.a);  
}
