#pragma once

#include "Algebra/Monoid/sum_and_size.hpp"
#include "Algebra/Tag/linear_transform_tag.hpp"

template<typename T, typename size_value>
sum_and_size<T, size_value>& operator+=(sum_and_size<T, size_value> &lhs, const linear_transform_tag<T> &rhs) {
    lhs.val = lhs.val * rhs.a + lhs.sz * rhs.b;
    return lhs;
}
