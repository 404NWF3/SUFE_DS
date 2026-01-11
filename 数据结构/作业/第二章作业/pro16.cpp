#include <iostream>
#include <vector>
using namespace std;

template <class Type>
struct Node
{
    Type data;
    Node *next;
    Node(const Type &x, Node *p = nullptr) : data(x), next(p) {}
    Node() : next(nullptr) {}
    ~Node() {}
};

template <class Type>
class LinkList
{
    struct Node
    {
        Type data;
        Node *next;
        Node(const Type &x, Node *p = nullptr) : data(x), next(p) {}
        Node() : next(nullptr) {}
        ~Node() {}
    };

private:
    Node *head;     // 头指针
    Node *tail;     // 尾指针
    int length = 0; // 链表长度
public:
    LinkList()
    {
        head = new Node();
        tail = head;
    } // 带头结点

    LinkList(const LinkList &L)
    {
        // 复制构造函数
        head = new Node();
        Node *p = head, *q = L.head->next;
        while (q != nullptr)
        {
            p->next = new Node(q->data);
            p = p->next;
            q = q->next;
            length++;
        }
        tail = p;
    }

    LinkList(const vector<Type> &v)
    {
        // 通过向量初始化链表
        head = new Node();
        Node *p = head;
        for (const auto &item : v)
        {
            p->next = new Node(item);
            p = p->next;
            length++;
        }
        tail = p;
    }

    ~LinkList()
    {
        while (!head)
        {
            Node *p = head;
            head = head->next;
            delete p;
        }
    }

    int size() const { return length; }
    Node *getHead() const { return head; }
    void display() const
    {
        Node *p = head->next;
        while (p != nullptr)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    void pushback(const Type &x)
    {
        tail->next = new Node(x);
        tail = tail->next;
        length++;
    }
    LinkList<Type> solve(const LinkList<Type> &Y);
};

// template <class Type>
// LinkList<Type> solve(const LinkList<Type> &X, const LinkList<Type> &Y)
// {
//     // 返回两个有序链表的合并链表
//     LinkList<Type> Z;
//     Node *p = X.getHead()->next, *q = Y.getHead()->next, *r = Z.getHead();
//     while (*p != nullptr && *q != nullptr)
//     {
//         Z.pushback(p->data);
//         Z.pushback(q->data);
//     }
//     while (*p != nullptr)
//     {
//         Z.pushback(p->data);
//     }
//     while (*q != nullptr)
//     {
//         Z.pushback(q->data);
//     }
// }

template <class Type>
LinkList<Type> LinkList<Type>::solve(const LinkList<Type> &Y)
{
    // 返回两个有序链表的合并链表
    LinkList<Type> Z;
    Node *p = this->head->next, *q = Y.head->next;
    while (p != nullptr && q != nullptr)
    {
        Z.pushback(p->data);
        p = p->next;
        Z.pushback(q->data);
        q = q->next;
    }
    while (p != nullptr)
    {
        Z.pushback(p->data);
        p = p->next;
    }
    while (q != nullptr)
    {
        Z.pushback(q->data);
        q = q->next;
    }
    return Z;
}

int main()
{
    cout << "当 m < n 时: " << endl;
    LinkList<int> X1({1, 2, 3}), Y1({4, 5, 6, 7});
    cout << "X = ";
    X1.display();
    cout << "Y = ";
    Y1.display();

    LinkList Z1 = X1.solve(Y1);
    cout << "Z = ";
    Z1.display();

    cout << "当 m > n 时: " << endl;
    LinkList<int> X2({1, 2, 3, 4}), Y2({5, 6, 7});
    cout << "X = ";
    X2.display();
    cout << "Y = ";
    Y2.display();
    LinkList Z2 = X2.solve(Y2);
    cout << "Z = ";
    Z2.display();

    cout << "当 m = n 时: " << endl;
    LinkList<int> X3({1, 2, 3}), Y3({4, 5, 6});
    cout << "X = ";
    X3.display();
    cout << "Y = ";
    Y3.display();
    LinkList Z3 = X3.solve(Y3);
    cout << "Z = ";
    Z3.display();
    return 0;
}
