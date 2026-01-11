#include <iostream>
#include <stack>
#include <queue>
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
        postOrderRecStack(root);
        cout << endl;
    }

    bool isComplete()
    {
        return isCompleteNode(root);
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
        struct state
        {
            Node *n;
            bool visited;
            state(Node *node, bool vis) : n(node), visited(vis) {}
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
    bool isCompleteNode(Node *node)
    {
        queue<Node*> q;
        q.push(node);

        bool end = false;
        while (!q.empty())
        {
            Node* cur = q.front();
            q.pop();

            if (cur == nullptr)
            {
                end = true;
                continue;
            }
            if (end)
                return false;

            q.push(cur->left);
            q.push(cur->right);
        }
        return true;
    }
};

int main()
{
    {
        BinaryTree tree;
        cout << "Test 1 - 空树，1 ：" << tree.isComplete() << '\n';
    }
    {
        BinaryTree tree;
        tree.insert(10);
        cout << "Test 2 - 单节点，1 ：" << tree.isComplete() << '\n';
    }
    {
        BinaryTree tree;
        // Perfect (complete) binary search tree
        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);
        cout << "Test 3 - 完美树 (5,3,7,2,4,6,8): 1 ：" << tree.isComplete() << '\n';
    }
    {
        BinaryTree tree;
        // Root has right child but no left child -> NOT complete
        tree.insert(1);
        tree.insert(3);
        tree.insert(2);
        cout << "Test 4 - 根节点有右子节点但无左子节点 (1,3,2): 0 ：" << tree.isComplete() << '\n';
    }
    return 0;
}