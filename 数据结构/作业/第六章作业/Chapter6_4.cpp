#include <iostream>
#include <stack>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
public:
    BinaryTree() : root(nullptr) {}

    void insert(int val)
    {
        root = insertRec(root, val);
    }

    void postorder()
    {
        cout << "递归实现：";
        postOrderRec(root);
        cout << endl <<"非递归实现：";
        postOrderRecStack(root);
        cout << endl;
    }

private:
    Node *root;
    Node *insertRec(Node *node, int val)
    {
        if (node == nullptr)
            return new Node(val);
        if (val < node->data)
            node->left = insertRec(node->left, val);
        else
            node->right = insertRec(node->right, val);
        return node;
    }
    void postOrderRec(Node *node)
    {
        if (node != nullptr)
        {
            postOrderRec(node->left);
            postOrderRec(node->right);
            cout << node->data << " ";
        }
    }
    void postOrderRecStack(Node *node)
    {
        struct state{
            Node* n;
            bool visited;
            state(Node* node, bool vis): n(node), visited(vis) {}
        };
        
        stack<state> s;
        Node *current = node;

        while (current != nullptr || !s.empty())
        {
            while (current != nullptr)
            {
                s.push({current, false});
                current = current->left;
            }
            current = s.top().n;
            if (current->right == nullptr || s.top().visited)
            {
                cout << current->data << " ";
                s.pop();
                current = nullptr;
            }
            else
            {
                current = current->right;
                s.top().visited = true;
            }
        }
    }
};

int main()
{
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.postorder();
    return 0;
}