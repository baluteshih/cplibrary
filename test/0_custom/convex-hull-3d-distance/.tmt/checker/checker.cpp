#include "testlib.h"
#include <algorithm>
#include <cmath>
#include <string>

long double read_distance(InStream &stream, bool official) {
    std::string token = stream.readToken();
    try {
        std::size_t used = 0;
        long double value = std::stold(token, &used);
        if (used == token.size() && std::isfinite(value) && value >= 0) return value;
    }
    catch (...) {}
    quitf(official ? _fail : _wa, "Expected a finite nonnegative distance");
}
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    inf.readInt();
    int q = inf.readInt();
    for (int i = 0; i < q; ++i) {
        long double expected = read_distance(ans, true), actual = read_distance(ouf, false);
        if (std::fabs(expected - actual) > 1e-8L * std::max(1.0L, expected)) quitf(_wa, "Wrong distance at query %d", i + 1);
    }
    if (!ans.seekEof()) quitf(_fail, "Extra official output");
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "Every plane distance is within tolerance");
}
