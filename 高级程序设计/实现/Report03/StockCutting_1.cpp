/*
 * File: StockCutting.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the stock-cutting problem
 * fron Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

/* Function prototypes */
void testCutStock(Vector<int> & requests, int stockLength);
int cutStock(Vector<int> & requests, int stockLength);
void cutStockRec(const Vector<int> & requests, Vector<int> &stocksLeft, int index, int stockLength, int &best);
/* Main program */

int main() {
    Vector<int> test1;
    test1 += 4, 3, 4, 1, 7, 8;
    testCutStock(test1, 10);
    Vector<int> test2;
    test2 += 6, 6, 3, 3, 2, 2, 2, 2, 2;
    testCutStock(test2, 10);
    return 0;
}

/*
 * Function: cutStock
 * Usage: int units = cutStock(requests, stockLength);
 * ---------------------------------------------------
 * Computes the minimum number of stock pipes required to satisfy
 * the vector of requests of individual pieces.
 */

int cutStock(Vector<int> & requests, int stockLength) {
    int best = requests.size();
    Vector<int> stocksLeft = {};
    cutStockRec(requests, stocksLeft, 0, stockLength, best);
    return best;
}

/*
 * TODO: Designs and implements the recursive function that
 * computes the minimum number of stock pipes required to satisfy
 * the vector of requests of individual pieces
 * ------------------------------------------------------------------------
 */

void cutStockRec(const Vector<int> & requests, Vector<int> &stocksLeft, int index, int stockLength, int &best){
    int size = stocksLeft.size();

    if (index >= requests.size())
        best = min(best, size);

    if (size >= best)
        return;

    int cur = requests[index];

    for (int i = 0; i < size; i++){
        if (cur <= stocksLeft[i]){
            stocksLeft[i] -= cur;
            cutStockRec(requests, stocksLeft, index + 1, stockLength, best);
            stocksLeft[i] += cur;
        }
    }

    stocksLeft.add(stockLength - cur);
    cutStockRec(requests, stocksLeft, index + 1, stockLength, best);
    stocksLeft.remove(stocksLeft.size() - 1);
}

/*
 * Function: testCutStock
 * Usage: testCutStock(requests, stockLength);
 * -------------------------------------------
 * Conducts a test of the cutStock implementation by reporting how many
 * units are required to satisfy the requests.
 */

void testCutStock(Vector<int> & requests, int stockLength) {
    cout << "cutStock([";
    for (int i = 0; i < requests.size(); i++) {
        if (i > 0) cout << ", ";
        cout << requests[i];
    }
    cout << "]) -> " << cutStock(requests, stockLength) << endl;
}
