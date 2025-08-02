#include <iostream>

using namespace std;

int main() {
    bool isInGroup[20];
    for (bool &i: isInGroup) {
        i = true;
    }

    int personNumberInGroup = 20;
    int times = 0;
    int i = 0;
    while (personNumberInGroup > 1) {
        if (isInGroup[i]) times++;
        if (times == 3) {
            cout << i << endl;
            isInGroup[i] = false;
            times = 0;
            personNumberInGroup--;
        }
        i++;
        if (i == 20) i = 0;
    }
    return 0;
}
