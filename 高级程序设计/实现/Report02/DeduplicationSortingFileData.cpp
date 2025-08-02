/*
 * File: sortingfiledata.cpp
 * This program sorts integers read from the text file.
 */

#include <fstream>
#include <string>
#include <cctype>
#include "set.h"
#include "error.h"
#include "filelib.h"
#include <string>
#include "console.h"
#include "simpio.h"

using namespace std;

int stringToInt(string s);
void sortArray(int data[], int counter);
void displayArray(int data[], int counter);

/* Main program */

int main(){

    // Here, we assume that the number of integers in raw-data.txt does not exceed 100
    int data[100], counter = 0;
    Set<int> Unique;

    ifstream inputFile("raw-data.txt");
    if(!inputFile) error("Unable to open raw-data.txt for reading.");

    while (inputFile >> data[counter++]){
        Unique.add(data[counter-1]);
    }

    inputFile.close();

    // sort the array
    sortArray(data,counter);
    // Open binary format file as output file stream
    // TODO: fill the code

    // Open binary format file as output file stream
    ofstream outputFile("sorted-data.bin", ios::binary);
    if (!outputFile) error("Unable to open sorted-data.bin for writing.");


    for (int i : Unique){
        cout << i << " ";
        outputFile.write(reinterpret_cast<char*>(&i), sizeof(int));
    }
    cout << endl;

    outputFile.close();


    // ---------------  End of Task 1  --------------

    // ------------ Beginning of Task 2  ------------
    // Read the data from sorted-data.bin, calaulate the median and output to the screen.
    // Open binary format file as input file stream
    // : fill the code

    ifstream binFile("sorted-data.bin", ios::binary);
    if (!binFile) error("Unable to open sorted-data.bin for reading.");

    double median = 0;
    int array[100];
    int counter1 = 0;

    int a;
    while (binFile.read(reinterpret_cast<char*>(&a), sizeof(int))) {
        array[counter1++] = a;
    }

    binFile.close();


    if (counter1 % 2 == 1) {
        median = array[counter1 / 2];
    } else {
        median = (array[counter1 / 2 - 1] + array[counter1 / 2]) / 2.0;
    }
    cout << "Median is: " << median << endl;

    // ---------------  End of Task 2  --------------
    return 0;
}

void sortArray(int data[], int counter)
{
    for(int i = 0; i < counter-1; i++)
        for(int j = 0; j < counter-i-1; j++){
            if (data[j] > data[j+1]){
                int temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
}

void displayArray(int data[], int counter)
{
    for(int i = 0; i < counter; i++) {
           cout << data[i] << "-";
    }
    cout << endl;
}

int stringToInt(string s)
{
    int sum = 0;
    for(unsigned int i = 0; i < s.length(); i++){
        if(isdigit(s[i])){
            sum *= 10;
            sum += (s[i] - '0');
        }
        else{
            cout << "data error!" << endl;
            return 0;
        }
    }
    return sum;
}
