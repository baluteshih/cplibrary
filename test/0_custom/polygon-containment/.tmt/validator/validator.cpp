#include "testlib.h"
#include "validation_geometry.hpp"
int main(int argc, char **argv) {
    registerValidation(argc,argv);
    int n=inf.readInt(0,10000,"n"); inf.readSpace();
    int q=inf.readInt(1,200000,"q"); inf.readEoln();
    ensuref(1LL*std::max(n,1)*q<=2000000,"Query work exceeds budget");
    std::vector<Point> p(n);
    for (auto &a : p) {
        a.x=inf.readLong(-100000000LL,100000000LL,"x"); inf.readSpace();
        a.y=inf.readLong(-100000000LL,100000000LL,"y"); inf.readEoln();
    }
    if (n==2) ensuref(p[0].x!=p[1].x || p[0].y!=p[1].y,"Segment endpoints coincide");
    if (n>=3) ensuref(simple_polygon(p),"Not a nondegenerate simple polygon");
    for (int i=0;i<q;++i) {
        inf.readLong(-100000000LL,100000000LL,"u"); inf.readSpace();
        inf.readLong(-100000000LL,100000000LL,"v"); inf.readEoln();
    }
    inf.readEof();
    return 42;
}
