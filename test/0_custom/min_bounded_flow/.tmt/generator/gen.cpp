#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Usage: gen <n> <m> <max_bound> <mode> <param> [<slack>]
// A planted flow is built from random s->t paths and random cycles avoiding t (vertex 0
// is s, vertex 1 is t before relabelling), so it is a feasible s-t flow. Apart from
// self-loops, t never has an outgoing edge, so every flow value equals t's net inflow and
// is non-negative.
//   feasible <free%> : bounds are planted flow -/+ up to <slack> (default 0); <free%>
//                      percent of the edges get lower = 0 and a random upper instead
//   tight <free%>    : heavy flows, every non-free edge has lower = upper = flow
//   perturb <k>      : feasible with 20% free edges, then <k> edges get a bound
//                      shifted just past their planted flow (often infeasible)
//   random <unused>  : independent random bounds on random edges (usually infeasible);
//                      an edge leaving t is reversed

struct Edge {
    int u;
    int v;
    int lower;
    int upper;
};

struct Planted {
    int u;
    int v;
    int flow;
};

std::vector<Planted> plant(int n, int m, int min_flow, int max_flow) {
    std::vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }

    int max_len = rnd.next(1, n);
    std::vector<Planted> planted;
    while (static_cast<int>(planted.size()) < m) {
        int left = m - static_cast<int>(planted.size());
        int len = rnd.next(1, std::min({n, max_len, left}));
        int flow = rnd.next(min_flow, max_flow);
        shuffle(order.begin(), order.end());
        if (rnd.next(2) == 0 && n > 2) {
            std::vector<int> cycle;
            for (int v : order) {
                if (static_cast<int>(cycle.size()) < std::min(len, n - 1) && v != 1) {
                    cycle.push_back(v);
                }
            }
            len = static_cast<int>(cycle.size());
            for (int i = 0; i < len; ++i) {
                planted.push_back({cycle[i], cycle[(i + 1) % len], flow});
            }
        }
        else {
            std::vector<int> path = {0};
            for (int v : order) {
                if (static_cast<int>(path.size()) == len) {
                    break;
                }
                if (v > 1) {
                    path.push_back(v);
                }
            }
            path.push_back(1);
            for (int i = 0; i + 1 < static_cast<int>(path.size()); ++i) {
                planted.push_back({path[i], path[i + 1], flow});
            }
        }
    }
    planted.resize(m);
    return planted;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    const int n = opt<int>(1);
    const int m = opt<int>(2);
    const int max_bound = opt<int>(3);
    const std::string mode = opt<std::string>(4);
    const int param = opt<int>(5);
    const int slack = argc > 6 ? opt<int>(6) : 0;

    std::vector<Edge> edges;
    if (mode == "random") {
        for (int i = 0; i < m; ++i) {
            int u = rnd.next(0, n - 1);
            int v = rnd.next(0, n - 1);
            if (u == 1) {
                std::swap(u, v);
            }
            int lower = rnd.next(0, max_bound);
            int upper = rnd.next(lower, max_bound);
            edges.push_back({u, v, lower, upper});
        }
    }
    else {
        ensuref(mode == "feasible" || mode == "tight" || mode == "perturb", "unknown mode %s",
                mode.c_str());
        int min_flow = mode == "tight" ? max_bound * 9 / 10 : 0;
        int free_percent = mode == "perturb" ? 20 : param;
        std::vector<Planted> planted = plant(n, m, min_flow, max_bound);
        for (const Planted &p : planted) {
            if (rnd.next(100) < free_percent) {
                int upper = rnd.next(p.flow, max_bound);
                edges.push_back({p.u, p.v, 0, upper});
            }
            else {
                int lower = std::max(0, p.flow - rnd.next(0, slack));
                int upper = std::min(max_bound, p.flow + rnd.next(0, slack));
                edges.push_back({p.u, p.v, lower, upper});
            }
        }
        if (mode == "perturb") {
            for (int k = 0; k < param; ++k) {
                int i = rnd.next(0, m - 1);
                const Planted &p = planted[i];
                if (p.flow < max_bound && rnd.next(2) == 0) {
                    edges[i].lower = p.flow + 1;
                    edges[i].upper = std::max(edges[i].upper, edges[i].lower);
                }
                else if (p.flow > 0) {
                    edges[i].upper = p.flow - 1;
                    edges[i].lower = std::min(edges[i].lower, edges[i].upper);
                }
            }
        }
    }

    std::vector<int> label(n);
    for (int i = 0; i < n; ++i) {
        label[i] = i + 1;
    }
    shuffle(label.begin(), label.end());
    shuffle(edges.begin(), edges.end());

    std::cout << n << ' ' << m << ' ' << label[0] << ' ' << label[1] << '\n';
    for (const Edge &e : edges) {
        std::cout << label[e.u] << ' ' << label[e.v] << ' ' << e.lower << ' ' << e.upper << '\n';
    }
}
