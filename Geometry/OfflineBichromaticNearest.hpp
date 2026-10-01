#pragma once

#include "Geometry/base.hpp"
#include "DataStructure/ZkwSegmentTree.hpp"

template<typename Dist, bool maintain_count>
struct BichromaticNearestResult;

template<typename Dist>
struct BichromaticNearestResult<Dist, false> {
    int id = -1;
    Dist dist2{};
};

template<typename Dist>
struct BichromaticNearestResult<Dist, true> {
    int id = -1;
    Dist dist2{};
    int count = 0;
};

template<
    typename Point, // |x|, |y| <= C
    bool maintain_count = false,
    typename MulT = typename Point::value_type, // 8C^2
    typename EventT = MulT, // 8C^3
    typename EventMulT = EventT, // 128C^5
    MulT eps = std::is_same_v<typename Point::value_type, MulT> ? MulT(Point::eps_val) : get_default_eps<MulT>(),
    EventT event_eps = std::is_same_v<MulT, EventT> ? EventT(eps) : get_default_eps<EventT>()
>
struct OfflineBichromaticNearest {
    using Result = BichromaticNearestResult<MulT, maintain_count>;

    struct Empty {};
    struct CountData { int count = 1; };
    using MaybeCount = std::conditional_t<maintain_count, CountData, Empty>;
    struct BaseSite {
        Point p;
        int original_id;
        [[no_unique_address]] MaybeCount data;
    };
    struct Site {
        MulT x, y;
        int id, yr;
        [[no_unique_address]] MaybeCount data;
    };
    struct Query {
        MulT x, y;
        int id;
    };
    struct Event {
        EventT num, den;
        int u, v, w;
    };
    struct EventGreater {
        bool operator()(const Event &a, const Event &b) const {
            if constexpr (std::is_floating_point_v<EventT>) {
                EventT x = a.num / a.den, y = b.num / b.den;
                if (x != y) return x > y;
            }
            else {
                EventMulT x = EventMulT(a.num) * EventMulT(b.den);
                EventMulT y = EventMulT(b.num) * EventMulT(a.den);
                if (x != y) return x > y;
            }
            return std::tie(a.v, a.u, a.w) > std::tie(b.v, b.u, b.w);
        }
    };
    struct ActiveNoCount {
        int first = -1, last = -1;
        friend ActiveNoCount operator+(const ActiveNoCount &a, const ActiveNoCount &b) {
            return {a.first != -1 ? a.first : b.first, b.last != -1 ? b.last : a.last};
        }
    };
    struct ActiveCount {
        int first = -1, last = -1;
        int count = 0;
        friend ActiveCount operator+(const ActiveCount &a, const ActiveCount &b) {
            return {a.first != -1 ? a.first : b.first, b.last != -1 ? b.last : a.last, a.count + b.count};
        }
    };

    using ActiveInfo = std::conditional_t<maintain_count, ActiveCount, ActiveNoCount>;

    std::vector<BaseSite> base;

