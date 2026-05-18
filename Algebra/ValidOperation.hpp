#pragma once

template<typename T, typename Fallback>
using ReplaceVoid = std::conditional_t<std::same_as<T, void>, Fallback, T>;

template <typename A, typename B>
concept ValidAddableState =
    (std::same_as<A, void> && std::same_as<B, void>) ||
    requires(const ReplaceVoid<A, B>& a, 
             const ReplaceVoid<B, A>& b) {
        a + b;
    };

template <typename A, typename B>
concept ValidSubtractableState = 
    (std::same_as<A, void> && std::same_as<B, void>) ||
    requires(const ReplaceVoid<A, B>& a, 
             const ReplaceVoid<B, A>& b) {
        a - b;
    };
