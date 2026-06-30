#pragma once

#include "Algebra/ValidOperation.hpp"

template <typename Edge, typename Vertex>
struct UnifiedWeight {
    using type = std::conditional_t<std::is_void_v<Vertex>, Edge, Vertex>;
};

template <typename Edge, typename Vertex>
using UnifiedWeight_t = typename UnifiedWeight<Edge, Vertex>::type;

template <typename Edge, typename Vertex>
concept AddableUnifiedWeight = 
    (std::is_void_v<Vertex> && Addable<Edge, Edge>) ||
    (Addable<Vertex, Vertex> && (std::is_void_v<Edge> || Addable<Vertex, Edge>));
