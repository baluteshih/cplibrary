#pragma once

#include "DataStructure/DefaultAllocator.hpp"
#include "Algebra/ValidOperation.hpp"
#include "Algebra/size_value.hpp"

template<typename Key = void, 
         typename Value = size_v,
         typename Tag = void, 
         bool Rev = false,
         template<typename> class Allocator = DefaultAllocator
>
class Splay {
    static constexpr bool hasKey = !std::is_void_v<Key>;
    static constexpr bool hasValue = !std::is_void_v<Value>;
    static constexpr bool hasTag = !std::is_void_v<Tag>;
    static constexpr bool hasTagToKey = Addable<Key, Tag>;
    static constexpr bool hasTagToValue = Addable<Value, Tag>;
    static constexpr bool hasSize = requires(Value v) { v.size(); };
    static constexpr bool hasValueReverse = requires(Value v) { v.reverse(); };
    struct Empty {};
    template <bool Condition, typename T>
    static auto get_default() {
        if constexpr (Condition) return T();
        else return Empty{};
    }
    static_assert(hasKey || hasValue);
    static_assert(!hasValue || Addable<Value, Value>);
    static_assert(!hasTag || Addable<Tag, Tag>);
    struct node {
        node *l = nullptr, *r = nullptr, *f = nullptr;
        [[no_unique_address]] std::conditional_t<hasKey, Key, Empty> key = get_default<hasKey, Key>();
        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty> org = get_default<hasValue, Value>();
        [[no_unique_address]] std::conditional_t<hasValue, Value, Empty> val = get_default<hasValue, Value>();
        [[no_unique_address]] std::conditional_t<hasTag, Tag, Empty> lazy = get_default<hasTag, Tag>();
        [[no_unique_address]] std::conditional_t<Rev, int, Empty> rev = get_default<Rev, int>();
        void up() {
            if constexpr (hasValue) {
                val = org;
                if (l) val = l->val + org;
                if (r) val = val + r->val;
            }
            if (l) l->f = this;
            if (r) r->f = this;
        }
        void give_tag(const auto &tag) requires (hasTag) {
            if constexpr (hasTagToValue) {
                org = org + tag; 
                val = val + tag;
            }
            if constexpr (hasTagToKey) {
                key = key + tag;
            }
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
            bool need_rev = false;
            if constexpr (Rev) need_rev = rev;
            bool need_tag = false;
            if constexpr (hasTag) { 
                if constexpr (std::equality_comparable<Tag>) need_tag = !(lazy == Tag());
                else need_tag = true;
            }
            if (!need_rev && !need_tag) return;
            if (l) {
                if constexpr (hasTag) if (need_tag) l->give_tag(lazy);
                if constexpr (Rev) if (need_rev) l->reverse();
            }
            if (r) {
                if constexpr (hasTag) if (need_tag) r->give_tag(lazy);
                if constexpr (Rev) if (need_rev) r->reverse();
            }
            if constexpr (hasTag) lazy = Tag();
            if constexpr (Rev) rev = 0;
        }
        node() = default;
        node(const auto &v) requires (!hasKey || !hasValue) {
            if constexpr (hasKey) key = Key(v);
            else org = val = Value(v);
        }
        node(const auto &k, const auto &v) requires (hasKey && hasValue) : key(k), org(v), val(v) {}
        friend std::ostream& operator<<(std::ostream& os, const node &v) {
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
            std::cerr << "\e[0m\n";
        }
    };
    using NodeAlloc = Allocator<node>;
    node *root = nullptr;
    static void push_all(node *x) {
        if (!x) return;
        static std::vector<node*> st;
        st.clear();
        node *cur = x;
        while (cur) {
            st.push_back(cur);
            cur = cur->f;
        }
        for (int i = (int)st.size() - 1; i >= 0; --i) {
            if constexpr (hasTag || Rev) st[i]->down();
        }
    }
    static void rotate(node *x) {
        node *y = x->f, *z = y->f;
        int k = (y->r == x);
        if (z) (z->l == y ? z->l : z->r) = x;
        x->f = z;
        node *c = (k ? x->l : x->r);
        (k ? y->r : y->l) = c;
        if (c) c->f = y;
        (k ? x->l : x->r) = y;
        y->f = x;
        y->up();
        x->up();
    }
    static void splay_node(node *x, node *goal = nullptr) {
        if (!x) return;
        while (x->f != goal) {
            node *y = x->f, *z = y->f;
            if (z != goal) {
                if ((z->l == y) ^ (y->l == x)) rotate(x);
                else rotate(y);
            }
            rotate(x);
        }
    }
    static void split(node *source, node *&left, node *&right, const auto &condition) {
        if (!source) return void(left = right = nullptr);
        node *cur = source, *last = nullptr, *split_point = nullptr;
        while (cur) {
            if constexpr (hasTag || Rev) cur->down();
            last = cur;
            if (condition(cur)) {
                split_point = cur;
                cur = cur->r;
            }
            else {
                cur = cur->l;
            }
        }
        if (last) splay_node(last);
        if (split_point) {
            splay_node(split_point); 
            left = split_point;
            right = left->r;
            if (right) right->f = nullptr;
            left->r = nullptr;
            left->up();
        }
        else {
            left = nullptr;
            right = last;
        }
    }
    static void split_value(node *source, node *&left, node *&right, const auto &condition) requires (hasValue) {
        if (!source) return void(left = right = nullptr);
        node *cur = source, *last = nullptr, *split_point = nullptr;
        Value left_product = Value();
        while (cur) {
            if constexpr (hasTag || Rev) cur->down();
            last = cur;
            Value current = left_product + get_val(cur->l) + cur->org; 
            if (condition(current)) {
                split_point = cur;
                left_product = current;
                cur = cur->r;
            }
            else {
                cur = cur->l;
            }
        }
        if (last) splay_node(last);
        if (split_point) {
            splay_node(split_point);
            left = split_point;
            right = left->r;
            if (right) right->f = nullptr;
            left->r = nullptr;
            left->up();
        }
        else {
            left = nullptr;
            right = last;
        }
    }
    static Value prefix_product(node *&source, const auto &condition) requires (hasValue) {
        if (!source) return Value();
        node *cur = source, *last = nullptr;
        Value res = Value();
        while (cur) {
            if constexpr (hasTag || Rev) cur->down();
            last = cur;
            if (condition(cur)) {
                res = res + get_val(cur->l) + cur->org;
                cur = cur->r;
            }
            else {
                cur = cur->l;
            }
        }
        if (last) {
            splay_node(last);
            source = last;
        }
        return res;
    }
    static Value prefix_product_cond(node *&source, const auto &left_product, const auto &condition) requires (hasValue) {
        if (!source) return left_product;
        node *cur = source, *last = nullptr;
        Value current_left = left_product;
        while (cur) {
            if constexpr (hasTag || Rev) cur->down();
            last = cur;
            Value current = current_left + get_val(cur->l) + cur->org;
            if (condition(current)) {
                current_left = current;
                cur = cur->r;
            }
            else {
                cur = cur->l;
            }
        }
        if (last) {
            splay_node(last);
            source = last;
        }
        return current_left;
    }
    static node *merge(node *left, node *right) {
        if (!left || !right) return left ? left : right;
        node *mx = find_max(left);
        splay_node(mx);
        mx->r = right;
        right->f = mx;
        mx->up();
        return mx;
    }
    static auto get_key(node *a, auto Default = Key()) requires (hasKey) { return a ? a->key : Default; }
    static Value get_org(node *a, Value Default = Value()) requires (hasValue) { return a ? a->org : Default; }
    static Value get_val(node *a, Value Default = Value()) requires (hasValue) { return a ? a->val : Default; }
    static size_t get_size(node *a) requires (hasSize) { return a ? a->val.size() : 0; }
    static void free(node *&ptr) {
        if (ptr == nullptr) return;
        free(ptr->l);
        free(ptr->r);
        NodeAlloc::deallocate(ptr);
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
    static node* find_kth(node *&source, int k) requires (hasSize) {
        node *cur = source, *last = nullptr;
        while (cur) {
            if constexpr (hasTag || Rev) cur->down();
            last = cur;
            int l_sz = get_size(cur->l);
            if (k < l_sz) {
                cur = cur->l;
            }
            else if (k == l_sz) {
                break;
            }
            else {
                k -= l_sz + 1;
                cur = cur->r;
            }
        }
        if (cur) {
            splay_node(cur);
            source = cur;
            return cur;
        }
        else if (last) {
            splay_node(last);
            source = last;
        }
        return nullptr;
    }
    static node* find_next(node *ptr) {
        assert(ptr != nullptr);
        push_all(ptr);
        if (ptr->r != nullptr) return find_min(ptr->r);
        while (ptr->f != nullptr && ptr->f->r == ptr) ptr = ptr->f;
        return ptr->f;
    }
    static node* find_prev(node *ptr) {
        assert(ptr != nullptr);
        push_all(ptr);
        if (ptr->l != nullptr) return find_max(ptr->l);
        while (ptr->f != nullptr && ptr->f->l == ptr) ptr = ptr->f;
        return ptr->f;
    }
    node *find(const auto &condition) {
        node *cur = root, *res = nullptr, *last = nullptr;
        while (cur != nullptr) {
            if constexpr (hasTag || Rev) cur->down();
            last = cur;
            if (condition(cur)) cur = cur->r;
            else {
                res = cur;
                cur = cur->l;
            }
        }
        if (last) { splay_node(last); root = last; }
        if (res && res != last) { splay_node(res); root = res; }
        return res;
    }
    node *find_value(const auto &condition) requires (hasValue) {
        node *cur = root, *res = nullptr, *last = nullptr;
        Value left_product = Value();
        while (cur != nullptr) {
            if constexpr (hasTag || Rev) cur->down();
            last = cur;
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
        if (res) { splay_node(res); root = res; }
        else if (last) { splay_node(last); root = last; }
        return res;
    }
public:
    Splay() = default;
    Splay(node *root_) : root(root_) {}
    Splay(const auto &v) requires (!hasKey || !hasValue) : root(NodeAlloc::allocate(v)) {}
    Splay(const auto &k, const auto &v) requires (hasKey && hasValue) : root(NodeAlloc::allocate(k, v)) {}
    void destruct() { free(root); }
    void reverse() requires (Rev) {
        if (root) root->reverse();
    }
    void transform(const auto &tag) requires (hasTag) {
        if (root) root->give_tag(tag);
    }
    Splay& left_merge(auto&& left) requires std::same_as<std::decay_t<decltype(left)>, Splay> {
        root = merge(left.root, root);
        left.root = nullptr;
        return *this;
    }
    Splay& right_merge(auto&& right) requires std::same_as<std::decay_t<decltype(right)>, Splay> {
        root = merge(root, right.root);
        right.root = nullptr;
        return *this;
    }
    static Splay merge(auto&& left, auto&& right) 
        requires (std::same_as<std::decay_t<decltype(left)>, Splay> &&
                  std::same_as<std::decay_t<decltype(right)>, Splay>) {
        Splay res(merge(left.root, right.root));
        left.root = right.root = nullptr;
        return res;
    }
    void swap(Splay &rhs) { std::swap(root, rhs.root); }
    bool empty() const { return root == nullptr; }
    int size() const requires (hasSize) { return get_size(root); }
    void push_back(const auto &v) { right_merge(Splay(v)); }
    void push_back(const auto &k, const auto &v) requires (hasKey && hasValue) { right_merge(Splay(k, v)); }
    void push_front(const auto &v) { left_merge(Splay(v)); }
    void push_front(const auto &k, const auto &v) requires (hasKey && hasValue) { left_merge(Splay(k, v)); }
    struct Iterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using reference         = const node&;
        using value_type        = node;
        using pointer           = node*; 
        Iterator(node* ptr, Splay *tree) : m_ptr(ptr), m_tree(tree) {}
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
            if (m_ptr == nullptr) m_ptr = find_max(m_tree->root);
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
        void access_ptr() { push_all(m_ptr); }
    private:
        node* m_ptr;
        Splay* m_tree;
        friend class Splay;
    };
    Iterator begin() { return Iterator(find_min(root), this); }
    Iterator end() { return Iterator(nullptr, this); }
    Iterator rbegin() { return Iterator(find_max(root), this); }
    void splay(Iterator it) {
        if (it != end()) {
            node *x = it.operator->();
            push_all(x);
            splay_node(x);
            root = x;
        }
    }
    Iterator bound_condition(const auto &condition) { return Iterator(find(condition), this); }
    Iterator bound_condition_value(const auto &condition) requires (hasValue) { return Iterator(find_value(condition), this); }
    template<typename K, typename Comp = std::less<Key>>
    Iterator lower_bound(const K &k, const Comp &cmp = Comp()) requires (hasKey) {
        return Iterator(find([&k, &cmp](node *src) { return cmp(src->key, k); }), this);
    }
    template<typename K, typename Comp = std::less<Key>>
    Iterator upper_bound(const K &k, const Comp &cmp = Comp()) requires (hasKey) {
        return Iterator(find([&k, &cmp](node *src) { return !cmp(k, src->key); }), this);
    }
    template<typename V, typename Comp = std::less<Value>>
    Iterator lower_bound_value(const V &v, const Comp &cmp = Comp()) requires (hasValue) {
        return Iterator(find_value([&v, &cmp](const Value &src) { return cmp(src, v); }), this);
    }
    template<typename V, typename Comp = std::less<Value>>
    Iterator upper_bound_value(const V &v, const Comp &cmp = Comp()) requires (hasValue) {
        return Iterator(find_value([&v, &cmp](const Value &src) { return !cmp(v, src); }), this);
    }
    void erase(Iterator it) {
        if (it == end()) return;
        node *target = it.operator->();
        splay_node(target);
        if (target->l) target->l->f = nullptr;
        if (target->r) target->r->f = nullptr;
        root = merge(target->l, target->r);
        NodeAlloc::deallocate(target);
    }
    Splay split_key(const auto &condition) {
        node *left;
        split(root, left, root, condition);
        return Splay(left);
    }
    template<typename K, typename Comp = std::less<Key>>
    Splay split_key_lt(const K &k, const Comp &cmp = Comp()) requires (hasKey) {
        return split_key([&k, &cmp](node *src) { return cmp(src->key, k); });
    }
    template<typename K, typename Comp = std::less<Key>>
    Splay split_key_leq(const K &k, const Comp &cmp = Comp()) requires (hasKey) {
        return split_key([&k, &cmp](node *src) { return !cmp(k, src->key); });
    }
    Splay split_value(const auto &condition) requires (hasValue) {
        node *left;
        split_value(root, left, root, condition);
        return Splay(left);
    }
    Splay split_size(const int &k) requires (hasSize) {
        if (k <= 0) return Splay();
        if (k >= size()) {
            Splay left(root);
            root = nullptr;
            return left;
        }
        node *kth_node = find_kth(root, k); 
        node *left_root = kth_node->l;
        if (left_root) left_root->f = nullptr;
        kth_node->l = nullptr;
        kth_node->up();
        return Splay(left_root);
    }
    Key get_key() requires (hasKey) { return get_key(root); }
    Value product() requires (hasValue) { return get_val(root); }
    template<typename K, typename Comp = std::less<Key>>
    Value prefix_product_key_lt(const K &k, const Comp &cmp = Comp()) requires (hasKey && hasValue) {
        return prefix_product(root, [&k, &cmp](node *src) {
            return cmp(src->key, k);
        });
    }
    template<typename K, typename Comp = std::less<Key>>
    Value prefix_product_key_leq(const K &k, const Comp &cmp = Comp()) requires (hasKey && hasValue) {
        return prefix_product(root, [&k, &cmp](node *src) {
            return !cmp(k, src->key);
        });
    }
    Value prefix_product_cond(const auto &condition) requires (hasValue) {
        return prefix_product_cond(root, Value(), condition);
    }
    std::array<Splay, 2> split_range(int l, int r) requires (hasSize) {
        assert(l <= r);
        Splay left = split_size(l);
        Splay right = split_size(r - l);
        swap(right);
        return {std::move(left), std::move(right)};
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
    Iterator kth(int k) requires (hasSize) {
        return Iterator(find_kth(root, k), this);
    }
};
