#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<class Type>
void SelectionSort(vector<Type>& arr){
    int n = arr.size();
    for(int i = 0; i < n - 1; i++){
        int maxIndex = i;
        for(int j = i + 1; j < n; j++){
            if(arr[j] > arr[maxIndex])
                maxIndex = j;
        }
        if(maxIndex != i)
            swap(arr[i], arr[maxIndex]);
    }
}

struct student{
    string number;
    int score;
    student(string n, int s): number(n), score(s) {}
    bool operator<(const student& other) const{
        return score < other.score;
    }
    bool operator>(const student& other) const{
        return score > other.score;
    }
    friend ostream& operator<<(ostream& os, const student& stu){
        os << "{" << stu.number << " " << stu.score << "}";
        return os;
    }
};

int main(){
    // vector<student> students;
    // for (int i = 0; i < 40; i++){
    //     string num;
    //     int sc;
    //     cin >> num >> sc;
    //     students.push_back({num, sc});
    // }

    vector<student> students = {
        student("2024001", 78), student("2024002", 85), student("2024003", 92), student("2024004", 64),
        student("2024005", 73), student("2024006", 88), student("2024007", 55), student("2024008", 91),
        student("2024009", 67), student("2024010", 76), student("2024011", 82), student("2024012", 95),
        student("2024013", 60), student("2024014", 70), student("2024015", 84), student("2024016", 58),
        student("2024017", 79), student("2024018", 86), student("2024019", 63), student("2024020", 97),
        student("2024021", 45), student("2024022", 69), student("2024023", 81), student("2024024", 75),
        student("2024025", 90), student("2024026", 52), student("2024027", 83), student("2024028", 74),
        student("2024029", 66), student("2024030", 89), student("2024031", 93), student("2024032", 57),
        student("2024033", 72), student("2024034", 80), student("2024035", 65), student("2024036", 94),
        student("2024037", 51), student("2024038", 77), student("2024039", 87), student("2024040", 68)
    };

    cout << "Original Students:" << endl;
    int i = 0;
    for(const auto& stu : students){
        cout << stu << "  ";
        if (++i % 5 == 0)
            cout << endl;
    }

    SelectionSort(students);

    cout << "Sorted students by score:" << endl;
    i = 0;
    for(const auto& stu : students){
        cout << stu << "  ";
        if (++i % 5 == 0)
            cout << endl;
    }

    return 0;
}
