#pragma once

#include "Tree/Tree.hpp"
#include "Tree/centroid_divide_and_conquer.hpp"

template<typename Edge = void, typename Vertex = void>
class CentroidTree : public Tree<Edge, Vertex> {
public:
    std::vector<int> c_pa;
    using super = Tree<Edge, Vertex>;
    CentroidTree(int n): super(n) {} 
    CentroidTree(const super &tree): super(tree) {}
    template<typename F_Pre = NullFunc, typename F_Merge = NullFunc, typename F_Post = NullFunc>
    void build(F_Pre pre_func = NullFunc{}, F_Merge merge_func = NullFunc{}, F_Post post_func = NullFunc{}) {
        c_pa = centroid_divide_and_conquer(*this, pre_func, merge_func, post_func);
    }
    /*
    action(c, prev_c)
        - c: current centorid
        - prev_c: previous centroid, -1 if none
    */
    void climb(int u, auto action) const {
        int c = u, prev_c = -1;
        while (c != -1) {
            action(c, prev_c);
            prev_c = c;
            c = c_pa[c];
        }
    }
};
