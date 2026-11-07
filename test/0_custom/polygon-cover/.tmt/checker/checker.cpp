#include "testlib.h"
#include <algorithm>
#include <cmath>
#include <string>

long double read_value(InStream &stream, bool official) {
    std::string token = stream.readToken();
    try {
        std::size_t used = 0;
        long double value = std::stold(token, &used);
        if (used == token.size() && std::isfinite(value)) return value;
    }
    catch (...) {}
    quitf(official ? _fail : _wa, "Expected a finite real number");
}

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int k = inf.readInt();
    for (int depth = 1; depth <= k; ++depth) {
        long double expected = read_value(ans, true);
        long double actual = read_value(ouf, false);
        long double allowed = 1e-6L * std::max(1.0L, std::fabs(expected));
        if (std::fabs(actual - expected) > allowed) {
            quitf(_wa, "Area at depth %d differs from reference", depth);
        }
    }
    if (!ans.seekEof()) quitf(_fail, "Extra official answer tokens");
    if (!ouf.seekEof()) quitf(_wa, "Extra output tokens");
    quitf(_ok, "All coverage areas within tolerance");
}
