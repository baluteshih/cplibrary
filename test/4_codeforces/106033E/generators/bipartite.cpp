#include "testlib.h"
#include <vector>
#include <array>
#include <cstdio>

const int MAXC = 1'000'000'000;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = opt<int>("N", 200);
    int wl = opt<int>("wl", 1);
    int wr = opt<int>("wr", MAXC / N);
    int noise = opt<bool>("noise", true);

    std::vector<std::vector<int>> vis(N, std::vector<int>(N));

    std::vector<std::array<int, 3>> edges;

    for (int i = 1; i <= (N - 2) / 2; ++i)
        edges.push_back({0, i, MAXC}); 
    for (int i = (N - 2) / 2 + 1; i + 1 < N; ++i)
        edges.push_back({i, N - 1, MAXC});
    for (int i = 1; i <= (N - 2) / 2; ++i)
        for (int j = (N - 2) / 2 + 1; j + 1 < N; ++j)
            edges.push_back({i, j, rnd.next(wl, wr)});

    for (auto [u, v, c] : edges)
        vis[u][v] = 1;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (i != j && noise && !vis[i][j])
                edges.push_back({i, j, rnd.next(1, 10)});
    
    shuffle(edges.begin(), edges.end());
    printf("%d %d\n", N, int(edges.size()));
    for (auto [u, v, c] : edges)
        printf("%d %d %d\n", u + 1, v + 1, c);
}
