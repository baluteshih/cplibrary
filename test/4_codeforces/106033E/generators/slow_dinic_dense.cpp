#include "testlib.h"
#include <vector>
#include <utility>
#include <array>
#include <iostream>
#include <cassert>

using std::vector, std::tuple, std::cout;

const int MAXC = 1'000'000'000;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  const int N = opt<int>("N", 200);

  vector<tuple<int, int, int>> edges;
  vector<int> perm(N);
  for (int i = 0; i < N; i++)
    perm[i] = i;
  shuffle(perm.begin() + 1, perm.end() - 1);
  auto add_edge = [&](int a, int b, int c) {
    edges.emplace_back(a, b, rnd.next(1, c));
  };

  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < i; j++) {
      add_edge(i, j, 1);
      if (j + 1 != i)
        add_edge(j, i, 1);
    }
  }
  shuffle(edges.begin(), edges.end());
  for (int i = 1; i < N - 1; i++) {
    add_edge(i - 1, i, 1 << 29);
  }
  for (int i = 0; i < N - 1; i++) {
    add_edge(i, N - 1, 1 << 15);
    add_edge(N - 1, i, 1 << 29);
  }

  cout << N << ' ' << int(edges.size()) << '\n';
  for (auto [u, v, w] : edges)
    cout << u + 1 << ' ' << v + 1 << ' ' << w << '\n';
}
