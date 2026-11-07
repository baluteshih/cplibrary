#include "testlib.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(0, 200'000, "n");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readInt(-100'000'000, 100'000'000, "x");
        inf.readSpace();
        inf.readInt(-100'000'000, 100'000'000, "y");
        inf.readEoln();
    }
    inf.readEof();
    return 42;
}
