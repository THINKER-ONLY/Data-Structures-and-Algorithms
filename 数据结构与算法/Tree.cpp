#include <iostream>

class TreeNode
{
    public :
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data)
    {
        this->data = data;
        left = right = nullptr;
    }
};

class BinaryTree
{
    public :
    TreeNode* root;
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() 
    {
        clear(root);
    }
    void insert(int value)
    {
        root = insertNode(root, value);
    }
    void inorderTraversal()
    {
        inorder(root);
        std::cout << std::endl;
    }

    private :
    TreeNode* insertNode(TreeNode* node, int value)
    {
        if (node == nullptr)
        {
            return new TreeNode(value);
        }
        if (rand() % 2 == 0) 
        {
            node->left = insertNode(node->left, value);
        } 
        else 
        {
            node->right = insertNode(node->right, value);
        }
        return node;
    }

    void inorder(TreeNode* node)
    {
        if (node ==nullptr) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }
    void clear(TreeNode* node)
    {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

int main()
{
    BinaryTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);

    std::cout << "Inorder Traversal of Binary Tree" << std::endl;
    tree.inorderTraversal();

    //std::cout << "Inorder Traversal of Binary Tree" << std::endl;
    //tree.inorderTraversal();
    return 0;
}