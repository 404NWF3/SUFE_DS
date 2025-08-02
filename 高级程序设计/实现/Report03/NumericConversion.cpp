/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt from
 * Assignment #3
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <string>
#include <cctype>
using namespace std;

/* Function prototypes */
string integerToString(int n);
int stringToInteger(string str);
bool isNumeric(string &str);

/* Main program */
int main()
{
    int N = getInteger("Please input integer N: ");
    cout<<"Converted String is:"<<integerToString(N)<<endl<<endl;
    string str;
    do{
        str = getLine("Please input a digital string: ");
        if(isNumeric(str))
            break;
        else
            cout<<"Illeagal digital string format. Try again!"<<endl<<endl;
    } while(true);

    cout<<"Converted Integer is:"<<stringToInteger(str)<<endl;
    return 0;
}

/*
 * Function: integerToString
 * Usage: str = integerToString(n);
 * ------------------------
 * This function performs converting a integer to a string.
 */
string integerToString(int n)
{
    if (n < 0) return "-" + integerToString(-1 * n);
    if (n >= 0 && n <= 9)
        return string(1, n + '0');
    return integerToString(n / 10) + string(1, n % 10 + '0');
}

/*
 * Function: stringToInteger
 * Usage: n = stringToInteger(str);
 * ------------------------
 * This function performs converting a string to a integer.
 */
int stringToInteger(string str)
{
    int length = str.length();
    if (length == 0) return INT_MAX;
    if (length == 1){
        if (str[0] == '-') return INT_MIN;
        return str[0] - '0';
    }
    if (str[0] == '-')
        return -1 * stringToInteger(str.substr(1, length - 1));
    return str[length - 1] - '0' + 10 * stringToInteger(str.substr(0, length-1));
}

/*
 * Function: isNumeric
 * Usage: bool flag = isNumeric(str);
 * ------------------------
 * This function checks a legal digital string.
 */
bool isNumeric(string &str)
{
    if(!str.length())
        return false;
    unsigned int startPosition = 0;
    if(str[0] == '-'){
        if(str.length()==1){
            return false;
        }
        else{
            startPosition = 1;
        }
    }
    for(unsigned int i = startPosition; i<str.length();i++)
        if(isdigit(str[i]))
            ;
        else
            return false;
    return true;
}

