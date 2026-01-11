/*
写一个倒置顺序存储的线性表的函数，要求使用最少的附加存储空间来完成。
*/

#include <iostream>
using namespace std;

const int defaultSize = 100;

// 直接使用ppt中线性表的定义，增加reversed函数，返回一个SeqList对象，reverse函数，返回void
template <class Type>
class SeqList
{
public:
    SeqList(int MaxSize = defaultSize);             // 构造函数
    SeqList(const SeqList &L);                      // 复制构造函数
    ~SeqList() { delete[] list; }                   // 析构函数
    int length() const { return last + 1; }         // 计算表长度
    int Find(Type &x) const;                        // 查找
    int IsIn(Type &x);                              // 判断x是否在表中
    int Insert(Type &x, int i);                     // 插入x在表中第i个位置处
    int Remove(int i);                              // 删除第i个位置处的表项
    int Next(Type &x);                              // 寻找x的后继
    int Prior(Type &x);                             // 寻找x的前驱
    int IsEmpty() { return last == -1; }            // 判断表空否
    int IsFull() { return last == MaxSize - 1; }    // 判断表满否
    void pushback(Type &x) { Insert(x, last + 1); } // 尾插法
    Type Get(int i) { return i < 0 || i > last ? NULL : list[i]; }
    // 取第i个元素的值
    void reverse();                             // 倒置函数
    SeqList<Type> reversed();                   // 倒置函数，返回一个新的顺序表
    Type &operator[](int i) { return list[i];} // 重载[]运算符
private:
    Type *list;  // 表的存放数组
    int MaxSize; // 表的最大可容纳项数
    int last;    // 当前已存表项的最后位置
};

template <class Type>
SeqList<Type>::SeqList(int MaxSize)
{
    this->MaxSize = MaxSize;
    last = -1;
    list = new Type[MaxSize];
    if (list == NULL)
    {
        cerr << "存储分配错误" << endl;
        exit(1);
    }
}

template <class Type>
SeqList<Type>::SeqList(const SeqList &L)
{
    MaxSize = L.MaxSize;
    last = L.last;
    list = new Type[MaxSize];
    if (list == NULL)
    {
        cerr << "存储分配错误" << endl;
        exit(1);
    }
    for (int i = 0; i <= last; i++)
        list[i] = L.Get(i);
}

template <class Type>
int SeqList<Type>::Insert(Type &x, int i) // 插入x在表中第i个位置处
{
    if (IsFull())
    {
        cerr << "表满" << endl;
        return 0;
    }
    if (i < 0 || i > last + 1)
    {
        cerr << "插入位置不合法" << endl;
        return 0;
    }
    for (int j = last; j >= i; j--)
        list[j + 1] = list[j]; // 插入位置及之后的元素后移
    list[i] = x;               // 插入x
    last++;
    return 1;
}

// 实现reverse和reversed函数
template <class Type>
void SeqList<Type>::reverse()
{
    int i = 0, j = last;
    while (i < j)
    {
        int temp = list[i];
        list[i] = list[j];
        list[j] = temp;
        i++;
        j--;
    }
}

template <class Type>
SeqList<Type> SeqList<Type>::reversed()
{
    SeqList<Type> newList(MaxSize);
    for (int i = last; i >= 0; i--)
    {
        newList.Insert(list[i], newList.length());
    }
    return newList;
}

// 定义一个全局的倒置函数
template <class Type>
void reverse(SeqList<Type> &L)
{
    int i = 0, j = L.length() - 1;
    while (i < j)
    {
        // int temp_i = L.Get(i), temp_j = L.Get(j);
        // L.Insert(temp_j, i);
        // L.Insert(temp_i, j);
        Type temp = L.Get(i);
        L[i] = L[j];
        L[j] = temp;
        i++;
        j--;
    }
}

int main()
{
    SeqList<int> test;
    for (int i = 1; i <= 10; i++)
    {
        test.pushback(i);
    }
    cout << "原顺序表为：";
    for (int i = 0; i < test.length(); i++)
    {
        cout << test.Get(i) << " ";
    }
    // test.reverse();
    reverse(test);
    cout << "\n逆置后顺序表为：";
    for (int i = 0; i < test.length(); i++)
    {
        cout << test.Get(i) << " ";
    }
    return 0;
}