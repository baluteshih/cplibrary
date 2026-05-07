#pragma once

#include "Geometry/base.hpp"
#include "DataStructure/BIT.hpp"

// cnt[i][j] = weight sum of points k s.t. strictly above ij, and i < k < j
// cnt2[i][j] = weight sum of points k s.t. strictly in ij
// preprocess space: O(n^2), time: O(n(n+m)log(n+m)), query time: O(1)
template<typename T, typename Point>
struct PointInAngle {
    std::vector<int> pl;
    std::vector<Point> pts;
    std::vector<std::vector<T>> cnt, cnt2;
    std::vector<T> cnt3;
    PointInAngle(const std::vector<Point> &_pts, const std::vector<T> weight, const std::vector<Point> &extra = {}, const std::vector<T> extra_weight = {}) : pl(_pts.size()), pts(_pts) {
        assert(_pts.size() == weight.size());
        assert(extra.size() == extra_weight.size());
        pts.insert(pts.end(), extra.begin(), extra.end());
        std::ranges::sort(pts), pts.erase(std::ranges::unique(pts).begin(), pts.end());
        int n = pts.size();
        cnt.resize(n, std::vector<T>(n));
        cnt2.resize(n, std::vector<T>(n));
        cnt3.resize(n);
        for (int i = 0; i < int(_pts.size()); ++i) {
            pl[i] = std::ranges::lower_bound(pts, _pts[i]) - pts.begin();
            cnt3[pl[i]] = cnt3[pl[i]] + weight[i];
        }
        for (int i = 0; i < int(extra.size()); ++i) {
            int idx = std::ranges::lower_bound(pts, extra[i]) - pts.begin();
            cnt3[idx] = cnt3[idx] + extra_weight[i];
        }
        for (int i = 0; i + 1 < n; ++i) {
            std::vector<int> cur(n - i - 1);
            std::iota(cur.begin(), cur.end(), i + 1);
            std::ranges::sort(cur, [&](int a, int b) {
                Point lft = pts[a] - pts[i];
                Point rgt = pts[b] - pts[i];
                if (sameDirection(lft, rgt)) return a < b;
                return polar(lft, rgt);
            });
            BIT<T> bit(n);
            for (int j = 0, k = 0, op = 0; j < int(cur.size()); j = k) {
                while (k < int(cur.size()) && sameDirection(pts[cur[j]] - pts[i], pts[cur[k]] - pts[i]))
                    bit.modify(cur[k], T() - cnt3[cur[k]]), ++k;
                while (op < j + int(cur.size()) && (op < k || side(pts[i], pts[cur[j]], pts[cur[op % int(cur.size())]]) > 0))
                    bit.modify(cur[op % int(cur.size())], cnt3[cur[op % int(cur.size())]]), ++op;
                T sum = T();
                for (int p = j; p < k; ++p) {
                    cnt[i][cur[p]] = bit.prefix(cur[p] - 1);
                    cnt2[i][cur[p]] = sum;
                    sum = sum + cnt3[cur[p]];
                }
            }
        }
    }
    // calculate weight sum of points strictly inside triangle i, j, k
    T calc_tri(int x, int y, int z) {
        std::tie(x, y, z) = std::make_tuple(pl[x], pl[y], pl[z]);
        if (x > y) std::swap(x, y);
        if (y > z) std::swap(y, z);
        if (x > y) std::swap(x, y);
        if (x == y || y == z) return T();
        int tmp = side(pts[x], pts[y], pts[z]);
        if (tmp == 0) return T();
        if (tmp < 0) return cnt[x][z] - cnt[x][y] - cnt[y][z] - cnt2[x][y] - cnt2[y][z] - cnt3[y];
        return cnt[x][y] + cnt[y][z] - cnt[x][z] - cnt2[x][z];
    }
};
