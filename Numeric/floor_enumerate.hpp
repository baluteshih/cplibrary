#pragma once

/* 
call (x, l, r) such that i in [l, r) having x = floor(n / i)
x is enumerated from large to small
*/
template<typename T, typename F>
void floor_enumerate(T n, F func) {
    for (T l = 1, r; l <= n; l = r + 1) {
        T x = n / l;
        r = n / x;
        func(x, l, r + 1);
    }
}
