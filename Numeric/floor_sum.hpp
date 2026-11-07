#pragma once

// sum^{n-1}_0 floor((a * i + b) / m) in log(n + m + a + b)
template<typename T = long long, typename Res = T>
Res floor_sum(T n, T m, T a, T b) {
    assert(n >= 0 && m > 0 && a >= 0 && b >= 0);
    Res N = n, M = m, A = a, B = b, ans = 0;
    while (N != 0) {
        if (A >= M) {
            Res x = N, y = N - 1;
            if (x % 2 == 0) x /= 2;
            else y /= 2;
            ans += x * y * (A / M), A %= M;
        }
        if (B >= M) ans += N * (B / M), B %= M;
        Res top = A * N + B;
        if (top < M) break;
        N = top / M, B = top % M, std::swap(M, A);
    }
    return ans;
}
