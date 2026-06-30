#pragma once

#include "Algebra/ValidOperation.hpp"

template<typename T>
concept isField = Addable<T, T> && Multiplicable<T, T> && std::default_initializable<T>;
