#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>
struct Point { long long x,y; };
using Shape = std::vector<Point>;
struct Edge { Point a,b; };
long long determinant(long long x,long long y,long long u,long long v) {
    return x*v-y*u;
}
long double signed_area(const Shape &p) {
    long long doubled=0;
    for (std::size_t i=0;i<p.size();++i) {
        auto a=p[i],c=p[(i+1)%p.size()];
        doubled += (a.x-c.x)*(a.y+c.y);
    }
    return static_cast<long double>(doubled)/2;
}
std::vector<long double> cover_area(const std::vector<Shape> &shapes) {
    std::vector<long double> cuts;
    std::vector<Edge> edges;
    for (const auto &p : shapes) {
        for (std::size_t i=0;i<p.size();++i) {
            cuts.push_back(static_cast<long double>(p[i].x));
            edges.push_back({p[i],p[(i+1)%p.size()]});
        }
    }
    for (std::size_t i=0;i<edges.size();++i) {
        auto a=edges[i].a,b=edges[i].b;
        for (std::size_t j=0;j<i;++j) {
            auto c=edges[j].a,d=edges[j].b;
            long long rx=b.x-a.x,ry=b.y-a.y,sx=d.x-c.x,sy=d.y-c.y;
            long long den=determinant(rx,ry,sx,sy);
            if (den==0) continue;
            long long t=determinant(c.x-a.x,c.y-a.y,sx,sy);
            long long u=determinant(c.x-a.x,c.y-a.y,rx,ry);
            if (den<0) { den=-den;t=-t;u=-u; }
            if (0<=t && t<=den && 0<=u && u<=den) {
                cuts.push_back(a.x+static_cast<long double>(rx)*t/den);
            }
        }
    }
    std::sort(cuts.begin(),cuts.end());
    cuts.erase(std::unique(cuts.begin(),cuts.end()),cuts.end());
    std::vector<long double> area(shapes.size() + 1);
    for (std::size_t slab=1;slab<cuts.size();++slab) {
        long double left=cuts[slab-1],right=cuts[slab],mid=(left+right)/2;
        if (!(left<mid && mid<right)) continue;
        std::vector<std::pair<long double,long double>> intervals;
        for (const auto &p : shapes) {
            std::vector<long double> heights;
            for (std::size_t i=0;i<p.size();++i) {
                auto a=p[i],c=p[(i+1)%p.size()];
                if (std::min(a.x,c.x)<mid && mid<std::max(a.x,c.x)) {
                    heights.push_back(a.y+(mid-a.x)*(c.y-a.y)/(c.x-a.x));
                }
            }
            std::sort(heights.begin(),heights.end());
            for (std::size_t i=0;i+1<heights.size();i+=2) intervals.emplace_back(heights[i],heights[i+1]);
        }
        std::vector<std::pair<long double, int>> events;
        for (auto [low, high] : intervals) {
            events.emplace_back(low, 1);
            events.emplace_back(high, -1);
        }
        std::sort(events.begin(), events.end());
        std::vector<long double> exact(shapes.size() + 1);
        int count = 0;
        for (std::size_t i = 1; i < events.size(); ++i) {
            count += events[i - 1].second;
            exact[count] += events[i].first - events[i - 1].first;
        }
        long double length = 0;
        for (int depth = int(shapes.size()); depth >= 1; --depth) {
            length += exact[depth];
            area[depth] += (right - left) * length;
        }
    }
    return area;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int k;
    std::cin>>k;
    std::vector<Shape> shapes(k);
    for (auto &p : shapes) {
        int n;std::cin>>n;p.resize(n);
        for (auto &a : p) std::cin>>a.x>>a.y;
#ifdef POLYGON_BOXES
        long long lx=p[0].x,rx=lx,ly=p[0].y,ry=ly;
        for (auto a : p) { lx=std::min(lx,a.x);rx=std::max(rx,a.x);ly=std::min(ly,a.y);ry=std::max(ry,a.y); }
        p={{lx,ly},{rx,ly},{rx,ry},{lx,ry}};
#endif
    }
    std::vector<long double> answer = cover_area(shapes);
#ifdef SUM_ONLY
    std::fill(answer.begin(), answer.end(), 0);
    for (const auto &p : shapes) answer[1] += signed_area(p);
#endif
#ifdef PAIRWISE_ONLY
    std::fill(answer.begin(), answer.end(), 0);
    for (const auto &p : shapes) answer[1] += signed_area(p);
    long double overlap = 0;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < i; ++j) {
            overlap += signed_area(shapes[i]) + signed_area(shapes[j]) - cover_area({shapes[i], shapes[j]})[1];
        }
    }
    if (k > 0) answer[1] -= overlap;
    if (k > 1) answer[2] = overlap;
#endif
#ifdef EXACT_ONLY
    for (int i = 1; i < k; ++i) answer[i] -= answer[i + 1];
#endif
#ifdef SUFFIX_SUM
    for (int i = k - 1; i >= 1; --i) answer[i] += answer[i + 1];
#endif
#ifdef UNION_ONLY
    for (int i = 2; i <= k; ++i) answer[i] = 0;
#endif
    std::cout << std::fixed << std::setprecision(18);
    for (int i = 1; i <= k; ++i) {
#ifdef INTEGER_AREA
        answer[i] = std::floor(answer[i]);
#endif
        std::cout << answer[i] << (i == k ? '\n' : ' ');
    }
    if (k == 0) std::cout << '\n';
}
