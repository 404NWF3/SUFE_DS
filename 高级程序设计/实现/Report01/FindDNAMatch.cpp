/*
 * File: FindDNAMatch.cpp
 * ----------------------
 * Name: Ni Weifeng
 * This file solves the DNA matching exercise from the text.
 * Data Science and Big Data Technology Class 2
 * 2024110089
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Prototypes */

int findDNAMatch(string s1, string s2, int start = 0);
string matchingStrand(string strand);
void findAllMatches(string s1, string s2);

/* Main program */

int main() {
   findAllMatches("TTGCC", "TAACGGTACGTC");
   findAllMatches("TGC", "TAACGGTACGTC");
   findAllMatches("CCC", "TAACGGTACGTC");
   return 0;
}

/*
 * Function: findAllMatches
 * Usage: findAllMatches(s1, s2);
 * ------------------------------
 * Finds all positions at which s1 can bind to s2.
 */

void findAllMatches(string s1, string s2) {
   int start = 0;
   while (true) {
      int index = findDNAMatch(s1, s2, start);
      if (index == -1) break;
      cout << s1 << " matches " << s2 << " at position " << index << endl;
      start = index + 1;
   }
   if (start == 0) {
      cout << s1 << " has no matches in " << s2 << endl;
   }
}

// This is a helper function to convert a subsequence into its pair.
string matchingStrand(string strand){
    int len = strand.size();
    if (len == 0)
        return "";

    if (strand[0] == 'A')
        return "T" + matchingStrand(strand.substr(1));
    if (strand[0] == 'T')
        return "A" + matchingStrand(strand.substr(1));
    if (strand[0] == 'G')
        return "C" + matchingStrand(strand.substr(1));
    if (strand[0] == 'C')
        return "G" + matchingStrand(strand.substr(1));
    else
        return "Is this a DNA sequence? ";
}

/*
 * Function: findDNAMatch
 * Usage: int pos = findDNAMatch(s1, s2);
 *        int pos = findDNAMatch(s1, s2, start);
 * ---------------------------------------------
 * Returns the first index position at which strand s1 would bind to
 * the strand s2, or -1 if no such position exists.  If the start
 * parameter is supplied, the search begins at that index position.
 */

int findDNAMatch(string s1, string s2, int start) {

    int len1 = s1.size(), len2 = s2.size();

    // Be careful the end of recurrence, in case out of range.
    for (int i = start; i <= len2 - len1; i++){
        if (matchingStrand(s1) == s2.substr(i, len1))
            return i;
    }
    return -1;
}

