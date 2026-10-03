#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Usage: gen <n> <m> <max_bound> <mode> <param> [<slack>]
//   feasible <slack> : sum of random cycles; bounds are flow -/+ up to <slack>
//   tight <unused>   : sum of heavy cycles; half the edges have lower = upper = flow,
//                      the other half lower = 0, so vertex demands are huge
//   perturb <k> [<s>]: like feasible with slack <s> (default 3), then <k> edges get a
//                      bound shifted just past their planted flow (often infeasible)
//   random <unused>  : independent random bounds on random edges (usually infeasible)

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

std::vector<Planted> plant_cycles(int n, int m, int min_flow, int max_flow, int max_len) {
    std::vector<int> order(n);
    for (int i = 0; i < n; ++i) {
        order[i] = i;
    }

    std::vector<Planted> planted;
    while (static_cast<int>(planted.size()) < m) {
        int left = m - static_cast<int>(planted.size());
        int len = rnd.next(1, std::min({n, max_len, left}));
        shuffle(order.begin(), order.end());
        int flow = rnd.next(min_flow, max_flow);
        for (int i = 0; i < len; ++i) {
            planted.push_back({order[i], order[(i + 1) % len], flow});
        }
    }
    return planted;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    const int n = opt<int>(1);
    const int m = opt<int>(2);
    const int max_bound = opt<int>(3);
    const std::string mode = opt<std::string>(4);
    const int param = opt<int>(5);

    std::vector<Edge> edges;
    if (mode == "random") {
        for (int i = 0; i < m; ++i) {
            int u = rnd.next(0, n - 1);
            int v = rnd.next(0, n - 1);
            int lower = rnd.next(0, max_bound);
            int upper = rnd.next(lower, max_bound);
            edges.push_back({u, v, lower, upper});
        }
    }
    else if (mode == "tight") {
        int max_len = rnd.next(2, n);
        std::vector<Planted> planted = plant_cycles(n, m, max_bound * 9 / 10, max_bound, max_len);
        for (int i = 0; i < m; ++i) {
            const Planted &p = planted[i];
            bool exact = rnd.next(2) == 0;
            edges.push_back({p.u, p.v, exact ? p.flow : 0, exact ? p.flow : max_bound});
        }
    }
    else {
        ensuref(mode == "feasible" || mode == "perturb", "unknown mode %s", mode.c_str());
        int slack = mode == "feasible" ? param : argc > 6 ? opt<int>(6) : 3;
        int max_len = rnd.next(1, n);
        std::vector<Planted> planted = plant_cycles(n, m, 0, max_bound, max_len);
        for (const Planted &p : planted) {
            int lower = std::max(0, p.flow - rnd.next(0, slack));
            int upper = std::min(max_bound, p.flow + rnd.next(0, slack));
            edges.push_back({p.u, p.v, lower, upper});
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

    std::cout << n << ' ' << m << '\n';
    for (const Edge &e : edges) {
        std::cout << label[e.u] << ' ' << label[e.v] << ' ' << e.lower << ' ' << e.upper << '\n';
    }
}
