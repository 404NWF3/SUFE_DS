/*
 * File: DominoChain.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the Domino Chain problem
 * from Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cctype>
#include <string>
#include "domino.h"
#include "strlib.h"
#include "tokenscanner.h"
#include "vector.h"
#include "set.h"
#include "console.h"
using namespace std;

/* Function prototypes */

void testDominos(string str);
bool canFormDominoChain(Vector<Domino> & dominos);
bool canFormDominoChainRec(Vector<Domino> & remaining, int designated);
Vector<Domino> createDominoVector(string str);

/* Main program */

int main() {
   testDominos("1-4, 1-6, 2-6, 3-4, 4-4");
   testDominos("1-6, 2-6, 3-4, 4-4");
   testDominos("2-5, 3-6, 5-1, 3-5, 1-6");
   return 0;
}

void testDominos(string str) {
   Vector<Domino> dominos = createDominoVector(str);
   bool ok = canFormDominoChain(dominos);
   cout << boolalpha << endl << "Forms Domino Chain (" << str << ") -> " << ok << endl;
}

/*
 * Wrapper Function: canFormDominoChain
 * Usage: if (canFormDominoChain(dominos)) . . .
 * --------------------------------------------------
 * Checks to see if the domino vector can form a chain which
 * begins with any dominos in the vector. The recursive insight
 * is that the entire set forms a chain if and only if there is
 * some domino whose left side matches the designated starting
 * number and the remaining dominos form a chain starting with
 * the count from that domino's right side or, conversely, there
 * is a domino that fits if you reverse its left and right sides.
 */
bool canFormDominoChain(Vector<Domino> & dominos){
    if (dominos.isEmpty())
        return false;
    Set<int> dots;
    for (const Domino &d : dominos){
        dots.add(d.getLeftDots());
        dots.add(d.getRightDots());
    }
    for (int i : dots)
        if (canFormDominoChainRec(dominos, i))
            return true;
    return false;
}
/*
 * TODO: designs and implements the recursive function that
 * checks whether a domino chain is formed
 * ------------------------------------------------------------------------
 */

bool canFormDominoChainRec(Vector<Domino> & remaining, int designated){
    int size = remaining.size();
    if (size == 1){
        int left = remaining[0].getLeftDots(), right = remaining[0].getRightDots();
        if (left == designated || right == designated)
            return true;
    }
    for (int i = 0; i < size; i++){
        Domino d = remaining[i];
        int left = d.getLeftDots(), right = d.getRightDots();
        remaining.remove(i);
        if (left == designated)
            if (canFormDominoChainRec(remaining, right))
                return true;
        if (right == designated)
            if (canFormDominoChainRec(remaining, left))
                return true;
        remaining.insert(i, d);
    }
    return false;
}

/*
 * Function: createDominoVector
 * Usage: Vector<Domino> vec = createDominoVector(str);
 * ----------------------------------------------------
 * Parses a string composed of comma-separated left-right pairs into a
 * chain of Domino objects.
 */

Vector<Domino> createDominoVector(string str) {
   Vector<Domino> vec;
   TokenScanner scanner(str);
   scanner.ignoreWhitespace();
   while (true) {
      int left = stringToInteger(scanner.nextToken());
      scanner.verifyToken("-");
      int right = stringToInteger(scanner.nextToken());
      vec += Domino(left, right);
      if (!scanner.hasMoreTokens()) break;
      scanner.verifyToken(",");
   }
   return vec;
}
