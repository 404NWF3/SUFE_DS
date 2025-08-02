/*
 * File: Boggle.cpp
 * -----------------------
 * Name: [TODO: enter name here]
 * This file is the starter code for the Boggle Game problem
 * from Assignment #4.
 * [TODO: extend the documentation]
 */

#include <cctype>
#include <fstream>
#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
//#include <QMediaPlayer>
#include "console.h"

using namespace std;

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;
const string STANDARD_CUBES_FIlE = "res/cubes16.txt";
const string BIG_BOGGLE_CUBES_FILE = "res/cubes25.txt";

int dir_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dir_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Position{
    int x,  y;
    Position(int x = 0, int y = 0){
        this->x = x;
        this->y = y;
    }
};

/* Function prototypes */

void welcome();
void giveInstructions();
void playBoggle();

// 1. The Dice
// 读取cubes.txt
Vector<string> readCubesFromFile(const string& filename);
// 洗牌算法shuffle
void shuffleCubes(Vector<string>& cubes);
// 创建游戏面板
void fillBoard(Grid<char>& board, const Vector<string>& cubes);
void fillBoard(Grid<char>& board, const string& words);
// 整合The Dice部分的整个流程
void initializeGame(Grid<char>& board, const string &filename, bool isCustom);

// 2. Human's Turn
void HumanTurn(const Grid<char>& board, const Lexicon& english, Set<string> &found);
bool CheckValid(const string &targetWord, const Lexicon & english, const Set<string> &found);
bool CheckContains(const Grid<char>& board, const string &targetWord);
bool CheckContainsRec(const Grid<char>& board, string word, const Position& p, Grid<bool> &used, Vector<Position> & track);

// 3. Computer's Turn
void ComputerTurn(const Grid<char>& board, const Lexicon& english, const Set<string> &HumanFound, Set<string> &ComputerFound);
void ComputerFinding(const Grid<char>& board, const Lexicon& english, const Position& p, string & prefix,const Set<string> &HumanFound, Set<string> &ComputerFound, Grid<bool> &used);
/* Main program */

// You need to design specific data structures and functions
// to complete this assignment.

int main() {
    welcome();
    if (getYesOrNo("Do you need instructions? ")) {
        giveInstructions();
    }

    playBoggle();
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}

void playBoggle() {
    // 1. The Dice
    Lexicon english("res/EnglishWords.txt");
    string filename = "";
    int scale = 0;
    bool isCustom = false;

    //  [TODO: Fill and extend code here]

    while (true) {
        while (true){
            string mode = getLine("which mode do you prefer? Cubes16 or Cubes25? :");

            if (mode == "Cubes16"){
                filename = STANDARD_CUBES_FIlE;
                scale = 4;
                break;
            }
            else if (mode == "Cubes25"){
                filename = BIG_BOGGLE_CUBES_FILE;
                scale = 5;
                break;
            }
            else if (mode == "quit")
                break;
            else
                cout << "Please input 'Cubes16' or 'Cubes25' to play or 'exit' to quit!";
        }

        while (true){
            string mode = getLine("Would you like Custom mode or Random mode?: ");
            if (mode == "Random"){
                isCustom = false;
                break;
            }
            else if (mode == "Custom"){
                isCustom = true;
                break;
            }
            else{
                cout << "Please input 'Custom' or 'Random' to play or 'exit' to quit!";
            }
        }

        Grid<char> board(scale, scale);

        GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
        gw.setLocation(50,50);
        initGBoggle(gw);
        initializeGame(board, filename, isCustom);

        // 2. Human Turn
        cout << endl;
        cout << "It's your turn!" << endl;
        Set<string> found;
        HumanTurn(board, english, found);
        cout << found << endl;

        // 3. Computer Turn
        Set<string> ComputerFound;
        ComputerTurn(board, english, found, ComputerFound);
        cout << ComputerFound << endl;

        if (!getYesOrNo("Would you like to play again? ")) break;
    }

    exitGraphics();
}

Vector<string> readCubesFromFile(const string& filename){
    Vector<string> cubes;
    ifstream file(filename);

    string line;
    while (getline(file, line)){
        if (line != "")
            cubes.add(line);
    }

    return cubes;
}

void shuffleCubes(Vector<string>& cubes){
    int size = cubes.size();
    for (int i = 0; i < cubes.size(); i++){
        int r = randomInteger(i, size - 1);
        string temp = cubes[i];
        cubes[i] = cubes[r];
        cubes[r] = temp;
    }
}

void fillBoard(Grid<char>& board, const Vector<string>& cubes){
    int index = 0;
    for (int i = 0; i < board.numRows(); i++){
        for (int j = 0; j < board.numCols(); j++){
            string cur = cubes[index++];
            int res = randomInteger(0, cur.size() - 1);
            board[i][j] = cur[res];
        }
    }
}

void fillBoard(Grid<char>& board, const string& words){
    int index = 0;
    for (int i = 0; i < board.numRows(); i++){
        for (int j = 0; j < board.numCols(); j++){
            board[i][j] = words[index++];
        }
    }
}

