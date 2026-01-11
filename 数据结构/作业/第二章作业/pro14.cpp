#include <iostream>
using namespace std;

template <class Type>
class LinkList
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
    LinkList() { head = new Node(); } // 带头结点
    ~LinkList()
    {
        while (!head)
        {
            Node *p = head;
            head = head->next;
            delete p;
        }
    }

    void insert(const Type &a, const Type &b)
    {
        // 在值为a的节点后插入值为b的节点
        Node *p = head;
        while (p->next != nullptr && p->next->data != b)
            p = p->next;

        if (p->next != nullptr)
            // 找到值为b的节点
            p->next = new Node(a, p->next);
        else
        {
            // 未找到值为b的节点
            p->next = new Node(a);
        }
    }

    void display(){
        Node *p = head->next;
        while(p != nullptr){
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
};

int main() {
    LinkList<int> list;
    // 初始化一个链表：4 3 2 1
    list.insert(1, 0);
    list.insert(2, 1);
    list.insert(3, 2);
    list.insert(4, 3);

    cout << "初始链表: ";
    list.display();

    // 把10插在3前面
    list.insert(10, 3);
    cout << "把10插到3的前面后: ";
    list.display();

    // 把20插在5前面(5不存在)
    cout << "把20插到5的前面后(5不存在): ";
    list.insert(20, 5);
    list.display();

    return 0;
}