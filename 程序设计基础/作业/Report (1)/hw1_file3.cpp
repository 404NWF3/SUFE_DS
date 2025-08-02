#include <iostream>
using namespace std;

int main() {
    int sum = 0;
    int flag = 1;
    for (int i = 1; i <= 101; i+=2) {
        // cout << i * flag << endl;
        sum += i * flag;
        // cout << "sum=" << sum << endl;
        flag *= -1;
    }
    cout << "1-3+5-7...+101=" << sum << endl;

    return 0;
}
