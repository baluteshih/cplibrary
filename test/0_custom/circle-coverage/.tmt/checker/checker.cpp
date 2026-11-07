#include "testlib.h"
#include <algorithm>
#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <string>

long double readNumber(InStream &stream) {
    std::string token = stream.readToken();
    char *end = nullptr;
    errno = 0;
    long double value = std::strtold(token.c_str(), &end);
    if (end == token.c_str() || *end != '\0' || !std::isfinite(value)) {
        stream.quitf(_wa, "expected a finite real number");
    }
    return value;
}

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    for (int k = 1; k <= n; ++k) {
        long double expected = readNumber(ans);
        long double actual = readNumber(ouf);
        long double tolerance = 1e-6L * std::max(1.0L, std::abs(expected));
        if (std::abs(actual - expected) > tolerance) {
            quitf(_wa, "layer %d: expected %.15Lf, got %.15Lf", k, expected, actual);
        }
    }
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output token");
    }
    quitf(_ok, "all %d coverage areas match", n);
}