    explicit OfflineBichromaticNearest(const std::vector<Point> &blue) {
        std::vector<int> ord(blue.size());
        std::iota(ord.begin(), ord.end(), 0);
        std::ranges::sort(ord, [&](int a, int b) {
            if (blue[a].x != blue[b].x) return blue[a].x < blue[b].x;
            if (blue[a].y != blue[b].y) return blue[a].y < blue[b].y;
            return a < b;
        });
        for (int id : ord) {
            if (base.empty() || base.back().p.x != blue[id].x || base.back().p.y != blue[id].y)
                base.push_back({blue[id], id, {}});
            else if constexpr (maintain_count)
                ++base.back().data.count;
        }
    }
    static MulT sqdist(MulT ax, MulT ay, MulT bx, MulT by) {
        MulT dx = ax - bx, dy = ay - by;
        return dx * dx + dy * dy;
    }
    static MulT sqdist(const Query &q, const Site &p) {
        return sqdist(q.x, q.y, p.x, p.y);
    }
    static MulT orient(const Site &a, const Site &b, const Site &c) {
        MulT x1 = b.x - a.x, y1 = b.y - a.y;
        MulT x2 = c.x - a.x, y2 = c.y - a.y;
        return x1 * y2 - y1 * x2;
    }
    static MulT norm2(const Site &p) {
        return p.x * p.x + p.y * p.y;
    }
    static int multiplicity(const Site &p) {
        if constexpr (maintain_count) return p.data.count;
        else return 1;
    }
    static ActiveInfo active_leaf(int v, int count) {
        if constexpr (maintain_count) return {v, v, count};
        else return {v, v};
    }
    static Event make_event(const Site &a, const Site &b, const Site &c) {
        MulT sa = norm2(a), sb = norm2(b), sc = norm2(c);
        EventT num = EventT(sb - sa) * EventT(c.y - a.y) - EventT(sc - sa) * EventT(b.y - a.y);
        EventT den = EventT(2) * EventT(orient(a, b, c));
        if (den < EventT(0)) num = -num, den = -den;
        return {num, den, a.id, b.id, c.id};
    }
    static bool event_before_x(const Event &e, MulT x, bool inclusive) {
        if constexpr (std::is_floating_point_v<EventT>) {
            int c = Geometry<EventT, event_eps>::cmp(e.num / e.den, EventT(x));
            return inclusive ? c <= 0 : c < 0;
        }
        else {
            EventMulT lhs = EventMulT(e.num);
            EventMulT rhs = EventMulT(x) * EventMulT(e.den);
            return inclusive ? lhs <= rhs : lhs < rhs;
        }
    }

