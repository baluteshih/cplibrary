#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
struct Point { long long x, y; };
__int128 orientation(Point a, Point b, Point p) {
    return __int128(b.x-a.x)*(p.y-a.y)-__int128(b.y-a.y)*(p.x-a.x);
}
std::string classify(const std::vector<Point> &v, Point p) {
    int n = int(v.size()), winding = 0;
    if (n == 0) return "OUT";
#ifdef BBOX_ONLY
    long long lx=v[0].x,rx=lx,ly=v[0].y,ry=ly;
    for (auto a : v) { lx=std::min(lx,a.x); rx=std::max(rx,a.x); ly=std::min(ly,a.y); ry=std::max(ry,a.y); }
    if (p.x<lx || p.x>rx || p.y<ly || p.y>ry) return "OUT";
    return p.x==lx || p.x==rx || p.y==ly || p.y==ry ? "ON" : "IN";
#endif
    for (int i = 0; i < n; ++i) {
        auto a=v[i],b=v[(i+1)%n];
        __int128 side=orientation(a,b,p);
        if (side==0 && std::min(a.x,b.x)<=p.x && p.x<=std::max(a.x,b.x)
                && std::min(a.y,b.y)<=p.y && p.y<=std::max(a.y,b.y)) {
#ifdef BOUNDARY_INSIDE
            return "IN";
#elif defined(BOUNDARY_OUTSIDE)
            return "OUT";
#else
            return "ON";
#endif
        }
#ifdef DOUBLE_VERTEX
        if (a.y!=b.y && std::min(a.y,b.y)<=p.y && p.y<=std::max(a.y,b.y)
                && ((b.y>a.y && side>0) || (b.y<a.y && side<0))) winding ^= 1;
#else
        if (a.y<=p.y && p.y<b.y && side>0) ++winding;
        if (b.y<=p.y && p.y<a.y && side<0) --winding;
#endif
    }
#ifdef CCW_ONLY
    return winding>0 ? "IN" : "OUT";
#else
    return winding!=0 ? "IN" : "OUT";
#endif
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,q;
    std::cin>>n>>q;
    std::vector<Point> vertices(n);
    for (auto &p : vertices) std::cin>>p.x>>p.y;
    while (q-- != 0) {
        Point p; std::cin>>p.x>>p.y;
        std::cout<<classify(vertices,p)<<'\n';
    }
}
