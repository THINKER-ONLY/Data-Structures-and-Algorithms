#include <iostream>
using namespace std;

template<typename T>
class RedBlackTree {
private:
    enum Color { RED, BLACK };
    struct Node {
        T key;
        Color color;
        Node *left;
        Node *right;
        Node *parent;
        Node(T k, Color c, Node *l, Node *r, Node *p)
            : key(k), color(c), left(l), right(r), parent(p) {}
    };
    Node *root;
    Node *nil; // 哨兵节点

    void leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != nil)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nil)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *y) {
        Node *x = y->left;
        y->left = x->right;
        if (x->right != nil)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nil)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
        x->right = y;
        y->parent = x;
    }

    void insertFix(Node *z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node *uncle = z->parent->parent->right;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node *uncle = z->parent->parent->left;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Node *u, Node *v) {
        if (u->parent == nil)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    void deleteFix(Node *x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node *sibling = x->parent->right;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    sibling = x->parent->right;
                }
                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    x = x->parent;
                } else {
                    if (sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = x->parent->right;
                    }
                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node *sibling = x->parent->left;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    sibling = x->parent->left;
                }
                if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                    sibling->color = RED;
                    x = x->parent;
                } else {
                    if (sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = x->parent->left;
                    }
                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    Node *minimum(Node *z) {
        while (z->left != nil)
            z = z->left;
        return z;
    }

    void destroy(Node *node) {
        if (node != nil) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    RedBlackTree() {
        nil = new Node(T(), BLACK, nullptr, nullptr, nullptr);
        nil->left = nil;
        nil->right = nil;
        nil->parent = nil;
        root = nil;
    }

    ~RedBlackTree() {
        destroy(root);
        delete nil;
    }

    void insert(T key) {
        Node *z = new Node(key, RED, nil, nil, nil);
        Node *y = nil;
        Node *x = root;
        while (x != nil) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (y == nil)
            root = z;
        else if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        insertFix(z);
    }

    void remove(T key) {
        Node *z = find(key);
        if (z == nil)
            return;
        Node *y = z;
        Node *x;
        Color yOriginalColor = y->color;
        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (yOriginalColor == BLACK)
            deleteFix(x);
    }

    Node *find(T key) {
        Node *current = root;
        while (current != nil) {
            if (key == current->key)
                return current;
            else if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return nil;
    }

    void inorderTraversal(Node *node) {
        if (node != nil) {
            inorderTraversal(node->left);
            cout << node->key << "(" << (node->color == RED ? "R" : "B") << ") ";
            inorderTraversal(node->right);
        }
    }

    void printInorder() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    RedBlackTree<int> rbt;
    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(18);
    rbt.insert(10);
    rbt.insert(22);
    rbt.insert(8);
    rbt.insert(11);
    rbt.insert(26);
    rbt.insert(2);
    rbt.insert(6);
    rbt.insert(13);

    cout << "中序遍历红黑树:" << endl;
    rbt.printInorder();

    rbt.remove(18);
    rbt.remove(11);
    rbt.remove(3);
    rbt.remove(10);

    cout << "删除后的中序遍历:" << endl;
    rbt.printInorder();

    return 0;
}