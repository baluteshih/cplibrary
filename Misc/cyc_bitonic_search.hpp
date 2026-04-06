#pragma once

/* 
   bool pred(int a, int b);
   a is better than b
   f(0) ~ f(n - 1) is a cyclic-shift bitonic-function
   return idx s.t. pred(x, idx) is false forall x
*/
int cyc_bitonic_search(int n, auto pred) {
    if (n == 1) return 0;
    int l = 0, r = n; bool rv = pred(1, 0);
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (pred(0, m) ? rv: pred(m, (m + 1) % n)) r = m;
        else l = m;
    }
    return pred(l, r % n) ? l : r % n;
}

/* 
   bool pred(int o, int a, int b);
   a is better than b
   f(o, 0) ~ f(o, n - 1) is a cyclic-shift bitonic-function
   return idx[o] s.t. pred(o, x, idx[o]) is false forall x
   idx should be non-decreasing, and idx[o] != o
*/
std::vector<int> rotating_calipers(int n, auto pred) {
    assert(n >= 2);
    std::vector<int> res(n, 1);
    for (int i = 2; i < n; ++i)
        if (pred(0, i, res[0]))
            res[0] = i;
    for (int i = 1; i < n; ++i) {
        res[i] = res[i - 1];
        while ((res[i] + 1) % n != i && pred(i, (res[i] + 1) % n, res[i] % n))
            ++res[i];
        res[i] %= n;
    }
    return res;
}
