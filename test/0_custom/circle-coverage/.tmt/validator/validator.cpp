#include "testlib.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 500, "n");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readInt(-10'000, 10'000, "x");
        inf.readSpace();
        inf.readInt(-10'000, 10'000, "y");
        inf.readSpace();
        inf.readInt(1, 10'000, "r");
        inf.readEoln();
    }
    inf.readEof();
    return 42;
}
