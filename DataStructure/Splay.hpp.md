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
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum_splay.test.cpp
    title: test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum_splay.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set_splay.test.cpp
    title: test/1_library_checker/data_structure/ordered_set_splay.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp
    title: test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/Splay.hpp\"\n\n#line 2 \"DataStructure/DefaultAllocator.hpp\"\
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
    \  }\n};\n"
  code: "#pragma once\n\n#include \"DataStructure/DefaultAllocator.hpp\"\n#include\
    \ \"Algebra/ValidOperation.hpp\"\n#include \"Algebra/size_value.hpp\"\n\ntemplate<typename\
    \ Key = void, \n         typename Value = size_v,\n         typename Tag = void,\
    \ \n         bool Rev = false,\n         template<typename> class Allocator =\
    \ DefaultAllocator\n>\nclass Splay {\n    static constexpr bool hasKey = !std::is_void_v<Key>;\n\
    \    static constexpr bool hasValue = !std::is_void_v<Value>;\n    static constexpr\
    \ bool hasTag = !std::is_void_v<Tag>;\n    static constexpr bool hasTagToKey =\
    \ Addable<Key, Tag>;\n    static constexpr bool hasTagToValue = Addable<Value,\
    \ Tag>;\n    static constexpr bool hasSize = requires(Value v) { v.size(); };\n\
    \    static constexpr bool hasValueReverse = requires(Value v) { v.reverse();\
    \ };\n    struct Empty {};\n    template <bool Condition, typename T>\n    static\
    \ auto get_default() {\n        if constexpr (Condition) return T();\n       \
    \ else return Empty{};\n    }\n    static_assert(hasKey || hasValue);\n    static_assert(!hasValue\
    \ || Addable<Value, Value>);\n    static_assert(!hasTag || Addable<Tag, Tag>);\n\
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
    \  }\n};\n"
  dependsOn:
  - DataStructure/DefaultAllocator.hpp
  - Algebra/ValidOperation.hpp
  - Algebra/size_value.hpp
  isVerificationFile: false
  path: DataStructure/Splay.hpp
  requiredBy: []
  timestamp: '2026-09-22 00:37:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/1_library_checker/data_structure/range_reverse_range_sum_splay.test.cpp
  - test/1_library_checker/data_structure/ordered_set_splay.test.cpp
  - test/1_library_checker/data_structure/dynamic_sequence_range_affine_range_sum_splay.test.cpp
documentation_of: DataStructure/Splay.hpp
layout: document
title: Splay
---

A highly flexible self-adjusting binary search tree (Splay Tree). It supports sequences, ordered sets/maps, lazy propagation, and range reversals. Accessed nodes are splayed to the root using tree rotations, achieving amortized $O(\log N)$ time per operation without requiring random priorities or tree height balancing.

## Template Parameters

```cpp
template<
    typename Key = void, 
    typename Value = size_v,
    typename Tag = void, 
    bool Rev = false,
    template<typename> class Allocator = DefaultAllocator
>
class Splay;
```

* `Key`: The type of search keys.
    * Use `void` for sequence-only usage.
* `Value`: The type of elements or range aggregates. Defaults to `size_v`.
    * Must support associative `operator+` for merging (commutative or non-commutative).
    * Must have a default constructor `Value()` acting as the identity element.
    * Requires a member function `size()` for size-based operations.
* `Tag`: The type of lazy tags.
    * Must support `operator+` for tag composition (`Tag + Tag`).
    * Must have a default constructor `Tag()` acting as the identity tag.
    * If `operator+` between `Value` and `Tag` is supported, the lazy tag will be applied to `Value`.
    * If `operator+` between `Key` and `Tag` is supported, the lazy tag will be applied to `Key`.
    * **WARNING**: It is recommended to use a custom struct to implement the `Tag` to prevent unexpected application. 
* `Rev`: If `true`, supports range reversals (`range_reverse`).
    * If `Value` has a `reverse()` member function, it is called for the node value and composed value during propagation.
