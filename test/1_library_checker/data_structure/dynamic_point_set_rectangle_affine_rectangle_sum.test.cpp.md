---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
    title: Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/sum_and_size.hpp
    title: Algebra/Monoid/sum_and_size.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/Tag/linear_transform_tag.hpp
    title: Algebra/Tag/linear_transform_tag.hpp
  - icon: ':question:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':question:'
    path: DataStructure/DefaultAllocator.hpp
    title: Default Allocator
  - icon: ':heavy_check_mark:'
    path: DataStructure/KDTree.hpp
    title: DataStructure/KDTree.hpp
  - icon: ':question:'
    path: Numeric/Modint.hpp
    title: Numeric/Modint.hpp
  - icon: ':question:'
    path: Numeric/internal_math.hpp
    title: Numeric/internal_math.hpp
  - icon: ':question:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_point_set_rectangle_affine_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_point_set_rectangle_affine_rectangle_sum
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_point_set_rectangle_affine_rectangle_sum\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp\"\
    \n\n#line 2 \"DataStructure/KDTree.hpp\"\n\n#line 2 \"DataStructure/DefaultAllocator.hpp\"\
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
    \        }\n    };\n};\n#line 2 \"Numeric/Modint.hpp\"\n\n// Reference: Atcoder\
    \ Library https://github.com/atcoder/ac-library\n#line 2 \"Numeric/internal_math.hpp\"\
    \n// Reference: Atcoder Library https://github.com/atcoder/ac-library\n\n#ifdef\
    \ _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace internal {\nconstexpr long\
    \ long safe_mod(long long x, long long m) {\n    x %= m;\n    if (x < 0) x +=\
    \ m;\n    return x;\n}\nconstexpr long long pow_mod_constexpr(long long x, long\
    \ long n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m = (unsigned\
    \ int)(m);\n    unsigned long long r = 1;\n    unsigned long long y = safe_mod(x,\
    \ m);\n    while (n) {\n        if (n & 1) r = (r * y) % _m;\n        y = (y *\
    \ y) % _m;\n        n >>= 1;\n    }\n    return r;\n}\nconstexpr bool is_prime_constexpr(int\
    \ n) {\n    if (n <= 1) return false;\n    if (n == 2 || n == 7 || n == 61) return\
    \ true;\n    if (n % 2 == 0) return false;\n    long long d = n - 1;\n    while\
    \ (d % 2 == 0) d /= 2;\n    constexpr long long bases[3] = {2, 7, 61};\n    for\
    \ (long long a : bases) {\n        long long t = d;\n        long long y = pow_mod_constexpr(a,\
    \ t, n);\n        while (t != n - 1 && y != 1 && y != n - 1)\n            y =\
    \ y * y % n, t <<= 1;\n        if (y != n - 1 && t % 2 == 0)\n            return\
    \ false;\n    }\n    return true;\n}\ntemplate <int n> constexpr bool is_prime\
    \ = is_prime_constexpr(n);\nconstexpr std::pair<long long, long long> inv_gcd(long\
    \ long a, long long b) {\n    a = safe_mod(a, b);\n    if (a == 0) return {b,\
    \ 0};\n    long long s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n        long\
    \ long u = s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp = s;\n\
    \        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0 < 0)\
    \ m0 += b / s;\n    return {s, m0};\n}\n}  // namespace internal\n\nnamespace\
    \ internal {\n#ifndef _MSC_VER\n    template <class T>\n        using is_signed_int128\
    \ =\n        typename std::conditional<std::is_same<T, __int128_t>::value ||\n\
    \        std::is_same<T, __int128>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using is_unsigned_int128 =\n        typename\
    \ std::conditional<std::is_same<T, __uint128_t>::value ||\n        std::is_same<T,\
    \ unsigned __int128>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using make_unsigned_int128 =\n        typename\
    \ std::conditional<std::is_same<T, __int128_t>::value,\n                 __uint128_t,\n\
    \                 unsigned __int128>;\n    template <class T>\n        using is_integral\
    \ = typename std::conditional<std::is_integral<T>::value ||\n        is_signed_int128<T>::value\
    \ ||\n        is_unsigned_int128<T>::value,\n        std::true_type,\n       \
    \ std::false_type>::type;\n    template <class T>\n        using is_signed_int\
    \ = typename std::conditional<(is_integral<T>::value &&\n                std::is_signed<T>::value)\
    \ ||\n        is_signed_int128<T>::value,\n        std::true_type,\n        std::false_type>::type;\n\
    \    template <class T>\n        using is_unsigned_int =\n        typename std::conditional<(is_integral<T>::value\
    \ &&\n                std::is_unsigned<T>::value) ||\n        is_unsigned_int128<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<\n        is_signed_int128<T>::value,\n\
    \        make_unsigned_int128<T>,\n        typename std::conditional<std::is_signed<T>::value,\n\
    \        std::make_unsigned<T>,\n        std::common_type<T>>::type>::type;\n\
    #else\n    template <class T> using is_integral = typename std::is_integral<T>;\n\
    \    template <class T>\n        using is_signed_int =\n        typename std::conditional<is_integral<T>::value\
    \ && std::is_signed<T>::value,\n                 std::true_type,\n           \
    \      std::false_type>::type;\n    template <class T>\n        using is_unsigned_int\
    \ =\n        typename std::conditional<is_integral<T>::value &&\n        std::is_unsigned<T>::value,\n\
    \        std::true_type,\n        std::false_type>::type;\n    template <class\
    \ T>\n        using to_unsigned = typename std::conditional<is_signed_int<T>::value,\n\
    \              std::make_unsigned<T>,\n              std::common_type<T>>::type;\n\
    #endif\n    template <class T> using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\n\
    \    template <class T> using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\n\
    \    template <class T> using to_unsigned_t = typename to_unsigned<T>::type;\n\
    \    struct modint_base {};\n    struct static_modint_base : modint_base {};\n\
    \    template <class T> using is_modint = std::is_base_of<modint_base, T>;\n \
    \   template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\
    }  // namespace internal\n#line 5 \"Numeric/Modint.hpp\"\n\ntemplate <int m, std::enable_if_t<(1\
    \ <= m)>* = nullptr>\nstruct static_modint : internal::static_modint_base {\n\
    \    using mint = static_modint;\n\n  public:\n    static constexpr int mod()\
    \ { return m; }\n    static mint raw(int v) {\n        mint x;\n        x._v =\
    \ v;\n        return x;\n    }\n\n    static_modint() : _v(0) {}\n    template\
    \ <class T, internal::is_signed_int_t<T>* = nullptr>\n    static_modint(T v) {\n\
    \        long long x = (long long)(v % (long long)(umod()));\n        if (x <\
    \ 0) x += umod();\n        _v = (unsigned int)(x);\n    }\n    template <class\
    \ T, internal::is_unsigned_int_t<T>* = nullptr>\n    static_modint(T v) {\n  \
    \      _v = (unsigned int)(v % umod());\n    }\n\n    unsigned int val() const\
    \ { return _v; }\n\n    mint& operator++() {\n        _v++;\n        if (_v ==\
    \ umod()) _v = 0;\n        return *this;\n    }\n    mint& operator--() {\n  \
    \      if (_v == 0) _v = umod();\n        _v--;\n        return *this;\n    }\n\
    \    mint operator++(int) {\n        mint result = *this;\n        ++*this;\n\
    \        return result;\n    }\n    mint operator--(int) {\n        mint result\
    \ = *this;\n        --*this;\n        return result;\n    }\n\n    mint& operator+=(const\
    \ mint& rhs) {\n        _v += rhs._v;\n        if (_v >= umod()) _v -= umod();\n\
    \        return *this;\n    }\n    mint& operator-=(const mint& rhs) {\n     \
    \   _v -= rhs._v;\n        if (_v >= umod()) _v += umod();\n        return *this;\n\
    \    }\n    mint& operator*=(const mint& rhs) {\n        unsigned long long z\
    \ = _v;\n        z *= rhs._v;\n        _v = (unsigned int)(z % umod());\n    \
    \    return *this;\n    }\n    mint& operator/=(const mint& rhs) { return *this\
    \ = *this * rhs.inv(); }\n\n    mint operator+() const { return *this; }\n   \
    \ mint operator-() const { return mint() - *this; }\n\n    mint pow(long long\
    \ n) const {\n        assert(0 <= n);\n        mint x = *this, r = 1;\n      \
    \  while (n) {\n            if (n & 1) r *= x;\n            x *= x;\n        \
    \    n >>= 1;\n        }\n        return r;\n    }\n    mint inv() const {\n \
    \       if (prime) {\n            assert(_v);\n            return pow(umod() -\
    \ 2);\n        } else {\n            auto eg = internal::inv_gcd(_v, m);\n   \
    \         assert(eg.first == 1);\n            return eg.second;\n        }\n \
    \   }\n\n    friend mint operator+(const mint& lhs, const mint& rhs) {\n     \
    \   return mint(lhs) += rhs;\n    }\n    friend mint operator-(const mint& lhs,\
    \ const mint& rhs) {\n        return mint(lhs) -= rhs;\n    }\n    friend mint\
    \ operator*(const mint& lhs, const mint& rhs) {\n        return mint(lhs) *= rhs;\n\
    \    }\n    friend mint operator/(const mint& lhs, const mint& rhs) {\n      \
    \  return mint(lhs) /= rhs;\n    }\n    friend bool operator==(const mint& lhs,\
    \ const mint& rhs) {\n        return lhs._v == rhs._v;\n    }\n    friend bool\
    \ operator!=(const mint& lhs, const mint& rhs) {\n        return lhs._v != rhs._v;\n\
    \    }\n    friend std::strong_ordering operator<=>(const mint& lhs, const mint&\
    \ rhs) {\n        return lhs._v <=> rhs._v;\n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const mint& v) {\n        os << v._v;\n        return os;\n    }\n    friend\
    \ std::istream& operator>>(std::istream& is, mint& v) {\n        long long x;\n\
    \        is >> x;\n        x %= (long long)(umod());\n        if (x < 0) x +=\
    \ umod();\n        v._v = (unsigned int)(x);\n        return is;\n    }\n\n  private:\n\
    \    unsigned int _v;\n    static constexpr unsigned int umod() { return m; }\n\
    \    static constexpr bool prime = internal::is_prime<m>;\n};\n\nusing modint998244353\
    \ = static_modint<998244353>;\nusing modint1000000007 = static_modint<1000000007>;\n\
    #line 2 \"Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp\"\n\n#line 2\
    \ \"Algebra/Monoid/sum_and_size.hpp\"\n\ntemplate<typename T, typename size_type\
    \ = int>\nstruct sum_and_size {\n    T val;\n    size_type sz;\n    sum_and_size(T\
    \ _val, size_type _sz) : val(_val), sz(_sz) {}\n    sum_and_size(T _val) : sum_and_size(_val,\
    \ 1) {}\n    sum_and_size() : sum_and_size(0, 0) {}\n    sum_and_size operator+(const\
    \ sum_and_size &rhs) const {\n        return sum_and_size(val + rhs.val, sz +\
    \ rhs.sz);\n    }\n    sum_and_size operator-(const sum_and_size &rhs) const {\n\
    \        return sum_and_size(val - rhs.val, sz - rhs.sz);\n    }\n    friend std::ostream&\
    \ operator<<(std::ostream& os, const sum_and_size &v) {\n        os << v.val;\n\
    \        return os;\n    }\n    friend std::istream& operator>>(std::istream&\
    \ is, sum_and_size &v) {\n        is >> v.val;\n        v.sz = 1;\n        return\
    \ is;\n    }\n};\n#line 2 \"Algebra/Tag/linear_transform_tag.hpp\"\n\ntemplate<typename\
    \ T>\nstruct linear_transform_tag {\n    T a, b;\n    linear_transform_tag(T _a\
    \ = 1, T _b = 0): a(_a), b(_b) {}\n    linear_transform_tag operator+(const linear_transform_tag\
    \ &rhs) const {\n        return linear_transform_tag(a * rhs.a, rhs.a * b + rhs.b);\n\
    \    }\n    bool operator==(const linear_transform_tag &rhs) const {\n       \
    \ return a == rhs.a && b == rhs.b;\n    }\n};\n#line 5 \"Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp\"\
    \n\ntemplate<typename T, typename size_value>\nsum_and_size<T, size_value> operator+(const\
    \ sum_and_size<T, size_value> &lhs, const linear_transform_tag<T> &rhs) {\n  \
    \  return sum_and_size<T, size_value>(lhs.val * rhs.a + lhs.sz * rhs.b, lhs.sz);\
    \  \n}\n#line 7 \"test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp\"\
    \n\nusing mint = modint998244353;\nusing kdtree = KDTree<2, long long, sum_and_size<mint>,\
    \ linear_transform_tag<mint>>;\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n, q;\n    std::cin >> n >> q;\n    kdtree tree;\n\
    \    std::vector<std::pair<kdtree::Point, sum_and_size<mint>>> arr(n);\n    for\
    \ (auto &[pt, v] : arr)\n        std::cin >> pt[0] >> pt[1] >> v;\n    auto pts\
    \ = tree.build(arr);\n    while (q--) {\n        int op;\n        std::cin >>\
    \ op;\n        if (op == 0) {\n            kdtree::Point pt;\n            sum_and_size<mint>\
    \ w;\n            std::cin >> pt[0] >> pt[1] >> w;\n            pts.push_back(tree.insert(pt,\
    \ w));\n        }\n        else if (op == 1) {\n            int x;\n         \
    \   sum_and_size<mint> w;\n            std::cin >> x >> w;\n            tree.update_node(pts[x],\
    \ [&](auto &v) {\n                v = w;  \n            });\n        }\n     \
    \   else if (op == 2) {\n            int l, d, r, u;\n            std::cin >>\
    \ l >> d >> r >> u;\n            std::cout << tree.query_range(kdtree::Rect(l,\
    \ d, r - 1, u - 1)) << \"\\n\";\n        }\n        else {\n            int l,\
    \ d, r, u;\n            linear_transform_tag<mint> tag;\n            std::cin\
    \ >> l >> d >> r >> u >> tag.a >> tag.b;\n            tree.transform_range(kdtree::Rect(l,\
    \ d, r - 1, u - 1), tag);\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_point_set_rectangle_affine_rectangle_sum\"\
    \n#include \"assumption.hpp\"\n\n#include \"DataStructure/KDTree.hpp\"\n#include\
    \ \"Numeric/Modint.hpp\"\n#include \"Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp\"\
    \n\nusing mint = modint998244353;\nusing kdtree = KDTree<2, long long, sum_and_size<mint>,\
    \ linear_transform_tag<mint>>;\n\nint main() {\n    std::ios::sync_with_stdio(0),\
    \ std::cin.tie(0);\n    int n, q;\n    std::cin >> n >> q;\n    kdtree tree;\n\
    \    std::vector<std::pair<kdtree::Point, sum_and_size<mint>>> arr(n);\n    for\
    \ (auto &[pt, v] : arr)\n        std::cin >> pt[0] >> pt[1] >> v;\n    auto pts\
    \ = tree.build(arr);\n    while (q--) {\n        int op;\n        std::cin >>\
    \ op;\n        if (op == 0) {\n            kdtree::Point pt;\n            sum_and_size<mint>\
    \ w;\n            std::cin >> pt[0] >> pt[1] >> w;\n            pts.push_back(tree.insert(pt,\
    \ w));\n        }\n        else if (op == 1) {\n            int x;\n         \
    \   sum_and_size<mint> w;\n            std::cin >> x >> w;\n            tree.update_node(pts[x],\
    \ [&](auto &v) {\n                v = w;  \n            });\n        }\n     \
    \   else if (op == 2) {\n            int l, d, r, u;\n            std::cin >>\
    \ l >> d >> r >> u;\n            std::cout << tree.query_range(kdtree::Rect(l,\
    \ d, r - 1, u - 1)) << \"\\n\";\n        }\n        else {\n            int l,\
    \ d, r, u;\n            linear_transform_tag<mint> tag;\n            std::cin\
    \ >> l >> d >> r >> u >> tag.a >> tag.b;\n            tree.transform_range(kdtree::Rect(l,\
    \ d, r - 1, u - 1), tag);\n        }\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/KDTree.hpp
  - DataStructure/DefaultAllocator.hpp
  - Algebra/ValidOperation.hpp
  - Numeric/Modint.hpp
  - Numeric/internal_math.hpp
  - Algebra/Acted_Monoid/sum_and_size-linear_transform.hpp
  - Algebra/Monoid/sum_and_size.hpp
  - Algebra/Tag/linear_transform_tag.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2026-10-03 12:08:22+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp
- /verify/test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp.html
title: test/1_library_checker/data_structure/dynamic_point_set_rectangle_affine_rectangle_sum.test.cpp
---
