#include "testlib.h"
#include <vector>
#include <utility>
#include <array>
#include <iostream>

using std::vector, std::tuple, std::cout;

const int MAXC = 1'000'000'000;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  const int N = opt<int>("N", 200);

  // generate a graph that needs to "regret"
  vector<tuple<int, int, int>> edges;
  edges.emplace_back(0, 1, 1);
  edges.emplace_back(1, 2, 1);
  edges.emplace_back(2, N - 1, 1);

  int cnt = 3;
  for (int f = 2; cnt + f * 2 < N; f++) {
    {
      int last = 0;
      for (int i = 0; i < f; i++) {
        int id = cnt++;
        edges.emplace_back(last, id, f);
        last = id;
      }
      edges.emplace_back(last, 2, f);
    }
    {
      int last = N - 1;
      for (int i = 0; i < f; i++) {
        int id = cnt++;
        edges.emplace_back(id, last, f);
        last = id;
      }
      edges.emplace_back(1, last, f);
    }
  }

  cout << N << ' ' << int(edges.size()) << '\n';
  for (auto [u, v, w] : edges)
    cout << u + 1 << ' ' << v + 1 << ' ' << w << '\n';
}
