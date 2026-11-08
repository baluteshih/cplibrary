#include "testlib.h"
#include "exact_geometry.hpp"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(4, 3000, "n");
    inf.readEoln();
    std::vector<Point> p(n);
    for (auto &q : p) {
        for (int j = 0; j < 3; ++j) {
            if (j) inf.readSpace();
            q[j] = inf.readLong(-1000000000LL, 1000000000LL, "coordinate");
        }
        inf.readEoln();
    }
    ensuref(dimension_three(p), "The point cloud must have affine dimension three");
    inf.readEof();
    return 42;
}
