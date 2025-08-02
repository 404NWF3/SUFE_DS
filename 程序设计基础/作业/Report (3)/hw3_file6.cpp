#include<iostream>
using namespace std;

int num_root(int n) {
    if (n > 0 && n < 9) return n;
    return num_root(num_root(n / 10) + n % 10);
}

int main() {
    int n;
    cin >> n;

    cout << num_root(n) << endl;
    return 0;
}
