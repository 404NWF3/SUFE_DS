/*
 * File: AnagramClusters.cpp
 * --------------------
 * Name: Ni Weifeng
 * This file is the starter project for the Anagram Clusters problem
 * on Assignment #2.
 * 2024110089
 */

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "simpio.h"
#include "strlib.h"
#include "map.h"
using namespace std;

/* Function prototypes */

string sortedVersionOf(const string& input);

/* Main program */

int main()
{
    Lexicon english("EnglishWords.txt");
    Map<string, Lexicon> anagramClusters;

    /* Distribute words into their anagram clusters by using
     * the handy map autoinsertion feature.
     * [TODO: fill the code]
     */

    // 遍历english中的每一个单词，找到原型，加到anaC.lexcion中
    for (const string& word : english){
        anagramClusters[sortedVersionOf(word)].add(word);
    }


    while (true) {

        string word = getLine("Enter a word: ");

        /* The key we'll use will be the sorted version of the word.
         * Question to ponder: why convert to lower case, then
         * sort, rather than the other way around?
         */


        string key = sortedVersionOf(toLowerCase(word));

        if (anagramClusters.containsKey(key)) {
            cout << anagramClusters[key] << endl;
        } else {
            cout << "Opps, such words are not to be found here!" << endl;
        }
    }
    return 0;
}


/**
 * Given a word, returns a string formed by sorting the letters
 * in that word.
 *
 * @param word The input word
 * @return A sorted version of the word
 */
string sortedVersionOf(const string& input) {
    /* This algorithm is an implementation of an algorithm called
     * "Counting Sort." It's described in the slides 05 for Lecture.
     */

    Map<char, int> count_table;
    for (char c : input){
        count_table[toLowerCase(c)] += 1;
    }

    string result;
    /* Iterate over the frequency table and build the result
     * string from the information it contains.
     * [TODO: fill the code]
     */

    for (char i = 'a' ; i <= 'z'; i++){
        result += string(count_table[i], i);
    }

    return result;
}



























