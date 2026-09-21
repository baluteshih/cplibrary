#include "testlib.h"
#include <vector>
#include <utility>
#include <array>
#include <iostream>
#include <cassert>

using std::vector, std::tuple, std::cout;

const int MAXC = 1'000'000'000;

// https://www.zhihu.com/question/266149721
// https://web.archive.org/web/20111122025140/http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=maxFlowRevisited

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  const int N = opt<int>("N", 200);

  const int S = 0;
  const int k = N / 6, p = N / 6 - 1;
  int cnt = 1;
  vector<int> s, t, u, v;
  for (int i = 0; i < k; i++)
    s.push_back(cnt++);
  for (int i = 0; i < k; i++)
    t.push_back(cnt++);
  for (int i = 0; i < p * 2; i++)
    u.push_back(cnt++);
  for (int i = 0; i < p * 2; i++)
    v.push_back(cnt++);

  assert(cnt < N);

  vector<int> path;
  while (cnt < N)
    path.push_back(cnt++);
  // std::cerr << path.size() << std::endl;
  const int T = path.front();

  vector<tuple<int, int, int>> edges;
  vector<int> perm(N);
  for (int i = 0; i < N; i++)
    perm[i] = i;
  shuffle(perm.begin() + 1, perm.end() - 1);
  vector<vector<int>> used(N, vector<int>(N, 0));
  auto add_edge = [&](int a, int b, int c) {
    edges.emplace_back(perm[a], perm[b], c);
    used[a][b] = true;
  };

  constexpr int M = 1 << 15;
  for (int si : s)
    add_edge(S, si, k * M);
  for (int si : s)
    for (int ti : t)
      add_edge(si, ti, 1 * M);
  for (int ti : t)
    add_edge(ti, T, k * M);

  for (int i = 1; i < p; i += 2)
    for (int ti : t)
      add_edge(u[i], ti, k * M);
  for (int i = 1; i < p; i += 2)
    for (int si : s)
      add_edge(si, v[i], k * M);

  add_edge(S, u[0], MAXC);
  for (int i = 1; i < p; i++)
    add_edge(u[i - 1], u[i], MAXC);
  add_edge(u.back(), v.back(), MAXC);
  for (int i = 1; i < p; i++)
    add_edge(v[i], v[i - 1], MAXC);
  add_edge(v[0], T, MAXC);

  for (size_t i = 1; i < path.size(); i++)
    add_edge(path[i - 1], path[i], MAXC);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (i != j && !used[i][j])
        add_edge(i, j, 1);
  shuffle(edges.begin(), edges.end());

  cout << N << ' ' << int(edges.size()) << '\n';
  for (auto [u, v, w] : edges)
    cout << u + 1 << ' ' << v + 1 << ' ' << w << '\n';
}
