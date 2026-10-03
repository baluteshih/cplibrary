#pragma once

#include "Algebra/Monoid/sum_v.hpp"
#include "Algebra/Tag/add_tag.hpp"

template<typename T>
sum_v<T> operator+(const sum_v<T> &lhs, const add_tag<T> &rhs) {
    return sum_v<T>(lhs.val + rhs.a);  
}
