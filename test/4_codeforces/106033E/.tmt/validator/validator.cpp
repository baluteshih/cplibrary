#include "testlib.h"
#include <iostream>
#include <set>
#include <utility>
#include <string>

const int MAXN = 400;
const long long MAXC = 1'000'000'000;

int main() {
    registerValidation();

    int N = inf.readInt(2, MAXN, "N");
    inf.readSpace();
    int M = inf.readInt(0, N * (N - 1), "M");
    inf.readEoln();

    std::set<std::pair<int, int>> seen_edges;

    for (int i = 0; i < M; ++i) {
        int u = inf.readInt(1, N, "u_" + std::to_string(i));
        inf.readSpace();
        int v = inf.readInt(1, N, "v_" + std::to_string(i));
        inf.readSpace();
        inf.readLong(1, MAXC, "c_" + std::to_string(i));
        inf.readEoln();

        ensuref(u != v, "Self-loop detected: u == v == %d", u);

        auto edge = std::make_pair(u, v);
        ensuref(seen_edges.insert(edge).second, "Duplicate edge (%d -> %d)", u, v);
    }

    inf.readEof();
    return 42;
}
