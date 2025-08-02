#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char words[30][41], n;

void swap(char a[], char b[]);
void printWords();

void bubbleSortStr();

int main() {
    printf("Please input the name of several cities, one city per line(@ --- end of input):\n");

    while (cin.getline(words[n], 41)) {
        if (words[n][0] == '@') break;
        n++;
    }
    bubbleSortStr();
    printWords();

    return 0;
}

void swap(char a[], char b[]) {
    char c[41];
    strcpy(c, a);
    strcpy(a, b);
    strcpy(b, c);
}

void printWords() {
    for (int i = 0; i < n; i++) {
        printf("%s\n", words[i]);
    }
}

void bubbleSortStr() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(words[j], words[j+1]) > 0) {
                swap(words[j], words[j+1]);
            }
        }
    }
}