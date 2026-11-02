#pragma once

#include "Algebra/Monoid/min_v.hpp"
#include "Algebra/Tag/add_tag.hpp"
#include "Algebra/ValidOperation.hpp"

template<typename T, typename U>
min_v<T>& operator+=(min_v<T> &lhs, const add_tag<U> &rhs) {
    lhs.val += rhs.a;
    return lhs;
}

template<typename T, typename U>
min_v<T>& operator-=(min_v<T> &lhs, const add_tag<U> &rhs) requires (AssignSubtractable<T, U>) {
    lhs.val -= rhs.a;
    return lhs;
}
