/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include "console.h"
#include "map.h"
#include <string>
#include <iostream>
using namespace std;

// findAll1difWords：找到一个ladder的下一个单词，要求不予原单词重复，在english中，不在unique中
Vector<string> findAll1difWords(const string& word, const Lexicon& english, const Lexicon &unique);

// printLadder：按照题目大意输出单词链
void printLadder(const Vector<string>& ladder);

// solve主函数：BFS寻找从start到destination的最短路径，其中所有单词都在词典english中
Vector<string> solve(const string& start, const string& destination, const Lexicon& english);


int main() {
    Lexicon english("EnglishWords.txt");
    string start, destination;

    while (true)
    {
        start = getLine("Enter start word (RETURN to exit): ");
        if (start == "RETURN") return -1;
        destination = getLine("Enter destination word: ");

        Vector ladder = solve(start, destination, english);
        if (!ladder.isEmpty()) printLadder(ladder);
        else {
            cout << "No ladder found." << endl;
        }
    }

    return 0;
}

Vector<string> findAll1difWords(const string& word, const Lexicon& english, const Lexicon &unique){
    Vector<string> res;

    // 将word的每一位都转化为a-z，并且temp与word不同，并且检查是否在english中以及是否不在unique中
    int length = word.length();

    for (int i = 0; i < length; i++){
        string temp = word;
        for (char j = 'a'; j <= 'z'; j++){
            temp[i] = j;
            if (temp != word && english.contains(temp) && !unique.contains(temp)){
                res.add(temp);
            }
        }
    }

    return res;
}

void printLadder(const Vector<string>& ladder){
    int sizea = ladder.size();
    cout << "Found ladder: ";
    for (int i = 0; i < sizea; i++){
        cout << ladder[i] << " ";
    }
    cout << endl;
}

void printLadder1(const Vector<string>& ladder){
    int sizea = ladder.size();
    cout << "test: ";
    for (int i = 0; i < sizea; i++){
        cout << ladder[i];
    }
    cout << endl;
}

Vector<string> solve(const string& start, const string& destination, const Lexicon& english){
    Queue<Vector<string>> ladders;
    //初始化放入只包含start的队列；
    ladders.enqueue(Vector(1, start));
    //初始化已访问单词
    Lexicon unique;
    unique.add(start);

    while(!ladders.isEmpty()){
        Vector curLadder = ladders.dequeue();
        //找到当前ladder的最后一个单词
        string endofLadder = curLadder[curLadder.size()-1];
        if (endofLadder == destination) return curLadder;

        Vector<string> nextWords = findAll1difWords(endofLadder, english, unique);

        for (const string &nextWord : nextWords){
            Vector<string> temp = curLadder;
            temp.add(nextWord);
            ladders.enqueue(temp);
            unique.add(nextWord);
        }
    }

    return Vector<string>();
}
