#pragma once

#include "DataStructure/DefaultAllocator.hpp"
#include "Algebra/ValidOperation.hpp"

#ifndef KDTREE_ALPHA
    #define KDTREE_ALPHA 0.75
#endif

enum class KDIntersect { OUTSIDE = 0, INSIDE = 1, PARTIAL = 2 };

template<size_t K,
         typename Coord = long long,
         typename Value = void,
         typename Tag = void,
         template<typename> class Allocator = DefaultAllocator
>
class KDTree {
    static constexpr bool hasValue = !std::is_void_v<Value>;
    static constexpr bool hasTag = !std::is_void_v<Tag>;
    static constexpr bool hasTagToValue = Addable<Value, Tag>;
    struct Empty {};
    template <bool Condition, typename T>
    static auto get_default() {
        if constexpr (Condition) return T();
        else return Empty{};
    }
    static_assert(!hasValue || Addable<Value, Value>);
    static_assert(!hasTag || Addable<Tag, Tag>);
public:
    using Point = std::array<Coord, K>;

    struct node {
        node *l = nullptr, *r = nullptr;
        Point pt;
        Point mn, mx;
        int sz = 1;
        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty> org = get_default<hasValue, Value>();
        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty> val = get_default<hasValue, Value>();
        [[no_unique_address]] std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();

        node() = default;
        node(const Point &p) requires (!hasValue) : pt(p), mn(p), mx(p) {}
        node(const Point &p, const Value &v) requires (hasValue) : pt(p), mn(p), mx(p), org(v), val(v) {}

