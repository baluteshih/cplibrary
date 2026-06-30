#pragma once

template<typename T, typename Fallback>
using ReplaceVoid = std::conditional_t<std::same_as<T, void>, Fallback, T>;

template <typename A, typename B>
concept ValidAddableState = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a + b; };

template <typename A, typename B>
concept ValidSubtractableState = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a - b; };
