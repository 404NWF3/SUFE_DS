#include <iostream>
using namespace std;

int main() {
    //y为兔子的数量，m为头的数量，n为脚的数量
    int m, n;
    cout << "请依次输入鸡和兔的总数量，腿的总数量：";
    cin >> m >> n;

    if (n < 2 * m || n > 4 * m || n % 2 == 1) {
        cout << "无解";
    } else {
        //n-2m一定为偶数
        int y = (n - 2 * m) / 2;
        int x = m - y;
        cout << "鸡：" << x << " 兔：" << y << endl;
    }

    return 0;
}
