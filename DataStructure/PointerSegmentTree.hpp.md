---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: DataStructure/DefaultAllocator.hpp
    title: DataStructure/DefaultAllocator.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp
    title: test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/point_set_range_composite_pointer.test.cpp
    title: test/1_library_checker/data_structure/point_set_range_composite_pointer.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/point_set_range_frequency.test.cpp
    title: test/1_library_checker/data_structure/point_set_range_frequency.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_affine_range_sum_pointer.test.cpp
    title: test/1_library_checker/data_structure/range_affine_range_sum_pointer.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/PointerSegmentTree.hpp\"\n\n#line 2 \"DataStructure/DefaultAllocator.hpp\"\
    \n\ntemplate<typename T>\nstruct DefaultAllocator {\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        return new T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { delete p; }\n};\n#line 4 \"DataStructure/PointerSegmentTree.hpp\"\
    \n\ntemplate<typename Value = int, typename Tag = void, bool pushdown = true,\
    \ template<typename> class Allocator = DefaultAllocator, bool dynamic = false,\
    \ bool persistent = false>\nclass PointerSegmentTree {\n    static constexpr bool\
    \ hasTag = !std::is_same_v<Tag, void>;\n    static constexpr bool hasGet = requires(int\
    \ l, int r) { Value::get(l, r); };\n    static_assert(pushdown || hasTag, \"Lazy\
    \ tag must exist when pushdown is false\");\n    int n;\n    struct Empty {};\n\
    \    template <bool Condition, typename T>\n    static auto get_default() {\n\
    \        if constexpr (Condition) return T();\n        else return Empty{};\n\
    \    }\n    struct node {\n        node *l = nullptr, *r = nullptr;\n        Value\
    \ val;\n        [[no_unique_address]] std::conditional_t<hasTag, Tag, Empty> lazy\
    \ = get_default<hasTag, Tag>();\n        Value get_val() {\n            if constexpr\
    \ (pushdown) return val;\n            else return val + lazy;\n        }\n   \
    \     void up() {\n            if constexpr (dynamic) {\n                val =\
    \ Value();\n                if (l) val = l->get_val();\n                if (r)\
    \ val = val + r->get_val();\n            }\n            else {\n             \
    \   val = l->get_val() + r->get_val();\n            }\n        }\n        void\
    \ up(int lft, int rgt) requires (dynamic && hasGet) {\n            if (l) val\
    \ = l->get_val();\n            else val = Value::get(lft, (lft + rgt) / 2);\n\
    \            if (r) val = val + r->get_val();\n            else val = val + Value::get((lft\
    \ + rgt) / 2, rgt);\n        }\n        void give_tag(const auto &tag) requires\
    \ (hasTag) {\n            if constexpr (pushdown) val = val + tag;\n         \
    \   lazy = lazy + tag;\n        }\n        void down() requires (hasTag && pushdown)\
    \ {\n            bool need_tag = false;\n            if constexpr (hasTag) { \n\
    \                if constexpr (std::equality_comparable<Tag>) need_tag = (lazy\
    \ != Tag());\n                else need_tag = true;\n            }\n         \
    \   if (!need_tag) return;\n            if constexpr (persistent) {\n        \
    \        if constexpr (persistent) l = NodeAlloc::allocate(*l);\n            \
    \    if constexpr (persistent) r = NodeAlloc::allocate(*r);\n            }\n \
    \           l->give_tag(lazy);\n            r->give_tag(lazy);\n            lazy\
    \ = Tag();\n        }\n        node() = default;\n        node(const auto &v)\
    \ : val(v) {}\n    };\n    node *root = nullptr;\n    using NodeAlloc = Allocator<node>;\n\
    \    void initialize(int l, int r, node *&p, const vector<Value> &data) {\n  \
    \      if (r - l == 1) \n            return p = NodeAlloc::allocate(data[l]),\
    \ void();\n        p = NodeAlloc::allocate();\n        int mid = (l + r) >> 1;\n\
    \        initialize(l, mid, p->l, data);\n        initialize(mid, r, p->r, data);\n\
    \        p->up();\n    }\n    Value range_prod(int L, int R, int l, int r, node\
    \ *p) {\n        if constexpr (dynamic) {\n            if (!p) {\n           \
    \     if constexpr (hasGet) return Value::get(std::max(L, l), std::min(R, r));\n\
    \                return Value();\n            }\n        }\n        if (L <= l\
    \ && R >= r)\n            return p->get_val();\n        if constexpr (hasTag &&\
    \ pushdown) p->down();\n        int mid = (l + r) >> 1;\n        if constexpr\
    \ (pushdown) {\n            if (R <= mid) return range_prod(L, R, l, mid, p->l);\n\
    \            if (L >= mid) return range_prod(L, R, mid, r, p->r);\n          \
    \  return range_prod(L, R, l, mid, p->l) + range_prod(L, R, mid, r, p->r); \n\
    \        }\n        else {\n            if (R <= mid) return range_prod(L, R,\
    \ l, mid, p->l) + p->lazy;\n            if (L >= mid) return range_prod(L, R,\
    \ mid, r, p->r) + p->lazy;\n            return range_prod(L, R, l, mid, p->l)\
    \ + range_prod(L, R, mid, r, p->r) + p->lazy;\n        }\n    }\n    void check_node(node\
    \ *&p, int l, int r) requires (dynamic || persistent) {\n        bool allocated\
    \ = false; \n        if constexpr (dynamic) if (!p) {\n            allocated =\
    \ true;\n            if constexpr (hasGet) p = NodeAlloc::allocate(Value::get(l,\
    \ r));\n            else p = NodeAlloc::allocate();\n        }\n        if constexpr\
    \ (persistent) if (!allocated) p = NodeAlloc::allocate(*p);\n    }\n    void update(node\
    \ *&p, int l, int r) {\n        if constexpr (dynamic && hasGet) p->up(l, r);\n\
    \        else p->up();\n    }\n    void modify(int x, int l, int r, node *&p,\
    \ const Value &v) {\n        if constexpr (dynamic || persistent) check_node(p,\
    \ l, r);\n        if (r - l == 1)\n            return p->val = v, void();\n  \
    \      if constexpr (hasTag && pushdown) p->down();\n        int mid = (l + r)\
    \ >> 1;\n        if constexpr (pushdown) {\n            if (x < mid) modify(x,\
    \ l, mid, p->l, v);\n            else modify(x, mid, r, p->r, v);\n        }\n\
    \        else {\n            if (x < mid) modify(x, l, mid, p->l, v - p->lazy);\n\
    \            else modify(x, mid, r, p->r, v - p->lazy);\n        }\n        update(p,\
    \ l, r);\n    }\n    void transform(int x, int l, int r, node *&p, const auto\
    \ &func) {\n        if constexpr (dynamic || persistent) check_node(p, l, r);\n\
    \        if (r - l == 1)\n            return func(p->val), void();\n        if\
    \ constexpr (hasTag && pushdown) p->down();\n        int mid = (l + r) >> 1;\n\
    \        if (x < mid) transform(x, l, mid, p->l, func);\n        else transform(x,\
    \ mid, r, p->r, func);\n        update(p, l, r);\n    }\n    void range_transform(int\
    \ L, int R, int l, int r, node *&p, const auto &tag) requires (hasTag) {\n   \
    \     if constexpr (dynamic || persistent) check_node(p, l, r);\n        if (L\
    \ <= l && R >= r)\n            return p->give_tag(tag);\n        if constexpr\
    \ (pushdown) p->down();\n        int mid = (l + r) >> 1;\n        if (L < mid)\
    \ range_transform(L, R, l, mid, p->l, tag);\n        if (R > mid) range_transform(L,\
    \ R, mid, r, p->r, tag);\n        update(p, l, r);\n    }\n    void range_transform_beats(int\
    \ L, int R, int l, int r, node *&p, const auto &tag, const auto &tag_condition,\
    \ auto... tag_sum) requires (hasTag) {\n        if constexpr (dynamic || persistent)\
    \ check_node(p, l, r);\n        if (L <= l && R >= r && tag_condition([&]{ if\
    \ constexpr(pushdown) return p->val; else return p->get_val() + (..., tag_sum);\
    \ }()))\n            return p->give_tag(tag);\n        assert(r - l > 1);\n  \
    \      if constexpr (pushdown) p->down();\n        else ((tag_sum = tag_sum +\
    \ p->lazy), ...);\n        int mid = (l + r) >> 1;\n        if (L < mid) range_transform_beats(L,\
    \ R, l, mid, p->l, tag, tag_condition, tag_sum...);\n        if (R > mid) range_transform_beats(L,\
    \ R, mid, r, p->r, tag, tag_condition, tag_sum...);\n        update(p, l, r);\n\
    \    }\n    int range_left_search(int L, int R, int l, int r, node *p, const auto\
    \ &condition, auto... tag_sum) {\n        if constexpr (!dynamic) if (!p) return\
    \ R;\n        if (r - l == 1) {\n            if (!condition([&]{ if constexpr(pushdown)\
    \ return p->val; else return p->get_val() + (..., tag_sum); }()))\n          \
    \      return R;\n            return l;\n        }\n        int mid = (l + r)\
    \ >> 1;\n        if constexpr (hasTag && pushdown) p->down();\n        if constexpr\
    \ (!pushdown) ((tag_sum = tag_sum + p->lazy), ...);\n        if (L <= l && R >=\
    \ r) {\n            if (p->l && condition([&]{ if constexpr(pushdown) return p->l->val;\
    \ else return p->l->get_val() + (..., tag_sum); }()))\n                return\
    \ range_left_search(L, R, l, mid, p->l, condition, tag_sum...);\n            return\
    \ range_left_search(L, R, mid, r, p->r, condition, tag_sum...);\n        }\n \
    \       int left = R;\n        if (L < mid) left = range_left_search(L, R, l,\
    \ mid, p->l, condition, tag_sum...);\n        if (left == R) {\n            if\
    \ (R > mid) return range_left_search(L, R, mid, r, p->r, condition, tag_sum...);\n\
    \            return R;\n        }\n        return left;\n    }\n    int range_right_search(int\
    \ L, int R, int l, int r, node *p, const auto &condition, auto... tag_sum) {\n\
    \        if constexpr (!dynamic) if (!p) return L - 1;\n        if (r - l == 1)\
    \ {\n            if (!condition([&]{ if constexpr(pushdown) return p->val; else\
    \ return p->get_val() + (..., tag_sum); }()))\n                return L - 1;\n\
    \            return l;\n        }\n        int mid = (l + r) >> 1;\n        if\
    \ constexpr (hasTag && pushdown) p->down();\n        if constexpr (!pushdown)\
    \ ((tag_sum = tag_sum + p->lazy), ...);\n        if (L <= l && R >= r) {\n   \
    \         if (p->r && condition([&]{ if constexpr(pushdown) return p->r->val;\
    \ else return p->r->get_val() + (..., tag_sum); }()))\n                return\
    \ range_right_search(L, R, mid, r, p->r, condition, tag_sum...);\n           \
    \ return range_right_search(L, R, l, mid, p->l, condition, tag_sum...);\n    \
    \    }\n        int right = L - 1;\n        if (R > mid) right = range_right_search(L,\
    \ R, mid, r, p->r, condition, tag_sum...);\n        if (right == L - 1) {\n  \
    \          if (L < mid) return range_right_search(L, R, l, mid, p->l, condition,\
    \ tag_sum...);\n            return L - 1;\n        }\n        return right;\n\
    \    }\n    Value get(int x, int l, int r, node *p) {\n        [[no_unique_address]]\
    \ std::conditional_t<!pushdown, Tag, Empty> tag;\n        while (r - l > 1) {\n\
    \            if constexpr (hasTag && pushdown) p->down();\n            if constexpr\
    \ (!pushdown) tag = tag + p->lazy;\n            int mid = (l + r) >> 1;\n    \
    \        if (x < mid) r = mid, p = p->l;\n            else l = mid, p = p->r;\n\
    \            if constexpr (dynamic || persistent) if (!p) {\n                if\
    \ constexpr (hasGet) return Value::get(x, x + 1) + tag;\n                else\
    \ return Value() + tag;\n            }\n        }\n        if constexpr (pushdown)\
    \ return p->val;\n        else return p->get_val() + tag;\n    }\n    void range_copy(int\
    \ L, int R, int l, int r, node *&p, node *&q) requires (pushdown && persistent)\
    \ {\n        if (L <= l && R >= r)\n            return p = q, void();\n      \
    \  if constexpr (dynamic || persistent) check_node(p, l, r);\n        if constexpr\
    \ (hasTag && pushdown) p->down(), q->down();\n        int mid = (l + r) >> 1;\n\
    \        if (L < mid) range_copy(L, R, l, mid, p->l, q->l);\n        if (R > mid)\
    \ range_copy(L, R, mid, r, p->r, q->r);\n        update(p, l, r);\n    }\n   \
    \ void printnode(int l, int r, node *p) {\n        std::cerr << \"[\" << l <<\
    \ \", \" << r << \"): \";\n        if constexpr (hasTag) std::cerr << \"val =\
    \ \" << p->val << \", tag = \" << p->lazy;\n        else std::cerr << p->val;\n\
    \        std::cerr << \"\\n\";\n    }\n    void printinfo(int L, int R, int l,\
    \ int r, node *p) {\n        printnode(l, r, p);\n        if (L <= l && R >= r)\n\
    \            return;\n        int mid = (l + r) >> 1;\n        if (L < mid) printinfo(L,\
    \ R, l, mid, p->l);\n        if (R > mid) printinfo(L, R, mid, r, p->r);\n   \
    \ }\n    void printall(int l, int r, node *p) {\n        printnode(l, r, p);\n\
    \        if (r - l == 1) return;\n        int mid = (l + r) >> 1;\n        printall(l,\
    \ mid, p->l);\n        printall(mid, r, p->r);\n    }\npublic:\n    PointerSegmentTree(const\
    \ vector<Value> &data): n(data.size()), root(nullptr) { \n        initialize(0,\
    \ n, root, data);\n    }\n    PointerSegmentTree(int size) requires (!dynamic)\
    \ : PointerSegmentTree(vector<Value>(size)) {}\n    PointerSegmentTree(int size\
    \ = 0) requires (dynamic || persistent) : n(size), root(nullptr) {}\n    Value\
    \ get(int x) {\n        assert(0 <= x && x < n);\n        return get(x, 0, n,\
    \ root);\n    }\n    Value range_prod(int l, int r) {\n        assert(0 <= l &&\
    \ r <= n);\n        assert(l <= r);\n        if (l == r) return Value();\n   \
    \     return range_prod(l, r, 0, n, root);\n    }\n    void modify(int x, const\
    \ Value &v) {\n        assert(0 <= x && x < n);\n        modify(x, 0, n, root,\
    \ v);\n    }\n    void transform(int x, const auto &func) {\n        assert(0\
    \ <= x && x < n);\n        transform(x, 0, n, root, func);\n    }\n    void range_transform(int\
    \ l, int r, const auto &tag) requires (hasTag) {\n        assert(0 <= l && r <=\
    \ n);\n        assert(l <= r);\n        if (l < r)\n            range_transform(l,\
    \ r, 0, n, root, tag);\n    }\n    void range_transform_beats(int l, int r, const\
    \ auto &tag, const auto &tag_condition) requires (hasTag) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l < r)\n            range_transform_beats(l,\
    \ r, 0, n, root, tag, tag_condition);\n    }\n    /*\n       For the given element\
    \ range [l, r)\n       Perform segment tree binary search within the range with\
    \ left half first \n       return fail if the node is empty\n     */\n    int\
    \ range_left_search(const auto &condition, int l = -1, int r = -1) {\n       \
    \ if (l == -1 && r == -1) l = 0, r = n;\n        assert(0 <= l && r <= n);\n \
    \       assert(l <= r);\n        if (l == r) return r;\n        return range_left_search(l,\
    \ r, 0, n, root, condition);\n    }\n    /*\n       For the given element range\
    \ (l, r]\n       Perform segment tree binary search within the range with right\
    \ half first \n     */\n    int range_right_search(const auto &condition, int\
    \ l = -1, int r = -1) {\n        if (l == -1 && r == -1) l = -1, r = n - 1;\n\
    \        ++l, ++r;\n        assert(0 <= l && r <= n);\n        assert(l <= r);\n\
    \        if (l == r) return l - 1;\n        return range_right_search(l, r, 0,\
    \ n, root, condition);\n    }\n    void range_copy(int l, int r, PointerSegmentTree\
    \ &other) requires (pushdown && persistent) {\n        assert(0 <= l && r <= n);\n\
    \        assert(l <= r);\n        if (l < r)\n            range_copy(l, r, 0,\
    \ n, root, other.root);\n    }\n    void printinfo(int l, int r) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        std::cerr << \"\\e[1;33mInfo\
    \ [\" << l << \", \" << r << \"):\\n\";\n        if (l < r) \n            printinfo(l,\
    \ r, 0, n, root);\n        cerr << \"\\e[0m\\n\";\n    }\n    void printall()\
    \ {\n        std::cerr << \"\\e[1;33mInfo all:\\n\";\n        printall(0, n, root);\n\
    \        cerr << \"\\e[0m\\n\";\n    }\n};\n"
  code: "#pragma once\n\n#include \"DataStructure/DefaultAllocator.hpp\"\n\ntemplate<typename\
    \ Value = int, typename Tag = void, bool pushdown = true, template<typename> class\
    \ Allocator = DefaultAllocator, bool dynamic = false, bool persistent = false>\n\
    class PointerSegmentTree {\n    static constexpr bool hasTag = !std::is_same_v<Tag,\
    \ void>;\n    static constexpr bool hasGet = requires(int l, int r) { Value::get(l,\
    \ r); };\n    static_assert(pushdown || hasTag, \"Lazy tag must exist when pushdown\
    \ is false\");\n    int n;\n    struct Empty {};\n    template <bool Condition,\
    \ typename T>\n    static auto get_default() {\n        if constexpr (Condition)\
    \ return T();\n        else return Empty{};\n    }\n    struct node {\n      \
    \  node *l = nullptr, *r = nullptr;\n        Value val;\n        [[no_unique_address]]\
    \ std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();\n\
    \        Value get_val() {\n            if constexpr (pushdown) return val;\n\
    \            else return val + lazy;\n        }\n        void up() {\n       \
    \     if constexpr (dynamic) {\n                val = Value();\n             \
    \   if (l) val = l->get_val();\n                if (r) val = val + r->get_val();\n\
    \            }\n            else {\n                val = l->get_val() + r->get_val();\n\
    \            }\n        }\n        void up(int lft, int rgt) requires (dynamic\
    \ && hasGet) {\n            if (l) val = l->get_val();\n            else val =\
    \ Value::get(lft, (lft + rgt) / 2);\n            if (r) val = val + r->get_val();\n\
    \            else val = val + Value::get((lft + rgt) / 2, rgt);\n        }\n \
    \       void give_tag(const auto &tag) requires (hasTag) {\n            if constexpr\
    \ (pushdown) val = val + tag;\n            lazy = lazy + tag;\n        }\n   \
    \     void down() requires (hasTag && pushdown) {\n            bool need_tag =\
    \ false;\n            if constexpr (hasTag) { \n                if constexpr (std::equality_comparable<Tag>)\
    \ need_tag = (lazy != Tag());\n                else need_tag = true;\n       \
    \     }\n            if (!need_tag) return;\n            if constexpr (persistent)\
    \ {\n                if constexpr (persistent) l = NodeAlloc::allocate(*l);\n\
    \                if constexpr (persistent) r = NodeAlloc::allocate(*r);\n    \
    \        }\n            l->give_tag(lazy);\n            r->give_tag(lazy);\n \
    \           lazy = Tag();\n        }\n        node() = default;\n        node(const\
    \ auto &v) : val(v) {}\n    };\n    node *root = nullptr;\n    using NodeAlloc\
    \ = Allocator<node>;\n    void initialize(int l, int r, node *&p, const vector<Value>\
    \ &data) {\n        if (r - l == 1) \n            return p = NodeAlloc::allocate(data[l]),\
    \ void();\n        p = NodeAlloc::allocate();\n        int mid = (l + r) >> 1;\n\
    \        initialize(l, mid, p->l, data);\n        initialize(mid, r, p->r, data);\n\
    \        p->up();\n    }\n    Value range_prod(int L, int R, int l, int r, node\
    \ *p) {\n        if constexpr (dynamic) {\n            if (!p) {\n           \
    \     if constexpr (hasGet) return Value::get(std::max(L, l), std::min(R, r));\n\
    \                return Value();\n            }\n        }\n        if (L <= l\
    \ && R >= r)\n            return p->get_val();\n        if constexpr (hasTag &&\
    \ pushdown) p->down();\n        int mid = (l + r) >> 1;\n        if constexpr\
    \ (pushdown) {\n            if (R <= mid) return range_prod(L, R, l, mid, p->l);\n\
    \            if (L >= mid) return range_prod(L, R, mid, r, p->r);\n          \
    \  return range_prod(L, R, l, mid, p->l) + range_prod(L, R, mid, r, p->r); \n\
    \        }\n        else {\n            if (R <= mid) return range_prod(L, R,\
    \ l, mid, p->l) + p->lazy;\n            if (L >= mid) return range_prod(L, R,\
    \ mid, r, p->r) + p->lazy;\n            return range_prod(L, R, l, mid, p->l)\
    \ + range_prod(L, R, mid, r, p->r) + p->lazy;\n        }\n    }\n    void check_node(node\
    \ *&p, int l, int r) requires (dynamic || persistent) {\n        bool allocated\
    \ = false; \n        if constexpr (dynamic) if (!p) {\n            allocated =\
    \ true;\n            if constexpr (hasGet) p = NodeAlloc::allocate(Value::get(l,\
    \ r));\n            else p = NodeAlloc::allocate();\n        }\n        if constexpr\
    \ (persistent) if (!allocated) p = NodeAlloc::allocate(*p);\n    }\n    void update(node\
    \ *&p, int l, int r) {\n        if constexpr (dynamic && hasGet) p->up(l, r);\n\
    \        else p->up();\n    }\n    void modify(int x, int l, int r, node *&p,\
    \ const Value &v) {\n        if constexpr (dynamic || persistent) check_node(p,\
    \ l, r);\n        if (r - l == 1)\n            return p->val = v, void();\n  \
    \      if constexpr (hasTag && pushdown) p->down();\n        int mid = (l + r)\
    \ >> 1;\n        if constexpr (pushdown) {\n            if (x < mid) modify(x,\
    \ l, mid, p->l, v);\n            else modify(x, mid, r, p->r, v);\n        }\n\
    \        else {\n            if (x < mid) modify(x, l, mid, p->l, v - p->lazy);\n\
    \            else modify(x, mid, r, p->r, v - p->lazy);\n        }\n        update(p,\
    \ l, r);\n    }\n    void transform(int x, int l, int r, node *&p, const auto\
    \ &func) {\n        if constexpr (dynamic || persistent) check_node(p, l, r);\n\
    \        if (r - l == 1)\n            return func(p->val), void();\n        if\
    \ constexpr (hasTag && pushdown) p->down();\n        int mid = (l + r) >> 1;\n\
    \        if (x < mid) transform(x, l, mid, p->l, func);\n        else transform(x,\
    \ mid, r, p->r, func);\n        update(p, l, r);\n    }\n    void range_transform(int\
    \ L, int R, int l, int r, node *&p, const auto &tag) requires (hasTag) {\n   \
    \     if constexpr (dynamic || persistent) check_node(p, l, r);\n        if (L\
    \ <= l && R >= r)\n            return p->give_tag(tag);\n        if constexpr\
    \ (pushdown) p->down();\n        int mid = (l + r) >> 1;\n        if (L < mid)\
    \ range_transform(L, R, l, mid, p->l, tag);\n        if (R > mid) range_transform(L,\
    \ R, mid, r, p->r, tag);\n        update(p, l, r);\n    }\n    void range_transform_beats(int\
    \ L, int R, int l, int r, node *&p, const auto &tag, const auto &tag_condition,\
    \ auto... tag_sum) requires (hasTag) {\n        if constexpr (dynamic || persistent)\
    \ check_node(p, l, r);\n        if (L <= l && R >= r && tag_condition([&]{ if\
    \ constexpr(pushdown) return p->val; else return p->get_val() + (..., tag_sum);\
    \ }()))\n            return p->give_tag(tag);\n        assert(r - l > 1);\n  \
    \      if constexpr (pushdown) p->down();\n        else ((tag_sum = tag_sum +\
    \ p->lazy), ...);\n        int mid = (l + r) >> 1;\n        if (L < mid) range_transform_beats(L,\
    \ R, l, mid, p->l, tag, tag_condition, tag_sum...);\n        if (R > mid) range_transform_beats(L,\
    \ R, mid, r, p->r, tag, tag_condition, tag_sum...);\n        update(p, l, r);\n\
    \    }\n    int range_left_search(int L, int R, int l, int r, node *p, const auto\
    \ &condition, auto... tag_sum) {\n        if constexpr (!dynamic) if (!p) return\
    \ R;\n        if (r - l == 1) {\n            if (!condition([&]{ if constexpr(pushdown)\
    \ return p->val; else return p->get_val() + (..., tag_sum); }()))\n          \
    \      return R;\n            return l;\n        }\n        int mid = (l + r)\
    \ >> 1;\n        if constexpr (hasTag && pushdown) p->down();\n        if constexpr\
    \ (!pushdown) ((tag_sum = tag_sum + p->lazy), ...);\n        if (L <= l && R >=\
    \ r) {\n            if (p->l && condition([&]{ if constexpr(pushdown) return p->l->val;\
    \ else return p->l->get_val() + (..., tag_sum); }()))\n                return\
    \ range_left_search(L, R, l, mid, p->l, condition, tag_sum...);\n            return\
    \ range_left_search(L, R, mid, r, p->r, condition, tag_sum...);\n        }\n \
    \       int left = R;\n        if (L < mid) left = range_left_search(L, R, l,\
    \ mid, p->l, condition, tag_sum...);\n        if (left == R) {\n            if\
    \ (R > mid) return range_left_search(L, R, mid, r, p->r, condition, tag_sum...);\n\
    \            return R;\n        }\n        return left;\n    }\n    int range_right_search(int\
    \ L, int R, int l, int r, node *p, const auto &condition, auto... tag_sum) {\n\
    \        if constexpr (!dynamic) if (!p) return L - 1;\n        if (r - l == 1)\
    \ {\n            if (!condition([&]{ if constexpr(pushdown) return p->val; else\
    \ return p->get_val() + (..., tag_sum); }()))\n                return L - 1;\n\
    \            return l;\n        }\n        int mid = (l + r) >> 1;\n        if\
    \ constexpr (hasTag && pushdown) p->down();\n        if constexpr (!pushdown)\
    \ ((tag_sum = tag_sum + p->lazy), ...);\n        if (L <= l && R >= r) {\n   \
    \         if (p->r && condition([&]{ if constexpr(pushdown) return p->r->val;\
    \ else return p->r->get_val() + (..., tag_sum); }()))\n                return\
    \ range_right_search(L, R, mid, r, p->r, condition, tag_sum...);\n           \
    \ return range_right_search(L, R, l, mid, p->l, condition, tag_sum...);\n    \
    \    }\n        int right = L - 1;\n        if (R > mid) right = range_right_search(L,\
    \ R, mid, r, p->r, condition, tag_sum...);\n        if (right == L - 1) {\n  \
    \          if (L < mid) return range_right_search(L, R, l, mid, p->l, condition,\
    \ tag_sum...);\n            return L - 1;\n        }\n        return right;\n\
    \    }\n    Value get(int x, int l, int r, node *p) {\n        [[no_unique_address]]\
    \ std::conditional_t<!pushdown, Tag, Empty> tag;\n        while (r - l > 1) {\n\
    \            if constexpr (hasTag && pushdown) p->down();\n            if constexpr\
    \ (!pushdown) tag = tag + p->lazy;\n            int mid = (l + r) >> 1;\n    \
    \        if (x < mid) r = mid, p = p->l;\n            else l = mid, p = p->r;\n\
    \            if constexpr (dynamic || persistent) if (!p) {\n                if\
    \ constexpr (hasGet) return Value::get(x, x + 1) + tag;\n                else\
    \ return Value() + tag;\n            }\n        }\n        if constexpr (pushdown)\
    \ return p->val;\n        else return p->get_val() + tag;\n    }\n    void range_copy(int\
    \ L, int R, int l, int r, node *&p, node *&q) requires (pushdown && persistent)\
    \ {\n        if (L <= l && R >= r)\n            return p = q, void();\n      \
    \  if constexpr (dynamic || persistent) check_node(p, l, r);\n        if constexpr\
    \ (hasTag && pushdown) p->down(), q->down();\n        int mid = (l + r) >> 1;\n\
    \        if (L < mid) range_copy(L, R, l, mid, p->l, q->l);\n        if (R > mid)\
    \ range_copy(L, R, mid, r, p->r, q->r);\n        update(p, l, r);\n    }\n   \
    \ void printnode(int l, int r, node *p) {\n        std::cerr << \"[\" << l <<\
    \ \", \" << r << \"): \";\n        if constexpr (hasTag) std::cerr << \"val =\
    \ \" << p->val << \", tag = \" << p->lazy;\n        else std::cerr << p->val;\n\
    \        std::cerr << \"\\n\";\n    }\n    void printinfo(int L, int R, int l,\
    \ int r, node *p) {\n        printnode(l, r, p);\n        if (L <= l && R >= r)\n\
    \            return;\n        int mid = (l + r) >> 1;\n        if (L < mid) printinfo(L,\
    \ R, l, mid, p->l);\n        if (R > mid) printinfo(L, R, mid, r, p->r);\n   \
    \ }\n    void printall(int l, int r, node *p) {\n        printnode(l, r, p);\n\
    \        if (r - l == 1) return;\n        int mid = (l + r) >> 1;\n        printall(l,\
    \ mid, p->l);\n        printall(mid, r, p->r);\n    }\npublic:\n    PointerSegmentTree(const\
    \ vector<Value> &data): n(data.size()), root(nullptr) { \n        initialize(0,\
    \ n, root, data);\n    }\n    PointerSegmentTree(int size) requires (!dynamic)\
    \ : PointerSegmentTree(vector<Value>(size)) {}\n    PointerSegmentTree(int size\
    \ = 0) requires (dynamic || persistent) : n(size), root(nullptr) {}\n    Value\
    \ get(int x) {\n        assert(0 <= x && x < n);\n        return get(x, 0, n,\
    \ root);\n    }\n    Value range_prod(int l, int r) {\n        assert(0 <= l &&\
    \ r <= n);\n        assert(l <= r);\n        if (l == r) return Value();\n   \
    \     return range_prod(l, r, 0, n, root);\n    }\n    void modify(int x, const\
    \ Value &v) {\n        assert(0 <= x && x < n);\n        modify(x, 0, n, root,\
    \ v);\n    }\n    void transform(int x, const auto &func) {\n        assert(0\
    \ <= x && x < n);\n        transform(x, 0, n, root, func);\n    }\n    void range_transform(int\
    \ l, int r, const auto &tag) requires (hasTag) {\n        assert(0 <= l && r <=\
    \ n);\n        assert(l <= r);\n        if (l < r)\n            range_transform(l,\
    \ r, 0, n, root, tag);\n    }\n    void range_transform_beats(int l, int r, const\
    \ auto &tag, const auto &tag_condition) requires (hasTag) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        if (l < r)\n            range_transform_beats(l,\
    \ r, 0, n, root, tag, tag_condition);\n    }\n    /*\n       For the given element\
    \ range [l, r)\n       Perform segment tree binary search within the range with\
    \ left half first \n       return fail if the node is empty\n     */\n    int\
    \ range_left_search(const auto &condition, int l = -1, int r = -1) {\n       \
    \ if (l == -1 && r == -1) l = 0, r = n;\n        assert(0 <= l && r <= n);\n \
    \       assert(l <= r);\n        if (l == r) return r;\n        return range_left_search(l,\
    \ r, 0, n, root, condition);\n    }\n    /*\n       For the given element range\
    \ (l, r]\n       Perform segment tree binary search within the range with right\
    \ half first \n     */\n    int range_right_search(const auto &condition, int\
    \ l = -1, int r = -1) {\n        if (l == -1 && r == -1) l = -1, r = n - 1;\n\
    \        ++l, ++r;\n        assert(0 <= l && r <= n);\n        assert(l <= r);\n\
    \        if (l == r) return l - 1;\n        return range_right_search(l, r, 0,\
    \ n, root, condition);\n    }\n    void range_copy(int l, int r, PointerSegmentTree\
    \ &other) requires (pushdown && persistent) {\n        assert(0 <= l && r <= n);\n\
    \        assert(l <= r);\n        if (l < r)\n            range_copy(l, r, 0,\
    \ n, root, other.root);\n    }\n    void printinfo(int l, int r) {\n        assert(0\
    \ <= l && r <= n);\n        assert(l <= r);\n        std::cerr << \"\\e[1;33mInfo\
    \ [\" << l << \", \" << r << \"):\\n\";\n        if (l < r) \n            printinfo(l,\
    \ r, 0, n, root);\n        cerr << \"\\e[0m\\n\";\n    }\n    void printall()\
    \ {\n        std::cerr << \"\\e[1;33mInfo all:\\n\";\n        printall(0, n, root);\n\
    \        cerr << \"\\e[0m\\n\";\n    }\n};\n"
  dependsOn:
  - DataStructure/DefaultAllocator.hpp
  isVerificationFile: false
  path: DataStructure/PointerSegmentTree.hpp
  requiredBy: []
  timestamp: '2026-05-06 01:14:34+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/point_set_range_frequency.test.cpp
  - test/1_library_checker/data_structure/range_affine_range_sum_pointer.test.cpp
  - test/1_library_checker/data_structure/point_set_range_composite_pointer.test.cpp
  - test/1_library_checker/data_structure/persistent_range_affine_range_sum.test.cpp
documentation_of: DataStructure/PointerSegmentTree.hpp
layout: document
redirect_from:
- /library/DataStructure/PointerSegmentTree.hpp
- /library/DataStructure/PointerSegmentTree.hpp.html
title: DataStructure/PointerSegmentTree.hpp
---