* `Allocator`: The allocator used for node management. Defaults to `DefaultAllocator`.

---

## Node Structure

The `node` struct contains the following members. Some members are conditionally present based on the template parameters.

```cpp
struct node {
    node *l, *r;
    node *f;
    Key key;        // Present only if Key is not void
    Value org;      // Present only if Value is not void
    Value val;      // Present only if Value is not void
    Tag lazy;       // Present only if Tag is not void
    int rev;        // Present only if Rev is true
};
```

* `l`, `r`: Pointers to the left and right children.
* `f`: Pointer to the parent node. Used for tree rotations and iterator movement.
* `key`: The search key of the current node.
* `org`: The value stored in this node.
* `val`: The aggregate value of the entire subtree rooted at this node (includes `l`, `r`, and `org`).
* `lazy`: The pending lazy tag to be propagated to children.
* `rev`: A flag indicating if the subtree needs to be reversed.

### `operator<<`

```cpp
friend ostream& operator<<(ostream& os, const node &v);
```

* $O(1)$ time (assuming $O(1)$ for `Key` and `Value` output)

Functionalities:
* Outputs the content of the node to the stream.
* If both `Key` and `Value` are present, outputs `{key = ..., org = ...}`. Otherwise, outputs only the present one.

### debuginfo

```cpp
void debuginfo() const;
```

* $O(1)$ time

Functionalities:
* Prints debugging information for the node to `std::cerr`, including its children and parent pointers.

---

## Iterator

The `Iterator` is a bidirectional iterator.

### `operator*` / `operator->`

```cpp
node& operator*() const;
node* operator->() const;
```

* $O(1)$ time

Returns the reference or pointer to the underlying node.

### begin / end / rbegin

```cpp
Iterator begin();
Iterator end();
Iterator rbegin();
```

* Amortized $O(\log N)$ time for `begin` and `rbegin`; $O(1)$ time for `end`

Returns the corresponding iterators for traversing the Splay tree.

### `operator++` / `operator--`

```cpp
Iterator& operator++();
Iterator operator++(int);
Iterator& operator--();
Iterator operator--(int);
```

* Amortized $O(\log N)$ time

Moves the iterator to the next or previous element in in-order traversal. Automatically pushes down pending lazy tags and reverse flags on the path.

### `operator==` / `operator!=`

```cpp
bool operator==(const Iterator& a, const Iterator& b);
bool operator!=(const Iterator& a, const Iterator& b);
```

* $O(1)$ time

Compares two iterators for equality.

### `access_ptr`

```cpp
void access_ptr();
```

* $O(\log N)$ time

Functionalities:
* Ensures all lazy tags and reverse flags on the path from the root to the node pointed by the iterator are propagated.

---

## Searching (Iterators)

These methods return an `Iterator` to a node satisfying specific conditions.

### lower_bound / upper_bound (Key)

```cpp
template<typename K, typename Comp = std::less<Key>>
Iterator lower_bound(const K &k, const Comp &cmp = Comp());

template<typename K, typename Comp = std::less<Key>>
Iterator upper_bound(const K &k, const Comp &cmp = Comp());
```

* Requires `Key` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* `lower_bound` finds the iterator of the node such that:
    * All nodes on its left satisfy `cmp(node->key, k) == true`.
    * All nodes on its right satisfy `cmp(node->key, k) == false`.
    * The node itself satisfies `cmp(node->key, k) == false`.
* `upper_bound` finds the iterator of the node such that:
    * All nodes on its left satisfy `cmp(k, node->key) == false`.
    * All nodes on its right satisfy `cmp(k, node->key) == true`.
    * The node itself satisfies `cmp(k, node->key) == true`.
* Splays the found node (or the last visited node) to the root.

Assumes the Splay tree is ordered by `Key`.

### lower_bound_value / upper_bound_value (Value)

```cpp
template<typename V, typename Comp = std::less<Value>>
Iterator lower_bound_value(const V &v, const Comp &cmp = Comp());

template<typename V, typename Comp = std::less<Value>>
Iterator upper_bound_value(const V &v, const Comp &cmp = Comp());
```

