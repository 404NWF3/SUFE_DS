#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class treeNode
{
public:
    int data;
    treeNode *lchild, *rchild;
    treeNode(int data = 0, treeNode *lchild = nullptr, treeNode *rchild = nullptr) : data(data), lchild(lchild), rchild(rchild) {}

    void preOrder()
    {
        cout << data << " ";
        if (lchild)
            lchild->preOrder();
        if (rchild)
            rchild->preOrder();
    }

    void inOrder()
    {
        if (lchild)
            lchild->inOrder();
        cout << data << " ";
        if (rchild)
            rchild->inOrder();
    }
};

treeNode *HuffmanTree(const vector<int> &seq)
{
    struct Cmp
    {
        bool operator()(const treeNode *a, const treeNode *b) const
        {
            return a->data > b->data;
        }
    };
    priority_queue<treeNode *, vector<treeNode *>, Cmp> pq;
    for (int val : seq)
        pq.push(new treeNode(val));

    while (pq.size() > 1)
    {
        treeNode *left = pq.top();
        pq.pop();
        treeNode *right = pq.top();
        pq.pop();
        treeNode *parent = new treeNode(left->data + right->data, left, right);
        pq.push(parent);
    }

    return pq.top();
}

int main()
{
    vector<int> seq = {5, 6, 3, 7, 4};
    treeNode *root = HuffmanTree(seq);

    cout << "前序: ";
    root->preOrder();
    cout << endl;

    cout << "中序: ";
    root->inOrder();
    cout << endl;

    return 0;
}