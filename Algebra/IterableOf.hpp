#pragma once

template <typename C, typename T>
concept IterableOf = std::ranges::range<C> && std::same_as<std::ranges::range_value_t<C>, T>;
