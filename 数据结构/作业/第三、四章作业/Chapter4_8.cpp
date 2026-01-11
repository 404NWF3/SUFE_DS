#include <iostream>
using namespace std;

template <class Type>
class MyStack
{
private:
    struct Node
    {
        Type data;
        Node *next = nullptr;
    };
    Node *top;
    int length;

public:
    MyStack() : top(nullptr), length(0) {}
    ~MyStack()
    {
        while (top != nullptr)
        {
            Node *temp = top;
            top = top->next;
            delete temp;
        }
    }
    
    void push(const Type &t);
    Type pop();
    bool isEmpty() const { return top == nullptr; }
    int size() const { return length; }
};

template <class Type>
void MyStack<Type>::push(const Type &t)
{
    Node *newNode = new Node();
    newNode->data = t;
    newNode->next = top;
    top = newNode;
    length++;
}

template <class Type>
Type MyStack<Type>::pop()
{
    if (isEmpty())
    {
        throw runtime_error("栈空。");
    }
    Node *temp = top;
    Type data = top->data;
    top = top->next;
    delete temp;
    length--;
    return data;
}

int main()
{
    MyStack<int> stack;
    stack.push(10);
    stack.push(20);
    cout << "弹出: " << stack.pop() << endl;
    cout << "弹出: " << stack.pop() << endl;
    return 0;
}