#pragma once

#include "Tree/Tree.hpp"

struct NullFunc {
    constexpr void operator()(auto&&...) const {}
};

/*
merge_func: void merge_func(int c, std::vector<std::vector<int>> groups);
    - c: the center, groups: subtrees with pre-order
pre_func: void pre_func(int u, int f);
    - u: current vertex, f: parent
    - the center would be called at first with pre_func(c, -1);
post_func: void post_func(int u, std::vector<int> child);
    - u: current vertex, child: child vertices
post_merge_func: void post_merge_func(int c, std::vector<int> cent_child);
    - c: the center, cent_child: c's center children 
return value: c_pa[u]: the centroid parent of u
*/

template<typename _Tree, typename F_Pre = NullFunc, typename F_Merge = NullFunc, typename F_Post = NullFunc, typename F_PMerge = NullFunc>
std::vector<int> centroid_divide_and_conquer(_Tree &tree, F_Pre pre_func = NullFunc{}, F_Merge merge_func = NullFunc{}, F_Post post_func = NullFunc{}, F_PMerge post_merge_func = NullFunc{}) {
    constexpr bool useMerge = !std::is_same_v<std::decay_t<decltype(merge_func)>, NullFunc>;
    constexpr bool usePre   = !std::is_same_v<std::decay_t<decltype(pre_func)>, NullFunc>;
    constexpr bool usePost  = !std::is_same_v<std::decay_t<decltype(post_func)>, NullFunc>;
    constexpr bool usePostMerge  = !std::is_same_v<std::decay_t<decltype(post_merge_func)>, NullFunc>;
    int n = tree.n();
    std::vector<int> done(n), sz(n), res(n);
    auto get_cent = [&](auto self, int u, int f, int &mx, int &c, int num) -> void {
        int mxsz = 0;
        sz[u] = 1;
        for (auto [v, eid] : tree[u])
            if (!done[v] && v != f) {
                self(self, v, u, mx, c, num);
                sz[u] += sz[v];
                mxsz = std::max(mxsz, sz[v]);
            }
        if (mx > std::max(mxsz, num - sz[u]))
            mx = std::max(mxsz, num - sz[u]), c = u;
    };
    auto dfs = [&](auto self, int u, int f, auto &g) -> void {
        if constexpr (useMerge) g.push_back(u);
        if constexpr (usePre) pre_func(u, f);
        std::conditional_t<usePost, std::vector<int>, typename _Tree::Empty> child;
        for (auto [v, eid] : tree[u])
            if (!done[v] && v != f) {
                self(self, v, u, g);
                if constexpr (usePost) child.push_back(v);
            }
        if constexpr (usePost) post_func(u, child);
    };
    auto cut = [&](auto self, int u, int num) -> int {
        int mx = n + 1, c = 0;
        get_cent(get_cent, u, -1, mx, c, num);
        done[c] = 1;
        std::conditional_t<useMerge, std::vector<std::vector<int>>, typename _Tree::Empty> groups;
        if constexpr (usePre) pre_func(c, -1);
        std::conditional_t<usePost, std::vector<int>, typename _Tree::Empty> child;
        for (auto [v, eid] : tree[c])
            if (!done[v]) {
                if constexpr (useMerge) {
                    groups.emplace_back();
                    groups.back().reserve(sz[v] > sz[c] ? num - sz[c] : sz[v]);
                    dfs(dfs, v, c, groups.back());
                }
                else dfs(dfs, v, c, groups);
                if constexpr (usePost) child.push_back(v);
            }
        if constexpr (usePost) post_func(c, child);
        if constexpr (useMerge) merge_func(c, groups);
        std::conditional_t<usePostMerge, std::vector<int>, typename _Tree::Empty> cent_child;
        for (auto [v, eid] : tree[c])
            if (!done[v]) {
                int ch;
                if (sz[v] > sz[c])
                    ch = self(self, v, num - sz[c]);
                else
                    ch = self(self, v, sz[v]);
                res[ch] = c;
                if constexpr (usePostMerge) cent_child.push_back(ch);
            }
        if constexpr (usePostMerge) post_merge_func(c, cent_child);
        done[c] = 0;
        return c;
    };
    res[cut(cut, 0, n)] = -1;
    return res;
}
