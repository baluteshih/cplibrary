#pragma once

#include "Geometry/base.hpp"
#include "Geometry/convex.hpp"

/* The two convex should not intersect
return a pair (i, j) such that P[i], Q[j] is the tangent line such that all points located in their left side
call outerTangentBetweenConvex(Q, P) to get another tangent line 

reference: David Kirkpatrick and Jack Snoeyink. 1994. Computing Common Tangents Without a Separating Line. Technical Report. University of British Columbia, CAN.
*/
template <typename polygon>
std::pair<int, int> outerTangentBetweenConvex(const polygon &P, const polygon &Q) {
    using Point = polygon::Point;
    assert(!P.empty() && !Q.empty());
    if (P.size() == 1 && Q.size() == 1) return std::make_pair(0, 0);
    if (P.size() == 1) return std::make_pair(0, tangentLineToConvex(P[0], Q).first); 
    if (Q.size() == 1) return std::make_pair(tangentLineToConvex(Q[0], P).second, 0);
    struct Info {
        int n, dir, st, end, tent;
        bool wrap;
        Point tang_p1, tang_p2;
        bool done() { return (end - tent) == dir; }
        bool refined() { return st != tent; }
    };
    auto refine = [&](const auto &_P, Info &Pinfo, const auto &_Q, Info &Qinfo) {
        int mid = Pinfo.tent + (Pinfo.end - Pinfo.tent) / 2;
        Point pm = _P.at(mid), pm1 = _P.at(mid + Pinfo.dir);
        if (Qinfo.refined() && side(Qinfo.tang_p1, Qinfo.tang_p2, pm) != 1) {
            Point qt = _Q.at(Qinfo.tent);
            if ((Qinfo.dir == 1) != (side(_P[0], qt, pm) == 1))
                Qinfo.st = Qinfo.tent;
            else {
                Qinfo.end = Qinfo.tent;
                Qinfo.tent = Qinfo.st;
                Pinfo.st = Pinfo.tent;
            }
        }
        Point qend = _Q.at(Qinfo.end), qt = _Q.at(Qinfo.tent);
        bool left_base = side(_Q[0], pm, _P[0]) == -1;
        int action = 2;
        if (Pinfo.wrap && (left_base != (mid > Pinfo.n)))
            action = !left_base;
        else if (side(pm, pm1, _Q[0]) != Pinfo.dir)
            action = left_base;
        else if (side(pm, pm1, qend) != Pinfo.dir)
            action = side(_Q[0], pm, qend) == 1;
        else if (Qinfo.refined() && side(pm, pm1, qt) != Pinfo.dir)
            action = side(_Q[0], pm, qt) == 1;

        if (action == 2) {
            Pinfo.tent = mid;
            Pinfo.tang_p1 = pm;
            Pinfo.tang_p2 = pm1;
            if (Pinfo.dir == -1)
                std::swap(Pinfo.tang_p1, Pinfo.tang_p2);
        }
        else if ((Pinfo.dir == 1) != (action == 1))
            Pinfo.st = Pinfo.tent = mid;
        else
            Pinfo.end = mid;
    };
    Info Pinfo{int(P.size()), 1, 0, int(P.size()), 0, false, P[0], P[1]};
    Info Qinfo{int(Q.size()), -1, int(Q.size()), 0, int(Q.size()), false, Q.back(), Q[0]};

    if (side(P[0], P[1], Q[0]) == 1) {
        Pinfo.wrap = true;
        Pinfo.tent = P.size();
        Pinfo.end += P.size();
    }
    if (side(Q.back(), Q[0], P[0]) == 1) {
        Qinfo.wrap = true;
        Qinfo.st += Q.size();
    }

    while (!Pinfo.done() || !Qinfo.done()) {
        if (!Pinfo.done()) refine(P, Pinfo, Q, Qinfo);
        if (!Qinfo.done()) refine(Q, Qinfo, P, Pinfo);
    }

    return std::make_pair(Pinfo.end % Pinfo.n, Qinfo.end % Qinfo.n);
}
