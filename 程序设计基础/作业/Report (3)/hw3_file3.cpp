#include <iostream>
#include <cstring>
using namespace std;
char charwords[1001][21];
int i = 0;
char statwords[1000][1000];
int statcounts[1000];
int wordNum = 0;

bool isWord(char ch) {
    return isalpha(ch) || ch == 39;
}

bool equalStr(char ch1[], char ch2[]) {
    if (strlen(ch1) == strlen(ch2)) {
        for (int i = 0; i < strlen(ch1); i++) {
            if (ch1[i] != ch2[i]) return false;
        }
        return true;
    }
    return false;
}

void readWords();

void countAndPrintWords();

int main() {
    readWords();
    countAndPrintWords();

    return 0;
}

void readWords() {
    while (cin.getline(charwords[i++], 20, ' ')) {
    }
    for (int j = 0; j < i; j++) {
        // cout << j << "  " << charwords[j] << endl;
        for (int k = 0; charwords[j][k] != '\0'; k++) {
            // if (isWord(charwords[j][k])) tolower(charwords[j][k]);
            //濡傛灉杈撳叆鐨勪竴琛屼腑鏈夊涓崟璇嶏紝鍒欏垎寮€鎵€鏈夊崟璇�
            if (!isWord(charwords[j][k])) {
                //鍦╧澶勭粓姝�
                charwords[j][k] = '\0';
                //浠巏+1澶勬壘鍒扮涓€涓笉涓哄崟璇嶇殑鍦板潃
                for (int l = k + 1; charwords[j][l] != '\0'; l++) {
                    if (isWord(charwords[j][l])) {
                        // cout << "***" << endl;
                        strncpy(charwords[i++], charwords[j] + l, strlen(charwords[j])) - l;
                        break;
                    }
                }
                charwords[j][k + 1] = '\0';
            }
        }
    }
    for (int j = 0; j < i; j++) {
        for (int k = 0; charwords[j][k] != '\0'; k++) {
            charwords[j][k] = tolower(charwords[j][k]);
        }
    }
    // cout << "sorted words:" << endl;
    // for (int j = 0; j < i; j++) {
    //     cout << j << "  ";
    //     cout << charwords[j] << endl;
    // }
}

void countAndPrintWords() {
    for (int j = 0; j < i; j++) {
        //淇濊瘉绗琷涓笉涓虹┖瀛楃
        if (charwords[j][0] != '\0') {
            // cout << j << " " << charwords[j] << endl;
            //瀵绘壘鐩爣鍗曡瘝鏄惁宸茬粡鍦╯tatwords涓瓨鍦�(false)锛屼笉瀛樺湪涓�(true)
            bool flag = true;
            for (int k = 0; k < wordNum; k++) {
                if (equalStr(charwords[j], statwords[k])) {
                    // cout << "===" << endl;
                    // cout << statcounts[k] << endl;
                    statcounts[k]++;
                    // cout << statcounts[k] << endl;
                    flag = false;
                    break;
                }
            }
            if (flag) {
                strncpy(statwords[wordNum], charwords[j], strlen(charwords[j]));
                statcounts[wordNum] = 1;
                // cout << statcounts[wordNum] << endl;
                wordNum++;
            }
        }
    }
    for (int j = 0; j < wordNum; j++) {
        if (j % 5 == 0)cout << endl;
        cout << statwords[j] << "\t" << statcounts[j] << '\t';

    }
}
