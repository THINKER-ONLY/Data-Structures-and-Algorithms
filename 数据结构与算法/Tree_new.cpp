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
    protected :
    TreeNode* root;
    public :
    BinaryTree() : root(nullptr) {}
    virtual ~BinaryTree() 
    {
        delete root;
    }

    virtual void insert(int value) = 0;
    virtual void find(int value) = 0;
    virtual void remove(int value) = 0;

    int Height()
    {
        return getHeight(root);
    }

    int Nodes()
    {
        return countNodes(root);
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

    bool isBalanced()
    {
        return isBalanced(root);
    }

    protected :
    int getHeight(TreeNode* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return 1 + std::max(leftHeight, rightHeight);
    }
    int countNodes(TreeNode* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
    void preorder(TreeNode* node)
    {
        if (node == nullptr) return;
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
    void inorder(TreeNode* node)
    {
        if (node == nullptr) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }
    void postorder(TreeNode* node)
    {
        if (node == nullptr) return;
        inorder(node->left);
        inorder(node->right);
        std::cout << node->data << " ";
    }
    bool isBalanced(TreeNode* node)
    {
        if (node == nullptr)
        {
            return true;
        }
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return std::abs(leftHeight - rightHeight <= 1) && isBalanced(node->left) && isBalanced(node->right);
    }

};

class BinarySearchTree : public BinaryTree
{
    public :
    void insert(int value) override
    {
        root = insertNode(root, value);
    }

    void find(int value) override
    {
        TreeNode* foundNode = findNode(root, value);
        if (foundNode != nullptr) 
        {
            std::cout << "Node found. The number is: " << foundNode->data << std::endl;
        } 
        else 
        {
            std::cout << "Node not found." << std::endl;
        }
    }

    void remove(int value) override
    {
        root = removeNode(root, value);
    }

    private :
    TreeNode* insertNode(TreeNode* node, int value)
    {
        if (node == nullptr)
        {
            return new TreeNode(value);
        }
        if (value < node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else
        {
            node->right = insertNode(node->right, value);
        }

        return node;
    }

    TreeNode* findNode(TreeNode* node , int value)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (value == node->data)
        {
            return node;
        }
        if (value < node->data)
        {
            return findNode(node->left, value);
        }
        else
        {
            return findNode(node->right, value);
        }
    }

    TreeNode* removeNode(TreeNode* node, int value)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        if (value == node->data)
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr)
            {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                TreeNode* temp = node->right;
                while (temp->left != nullptr)
                {
                    temp = temp->left;
                }
                node->data = temp->data;
                node->right = removeNode(node->right, temp->data);
            }
        }
        else if (value < node->data)
        {
            node->left = removeNode(node->left, value);
        }
        else
        {
            node->right = removeNode(node->right, value);
        }
        return node;
    }
};

int main()
{
    BinarySearchTree bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(8);
    bst.insert(3);
    bst.insert(7);
    bst.insert(6);
    bst.insert(9);
    bst.insert(12);
    bst.insert(18);

    std::cout << "Height of the tree: " << bst.Height() << std::endl;
    std::cout << "Number of nodes: " << bst.Nodes() << std::endl;
    std::cout << "Is the tree balanced? " << (bst.isBalanced() ? "Yes" : "No") << std::endl;

    std::cout << "Preorder Traversal: ";
    bst.preorderTraversal();
    
    std::cout << "Inorder Traversal: ";
    bst.inorderTraversal();

    std::cout << "Postorder Traversal: ";
    bst.postorderTraversal();

    bst.find(8);
    bst.find(20);

    bst.remove(5);
    
    std::cout << "Preorder Traversal: ";
    bst.preorderTraversal();

    std::cout << "Inorder Traversal: ";
    bst.inorderTraversal();

    std::cout << "Postorder Traversal: ";
    bst.postorderTraversal();

    return 0;
}