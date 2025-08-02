#include <iostream>
using namespace std;

int displace_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int displace_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

string print_point(int x, int y) {
    return "[" + to_string(x) + "," + to_string(y) + "]";
}

int main() {
    //n*m阶矩阵
    //n行m列
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x = i, y = j;
            cout << "当前坐标方格是" << print_point(x, y) << "相邻方格坐标：" << endl;
            cout << "\t";
            for (int k = 0; k < 8; k++) {
                bool flag = x + displace_x[k] >= 0 && x + displace_x[k] <= n - 1 && y + displace_y[k] >= 0 && y + displace_y[k]
                    <= m - 1;
                if (flag) cout << print_point(x + displace_x[k], y + displace_y[k]) << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
