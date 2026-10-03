#include "testlib.h"

#include <string>
#include <vector>

struct Edge {
    int u;
    int v;
    long long lower;
    long long upper;
};

// Reads "YES" + m flows (or "NO") from the stream and returns whether a valid
// circulation was given. Malformed or invalid output fails the stream.
bool read_answer(InStream &stream, int n, const std::vector<Edge> &edges) {
    std::string verdict = stream.readToken("YES|NO", "verdict");
    if (verdict == "NO") {
        return false;
    }

    std::vector<long long> balance(n, 0);
    for (int i = 0; i < static_cast<int>(edges.size()); ++i) {
        const Edge &e = edges[i];
        long long flow = stream.readLong(e.lower, e.upper, format("flow[%d]", i + 1));
        balance[e.u] -= flow;
        balance[e.v] += flow;
    }
    for (int v = 0; v < n; ++v) {
        if (balance[v] != 0) {
            stream.quitf(_wa, "flow is not conserved at vertex %d (in - out = %lld)", v + 1, balance[v]);
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    std::vector<Edge> edges(m);
    for (Edge &e : edges) {
        e.u = inf.readInt() - 1;
        e.v = inf.readInt() - 1;
        e.lower = inf.readLong();
        e.upper = inf.readLong();
    }

    bool jury_yes = read_answer(ans, n, edges);
    bool team_yes = read_answer(ouf, n, edges);
    if (!ouf.seekEof()) {
        quitf(_wa, "extra tokens after the expected output");
    }

    if (jury_yes && !team_yes) {
        quitf(_wa, "a feasible circulation exists, but contestant printed NO");
    }
    if (!jury_yes && team_yes) {
        quitf(_fail, "contestant found a valid circulation, but jury printed NO");
    }
    quitf(_ok, "%s", jury_yes ? "valid circulation" : "correctly reported NO");
}
