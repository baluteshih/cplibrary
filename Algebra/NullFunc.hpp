#pragma once

struct NullFunc {
    constexpr void operator()(auto&&...) const {}
};
