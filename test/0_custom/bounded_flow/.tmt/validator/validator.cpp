#include "testlib.h"

const int MAX_N = 200;
const int MAX_M = 10'200;
const int MAX_BOUND = 100'000;

int main(int argc, char **argv) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, MAX_N, "n");
    inf.readSpace();
    int m = inf.readInt(1, MAX_M, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n, "u");
        inf.readSpace();
        inf.readInt(1, n, "v");
        inf.readSpace();
        int lower = inf.readInt(0, MAX_BOUND, "lower");
        inf.readSpace();
        inf.readInt(lower, MAX_BOUND, "upper");
        inf.readEoln();
    }
    inf.readEof();

    return 42;
}
