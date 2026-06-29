#pragma once

#include "Algebra/ValidOperation.hpp"

template <typename Edge, typename Vertex>
struct UnifiedWeight {
    using type = std::conditional_t<!std::is_same_v<Vertex, void>, Vertex, Edge>;
};

template <typename Edge, typename Vertex>
using UnifiedWeight_t = typename UnifiedWeight<Edge, Vertex>::type;

template <typename Edge, typename Vertex>
concept ValidAddableUnifiedWeight = 
    (std::is_void_v<Vertex> && ValidAddableState<Edge, Edge>) ||
    (ValidAddableState<Vertex, Vertex> && (std::is_void_v<Edge> || ValidAddableState<Vertex, Edge>));
