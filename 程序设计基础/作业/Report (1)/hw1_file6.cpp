#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "请输入数字塔的高度(0-9)：";
    cin >> n;

    if (n < 0 || n > 9) return 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n - i; j++) cout << " ";
        for (int k = 1; k <= i; k++) cout << k;
        for (int k = i - 1; k > 0; k--) cout << k;
        cout << endl;
    }
    for (int i = 0; i < 2 * n + 1; i++) cout << "*";
    return 0;
}
