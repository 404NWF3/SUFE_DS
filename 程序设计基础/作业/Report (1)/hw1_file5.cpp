#include <iostream>
using namespace std;

int main(void) {
    while (true) {
        int rowsNumber;
        cout << "Please Enter the Number of Rows:";
        cin >> rowsNumber;
        if (rowsNumber > 0) {
            for (int i = 1; i <= rowsNumber; i++) {
                for (int j = 0; j < rowsNumber - i; j++) {
                    cout << " ";
                }
                for (int j = 0; j < 2 * i - 1; j++) {
                    cout << "*";
                }
                cout << endl;
            }
        } else return 0;
    }
    return 1;
}
