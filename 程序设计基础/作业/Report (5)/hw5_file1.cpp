#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

void RegularPluralForm(char word[]);
bool isVowel(char ch);
void MultiplePluralForm(char target[], const char source[]);

int main()
{
    char word1[81]="bus";
    RegularPluralForm(word1);
    cout << word1 << endl; strcpy(word1, "box");
    RegularPluralForm(word1);
    cout << word1 << endl; strcpy(word1, "peach");
    RegularPluralForm(word1);
    cout << word1 << endl; strcpy(word1, "dish");
    RegularPluralForm(word1);
    cout << word1 << endl; strcpy(word1, "class");
    RegularPluralForm(word1);
    cout << word1 << endl; strcpy(word1, "quiz");
    RegularPluralForm(word1);
    cout << word1 << endl;
    strcpy(word1, "dictionary");
    RegularPluralForm(word1);
    cout << word1 << endl;
    strcpy(word1, "family");
    RegularPluralForm(word1);
    cout << word1 << endl; strcpy(word1, "monkey");
    RegularPluralForm(word1);
    cout << word1 << endl; strcpy(word1, "boy");
    RegularPluralForm(word1);
    cout << word1 << endl;
    strcpy(word1, "knife");
    RegularPluralForm(word1);
    cout << word1 << endl;
    strcpy(word1, "leaf");
    RegularPluralForm(word1);
    cout << word1 << endl;
    strcpy(word1, "apple");
    RegularPluralForm(word1);
    cout << word1 << endl;
    strcpy(word1, "tool");
    RegularPluralForm(word1);
    cout << word1 << endl;
    return 0;
}

bool isVowel(char ch)
{
    ch = tolower(ch);
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

void RegularPluralForm(char word[])
{
    int len = strlen(word);
    if (word[len - 1] == 's' || word[len - 1] == 'x' || word[len - 1] == 'z')
    {
        strcat(word, "es");
    }
    else if (word[len - 1] == 'h' && (word[len - 2] == 'c' || word[len - 2] == 's'))
    {
        strcat(word, "es");
    }
    else if (word[len - 1] == 'y' && !isVowel(word[len - 2]))
    {
        word[len - 1] = '\0';
        strcat(word, "ies");
    }
    else if (word[len - 1] == 'f')
    {
        word[len - 1] = '\0';
        strcat(word, "ves");
    }
    else if (word[len - 2] == 'f' && word[len - 1] == 'e')
    {
        word[len - 2] = '\0';
        strcat(word, "ves");
    }
    else if (word[len - 1] == 'o')
    {
        strcat(word, "es");
    }
    else
    {
        strcat(word, "s");
    }
}