---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/ValidOperation.hpp
    title: Algebra/ValidOperation.hpp
  - icon: ':heavy_check_mark:'
    path: Algebra/size_value.hpp
    title: Algebra/size_value.hpp
  - icon: ':heavy_check_mark:'
    path: DataStructure/DefaultAllocator.hpp
    title: Default Allocator
  - icon: ':heavy_check_mark:'
    path: DataStructure/Splay.hpp
    title: Splay
  - icon: ':heavy_check_mark:'
    path: Tree/LinkCutTree.hpp
    title: Tree/LinkCutTree.hpp
  - icon: ':heavy_check_mark:'
    path: assumption.hpp
    title: assumption.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum
  bundledCode: "#line 1 \"test/1_library_checker/tree/dynamic_tree_vertex_add_subtree_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum\"\
    \n#line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n\
    #line 3 \"test/1_library_checker/tree/dynamic_tree_vertex_add_subtree_sum.test.cpp\"\
    \n\n#line 2 \"Tree/LinkCutTree.hpp\"\n\n#line 2 \"DataStructure/Splay.hpp\"\n\n\
    #line 2 \"DataStructure/DefaultAllocator.hpp\"\n\ntemplate<typename T>\nstruct\
    \ DefaultAllocator {\n    template<typename... Args>\n    static T* allocate(Args&&...\
    \ args) { \n        return new T(std::forward<Args>(args)...);\n    }\n    static\
    \ void deallocate(T* p) { delete p; }\n};\n#line 2 \"Algebra/ValidOperation.hpp\"\
    \n\ntemplate <typename A, typename B>\nconcept Addable = !std::is_void_v<A> &&\
    \ !std::is_void_v<B> && requires(A a, B b) { a + b; };\n\ntemplate <typename A,\
    \ typename B>\nconcept Subtractable = !std::is_void_v<A> && !std::is_void_v<B>\
    \ && requires(A a, B b) { a - b; };\n\ntemplate <typename A, typename B>\nconcept\
    \ Multiplicable = !std::is_void_v<A> && !std::is_void_v<B> && requires(A a, B\
    \ b) { a * b; };\n#line 2 \"Algebra/size_value.hpp\"\n\nstruct size_v {\n    int\
    \ sz;\n    size_v(int sz_ = 0): sz(sz_) {}\n    size_v operator+(const size_v\
    \ &rhs) const {\n        return size_v(sz + rhs.sz);\n    }\n    int size() const\
    \ {\n        return sz; \n    }\n    friend std::ostream& operator<<(std::ostream&\
    \ os, const size_v &v) {\n        os << v.sz;\n        return os;\n    }\n};\n\
    #line 6 \"DataStructure/Splay.hpp\"\n\ntemplate<typename Key = void, \n      \
    \   typename Value = size_v,\n         typename Tag = void, \n         bool Rev\
    \ = false,\n         template<typename> class Allocator = DefaultAllocator\n>\n\
    class Splay {\n    static constexpr bool hasKey = !std::is_void_v<Key>;\n    static\
    \ constexpr bool hasValue = !std::is_void_v<Value>;\n    static constexpr bool\
    \ hasTag = !std::is_void_v<Tag>;\n    static constexpr bool hasTagToKey = Addable<Key,\
    \ Tag>;\n    static constexpr bool hasTagToValue = Addable<Value, Tag>;\n    static\
    \ constexpr bool hasSize = requires(Value v) { v.size(); };\n    static constexpr\
    \ bool hasValueReverse = requires(Value v) { v.reverse(); };\n    struct Empty\
    \ {};\n    template <bool Condition, typename T>\n    static auto get_default()\
    \ {\n        if constexpr (Condition) return T();\n        else return Empty{};\n\
    \    }\n    static_assert(hasKey || hasValue);\n    static_assert(!hasValue ||\
    \ Addable<Value, Value>);\n    static_assert(!hasTag || Addable<Tag, Tag>);\n\
    public:\n    struct node {\n        node *l = nullptr, *r = nullptr, *f = nullptr;\n\
    \        [[no_unique_address]] std::conditional_t<hasKey, Key, Empty> key = get_default<hasKey,\
    \ Key>();\n        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty>\
    \ org = get_default<hasValue, Value>();\n        [[no_unique_address]] std::conditional_t<hasValue,\
    \ Value, Empty> val = get_default<hasValue, Value>();\n        [[no_unique_address]]\
    \ std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();\n\
    \        [[no_unique_address]] std::conditional_t<Rev, int, Empty> rev = get_default<Rev,\
    \ int>();\n        bool is_root() const {\n            return f == nullptr ||\
    \ (f->l != this && f->r != this);\n        }\n        void up() {\n          \
    \  if constexpr (hasValue) {\n                val = org;\n                if (l)\
    \ val = l->val + val;\n                if (r) val = val + r->val;\n          \
    \  }\n            if (l) l->f = this;\n            if (r) r->f = this;\n     \
    \   }\n        void give_tag(const auto &tag) requires (hasTag) {\n          \
    \  if constexpr (hasTagToValue) {\n                org = org + tag; \n       \
    \         val = val + tag;\n            }\n            if constexpr (hasTagToKey)\
    \ {\n                key = key + tag;\n            }\n            lazy = lazy\
    \ + tag;\n        }\n        void reverse() requires (Rev) {\n            rev\
    \ ^= 1;\n            if constexpr (hasValueReverse) {\n                org.reverse();\n\
    \                val.reverse();\n            }\n            std::swap(l, r);\n\
    \        }\n        void down() requires (hasTag || Rev) {\n            bool need_rev\
    \ = false;\n            if constexpr (Rev) need_rev = rev;\n            bool need_tag\
    \ = false;\n            if constexpr (hasTag) { \n                if constexpr\
    \ (std::equality_comparable<Tag>) need_tag = !(lazy == Tag());\n             \
    \   else need_tag = true;\n            }\n            if (!need_rev && !need_tag)\
    \ return;\n            if (l) {\n                if constexpr (hasTag) if (need_tag)\
    \ l->give_tag(lazy);\n                if constexpr (Rev) if (need_rev) l->reverse();\n\
    \            }\n            if (r) {\n                if constexpr (hasTag) if\
    \ (need_tag) r->give_tag(lazy);\n                if constexpr (Rev) if (need_rev)\
    \ r->reverse();\n            }\n            if constexpr (hasTag) lazy = Tag();\n\
    \            if constexpr (Rev) rev = 0;\n        }\n        node() = default;\n\
    \        node(const auto &v) requires (!hasKey || !hasValue) {\n            if\
    \ constexpr (hasKey) key = Key(v);\n            else org = val = Value(v);\n \
    \       }\n        node(const auto &k, const auto &v) requires (hasKey && hasValue)\
    \ : key(k), org(v), val(v) {}\n        friend std::ostream& operator<<(std::ostream&\
    \ os, const node &v) {\n            if constexpr (hasKey && hasValue) os << \"\
    {key = \" << v.key << \", org = \" << v.org << \"}\";\n            else if constexpr\
    \ (hasKey) os << v.key;\n            else os << v.org;\n            return os;\n\
    \        }\n        void debuginfo() const {\n            std::cerr << \"\\e[1;33minfo:\
    \ \";\n            auto printnode = [&](std::string name, node* ptr) {\n     \
    \           std::cerr << name << \": \";\n                if (ptr) std::cerr <<\
    \ *ptr;\n                else std::cerr << \"null\";\n            };\n       \
    \     printnode(\"l\", l), std::cerr << \", \";\n            printnode(\"r\",\
    \ r), std::cerr << \", \";\n            printnode(\"f\", f);\n            std::cerr\
    \ << \"\\e[0m\\n\";\n        }\n    };\n    using NodeAlloc = Allocator<node>;\n\
    \    node *root = nullptr;\n    static void push_all(node *x) {\n        if (!x)\
    \ return;\n        static std::vector<node*> st;\n        st.clear();\n      \
    \  node *cur = x;\n        while (cur) {\n            st.push_back(cur);\n   \
    \         if (cur->is_root()) break;\n            cur = cur->f;\n        }\n \
    \       for (int i = (int)st.size() - 1; i >= 0; --i) {\n            if constexpr\
    \ (hasTag || Rev) st[i]->down();\n        }\n    }\n    static void rotate(node\
    \ *x) {\n        node *y = x->f, *z = y->f;\n        int k = (y->r == x);\n  \
    \      if (!y->is_root()) (z->l == y ? z->l : z->r) = x;\n        x->f = z;\n\
    \        node *c = (k ? x->l : x->r);\n        (k ? y->r : y->l) = c;\n      \
    \  if (c) c->f = y;\n        (k ? x->l : x->r) = y;\n        y->f = x;\n     \
    \   y->up();\n        x->up();\n    }\n    static void splay_node(node *x, node\
    \ *goal = nullptr) {\n        if (!x) return;\n        while (x->f != goal &&\
    \ !x->is_root()) {\n            node *y = x->f, *z = y->f;\n            if (y->f\
    \ != goal && !y->is_root()) {\n                if ((z->l == y) ^ (y->l == x))\
    \ rotate(x);\n                else rotate(y);\n            }\n            rotate(x);\n\
    \        }\n    }\n    static void split(node *source, node *&left, node *&right,\
    \ const auto &condition) {\n        if (!source) return void(left = right = nullptr);\n\
    \        node *cur = source, *last = nullptr, *split_point = nullptr;\n      \
    \  while (cur) {\n            if constexpr (hasTag || Rev) cur->down();\n    \
    \        last = cur;\n            if (condition(cur)) {\n                split_point\
    \ = cur;\n                cur = cur->r;\n            }\n            else {\n \
    \               cur = cur->l;\n            }\n        }\n        if (last) splay_node(last);\n\
    \        if (split_point) {\n            splay_node(split_point); \n         \
    \   left = split_point;\n            right = left->r;\n            if (right)\
    \ right->f = nullptr;\n            left->r = nullptr;\n            left->up();\n\
    \        }\n        else {\n            left = nullptr;\n            right = last;\n\
    \        }\n    }\n    static void split_value(node *source, node *&left, node\
    \ *&right, const auto &condition) requires (hasValue) {\n        if (!source)\
    \ return void(left = right = nullptr);\n        node *cur = source, *last = nullptr,\
    \ *split_point = nullptr;\n        Value left_product = Value();\n        while\
    \ (cur) {\n            if constexpr (hasTag || Rev) cur->down();\n           \
    \ last = cur;\n            Value current = left_product + get_val(cur->l) + cur->org;\
    \ \n            if (condition(current)) {\n                split_point = cur;\n\
    \                left_product = current;\n                cur = cur->r;\n    \
    \        }\n            else {\n                cur = cur->l;\n            }\n\
    \        }\n        if (last) splay_node(last);\n        if (split_point) {\n\
    \            splay_node(split_point);\n            left = split_point;\n     \
    \       right = left->r;\n            if (right) right->f = nullptr;\n       \
    \     left->r = nullptr;\n            left->up();\n        }\n        else {\n\
    \            left = nullptr;\n            right = last;\n        }\n    }\n  \
    \  static Value prefix_product(node *&source, const auto &condition) requires\
    \ (hasValue) {\n        if (!source) return Value();\n        node *cur = source,\
    \ *last = nullptr;\n        Value res = Value();\n        while (cur) {\n    \
    \        if constexpr (hasTag || Rev) cur->down();\n            last = cur;\n\
    \            if (condition(cur)) {\n                res = res + get_val(cur->l)\
    \ + cur->org;\n                cur = cur->r;\n            }\n            else\
    \ {\n                cur = cur->l;\n            }\n        }\n        if (last)\
    \ {\n            splay_node(last);\n            source = last;\n        }\n  \
    \      return res;\n    }\n    static Value prefix_product_cond(node *&source,\
    \ const auto &left_product, const auto &condition) requires (hasValue) {\n   \
    \     if (!source) return left_product;\n        node *cur = source, *last = nullptr;\n\
    \        Value current_left = left_product;\n        while (cur) {\n         \
    \   if constexpr (hasTag || Rev) cur->down();\n            last = cur;\n     \
    \       Value current = current_left + get_val(cur->l) + cur->org;\n         \
    \   if (condition(current)) {\n                current_left = current;\n     \
    \           cur = cur->r;\n            }\n            else {\n               \
    \ cur = cur->l;\n            }\n        }\n        if (last) {\n            splay_node(last);\n\
    \            source = last;\n        }\n        return current_left;\n    }\n\
    \    static node *merge(node *left, node *right) {\n        if (!left || !right)\
    \ return left ? left : right;\n        node *mx = find_max(left);\n        splay_node(mx);\n\
    \        mx->r = right;\n        right->f = mx;\n        mx->up();\n        return\
    \ mx;\n    }\n    static auto get_key(node *a, auto Default = Key()) requires\
    \ (hasKey) { return a ? a->key : Default; }\n    static Value get_org(node *a,\
    \ Value Default = Value()) requires (hasValue) { return a ? a->org : Default;\
    \ }\n    static Value get_val(node *a, Value Default = Value()) requires (hasValue)\
    \ { return a ? a->val : Default; }\n    static size_t get_size(node *a) requires\
    \ (hasSize) { return a ? a->val.size() : 0; }\n    static void free(node *&ptr)\
    \ {\n        if (ptr == nullptr) return;\n        free(ptr->l);\n        free(ptr->r);\n\
    \        NodeAlloc::deallocate(ptr);\n        ptr = nullptr;\n    }\n    static\
    \ node* find_min(node *start) {\n        if (!start) return nullptr;\n       \
    \ node *res = start;\n        while (true) {\n            if constexpr (hasTag\
    \ || Rev) res->down();\n            if (res->l) res = res->l;\n            else\
    \ break;\n        }\n        return res;\n    }\n    static node* find_max(node\
    \ *start) {\n        if (!start) return nullptr;\n        node *res = start;\n\
    \        while (true) {\n            if constexpr (hasTag || Rev) res->down();\n\
    \            if (res->r) res = res->r;\n            else break;\n        }\n \
    \       return res;\n    }\n    static node* find_kth(node *&source, int k) requires\
    \ (hasSize) {\n        node *cur = source, *last = nullptr;\n        while (cur)\
    \ {\n            if constexpr (hasTag || Rev) cur->down();\n            last =\
    \ cur;\n            int l_sz = get_size(cur->l);\n            if (k < l_sz) {\n\
    \                cur = cur->l;\n            }\n            else if (k == l_sz)\
    \ {\n                break;\n            }\n            else {\n             \
    \   k -= l_sz + 1;\n                cur = cur->r;\n            }\n        }\n\
    \        if (cur) {\n            splay_node(cur);\n            source = cur;\n\
    \            return cur;\n        }\n        else if (last) {\n            splay_node(last);\n\
    \            source = last;\n        }\n        return nullptr;\n    }\n    static\
    \ node* find_next(node *ptr) {\n        assert(ptr != nullptr);\n        push_all(ptr);\n\
    \        if (ptr->r != nullptr) return find_min(ptr->r);\n        while (ptr->f\
    \ != nullptr && ptr->f->r == ptr) ptr = ptr->f;\n        return ptr->f;\n    }\n\
    \    static node* find_prev(node *ptr) {\n        assert(ptr != nullptr);\n  \
    \      push_all(ptr);\n        if (ptr->l != nullptr) return find_max(ptr->l);\n\
    \        while (ptr->f != nullptr && ptr->f->l == ptr) ptr = ptr->f;\n       \
    \ return ptr->f;\n    }\n    node *find(const auto &condition) {\n        node\
    \ *cur = root, *res = nullptr, *last = nullptr;\n        while (cur != nullptr)\
    \ {\n            if constexpr (hasTag || Rev) cur->down();\n            last =\
    \ cur;\n            if (condition(cur)) cur = cur->r;\n            else {\n  \
    \              res = cur;\n                cur = cur->l;\n            }\n    \
    \    }\n        if (last) { splay_node(last); root = last; }\n        if (res\
    \ && res != last) { splay_node(res); root = res; }\n        return res;\n    }\n\
    \    node *find_value(const auto &condition) requires (hasValue) {\n        node\
    \ *cur = root, *res = nullptr, *last = nullptr;\n        Value left_product =\
    \ Value();\n        while (cur != nullptr) {\n            if constexpr (hasTag\
    \ || Rev) cur->down();\n            last = cur;\n            Value current = left_product\
    \ + get_val(cur->l) + cur->org; \n            if (condition(current)) {\n    \
    \            cur = cur->r;\n                left_product = current;\n        \
    \    }\n            else {\n                res = cur;\n                cur =\
    \ cur->l;\n            }\n        }\n        if (res) { splay_node(res); root\
    \ = res; }\n        else if (last) { splay_node(last); root = last; }\n      \
    \  return res;\n    }\n    Splay() = default;\n    Splay(node *root_) : root(root_)\
    \ {}\n    Splay(const auto &v) requires (!hasKey || !hasValue) : root(NodeAlloc::allocate(v))\
    \ {}\n    Splay(const auto &k, const auto &v) requires (hasKey && hasValue) :\
    \ root(NodeAlloc::allocate(k, v)) {}\n    void destruct() { free(root); }\n  \
    \  void reverse() requires (Rev) {\n        if (root) root->reverse();\n    }\n\
    \    void transform(const auto &tag) requires (hasTag) {\n        if (root) root->give_tag(tag);\n\
    \    }\n    Splay& left_merge(auto&& left) requires std::same_as<std::decay_t<decltype(left)>,\
    \ Splay> {\n        root = merge(left.root, root);\n        left.root = nullptr;\n\
    \        return *this;\n    }\n    Splay& right_merge(auto&& right) requires std::same_as<std::decay_t<decltype(right)>,\
    \ Splay> {\n        root = merge(root, right.root);\n        right.root = nullptr;\n\
    \        return *this;\n    }\n    static Splay merge(auto&& left, auto&& right)\
    \ \n        requires (std::same_as<std::decay_t<decltype(left)>, Splay> &&\n \
    \                 std::same_as<std::decay_t<decltype(right)>, Splay>) {\n    \
    \    Splay res(merge(left.root, right.root));\n        left.root = right.root\
    \ = nullptr;\n        return res;\n    }\n    void swap(Splay &rhs) { std::swap(root,\
    \ rhs.root); }\n    bool empty() const { return root == nullptr; }\n    int size()\
    \ const requires (hasSize) { return get_size(root); }\n    void push_back(const\
    \ auto &v) { right_merge(Splay(v)); }\n    void push_back(const auto &k, const\
    \ auto &v) requires (hasKey && hasValue) { right_merge(Splay(k, v)); }\n    void\
    \ push_front(const auto &v) { left_merge(Splay(v)); }\n    void push_front(const\
    \ auto &k, const auto &v) requires (hasKey && hasValue) { left_merge(Splay(k,\
    \ v)); }\n    struct Iterator {\n        using iterator_category = std::bidirectional_iterator_tag;\n\
    \        using difference_type   = std::ptrdiff_t;\n        using reference  \
    \       = const node&;\n        using value_type        = node;\n        using\
    \ pointer           = node*; \n        Iterator(node* ptr, Splay *tree) : m_ptr(ptr),\
    \ m_tree(tree) {}\n        reference operator*() const { return *m_ptr; }\n  \
    \      auto operator->() const { return m_ptr; }\n        \n        Iterator&\
    \ operator++() {\n            m_ptr = find_next(m_ptr);\n            return *this;\n\
    \        }\n        Iterator operator++(int) {\n            Iterator tmp = *this;\n\
    \            ++(*this);\n            return tmp;\n        }\n        Iterator&\
    \ operator--() {\n            if (m_ptr == nullptr) m_ptr = find_max(m_tree->root);\n\
    \            else m_ptr = find_prev(m_ptr);\n            return *this;\n     \
    \   }\n        Iterator operator--(int) {\n            Iterator tmp = *this;\n\
    \            --(*this);\n            return tmp;\n        }\n        friend bool\
    \ operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr;\
    \ };\n        friend bool operator!= (const Iterator& a, const Iterator& b) {\
    \ return a.m_ptr != b.m_ptr; };\n        void access_ptr() { push_all(m_ptr);\
    \ }\n    private:\n        node* m_ptr;\n        Splay* m_tree;\n        friend\
    \ class Splay;\n    };\n    Iterator begin() { return Iterator(find_min(root),\
    \ this); }\n    Iterator end() { return Iterator(nullptr, this); }\n    Iterator\
    \ rbegin() { return Iterator(find_max(root), this); }\n    void splay(Iterator\
    \ it) {\n        if (it != end()) {\n            node *x = it.operator->();\n\
    \            push_all(x);\n            splay_node(x);\n            root = x;\n\
    \        }\n    }\n    Iterator bound_condition(const auto &condition) { return\
    \ Iterator(find(condition), this); }\n    Iterator bound_condition_value(const\
    \ auto &condition) requires (hasValue) { return Iterator(find_value(condition),\
    \ this); }\n    template<typename K, typename Comp = std::less<Key>>\n    Iterator\
    \ lower_bound(const K &k, const Comp &cmp = Comp()) requires (hasKey) {\n    \
    \    return Iterator(find([&k, &cmp](node *src) { return cmp(src->key, k); }),\
    \ this);\n    }\n    template<typename K, typename Comp = std::less<Key>>\n  \
    \  Iterator upper_bound(const K &k, const Comp &cmp = Comp()) requires (hasKey)\
    \ {\n        return Iterator(find([&k, &cmp](node *src) { return !cmp(k, src->key);\
    \ }), this);\n    }\n    template<typename V, typename Comp = std::less<Value>>\n\
    \    Iterator lower_bound_value(const V &v, const Comp &cmp = Comp()) requires\
    \ (hasValue) {\n        return Iterator(find_value([&v, &cmp](const Value &src)\
    \ { return cmp(src, v); }), this);\n    }\n    template<typename V, typename Comp\
    \ = std::less<Value>>\n    Iterator upper_bound_value(const V &v, const Comp &cmp\
    \ = Comp()) requires (hasValue) {\n        return Iterator(find_value([&v, &cmp](const\
    \ Value &src) { return !cmp(v, src); }), this);\n    }\n    void erase(Iterator\
    \ it) {\n        if (it == end()) return;\n        node *target = it.operator->();\n\
    \        splay_node(target);\n        if (target->l) target->l->f = nullptr;\n\
    \        if (target->r) target->r->f = nullptr;\n        root = merge(target->l,\
    \ target->r);\n        NodeAlloc::deallocate(target);\n    }\n    Splay split_key(const\
    \ auto &condition) {\n        node *left;\n        split(root, left, root, condition);\n\
    \        return Splay(left);\n    }\n    template<typename K, typename Comp =\
    \ std::less<Key>>\n    Splay split_key_lt(const K &k, const Comp &cmp = Comp())\
    \ requires (hasKey) {\n        return split_key([&k, &cmp](node *src) { return\
    \ cmp(src->key, k); });\n    }\n    template<typename K, typename Comp = std::less<Key>>\n\
    \    Splay split_key_leq(const K &k, const Comp &cmp = Comp()) requires (hasKey)\
    \ {\n        return split_key([&k, &cmp](node *src) { return !cmp(k, src->key);\
    \ });\n    }\n    Splay split_value(const auto &condition) requires (hasValue)\
    \ {\n        node *left;\n        split_value(root, left, root, condition);\n\
    \        return Splay(left);\n    }\n    Splay split_size(const int &k) requires\
    \ (hasSize) {\n        if (k <= 0) return Splay();\n        if (k >= size()) {\n\
    \            Splay left(root);\n            root = nullptr;\n            return\
    \ left;\n        }\n        node *kth_node = find_kth(root, k); \n        node\
    \ *left_root = kth_node->l;\n        if (left_root) left_root->f = nullptr;\n\
    \        kth_node->l = nullptr;\n        kth_node->up();\n        return Splay(left_root);\n\
    \    }\n    Key get_key() requires (hasKey) { return get_key(root); }\n    Value\
    \ product() requires (hasValue) { return get_val(root); }\n    template<typename\
    \ K, typename Comp = std::less<Key>>\n    Value prefix_product_key_lt(const K\
    \ &k, const Comp &cmp = Comp()) requires (hasKey && hasValue) {\n        return\
    \ prefix_product(root, [&k, &cmp](node *src) {\n            return cmp(src->key,\
    \ k);\n        });\n    }\n    template<typename K, typename Comp = std::less<Key>>\n\
    \    Value prefix_product_key_leq(const K &k, const Comp &cmp = Comp()) requires\
    \ (hasKey && hasValue) {\n        return prefix_product(root, [&k, &cmp](node\
    \ *src) {\n            return !cmp(k, src->key);\n        });\n    }\n    Value\
    \ prefix_product_cond(const auto &condition) requires (hasValue) {\n        return\
    \ prefix_product_cond(root, Value(), condition);\n    }\n    std::array<Splay,\
    \ 2> split_range(int l, int r) requires (hasSize) {\n        assert(l <= r);\n\
    \        Splay left = split_size(l);\n        Splay right = split_size(r - l);\n\
    \        swap(right);\n        return {std::move(left), std::move(right)};\n \
    \   }\n    Value range_prod(int l, int r) requires (hasValue && hasSize) {\n \
    \       auto [left, right] = split_range(l, r);\n        Value res = product();\n\
    \        this->left_merge(left).right_merge(right);\n        return res;\n   \
    \ }\n    void range_transform(int l, int r, const auto &tag) requires (hasTag\
    \ && hasSize) {\n        auto [left, right] = split_range(l, r);\n        if (!empty())\
    \ transform(tag);\n        this->left_merge(left).right_merge(right);\n    }\n\
    \    void range_reverse(int l, int r) requires (Rev && hasSize) {\n        auto\
    \ [left, right] = split_range(l, r);\n        if (!empty()) reverse();\n     \
    \   this->left_merge(left).right_merge(right);\n    }\n    Iterator kth(int k)\
    \ requires (hasSize) {\n        return Iterator(find_kth(root, k), this);\n  \
    \  }\n};\n#line 6 \"Tree/LinkCutTree.hpp\"\n\ntemplate <\n    typename Value =\
    \ void,\n    typename Path = void,\n    typename Subtree = void,\n    typename\
    \ Tag = void,\n    bool Rev = true,\n    template<typename> class Allocator =\
    \ DefaultAllocator\n>\nclass LinkCutTree {\n    static constexpr bool hasValue\
    \ = !std::is_void_v<Value>;\n    static constexpr bool hasPath = !std::is_void_v<Path>;\n\
    \    static constexpr bool hasSubtree = !std::is_void_v<Subtree>;\n    static\
    \ constexpr bool hasTag = !std::is_void_v<Tag>;\n    static constexpr bool hasInvertibleTag\
    \ = hasTag && requires(Tag t) { -t; };\n    struct Empty {};\n    using SafeValue\
    \ = std::conditional_t<hasValue, Value, Empty>;\n    using SafeTag = std::conditional_t<hasTag,\
    \ Tag, Empty>;\n    struct CompositeInfo {\n        [[no_unique_address]] std::conditional_t<hasValue,\
    \ Value, Empty> org;\n        [[no_unique_address]] std::conditional_t<hasPath,\
    \ Path, Empty> path_val;\n        [[no_unique_address]] std::conditional_t<hasSubtree,\
    \ Subtree, Empty> sub_val;\n        [[no_unique_address]] std::conditional_t<hasSubtree,\
    \ Subtree, Empty> vir;\n        [[no_unique_address]] std::conditional_t<hasSubtree\
    \ && hasInvertibleTag, Tag, Empty> vir_lazy;\n        CompositeInfo() = default;\n\
    \        CompositeInfo operator+(const CompositeInfo& rhs) const {\n         \
    \   CompositeInfo res;\n            if constexpr (hasPath) res.path_val = this->path_val\
    \ + rhs.path_val;\n            if constexpr (hasSubtree) res.sub_val = this->sub_val\
    \ + rhs.sub_val;\n            return res;\n        }\n        CompositeInfo operator+(const\
    \ SafeTag& t) const requires (hasTag) {\n            CompositeInfo res = *this;\n\
    \            if constexpr (Addable<Value, Tag>) res.org = res.org + t;\n     \
    \       if constexpr (Addable<Path, Tag>) res.path_val = res.path_val + t;\n \
    \           if constexpr (Addable<Subtree, Tag>) res.sub_val = res.sub_val + t;\n\
    \            if constexpr (hasSubtree && hasInvertibleTag) res.vir_lazy = res.vir_lazy\
    \ + t;\n            return res;\n        }\n        void reverse() {\n       \
    \     if constexpr (hasPath && requires { path_val.reverse(); }) path_val.reverse();\n\
    \            if constexpr (hasSubtree && requires { sub_val.reverse(); }) sub_val.reverse();\n\
    \        }\n    };\npublic:\n    using SplayTree = Splay<void, CompositeInfo,\
    \ Tag, Rev, Allocator>;\n    using node = typename SplayTree::node;\n    void\
    \ splay(node* x) {\n        SplayTree::push_all(x);\n        SplayTree::splay_node(x);\n\
    \    }\n    std::vector<node> tr;\n    LinkCutTree(int n = 0) : tr(n) {}\n   \
    \ LinkCutTree(const std::vector<SafeValue>& vals) requires (!std::is_void_v<Value>)\
    \ : tr(vals.size()) {\n        for (size_t i = 0; i < vals.size(); ++i) {\n  \
    \          tr[i].org.org = vals[i];\n            if constexpr (!std::is_void_v<Path>)\
    \ tr[i].org.path_val = Path(vals[i]);\n            if constexpr (!std::is_void_v<Subtree>)\
    \ tr[i].org.sub_val = Subtree(vals[i]);\n            tr[i].up();\n        }\n\
    \    }\n    node* get_node(int x) { return &tr[x]; }\n    const SafeValue& getdata(int\
    \ x) const requires (!std::is_void_v<Value>) {\n        access(x);\n        return\
    \ tr[x].org.org;\n    }\n    void set_val(int x, const SafeValue& v) requires\
    \ (hasValue) {\n        access(x);\n        tr[x].org.org = v;\n        if constexpr\
    \ (hasPath) tr[x].org.path_val = Path(v);\n        if constexpr (hasSubtree) {\n\
    \            if constexpr (hasInvertibleTag) tr[x].org.sub_val = Subtree(v) +\
    \ (tr[x].org.vir + tr[x].org.vir_lazy);\n            else tr[x].org.sub_val =\
    \ Subtree(v) + tr[x].org.vir;\n        }\n        tr[x].up();\n    }\n    void\
    \ transform(int x, const auto& func) {\n        access(x); \n        splay(&tr[x]);\n\
    \        func(tr[x].org.org);\n        if constexpr (hasPath) tr[x].org.path_val\
    \ = Path(tr[x].org.org);\n        if constexpr (hasSubtree) {\n            if\
    \ constexpr (hasInvertibleTag) tr[x].org.sub_val = Subtree(tr[x].org.org) + (tr[x].org.vir\
    \ + tr[x].org.vir_lazy);\n            else tr[x].org.sub_val = Subtree(tr[x].org.org)\
    \ + tr[x].org.vir;\n        }\n        tr[x].up();\n    }\n    int access(int\
    \ x) {\n        node* curr = &tr[x];\n        node* last = nullptr;\n        for\
    \ (node* y = curr; y; y = y->f) {\n            splay(y);\n            if constexpr\
    \ (hasSubtree) {\n                static_assert(Subtractable<Subtree, Subtree>,\
    \ \"Subtree requires operator- to maintain virtual trees\");\n               \
    \ if (last) y->org.vir = y->org.vir - last->val.sub_val;\n                if constexpr\
    \ (hasInvertibleTag) {\n                    if (y->r) y->r->give_tag(-y->org.vir_lazy);\n\
    \                    if (last) last->give_tag(y->org.vir_lazy);\n            \
    \    }\n                if (y->r) y->org.vir = y->org.vir + y->r->val.sub_val;\n\
    \                if constexpr (hasInvertibleTag) y->org.sub_val = Subtree(y->org.org)\
    \ + (y->org.vir + y->org.vir_lazy);\n                else y->org.sub_val = Subtree(y->org.org)\
    \ + y->org.vir;\n            }\n            y->r = last;\n            y->up();\n\
    \            last = y;\n        }\n        splay(curr);\n        return last ?\
    \ static_cast<int>(last - tr.data()) : -1;\n    }\n    int findroot(int x) {\n\
    \        access(x);\n        node* curr = &tr[x];\n        while (true) {\n  \
    \          if constexpr (hasTag || Rev) curr->down();\n            if (curr->l)\
    \ curr = curr->l;\n            else break;\n        }\n        splay(curr);\n\
    \        return curr - &tr[0];\n    }\n    bool is_connected(int x, int y) {\n\
    \        return findroot(x) == findroot(y);\n    }\n    int get_lca(int x, int\
    \ y) {\n        if (!is_connected(x, y)) return -1;\n        access(x);\n    \
    \    return access(y);\n    }\n    void makeroot(int x) requires (Rev) {\n   \
    \     access(x);\n        tr[x].reverse();\n    }\n    void split(int x, int y)\
    \ requires (Rev) {\n        makeroot(x);\n        access(y);\n    }\n    bool\
    \ link(int x, int y) requires (Rev) {\n        makeroot(x);\n        if (findroot(y)\
    \ == x) return false;\n        access(y);\n        splay(&tr[y]);\n        tr[x].f\
    \ = &tr[y];\n        if constexpr (hasSubtree) {\n            if constexpr (hasInvertibleTag)\
    \ {\n                tr[x].give_tag(-tr[y].org.vir_lazy);\n            }\n   \
    \         tr[y].org.vir = tr[y].org.vir + tr[x].val.sub_val;\n            if constexpr\
    \ (hasInvertibleTag) tr[y].org.sub_val = Subtree(tr[y].org.org) + (tr[y].org.vir\
    \ + tr[y].org.vir_lazy);\n            else tr[y].org.sub_val = Subtree(tr[y].org.org)\
    \ + tr[y].org.vir;\n            tr[y].up();\n        }\n        return true;\n\
    \    }\n    bool cut(int x, int y) requires (Rev) {\n        makeroot(x);\n  \
    \      if (findroot(y) != x) return false;\n        access(y);\n        if (tr[y].l\
    \ != &tr[x] || tr[x].r != nullptr) return false;\n        tr[y].l = nullptr;\n\
    \        tr[x].f = nullptr;\n        tr[y].up();\n        return true;\n    }\n\
    \    Path path_query(int x, int y) requires (hasPath && Rev) {\n        makeroot(x);\n\
    \        access(y);\n        splay(&tr[y]);\n        return tr[y].val.path_val;\n\
    \    }\n    void path_transform(int x, int y, const SafeTag& tag) requires (hasPath\
    \ && hasTag && Rev) {\n        makeroot(x);\n        access(y);\n        splay(&tr[y]);\n\
    \        tr[y].give_tag(tag);\n        tr[y].up();\n    }\n    Subtree subtree_query(int\
    \ x) requires (hasSubtree) {\n        access(x);\n        splay(&tr[x]);\n   \
    \     return tr[x].org.sub_val;\n    }\n    void subtree_transform(int x, const\
    \ SafeTag& tag) requires (hasSubtree && hasTag && hasInvertibleTag) {\n      \
    \  access(x);\n        splay(&tr[x]);\n        tr[x].org.org = tr[x].org.org +\
    \ tag;\n        tr[x].org.vir_lazy = tr[x].org.vir_lazy + tag;\n        if constexpr\
    \ (hasPath) tr[x].org.path_val = Path(tr[x].org.org);\n        tr[x].org.sub_val\
    \ = Subtree(tr[x].org.org) + (tr[x].org.vir + tr[x].org.vir_lazy);\n        tr[x].up();\n\
    \    }\n    bool link_directed(int child, int parent) {\n        if (is_connected(child,\
    \ parent)) return false; \n        access(child);\n        splay(&tr[child]);\n\
    \        if (tr[child].l) return false;\n        access(parent);\n        splay(&tr[parent]);\n\
    \        tr[child].f = &tr[parent];\n        if constexpr (hasSubtree) {\n   \
    \         if constexpr (hasInvertibleTag) tr[child].give_tag(-tr[parent].org.vir_lazy);\n\
    \            tr[parent].org.vir = tr[parent].org.vir + tr[child].val.sub_val;\n\
    \            if constexpr (hasInvertibleTag) tr[parent].org.sub_val = Subtree(tr[parent].org.org)\
    \ + (tr[parent].org.vir + tr[parent].org.vir_lazy);\n            else tr[parent].org.sub_val\
    \ = Subtree(tr[parent].org.org) + tr[parent].org.vir;\n            tr[parent].up();\n\
    \        }\n        return true;\n    }\n    bool cut_directed(int child) {\n\
    \        access(child);\n        splay(&tr[child]);\n        if (!tr[child].l)\
    \ return false; \n        tr[child].l->f = nullptr;\n        tr[child].l = nullptr;\n\
    \        tr[child].up();\n        return true;\n    }\n};\n#line 5 \"test/1_library_checker/tree/dynamic_tree_vertex_add_subtree_sum.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int\
    \ n, q;\n    std::cin >> n >> q;\n    std::vector<long long> arr(n);\n    for\
    \ (auto &v : arr) std::cin >> v;\n    LinkCutTree<long long, void, long long>\
    \ lct(arr);\n    for (int i = 1; i < n; ++i) {\n        int u, v;\n        std::cin\
    \ >> u >> v;\n        lct.link(u, v);\n    }\n    while (q--) {\n        int op;\n\
    \        std::cin >> op;\n        if (op == 0) {\n            int u, v, w, x;\n\
    \            std::cin >> u >> v >> w >> x;\n            lct.cut(u, v);\n     \
    \       lct.link(w, x);\n        }\n        else if (op == 1) {\n            int\
    \ p, x;\n            std::cin >> p >> x;\n            lct.transform(p, [&](auto\
    \ &v) {\n                v += x;\n            });\n        }\n        else {\n\
    \            int v, p;\n            std::cin >> v >> p;\n            lct.makeroot(p);\n\
    \            std::cout << lct.subtree_query(v) << \"\\n\";\n        }\n    }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum\"\
    \n#include \"assumption.hpp\"\n\n#include \"Tree/LinkCutTree.hpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    std::vector<long long> arr(n);\n    for (auto &v : arr) std::cin\
    \ >> v;\n    LinkCutTree<long long, void, long long> lct(arr);\n    for (int i\
    \ = 1; i < n; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n       \
    \ lct.link(u, v);\n    }\n    while (q--) {\n        int op;\n        std::cin\
    \ >> op;\n        if (op == 0) {\n            int u, v, w, x;\n            std::cin\
    \ >> u >> v >> w >> x;\n            lct.cut(u, v);\n            lct.link(w, x);\n\
    \        }\n        else if (op == 1) {\n            int p, x;\n            std::cin\
    \ >> p >> x;\n            lct.transform(p, [&](auto &v) {\n                v +=\
    \ x;\n            });\n        }\n        else {\n            int v, p;\n    \
    \        std::cin >> v >> p;\n            lct.makeroot(p);\n            std::cout\
    \ << lct.subtree_query(v) << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - assumption.hpp
  - Tree/LinkCutTree.hpp
  - DataStructure/Splay.hpp
  - DataStructure/DefaultAllocator.hpp
  - Algebra/ValidOperation.hpp
  - Algebra/size_value.hpp
  isVerificationFile: true
  path: test/1_library_checker/tree/dynamic_tree_vertex_add_subtree_sum.test.cpp
  requiredBy: []
  timestamp: '2026-10-03 12:33:30+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/tree/dynamic_tree_vertex_add_subtree_sum.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/tree/dynamic_tree_vertex_add_subtree_sum.test.cpp
- /verify/test/1_library_checker/tree/dynamic_tree_vertex_add_subtree_sum.test.cpp.html
title: test/1_library_checker/tree/dynamic_tree_vertex_add_subtree_sum.test.cpp
---
