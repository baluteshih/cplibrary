#include "testlib.h"
#include "judge_geometry.hpp"
#include <algorithm>
#include <vector>

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    inf.readInt();
    std::vector<Key> supports(n + 1);
    for (int i = 1; i <= n; ++i) {
        long long x = inf.readLong(), y = inf.readLong();
        long long u = inf.readLong(), v = inf.readLong();
        supports[i] = key(make_dual(x, y, u, v, i));
    }
    int m = ans.readInt(3, n, "official edge count");
    std::vector<Key> expected(m);
    for (auto &k : expected) k = supports[ans.readInt(1, n)];
    if (!ans.seekEof()) quitf(_fail, "Extra official tokens");
    if (ouf.readInt(3, n, "edge count") != m) quitf(_wa, "Wrong number of edges");
    std::vector<Key> actual(m);
    for (auto &k : actual) k = supports[ouf.readInt(1, n)];
    if (!ouf.seekEof()) quitf(_wa, "Extra output tokens");
    auto first = std::find(expected.begin(), expected.end(), actual[0]);
    if (first == expected.end()) quitf(_wa, "Redundant constraint selected");
    int offset = int(first - expected.begin());
    for (int i = 0; i < m; ++i) {
        if (actual[i] != expected[(offset + i) % m]) quitf(_wa, "Wrong boundary or cyclic order");
    }
    quitf(_ok, "Correct boundary up to cyclic rotation and coincident representatives");
}