* Requires `Value` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* `lower_bound_value` finds the iterator of the node such that:
    * The product `res` of all nodes on its left satisfies `cmp(res, v) == true`.
    * The node itself satisfies `cmp(res + node->org, v) == false`.
* `upper_bound_value` finds the iterator of the node such that:
    * The product `res` of all nodes on its left satisfies `cmp(v, res) == false`.
    * The node itself satisfies `cmp(v, res + node->org) == true`.
* Splays the found node (or the last visited node) to the root.

Assumes monotonicity of prefix products with respect to the comparison.

### bound_condition

```cpp
Iterator bound_condition(const auto &condition);
Iterator bound_condition_value(const auto &condition);
```

* `bound_condition_value` requires `Value` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* `bound_condition` finds the iterator of the node such that:
    * All nodes on its left satisfy `condition(node*) == true`.
    * All nodes on its right satisfy `condition(node*) == false`.
    * The node itself satisfies `condition(node*) == false`.
* `bound_condition_value` finds the iterator of the node such that:
    * The product `res` of all nodes on its left satisfies `condition(res) == true`.
    * The node itself satisfies `condition(res + node->org) == false`.
* Splays the found node (or the last visited node) to the root.

Assumes a `true, ..., true, false, ..., false` distribution.

### kth

```cpp
Iterator kth(int k);
```

* Requires `size()` member function for `Value`.
* Amortized $O(\log N)$ time

Functionalities:
* Returns the iterator of the node such that:
    * The number of nodes on its left is exactly `k`.
    * The node is the $k$-th element ($0$-based) in the Splay tree.
* Splays the $k$-th node to the root.

---

## Core Operations

### splay

```cpp
void splay(Iterator it);
```

* Amortized $O(\log N)$ time

Functionalities:
* Splays the node pointed to by `it` to the root of the tree using tree rotations.
* Ensures all lazy tags and reverse flags on the path from the root to the node are propagated before rotating.
* If `it == end()`, does nothing.

### merge

```cpp
static Splay merge(auto&& left, auto&& right);
Splay& left_merge(auto&& left);
Splay& right_merge(auto&& right);
```

* Amortized $O(\log N)$ time

Functionalities:
* Merges two Splay trees into one.
* The relative order of nodes in `left` and `right` is preserved, with all nodes from `left` appearing before nodes from `right`.
* Splays the maximum element of `left` to its root, making its right child `nullptr`, then attaches `right` as its right child.
* The original Splay trees passed by move will have their roots set to `nullptr`.

### split

```cpp
Splay split_key(const auto &condition);
template<typename K, typename Comp = std::less<Key>>
Splay split_key_lt(const K &k, const Comp &cmp = Comp());
template<typename K, typename Comp = std::less<Key>>
Splay split_key_leq(const K &k, const Comp &cmp = Comp());
Splay split_value(const auto &condition);
Splay split_size(const int &k);
```

* Amortized $O(\log N)$ time

Functionalities:
* Splits the Splay tree into two parts. Returns a new Splay tree containing the prefix; the remaining suffix stays in the original Splay tree (`*this`).
* `split_key` assumes all nodes satisfying `condition(node*) == true` form a prefix.
* `split_key_lt` assumes all nodes satisfying `cmp(node->key, k) == true` form a prefix. Requires `Key` not to be `void`.
* `split_key_leq` assumes all nodes satisfying `cmp(k, node->key) == false` form a prefix. Requires `Key` not to be `void`.
* `split_value` assumes all nodes satisfying `condition(prefix_product) == true` form a prefix. Requires `Value` not to be `void`.
* `split_size` returns a Splay tree containing the leftmost `k` nodes. Requires `size()` in `Value`.

---

## Modifiers

### push_back / push_front

```cpp
void push_back(const auto &v);
void push_back(const auto &k, const auto &v);
void push_front(const auto &v);
void push_front(const auto &k, const auto &v);
```