    // inclusive_site_x = true  => site.x <= query.x
    // inclusive_site_x = false => site.x <  query.x
    std::vector<Result> sweep(const std::vector<Point> &red, int sx, bool inclusive_site_x) const {
        int n = int(base.size()), qn = int(red.size());

        std::vector<Site> p(n);
        for (int i = 0; i < n; ++i) {
            p[i].x = MulT(sx) * MulT(base[i].p.x);
            p[i].y = MulT(base[i].p.y);
            p[i].id = i;
            p[i].yr = -1;
            if constexpr (maintain_count) p[i].data.count = base[i].data.count;
        }

        std::vector<int> yo(n);
        std::iota(yo.begin(), yo.end(), 0);
        std::ranges::sort(yo, [&](int a, int b) {
            if (p[a].y != p[b].y) return p[a].y < p[b].y;
            return a < b;
        });
        int yn = 0;
        for (int i = 0; i < n; ++i) {
            if (i == 0 || p[yo[i]].y != p[yo[i - 1]].y) ++yn;
            p[yo[i]].yr = yn - 1;
        }

        std::vector<Query> q(qn);
        for (int i = 0; i < qn; ++i)
            q[i] = {MulT(sx) * MulT(red[i].x), MulT(red[i].y), i};

        std::vector<int> po(n), qo(qn);
        std::iota(po.begin(), po.end(), 0);
        std::iota(qo.begin(), qo.end(), 0);
        std::ranges::sort(po, [&](int a, int b) {
            if (p[a].x != p[b].x) return p[a].x < p[b].x;
            if (p[a].y != p[b].y) return p[a].y < p[b].y;
            return a < b;
        });
        std::ranges::sort(qo, [&](int a, int b) {
            if (q[a].x != q[b].x) return q[a].x < q[b].x;
            return a < b;
        });

        ZkwSegmentTree<ActiveInfo> tr(yn);
        std::priority_queue<Event, std::vector<Event>, EventGreater> pq;

        auto has = [](const ActiveInfo &x) { return x.first != -1; };
        auto at = [&](int r) { return tr.get(r).first; };
        auto active = [&](int v) { return v >= 0 && at(p[v].yr) == v; };
        auto prev = [&](int r) {
            if (r == 0) return -1;
            int x = tr.range_right_search(has, -1, r - 1);
            return x == -1 ? -1 : at(x);
        };
        auto next = [&](int r) {
            int x = tr.range_left_search(has, r + 1, yn);
            return x == yn ? -1 : at(x);
        };
        auto neigh = [&](int v) { return std::pair(prev(p[v].yr), next(p[v].yr)); };
        auto schedule = [&](int v) {
            if (!active(v)) return;
            auto [u, w] = neigh(v);
            if (u != -1 && w != -1 && Geometry<MulT, eps>::sign(orient(p[u], p[v], p[w])) < 0)
                pq.push(make_event(p[u], p[v], p[w]));
        };
        auto valid = [&](const Event &e) {
            if (!active(e.u) || !active(e.v) || !active(e.w)) return false;
            auto [u, w] = neigh(e.v);
            return u == e.u && w == e.w;
        };
        auto erase = [&](int v) {
            auto [u, w] = neigh(v);
            tr.modify(p[v].yr, ActiveInfo());
            schedule(u), schedule(w);
        };
        auto process = [&](MulT x, bool inclusive) {
            while (!pq.empty() && event_before_x(pq.top(), x, inclusive)) {
                Event e = pq.top();
                pq.pop();
                if (valid(e)) erase(e.v);
            }
        };
        auto insert = [&](int v) {
            int r = p[v].yr;
            int u = prev(r), w = next(r);
            tr.modify(r, active_leaf(v, multiplicity(p[v])));
            schedule(u), schedule(v), schedule(w);
        };

        auto nearest = [&](const Query &x) -> Result {
            if (!has(tr.all_prod())) return {};

            int r = tr.descend([&](const ActiveInfo &a, const ActiveInfo &b) {
                if (!has(a)) return false;
                if (!has(b)) return true;
                return Geometry<MulT, eps>::cmp(sqdist(x, p[a.last]), sqdist(x, p[b.first])) <= 0;
            });

            int v = at(r);
            MulT d = sqdist(x, p[v]);
            if constexpr (!maintain_count) return {base[p[v].id].original_id, d};
            else {
                auto left_tied = [&](const ActiveInfo &a) {
                    return has(a) && Geometry<MulT, eps>::cmp(sqdist(x, p[a.last]), d) == 0;
                };
                auto right_tied = [&](const ActiveInfo &a) {
                    return has(a) && Geometry<MulT, eps>::cmp(sqdist(x, p[a.first]), d) == 0;
                };
                int l = tr.range_left_search(left_tied, 0, r + 1);
                int rr = tr.range_right_search(right_tied, r - 1, yn - 1);
                int count = tr.range_prod(l, rr + 1).count;
                return {base[p[v].id].original_id, d, count};
            }
        };

        std::vector<Result> ans(qn);
        int i = 0, j = 0;
        auto insert_at = [&](MulT x) {
            while (i < n && p[po[i]].x == x) insert(po[i++]);
        };
        auto query_at = [&](MulT x) {
            while (j < qn && q[qo[j]].x == x) {
                ans[q[qo[j]].id] = nearest(q[qo[j]]);
                ++j;
            }
        };

        while (i < n || j < qn) {
            MulT x;
            if (i == n) x = q[qo[j]].x;
            else if (j == qn) x = p[po[i]].x;
            else x = std::min(p[po[i]].x, q[qo[j]].x);

            process(x, false);

            if constexpr (maintain_count) {
                if (inclusive_site_x)
                    insert_at(x), process(x, false), query_at(x);
                else
                    query_at(x), insert_at(x), process(x, false);
                process(x, true);
            }
            else {
                if (inclusive_site_x)
                    insert_at(x), process(x, true), query_at(x);
                else
                    query_at(x), insert_at(x), process(x, true);
            }
        }
        return ans;
    }

    std::vector<Result> query(const std::vector<Point> &red) const {
        std::vector<Result> ans(red.size());
        if (base.empty()) return ans;
        auto l = sweep(red, +1, true);
        auto r = sweep(red, -1, !maintain_count);
        for (int i = 0; i < int(red.size()); ++i) {
            if (l[i].id == -1) {
                ans[i] = r[i];
                continue;
            }
            if (r[i].id == -1) {
                ans[i] = l[i];
                continue;
            }
            int c = Geometry<MulT, eps>::cmp(l[i].dist2, r[i].dist2);
            if (c < 0) ans[i] = l[i];
            else if (c > 0) ans[i] = r[i];
            else if constexpr (maintain_count)
                ans[i] = {l[i].id, l[i].dist2, l[i].count + r[i].count};
            else
                ans[i] = l[i];
        }
        return ans;
    }
};
