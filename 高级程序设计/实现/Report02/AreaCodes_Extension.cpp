/*
 * File: AreaCodes.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * This file is the starter project for the Area Codes problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include "error.h"
#include "map.h"
#include "vector.h"
#include "simpio.h"
#include "strlib.h"
#include "console.h"

using namespace std;

/* Function prototypes */


void readCodeFile(string filename, Map<string, Vector<int>> & map);
string findAreaCode(int code, const Map<string, Vector<int>> & map);
/* Main program */

int main()
{
    Map<string, Vector<int>> areaCodeToState;
    readCodeFile("AreaCodes.txt", areaCodeToState);

    /*
 * The program looks up a numeric area codes for the United States
 * and Canada,works in both directions.  If the user enters a number,
 * the program prints out the state or province to which that code is
 * assigned. If the user enters a
 *  name, it prints out all the area
 * codes assigned to that name.
 * TODO fill the code.
 */

    string input;
    while (true){
        input = getLine("Enter the area code or the state name:");
        // 为输入分类：
        // 1. 是数字
        if (isdigit(input[0])){
            string ans = findAreaCode(stoi(input), areaCodeToState);
            if (ans == "") {
                cout << "There is no " << input << endl;
                continue;
            }
            cout << ans << endl;
        }

        // 2. 是地区
        else {
            if (!areaCodeToState.containsKey(input)){
                cout << "There is no " << input << endl;
                continue;
            }
            for (int i : areaCodeToState[input]){
                cout << i << endl;
            }
        }
    }


    return 0;
}

/*
 * Function: readCodeFile
 * Usage: readCodeFile(filename, map);
 * -----------------------------------
 * Reads a data file representing area codes and locations into the map,
 * which must be declared by the client.  Each line must consist of the
 * area code, a hyphen, and the name of the state/province.
 */

void readCodeFile(string filename, Map<string, Vector<int>> & map)
{
    ifstream infile;

    infile.open(filename.c_str());
    if (infile.fail())
        error("Can't read the data file");

    string line;
    while (getline(infile, line))
    {
        string Area = line.substr(4, line.length() - 4);
        int code = stoi(line.substr(0, 3));
        map[Area].add(code);
    }

    infile.close();
}

string findAreaCode(int code, const Map<string, Vector<int>> & map){
    for (const string &area: map){
        for (int i : map[area]){
            if (i == code){
                return area;
            }
        }
    }
    return "";
}
