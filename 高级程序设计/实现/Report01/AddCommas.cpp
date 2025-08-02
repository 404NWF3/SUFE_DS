/*
 * File: AddCommas.cpp
 * -------------------
 * Name: Ni Weifeng
 * This program adds commas to numeric strings.
 * Data science and Big Data Technology Class 2
 * 2024110089
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Function prototypes */

string addCommas(string digits);

/* Main program */

int main() {
   while (true) {
      string digits = getLine("Enter a number: ");
      if (digits == "") break;
      cout << addCommas(digits) << endl;
   }
   return 0;

}

/*
 * Function: addCommas
 * Usage: string str = addCommas(digits);
 * --------------------------------------
 * Adds commas at every third position of the string digits
 * starting on the right.
 */

string addCommas(string digits) {
    if (digits[0] == '-')
        return "-" + addCommas(digits.substr(1));
    if ((digits[0] >= 'a' && digits[0] <= 'z') ||
        (digits[0] >= 'A' && digits[0] <= 'Z'))
        throw "Please input a integer!";

    int len = digits.size();

    // if length is shorter than 3, returns itself. This is completely included the empty case.
    if (len <= 3)
        return digits;

    // Before the "," go into the recursion and after remains.
    else
        return addCommas(digits.substr(0, len - 3)) + "," + digits.substr(len - 3, 3);
}
