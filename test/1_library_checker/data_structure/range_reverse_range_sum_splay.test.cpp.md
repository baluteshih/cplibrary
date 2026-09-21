---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Algebra/Monoid/sized_value.hpp
    title: Algebra/Monoid/sized_value.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/range_reverse_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_reverse_range_sum
  bundledCode: "#line 1 \"test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\n\
    #line 2 \"assumption.hpp\"\n\n#include <cassert>\n#include <bits/stdc++.h>\n#line\
    \ 3 \"test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp\"\
    \n\n#line 2 \"DataStructure/Splay.hpp\"\n\n#line 2 \"DataStructure/DefaultAllocator.hpp\"\
    \n\ntemplate<typename T>\nstruct DefaultAllocator {\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        return new T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { delete p; }\n};\n#line 2 \"Algebra/ValidOperation.hpp\"\
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
    \    struct node {\n        node *l = nullptr, *r = nullptr, *f = nullptr;\n \
    \       [[no_unique_address]] std::conditional_t<hasKey, Key, Empty> key = get_default<hasKey,\
    \ Key>();\n        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty>\
    \ org = get_default<hasValue, Value>();\n        [[no_unique_address]] std::conditional_t<hasValue,\
    \ Value, Empty> val = get_default<hasValue, Value>();\n        [[no_unique_address]]\
    \ std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();\n\
    \        [[no_unique_address]] std::conditional_t<Rev, int, Empty> rev = get_default<Rev,\
    \ int>();\n        void up() {\n            if constexpr (hasValue) {\n      \
    \          val = org;\n                if (l) val = l->val + org;\n          \
    \      if (r) val = val + r->val;\n            }\n            if (l) l->f = this;\n\
    \            if (r) r->f = this;\n        }\n        void give_tag(const auto\
    \ &tag) requires (hasTag) {\n            if constexpr (hasTagToValue) {\n    \
    \            org = org + tag; \n                val = val + tag;\n           \
    \ }\n            if constexpr (hasTagToKey) {\n                key = key + tag;\n\
    \            }\n            lazy = lazy + tag;\n        }\n        void reverse()\
    \ requires (Rev) {\n            rev ^= 1;\n            if constexpr (hasValueReverse)\
    \ {\n                org.reverse();\n                val.reverse();\n        \
    \    }\n            std::swap(l, r);\n        }\n        void down() requires\
    \ (hasTag || Rev) {\n            bool need_rev = false;\n            if constexpr\
    \ (Rev) need_rev = rev;\n            bool need_tag = false;\n            if constexpr\
    \ (hasTag) { \n                if constexpr (std::equality_comparable<Tag>) need_tag\
    \ = !(lazy == Tag());\n                else need_tag = true;\n            }\n\
    \            if (!need_rev && !need_tag) return;\n            if (l) {\n     \
    \           if constexpr (hasTag) if (need_tag) l->give_tag(lazy);\n         \
    \       if constexpr (Rev) if (need_rev) l->reverse();\n            }\n      \
    \      if (r) {\n                if constexpr (hasTag) if (need_tag) r->give_tag(lazy);\n\
    \                if constexpr (Rev) if (need_rev) r->reverse();\n            }\n\
    \            if constexpr (hasTag) lazy = Tag();\n            if constexpr (Rev)\
    \ rev = 0;\n        }\n        node() = default;\n        node(const auto &v)\
    \ requires (!hasKey || !hasValue) {\n            if constexpr (hasKey) key = Key(v);\n\
    \            else org = val = Value(v);\n        }\n        node(const auto &k,\
    \ const auto &v) requires (hasKey && hasValue) : key(k), org(v), val(v) {}\n \
    \       friend std::ostream& operator<<(std::ostream& os, const node &v) {\n \
    \           if constexpr (hasKey && hasValue) os << \"{key = \" << v.key << \"\
    , org = \" << v.org << \"}\";\n            else if constexpr (hasKey) os << v.key;\n\
    \            else os << v.org;\n            return os;\n        }\n        void\
    \ debuginfo() const {\n            std::cerr << \"\\e[1;33minfo: \";\n       \
    \     auto printnode = [&](std::string name, node* ptr) {\n                std::cerr\
    \ << name << \": \";\n                if (ptr) std::cerr << *ptr;\n          \
    \      else std::cerr << \"null\";\n            };\n            printnode(\"l\"\
    , l), std::cerr << \", \";\n            printnode(\"r\", r), std::cerr << \",\
    \ \";\n            printnode(\"f\", f);\n            std::cerr << \"\\e[0m\\n\"\
    ;\n        }\n    };\n    using NodeAlloc = Allocator<node>;\n    node *root =\
    \ nullptr;\n    static void push_all(node *x) {\n        if (!x) return;\n   \
    \     static std::vector<node*> st;\n        st.clear();\n        node *cur =\
    \ x;\n        while (cur) {\n            st.push_back(cur);\n            cur =\
    \ cur->f;\n        }\n        for (int i = (int)st.size() - 1; i >= 0; --i) {\n\
    \            if constexpr (hasTag || Rev) st[i]->down();\n        }\n    }\n \
    \   static void rotate(node *x) {\n        node *y = x->f, *z = y->f;\n      \
    \  int k = (y->r == x);\n        if (z) (z->l == y ? z->l : z->r) = x;\n     \
    \   x->f = z;\n        node *c = (k ? x->l : x->r);\n        (k ? y->r : y->l)\
    \ = c;\n        if (c) c->f = y;\n        (k ? x->l : x->r) = y;\n        y->f\
    \ = x;\n        y->up();\n        x->up();\n    }\n    static void splay_node(node\
    \ *x, node *goal = nullptr) {\n        if (!x) return;\n        while (x->f !=\
    \ goal) {\n            node *y = x->f, *z = y->f;\n            if (z != goal)\
    \ {\n                if ((z->l == y) ^ (y->l == x)) rotate(x);\n             \
    \   else rotate(y);\n            }\n            rotate(x);\n        }\n    }\n\
    \    static void split(node *source, node *&left, node *&right, const auto &condition)\
    \ {\n        if (!source) return void(left = right = nullptr);\n        node *cur\
    \ = source, *last = nullptr, *split_point = nullptr;\n        while (cur) {\n\
    \            if constexpr (hasTag || Rev) cur->down();\n            last = cur;\n\
    \            if (condition(cur)) {\n                split_point = cur;\n     \
    \           cur = cur->r;\n            }\n            else {\n               \
    \ cur = cur->l;\n            }\n        }\n        if (last) splay_node(last);\n\
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
    \  return res;\n    }\npublic:\n    Splay() = default;\n    Splay(node *root_)\
    \ : root(root_) {}\n    Splay(const auto &v) requires (!hasKey || !hasValue) :\
    \ root(NodeAlloc::allocate(v)) {}\n    Splay(const auto &k, const auto &v) requires\
    \ (hasKey && hasValue) : root(NodeAlloc::allocate(k, v)) {}\n    void destruct()\
    \ { free(root); }\n    void reverse() requires (Rev) {\n        if (root) root->reverse();\n\
    \    }\n    void transform(const auto &tag) requires (hasTag) {\n        if (root)\
    \ root->give_tag(tag);\n    }\n    Splay& left_merge(auto&& left) requires std::same_as<std::decay_t<decltype(left)>,\
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
    \  }\n};\n#line 1 \"Algebra/Monoid/sized_value.hpp\"\ntemplate <typename T, typename\
    \ size_type = int>\nstruct sized_value {\n    T val;\n    size_type sz;\n    sized_value()\
    \ : val(), sz(0) {}\n    sized_value(T v, size_type s = 1) : val(v), sz(s) {}\n\
    \    sized_value operator+(const sized_value &rhs) const {\n        return sized_value(val\
    \ + rhs.val, sz + rhs.sz);\n    }\n    template <typename Tag>\n    sized_value\
    \ operator+(const Tag &tag) const {\n        if constexpr (requires { val.apply(tag,\
    \ sz); }) {\n            return sized_value(val.apply(tag, sz), sz);\n       \
    \ }\n        else if constexpr (requires { val + tag; }) {\n            return\
    \ sized_value(val + tag, sz);\n        }\n        else {\n            static_assert(!sizeof(Tag*),\
    \ \"Type T must implement either apply(Tag, size_type) or operator+(Tag)\");\n\
    \            return *this;\n        }\n    }\n    size_type size() const { return\
    \ sz; }\n    friend std::ostream& operator<<(std::ostream& os, const sized_value\
    \ &v) requires requires(std::ostream& out, const T& inner_val) { out << inner_val;\
    \ } {\n        os << v.val << \" \" << v.sz;\n        return os;\n    }\n};\n\
    #line 6 \"test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp\"\
    \n\nstruct Value {\n    long long sum;\n    Value(long long sum_ = 0): sum(sum_)\
    \ {}\n    Value operator+(const Value &rhs) const {\n        return Value(sum\
    \ + rhs.sum);\n    }\n    friend std::ostream& operator<<(std::ostream& os, const\
    \ Value &v) {\n        os << v.sum;\n        return os;\n    }\n};\n\nusing val\
    \ = sized_value<Value>;\nusing splay = Splay<void, val, void, true>;\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    splay tree;\n    for (int i = 0; i < n; ++i) {\n        int\
    \ x;\n        std::cin >> x;\n        tree.push_back(val(x, 1));\n    }\n    while\
    \ (q--) {\n        int op, l, r;\n        std::cin >> op >> l >> r;\n        if\
    \ (op == 0)\n            tree.range_reverse(l, r);\n        else\n           \
    \ std::cout << tree.range_prod(l, r).val << \"\\n\";\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\
    \n#include \"assumption.hpp\"\n\n#include \"DataStructure/Splay.hpp\"\n#include\
    \ \"Algebra/Monoid/sized_value.hpp\"\n\nstruct Value {\n    long long sum;\n \
    \   Value(long long sum_ = 0): sum(sum_) {}\n    Value operator+(const Value &rhs)\
    \ const {\n        return Value(sum + rhs.sum);\n    }\n    friend std::ostream&\
    \ operator<<(std::ostream& os, const Value &v) {\n        os << v.sum;\n     \
    \   return os;\n    }\n};\n\nusing val = sized_value<Value>;\nusing splay = Splay<void,\
    \ val, void, true>;\n\nint main() {\n    std::ios::sync_with_stdio(0), std::cin.tie(0);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    splay tree;\n    for (int i = 0;\
    \ i < n; ++i) {\n        int x;\n        std::cin >> x;\n        tree.push_back(val(x,\
    \ 1));\n    }\n    while (q--) {\n        int op, l, r;\n        std::cin >> op\
    \ >> l >> r;\n        if (op == 0)\n            tree.range_reverse(l, r);\n  \
    \      else\n            std::cout << tree.range_prod(l, r).val << \"\\n\";\n\
    \    }\n}\n"
  dependsOn:
  - assumption.hpp
  - DataStructure/Splay.hpp
  - DataStructure/DefaultAllocator.hpp
  - Algebra/ValidOperation.hpp
  - Algebra/size_value.hpp
  - Algebra/Monoid/sized_value.hpp
  isVerificationFile: true
  path: test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp
  requiredBy: []
  timestamp: '2026-09-22 01:12:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp
layout: document
redirect_from:
- /verify/test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp
- /verify/test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp.html
title: test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp
---
