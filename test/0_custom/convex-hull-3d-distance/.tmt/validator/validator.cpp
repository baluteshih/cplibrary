#include "testlib.h"
#include "exact_geometry.hpp"

Wide scalar(const Point &a, const Point &b) {
    return Wide(a[0]) * b[0] + Wide(a[1]) * b[1] + Wide(a[2]) * b[2];
}
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(4, 500, "n");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();
    std::vector<Point> p(n);
    for (auto &x : p) {
        for (int j = 0; j < 3; ++j) {
            if (j) inf.readSpace();
            x[j] = inf.readLong(-1000000LL, 1000000LL, "coordinate");
        }
        inf.readEoln();
    }
    ensuref(dimension_three(p), "Point cloud must have affine dimension three");
    std::set<Point> checked;
    for (int i = 0; i < q; ++i) {
        Point normal;
        for (int j = 0; j < 3; ++j) {
            if (j) inf.readSpace();
            normal[j] = inf.readLong(-8000000000000LL, 8000000000000LL, "normal");
        }
        ensuref(gcd_wide(gcd_wide(normal[0], normal[1]), normal[2]) == 1, "Normal must be nonzero and primitive");
        for (int j = 0; j < 3; ++j) {
            inf.readSpace();
            inf.readLong(-1000000LL, 1000000LL, "query coordinate");
        }
        inf.readEoln();
        if (!checked.insert(normal).second) continue;
        Wide d = scalar(normal, p[0]);
        for (const auto &x : p) d = std::max(d, scalar(normal, x));
        std::vector<Point> on;
        for (const auto &x : p) if (scalar(normal, x) == d) on.push_back(x);
        int b = 1;
        while (b < int(on.size()) && on[b] == on[0]) ++b;
        bool facet = false;
        if (b < int(on.size())) {
            for (const auto &x : on) if (!zero(cross(difference(on[b], on[0]), difference(x, on[0])))) facet = true;
        }
        ensuref(facet, "Normal must expose a positive-area facet");
    }
    inf.readEof();
    return 42;
}
