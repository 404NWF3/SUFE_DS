#include <iostream>
#include <cstring>
using namespace std;

bool isPalindrome(char str[]) {
    int len = strlen(str);
    if (len <= 1) return true;
    if (str[0] != str[len - 1]) return false;
    char temp[len - 1];
    strncpy(temp, str + 1, len - 2);
    temp[len - 2] = '\0';
    return isPalindrome(temp);
}

int main() {
    char str[81];
    cout << "Please input a string: ";
    cin.getline(str, 80);
    char ret[81];
    strcpy(ret, str);
    for (char &ch : str) {
        ch = tolower(ch);
    }

    if (isPalindrome(str))
        cout << ret << " is a palindrome." << endl;
    else
        cout << ret << " is not a palindrome." << endl;

    return 0;
}
