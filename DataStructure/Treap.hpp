#ifndef __BALU_TREAP__
#define __BALU_TREAP__

namespace TreapMeasure {
    enum class MergeType {
        PRI,
        RANDOM
    };
    struct size_v {
        int sz;
        size_v(int sz_ = 0): sz(sz_) {}
        size_v operator+(const size_v &rhs) const {
            return size_v(sz + rhs.sz);
        }
        int size() const {
            return sz; 
        }
        friend ostream& operator<<(ostream& os, const size_v &v) {
            os << v.sz;
            return os;
        }
    };
}
template<typename Key = void, 
         typename Value = TreapMeasure::size_v,
         typename Tag = void, 
         bool Rev = false,
         TreapMeasure::MergeType Mtype = TreapMeasure::MergeType::PRI
>
class Treap {
    static constexpr bool hasKey = !std::is_same_v<Key, void>;
    static constexpr bool hasValue = !std::is_same_v<Value, void>;
    static constexpr bool hasTag = !std::is_same_v<Tag, void>;
    static constexpr bool usePri = Mtype == TreapMeasure::MergeType::PRI;
    static constexpr bool hasSize = requires(Value v) { v.size(); };
    static constexpr bool hasValueReverse = requires(Value v) { v.reverse(); };
    struct Empty {};
    template <bool Condition, typename T>
    static auto get_default() {
        if constexpr (Condition) return T();
        else return Empty{};
    }
    template <bool Condition>
    static auto get_pri() {
        if constexpr (Condition) return rng();
        else return Empty{};
    }
    static_assert(hasKey || hasValue);
    static_assert(!hasTag || hasValue);
    static inline std::mt19937 rng{880301};
    struct node {
        node *l = nullptr, *r = nullptr, *f = nullptr;
        [[no_unique_address]] std::conditional_t<hasKey, Key, Empty> key = get_default<hasKey, Key>();
        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty> org = get_default<hasValue, Value>();
        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty> val = get_default<hasValue, Value>();
        [[no_unique_address]] std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();
        [[no_unique_address]] std::conditional_t<Rev, int, Empty> rev = get_default<Rev, int>();
        [[no_unique_address]] std::conditional_t<usePri, unsigned, Empty> pri = get_pri<usePri>();
        void up() {
            if constexpr (hasValue) {
                val = org;
                if (l) val = l->val + org;
                if (r) val = val + r->val;
            }
            f = nullptr;
            if (l) l->f = this;
            if (r) r->f = this;
        }
        void give_tag(const auto &tag) requires (hasTag) {
            org = org + tag; 
            val = val + tag;
            lazy = lazy + tag;
        }
        void reverse() requires (Rev) {
            rev ^= 1;
            if constexpr (hasValueReverse) {
                org.reverse();
                val.reverse();
            }
            std::swap(l, r);
        }
        void down() requires (hasTag || Rev) {
            if constexpr (hasTag) { 
                if (l) l->give_tag(lazy);
                if (r) r->give_tag(lazy);
                lazy = Tag();
            }
            if constexpr (Rev) {
                if (rev) {
                    if (l) l->reverse();
                    if (r) r->reverse();
                    rev = 0;
                }
            }
        }
        node() = default;
        node(const auto &v) {
            if constexpr (hasKey) key = Key(v);
            if constexpr (hasValue) org = val = Value(v);
        }
        node(const auto &k, const auto &v) requires (hasKey && hasValue) : key(k), org(v), val(v) {
        }
        friend ostream& operator<<(ostream& os, const node &v) {
            if constexpr (hasKey && hasValue) os << "{key = " << v.key << ", org = " << v.org << "}";
            else if constexpr (hasKey) os << v.key;
            else os << v.org;
            return os;
        }
        void debuginfo() const {
            std::cerr << "\e[1;33minfo: ";
            auto printnode = [&](std::string name, node* ptr) {
                std::cerr << name << ": ";
                if (ptr) std::cerr << *ptr;
                else std::cerr << "null";
            };
            printnode("l", l), std::cerr << ", ";
            printnode("r", r), std::cerr << ", ";
            printnode("f", f);
            cerr << "\e[0m\n";
        }
    };
    node *root = nullptr;
    static void split(node *source, node *&left, node *&right, const auto &condition) {
        if (!source) return left = right = nullptr, void();
        if constexpr (hasTag || Rev) source->down();
        if (condition(source)) {
            left = source;
            split(source->r, left->r, right, condition);
            left->up();
        }
        else {
            right = source;
            split(source->l, left, right->l, condition);
            right->up();
        }
    }
    static void split_value(node *source, node *&left, node *&right, const auto &left_product, const auto &condition) requires (hasValue) {
        if (!source) return left = right = nullptr, void();
        if constexpr (hasTag || Rev) source->down();
        Value current = left_product + get_val(source->l) + source->org;
        if (condition(current)) {
            left = source;
            split_value(source->r, left->r, right, current, condition);
            left->up();
        }
        else {
            right = source;
            split_value(source->l, left, right->l, left_product, condition);
            right->up();
        }
    }
    static Value prefix_product(node *source, const auto &condition) requires (hasValue) {
        if (!source) return Value();
        if constexpr (hasTag || Rev) source->down();
        if (condition(source))
            return get_val(source->l) + source->org + prefix_product(source->r, condition);
        return prefix_product(source->l, condition);
    }
    static Value prefix_product_value(node *source, const auto &left_product, const auto &condition) requires (hasValue) {
        if (!source) return left_product;
        if constexpr (hasTag || Rev) source->down();
        Value current = left_product + get_val(source->l) + source->org;
        if (condition(current))
            return prefix_product_value(source->r, current, condition);
        return prefix_product_value(source->l, left_product, condition);
    }
    static node *merge(node *left, node *right) {
        if (!left || !right) return left ? left : right;
        bool useleft = true;
        if constexpr (Mtype == TreapMeasure::MergeType::PRI)
            useleft = left->pri < right->pri;
        if constexpr (Mtype == TreapMeasure::MergeType::RANDOM)
            useleft = rng() % (get_size(left) + get_size(right)) < get_size(left);
        if (useleft) {
            if constexpr (hasTag || Rev) left->down();
            left->r = merge(left->r, right);
            left->up();
            return left;
        }
        if constexpr (hasTag || Rev) right->down();
        right->l = merge(left, right->l);
        right->up();
        return right;
    }
    static Key get_key(node *a) requires (hasKey) {
        return get_key(a, Key());
    }
    static Key get_key(node *a, auto Default) requires (hasKey) {
        return a ? a->key : Default;
    }
    static Value get_org(node *a) requires (hasValue) {
        return a ? a->org : Value();
    }
    static Value get_org(node *a, auto Default) requires (hasValue) {
        return a ? a->org : Default;
    }
    static Value get_val(node *a) requires (hasValue) {
        return a ? a->val : Value();
    }
    static Value get_val(node *a, Value Default) requires (hasValue) {
        return a ? a->val : Default;
    }
    static int get_size(node *a) requires (hasSize) { 
        return a ? a->val.size() : 0;
    }
    static void free(node *&ptr) {
        if (ptr == nullptr) return;
        free(ptr->l);
        free(ptr->r);
        delete ptr;
        ptr = nullptr;
    }
    static node* find_min(node *start) {
        if (!start) return nullptr;
        node *res = start;
        while (true) {
            if constexpr (hasTag || Rev) res->down();
            if (res->l) res = res->l;
            else break;
        }
        return res;
    }
    node* find_min() const {
        return find_min(root);
    }
    static node* find_max(node *start) {
        if (!start) return nullptr;
        node *res = start;
        while (true) {
            if constexpr (hasTag || Rev) res->down();
            if (res->r) res = res->r;
            else break;
        }
        return res;
    }
    node* find_max() const {
        return find_max(root);
    }
    static void access(node *ptr) {
        assert(ptr != nullptr);
        if (ptr->f != nullptr)
            access(ptr->f);
        if constexpr (hasTag || Rev) ptr->down();
    }
    static node* find_next(node *ptr) {
        assert(ptr != nullptr);
        access(ptr);
        if (ptr->r != nullptr)
            return find_min(ptr->r);
        while (ptr->f != nullptr && ptr->f->r == ptr)
            ptr = ptr->f;
        if (ptr->f == nullptr) return nullptr;
        return ptr->f;
    }
    static node* find_prev(node *ptr) {
        assert(ptr != nullptr);
        access(ptr);
        if (ptr->l != nullptr)
            return find_max(ptr->l);
        while (ptr->f != nullptr && ptr->f->l == ptr)
            ptr = ptr->f;
        assert(ptr->f != nullptr);
        return ptr->f;
    }
    node *find(const auto &condition) {
        node *cur = root, *res = nullptr;
        while (cur != nullptr) {
            if constexpr (hasTag || Rev) cur->down();
            if (condition(cur))
                cur = cur->r;
            else {
                res = cur;
                cur = cur->l;
            }
        }
        return res;
    }
    node *find_value(const auto &condition) {
        node *cur = root, *res = nullptr;
        Value left_product = Value();
        while (cur != nullptr) {
            if constexpr (hasTag || Rev) cur->down();
            Value current = left_product + get_val(cur->l) + cur->org; 
            if (condition(current)) {
                cur = cur->r;
                left_product = current;
            }
            else {
                res = cur;
                cur = cur->l;
            }
        }
        return res;
    }
public:
    Treap() = default;
    Treap(node *root_) : root(root_) {
    }
    Treap(const auto &v) : root(new node(v)) {
    }
    Treap(const auto &k, const auto &v) requires (hasKey && hasValue) : root(new node(k, v)) {
    }
    void destruct() {
        free(root);
    }
    void reverse() requires (Rev) {
        if (root) root->reverse();
    }
    void transform(const auto &tag) requires (hasTag) {
        if (root) root->give_tag(tag);
    }
    Treap& left_merge(auto&& left) requires std::same_as<std::decay_t<decltype(left)>, Treap> {
        root = merge(left.root, root);
        left.root = nullptr;
        return *this;
    }
    Treap& right_merge(auto&& right) requires std::same_as<std::decay_t<decltype(right)>, Treap> {
        root = merge(root, right.root);
        right.root = nullptr;
        return *this;
    }
    Treap& merge(auto&& right) requires std::same_as<std::decay_t<decltype(right)>, Treap> {
        return right_merge(right);
    }
    static Treap merge(auto&& left, auto&& right) 
        requires (std::same_as<std::decay_t<decltype(left)>, Treap> &&
                  std::same_as<std::decay_t<decltype(right)>, Treap>) {
        Treap res(left.merge(right));
        left.root = nullptr;
        return res;
    }
    void swap(Treap &rhs) {
        std::swap(root, rhs.root);
    }
    bool empty() {
        return root == nullptr;
    }
    int size() requires (hasSize) {
        return get_size(root);
    }
    void push_back(const auto &v) {
        right_merge(Treap(v));
    }
    void push_back(const auto &k, const auto &v) requires (hasKey && hasValue) {
        right_merge(Treap(k, v));
    }
    void push_front(const auto &v) {
        left_merge(Treap(v)); 
    }
    void push_front(const auto &k, const auto &v) requires (hasKey && hasValue) {
        left_merge(Treap(k, v)); 
    }
    struct Iterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using reference         = const node&;
        using value_type        = node;
        using pointer           = node*; 
        Iterator(node* ptr, Treap *tree) : m_ptr(ptr), m_tree(tree) {}
        reference operator*() const { return *m_ptr; }
        auto operator->() const { return m_ptr; }
        Iterator& operator++() {
            m_ptr = find_next(m_ptr);
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        Iterator& operator--() {
            if (m_ptr == nullptr) m_ptr = m_tree->find_max();
            else m_ptr = find_prev(m_ptr);
            return *this;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        node* m_ptr;
        const Treap* m_tree;
    };
    Iterator begin() { return Iterator(find_min(), this); }
    Iterator end() { return Iterator(nullptr, this); }
    /*
    Find a node's iterator such that:
    - All nodes on its left have cmp(key, k) == true
    - All nodes on its right have cmp(key, k) == false
    - The node itself has cmp(key, k) == false
    Assume this is possible
    */
    template<typename K, typename Comp = std::less<Key>>
    Iterator lower_bound(const K &k, const Comp &cmp = Comp()) requires (hasKey) {
        return Iterator(find([&k, &cmp](node *src) { 
            return cmp(src->key, k);
        }), this);
    }
    /*
    Find a node's iterator such that:
    - All nodes on its left have cmp(k, key) == false
    - All nodes on its right have cmp(k, key) == true
    - The node itself has cmp(k, key) == true
    Assume this is possible
    */
    template<typename K, typename Comp = std::less<Key>>
    Iterator upper_bound(const K &k, const Comp &cmp = Comp()) requires (hasKey) {
        return Iterator(find([&k, &cmp](node *src) { 
            return !cmp(k, src->key);
        }), this);
    }
    /*
    Find a node's iterator such that:
    - The product "res" of all nodes on its left have cmp(res, v) == true
    - The node itself has cmp(res + node->org, k) == false
    Assume this is possible
    */
    template<typename V, typename Comp = std::less<Value>>
    Iterator lower_bound_value(const V &v, const Comp &cmp = Comp()) requires (hasValue) {
        return Iterator(find_value([&v, &cmp](const Value &src) { 
            return cmp(src, v);
        }), this);
    }
    /*
    Find a node's iterator such that:
    - The product "res" of all nodes on its left have cmp(v, res) == false
    - The node itself has cmp(k, res + node->org) == true
    Assume this is possible
    */
    template<typename V, typename Comp = std::less<Value>>
    Iterator upper_bound_value(const V &v, const Comp &cmp = Comp()) requires (hasValue) {
        return Iterator(find_value([&v, &cmp](const Value &src) { 
            return !cmp(v, src);
        }), this);
    }
    /*
    Assume that all nodes having condition(node*) == true form a prefix, 
    return a Treap containing these nodes, the rest remain at source
    */
    Treap split_key(const auto &condition) {
        node *left;
        split(root, left, root, condition);
        return Treap(left);
    }
    /*
    Assume that all nodes having cmp(key, k) == true form a prefix, 
    return a Treap containing these nodes, the rest remain at source
    */
    template<typename K, typename Comp = std::less<Key>>
    Treap split_key_lt(const K &k, const Comp &cmp = Comp()) requires (hasKey) {
        return split_key([&k, &cmp](node *src) {
            return cmp(src->key, k); 
        });
    }
    /*
    Assume that all nodes having cmp(k, key) == false form a prefix, 
    return a Treap containing these nodes, the rest remain at source
    */
    template<typename K, typename Comp = std::less<Key>>
    Treap split_key_leq(const K &k, const Comp &cmp = Comp()) requires (hasKey) {
        return split_key([&k, &cmp](node *src) {
            return !cmp(k, src->key); 
        });
    }
    /*
    Assume that all nodes having condition(prefix_product) == true form a prefix, 
    return a Treap containing these nodes, the rest remain at source
    */
    Treap split_value(const auto &condition) requires (hasValue) {
        node *left;
        split_value(root, left, root, Value(), condition);
        return Treap(left);
    }
    /*
    Assume that all nodes having cmp(prefix_product, v) == true form a prefix, 
    return a Treap containing these nodes, the rest remain at source
    */
    template<typename V, typename Comp = std::less<Value>>
    Treap split_value_lt(const V &v, const Comp &cmp = Comp()) requires (hasValue) {
        return split_value([&v, &cmp](const Value &src) {
            return cmp(src, v); 
        });
    }
    /*
    Assume that all nodes having cmp(v, prefix_product) == false form a prefix, 
    return a Treap containing these nodes, the rest remain at source
    */
    template<typename V, typename Comp = std::less<Value>>
    Treap split_value_leq(const V &v, const Comp &cmp = Comp()) requires (hasValue) {
        return split_value([&v, &cmp](const Value &src) {
            return !cmp(v, src);
        });
    }
    /*
    return a Treap containing the left most k nodes, the rest remain at source
    */
    Treap split_size(const int &k) requires (hasSize) {
        return split_value([&k](const Value &src) {
            return src.size() <= k;  
        });
    }
    Key get_key() requires (hasKey) {
        return get_key(root);
    }
    Value product() requires (hasValue) {
        return get_val(root);
    }
    /*
    return the product of all the nodes that cmp(key, k) == true
    Assume these nodes form a prefix
    */
    template<typename K, typename Comp = std::less<Key>>
    Value prefix_product_key_lt(const K &k, const Comp &cmp = Comp()) requires (hasKey && hasValue) {
        return prefix_product(root, [&k, &cmp](node *src) {
            return cmp(src->key, k);
        });
    }
    /*
    return the product of all the nodes that cmp(k, key) == false
    Assume these nodes form a prefix
    */
    template<typename K, typename Comp = std::less<Key>>
    Value prefix_product_key_leq(const K &k, const Comp &cmp = Comp()) requires (hasKey && hasValue) {
        return prefix_product(root, [&k, &cmp](node *src) {
            return !cmp(k, src->key);
        });
    }
    /*
    return the product of longest prefix such that the product "res" of them has cmp(res, v) == true
    Assume monotonicity
    */
    template<typename V, typename Comp = std::less<Value>>
    Value prefix_product_value_lt(const V &v, const Comp &cmp = Comp()) requires (hasValue) {
        return prefix_product_value(root, [&v, &cmp](const Value &src) {
            return cmp(src, v);
        });
    }
    /*
    return the product of longest prefix such that the product "res" of them has cmp(v, res) == false
    Assume monotonicity
    */
    template<typename V, typename Comp = std::less<Value>>
    Value prefix_product_value_leq(const V &v, const Comp &cmp = Comp()) requires (hasValue) {
        return prefix_product_value(root, [&v, &cmp](const Value &src) {
            return !cmp(v, src);
        });
    }
    std::array<Treap, 2> split_range(int l, int r) requires (hasSize) {
        assert(l <= r);
        Treap left = split_size(l);
        Treap right = split_size(r - l);
        swap(right);
        return {left, right};
    }
    Value range_prod(int l, int r) requires (hasValue && hasSize) {
        auto [left, right] = split_range(l, r);
        Value res = product();
        this->left_merge(left).right_merge(right);
        return res;
    }
    void range_transform(int l, int r, const auto &tag) requires (hasTag && hasSize) {
        auto [left, right] = split_range(l, r);
        if (!empty()) transform(tag);
        this->left_merge(left).right_merge(right);
    }
    void range_reverse(int l, int r) requires (Rev && hasSize) {
        auto [left, right] = split_range(l, r);
        if (!empty()) reverse();
        this->left_merge(left).right_merge(right);
    }
    /*
    1-base
    */
    Iterator kth(int k) requires (hasSize) {
        return Iterator(find_value([&k](const Value &v) {
            return v.size() < k;
        }), this);
    }
};
#endif // __BALU_TREAP__
