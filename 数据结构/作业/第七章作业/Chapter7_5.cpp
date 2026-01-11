#include <iostream>
#include <stack>
using namespace std;

template <class Type>
class BinaryTree;

template <class Type>
class TreeNode
{
    template <class>
    friend class BinaryTree;

public:
    Type data;
    TreeNode *left, *right;

    TreeNode() : left(nullptr), right(nullptr) {}
    TreeNode(const Type &_data) : data(_data), left(nullptr), right(nullptr) {}
    TreeNode(const Type &_data, TreeNode *_left, TreeNode *_right) : data(_data), left(_left), right(_right) {}
};

template <class Type>
stack<Type> foundNode(TreeNode<Type> *node, const Type &);

template <class Type>
bool foundNodeRecursive(TreeNode<Type> *node, const Type &, stack<Type> &path);

int main()
{
    TreeNode<int> *root = new TreeNode<int>(1);
    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);
    root->left->left = new TreeNode<int>(4);
    root->left->right = new TreeNode<int>(5);
    root->right->right = new TreeNode<int>(6);

    int target = 5;
    cout << "Searching for node " << target << "..." << endl;
    stack<int> result = foundNode(root, target);

    if (result.empty())
    {
        cout << "Node not found." << endl;
    }
    else
    {
        cout << "Path to node (Root -> Target): ";
        stack<int> temp;
        while (!result.empty())
        {
            temp.push(result.top());
            result.pop();
        }

        while (!temp.empty())
        {
            cout << temp.top() << (temp.size() > 1 ? " -> " : "");
            temp.pop();
        }
        cout << endl;
    }

    target = 10;
    cout << "Searching for node " << target << "..." << endl;
    result = foundNode(root, target);

    if (result.empty())
    {
        cout << "Node not found." << endl;
    }
    else
    {
        cout << "Path to node (Root -> Target): ";
        stack<int> temp;
        while (!result.empty())
        {
            temp.push(result.top());
            result.pop();
        }

        while (!temp.empty())
        {
            cout << temp.top() << (temp.size() > 1 ? " -> " : "");
            temp.pop();
        }
        cout << endl;
    }

    return 0;
}

template <class Type>
stack<Type> foundNode(TreeNode<Type> *node, const Type &_data)
{
    // 先不考虑路径显示
    // x最多有一个
    stack<Type> path;
    if (foundNodeRecursive(node, _data, path))
        return path;
    else
        return {};
}

template <class Type>
bool foundNodeRecursive(TreeNode<Type> *node, const Type &_data, stack<Type> &path)
{
    if (!node)
        return false;
    path.push(node->data);

    if (node->data == _data)
    {
        return true;
    }
    if (foundNodeRecursive(node->left, _data, path))
        return true;
    if (foundNodeRecursive(node->right, _data, path))
        return true;
    path.pop();
    return false;
}