* Amortized $O(\log N)$ time

Functionalities:
* Inserts a new node at the end (`push_back`) or at the beginning (`push_front`) of the Splay tree.
* The number of arguments depends on whether `Key` and `Value` are `void`.

### erase

```cpp
void erase(Iterator it);
```

* Amortized $O(\log N)$ time

Functionalities:
* Removes the node pointed to by the iterator from the Splay tree.
* Splays the target node to the root, disconnects its left and right subtrees, merges them, and deallocates the erased node.
* If `it == end()`, does nothing.

### swap

```cpp
void swap(Splay &rhs);
```

* $O(1)$ time

Functionalities:
* Swaps the entire content (root pointer) with another Splay tree.

### transform

```cpp
void transform(const auto &tag);
```

* $O(1)$ time
* Requires `Tag` not to be `void`.

Functionalities:
* Applies the lazy tag `tag` to the entire Splay tree by updating the root's lazy field.

### reverse

```cpp
void reverse();
```

* $O(1)$ time
* Requires `Rev` to be `true`.

Functionalities:
* Reverses the entire Splay tree by toggling the root's reverse flag.

### destruct

```cpp
void destruct();
```

* $O(N)$ time

Functionalities:
* Recursively deallocates all nodes in the Splay tree. Essential for manual memory management when not using a pool allocator.

---

## Range Operations

Requires `size()` member function for `Value`.

### split_range

```cpp
std::array<Splay, 2> split_range(int l, int r);
```

* Amortized $O(\log N)$ time

Functionalities:
* Splits the Splay tree into three parts: `[0, l)`, `[l, r)`, and `[r, N)`.
* The middle range `[l, r)` stays in the original Splay object (`*this`).
* The returned array contains the prefix `[0, l)` and suffix `[r, N)`.

### range_prod

```cpp
Value range_prod(int l, int r);
```

* Requires `Value` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* Returns the aggregate value (product) of all nodes in the range `[l, r)`.

### range_transform

```cpp
void range_transform(int l, int r, const auto &tag);
```

* Requires `Tag` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* Applies the lazy tag `tag` to all nodes in the range `[l, r)`.

### range_reverse

```cpp
void range_reverse(int l, int r);
```

* Requires `Rev` to be `true`.
* Amortized $O(\log N)$ time

Functionalities:
* Reverses the order of elements in the range `[l, r)`.

---

## Queries

### empty

```cpp
bool empty() const;
```

* $O(1)$ time

Functionalities:
* Returns `true` if the Splay tree contains no nodes (`root == nullptr`).

### size

```cpp
int size() const;
```

* $O(1)$ time
* Requires `size()` in `Value`.

Functionalities:
* Returns the total number of elements in the Splay tree.

### get_key

```cpp
Key get_key();
```

* $O(1)$ time
* Requires `Key` not to be `void`.

Functionalities:
* Returns the key stored at the root node.

### product

```cpp
Value product();
```

* $O(1)$ time
* Requires `Value` not to be `void`.

Functionalities:
* Returns the pre-calculated aggregate value (`val`) of the entire Splay tree (stored at the root).

### prefix_product

```cpp
template<typename K, typename Comp = std::less<Key>>
Value prefix_product_key_lt(const K &k, const Comp &cmp = Comp());

template<typename K, typename Comp = std::less<Key>>
Value prefix_product_key_leq(const K &k, const Comp &cmp = Comp());

Value prefix_product_cond(const auto &condition);
```

* Requires `Value` not to be `void`.
* Amortized $O(\log N)$ time

Functionalities:
* `prefix_product_key_lt` returns the product of all nodes with `key < k`. Requires `Key` not to be `void`.
* `prefix_product_key_leq` returns the product of all nodes with `key <= k`. Requires `Key` not to be `void`.
* `prefix_product_cond` returns the product of the longest prefix satisfying `condition(prefix_product)`.
* Splays the last visited node to the root.
* Assumes monotonicity where applicable.
