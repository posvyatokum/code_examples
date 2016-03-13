#include <iostream>

class Treap {
    struct Node {
        int id;
        int size;
        int prior;
        Node* left;
        Node* right;

        Node () {}

        Node (int id):
        id(id), size(0), prior(rand()), left(NULL), right(NULL) {}
    };
    Node* root_;

    int size_of(Node* vertex) {
        return vertex == NULL ? 0 : vertex->size;
    }

    void recalc(Node* &vertex) {
        if (vertex == NULL) return;
        vertex->size = size_of(vertex->left) + size_of(vertex->right) + 1;
    }

    Node* merge(Node* first, Node* second) {
        if (first == NULL || second == NULL) {
            recalc(first);
            recalc(second);
            return first == NULL ? second : first;
        }

        if (first->prior > second->prior) {
            first->right = merge(first->right, second);
            recalc(first);
            return first;
        } else {
            second->left = merge(first, second->left);
            recalc(second);
            return second;
        }
    }

    void split(Node* vertex, int x, Node* &less, Node* &gr_or_eq) {
        if (vertex == NULL) {
            less = gr_or_eq = NULL;
            return;
        }
        int key = size_of(vertex->left) + 1;

        if (key <= x) {
            split(vertex->right, x - key, vertex->right, gr_or_eq);
            less = vertex;
            recalc(less);
        } else {
            split(vertex->left, x, less, vertex->left);
            gr_or_eq = vertex;
            recalc(gr_or_eq);
        }
    }

    Node* operator [] (int x) {
        Node* p[3] = {};
        split(root_, x + 1, p[0], p[2]);
        split(p[0], x, p[0], p[1]);
        root_ = merge(merge(p[0], p[1]), p[2]);
        return p[1];
    }

public:
    Treap (): root_(NULL) {}

    void add(int x, int id) {
        Node* p[2] = {};
        split(root_, x, p[0], p[1]);
        root_ = merge(merge(p[0], new Node(id)), p[1]);
    }

    void erase(int x) {
        Node* p[3] = {};
        split(root_, x, p[0], p[2]);
        split(p[0], x - 1, p[0], p[1]);
        root_ = merge(p[0], p[2]);
    }

    int get_id(int x) {
        Node* p[3];
        split(root_, x, p[0], p[2]);
        split(p[0], x - 1, p[0], p[1]);
        int ans = p[1]->id;
        root_ = merge(merge(p[0], p[1]), p[2]);
        return ans;
    }
};

