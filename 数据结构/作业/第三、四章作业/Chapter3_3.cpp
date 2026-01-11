#include <iostream>
using namespace std;

class RemovePunctuation {
private:
    string text;
public:
    RemovePunctuation(const string& input) : text(input) {}

    string process() {
        string result;
        for (char ch : text) {
            if (!ispunct(ch)) {
                result += ch;
            }
        }
        return result;
    }
};

int main() {
    string input = "Hello, World! Welcome to C++ programming.";
    RemovePunctuation remover(input);
    string output = remover.process();
    cout << "Original: " << input << endl;
    cout << "Processed: " << output << endl;
    return 0;
}