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
#include "simpio.h"
#include "strlib.h"
#include "console.h"

using namespace std;

/* Function prototypes */

void readCodeFile(string filename, Map<int,string> & map);
/* Main program */

int main()
{
    Map<int,string> areaCodeToState;

    readCodeFile("AreaCodes.txt", areaCodeToState);

    /*
 * The program looks up a numeric area codes for the United States
 * and Canada,works in both directions.  If the user enters a number,
 * the program prints out the state or province to which that code is
 * assigned. If the user enters a name, it prints out all the area
 * codes assigned to that name.
 * TODO fill the code.
 */

    string input;
    while (true){
        input = getLine("Enter the area code or the state name:");
        // 为输入分类：
        if (isdigit(input[0])){
            cout << areaCodeToState[stoi(input)] << endl;
        }

        else {
            for (int i : areaCodeToState){
                if (areaCodeToState[i] == input){
                    cout << i << endl;
                }
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

void readCodeFile(string filename, Map<int,string> & map)
{
    ifstream infile;

    infile.open(filename.c_str());
    if (infile.fail())
        error("Can't read the data file");

    string line;
    while (getline(infile, line))
    {

        /* The program parses the every line of Area Codes file,
     * inserts the pairs, (area code, the name of the state/province)
     * into the map.
     * TODO fill the code
    */

        int code = stoi(line.substr(0, 3));
        string state = line.substr(4, line.length()-4);
        map[code] = state;
    }

    infile.close();
}
