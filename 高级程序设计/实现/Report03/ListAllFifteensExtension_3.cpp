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
#include "map.h"
#include "set.h"
#include "cgraphics.h"

using namespace std;

/* Global variables */
const int SUM = 15;

/* Function prototypes */

Vector<Vector<Card>> listAllFifteens(const Vector<Card> & cards);
Vector<Vector<Card>> listAllFifteensRec(const Vector<Card> & remainingCards, \
                                     const Vector<Card> & usedCards, int sum);

bool cmp(Card& a, Card& b){
    int a_rank = a.getRank(), b_rank = b.getRank();
    Suit a_suit = a.getSuit(), b_suit = b.getSuit();
    if (a_rank != b_rank)
        return a_rank < b_rank;
    return a_suit < b_suit;
}

void display(const Vector<Card>& hand){
    Vector<Vector<Card>> ans = listAllFifteens(hand);
    for (const Vector<Card>& cards : ans){
        for (Card C: cards ){
            cout << C << " ";
        }
        cout << endl;
    }
}

/*
 * Main program
 * ------------------------------------------------------------------
 * This program does no error-checking on the input.  One of the
 * extensions you might consider is adding code to this program (and
 * possibly to the Card class) to allow the program to report errors.
 */

// AD 5C 10S 4H 9C
// 5C 5D 5H 5S 10S
// 5C 5C 5C 5C 10S

int main()
{
    while (true)
    {
        // string handCardsString = "AD 5S 6H 3C QD 2H";
        // Card Suit: D---Diamonds, S---Spade, C---Club, H---Heart
        string handCardsString = getLine("Please input a hand of Cards:");

        if (handCardsString == "") break;
        TokenScanner scanner(handCardsString);
        scanner.ignoreWhitespace();

        Vector<Card> hand;
        while (scanner.hasMoreTokens()) {
            hand.add(Card(scanner.nextToken()));
        }

        cout << hand << endl;
        sort(hand.begin(), hand.end(), cmp);
        cout << hand << endl;
        initGraphics();
        displayResult(hand, listAllFifteens(hand));
        closeGraphics();

    }

    cout << endl <<"Game Over and Welcome to play again!"<<endl;
    return 0;
}

/* Wrapper Function & Recursive Function
 * Get all combinations of making a total of 15 from the vector of
 * cards.
 */

Vector<Vector<Card>> listAllFifteens(const Vector<Card> & cards)
{
    Vector<Vector<Card>> Fifteens = listAllFifteensRec(cards, {}, SUM);
    Set<Vector<Card>> assist;
    for (Vector<Card> c : Fifteens){
        sort(c.begin(), c.end(), cmp);
        assist.add(c);
    }

    Vector<Vector<Card>> res;
    for (const Vector<Card>& c : assist)
        res += c;

    return res;
}

Vector<Vector<Card>> listAllFifteensRec(const Vector<Card> & remainingCards,
                                        const Vector<Card> & usedCards, int sum)
{
    Vector<Vector<Card>> res = {};
    int size = remainingCards.size();
    if (size == 0) return {};
    Card top = remainingCards[0];
    int top_rank = top.getRank();

    Vector<Card> new_remaining = remainingCards.subList(1);
    Vector<Card> new_used = usedCards;
    new_used.add(top);
    res += listAllFifteensRec(new_remaining, usedCards, sum);

    if (top_rank == sum)
        res.add(new_used);

    if (top_rank < sum){
        res += listAllFifteensRec(new_remaining, new_used, sum - top_rank);
    }

    return res;
}



