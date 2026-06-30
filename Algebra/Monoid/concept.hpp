#pragma once

#include "Algebra/ValidOperation.hpp"

template<typename T>
concept isMonoid = Addable<T, T> && std::default_initializable<T>;

template<typename T>
concept isCommutativeMonoid = isMonoid<T>;
