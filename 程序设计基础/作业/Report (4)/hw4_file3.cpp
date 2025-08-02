#include <bits/stdc++.h>
using namespace std;

char *mysubstr(char *srcstr, int offset, int length);

int main() {
    char srcstr[] = "this is a test string!";
    char *tmp = mysubstr(srcstr, 8, 8);
    cout << "the substring is: " << tmp << endl;
    delete tmp;
    return 0;
}

char *mysubstr(char *srcstr, int offset, int length) {
    char *result = new char[length+1];
    for (int i = 0; i < length; i++) {
        result[i] = srcstr[offset + i];
    }
    result[length] = '\0';
    return result;
}
