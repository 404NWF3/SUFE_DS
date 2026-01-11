#include <iostream>
using namespace std;

template <class Type>
class Solution
{
private:
    struct Node
    {
        Type data;
        Node *next;
        Node(const Type &x, Node *p = nullptr) : data(x), next(p) {}
        Node() : next(nullptr) {}
        ~Node() {}
    };
    Node *head; // 头指针

public:
    Solution() { head = new Node(); } // 带头结点
    Solution(int n, int i, int k);    // 构造函数，建立一个含n个元素的环形链表
    ~Solution()
    {
        while (!head)
        {
            Node *p = head;
            head = head->next;
            delete p;
        }
    }

    void display(int i = 0)
    {
        // head为假头节点，使用双指针法输出环形链表
        Node *p = head->next, *q = head->next;
        while (i--)
        {
            p = p->next;
            q = q->next;
        }
        cout << p->data << " ";
        p = p->next;
        q = q->next->next;
        while (p != q)
        {
            cout << p->data << " ";
            p = p->next;
            q = q->next->next;
        }
    }

    void display(Node *cur)
    {
        // 以cur为起点，输出环形链表
        Node *p = cur, *q = cur;
        cout << p->data << " ";
        p = p->next;
        q = q->next->next;
        while (p != q)
        {
            cout << p->data << " ";
            p = p->next;
            q = q->next->next;
        }
    }

    void insert(const Type &x); // 插入元素
};

template <class Type>
Solution<Type>::Solution(int n, int i, int k)
{
    // 建立一个含n个元素(1-n)的环形链表
    // 从数字i开始，每次步长为k，删除该元素，直到链表为空

    // 1. 初始化环形链表
    cout << "输入参数: n = " << n << ", i = " << i << ", k = " << k << endl;
    head = new Node();
    Node *tail = head;
    for (int j = 1; j <= n; j++)
    {
        tail->next = new Node(j);
        tail = tail->next;
    }
    tail->next = head->next; // 形成环

    cout << "初始化环形链表: " << endl;
    display();
    cout << endl;

    // 2. 找到i位置
    Node *p = head, *q = head->next; // 增强鲁棒性
    while (--i)
    {
        p = p->next;
        q = q->next;
    }

    cout << "最终结果为：" << endl;
    // 3. 以k为步长删除元素
    while (q != nullptr)
    {
        int counter = k;

        if (p == q)
        {
            cout << q->data << " ";
            delete q;
            break;
        }

        while (--counter)
        {
            p = p->next;
            q = q->next;
        }

        cout << q->data << " ";
        p->next = q->next;
        Node *cur = q;
        q = p->next;
        delete cur;
    }
    cout << endl;
}

int main()
{
    Solution<int> s(10, 1, 3);
    Solution<int> t(10, 5, 12);
    return 0;
}