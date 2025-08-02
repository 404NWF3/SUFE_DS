/*
 * File: DominoChainExtension.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for Domino Chain Extension problem
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

void testFormsALLDominoChains(string str);
Set<Vector<Domino>> formsALLDominoChains(Vector<Domino>& dominos);
Set<Vector<Domino>> formsALLDominoChainsRec(Vector<Domino>& remaining, Vector<Domino>& used, int designated);
Vector<Domino> createDominoVector(string str);

/* Main program */

int main() {
   testFormsALLDominoChains("1-4, 1-6, 2-6, 3-4, 4-4");
   testFormsALLDominoChains("1-6, 2-6, 3-4, 4-4");
   testFormsALLDominoChains("2-5, 3-6, 5-1, 3-5, 1-6");
   return 0;
}

void testFormsALLDominoChains(string str) {
   Vector<Domino> dominos = createDominoVector(str);
   Set<Vector<Domino>> dominoChainsSet = formsALLDominoChains(dominos);
   cout << boolalpha << endl << "Forms Domino Chain (" << str << ") -> "
        << (!dominoChainsSet.isEmpty() ? "Success!" : "Failure!") << endl;
   for(const Vector<Domino>& dominoChain : dominoChainsSet){
       cout<< " Begin -> ";
       for(Domino domino : dominoChain)
           cout << domino << "->";
       cout << " End" << endl;
   }
}

/*
 * Wrapper Function: formsALLDominoChains
 * Usage:  dominoChainsSet = formsALLDominoChains(dominos)
 */

Set<Vector<Domino>> formsALLDominoChains(Vector<Domino> & dominos){
    Set<Vector<Domino>> res;
    if (dominos.isEmpty())
        return res;
    Set<int> dots;
    for (const Domino &d : dominos){
        dots.add(d.getLeftDots());
        dots.add(d.getRightDots());
    }
    for (int i : dots){
        Vector<Domino> used = {};
        res += formsALLDominoChainsRec(dominos, used, i);
    }
    return res;
}
/*
 * TODO: designs and implements the recursive function that
 * forms all domino chains
 * ------------------------------------------------------------------------
 */
Set<Vector<Domino>> formsALLDominoChainsRec(Vector<Domino>& remaining, Vector<Domino>& used, int designated){
    Set<Vector<Domino>> res;
    int size = remaining.size();
    if (remaining.isEmpty()){
        res.add(used);
        return res;
    }
    for (int i = 0; i < size; i++){
        Domino d = remaining[i];
        int left = d.getLeftDots(), right = d.getRightDots();
        remaining.remove(i);
        if (left == right){
            if (left == designated){
                used.add(d);
                res += formsALLDominoChainsRec(remaining, used, right);
                used.remove(used.size() - 1);
            }
        }
        else{
            if (left == designated){
                used.add(d);
                res += formsALLDominoChainsRec(remaining, used, right);
                used.remove(used.size() - 1);
            }
            if (right == designated){
                used.add(d.turnOver());
                res += formsALLDominoChainsRec(remaining, used, left);
                used.remove(used.size() - 1);
            }
        }
        remaining.insert(i, d);
    }
    return res;
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
