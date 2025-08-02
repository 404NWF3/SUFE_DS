/*
 * File: Game 24.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the Game 24 problem
 * from Assignment #4.
 * [TODO: extend the documentation]
 */

#include <string>
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "vector.h"
#include "set.h"
#include "strlib.h"
#include "card.h"
#include "display.h"

using namespace std;

/* Constants */
const int BIGNUM = 24;
static bool isZero(double x){ return fabs(x) < 1e-6; }

Vector<int> getSubs(int mask);
Set<string> countTwentyFours(Vector<Card> & cards);
Set<string> countTwentyFoursRec(const Vector<Card> & cards, int mask, Vector<Set<Card>>& memo);
Set<string> mergeCards(Vector<Card> & cards, Vector<Set<Card>>& memo);
Set<Card> dp(int mask, Vector<Set<Card>>& memo);
Set<Card> mergeSub(Set<Card> a, Set<Card> b);

int main(){
    initGraphics("GAME 24");
    while (true){
        // string handCardsString = "5C 10S 4H 9C";
        string handCardsString = getLine("Please input a hand of Cards:");
        if (handCardsString == "") break;
        TokenScanner scanner(handCardsString);
        scanner.ignoreWhitespace();
        Vector<Card> cards;
        bool isLegalCard = true;
        while (scanner.hasMoreTokens()) {
            string tokenString = scanner.nextToken();
            Card handCard = Card(tokenString);
            if(!handCard.fail())
               cards.add(handCard);
            else
               isLegalCard = false;
        }
        int cardsNum = cards.size();
        if (isLegalCard && cardsNum > 1 && cardsNum < 7){
            Set<string> solutionsStrings = countTwentyFours(cards);
            displayHandCards(handCardsString, cardsNum);
            displaySolutions(solutionsStrings, cardsNum);
        }
        else
            cout << "Please give at least 2 cards, up to 6 cards!" << endl << endl;
    }
    cout<<endl<<"Game Over and the windows will be closed in a few seconds..."<<endl;
    pause(3000);
    closeGraphics();
    return 0;
}

Set<string> countTwentyFours(Vector<Card> & cards){
    // 生成memo bitmask数组
    int size = cards.size();
    Vector<Set<Card>> memo(1 << size);
    for (int i = 0; i < size; i++)
        memo[1 << i] = {cards[i]};


    // 2C 2C 2C 3C
    // 5S 10S 4S 9S

    dp(memo.size() - 1, memo);
    Set<string> res;
    for (const Card& c : memo[memo.size() - 1]){
        if (c.getRank() == 24)
            res += c.toExpressionString();
    }

    return res;
}

Vector<int> getSubs(int mask){
    // 输入一个bitmask，输出它的所有子集
    Vector<int> res;

    for (int sub = mask - 1; sub; sub = (sub - 1) & mask)
        res += sub;

    return res;
}


Set<Card> dp(int mask, Vector<Set<Card>>& memo){
    if (!memo[mask].isEmpty())
        return memo[mask];
    Vector<int> subs = getSubs(mask);
    // 求所有划分
    for (int sub : subs){
        int other = mask ^ sub;
        if (sub < other)
            memo[mask] += mergeSub(dp(sub, memo), dp(other, memo));
    }

    return memo[mask];
}

Set<Card> mergeSub(Set<Card> a, Set<Card> b){
    Set<Card> res;
    for (const Card &l : a){
        for (const Card &r : b){
            const string& sL = l.toExpressionString();
            const string& sR = r.toExpressionString();

            // + *
            if (sL < sR){
                res += l + r;
                res += l * r;
            }
            else{
                res += r + l;
                res += r * l;
            }

            // -
            if (l.getRank() > r.getRank())
                res += l - r;
            else
                res += r - l;

            // /
            if (!isZero(r.getRank())) res += l / r;
            if (!isZero(l.getRank())) res += r / l;
        }
    }
    return res;
}