        void up() {
            sz = 1;
            mn = mx = pt;
            if constexpr (hasValue) val = org;

            if (l) {
                sz += l->sz;
                for (size_t i = 0; i < K; ++i) {
                    mn[i] = std::min(mn[i], l->mn[i]);
                    mx[i] = std::max(mx[i], l->mx[i]);
                }
                if constexpr (hasValue) val = val + l->val;
            }
            if (r) {
                sz += r->sz;
                for (size_t i = 0; i < K; ++i) {
                    mn[i] = std::min(mn[i], r->mn[i]);
                    mx[i] = std::max(mx[i], r->mx[i]);
                }
                if constexpr (hasValue) val = val + r->val;
            }
        }
        void give_tag(const auto &tag) requires (hasTag) {
            if constexpr (hasTagToValue) {
                org = org + tag;
                val = val + tag; 
            }
            lazy = lazy + tag;
        }
        void down() requires (hasTag) {
            bool need_tag = false;
            if constexpr (std::equality_comparable<Tag>) need_tag = !(lazy == Tag());
            else need_tag = true;
            
            if (!need_tag) return;
            
            if (l) l->give_tag(lazy);
            if (r) r->give_tag(lazy);
            lazy = Tag();
        }
        friend std::ostream& operator<<(std::ostream& os, const node &v) {
            os << "(";
            for(size_t i=0; i<K; ++i) os << v.pt[i] << (i+1==K ? "" : ", ");
            os << ")";
            if constexpr (hasValue) os << " {org = " << v.org << ", val = " << v.val << "}";
            return os;
        }
    };
    using NodeAlloc = Allocator<node>;
    node *root = nullptr;
private:
    static void free(node *&ptr) {
        if (ptr == nullptr) return;
        free(ptr->l);
        free(ptr->r);
        NodeAlloc::deallocate(ptr);
        ptr = nullptr;
    }
    static void flatten(node *u, std::vector<node*>& res) {
        if (!u) return;
        if constexpr (hasTag) u->down();
        flatten(u->l, res);
        res.push_back(u);
        flatten(u->r, res);
    }
    static bool cmp_less(node* a, node* b, int dim) {
        if (a->pt[dim] != b->pt[dim]) return a->pt[dim] < b->pt[dim];
        return std::less<node*>{}(a, b);
    }
    static node* build_tree(std::vector<node*>& nodes, int l, int r, int dim) {
        if (l > r) return nullptr;
        int mid = l + (r - l) / 2;
        std::nth_element(nodes.begin() + l, nodes.begin() + mid, nodes.begin() + r + 1, [dim](node* a, node* b) {
            return cmp_less(a, b, dim);
        });
        node *u = nodes[mid];
        u->l = build_tree(nodes, l, mid - 1, (dim + 1) % K);
        u->r = build_tree(nodes, mid + 1, r, (dim + 1) % K);
        u->up();
        return u;
    }
    static void insert_impl(node*& u, node* target, int dim, node**& rebuild_ptr, int& rebuild_dim) {
        if (!u) {
            u = target;
            u->up();
            return;
        }
        if constexpr (hasTag) u->down();
        if (cmp_less(target, u, dim))
            insert_impl(u->l, target, (dim + 1) % K, rebuild_ptr, rebuild_dim);
        else
            insert_impl(u->r, target, (dim + 1) % K, rebuild_ptr, rebuild_dim);
        u->up();
        int max_sz = std::max(u->l ? u->l->sz : 0, u->r ? u->r->sz : 0);
        if (max_sz > u->sz * KDTREE_ALPHA) {
            rebuild_ptr = &u;
            rebuild_dim = dim;
        }
    }
    static Value query_range_impl(node *u, const auto& condition) requires (hasValue) {
        if (!u) return Value();
        KDIntersect state = condition(u->mn, u->mx);
        if (state == KDIntersect::OUTSIDE) return Value();
        if (state == KDIntersect::INSIDE) return u->val;
        if constexpr (hasTag) u->down();
        Value res = Value();
        if (condition(u->pt, u->pt) != KDIntersect::OUTSIDE)
            res = res + u->org;
        if (u->l) res = res + query_range_impl(u->l, condition);
        if (u->r) res = res + query_range_impl(u->r, condition);
        return res;
    }
    static void transform_range_impl(node *u, const auto& condition, const Tag& tag) requires (hasTag) {
        if (!u) return;
        KDIntersect state = condition(u->mn, u->mx);
        if (state == KDIntersect::OUTSIDE) return;
        if (state == KDIntersect::INSIDE) {
            u->give_tag(tag);
            return;
        }
        u->down();
        if (condition(u->pt, u->pt) != KDIntersect::OUTSIDE) {
            if constexpr (hasTagToValue)
                u->org = u->org + tag;
        }
        transform_range_impl(u->l, condition, tag);
        transform_range_impl(u->r, condition, tag);
        u->up();
    }
    static bool update_node_impl(node* u, node* target, const auto& op, int dim) requires (hasValue) {
        if (!u) return false;
        for (size_t i = 0; i < K; ++i)
            if (target->pt[i] < u->mn[i] || target->pt[i] > u->mx[i]) return false;
        if constexpr (hasTag) u->down();
        if (u == target) {
            op(u->org); 
            u->up();
            return true;
        }
        bool updated = false;
        if (cmp_less(target, u, dim))
            updated = update_node_impl(u->l, target, op, (dim + 1) % K);
        else
            updated = update_node_impl(u->r, target, op, (dim + 1) % K);
        if (updated) u->up();
        return updated;
    }
    template <typename DistCalc>
    static void nearest_impl(node *u, const Point& target, int dim, DistCalc& calc, Coord& best_d, node*& best_u) {
        if (!u) return;
        Coord d = calc.dist(u->pt, target);
        if (d < best_d) {
            best_d = d;
            best_u = u;
        }
        Coord dl = u->l ? calc.min_dist(target, u->l->mn, u->l->mx) : std::numeric_limits<Coord>::max();
        Coord dr = u->r ? calc.min_dist(target, u->r->mn, u->r->mx) : std::numeric_limits<Coord>::max();
        if (dl < dr) {
            if (dl < best_d) nearest_impl(u->l, target, (dim + 1) % K, calc, best_d, best_u);
            if (dr < best_d) nearest_impl(u->r, target, (dim + 1) % K, calc, best_d, best_u);
        }
        else {
            if (dr < best_d) nearest_impl(u->r, target, (dim + 1) % K, calc, best_d, best_u);
            if (dl < best_d) nearest_impl(u->l, target, (dim + 1) % K, calc, best_d, best_u);
        }
    }
public:
    KDTree() = default;
    std::vector<node*> build(const std::vector<Point>& pts) requires (!hasValue) {
        std::vector<node*> handles;
        handles.reserve(pts.size());
        for (const auto& p : pts) handles.push_back(NodeAlloc::allocate(p));
        std::vector<node*> build_nodes = handles;
        if (!build_nodes.empty()) root = build_tree(build_nodes, 0, build_nodes.size() - 1, 0);
        else root = nullptr;
        return handles;
    }
    std::vector<node*> build(const std::vector<std::pair<Point, Value>>& pts) requires (hasValue) {
        std::vector<node*> handles;
        handles.reserve(pts.size());
        for (const auto& [p, v] : pts) handles.push_back(NodeAlloc::allocate(p, v));
        std::vector<node*> build_nodes = handles;
        if (!build_nodes.empty()) root = build_tree(build_nodes, 0, build_nodes.size() - 1, 0);
        else root = nullptr;
        return handles;
    }
    void destruct() { free(root); }
    int size() const { return root ? root->sz : 0; }
    node* insert(const Point &pt) requires (!hasValue) {
        node* u = NodeAlloc::allocate(pt);
        insert_target(u);
        return u;
    }
    node* insert(const Point &pt, const Value &v) requires (hasValue) {
        node* u = NodeAlloc::allocate(pt, v);
        insert_target(u);
        return u;
    }
    void insert_target(node* target) {
        node** rebuild_ptr = nullptr;
        int rebuild_dim = 0;
        insert_impl(root, target, 0, rebuild_ptr, rebuild_dim);
        if (rebuild_ptr != nullptr) {
            std::vector<node*> nodes;
            nodes.reserve((*rebuild_ptr)->sz);
            flatten(*rebuild_ptr, nodes);
            *rebuild_ptr = build_tree(nodes, 0, nodes.size() - 1, rebuild_dim);
        }
    }
    bool update_node(node* target, const auto& op) requires (hasValue) {
        if (!target) return false;
        return update_node_impl(root, target, op, 0);
    }
    Value query_range(const auto& condition) requires (hasValue) {
        return query_range_impl(root, condition);
    }
    void transform_range(const auto& condition, const Tag& tag) requires (hasTag) {
        transform_range_impl(root, condition, tag);
    }
    struct EuclideanDistCalc {
        Coord dist(const Point& a, const Point& b) {
            Coord res = Coord();
            for (int i = 0; i < K; ++i) res += (a[i] - b[i]) * (a[i] - b[i]);
            return res;
        }
        Coord min_dist(const Point& p, const Point& mn, const Point& mx) {
            Coord res = Coord();
            for (int i = 0; i < K; ++i) {
                Coord d = std::max<Coord>(0, std::max(mn[i] - p[i], p[i] - mx[i]));
                res += d * d;
            }
            return res;
        }
    };
    template<typename DistCalc = EuclideanDistCalc>
    std::pair<Coord, Point> nearest_neighbor(const Point& target, DistCalc calc) {
        Coord best_d = std::numeric_limits<Coord>::max();
        node* best_u = nullptr;
        nearest_impl(root, target, 0, calc, best_d, best_u);
        return {best_d, best_u->pt};
    }
    struct Rect {
        Coord x1, y1, x2, y2;
        Rect(Coord _x1, Coord _y1, Coord _x2, Coord _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {
            static_assert(K == 2);
        }
        KDIntersect operator()(const Point& mn, const Point& mx) const {
            if (mn[0] > x2 || mx[0] < x1 || mn[1] > y2 || mx[1] < y1) return KDIntersect::OUTSIDE;
            if (mn[0] >= x1 && mx[0] <= x2 && mn[1] >= y1 && mx[1] <= y2) return KDIntersect::INSIDE;
            return KDIntersect::PARTIAL;
        }
    };
    struct Box {
        Point b_mn, b_mx;
        Box(Point _mn, Point _mx) : b_mn(_mn), b_mx(_mx) {}
        KDIntersect operator()(const Point& mn, const Point& mx) const {
            bool inside = true;
            for (size_t i = 0; i < K; ++i) {
                if (mn[i] > b_mx[i] || mx[i] < b_mn[i]) return KDIntersect::OUTSIDE;
                if (mn[i] < b_mn[i] || mx[i] > b_mx[i]) inside = false;
            }
            return inside ? KDIntersect::INSIDE : KDIntersect::PARTIAL;
        }
    };
};
