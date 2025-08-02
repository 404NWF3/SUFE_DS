#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    double sum = 0;
    for (int i = n; i <= m; i++) {
        sum += static_cast<double>(i - n + 1) / i / i;
    }
    printf("%.5lf\n", sum);
    return 0;
}
