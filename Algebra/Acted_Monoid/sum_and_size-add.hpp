#pragma once

#include "Algebra/Monoid/sum_and_size.hpp"
#include "Algebra/Tag/add_tag.hpp"

template<typename T, typename size_value>
sum_and_size<T, size_value> operator+(const sum_and_size<T, size_value> &lhs, const add_tag<T> &rhs) {
    return sum_and_size<T, size_value>(lhs.val + rhs.a * lhs.sz, lhs.sz);  
}
