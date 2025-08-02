/*
 * File: PerfectNumbers.cpp
 * ------------------------
 * Name: Ni Weifeng
 * This program tests the isPerfect function by generating all the
 * perfect numbers up to some user-specified upper bound.
 * Data Science and Big Data Technology Class 2
 * 2024110089
 */

#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Function prototypes */

bool isPerfect(int n);

/* Main program */

int main() {
   int bound;
   cout << "Enter upper bound: ";
   cin >> bound;
   cout << "The perfect numbers between 1 and " << bound;
   cout << " are:" << endl;
   for (int i = 1; i <= bound; i++) {
      if (isPerfect(i)) {
         cout << i << endl;
      }
   }
   return 0;
}

/*
 * Function: isPerfect
 * Usage: if (isPerfect(n)) . . .
 * ------------------------------
 * This function returns true if n is a perfect number.
 */

bool isPerfect(int n) {
    if (n <= 1)
        return false;

    int sum_factors = 0;

    for (int i = 1; i < n; i++){
        if (n % i == 0)
            sum_factors += i;
    }

    return sum_factors == n;
}

