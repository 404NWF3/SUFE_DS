#include <iostream>
#include <string>
using namespace std;

void bubble_sort(string* arr, int n);

int main() {
    string s_arr[5];
    for (auto & i : s_arr) {
        cin >> i;
    }

    bubble_sort(s_arr, 5);
    for (string s : s_arr) {
        cout << s << endl;
    }
    return 0;
}

void bubble_sort(string* arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                string temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}