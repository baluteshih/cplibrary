#include "testlib.h"
#include <vector>
#include <utility>
#include <cstdio>

const int MAXC = 1'000'000'000;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = opt<int>("N", 200);
    int M = opt<int>("M", N * (N - 1));
    int wl = opt<int>("wl", 1);
    int wr = opt<int>("wr", MAXC);

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i != j)
                edges.emplace_back(i, j);
    shuffle(edges.begin(), edges.end());
    edges.resize(M);

    printf("%d %d\n", N, M);
    for (auto [u, v] : edges)
        printf("%d %d %d\n", u + 1, v + 1, rnd.next(wl, wr));
}
