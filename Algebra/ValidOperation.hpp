#pragma once

template <typename A, typename B>
concept Addable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a + b; };

template <typename A, typename B>
concept Subtractable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a - b; };

template <typename A, typename B>
concept Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B b) { a * b; };
