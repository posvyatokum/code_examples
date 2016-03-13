#include <iostream>

class RBTree {
    static const bool RED = true;
    static const bool BLACK = false;

    struct Node {
        Node* parent;
        Node* left;
        Node* right;
        bool color;
        int val;

        Node (Node* parent, Node* left, Node* right, bool color, int val):
            parent(parent), left(left), right(right), color(color), val(val) {}
    };

    Node* dummy_;
    Node* root_;

    bool get_color_ (Node* node) const {
        if (node == NULL) return BLACK;
        return node->color;
    }

    Node* get_uncle_ (Node* node) const {
        if (node->parent == NULL) return NULL;
        if (node->parent->parent == NULL) return NULL;
        return node->parent->parent->right == 
               node->parent ? node->parent->parent->left : node->parent->parent->right;
    }

    Node* get_grandparent_ (Node* node) const {
        if (node->parent == NULL) return NULL;
        return node->parent->parent;
    }

    void set_color_ (Node* node, bool color) {
        if (node == NULL) return;
        node->color = color;
    }

    void change_child_ (Node* node, Node* prev_child, Node* new_child) {
        if (node == NULL) return;
        if (node->right == prev_child) node->right = new_child;
        if (node->left == prev_child) node->left = new_child;
    }

    void change_parent_ (Node* node, Node* new_parent) {
        if (node == NULL) return;
        node->parent = new_parent;
    }

    void rotate_ (Node* node) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;
        change_child_(grandparent, parent, node);
        parent->parent = node;
        node->parent = grandparent;
        if (parent->left == node) {
            parent->left = node->right;
            change_parent_(node->right, parent);
            node->right = parent;
        } else {
            parent->right = node->left;
            change_parent_(node->left, parent);
            node->left = parent;
        }
        if (parent == root_) {
            root_ = node;
        }
    }

    void Balance (Node* node) {
        if (get_color_(node) == BLACK) return;
        if (node == root_) {
            set_color_(node, BLACK);
            return;
        }
        if (get_color_(node->parent) == BLACK) return;
        if (get_color_(get_uncle_(node)) == RED) {
            set_color_(node->parent, BLACK);
            set_color_(get_uncle_(node), BLACK);
            set_color_(get_grandparent_(node), RED);
            Balance(get_grandparent_(node));
            return;
        }
        Node* parent = node->parent;
        Node* grandparent = parent->parent;
        if ((parent->right == node) ^ (grandparent->right == parent)) {
            rotate_(node);
            rotate_(node);
            set_color_(node, BLACK);
            set_color_(node->right, RED);
            set_color_(node->left, RED);
        } else {
            rotate_(parent);
            set_color_(parent, BLACK);
            set_color_(parent->right, RED);
            set_color_(parent->left, RED);
        }
    }

    Node* find (int val) const {
        Node* node = root_;
        Node* prev = dummy_;
        while (node != NULL && node->val != val) {
            prev = node;
            if (node->val < val) node = node->right;
            else node = node->left;
        }
        return node != NULL ? node : prev;
    }
public:
    
    RBTree (): root_(NULL) {
        dummy_ = new Node (NULL, root_, root_, BLACK, 0);
        dummy_->parent = dummy_;
    }

    void insert (int val) {
        Node* node = find(val);
        if (node == dummy_) {
            root_ = new Node (dummy_, NULL, NULL, BLACK, val);
            dummy_->left = dummy_->right = root_;
            return;
        }
        if (node->val == val) return;
        Node* new_node = new Node(node, NULL, NULL, RED, val);
        if (node->val < val) node->right = new_node;
        else node->left = new_node;
        Balance(new_node);
    }

    bool in_tree (int val) {
        Node* node = find(val);
        return (node != dummy_ && node->val == val);
    }
};      
