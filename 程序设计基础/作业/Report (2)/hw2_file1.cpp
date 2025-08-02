#include <iostream>
using namespace std;

void printLine(int n);

int main() {
    int n;
    cout << "输入数字金字塔层数（< 10 ）：";

    cin >> n;
    if (n <= 0 || n >= 10) return -1;
    cout << "输出：" << endl;
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j < n - i; j++) cout << ' ';
        printLine(i);
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < n - i; j++) cout << ' ';
        printLine(i);
    }

    return 0;
}

void printLine(int n) {
    for (int i = 1; i <= n; i++) cout << i;
    for (int i = n - 1; i >= 1; i--) cout << i;
    cout << endl;
}
