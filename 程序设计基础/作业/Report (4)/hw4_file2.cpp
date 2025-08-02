#include <bits/stdc++.h>
using namespace std;

char *myStrstr(char *str1, char *str2);

int main() {
    char dest[10] = "abcdabc";
    char *rp;
    char ch1[] = "c";
    char str2[] = "abcde";
    rp = myStrstr(dest, ch1);
    if (rp == nullptr)
        cout << "no " << ch1 << " exist" << endl;
    else
        cout << "substring is " << rp << endl;
    rp = myStrstr(dest, str2);
    if (rp == nullptr)
        cout << "no " << str2 << " exist" << endl;
    else
        cout << "substring is " << rp << endl;
    return 0;
}

char *myStrstr(char *str1, char *str2) {
    // char *ret = nullptr;

    for (int i = 0; str1[i] != '\0'; i++) {
        for (int j = 0; str2[j] != '\0'; j++) {
            if (str1[i + j] != str2[j]) {
                break;
            }
            if (j == strlen(str2) - 1 && str1[i + j] == str2[j]) {
                return str1 + i;
            }
        }
    }
    return nullptr;
}
