#include "testlib.h"
#include "validation_geometry.hpp"
int main(int argc,char **argv) {
    registerValidation(argc,argv);
    int k=inf.readInt(0,60,"k");inf.readEoln();
    int total=0;
    for (int j=0;j<k;++j) {
        int n=inf.readInt(3,200,"n");inf.readEoln();
        total+=n;ensuref(total<=200,"Total vertices exceeds 200");
        std::vector<Point> p(n);
        for (auto &a : p) {
            a.x=inf.readLong(-10000LL,10000LL,"x");inf.readSpace();
            a.y=inf.readLong(-10000LL,10000LL,"y");inf.readEoln();
        }
        ensuref(simple_polygon(p),"Polygon is not simple and nondegenerate");
        __int128 area=0;
        for (int i=0;i<n;++i) area+=__int128(p[i].x)*p[(i+1)%n].y-__int128(p[i].y)*p[(i+1)%n].x;
        ensuref(area>0,"Polygon must be counterclockwise");
    }
    inf.readEof();return 42;
}
