#include <iostream>

using namespace std;

//long long factorial(int n);
// long long combination(int m, int n);

void printLine(int n);


int main() {
    int n;
    cin >> n;

    for (int i = 0; i <= n; i++) {
        for (int j = 1; j < n - i + 1; j++) cout << "\t";
        printLine(i);
    }

    return 0;
}

//long long factorial(int n) {
//	if (n == 0) return 1;
//	return n * factorial(n - 1);
//}

//long double combination(int m, int n) {
//	return static_cast<double>(factorial(m)) / factorial(n) / factorial(m - n);
//}
// long long combination(int m, int n) {
//     long long ret = 1;
//     for (int i = 1; i <= n; i++) {
//         ret *= (m - i + 1);
//         ret /= i;
//     }
//     return ret;
// }

void printLine(int n) {
    int comb = 1;
    cout << comb << "\t\t";
    for (int j = 1; j <= n; j++) {
        comb *= n - j + 1;
        comb /= j;
        cout << comb << "\t\t";
    }
    // for (int i = 0; i <= n; i++) {
    // 	cout << combination(n, i) << "\t\t";
    // }
    cout << endl;
}
