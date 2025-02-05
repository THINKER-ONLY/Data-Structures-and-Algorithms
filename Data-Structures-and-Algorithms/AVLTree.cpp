#include <iostream>
#include <algorithm>

typedef struct AVLNode
{
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int data) : data(data), left(nullptr), right(nullptr), height(1) {}
    ~AVLNode()
    {
        delete left;
        delete right;
    }
} AVLNode; 

class AVLTree
{
    protected :
        AVLNode* root;

    public :
        AVLTree() : root(nullptr) {}

        ~AVLTree()
        {
            delete root;
        }

        void insert(int data)
        {
            root = insertNode(root, data);
        }

        void preorderTraversal()
        {
            preorder(root);
            std::cout << std::endl;
        }
        void inorderTraversal()
        {
            inorder(root);
            std::cout << std::endl;
        }
        void postorderTraversal()
        {
            postorder(root);
            std::cout << std::endl;
        }

        void remove(int data)
        {
            root = removeNode(root, data);
        }

    private :
        AVLNode* insertNode(AVLNode* node, int data)
        {
            if (node == nullptr)
            {
                return new AVLNode(data);
            }

            if (data < node->data)
            {
                node->left = insertNode(node->left, data);
            }
            else if (data > node->data)
            {
                node->right = insertNode(node->right, data);
            }
            else
            {
                return node;
            }

            updateHeight(node);

            int balance = balanceFactor(node);

            if (balance > 1 && data < node->left->data)
            {
                return rightRotate(node);
            }

            if (balance < -1 && data > node->right->data)
            {
                return leftRotate(node);
            }

            if (balance > 1 && data > node->left->data)
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            if (balance < -1 && data < node->right->data)
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

        void preorder(AVLNode* node)
        {
            if (node == nullptr) return;
            std::cout << node->data << " ";
            preorder(node->left);
            preorder(node->right);
        }

        void inorder(AVLNode* node)
        {
            if (node == nullptr) return;
            inorder(node->left);
            std::cout << node->data << " ";
            inorder(node->right);
        }

        void postorder(AVLNode* node) 
        {
            if (node == nullptr) return;
            postorder(node->left);
            postorder(node->right);
            std::cout << node->data << " ";
        }

        AVLNode* findMin(AVLNode* node)
        {
            while (node->left != nullptr)
            {
                node = node->left;
            }
            return node;
        }

        AVLNode* removeNode(AVLNode* node, int data)
        {
            if (node == nullptr) return node;

            if (data < node->data)
            {
                node->left = removeNode(node->left, data);
            }
            else if (data > node->data)
            {
                node->right = removeNode(node->right, data);
            }
            else
            {
                if (node->left == nullptr || node->right == nullptr)
                {
                    AVLNode* temp = node->left ? node->left : node->right;
                    if (temp == nullptr)
                    {
                        temp = node;
                        node = nullptr;
                    }
                    else
                    {
                        *node = *temp;
                        node->left = node->right = nullptr;
                    }
                    delete temp;
                }
                else
                {
                    AVLNode* temp = findMin(node->right);
                    node->data = temp->data;
                    node->right = removeNode(node->right, temp->data);
                }
            }
            if (node == nullptr) return node;

            updateHeight(node);
            int balance = balanceFactor(node);

            if (balance > 1 && balanceFactor(node->left) >= 0)
            {
                return rightRotate(node);
            }

            if (balance > 1 && balanceFactor(node->left) < 0)
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            if (balance < -1 && balanceFactor(node->right) <= 0)
            {
                return leftRotate(node);
            }

            if (balance < -1 && balanceFactor(node->right) > 0)
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

        AVLNode* rightRotate(AVLNode* y)
        {
            AVLNode* x = y->left;
            AVLNode* temp = x->right;

            x->right = y;
            y->left = temp;

            updateHeight(y);
            updateHeight(x);

            return x;
        }

        AVLNode* leftRotate(AVLNode* x)
        {
            AVLNode* y = x->right;
            AVLNode* temp = y->left;

            y->left = x;
            x->right = temp;

            updateHeight(x);
            updateHeight(y);

            return y;
        }

        int height(AVLNode* node)
        {
            if (node == nullptr) return 0;
            return node->height;
        }

        int balanceFactor(AVLNode* node)
        {
            if (node == nullptr) return 0;
            return height(node->left) - height(node->right);
        }

        void updateHeight(AVLNode* node)
        {
            if (node == nullptr) return ;
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
        
};

int main()
{
    AVLTree Tree;
    Tree.insert(14);
    Tree.insert(9);
    Tree.insert(5);
    Tree.insert(17);
    Tree.insert(11);
    Tree.insert(12);
    Tree.insert(7);
    Tree.insert(19);
    Tree.insert(16);
    Tree.insert(27);

    std::cout << "Preorder Traversal: " << std::endl;
    Tree.preorderTraversal();
    std::cout << "Inorder Traversal: " << std::endl;
    Tree.inorderTraversal();
    std::cout << "Postorder Traversal: " << std::endl;
    Tree.postorderTraversal();

    Tree.remove(5);
    std::cout << "删除5后的中序遍历: ";
    Tree.inorderTraversal();

    Tree.remove(19);
    std::cout << "删除40后的中序遍历: ";
    Tree.inorderTraversal();

    return 0;
}