void initializeGame(Grid<char>& board, const string &filename, bool isCustom){
    if (isCustom){
        string words;
        while (true){
            words = getLine("Please enter 16 upper letters for Cubes16 mode and 25 upper letters for Cubers25 mode: ");
            if (board.numCols() == 4){
                if (words.length() == 16){
                    break;
                }
            }
            if (board.numCols() == 5){
                if (words.length() == 25){
                    break;
                }
            }
            cout << "You should input a Valid count of letters";
        }
        toUpperCaseInPlace(words);
        fillBoard(board, words);

    }
    else {
        Vector<string> cubes = readCubesFromFile(filename);
        shuffleCubes(cubes);
        fillBoard(board, cubes);
    }

    int scale = board.numCols();

    drawBoard(scale, scale);

    cout << "finish" << endl;

    for (int row = 0; row < scale; row++) {
        for (int col = 0; col < scale; col++) {
            labelCube(row, col, board[row][col]);
        }
    }
}

bool CheckValid(const string &targetWord, const Lexicon & english, const Set<string> &found){
    if (targetWord.length() < 4) {
        cout << "Not valid Word Length!" << endl;
        return false;
    }
    if (!english.contains(targetWord)){
        cout << "Not valid Word in the dictionary!" << endl;
        return false;
    }
    if (found.contains(targetWord)){
        cout << "You have found the word!" << endl;
        return false;
    }

    return true;
}

void HumanTurn(const Grid<char>& board, const Lexicon& english, Set<string> & found){
    while (true){
        string targetWord = getLine("Input a word (or Enter to stop):");
        if (targetWord == "") break;

        toLowerCaseInPlace(targetWord);

        // 排除两种不存在的情况
        if (!CheckValid(targetWord, english, found))
            continue;

        if (CheckContains(board, targetWord)){
            cout << "You have found a new word: " << targetWord << endl;
            found.add(targetWord);
        }
        else {
            cout << "Can not Found the word: " << targetWord << endl;
        }
    }
}

bool CheckContains(const Grid<char>& board, const string &targetWord){
    string word = targetWord;
    toUpperCaseInPlace(word);
    Queue<Position> q;

    for (int i = 0; i < board.numRows(); i++){
        for (int j = 0; j < board.numCols(); j++){
            if (board[i][j] == word[0]){
                Position temp(i, j);
                q.enqueue(temp);
            }
        }
    }

    while (!q.isEmpty()){
        Position cur = q.dequeue();
        Grid<bool> used(board.numRows(), board.numCols(), false);
        used[cur.x][cur.y] = true;
        Vector<Position> track;
        track.add(cur);
        if (CheckContainsRec(board, word, cur, used, track)){
            recordWordForPlayer(word, HUMAN);
            for (Position p: track){
                highlightCube(p.x, p.y, true);
            }
            pause(1000);
            for (Position p: track){
                highlightCube(p.x, p.y, false);
            }
            return true;
        }
    }

    return false;
}

bool CheckContainsRec(const Grid<char>& board, string word, const Position& p,  Grid<bool> & used, Vector<Position>& track){
    int length = word.length();
    if (length == 1)
        if (board[p.x][p.y] == word[0])
            return true;

    word = word.substr(1);
    for (int dir = 0; dir < 8; dir++){
        // 上下左右左上左下右上右下
        Position cur(p.x + dir_x[dir], p.y + dir_y[dir]);

        // 保证不越界
        if (cur.x >= 0 && cur.y >= 0 && cur.x < board.numRows() && cur.y < board.numCols()){
            if (board[cur.x][cur.y] == word[0] && used[cur.x][cur.y] == false){
                used[cur.x][cur.y] = true;
                track.add(cur);
                bool ans = CheckContainsRec(board, word, cur, used, track);
                if (ans) return true;
                used[cur.x][cur.y] = false;
                track.remove(track.size() - 1);
            }

        }
    }
    return false;
}

void ComputerTurn(const Grid<char>& board, const Lexicon& english, const Set<string> &HumanFound, Set<string> &ComputerFound){
    for (int i = 0; i < board.numRows(); i++){
        for (int j = 0; j < board.numCols(); j++){
            Position cur(i, j);
            string pre = string(1, board[i][j]);
            Grid<bool> used(board.numRows(), board.numCols(), false);
            used[cur.x][cur.y] = true;
            ComputerFinding(board, english, cur, pre, HumanFound, ComputerFound, used);
        }
    }
}

void ComputerFinding(const Grid<char>& board, const Lexicon& english, const Position& p, string & prefix,const Set<string> &HumanFound, Set<string> &ComputerFound, Grid<bool> &used){
    if (!english.containsPrefix(prefix))
        return;

    string word = toLowerCase(prefix);
    if (english.contains(word) && !HumanFound.contains(word) && !ComputerFound.contains(word) &&
        prefix.length() >=4){
        ComputerFound += prefix;
        recordWordForPlayer(prefix, COMPUTER);
    }

    for (int dir = 0; dir < 8; dir++){
        // 上下左右左上左下右上右下
        Position cur(p.x + dir_x[dir], p.y + dir_y[dir]);

        // 保证不越界
        if (cur.x >= 0 && cur.y >= 0 && cur.x < board.numRows() && cur.y < board.numCols() && used[cur.x][cur.y] == false){
            prefix += board[cur.x][cur.y];
            used[cur.x][cur.y] = true;
            ComputerFinding(board, english, cur, prefix, HumanFound, ComputerFound, used);
            prefix = prefix.substr(0, prefix.length()-1);
            used[cur.x][cur.y] = false;
        }
    }
}
