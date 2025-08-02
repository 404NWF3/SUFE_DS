// 驱动 程序 文件
#include <iostream>
#include "uset.h"
using namespace std;
int main()
{
    uset* myset;
    newSet(&myset);
    displaySet(myset);
    int i;
    for (i = 1; i < 80; i++)
        addElem(&i, myset);
    displaySet(myset);
    for (i = 50; i < 100; i++)
        addElem(&i, myset);
    displaySet(myset);
    for (i = 30; i < 100; i++)
        remElem(&i, myset);
    displaySet(myset);
    deleteSet(&myset);
    return 0;
}
