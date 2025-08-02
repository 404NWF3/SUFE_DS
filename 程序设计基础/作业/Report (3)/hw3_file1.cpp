#include <iostream>
using namespace std;

string decToBase(int n, int base) {
    string ret;
    while (n) {
        int temp;
        temp = n % base;
        n /= base;
        if (temp >= 0 && temp <= 9) {
            ret.insert(ret.begin(), temp + '0');
        }
        else {
            ret.insert(ret.begin(),static_cast<char>(temp-10+'A'));
        }
    }
    return ret;
}

int main() {
    int n;
    cout << "请输入转换的整数：";
    cin >> n;

    cout << decToBase(n, 2) << endl;
    cout << decToBase(n, 8) << endl;
    cout << decToBase(n, 16) << endl;

    return 0;
}
