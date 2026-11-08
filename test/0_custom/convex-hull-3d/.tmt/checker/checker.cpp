#include "testlib.h"
#include "exact_geometry.hpp"

Wide read_integer(InStream &stream, bool official) {
    Wide result;
    if (!parse_integer(stream.readToken(), result)) quitf(official ? _fail : _wa, "Invalid or overflowing integer");
    return result;
}
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int count = ans.readInt(4, 2 * n - 4, "official face count");
    Wide volume = read_integer(ans, true);
    int actual = ouf.readInt(4, 2 * n - 4, "face count");
    if (actual != count) quitf(_wa, "Wrong maximal facet count");
    if (read_integer(ouf, false) != volume) quitf(_wa, "Wrong six-times volume");
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (read_integer(ans, true) != read_integer(ouf, false)) quitf(_wa, "Wrong plane coefficients, orientation, normalization or order");
        }
    }
    if (!ans.seekEof()) quitf(_fail, "Extra official output");
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "Exact volume and all canonical outward facets match");
}
