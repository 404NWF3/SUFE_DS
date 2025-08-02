/*
 * File: KarelGoesHome.cpp
 * -----------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the KarelGoesHome problem  
 * from Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <iomanip>
#include "console.h"
#include "grid.h"
using namespace std;

/* Constants */
const int GRID_SIZE = 10;
const int FIELD_WIDTH = 6;

/* Function prototypes */
int countPaths(int street, int avenue);
Grid<int> memo(GRID_SIZE + 1, GRID_SIZE + 1, -1);

/* Main program */
int main() {
    memo[1][1] = 0;

    for (int street = GRID_SIZE; street > 0; street--) {
        for (int avenue = 1; avenue <= GRID_SIZE; avenue++) {
            int nPaths = countPaths(street, avenue);
            cout << right << setw(FIELD_WIDTH) << nPaths;
        }
        cout << endl;
    }
    return 0;
}

/*
 * Function: countPaths
 * Usage: int nPaths = countPaths(street, avenue);
 * -----------------------------------------------
 * Counts the paths from a particular street/avenue position in
 * Karel's world to the origin, subject to the restriction that
 * Karel can move only west and south.
 */

int countPaths(int street, int avenue) {
    if (memo[street][avenue] != -1)
        return memo[street][avenue];
    if (street == 1 || avenue == 1){
        return memo[street][avenue] = 1;
    }
    return memo[street][avenue] = countPaths(street - 1, avenue) +
                                  countPaths(street, avenue - 1);
}
