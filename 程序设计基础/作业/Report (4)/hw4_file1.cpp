#include <iostream>
#include <cstring> // 使用标准库字符串操作函数
using namespace std;

int main() {
    char *str1, *str2, *mergStr;
    int len1, len2; // 表示字符串 str1、str2 的长度
    int mergStrlen; // 表示合并后字符串的长度

    // 分配内存给 str1 和 str2
    str1 = new char[100];
    str2 = new char[100];

    // 输入两个字符串
    cin.getline(str1, 100);
    cin.getline(str2, 100);

    // 计算字符串长度
    len1 = strlen(str1);
    len2 = strlen(str2);
    mergStrlen = len1 + len2 + 1;

    // 分配合并后字符串的内存
    mergStr = new char[mergStrlen]; // +1 用于存储 '\0'
    // mergStr[0] = '\0'; // 初始化为空字符串

    // 将 str1 和 str2 合并到 mergStr
    strcpy(mergStr, str1);
    strcat(mergStr, str2);

    // 输出合并后的字符串
    cout << "合并字符串为：" << mergStr << endl;

    // 释放内存
    delete[] str1;
    delete[] str2;
    delete[] mergStr;

    return 0;
}
