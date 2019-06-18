#ifndef RELAXEDLEONARDOHEAP_HPP

#include <memory>

namespace Leonardo {
    template <class T, class Compare=std::less<T>>
    class RelaxedHeap {
        public:
            typedef T value_type;
            typedef Compare compare_type;

        private:
        struct Node {
            value_type value;

            int order;
            bool marked;

            std::unique_ptr<Node> left, right;
            std::unique_ptr<Node> next;

            Node* get_proper_sub_node(const compare_type comp = compare_type()) {
                if (comp(left->value, right->value))
                    return right.get();
                else
                    return left.get();
            }

            void semi_mark_sweep(const compare_type& comp = compare_type()) {
                for (Node* it = this;;) {
                    if (it->order > 1) {
                        Node *child = it->get_proper_sub_node(comp);

                        if (comp(it->value, child->value)) {
                            std::swap(it->value, child->value);
                            child->marked = it->marked;
                            it->marked = false;
                            
                            if (child->order > 1) {
                                if (child->left->marked)
                                    it = child->left.get();
                                else if (child->right->marked)
                                    it = child->right.get();
                                else
                                    break;
                            } else {
                                child->marked = false;
                                break;
                            }
                        } else {
                            it->marked = false;
                            break;
                        }
                    } else {
                        it->marked = false;
                        break;
                    }
                }
            }

            void mark_sweep(const compare_type& comp = compare_type()) {
                if (left->marked)
                    left->semi_mark_sweep(comp);
                else if (right->marked)
                    right->semi_mark_sweep(comp);

                semi_mark_sweep(comp);
            }
        };

        compare_type comp;
        std::unique_ptr<Node> root;

        public:

        RelaxedHeap (const compare_type& cmp = Compare()) : comp(cmp), root(nullptr) {}

        void push(value_type value) {
            if (empty()) {
                root.reset(new Node {value, 1, false, nullptr, nullptr, nullptr});
            } else {
                std::unique_ptr<Node> tmp {new Node {value, 1, false, nullptr, nullptr, nullptr}};

                if (comp(value, root->value)) {
                    std::swap(tmp->value, root->value);
                    
                    if (root->order > 1) {
                        root->marked = true;
                        root->mark_sweep(comp);
                    }
                }

                Node* t1 = root.get();
                Node* t2 = root->next.get();

                if (t2 && t2->order == (t1->order + 1)) {
                    tmp->order = t2->order + 1;
                    tmp->next = std::move(t2->next);
                    tmp->left = std::move(root->next);
                    tmp->right = std::move(root);
                    root = std::move(tmp); 
                } else if (1 == t1->order) {
                    tmp->order = 0;
                    tmp->next = std::move(root);
                    root = std::move(tmp);
                } else {
                    tmp->order = 1;
                    tmp->next = std::move(root);
                    root = std::move(tmp); 
                }
            }
        }

        void pop() {
            if (root->order > 1) {
                std::unique_ptr<Node> l = std::move(root->left);
                std::unique_ptr<Node> r = std::move(root->right);
                std::unique_ptr<Node> next = std::move(root->next);

                if (l->marked)
                    l->semi_mark_sweep(comp);
                else if (r->marked)
                    r->semi_mark_sweep(comp);

                l->next = std::move(next);
                r->next = std::move(l);
                root = std::move(r);
            } else {
                root = std::move(root->next);
            }
            
            if (empty()) return;

            Node* tmp = root.get();

            for (Node* it = root->next.get(); it; it = it->next.get())
                if (comp(tmp->value, it->value))
                    tmp = it;

            if (tmp != root.get()) {
                std::swap(tmp->value, root->value);

                if (tmp->order > 1) {
                    tmp->marked = true;
                    tmp->mark_sweep(comp);
                }
            }
        }

        value_type top() const {
            return root->value;
        }

        bool empty() const {
            return not root;
        }
    };
}

#endif
