#include "testlib.h"
#include <string>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, 200000, "n"); inf.readSpace();
    int q = inf.readInt(1, 200000, "q"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readLong(-100000000LL, 100000000LL, "x"); inf.readSpace();
        inf.readLong(-100000000LL, 100000000LL, "y"); inf.readEoln();
    }
    int areas = 0;
    for (int j = 0; j < q; ++j) {
        std::string op = inf.readToken("[VESA]", "operation");
        if (op == "A") ++areas;
        else {
            inf.readSpace(); inf.readLong(-1000000000LL, 1000000000LL, "index");
            if (op == "S") {
                inf.readSpace(); inf.readLong(-100000000LL, 100000000LL, "x");
                inf.readSpace(); inf.readLong(-100000000LL, 100000000LL, "y");
            }
        }
        inf.readEoln();
    }
    ensuref(areas > 0 && 1LL * areas * n <= 2000000, "Invalid area-query budget");
    inf.readEof();
    return 42;
}
