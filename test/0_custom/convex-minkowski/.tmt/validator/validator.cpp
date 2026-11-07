#include "testlib.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 199'999, "n");
    inf.readSpace();
    int m = inf.readInt(1, 199'999, "m");
    inf.readEoln();
    ensuref(n + m <= 200'000, "n + m must not exceed 200000");
    for (int i = 0; i < n + m; ++i) {
        inf.readInt(-100'000'000, 100'000'000, "x");
        inf.readSpace();
        inf.readInt(-100'000'000, 100'000'000, "y");
        inf.readEoln();
    }
    inf.readEof();
    return 42;
}
