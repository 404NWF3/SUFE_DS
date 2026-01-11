#include <iostream>
using namespace std;

template <class Type>
class threadBinaryTree;

template <class Type>
// 中序线索化二叉树
class threadTreeNode
{
    template <class>
    friend class threadBinaryTree;
    // ltag=0，lchild为左子女指针
    // ltag=1，lchild为前驱线索
    // rtag=0，rchild为右子女指针
    // rtag=1，rchild为后继指针
public:
    int ltag, rtag;
    threadTreeNode *lchild, *rchild;
    Type data;

    threadTreeNode(const Type &item) : data(item), lchild(nullptr), rchild(nullptr), ltag(0), rtag(0) {}
};

template <class Type>
class threadBinaryTree
{
protected:
    threadTreeNode<Type> *root;
    void CreateInThread(threadTreeNode<Type> *current, threadTreeNode<Type> *&pre);
    threadTreeNode<Type> *Parent(threadTreeNode<Type> *t);
    void clearNode(threadTreeNode<Type>* node) {
        if (node != nullptr) {
            if (node->ltag == 0)
                clearNode(node->lchild);
            if (node->rtag == 0)
                clearNode(node->rchild);
            delete node;
        }
    }   

public:
    threadBinaryTree() : root(nullptr) {};
    ~threadBinaryTree(){
        clearNode(root);
    }
    void CreateInThread();
    threadTreeNode<Type> *First(threadTreeNode<Type> *current);
    threadTreeNode<Type> *Last(threadTreeNode<Type> *current);
    threadTreeNode<Type> *Next(threadTreeNode<Type> *current);
    threadTreeNode<Type> *Prior(threadTreeNode<Type> *current);
    void InOrder(void (*visit)(threadTreeNode<Type> *p));
    void PreOrder(void (*visit)(threadTreeNode<Type> *p));
    void PostOrder(void (*visit)(threadTreeNode<Type> *p));
    static void printNode(threadTreeNode<Type> *p) { cout << p->data << " "; }
    threadTreeNode<Type> *getRoot() { return root; }
    void setRoot(threadTreeNode<Type> *r) { root = r; }
};

template <class Type>
threadTreeNode<Type> *threadBinaryTree<Type>::First(threadTreeNode<Type> *current)
{
    threadTreeNode<Type> *p = current;
    if (!p)
        return nullptr;
    while (p->ltag == 0)
    {
        p = p->lchild;
    }
    return p;
}

template <class Type>
threadTreeNode<Type> *threadBinaryTree<Type>::Last(threadTreeNode<Type> *current)
{
    threadTreeNode<Type> *p = current;
    if (!p)
        return nullptr;
    while (p->rtag == 0)
        p = p->rchild;
    return p;
}

template <class Type>
threadTreeNode<Type> *threadBinaryTree<Type>::Next(threadTreeNode<Type> *current)
{
    threadTreeNode<Type> *p = current;
    if (p->rtag == 0)
        return First(p->rchild);
    else
        return p->rchild;
}

template <class Type>
threadTreeNode<Type> *threadBinaryTree<Type>::Prior(threadTreeNode<Type> *current)
{
    threadTreeNode<Type> *p = current;
    if (p->ltag == 0)
        return Last(p->lchild);
    else
        return p->lchild;
}

template <class Type>
void threadBinaryTree<Type>::InOrder(void (*visit)(threadTreeNode<Type> *p))
{
    threadTreeNode<Type> *p;
    for (p = First(root); p != nullptr; p = Next(p))
    {
        visit(p);
    }
}

template <class Type>
void threadBinaryTree<Type>::CreateInThread(threadTreeNode<Type> *current, threadTreeNode<Type> *&pre)
{
    if (!current)
        return;
    CreateInThread(current->lchild, pre);
    if (!current->lchild)
    {
        current->lchild = pre;
        current->ltag = 1;
    }
    if (pre && !pre->rchild)
    {
        pre->rchild = current;
        pre->rtag = 1;
    }
    pre = current;
    CreateInThread(current->rchild, pre);
}

template <class Type>
void threadBinaryTree<Type>::CreateInThread()
{
    threadTreeNode<Type> *pre = nullptr;
    CreateInThread(root, pre);
}

template <class Type>
void threadBinaryTree<Type>::PreOrder(void (*visit)(threadTreeNode<Type> *p))
{
    threadTreeNode<Type> *p = root;
    while (p)
    {
        visit(p);
        if (p->ltag == 0)
            p = p->lchild;
        else if (p->rtag == 0)
            p = p->rchild;
        else
        {
            while (p && p->rtag)
                p = p->rchild;
            if (p)
                p = p->rchild;
        }
    }
}

int main()
{
    auto n1 = new threadTreeNode<int>(1);
    auto n2 = new threadTreeNode<int>(2);
    auto n3 = new threadTreeNode<int>(3);
    auto n4 = new threadTreeNode<int>(4);
    auto n5 = new threadTreeNode<int>(5);
    auto n6 = new threadTreeNode<int>(6);

    n1->lchild = n2;
    n1->rchild = n3;
    n2->lchild = n4;
    n2->rchild = n5;
    n3->lchild = n6; // n3->rchild 为空

    threadBinaryTree<int> t;
    t.setRoot(n1);

    // 中序线索化
    t.CreateInThread();

    // 中序遍历测试，期望输出：4 2 5 1 6 3
    cout << "中序遍历: ";
    t.InOrder(threadBinaryTree<int>::printNode);
    cout << endl;

    cout << "前序遍历: ";
    t.PreOrder(threadBinaryTree<int>::printNode);
    cout << endl;

    return 0;
}
