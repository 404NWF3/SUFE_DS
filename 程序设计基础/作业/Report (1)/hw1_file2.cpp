#include <iostream>
using namespace std;

int main() {
    int x1, y1, x2, y2, x3, y3;
    cout << "x1, y1: ";
    cin >> x1 >> y1;
    cout << "x2, y2: ";
    cin >> x2 >> y2;
    cout << "x3, y3: ";
    cin >> x3 >> y3;

    //不共线就能组成三角形
    double m_x1 = x1 - x2, m_y1 = y1 - y2, m_x2 = x2 - x3, m_y2 = y2 - y3;
    if (m_x1 * m_y2 - m_y1 * m_x2 !=0) cout << "Yes";
    else cout << "No";

    return 0;
}
