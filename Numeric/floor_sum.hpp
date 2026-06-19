#pragma once

// sum^{n-1}_0 floor((a * i + b) / m) in log(n + m + a + b)
template<typename T = long long, typename Res = T>
Res floor_sum(T n, T m, T a, T b) {
    Res ans = 0;
    if (a >= m) ans += Res(n - 1) * Res(n) * Res(a / m) / Res(2), a %= m;
    if (b >= m) ans += Res(n) * Res(b / m), b %= m;
    Res y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += Res(n - (x_max + a - 1) / a) * Res(y_max);
    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
    return ans;
}
