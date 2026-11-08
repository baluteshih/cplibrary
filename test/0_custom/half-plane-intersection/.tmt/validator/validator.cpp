#include "testlib.h"
#include <array>

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(4, 100000, "n");
    inf.readSpace();
    int b = inf.readInt(1, 1000000000, "B");
    inf.readEoln();
    std::array<std::array<long long, 4>, 4> box{{{-b, -b, b, -b}, {b, -b, b, b}, {b, b, -b, b}, {-b, b, -b, -b}}};
    for (int i = 0; i < n; ++i) {
        std::array<long long, 4> p;
        for (int j = 0; j < 4; ++j) {
            if (j) inf.readSpace();
            p[j] = inf.readLong(-1000000000LL, 1000000000LL, "coordinate");
        }
        inf.readEoln();
        if (i < 4) ensuref(p == box[i], "First four lines must be the specified square");
        ensuref(p[0] != p[2] || p[1] != p[3], "Zero direction");
        __int128 cross = __int128(p[2] - p[0]) * (-p[1]) - __int128(p[3] - p[1]) * (-p[0]);
        ensuref(cross > 0, "Origin must be strictly on the left");
    }
    inf.readEof();
    return 42;
}
