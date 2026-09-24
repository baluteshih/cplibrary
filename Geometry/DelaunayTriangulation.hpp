#pragma once

#include "Geometry/base.hpp"
#include "Geometry/centers.hpp"

template <typename Point, typename MulT = typename Point::value_type, MulT eps = std::is_same_v<typename Point::value_type, MulT> ? Point::eps_val : get_default_eps<MulT>()>
struct DelaunayTriangulation {
    using T = typename Point::value_type;
    struct Edge {
        int orig, dest;
        int nxt, prev;
    };
    std::vector<Point> pts;
    std::vector<Edge> edg;
    std::vector<int> oidx;
    int make_edge(int u, int v) {
        int e1 = edg.size(); edg.push_back({u, v, e1, e1});
        int e2 = edg.size(); edg.push_back({v, u, e2, e2});
        return e1;
    }
    void splice(int a, int b) {
        int a_nxt = edg[a].nxt, b_nxt = edg[b].nxt;
        edg[a].nxt = b_nxt; edg[b_nxt].prev = a;
        edg[b].nxt = a_nxt; edg[a_nxt].prev = b;
    }
    int sym(int e)   const { return e ^ 1; }
    int orig(int e)  const { return edg[e].orig; }
    int dest(int e)  const { return edg[e].dest; }
    int onxt(int e)  const { return edg[e].nxt; }
    int oprev(int e) const { return edg[e].prev; }
    int lnext(int e) const { return oprev(sym(e)); }
    int rprev(int e) const { return onxt(sym(e)); }
    int connect(int a, int b) {
        int e = make_edge(dest(a), orig(b));
        splice(e, lnext(a));
        splice(sym(e), b);
        return e;
    }
    void delete_edge(int e) {
        splice(e, oprev(e));
        splice(sym(e), oprev(sym(e)));
        edg[e].orig = -1;
        edg[sym(e)].orig = -1;
    }
    bool ccw(int a, int b, int c) const {
        return side(pts[a], pts[b], pts[c]) == 1;
    }
    bool in_circle(int a, int b, int c, int p) const {
        return pointInCircumCircle<Point, MulT, eps>(pts[a], pts[b], pts[c], pts[p]) == 1; 
    }
    bool right_of(int x, int e) const { return ccw(x, dest(e), orig(e)); }
    bool left_of(int x, int e)  const { return ccw(x, orig(e), dest(e)); }
    std::pair<int, int> solve(int l, int r) {
        if (l + 1 == r) {
            int a = make_edge(l, r);
            return {a, sym(a)};
        }
        if (l + 2 == r) {
            int a = make_edge(l, l + 1);
            int b = make_edge(l + 1, r);
            splice(sym(a), b);
            if (ccw(l, l + 1, r)) {
                connect(b, a);
                return {a, sym(b)};
            }
            else if (ccw(l, r, l + 1)) {
                int c = connect(b, a);
                return {sym(c), c};
            }
            else return {a, sym(b)};
        }
        int mid = l + (r - l) / 2;
        auto [ldo, ldi] = solve(l, mid);
        auto [rdi, rdo] = solve(mid + 1, r);
        while (true) {
            if (left_of(orig(rdi), ldi)) ldi = lnext(ldi);
            else if (right_of(orig(ldi), rdi)) rdi = rprev(rdi);
            else break;
        }
        int basel = connect(sym(rdi), ldi);
        if (orig(ldi) == orig(ldo)) ldo = sym(basel);
        if (orig(rdi) == orig(rdo)) rdo = basel;
        while (true) {
            int lcand = rprev(basel);
            bool lvalid = right_of(dest(lcand), basel);
            if (lvalid) {
                while (right_of(dest(onxt(lcand)), basel) && in_circle(dest(basel), orig(basel), dest(lcand), dest(onxt(lcand)))) {
                    int t = onxt(lcand);
                    delete_edge(lcand);
                    lcand = t;
                }
            }
            int rcand = oprev(basel);
            bool rvalid = right_of(dest(rcand), basel);
            if (rvalid) {
                while (right_of(dest(oprev(rcand)), basel) && in_circle(dest(basel), orig(basel), dest(rcand), dest(oprev(rcand)))) {
                    int t = oprev(rcand);
                    delete_edge(rcand);
                    rcand = t;
                }
            }
            if (!lvalid && !rvalid) break;
            if (!lvalid || (rvalid && in_circle(dest(lcand), orig(lcand), orig(basel), dest(rcand))))
                basel = connect(rcand, sym(basel));
            else
                basel = connect(sym(basel), sym(lcand));
        }
        return {ldo, rdo};
    }
    DelaunayTriangulation(std::vector<Point> input_pts) {
        oidx.resize(input_pts.size());
        std::iota(oidx.begin(), oidx.end(), 0);
        std::sort(oidx.begin(), oidx.end(), [&](int a, int b) {
            if (input_pts[a] != input_pts[b]) return input_pts[a] < input_pts[b];
            return a < b;
        });
        pts.resize(std::ranges::unique(oidx, [&](int a, int b) {
            return input_pts[a] == input_pts[b]; 
        }).begin() - oidx.begin());
        for (int i = 0; i < int(pts.size()); ++i) pts[i] = input_pts[oidx[i]];
        edg.clear();
        edg.reserve(pts.size() * 12);
        if (pts.size() >= 2) solve(0, pts.size() - 1);
    }
    std::vector<std::pair<int, int>> get_edges() {
        std::vector<std::pair<int, int>> res;
        for (int i = 0; i < int(edg.size()); i += 2)
            if (edg[i].orig != -1)
                res.emplace_back(oidx[orig(i)], oidx[dest(i)]);
        return res;
    }
};
