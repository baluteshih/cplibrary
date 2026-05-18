---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: Algebra/size_value.hpp
    title: Algebra/size_value.hpp
  - icon: ':question:'
    path: DataStructure/DefaultAllocator.hpp
    title: DataStructure/DefaultAllocator.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/ordered_set_treap.test.cpp
    title: test/1_library_checker/data_structure/ordered_set_treap.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/1_library_checker/data_structure/range_reverse_range_sum.test.cpp
    title: test/1_library_checker/data_structure/range_reverse_range_sum.test.cpp
  - icon: ':x:'
    path: test/3_qoj/17153.test.cpp
    title: test/3_qoj/17153.test.cpp
  - icon: ':x:'
    path: test/8_luogu/P3835.test.cpp
    title: test/8_luogu/P3835.test.cpp
  - icon: ':x:'
    path: test/8_luogu/P3835_pool.test.cpp
    title: test/8_luogu/P3835_pool.test.cpp
  - icon: ':x:'
    path: test/8_luogu/P5055.test.cpp
    title: test/8_luogu/P5055.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"DataStructure/Treap.hpp\"\n\n#line 2 \"DataStructure/DefaultAllocator.hpp\"\
    \n\ntemplate<typename T>\nstruct DefaultAllocator {\n    template<typename...\
    \ Args>\n    static T* allocate(Args&&... args) { \n        return new T(std::forward<Args>(args)...);\n\
    \    }\n    static void deallocate(T* p) { delete p; }\n};\n#line 2 \"Algebra/size_value.hpp\"\
    \n\nstruct size_v {\n    int sz;\n    size_v(int sz_ = 0): sz(sz_) {}\n    size_v\
    \ operator+(const size_v &rhs) const {\n        return size_v(sz + rhs.sz);\n\
    \    }\n    int size() const {\n        return sz; \n    }\n    friend ostream&\
    \ operator<<(ostream& os, const size_v &v) {\n        os << v.sz;\n        return\
    \ os;\n    }\n};\n#line 5 \"DataStructure/Treap.hpp\"\n\ntemplate<typename Key\
    \ = void, \n         typename Value = size_v,\n         typename Tag = void, \n\
    \         bool Rev = false,\n         template<typename> class Allocator = DefaultAllocator,\n\
    \         bool persistent = false\n>\nclass Treap {\n    static constexpr bool\
    \ hasKey = !std::is_same_v<Key, void>;\n    static constexpr bool hasValue = !std::is_same_v<Value,\
    \ void>;\n    static constexpr bool hasTag = !std::is_same_v<Tag, void>;\n   \
    \ static constexpr bool usePri = !persistent;\n    static constexpr bool hasSize\
    \ = requires(Value v) { v.size(); };\n    static constexpr bool hasValueReverse\
    \ = requires(Value v) { v.reverse(); };\n    struct Empty {};\n    template <bool\
    \ Condition, typename T>\n    static auto get_default() {\n        if constexpr\
    \ (Condition) return T();\n        else return Empty{};\n    }\n    template <bool\
    \ Condition>\n    static auto get_pri() {\n        if constexpr (Condition) return\
    \ rng();\n        else return Empty{};\n    }\n    static_assert(hasKey || hasValue);\n\
    \    static_assert(!hasTag || hasValue);\n    static inline std::mt19937 rng{880301};\n\
    \    struct node {\n        node *l = nullptr, *r = nullptr;\n        [[no_unique_address]]\
    \ std::conditional_t<!persistent, node*, Empty> f = get_default<!persistent, node*>();\n\
    \        [[no_unique_address]] std::conditional_t<hasKey, Key, Empty> key = get_default<hasKey,\
    \ Key>();\n        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty>\
    \ org = get_default<hasValue, Value>();\n        [[no_unique_address]] std::conditional_t<hasValue,\
    \ Value, Empty> val = get_default<hasValue, Value>();\n        [[no_unique_address]]\
    \ std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();\n\
    \        [[no_unique_address]] std::conditional_t<Rev, int, Empty> rev = get_default<Rev,\
    \ int>();\n        [[no_unique_address]] std::conditional_t<usePri, unsigned,\
    \ Empty> pri = get_pri<usePri>();\n        void up() {\n            if constexpr\
    \ (hasValue) {\n                val = org;\n                if (l) val = l->val\
    \ + org;\n                if (r) val = val + r->val;\n            }\n        \
    \    if constexpr (!persistent) {\n                f = nullptr;\n            \
    \    if (l) l->f = this;\n                if (r) r->f = this;\n            }\n\
    \        }\n        void give_tag(const auto &tag) requires (hasTag) {\n     \
    \       org = org + tag; \n            val = val + tag;\n            lazy = lazy\
    \ + tag;\n        }\n        void reverse() requires (Rev) {\n            rev\
    \ ^= 1;\n            if constexpr (hasValueReverse) {\n                org.reverse();\n\
    \                val.reverse();\n            }\n            std::swap(l, r);\n\
    \        }\n        void down() requires (hasTag || Rev) {\n            bool need_rev\
    \ = false;\n            if constexpr (Rev) need_rev = rev;\n            bool need_tag\
    \ = false;\n            if constexpr (hasTag) { \n                if constexpr\
    \ (std::equality_comparable<Tag>) need_tag = (lazy != Tag());\n              \
    \  else need_tag = true;\n            }\n            if (!need_rev && !need_tag)\
    \ return;\n            if (l) {\n                if constexpr (persistent) l =\
    \ NodeAlloc::allocate(*l);\n                if constexpr (hasTag) if (need_tag)\
    \ l->give_tag(lazy);\n                if constexpr (Rev) if (need_rev) l->reverse();\n\
    \            }\n            if (r) {\n                if constexpr (persistent)\
    \ r = NodeAlloc::allocate(*r);\n                if constexpr (hasTag) if (need_tag)\
    \ r->give_tag(lazy);\n                if constexpr (Rev) if (need_rev) r->reverse();\n\
    \            }\n            if constexpr (hasTag) lazy = Tag();\n            if\
    \ constexpr (Rev) rev = 0;\n        }\n        node() = default;\n        node(const\
    \ auto &v) requires (!hasKey || !hasValue) {\n            if constexpr (hasKey)\
    \ key = Key(v);\n            else org = val = Value(v);\n        }\n        node(const\
    \ auto &k, const auto &v) requires (hasKey && hasValue) : key(k), org(v), val(v)\
    \ {\n        }\n        friend ostream& operator<<(ostream& os, const node &v)\
    \ {\n            if constexpr (hasKey && hasValue) os << \"{key = \" << v.key\
    \ << \", org = \" << v.org << \"}\";\n            else if constexpr (hasKey) os\
    \ << v.key;\n            else os << v.org;\n            return os;\n        }\n\
    \        void debuginfo() const {\n            std::cerr << \"\\e[1;33minfo: \"\
    ;\n            auto printnode = [&](std::string name, node* ptr) {\n         \
    \       std::cerr << name << \": \";\n                if (ptr) std::cerr << *ptr;\n\
    \                else std::cerr << \"null\";\n            };\n            printnode(\"\
    l\", l), std::cerr << \", \";\n            printnode(\"r\", r), std::cerr << \"\
    , \";\n            if constexpr (!persistent) printnode(\"f\", f);\n         \
    \   cerr << \"\\e[0m\\n\";\n        }\n    };\n    using NodeAlloc = Allocator<node>;\n\
    \    node *root = nullptr;\n    static void split(node *source, node *&left, node\
    \ *&right, const auto &condition) {\n        if (!source) return left = right\
    \ = nullptr, void();\n        if constexpr (persistent) source = NodeAlloc::allocate(*source);\
    \ \n        if constexpr (hasTag || Rev) source->down();\n        if (condition(source))\
    \ {\n            left = source;\n            split(source->r, left->r, right,\
    \ condition);\n            left->up();\n        }\n        else {\n          \
    \  right = source;\n            split(source->l, left, right->l, condition);\n\
    \            right->up();\n        }\n    }\n    static void split_value(node\
    \ *source, node *&left, node *&right, const auto &left_product, const auto &condition)\
    \ requires (hasValue) {\n        if (!source) return left = right = nullptr, void();\n\
    \        if constexpr (persistent) source = NodeAlloc::allocate(*source); \n \
    \       if constexpr (hasTag || Rev) source->down();\n        Value current =\
    \ left_product + get_val(source->l) + source->org;\n        if (condition(current))\
    \ {\n            left = source;\n            split_value(source->r, left->r, right,\
    \ current, condition);\n            left->up();\n        }\n        else {\n \
    \           right = source;\n            split_value(source->l, left, right->l,\
    \ left_product, condition);\n            right->up();\n        }\n    }\n    static\
    \ Value prefix_product(node *source, const auto &condition) requires (hasValue)\
    \ {\n        if (!source) return Value();\n        if constexpr (hasTag || Rev)\
    \ source->down();\n        if (condition(source))\n            return get_val(source->l)\
    \ + source->org + prefix_product(source->r, condition);\n        return prefix_product(source->l,\
    \ condition);\n    }\n    static Value prefix_product_cond(node *source, const\
    \ auto &left_product, const auto &condition) requires (hasValue) {\n        if\
    \ (!source) return left_product;\n        if constexpr (hasTag || Rev) source->down();\n\
    \        Value current = left_product + get_val(source->l) + source->org;\n  \
    \      if (condition(current))\n            return prefix_product_cond(source->r,\
    \ current, condition);\n        return prefix_product_cond(source->l, left_product,\
    \ condition);\n    }\n    static node *merge(node *left, node *right) {\n    \
    \    if (!left || !right) return left ? left : right;\n        bool useleft =\
    \ true;\n        if constexpr (usePri)\n            useleft = left->pri < right->pri;\n\
    \        else\n            useleft = rng() % (get_size(left) + get_size(right))\
    \ < size_t(get_size(left));\n        if (useleft) {\n            if constexpr\
    \ (persistent) left = NodeAlloc::allocate(*left); \n            if constexpr (hasTag\
    \ || Rev) left->down();\n            left->r = merge(left->r, right);\n      \
    \      left->up();\n            return left;\n        }\n        if constexpr\
    \ (persistent) right = NodeAlloc::allocate(*right);\n        if constexpr (hasTag\
    \ || Rev) right->down();\n        right->l = merge(left, right->l);\n        right->up();\n\
    \        return right;\n    }\n    static Key get_key(node *a) requires (hasKey)\
    \ {\n        return get_key(a, Key());\n    }\n    static Key get_key(node *a,\
    \ auto Default) requires (hasKey) {\n        return a ? a->key : Default;\n  \
    \  }\n    static Value get_org(node *a) requires (hasValue) {\n        return\
    \ a ? a->org : Value();\n    }\n    static Value get_org(node *a, auto Default)\
    \ requires (hasValue) {\n        return a ? a->org : Default;\n    }\n    static\
    \ Value get_val(node *a) requires (hasValue) {\n        return a ? a->val : Value();\n\
    \    }\n    static Value get_val(node *a, Value Default) requires (hasValue) {\n\
    \        return a ? a->val : Default;\n    }\n    static int get_size(node *a)\
    \ requires (hasSize) { \n        return a ? a->val.size() : 0;\n    }\n    static\
    \ void free(node *&ptr) requires (!persistent) {\n        if (ptr == nullptr)\
    \ return;\n        free(ptr->l);\n        free(ptr->r);\n        delete ptr;\n\
    \        ptr = nullptr;\n    }\n    static node* find_min(node *start) {\n   \
    \     if (!start) return nullptr;\n        node *res = start;\n        while (true)\
    \ {\n            if constexpr (hasTag || Rev) res->down();\n            if (res->l)\
    \ res = res->l;\n            else break;\n        }\n        return res;\n   \
    \ }\n    node* find_min() const {\n        return find_min(root);\n    }\n   \
    \ static node* find_max(node *start) {\n        if (!start) return nullptr;\n\
    \        node *res = start;\n        while (true) {\n            if constexpr\
    \ (hasTag || Rev) res->down();\n            if (res->r) res = res->r;\n      \
    \      else break;\n        }\n        return res;\n    }\n    node* find_max()\
    \ const {\n        return find_max(root);\n    }\n    static void access(node\
    \ *ptr) requires (!persistent) {\n        assert(ptr != nullptr);\n        if\
    \ (ptr->f != nullptr)\n            access(ptr->f);\n        if constexpr (hasTag\
    \ || Rev) ptr->down();\n    }\n    static node* find_next(node *ptr) requires\
    \ (!persistent) {\n        assert(ptr != nullptr);\n        access(ptr);\n   \
    \     if (ptr->r != nullptr)\n            return find_min(ptr->r);\n        while\
    \ (ptr->f != nullptr && ptr->f->r == ptr)\n            ptr = ptr->f;\n       \
    \ if (ptr->f == nullptr) return nullptr;\n        return ptr->f;\n    }\n    static\
    \ node* find_prev(node *ptr) requires (!persistent) {\n        assert(ptr != nullptr);\n\
    \        access(ptr);\n        if (ptr->l != nullptr)\n            return find_max(ptr->l);\n\
    \        while (ptr->f != nullptr && ptr->f->l == ptr)\n            ptr = ptr->f;\n\
    \        assert(ptr->f != nullptr);\n        return ptr->f;\n    }\n    node *find(const\
    \ auto &condition) {\n        node *cur = root, *res = nullptr;\n        while\
    \ (cur != nullptr) {\n            if constexpr (hasTag || Rev) cur->down();\n\
    \            if (condition(cur))\n                cur = cur->r;\n            else\
    \ {\n                res = cur;\n                cur = cur->l;\n            }\n\
    \        }\n        return res;\n    }\n    node *find_value(const auto &condition)\
    \ {\n        node *cur = root, *res = nullptr;\n        Value left_product = Value();\n\
    \        while (cur != nullptr) {\n            if constexpr (hasTag || Rev) cur->down();\n\
    \            Value current = left_product + get_val(cur->l) + cur->org; \n   \
    \         if (condition(current)) {\n                cur = cur->r;\n         \
    \       left_product = current;\n            }\n            else {\n         \
    \       res = cur;\n                cur = cur->l;\n            }\n        }\n\
    \        return res;\n    }\npublic:\n    Treap() = default;\n    Treap(node *root_)\
    \ : root(root_) {}\n    Treap(const auto &v) requires (!hasKey || !hasValue) :\
    \ root(NodeAlloc::allocate(v)) {}\n    Treap(const auto &k, const auto &v) requires\
    \ (hasKey && hasValue) : root(NodeAlloc::allocate(k, v)) {}\n    void destruct()\
    \ requires (!persistent) {\n        free(root);\n    }\n    void reverse() requires\
    \ (Rev) {\n        if (root) {\n            if constexpr (persistent) root = NodeAlloc::allocate(*root);\n\
    \            root->reverse();\n        }\n    }\n    void transform(const auto\
    \ &tag) requires (hasTag) {\n        if (root) {\n            if constexpr (persistent)\
    \ root = NodeAlloc::allocate(*root);\n            root->give_tag(tag);\n     \
    \   }\n    }\n    Treap& left_merge(auto&& left) requires std::same_as<std::decay_t<decltype(left)>,\
    \ Treap> {\n        root = merge(left.root, root);\n        left.root = nullptr;\n\
    \        return *this;\n    }\n    Treap& right_merge(auto&& right) requires std::same_as<std::decay_t<decltype(right)>,\
    \ Treap> {\n        root = merge(root, right.root);\n        right.root = nullptr;\n\
    \        return *this;\n    }\n    static Treap merge(auto&& left, auto&& right)\
    \ \n        requires (std::same_as<std::decay_t<decltype(left)>, Treap> &&\n \
    \                 std::same_as<std::decay_t<decltype(right)>, Treap>) {\n    \
    \    Treap res(left.merge(right));\n        left.root = nullptr;\n        return\
    \ res;\n    }\n    void swap(Treap &rhs) {\n        std::swap(root, rhs.root);\n\
    \    }\n    bool empty() {\n        return root == nullptr;\n    }\n    int size()\
    \ requires (hasSize) {\n        return get_size(root);\n    }\n    void push_back(const\
    \ auto &v) {\n        right_merge(Treap(v));\n    }\n    void push_back(const\
    \ auto &k, const auto &v) requires (hasKey && hasValue) {\n        right_merge(Treap(k,\
    \ v));\n    }\n    void push_front(const auto &v) {\n        left_merge(Treap(v));\
    \ \n    }\n    void push_front(const auto &k, const auto &v) requires (hasKey\
    \ && hasValue) {\n        left_merge(Treap(k, v)); \n    }\n    struct Iterator\
    \ {\n        using iterator_category = std::bidirectional_iterator_tag;\n    \
    \    using difference_type   = std::ptrdiff_t;\n        using reference      \
    \   = const node&;\n        using value_type        = node;\n        using pointer\
    \           = node*; \n        Iterator(node* ptr, const Treap *tree) : m_ptr(ptr),\
    \ m_tree(tree) {}\n        reference operator*() const { return *m_ptr; }\n  \
    \      auto operator->() const { return m_ptr; }\n        Iterator& operator++()\
    \ requires (!persistent) {\n            m_ptr = find_next(m_ptr);\n          \
    \  return *this;\n        }\n        Iterator operator++(int) requires (!persistent)\
    \ {\n            Iterator tmp = *this;\n            ++(*this);\n            return\
    \ tmp;\n        }\n        Iterator& operator--() requires (!persistent) {\n \
    \           if (m_ptr == nullptr) m_ptr = m_tree->find_max();\n            else\
    \ m_ptr = find_prev(m_ptr);\n            return *this;\n        }\n        Iterator\
    \ operator--(int) requires (!persistent) {\n            Iterator tmp = *this;\n\
    \            --(*this);\n            return tmp;\n        }\n        friend bool\
    \ operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr;\
    \ };\n        friend bool operator!= (const Iterator& a, const Iterator& b) {\
    \ return a.m_ptr != b.m_ptr; };\n        void access_ptr() requires (!persistent)\
    \ {\n            access(m_ptr);\n        }\n    private:\n        node* m_ptr;\n\
    \        const Treap* m_tree;\n    };\n    Iterator begin() const { return Iterator(find_min(),\
    \ this); }\n    Iterator end() const { return Iterator(nullptr, this); }\n   \
    \ Iterator rbegin() const { return Iterator(find_max(), this); }\n    /*\n   \
    \ Find a node's iterator such that:\n    - All nodes on its left have condition(node*)\
    \ == true\n    - All nodes on its right have condition(node*) == false\n    -\
    \ The node itself has condition(node*) == false\n    Assume this is possible\n\
    \    */\n    Iterator bound_condition(const auto &condition) {\n        return\
    \ Iterator(find(condition), this);\n    }\n    /*\n    Find a node's iterator\
    \ such that:\n    - The product \"res\" of all nodes on its left have condition(res)\
    \ == true\n    - The node itself has condition(res + node->org) == false\n   \
    \ Assume this is possible\n    */\n    Iterator bound_condition_value(const auto\
    \ &condition) requires (hasValue) {\n        return Iterator(find_value(condition),\
    \ this);\n    }\n    /*\n    Find a node's iterator such that:\n    - All nodes\
    \ on its left have cmp(key, k) == true\n    - All nodes on its right have cmp(key,\
    \ k) == false\n    - The node itself has cmp(key, k) == false\n    Assume this\
    \ is possible\n    */\n    template<typename K, typename Comp = std::less<Key>>\n\
    \    Iterator lower_bound(const K &k, const Comp &cmp = Comp()) requires (hasKey)\
    \ {\n        return Iterator(find([&k, &cmp](node *src) { \n            return\
    \ cmp(src->key, k);\n        }), this);\n    }\n    /*\n    Find a node's iterator\
    \ such that:\n    - All nodes on its left have cmp(k, key) == false\n    - All\
    \ nodes on its right have cmp(k, key) == true\n    - The node itself has cmp(k,\
    \ key) == true\n    Assume this is possible\n    */\n    template<typename K,\
    \ typename Comp = std::less<Key>>\n    Iterator upper_bound(const K &k, const\
    \ Comp &cmp = Comp()) requires (hasKey) {\n        return Iterator(find([&k, &cmp](node\
    \ *src) { \n            return !cmp(k, src->key);\n        }), this);\n    }\n\
    \    /*\n    Find a node's iterator such that:\n    - The product \"res\" of all\
    \ nodes on its left have cmp(res, v) == true\n    - The node itself has cmp(res\
    \ + node->org, k) == false\n    Assume this is possible\n    */\n    template<typename\
    \ V, typename Comp = std::less<Value>>\n    Iterator lower_bound_value(const V\
    \ &v, const Comp &cmp = Comp()) requires (hasValue) {\n        return Iterator(find_value([&v,\
    \ &cmp](const Value &src) { \n            return cmp(src, v);\n        }), this);\n\
    \    }\n    /*\n    Find a node's iterator such that:\n    - The product \"res\"\
    \ of all nodes on its left have cmp(v, res) == false\n    - The node itself has\
    \ cmp(k, res + node->org) == true\n    Assume this is possible\n    */\n    template<typename\
    \ V, typename Comp = std::less<Value>>\n    Iterator upper_bound_value(const V\
    \ &v, const Comp &cmp = Comp()) requires (hasValue) {\n        return Iterator(find_value([&v,\
    \ &cmp](const Value &src) { \n            return !cmp(v, src);\n        }), this);\n\
    \    }\n    void erase(Iterator it) requires (!persistent) {\n        node* target\
    \ = it.operator->();\n        if (target->f) {\n            if (target->f->l ==\
    \ target) target->f->l = merge(target->l, target->r);\n            else target->f->r\
    \ = merge(target->l, target->r);\n        }\n        NodeAlloc::deallocate(target);\n\
    \    }\n    /*\n    Assume that all nodes having condition(node*) == true form\
    \ a prefix, \n    return a Treap containing these nodes, the rest remain at source\n\
    \    */\n    Treap split_key(const auto &condition) {\n        node *left;\n \
    \       split(root, left, root, condition);\n        return Treap(left);\n   \
    \ }\n    /*\n    Assume that all nodes having cmp(key, k) == true form a prefix,\
    \ \n    return a Treap containing these nodes, the rest remain at source\n   \
    \ */\n    template<typename K, typename Comp = std::less<Key>>\n    Treap split_key_lt(const\
    \ K &k, const Comp &cmp = Comp()) requires (hasKey) {\n        return split_key([&k,\
    \ &cmp](node *src) {\n            return cmp(src->key, k); \n        });\n   \
    \ }\n    /*\n    Assume that all nodes having cmp(k, key) == false form a prefix,\
    \ \n    return a Treap containing these nodes, the rest remain at source\n   \
    \ */\n    template<typename K, typename Comp = std::less<Key>>\n    Treap split_key_leq(const\
    \ K &k, const Comp &cmp = Comp()) requires (hasKey) {\n        return split_key([&k,\
    \ &cmp](node *src) {\n            return !cmp(k, src->key); \n        });\n  \
    \  }\n    /*\n    Assume that all nodes having condition(prefix_product) == true\
    \ form a prefix, \n    return a Treap containing these nodes, the rest remain\
    \ at source\n    */\n    Treap split_value(const auto &condition) requires (hasValue)\
    \ {\n        node *left;\n        split_value(root, left, root, Value(), condition);\n\
    \        return Treap(left);\n    }\n    /*\n    return a Treap containing the\
    \ left most k nodes, the rest remain at source\n    */\n    Treap split_size(const\
    \ int &k) requires (hasSize) {\n        return split_value([&k](const Value &src)\
    \ {\n            return src.size() <= k;  \n        });\n    }\n    Key get_key()\
    \ requires (hasKey) {\n        return get_key(root);\n    }\n    Value product()\
    \ requires (hasValue) {\n        return get_val(root);\n    }\n    /*\n    return\
    \ the product of all the nodes that cmp(key, k) == true\n    Assume these nodes\
    \ form a prefix\n    */\n    template<typename K, typename Comp = std::less<Key>>\n\
    \    Value prefix_product_key_lt(const K &k, const Comp &cmp = Comp()) requires\
    \ (hasKey && hasValue) {\n        return prefix_product(root, [&k, &cmp](node\
    \ *src) {\n            return cmp(src->key, k);\n        });\n    }\n    /*\n\
    \    return the product of all the nodes that cmp(k, key) == false\n    Assume\
    \ these nodes form a prefix\n    */\n    template<typename K, typename Comp =\
    \ std::less<Key>>\n    Value prefix_product_key_leq(const K &k, const Comp &cmp\
    \ = Comp()) requires (hasKey && hasValue) {\n        return prefix_product(root,\
    \ [&k, &cmp](node *src) {\n            return !cmp(k, src->key);\n        });\n\
    \    }\n    /*\n    return the product of longest prefix such that the product\
    \ \"res\" of them has condition(res) == true\n    Assume monotonicity\n    */\n\
    \    Value prefix_product_cond(const auto &condition) requires (hasValue) {\n\
    \        return prefix_product_cond(root, Value(), condition);\n    }\n    std::array<Treap,\
    \ 2> split_range(int l, int r) requires (hasSize) {\n        assert(l <= r);\n\
    \        Treap left = split_size(l);\n        Treap right = split_size(r - l);\n\
    \        swap(right);\n        return {left, right};\n    }\n    Value range_prod(int\
    \ l, int r) requires (hasValue && hasSize) {\n        auto [left, right] = split_range(l,\
    \ r);\n        Value res = product();\n        this->left_merge(left).right_merge(right);\n\
    \        return res;\n    }\n    void range_transform(int l, int r, const auto\
    \ &tag) requires (hasTag && hasSize) {\n        auto [left, right] = split_range(l,\
    \ r);\n        if (!empty()) transform(tag);\n        this->left_merge(left).right_merge(right);\n\
    \    }\n    void range_reverse(int l, int r) requires (Rev && hasSize) {\n   \
    \     auto [left, right] = split_range(l, r);\n        if (!empty()) reverse();\n\
    \        this->left_merge(left).right_merge(right);\n    }\n    /*\n    1-base\n\
    \    */\n    Iterator kth(int k) requires (hasSize) {\n        return Iterator(find_value([&k](const\
    \ Value &v) {\n            return v.size() < k;\n        }), this);\n    }\n};\n"
  code: "#pragma once\n\n#include \"DataStructure/DefaultAllocator.hpp\"\n#include\
    \ \"Algebra/size_value.hpp\"\n\ntemplate<typename Key = void, \n         typename\
    \ Value = size_v,\n         typename Tag = void, \n         bool Rev = false,\n\
    \         template<typename> class Allocator = DefaultAllocator,\n         bool\
    \ persistent = false\n>\nclass Treap {\n    static constexpr bool hasKey = !std::is_same_v<Key,\
    \ void>;\n    static constexpr bool hasValue = !std::is_same_v<Value, void>;\n\
    \    static constexpr bool hasTag = !std::is_same_v<Tag, void>;\n    static constexpr\
    \ bool usePri = !persistent;\n    static constexpr bool hasSize = requires(Value\
    \ v) { v.size(); };\n    static constexpr bool hasValueReverse = requires(Value\
    \ v) { v.reverse(); };\n    struct Empty {};\n    template <bool Condition, typename\
    \ T>\n    static auto get_default() {\n        if constexpr (Condition) return\
    \ T();\n        else return Empty{};\n    }\n    template <bool Condition>\n \
    \   static auto get_pri() {\n        if constexpr (Condition) return rng();\n\
    \        else return Empty{};\n    }\n    static_assert(hasKey || hasValue);\n\
    \    static_assert(!hasTag || hasValue);\n    static inline std::mt19937 rng{880301};\n\
    \    struct node {\n        node *l = nullptr, *r = nullptr;\n        [[no_unique_address]]\
    \ std::conditional_t<!persistent, node*, Empty> f = get_default<!persistent, node*>();\n\
    \        [[no_unique_address]] std::conditional_t<hasKey, Key, Empty> key = get_default<hasKey,\
    \ Key>();\n        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty>\
    \ org = get_default<hasValue, Value>();\n        [[no_unique_address]] std::conditional_t<hasValue,\
    \ Value, Empty> val = get_default<hasValue, Value>();\n        [[no_unique_address]]\
    \ std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();\n\
    \        [[no_unique_address]] std::conditional_t<Rev, int, Empty> rev = get_default<Rev,\
    \ int>();\n        [[no_unique_address]] std::conditional_t<usePri, unsigned,\
    \ Empty> pri = get_pri<usePri>();\n        void up() {\n            if constexpr\
    \ (hasValue) {\n                val = org;\n                if (l) val = l->val\
    \ + org;\n                if (r) val = val + r->val;\n            }\n        \
    \    if constexpr (!persistent) {\n                f = nullptr;\n            \
    \    if (l) l->f = this;\n                if (r) r->f = this;\n            }\n\
    \        }\n        void give_tag(const auto &tag) requires (hasTag) {\n     \
    \       org = org + tag; \n            val = val + tag;\n            lazy = lazy\
    \ + tag;\n        }\n        void reverse() requires (Rev) {\n            rev\
    \ ^= 1;\n            if constexpr (hasValueReverse) {\n                org.reverse();\n\
    \                val.reverse();\n            }\n            std::swap(l, r);\n\
    \        }\n        void down() requires (hasTag || Rev) {\n            bool need_rev\
    \ = false;\n            if constexpr (Rev) need_rev = rev;\n            bool need_tag\
    \ = false;\n            if constexpr (hasTag) { \n                if constexpr\
    \ (std::equality_comparable<Tag>) need_tag = (lazy != Tag());\n              \
    \  else need_tag = true;\n            }\n            if (!need_rev && !need_tag)\
    \ return;\n            if (l) {\n                if constexpr (persistent) l =\
    \ NodeAlloc::allocate(*l);\n                if constexpr (hasTag) if (need_tag)\
    \ l->give_tag(lazy);\n                if constexpr (Rev) if (need_rev) l->reverse();\n\
    \            }\n            if (r) {\n                if constexpr (persistent)\
    \ r = NodeAlloc::allocate(*r);\n                if constexpr (hasTag) if (need_tag)\
    \ r->give_tag(lazy);\n                if constexpr (Rev) if (need_rev) r->reverse();\n\
    \            }\n            if constexpr (hasTag) lazy = Tag();\n            if\
    \ constexpr (Rev) rev = 0;\n        }\n        node() = default;\n        node(const\
    \ auto &v) requires (!hasKey || !hasValue) {\n            if constexpr (hasKey)\
    \ key = Key(v);\n            else org = val = Value(v);\n        }\n        node(const\
    \ auto &k, const auto &v) requires (hasKey && hasValue) : key(k), org(v), val(v)\
    \ {\n        }\n        friend ostream& operator<<(ostream& os, const node &v)\
    \ {\n            if constexpr (hasKey && hasValue) os << \"{key = \" << v.key\
    \ << \", org = \" << v.org << \"}\";\n            else if constexpr (hasKey) os\
    \ << v.key;\n            else os << v.org;\n            return os;\n        }\n\
    \        void debuginfo() const {\n            std::cerr << \"\\e[1;33minfo: \"\
    ;\n            auto printnode = [&](std::string name, node* ptr) {\n         \
    \       std::cerr << name << \": \";\n                if (ptr) std::cerr << *ptr;\n\
    \                else std::cerr << \"null\";\n            };\n            printnode(\"\
    l\", l), std::cerr << \", \";\n            printnode(\"r\", r), std::cerr << \"\
    , \";\n            if constexpr (!persistent) printnode(\"f\", f);\n         \
    \   cerr << \"\\e[0m\\n\";\n        }\n    };\n    using NodeAlloc = Allocator<node>;\n\
    \    node *root = nullptr;\n    static void split(node *source, node *&left, node\
    \ *&right, const auto &condition) {\n        if (!source) return left = right\
    \ = nullptr, void();\n        if constexpr (persistent) source = NodeAlloc::allocate(*source);\
    \ \n        if constexpr (hasTag || Rev) source->down();\n        if (condition(source))\
    \ {\n            left = source;\n            split(source->r, left->r, right,\
    \ condition);\n            left->up();\n        }\n        else {\n          \
    \  right = source;\n            split(source->l, left, right->l, condition);\n\
    \            right->up();\n        }\n    }\n    static void split_value(node\
    \ *source, node *&left, node *&right, const auto &left_product, const auto &condition)\
    \ requires (hasValue) {\n        if (!source) return left = right = nullptr, void();\n\
    \        if constexpr (persistent) source = NodeAlloc::allocate(*source); \n \
    \       if constexpr (hasTag || Rev) source->down();\n        Value current =\
    \ left_product + get_val(source->l) + source->org;\n        if (condition(current))\
    \ {\n            left = source;\n            split_value(source->r, left->r, right,\
    \ current, condition);\n            left->up();\n        }\n        else {\n \
    \           right = source;\n            split_value(source->l, left, right->l,\
    \ left_product, condition);\n            right->up();\n        }\n    }\n    static\
    \ Value prefix_product(node *source, const auto &condition) requires (hasValue)\
    \ {\n        if (!source) return Value();\n        if constexpr (hasTag || Rev)\
    \ source->down();\n        if (condition(source))\n            return get_val(source->l)\
    \ + source->org + prefix_product(source->r, condition);\n        return prefix_product(source->l,\
    \ condition);\n    }\n    static Value prefix_product_cond(node *source, const\
    \ auto &left_product, const auto &condition) requires (hasValue) {\n        if\
    \ (!source) return left_product;\n        if constexpr (hasTag || Rev) source->down();\n\
    \        Value current = left_product + get_val(source->l) + source->org;\n  \
    \      if (condition(current))\n            return prefix_product_cond(source->r,\
    \ current, condition);\n        return prefix_product_cond(source->l, left_product,\
    \ condition);\n    }\n    static node *merge(node *left, node *right) {\n    \
    \    if (!left || !right) return left ? left : right;\n        bool useleft =\
    \ true;\n        if constexpr (usePri)\n            useleft = left->pri < right->pri;\n\
    \        else\n            useleft = rng() % (get_size(left) + get_size(right))\
    \ < size_t(get_size(left));\n        if (useleft) {\n            if constexpr\
    \ (persistent) left = NodeAlloc::allocate(*left); \n            if constexpr (hasTag\
    \ || Rev) left->down();\n            left->r = merge(left->r, right);\n      \
    \      left->up();\n            return left;\n        }\n        if constexpr\
    \ (persistent) right = NodeAlloc::allocate(*right);\n        if constexpr (hasTag\
    \ || Rev) right->down();\n        right->l = merge(left, right->l);\n        right->up();\n\
    \        return right;\n    }\n    static Key get_key(node *a) requires (hasKey)\
    \ {\n        return get_key(a, Key());\n    }\n    static Key get_key(node *a,\
    \ auto Default) requires (hasKey) {\n        return a ? a->key : Default;\n  \
    \  }\n    static Value get_org(node *a) requires (hasValue) {\n        return\
    \ a ? a->org : Value();\n    }\n    static Value get_org(node *a, auto Default)\
    \ requires (hasValue) {\n        return a ? a->org : Default;\n    }\n    static\
    \ Value get_val(node *a) requires (hasValue) {\n        return a ? a->val : Value();\n\
    \    }\n    static Value get_val(node *a, Value Default) requires (hasValue) {\n\
    \        return a ? a->val : Default;\n    }\n    static int get_size(node *a)\
    \ requires (hasSize) { \n        return a ? a->val.size() : 0;\n    }\n    static\
    \ void free(node *&ptr) requires (!persistent) {\n        if (ptr == nullptr)\
    \ return;\n        free(ptr->l);\n        free(ptr->r);\n        delete ptr;\n\
    \        ptr = nullptr;\n    }\n    static node* find_min(node *start) {\n   \
    \     if (!start) return nullptr;\n        node *res = start;\n        while (true)\
    \ {\n            if constexpr (hasTag || Rev) res->down();\n            if (res->l)\
    \ res = res->l;\n            else break;\n        }\n        return res;\n   \
    \ }\n    node* find_min() const {\n        return find_min(root);\n    }\n   \
    \ static node* find_max(node *start) {\n        if (!start) return nullptr;\n\
    \        node *res = start;\n        while (true) {\n            if constexpr\
    \ (hasTag || Rev) res->down();\n            if (res->r) res = res->r;\n      \
    \      else break;\n        }\n        return res;\n    }\n    node* find_max()\
    \ const {\n        return find_max(root);\n    }\n    static void access(node\
    \ *ptr) requires (!persistent) {\n        assert(ptr != nullptr);\n        if\
    \ (ptr->f != nullptr)\n            access(ptr->f);\n        if constexpr (hasTag\
    \ || Rev) ptr->down();\n    }\n    static node* find_next(node *ptr) requires\
    \ (!persistent) {\n        assert(ptr != nullptr);\n        access(ptr);\n   \
    \     if (ptr->r != nullptr)\n            return find_min(ptr->r);\n        while\
    \ (ptr->f != nullptr && ptr->f->r == ptr)\n            ptr = ptr->f;\n       \
    \ if (ptr->f == nullptr) return nullptr;\n        return ptr->f;\n    }\n    static\
    \ node* find_prev(node *ptr) requires (!persistent) {\n        assert(ptr != nullptr);\n\
    \        access(ptr);\n        if (ptr->l != nullptr)\n            return find_max(ptr->l);\n\
    \        while (ptr->f != nullptr && ptr->f->l == ptr)\n            ptr = ptr->f;\n\
    \        assert(ptr->f != nullptr);\n        return ptr->f;\n    }\n    node *find(const\
    \ auto &condition) {\n        node *cur = root, *res = nullptr;\n        while\
    \ (cur != nullptr) {\n            if constexpr (hasTag || Rev) cur->down();\n\
    \            if (condition(cur))\n                cur = cur->r;\n            else\
    \ {\n                res = cur;\n                cur = cur->l;\n            }\n\
    \        }\n        return res;\n    }\n    node *find_value(const auto &condition)\
    \ {\n        node *cur = root, *res = nullptr;\n        Value left_product = Value();\n\
    \        while (cur != nullptr) {\n            if constexpr (hasTag || Rev) cur->down();\n\
    \            Value current = left_product + get_val(cur->l) + cur->org; \n   \
    \         if (condition(current)) {\n                cur = cur->r;\n         \
    \       left_product = current;\n            }\n            else {\n         \
    \       res = cur;\n                cur = cur->l;\n            }\n        }\n\
    \        return res;\n    }\npublic:\n    Treap() = default;\n    Treap(node *root_)\
    \ : root(root_) {}\n    Treap(const auto &v) requires (!hasKey || !hasValue) :\
    \ root(NodeAlloc::allocate(v)) {}\n    Treap(const auto &k, const auto &v) requires\
    \ (hasKey && hasValue) : root(NodeAlloc::allocate(k, v)) {}\n    void destruct()\
    \ requires (!persistent) {\n        free(root);\n    }\n    void reverse() requires\
    \ (Rev) {\n        if (root) {\n            if constexpr (persistent) root = NodeAlloc::allocate(*root);\n\
    \            root->reverse();\n        }\n    }\n    void transform(const auto\
    \ &tag) requires (hasTag) {\n        if (root) {\n            if constexpr (persistent)\
    \ root = NodeAlloc::allocate(*root);\n            root->give_tag(tag);\n     \
    \   }\n    }\n    Treap& left_merge(auto&& left) requires std::same_as<std::decay_t<decltype(left)>,\
    \ Treap> {\n        root = merge(left.root, root);\n        left.root = nullptr;\n\
    \        return *this;\n    }\n    Treap& right_merge(auto&& right) requires std::same_as<std::decay_t<decltype(right)>,\
    \ Treap> {\n        root = merge(root, right.root);\n        right.root = nullptr;\n\
    \        return *this;\n    }\n    static Treap merge(auto&& left, auto&& right)\
    \ \n        requires (std::same_as<std::decay_t<decltype(left)>, Treap> &&\n \
    \                 std::same_as<std::decay_t<decltype(right)>, Treap>) {\n    \
    \    Treap res(left.merge(right));\n        left.root = nullptr;\n        return\
    \ res;\n    }\n    void swap(Treap &rhs) {\n        std::swap(root, rhs.root);\n\
    \    }\n    bool empty() {\n        return root == nullptr;\n    }\n    int size()\
    \ requires (hasSize) {\n        return get_size(root);\n    }\n    void push_back(const\
    \ auto &v) {\n        right_merge(Treap(v));\n    }\n    void push_back(const\
    \ auto &k, const auto &v) requires (hasKey && hasValue) {\n        right_merge(Treap(k,\
    \ v));\n    }\n    void push_front(const auto &v) {\n        left_merge(Treap(v));\
    \ \n    }\n    void push_front(const auto &k, const auto &v) requires (hasKey\
    \ && hasValue) {\n        left_merge(Treap(k, v)); \n    }\n    struct Iterator\
    \ {\n        using iterator_category = std::bidirectional_iterator_tag;\n    \
    \    using difference_type   = std::ptrdiff_t;\n        using reference      \
    \   = const node&;\n        using value_type        = node;\n        using pointer\
    \           = node*; \n        Iterator(node* ptr, const Treap *tree) : m_ptr(ptr),\
    \ m_tree(tree) {}\n        reference operator*() const { return *m_ptr; }\n  \
    \      auto operator->() const { return m_ptr; }\n        Iterator& operator++()\
    \ requires (!persistent) {\n            m_ptr = find_next(m_ptr);\n          \
    \  return *this;\n        }\n        Iterator operator++(int) requires (!persistent)\
    \ {\n            Iterator tmp = *this;\n            ++(*this);\n            return\
    \ tmp;\n        }\n        Iterator& operator--() requires (!persistent) {\n \
    \           if (m_ptr == nullptr) m_ptr = m_tree->find_max();\n            else\
    \ m_ptr = find_prev(m_ptr);\n            return *this;\n        }\n        Iterator\
    \ operator--(int) requires (!persistent) {\n            Iterator tmp = *this;\n\
    \            --(*this);\n            return tmp;\n        }\n        friend bool\
    \ operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr;\
    \ };\n        friend bool operator!= (const Iterator& a, const Iterator& b) {\
    \ return a.m_ptr != b.m_ptr; };\n        void access_ptr() requires (!persistent)\
    \ {\n            access(m_ptr);\n        }\n    private:\n        node* m_ptr;\n\
    \        const Treap* m_tree;\n    };\n    Iterator begin() const { return Iterator(find_min(),\
    \ this); }\n    Iterator end() const { return Iterator(nullptr, this); }\n   \
    \ Iterator rbegin() const { return Iterator(find_max(), this); }\n    /*\n   \
    \ Find a node's iterator such that:\n    - All nodes on its left have condition(node*)\
    \ == true\n    - All nodes on its right have condition(node*) == false\n    -\
    \ The node itself has condition(node*) == false\n    Assume this is possible\n\
    \    */\n    Iterator bound_condition(const auto &condition) {\n        return\
    \ Iterator(find(condition), this);\n    }\n    /*\n    Find a node's iterator\
    \ such that:\n    - The product \"res\" of all nodes on its left have condition(res)\
    \ == true\n    - The node itself has condition(res + node->org) == false\n   \
    \ Assume this is possible\n    */\n    Iterator bound_condition_value(const auto\
    \ &condition) requires (hasValue) {\n        return Iterator(find_value(condition),\
    \ this);\n    }\n    /*\n    Find a node's iterator such that:\n    - All nodes\
    \ on its left have cmp(key, k) == true\n    - All nodes on its right have cmp(key,\
    \ k) == false\n    - The node itself has cmp(key, k) == false\n    Assume this\
    \ is possible\n    */\n    template<typename K, typename Comp = std::less<Key>>\n\
    \    Iterator lower_bound(const K &k, const Comp &cmp = Comp()) requires (hasKey)\
    \ {\n        return Iterator(find([&k, &cmp](node *src) { \n            return\
    \ cmp(src->key, k);\n        }), this);\n    }\n    /*\n    Find a node's iterator\
    \ such that:\n    - All nodes on its left have cmp(k, key) == false\n    - All\
    \ nodes on its right have cmp(k, key) == true\n    - The node itself has cmp(k,\
    \ key) == true\n    Assume this is possible\n    */\n    template<typename K,\
    \ typename Comp = std::less<Key>>\n    Iterator upper_bound(const K &k, const\
    \ Comp &cmp = Comp()) requires (hasKey) {\n        return Iterator(find([&k, &cmp](node\
    \ *src) { \n            return !cmp(k, src->key);\n        }), this);\n    }\n\
    \    /*\n    Find a node's iterator such that:\n    - The product \"res\" of all\
    \ nodes on its left have cmp(res, v) == true\n    - The node itself has cmp(res\
    \ + node->org, k) == false\n    Assume this is possible\n    */\n    template<typename\
    \ V, typename Comp = std::less<Value>>\n    Iterator lower_bound_value(const V\
    \ &v, const Comp &cmp = Comp()) requires (hasValue) {\n        return Iterator(find_value([&v,\
    \ &cmp](const Value &src) { \n            return cmp(src, v);\n        }), this);\n\
    \    }\n    /*\n    Find a node's iterator such that:\n    - The product \"res\"\
    \ of all nodes on its left have cmp(v, res) == false\n    - The node itself has\
    \ cmp(k, res + node->org) == true\n    Assume this is possible\n    */\n    template<typename\
    \ V, typename Comp = std::less<Value>>\n    Iterator upper_bound_value(const V\
    \ &v, const Comp &cmp = Comp()) requires (hasValue) {\n        return Iterator(find_value([&v,\
    \ &cmp](const Value &src) { \n            return !cmp(v, src);\n        }), this);\n\
    \    }\n    void erase(Iterator it) requires (!persistent) {\n        node* target\
    \ = it.operator->();\n        if (target->f) {\n            if (target->f->l ==\
    \ target) target->f->l = merge(target->l, target->r);\n            else target->f->r\
    \ = merge(target->l, target->r);\n        }\n        NodeAlloc::deallocate(target);\n\
    \    }\n    /*\n    Assume that all nodes having condition(node*) == true form\
    \ a prefix, \n    return a Treap containing these nodes, the rest remain at source\n\
    \    */\n    Treap split_key(const auto &condition) {\n        node *left;\n \
    \       split(root, left, root, condition);\n        return Treap(left);\n   \
    \ }\n    /*\n    Assume that all nodes having cmp(key, k) == true form a prefix,\
    \ \n    return a Treap containing these nodes, the rest remain at source\n   \
    \ */\n    template<typename K, typename Comp = std::less<Key>>\n    Treap split_key_lt(const\
    \ K &k, const Comp &cmp = Comp()) requires (hasKey) {\n        return split_key([&k,\
    \ &cmp](node *src) {\n            return cmp(src->key, k); \n        });\n   \
    \ }\n    /*\n    Assume that all nodes having cmp(k, key) == false form a prefix,\
    \ \n    return a Treap containing these nodes, the rest remain at source\n   \
    \ */\n    template<typename K, typename Comp = std::less<Key>>\n    Treap split_key_leq(const\
    \ K &k, const Comp &cmp = Comp()) requires (hasKey) {\n        return split_key([&k,\
    \ &cmp](node *src) {\n            return !cmp(k, src->key); \n        });\n  \
    \  }\n    /*\n    Assume that all nodes having condition(prefix_product) == true\
    \ form a prefix, \n    return a Treap containing these nodes, the rest remain\
    \ at source\n    */\n    Treap split_value(const auto &condition) requires (hasValue)\
    \ {\n        node *left;\n        split_value(root, left, root, Value(), condition);\n\
    \        return Treap(left);\n    }\n    /*\n    return a Treap containing the\
    \ left most k nodes, the rest remain at source\n    */\n    Treap split_size(const\
    \ int &k) requires (hasSize) {\n        return split_value([&k](const Value &src)\
    \ {\n            return src.size() <= k;  \n        });\n    }\n    Key get_key()\
    \ requires (hasKey) {\n        return get_key(root);\n    }\n    Value product()\
    \ requires (hasValue) {\n        return get_val(root);\n    }\n    /*\n    return\
    \ the product of all the nodes that cmp(key, k) == true\n    Assume these nodes\
    \ form a prefix\n    */\n    template<typename K, typename Comp = std::less<Key>>\n\
    \    Value prefix_product_key_lt(const K &k, const Comp &cmp = Comp()) requires\
    \ (hasKey && hasValue) {\n        return prefix_product(root, [&k, &cmp](node\
    \ *src) {\n            return cmp(src->key, k);\n        });\n    }\n    /*\n\
    \    return the product of all the nodes that cmp(k, key) == false\n    Assume\
    \ these nodes form a prefix\n    */\n    template<typename K, typename Comp =\
    \ std::less<Key>>\n    Value prefix_product_key_leq(const K &k, const Comp &cmp\
    \ = Comp()) requires (hasKey && hasValue) {\n        return prefix_product(root,\
    \ [&k, &cmp](node *src) {\n            return !cmp(k, src->key);\n        });\n\
    \    }\n    /*\n    return the product of longest prefix such that the product\
    \ \"res\" of them has condition(res) == true\n    Assume monotonicity\n    */\n\
    \    Value prefix_product_cond(const auto &condition) requires (hasValue) {\n\
    \        return prefix_product_cond(root, Value(), condition);\n    }\n    std::array<Treap,\
    \ 2> split_range(int l, int r) requires (hasSize) {\n        assert(l <= r);\n\
    \        Treap left = split_size(l);\n        Treap right = split_size(r - l);\n\
    \        swap(right);\n        return {left, right};\n    }\n    Value range_prod(int\
    \ l, int r) requires (hasValue && hasSize) {\n        auto [left, right] = split_range(l,\
    \ r);\n        Value res = product();\n        this->left_merge(left).right_merge(right);\n\
    \        return res;\n    }\n    void range_transform(int l, int r, const auto\
    \ &tag) requires (hasTag && hasSize) {\n        auto [left, right] = split_range(l,\
    \ r);\n        if (!empty()) transform(tag);\n        this->left_merge(left).right_merge(right);\n\
    \    }\n    void range_reverse(int l, int r) requires (Rev && hasSize) {\n   \
    \     auto [left, right] = split_range(l, r);\n        if (!empty()) reverse();\n\
    \        this->left_merge(left).right_merge(right);\n    }\n    /*\n    1-base\n\
    \    */\n    Iterator kth(int k) requires (hasSize) {\n        return Iterator(find_value([&k](const\
    \ Value &v) {\n            return v.size() < k;\n        }), this);\n    }\n};\n"
  dependsOn:
  - DataStructure/DefaultAllocator.hpp
  - Algebra/size_value.hpp
  isVerificationFile: false
  path: DataStructure/Treap.hpp
  requiredBy: []
  timestamp: '2026-05-05 22:01:14+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/3_qoj/17153.test.cpp
  - test/8_luogu/P5055.test.cpp
  - test/8_luogu/P3835.test.cpp
  - test/8_luogu/P3835_pool.test.cpp
  - test/1_library_checker/data_structure/range_reverse_range_sum.test.cpp
  - test/1_library_checker/data_structure/ordered_set_treap.test.cpp
documentation_of: DataStructure/Treap.hpp
layout: document
redirect_from:
- /library/DataStructure/Treap.hpp
- /library/DataStructure/Treap.hpp.html
title: DataStructure/Treap.hpp
---
