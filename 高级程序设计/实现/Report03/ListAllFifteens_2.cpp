/*
 * File: CountFifteens.cpp
 * -----------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the CountFifteens problem from
 * Assignment #3.
 * [TODO: extend the documentation]
 */

#include <exception>
#include <iostream>
#include <string>
#include "card.h"
#include "console.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "vector.h"
using namespace std;

/* Function prototypes */
const int TARGET = 15;
int listAllFifteens(Vector<Card> & cards);
// TODO: declare the recursive function listAllFifteensRec
int listAllFifteensRec(int target, int index, const Vector<Card>& cards);

/* Main program */

// AD 5C 10S 4H 9C
// 5C 5D 5H 5S 10S

int main() {
   while (true) {
      string line = getLine("Enter a hand of cards: ");
      if (line == "") break;
      TokenScanner scanner(line);
      scanner.ignoreWhitespace();
      Vector<Card> hand;
      while (scanner.hasMoreTokens()) {
         hand.add(Card(scanner.nextToken()));
      }
      int nWays = listAllFifteens(hand);
      string plural = (nWays == 1) ? "" : "s";
      cout << nWays << " way" << plural << endl;
   }
   return 0;
}

/*
 * Counts the number of ways of making a total of 15 from the vector of
 * cards.
 */

int listAllFifteens(Vector<Card> & cards) {
    return listAllFifteensRec(TARGET, 0, cards);
}

   // TODO: Implement the recursive function listAllFifteensRec.
int listAllFifteensRec(int target, int index, const Vector<Card> &cards){
    int res = 0, size = cards.size();
    if (index >= size) return 0;
    Card top = cards[index];
    int top_rank = top.getRank();
    res += listAllFifteensRec(target, index + 1, cards);
    if (top_rank == target) res++;
    if (top_rank < target)
        res += listAllFifteensRec(target - top_rank, index + 1, cards);
    return res;
}
