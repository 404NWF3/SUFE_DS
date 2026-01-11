#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void writeToFile(string fileName, const vector<int>& v);
void writeToFile(string fileName, const string& s);
void writeToFile(string fileName, double* d, int n);
string readFromFile(const string& fileName);

int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    string s = "Hello, File!";
    int ds = 3;
    double d[3] = {1.1, 2.2, 3.3};
    string vName = "ints.txt", sName="string.txt", dName="doubles.txt";
    writeToFile(vName, v);
    writeToFile(sName, s);
    writeToFile(dName, d, ds);
    cout << readFromFile(vName) << endl;;
    cout << readFromFile(sName) << endl;
    cout << readFromFile(dName) << endl;
    return 0;
}

void writeToFile(string fileName, const vector<int>& v) {
    ofstream fout(fileName);
    if (!fout.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return;
    }
    for (const int& i : v) {
        fout << i << " ";
    }
    fout.close();
}

void writeToFile(string fileName, const string& s) {
    ofstream fout(fileName);
    if (!fout.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return;
    }
    fout << s << endl;
    fout.close();
}

void writeToFile(string fileName, double* d, int n) {
    ofstream fout(fileName);
    if (!fout.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        return;
    }
    for (int i = 0; i < n; i++) {
        fout << d[i] << endl;
    }
    fout.close();
}

string readFromFile(const string& fileName) {
    ifstream fin(fileName);

    if (!fin.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
    }
    string s, ans;
    while (getline(fin, s)) {
        ans+=s+"\n";
    }

    fin.close();
    return ans;
}