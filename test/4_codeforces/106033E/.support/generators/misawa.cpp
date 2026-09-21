#include "testlib.h"
#include <vector>
#include <utility>
#include <array>
#include <iostream>
#include <cassert>

using std::vector, std::tuple, std::cout;

const int MAXC = 1'000'000'000;

// https://gist.github.com/MiSawa/9532038
// http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=maxFlowRevisited
// 6k-2 頂点, 3k^2 + 4k - 4

vector<tuple<int, int, int>> worst_dinic2(int k) {
#define REP(i, b, n) for(int i = (b); i < (n); ++i)
  const int INF = 1<<25;
  const int q = k-1, n = 6*k - 2;
  const int src = 0, dst = 1;
  int a = 2;
  const int sb = a, se = a+=k;
  const int tb = a, te = a+=k;
  const int ub = a, ue = a+=2*q;
  const int vb = a, ve = a+=2*q;
  vector<tuple<int, int, int>> edges;
  vector<int> perm(n);
  for (int i = 0; i < n; i++)
    perm[i] = i;
  perm[n - 1] = dst;
  perm[dst] = n - 1;
  shuffle(perm.begin() + 2, perm.end() - 1);
  auto add_edge = [&](int a, int b, int c) {
    edges.emplace_back(perm[a], perm[b], c);
  };
  REP(s, sb, se) add_edge(src, s, k);
  REP(t, tb, te) add_edge(t, dst, k);
  REP(s, sb, se) REP(t, tb, te) add_edge(s, t, 1);
  add_edge(src, ub, INF); add_edge(vb, dst, INF);
  REP(u, ub, ue-1) add_edge(u, u+1, INF);
  REP(v, vb, ve-1) add_edge(v+1, v, INF);
  for(int u = ub+1; u < ue; u += 4) REP(t, tb, te)
    add_edge(u, t, k);
  for(int u = ub+3; u < ue; u += 4) REP(s, sb, se)
    add_edge(u, s, k);
  for(int v = vb+1; v < ve; v += 4) REP(s, sb, se)
    add_edge(s, v, k);
  for(int v = vb+3; v < ve; v += 4) REP(t, tb, te)
    add_edge(t, v, k);
  return edges;
#undef REP
}

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
  const int N = opt<int>("N", 200);

  auto edges = worst_dinic2(N / 6);

  cout << N << ' ' << int(edges.size()) << '\n';
  for (auto [u, v, w] : edges)
    cout << u + 1 << ' ' << v + 1 << ' ' << w << '\n';
}
