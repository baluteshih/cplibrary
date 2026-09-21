#include "testlib.h"
#include <vector>
#include <array>
#include <cstdio>

const int MAXC = 1'000'000'000;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = opt<int>("N", 200);
    int wl = opt<int>("wl", 1);
    int wr = opt<int>("wr", MAXC / N / N);
    int noise = opt<int>("noise", 0);

    std::vector<std::vector<int>> capacity(N, std::vector<int>(N));

    std::vector<int> vertices;
    for (int i = 1; i + 1 < N; ++i)
        vertices.push_back(i);
    shuffle(vertices.begin(), vertices.end());
    for (int i = int(vertices.size()) - 1; i >= 0; --i) {
        int v = rnd.next(wl, wr);
        for (int j = i - 1; j >= 0; --j) {
            int lst = 0;
            for (int k = 0; k <= j; ++k) {
                capacity[lst][vertices[k]] += v;
                lst = vertices[k];
            }
            capacity[lst][vertices[i]] += v;
            capacity[vertices[i]][N - 1] += v;
        }
    }

    while (noise--) {
        int u = 0, v = 0;
        while (u == v) {
            u = rnd.next(0, N - 1);
            v = rnd.next(0, N - 1);
        }
        capacity[u][v] += rnd.next(1, 10);
    }

    std::vector<std::array<int, 3>> edges;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (capacity[i][j] > 0)
                edges.push_back({i, j, capacity[i][j]});

    shuffle(edges.begin(), edges.end());
    printf("%d %d\n", N, int(edges.size()));
    for (auto [u, v, c] : edges)
        printf("%d %d %d\n", u + 1, v + 1, c);
}
