#pragma once

template<typename T, typename Fallback>
using ReplaceVoid = std::conditional_t<std::same_as<T, void>, Fallback, T>;

template <typename A, typename B>
concept ValidAddableState = requires(A a, B b) { a + b; };

template <typename A, typename B>
concept ValidSubtractableState = requires(A a, B b) { a - b; };
