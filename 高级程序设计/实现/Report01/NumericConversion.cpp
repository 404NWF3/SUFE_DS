/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: Ni Weifeng
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * Data Science and Big Data Technology Class 2
 * 2024110089
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */

int main() {

   cout << "Integer 123 ----> " << intToString(123) << endl;
   cout << "Integer -42 ----> " << intToString(-42) << endl;
   cout << "String 671 ----> " << stringToInt("671") << endl;
   cout << "String -99 ----> " << stringToInt("-99") << endl;
   return 0;
}

/*
 * A function that convert integral into string;
 * Considering that the input can only be an integral,
 * the base case is set when there is only one digit last
 */
string intToString(int n)
{
    // Whether the number is negative is important as the last one.
    if (n >= 0 && n <= 9)
        return string(1, n + '0');
    if (n >= -9 && n <= -1)
        return "-" + string(1, -n + '0');

    // Processing the specific digit
    int digit = n % 10;
    digit = digit > 0 ? digit : -digit;
    // Recurrence relation is set as Mr Zhang's instruction
    return intToString(n / 10) + string(1, digit + '0');
}

/*
 * A function that convert a string into integer;
 * Considering that the input can only be an empty string,
 * the base case is set when the string is empty.
 * When input string is empty, the function returns 0;
 */
int stringToInt(string str)
{
    int len = str.size();
    //
    if (str[0] == '-')
        return -stringToInt(str.substr(1));

    if (len == 0)
        return 0;

    // substr is the string going into the recursion chain!
    string substr = str.substr(0, len - 1);
    return stringToInt(substr) * 10 + (str[len-1]) - '0';
}
