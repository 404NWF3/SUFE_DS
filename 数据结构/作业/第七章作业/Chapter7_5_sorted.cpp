#include <iostream>
using namespace std;

template <class Type>
class BinaryTree;

template <class Type>
class TreeNode
{
    template <class>
    friend class BinaryTree;

private:
    Type data;
    TreeNode *left, *right;

public:
    TreeNode() : left(nullptr), right(nullptr) {}
    TreeNode(const Type &_data) : data(_data), left(nullptr), right(nullptr) {}
    TreeNode(const Type &_data, TreeNode *_left, TreeNode *_right) : data(_data), left(_left), right(_right) {}
};

template <class Type>
class BinaryTree
{
private:
    TreeNode<Type> *root;
    void clear(TreeNode<Type> *node)
    {
        if (!node)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    void insert(TreeNode<Type> *node, const Type &_data)
    {
        if (!node)
            return;
        if (_data <= node->data)
        {
            if (!node->left)
                node->left = new TreeNode(_data);
            else
                insert(node->left, _data);
        }
        else if (_data > node->data)
        {
            if (!node->right)
                node->right = new TreeNode(_data);
            else
                insert(node->right, _data);
        }
    }
    void find(TreeNode<Type> *node, const Type &_data)
    {
        // x 的值不多于一个，先不考虑输出所有祖先节点
        if (!node)
            return;
        cout << node->data << " ";

        if (_data == node->data)
        {
            return;
        }
        else if (_data > node->data)
        {
            if (!node->right)
            {
                cout << endl
                     << _data << " Not in the Tree!" << endl;
                return;
            }
            find(node->right, _data);
        }
        else if (_data < node->data)
        {
            if (!node->left)
            {
                cout << endl
                     << _data << " Not in the Tree!" << endl;
                return;
            }
            find(node->left, _data);
        }
    }
    void preOrder(TreeNode<Type> *node)
    {
        if (!node)
            return;
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(TreeNode<Type> *node)
    {
        if (!node)
            return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

public:
    BinaryTree()
    {
        root = nullptr;
    }
    ~BinaryTree() { clear(root); }
    void insert(const Type &_data)
    {
        if (!root)
            root = new TreeNode(_data);
        else
            insert(root, _data);
    }
    void find(const Type &_data)
    {
        find(root, _data);
    }
    void preOrder()
    {
        preOrder(root);
    }

    void inOrder()
    {
        inOrder(root);
    }
};

int main()
{
    BinaryTree<int> tree;
    tree.insert(7);
    tree.insert(4);
    tree.insert(9);
    tree.insert(1);
    tree.insert(5);
    tree.insert(8);
    tree.insert(10);
    tree.insert(2);
    cout << "PreOrder: ";
    tree.preOrder();
    cout << endl;
    cout << "InOrder: ";
    tree.inOrder();
    cout << endl;

    cout << "Find the path of 7: ";
    tree.find(7);
    cout << endl;

    cout << "Find the path of 4: ";
    tree.find(4);
    cout << endl;

    cout << "Find the path of 1: ";
    tree.find(1);
    cout << endl;

    cout << "Find the path of 2: ";
    tree.find(2);
    cout << endl;

    cout << "Find the path of 5: ";
    tree.find(5);
    cout << endl;

    cout << "Find the path of 9: ";
    tree.find(9);
    cout << endl;

    cout << "Find the path of 8: ";
    tree.find(8);
    cout << endl;

    cout << "Find the path of 10: ";
    tree.find(10);
    cout << endl;

    cout << "Find the path of -1: ";
    tree.find(-1);
    cout << endl;

    cout << "Find the path of 3: ";
    tree.find(3);
    cout << endl;

    cout << "Find the path of 6: ";
    tree.find(6);
    cout << endl;

    cout << "Find the path of 20: ";
    tree.find(20);
    cout << endl;

    return 0;
}