---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/DefaultAllocator.hpp
    title: Default Allocator
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp
    title: test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/KDTree.hpp\"\n\n#line 2 \"DataStructure/DefaultAllocator.hpp\"\
    \n\ntemplate<typename T>\nstruct DefaultAllocator {\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        return new T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { delete p; }\n};\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate <typename A, typename B>\nconcept Addable = !std::is_void_v<A> &&\
    \ !std::is_void_v<B> && requires(A a, B b) { a + b; };\n\ntemplate <typename A,\
    \ typename B>\nconcept Subtractable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a - b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a * b; };\n#line 5 \"DataStructure/KDTree.hpp\"\n\n#ifndef KDTREE_ALPHA\n\
    \    #define KDTREE_ALPHA 0.75\n#endif\n\nenum class KDIntersect { OUTSIDE = 0,\
    \ INSIDE = 1, PARTIAL = 2 };\n\ntemplate<size_t K,\n         typename Coord =\
    \ long long,\n         typename Value = void,\n         typename Tag = void,\n\
    \         template<typename> class Allocator = DefaultAllocator\n>\nclass KDTree\
    \ {\n    static constexpr bool hasValue = !std::is_void_v<Value>;\n    static\
    \ constexpr bool hasTag = !std::is_void_v<Tag>;\n    static constexpr bool hasTagToValue\
    \ = Addable<Value, Tag>;\n    struct Empty {};\n    template <bool Condition,\
    \ typename T>\n    static auto get_default() {\n        if constexpr (Condition)\
    \ return T();\n        else return Empty{};\n    }\n    static_assert(!hasValue\
    \ || Addable<Value, Value>);\n    static_assert(!hasTag || Addable<Tag, Tag>);\n\
    public:\n    using Point = std::array<Coord, K>;\n\n    struct node {\n      \
    \  node *l = nullptr, *r = nullptr;\n        Point pt;\n        Point mn, mx;\n\
    \        int sz = 1;\n        [[no_unique_address]] std::conditional_t<hasValue,\
    \ Value, Empty> org = get_default<hasValue, Value>();\n        [[no_unique_address]]\
    \ std::conditional_t<hasValue, Value, Empty> val = get_default<hasValue, Value>();\n\
    \        [[no_unique_address]] std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag,\
    \ Tag>();\n\n        node() = default;\n        node(const Point &p) requires\
    \ (!hasValue) : pt(p), mn(p), mx(p) {}\n        node(const Point &p, const Value\
    \ &v) requires (hasValue) : pt(p), mn(p), mx(p), org(v), val(v) {}\n\n       \
    \ void up() {\n            sz = 1;\n            mn = mx = pt;\n            if\
    \ constexpr (hasValue) val = org;\n\n            if (l) {\n                sz\
    \ += l->sz;\n                for (size_t i = 0; i < K; ++i) {\n              \
    \      mn[i] = std::min(mn[i], l->mn[i]);\n                    mx[i] = std::max(mx[i],\
    \ l->mx[i]);\n                }\n                if constexpr (hasValue) val =\
    \ val + l->val;\n            }\n            if (r) {\n                sz += r->sz;\n\
    \                for (size_t i = 0; i < K; ++i) {\n                    mn[i] =\
    \ std::min(mn[i], r->mn[i]);\n                    mx[i] = std::max(mx[i], r->mx[i]);\n\
    \                }\n                if constexpr (hasValue) val = val + r->val;\n\
    \            }\n        }\n        void give_tag(const auto &tag) requires (hasTag)\
    \ {\n            if constexpr (hasTagToValue) {\n                org = org + tag;\n\
    \                val = val + tag; \n            }\n            lazy = lazy + tag;\n\
    \        }\n        void down() requires (hasTag) {\n            bool need_tag\
    \ = false;\n            if constexpr (std::equality_comparable<Tag>) need_tag\
    \ = !(lazy == Tag());\n            else need_tag = true;\n            \n     \
    \       if (!need_tag) return;\n            \n            if (l) l->give_tag(lazy);\n\
    \            if (r) r->give_tag(lazy);\n            lazy = Tag();\n        }\n\
    \        friend std::ostream& operator<<(std::ostream& os, const node &v) {\n\
    \            os << \"(\";\n            for(size_t i=0; i<K; ++i) os << v.pt[i]\
    \ << (i+1==K ? \"\" : \", \");\n            os << \")\";\n            if constexpr\
    \ (hasValue) os << \" {org = \" << v.org << \", val = \" << v.val << \"}\";\n\
    \            return os;\n        }\n    };\n    using NodeAlloc = Allocator<node>;\n\
    \    node *root = nullptr;\nprivate:\n    static void free(node *&ptr) {\n   \
    \     if (ptr == nullptr) return;\n        free(ptr->l);\n        free(ptr->r);\n\
    \        NodeAlloc::deallocate(ptr);\n        ptr = nullptr;\n    }\n    static\
    \ void flatten(node *u, std::vector<node*>& res) {\n        if (!u) return;\n\
    \        if constexpr (hasTag) u->down();\n        flatten(u->l, res);\n     \
    \   res.push_back(u);\n        flatten(u->r, res);\n    }\n    static bool cmp_less(node*\
    \ a, node* b, int dim) {\n        if (a->pt[dim] != b->pt[dim]) return a->pt[dim]\
    \ < b->pt[dim];\n        return std::less<node*>{}(a, b);\n    }\n    static node*\
    \ build_tree(std::vector<node*>& nodes, int l, int r, int dim) {\n        if (l\
    \ > r) return nullptr;\n        int mid = l + (r - l) / 2;\n        std::nth_element(nodes.begin()\
    \ + l, nodes.begin() + mid, nodes.begin() + r + 1, [dim](node* a, node* b) {\n\
    \            return cmp_less(a, b, dim);\n        });\n        node *u = nodes[mid];\n\
    \        u->l = build_tree(nodes, l, mid - 1, (dim + 1) % K);\n        u->r =\
    \ build_tree(nodes, mid + 1, r, (dim + 1) % K);\n        u->up();\n        return\
    \ u;\n    }\n    static void insert_impl(node*& u, node* target, int dim, node**&\
    \ rebuild_ptr, int& rebuild_dim) {\n        if (!u) {\n            u = target;\n\
    \            u->up();\n            return;\n        }\n        if constexpr (hasTag)\
    \ u->down();\n        if (cmp_less(target, u, dim))\n            insert_impl(u->l,\
    \ target, (dim + 1) % K, rebuild_ptr, rebuild_dim);\n        else\n          \
    \  insert_impl(u->r, target, (dim + 1) % K, rebuild_ptr, rebuild_dim);\n     \
    \   u->up();\n        int max_sz = std::max(u->l ? u->l->sz : 0, u->r ? u->r->sz\
    \ : 0);\n        if (max_sz > u->sz * KDTREE_ALPHA) {\n            rebuild_ptr\
    \ = &u;\n            rebuild_dim = dim;\n        }\n    }\n    static Value query_range_impl(node\
    \ *u, const auto& condition) requires (hasValue) {\n        if (!u) return Value();\n\
    \        KDIntersect state = condition(u->mn, u->mx);\n        if (state == KDIntersect::OUTSIDE)\
    \ return Value();\n        if (state == KDIntersect::INSIDE) return u->val;\n\
    \        if constexpr (hasTag) u->down();\n        Value res = Value();\n    \
    \    if (condition(u->pt, u->pt) != KDIntersect::OUTSIDE)\n            res = res\
    \ + u->org;\n        if (u->l) res = res + query_range_impl(u->l, condition);\n\
    \        if (u->r) res = res + query_range_impl(u->r, condition);\n        return\
    \ res;\n    }\n    static void transform_range_impl(node *u, const auto& condition,\
    \ const Tag& tag) requires (hasTag) {\n        if (!u) return;\n        KDIntersect\
    \ state = condition(u->mn, u->mx);\n        if (state == KDIntersect::OUTSIDE)\
    \ return;\n        if (state == KDIntersect::INSIDE) {\n            u->give_tag(tag);\n\
    \            return;\n        }\n        u->down();\n        if (condition(u->pt,\
    \ u->pt) != KDIntersect::OUTSIDE) {\n            if constexpr (hasTagToValue)\n\
    \                u->org = u->org + tag;\n        }\n        transform_range_impl(u->l,\
    \ condition, tag);\n        transform_range_impl(u->r, condition, tag);\n    \
    \    u->up();\n    }\n    static bool update_node_impl(node* u, node* target,\
    \ const auto& op, int dim) requires (hasValue) {\n        if (!u) return false;\n\
    \        for (size_t i = 0; i < K; ++i)\n            if (target->pt[i] < u->mn[i]\
    \ || target->pt[i] > u->mx[i]) return false;\n        if constexpr (hasTag) u->down();\n\
    \        if (u == target) {\n            op(u->org); \n            u->up();\n\
    \            return true;\n        }\n        bool updated = false;\n        if\
    \ (cmp_less(target, u, dim))\n            updated = update_node_impl(u->l, target,\
    \ op, (dim + 1) % K);\n        else\n            updated = update_node_impl(u->r,\
    \ target, op, (dim + 1) % K);\n        if (updated) u->up();\n        return updated;\n\
    \    }\n    template <typename DistCalc>\n    static void nearest_impl(node *u,\
    \ const Point& target, int dim, DistCalc& calc, Coord& best_d, node*& best_u)\
    \ {\n        if (!u) return;\n        Coord d = calc.dist(u->pt, target);\n  \
    \      if (d < best_d) {\n            best_d = d;\n            best_u = u;\n \
    \       }\n        Coord dl = u->l ? calc.min_dist(target, u->l->mn, u->l->mx)\
    \ : std::numeric_limits<Coord>::max();\n        Coord dr = u->r ? calc.min_dist(target,\
    \ u->r->mn, u->r->mx) : std::numeric_limits<Coord>::max();\n        if (dl < dr)\
    \ {\n            if (dl < best_d) nearest_impl(u->l, target, (dim + 1) % K, calc,\
    \ best_d, best_u);\n            if (dr < best_d) nearest_impl(u->r, target, (dim\
    \ + 1) % K, calc, best_d, best_u);\n        }\n        else {\n            if\
    \ (dr < best_d) nearest_impl(u->r, target, (dim + 1) % K, calc, best_d, best_u);\n\
    \            if (dl < best_d) nearest_impl(u->l, target, (dim + 1) % K, calc,\
    \ best_d, best_u);\n        }\n    }\npublic:\n    KDTree() = default;\n    std::vector<node*>\
    \ build(const std::vector<Point>& pts) requires (!hasValue) {\n        std::vector<node*>\
    \ handles;\n        handles.reserve(pts.size());\n        for (const auto& p :\
    \ pts) handles.push_back(NodeAlloc::allocate(p));\n        std::vector<node*>\
    \ build_nodes = handles;\n        if (!build_nodes.empty()) root = build_tree(build_nodes,\
    \ 0, build_nodes.size() - 1, 0);\n        else root = nullptr;\n        return\
    \ handles;\n    }\n    std::vector<node*> build(const std::vector<std::pair<Point,\
    \ Value>>& pts) requires (hasValue) {\n        std::vector<node*> handles;\n \
    \       handles.reserve(pts.size());\n        for (const auto& [p, v] : pts) handles.push_back(NodeAlloc::allocate(p,\
    \ v));\n        std::vector<node*> build_nodes = handles;\n        if (!build_nodes.empty())\
    \ root = build_tree(build_nodes, 0, build_nodes.size() - 1, 0);\n        else\
    \ root = nullptr;\n        return handles;\n    }\n    void destruct() { free(root);\
    \ }\n    int size() const { return root ? root->sz : 0; }\n    node* insert(const\
    \ Point &pt) requires (!hasValue) {\n        node* u = NodeAlloc::allocate(pt);\n\
    \        insert_target(u);\n        return u;\n    }\n    node* insert(const Point\
    \ &pt, const Value &v) requires (hasValue) {\n        node* u = NodeAlloc::allocate(pt,\
    \ v);\n        insert_target(u);\n        return u;\n    }\n    void insert_target(node*\
    \ target) {\n        node** rebuild_ptr = nullptr;\n        int rebuild_dim =\
    \ 0;\n        insert_impl(root, target, 0, rebuild_ptr, rebuild_dim);\n      \
    \  if (rebuild_ptr != nullptr) {\n            std::vector<node*> nodes;\n    \
    \        nodes.reserve((*rebuild_ptr)->sz);\n            flatten(*rebuild_ptr,\
    \ nodes);\n            *rebuild_ptr = build_tree(nodes, 0, nodes.size() - 1, rebuild_dim);\n\
    \        }\n    }\n    bool update_node(node* target, const auto& op) requires\
    \ (hasValue) {\n        if (!target) return false;\n        return update_node_impl(root,\
    \ target, op, 0);\n    }\n    Value query_range(const auto& condition) requires\
    \ (hasValue) {\n        return query_range_impl(root, condition);\n    }\n   \
    \ void transform_range(const auto& condition, const Tag& tag) requires (hasTag)\
    \ {\n        transform_range_impl(root, condition, tag);\n    }\n    struct EuclideanDistCalc\
    \ {\n        Coord dist(const Point& a, const Point& b) {\n            Coord res\
    \ = Coord();\n            for (int i = 0; i < K; ++i) res += (a[i] - b[i]) * (a[i]\
    \ - b[i]);\n            return res;\n        }\n        Coord min_dist(const Point&\
    \ p, const Point& mn, const Point& mx) {\n            Coord res = Coord();\n \
    \           for (int i = 0; i < K; ++i) {\n                Coord d = std::max<Coord>(0,\
    \ std::max(mn[i] - p[i], p[i] - mx[i]));\n                res += d * d;\n    \
    \        }\n            return res;\n        }\n    };\n    template<typename\
    \ DistCalc = EuclideanDistCalc>\n    std::pair<Coord, Point> nearest_neighbor(const\
    \ Point& target, DistCalc calc) {\n        Coord best_d = std::numeric_limits<Coord>::max();\n\
    \        node* best_u = nullptr;\n        nearest_impl(root, target, 0, calc,\
    \ best_d, best_u);\n        return {best_d, best_u->pt};\n    }\n    struct Rect\
    \ {\n        Coord x1, y1, x2, y2;\n        Rect(Coord _x1, Coord _y1, Coord _x2,\
    \ Coord _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {\n            static_assert(K\
    \ == 2);\n        }\n        KDIntersect operator()(const Point& mn, const Point&\
    \ mx) const {\n            if (mn[0] > x2 || mx[0] < x1 || mn[1] > y2 || mx[1]\
    \ < y1) return KDIntersect::OUTSIDE;\n            if (mn[0] >= x1 && mx[0] <=\
    \ x2 && mn[1] >= y1 && mx[1] <= y2) return KDIntersect::INSIDE;\n            return\
    \ KDIntersect::PARTIAL;\n        }\n    };\n    struct Box {\n        Point b_mn,\
    \ b_mx;\n        Box(Point _mn, Point _mx) : b_mn(_mn), b_mx(_mx) {}\n       \
    \ KDIntersect operator()(const Point& mn, const Point& mx) const {\n         \
    \   bool inside = true;\n            for (size_t i = 0; i < K; ++i) {\n      \
    \          if (mn[i] > b_mx[i] || mx[i] < b_mn[i]) return KDIntersect::OUTSIDE;\n\
    \                if (mn[i] < b_mn[i] || mx[i] > b_mx[i]) inside = false;\n   \
    \         }\n            return inside ? KDIntersect::INSIDE : KDIntersect::PARTIAL;\n\
    \        }\n    };\n};\n"
  code: "#pragma once\n\n#include \"DataStructure/DefaultAllocator.hpp\"\n#include\
    \ \"Algebra/ValidOperation.hpp\"\n\n#ifndef KDTREE_ALPHA\n    #define KDTREE_ALPHA\
    \ 0.75\n#endif\n\nenum class KDIntersect { OUTSIDE = 0, INSIDE = 1, PARTIAL =\
    \ 2 };\n\ntemplate<size_t K,\n         typename Coord = long long,\n         typename\
    \ Value = void,\n         typename Tag = void,\n         template<typename> class\
    \ Allocator = DefaultAllocator\n>\nclass KDTree {\n    static constexpr bool hasValue\
    \ = !std::is_void_v<Value>;\n    static constexpr bool hasTag = !std::is_void_v<Tag>;\n\
    \    static constexpr bool hasTagToValue = Addable<Value, Tag>;\n    struct Empty\
    \ {};\n    template <bool Condition, typename T>\n    static auto get_default()\
    \ {\n        if constexpr (Condition) return T();\n        else return Empty{};\n\
    \    }\n    static_assert(!hasValue || Addable<Value, Value>);\n    static_assert(!hasTag\
    \ || Addable<Tag, Tag>);\npublic:\n    using Point = std::array<Coord, K>;\n\n\
    \    struct node {\n        node *l = nullptr, *r = nullptr;\n        Point pt;\n\
    \        Point mn, mx;\n        int sz = 1;\n        [[no_unique_address]] std::conditional_t<hasValue,\
    \ Value, Empty> org = get_default<hasValue, Value>();\n        [[no_unique_address]]\
    \ std::conditional_t<hasValue, Value, Empty> val = get_default<hasValue, Value>();\n\
    \        [[no_unique_address]] std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag,\
    \ Tag>();\n\n        node() = default;\n        node(const Point &p) requires\
    \ (!hasValue) : pt(p), mn(p), mx(p) {}\n        node(const Point &p, const Value\
    \ &v) requires (hasValue) : pt(p), mn(p), mx(p), org(v), val(v) {}\n\n       \
    \ void up() {\n            sz = 1;\n            mn = mx = pt;\n            if\
    \ constexpr (hasValue) val = org;\n\n            if (l) {\n                sz\
    \ += l->sz;\n                for (size_t i = 0; i < K; ++i) {\n              \
    \      mn[i] = std::min(mn[i], l->mn[i]);\n                    mx[i] = std::max(mx[i],\
    \ l->mx[i]);\n                }\n                if constexpr (hasValue) val =\
    \ val + l->val;\n            }\n            if (r) {\n                sz += r->sz;\n\
    \                for (size_t i = 0; i < K; ++i) {\n                    mn[i] =\
    \ std::min(mn[i], r->mn[i]);\n                    mx[i] = std::max(mx[i], r->mx[i]);\n\
    \                }\n                if constexpr (hasValue) val = val + r->val;\n\
    \            }\n        }\n        void give_tag(const auto &tag) requires (hasTag)\
    \ {\n            if constexpr (hasTagToValue) {\n                org = org + tag;\n\
    \                val = val + tag; \n            }\n            lazy = lazy + tag;\n\
    \        }\n        void down() requires (hasTag) {\n            bool need_tag\
    \ = false;\n            if constexpr (std::equality_comparable<Tag>) need_tag\
    \ = !(lazy == Tag());\n            else need_tag = true;\n            \n     \
    \       if (!need_tag) return;\n            \n            if (l) l->give_tag(lazy);\n\
    \            if (r) r->give_tag(lazy);\n            lazy = Tag();\n        }\n\
    \        friend std::ostream& operator<<(std::ostream& os, const node &v) {\n\
    \            os << \"(\";\n            for(size_t i=0; i<K; ++i) os << v.pt[i]\
    \ << (i+1==K ? \"\" : \", \");\n            os << \")\";\n            if constexpr\
    \ (hasValue) os << \" {org = \" << v.org << \", val = \" << v.val << \"}\";\n\
    \            return os;\n        }\n    };\n    using NodeAlloc = Allocator<node>;\n\
    \    node *root = nullptr;\nprivate:\n    static void free(node *&ptr) {\n   \
    \     if (ptr == nullptr) return;\n        free(ptr->l);\n        free(ptr->r);\n\
    \        NodeAlloc::deallocate(ptr);\n        ptr = nullptr;\n    }\n    static\
    \ void flatten(node *u, std::vector<node*>& res) {\n        if (!u) return;\n\
    \        if constexpr (hasTag) u->down();\n        flatten(u->l, res);\n     \
    \   res.push_back(u);\n        flatten(u->r, res);\n    }\n    static bool cmp_less(node*\
    \ a, node* b, int dim) {\n        if (a->pt[dim] != b->pt[dim]) return a->pt[dim]\
    \ < b->pt[dim];\n        return std::less<node*>{}(a, b);\n    }\n    static node*\
    \ build_tree(std::vector<node*>& nodes, int l, int r, int dim) {\n        if (l\
    \ > r) return nullptr;\n        int mid = l + (r - l) / 2;\n        std::nth_element(nodes.begin()\
    \ + l, nodes.begin() + mid, nodes.begin() + r + 1, [dim](node* a, node* b) {\n\
    \            return cmp_less(a, b, dim);\n        });\n        node *u = nodes[mid];\n\
    \        u->l = build_tree(nodes, l, mid - 1, (dim + 1) % K);\n        u->r =\
    \ build_tree(nodes, mid + 1, r, (dim + 1) % K);\n        u->up();\n        return\
    \ u;\n    }\n    static void insert_impl(node*& u, node* target, int dim, node**&\
    \ rebuild_ptr, int& rebuild_dim) {\n        if (!u) {\n            u = target;\n\
    \            u->up();\n            return;\n        }\n        if constexpr (hasTag)\
    \ u->down();\n        if (cmp_less(target, u, dim))\n            insert_impl(u->l,\
    \ target, (dim + 1) % K, rebuild_ptr, rebuild_dim);\n        else\n          \
    \  insert_impl(u->r, target, (dim + 1) % K, rebuild_ptr, rebuild_dim);\n     \
    \   u->up();\n        int max_sz = std::max(u->l ? u->l->sz : 0, u->r ? u->r->sz\
    \ : 0);\n        if (max_sz > u->sz * KDTREE_ALPHA) {\n            rebuild_ptr\
    \ = &u;\n            rebuild_dim = dim;\n        }\n    }\n    static Value query_range_impl(node\
    \ *u, const auto& condition) requires (hasValue) {\n        if (!u) return Value();\n\
    \        KDIntersect state = condition(u->mn, u->mx);\n        if (state == KDIntersect::OUTSIDE)\
    \ return Value();\n        if (state == KDIntersect::INSIDE) return u->val;\n\
    \        if constexpr (hasTag) u->down();\n        Value res = Value();\n    \
    \    if (condition(u->pt, u->pt) != KDIntersect::OUTSIDE)\n            res = res\
    \ + u->org;\n        if (u->l) res = res + query_range_impl(u->l, condition);\n\
    \        if (u->r) res = res + query_range_impl(u->r, condition);\n        return\
    \ res;\n    }\n    static void transform_range_impl(node *u, const auto& condition,\
    \ const Tag& tag) requires (hasTag) {\n        if (!u) return;\n        KDIntersect\
    \ state = condition(u->mn, u->mx);\n        if (state == KDIntersect::OUTSIDE)\
    \ return;\n        if (state == KDIntersect::INSIDE) {\n            u->give_tag(tag);\n\
    \            return;\n        }\n        u->down();\n        if (condition(u->pt,\
    \ u->pt) != KDIntersect::OUTSIDE) {\n            if constexpr (hasTagToValue)\n\
    \                u->org = u->org + tag;\n        }\n        transform_range_impl(u->l,\
    \ condition, tag);\n        transform_range_impl(u->r, condition, tag);\n    \
    \    u->up();\n    }\n    static bool update_node_impl(node* u, node* target,\
    \ const auto& op, int dim) requires (hasValue) {\n        if (!u) return false;\n\
    \        for (size_t i = 0; i < K; ++i)\n            if (target->pt[i] < u->mn[i]\
    \ || target->pt[i] > u->mx[i]) return false;\n        if constexpr (hasTag) u->down();\n\
    \        if (u == target) {\n            op(u->org); \n            u->up();\n\
    \            return true;\n        }\n        bool updated = false;\n        if\
    \ (cmp_less(target, u, dim))\n            updated = update_node_impl(u->l, target,\
    \ op, (dim + 1) % K);\n        else\n            updated = update_node_impl(u->r,\
    \ target, op, (dim + 1) % K);\n        if (updated) u->up();\n        return updated;\n\
    \    }\n    template <typename DistCalc>\n    static void nearest_impl(node *u,\
    \ const Point& target, int dim, DistCalc& calc, Coord& best_d, node*& best_u)\
    \ {\n        if (!u) return;\n        Coord d = calc.dist(u->pt, target);\n  \
    \      if (d < best_d) {\n            best_d = d;\n            best_u = u;\n \
    \       }\n        Coord dl = u->l ? calc.min_dist(target, u->l->mn, u->l->mx)\
    \ : std::numeric_limits<Coord>::max();\n        Coord dr = u->r ? calc.min_dist(target,\
    \ u->r->mn, u->r->mx) : std::numeric_limits<Coord>::max();\n        if (dl < dr)\
    \ {\n            if (dl < best_d) nearest_impl(u->l, target, (dim + 1) % K, calc,\
    \ best_d, best_u);\n            if (dr < best_d) nearest_impl(u->r, target, (dim\
    \ + 1) % K, calc, best_d, best_u);\n        }\n        else {\n            if\
    \ (dr < best_d) nearest_impl(u->r, target, (dim + 1) % K, calc, best_d, best_u);\n\
    \            if (dl < best_d) nearest_impl(u->l, target, (dim + 1) % K, calc,\
    \ best_d, best_u);\n        }\n    }\npublic:\n    KDTree() = default;\n    std::vector<node*>\
    \ build(const std::vector<Point>& pts) requires (!hasValue) {\n        std::vector<node*>\
    \ handles;\n        handles.reserve(pts.size());\n        for (const auto& p :\
    \ pts) handles.push_back(NodeAlloc::allocate(p));\n        std::vector<node*>\
    \ build_nodes = handles;\n        if (!build_nodes.empty()) root = build_tree(build_nodes,\
    \ 0, build_nodes.size() - 1, 0);\n        else root = nullptr;\n        return\
    \ handles;\n    }\n    std::vector<node*> build(const std::vector<std::pair<Point,\
    \ Value>>& pts) requires (hasValue) {\n        std::vector<node*> handles;\n \
    \       handles.reserve(pts.size());\n        for (const auto& [p, v] : pts) handles.push_back(NodeAlloc::allocate(p,\
    \ v));\n        std::vector<node*> build_nodes = handles;\n        if (!build_nodes.empty())\
    \ root = build_tree(build_nodes, 0, build_nodes.size() - 1, 0);\n        else\
    \ root = nullptr;\n        return handles;\n    }\n    void destruct() { free(root);\
    \ }\n    int size() const { return root ? root->sz : 0; }\n    node* insert(const\
    \ Point &pt) requires (!hasValue) {\n        node* u = NodeAlloc::allocate(pt);\n\
    \        insert_target(u);\n        return u;\n    }\n    node* insert(const Point\
    \ &pt, const Value &v) requires (hasValue) {\n        node* u = NodeAlloc::allocate(pt,\
    \ v);\n        insert_target(u);\n        return u;\n    }\n    void insert_target(node*\
    \ target) {\n        node** rebuild_ptr = nullptr;\n        int rebuild_dim =\
    \ 0;\n        insert_impl(root, target, 0, rebuild_ptr, rebuild_dim);\n      \
    \  if (rebuild_ptr != nullptr) {\n            std::vector<node*> nodes;\n    \
    \        nodes.reserve((*rebuild_ptr)->sz);\n            flatten(*rebuild_ptr,\
    \ nodes);\n            *rebuild_ptr = build_tree(nodes, 0, nodes.size() - 1, rebuild_dim);\n\
    \        }\n    }\n    bool update_node(node* target, const auto& op) requires\
    \ (hasValue) {\n        if (!target) return false;\n        return update_node_impl(root,\
    \ target, op, 0);\n    }\n    Value query_range(const auto& condition) requires\
    \ (hasValue) {\n        return query_range_impl(root, condition);\n    }\n   \
    \ void transform_range(const auto& condition, const Tag& tag) requires (hasTag)\
    \ {\n        transform_range_impl(root, condition, tag);\n    }\n    struct EuclideanDistCalc\
    \ {\n        Coord dist(const Point& a, const Point& b) {\n            Coord res\
    \ = Coord();\n            for (int i = 0; i < K; ++i) res += (a[i] - b[i]) * (a[i]\
    \ - b[i]);\n            return res;\n        }\n        Coord min_dist(const Point&\
    \ p, const Point& mn, const Point& mx) {\n            Coord res = Coord();\n \
    \           for (int i = 0; i < K; ++i) {\n                Coord d = std::max<Coord>(0,\
    \ std::max(mn[i] - p[i], p[i] - mx[i]));\n                res += d * d;\n    \
    \        }\n            return res;\n        }\n    };\n    template<typename\
    \ DistCalc = EuclideanDistCalc>\n    std::pair<Coord, Point> nearest_neighbor(const\
    \ Point& target, DistCalc calc) {\n        Coord best_d = std::numeric_limits<Coord>::max();\n\
    \        node* best_u = nullptr;\n        nearest_impl(root, target, 0, calc,\
    \ best_d, best_u);\n        return {best_d, best_u->pt};\n    }\n    struct Rect\
    \ {\n        Coord x1, y1, x2, y2;\n        Rect(Coord _x1, Coord _y1, Coord _x2,\
    \ Coord _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {\n            static_assert(K\
    \ == 2);\n        }\n        KDIntersect operator()(const Point& mn, const Point&\
    \ mx) const {\n            if (mn[0] > x2 || mx[0] < x1 || mn[1] > y2 || mx[1]\
    \ < y1) return KDIntersect::OUTSIDE;\n            if (mn[0] >= x1 && mx[0] <=\
    \ x2 && mn[1] >= y1 && mx[1] <= y2) return KDIntersect::INSIDE;\n            return\
    \ KDIntersect::PARTIAL;\n        }\n    };\n    struct Box {\n        Point b_mn,\
    \ b_mx;\n        Box(Point _mn, Point _mx) : b_mn(_mn), b_mx(_mx) {}\n       \
    \ KDIntersect operator()(const Point& mn, const Point& mx) const {\n         \
    \   bool inside = true;\n            for (size_t i = 0; i < K; ++i) {\n      \
    \          if (mn[i] > b_mx[i] || mx[i] < b_mn[i]) return KDIntersect::OUTSIDE;\n\
    \                if (mn[i] < b_mn[i] || mx[i] > b_mx[i]) inside = false;\n   \
    \         }\n            return inside ? KDIntersect::INSIDE : KDIntersect::PARTIAL;\n\
    \        }\n    };\n};\n"
  dependsOn:
  - DataStructure/DefaultAllocator.hpp
  - Algebra/ValidOperation.hpp
  isVerificationFile: false
  path: DataStructure/KDTree.hpp
  requiredBy: []
  timestamp: '2026-10-02 00:27:06+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp
documentation_of: DataStructure/KDTree.hpp
layout: document
redirect_from:
- /library/DataStructure/KDTree.hpp
- /library/DataStructure/KDTree.hpp.html
title: DataStructure/KDTree.hpp
---
