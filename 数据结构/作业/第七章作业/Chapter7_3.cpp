#include <iostream>
#include <vector>
using namespace std;

template <class Type>
Type find(const vector<Type> &, Type x);

template <class Type>
Type find(const vector<Type> &vec, Type x, int begin, int end);

int main()
{
    vector<int> v = {1, 2, 3, 4, 4, 6, 7};
    cout << "Search 1 at :" << find(v, 1) << endl;
    cout << "Search 2 at :" << find(v, 2) << endl;
    cout << "Search 3 at :" << find(v, 3) << endl;
    cout << "Search 4 at :" << find(v, 4) << endl;
    cout << "Search 6 at :" << find(v, 6) << endl;
    cout << "Search 7 at :" << find(v, 7) << endl;
    cout << "Search 5 at :" << find(v, 5) << endl;
    cout << "Search -1 at :" << find(v, -1) << endl;

    cout << "Search 8 at :" << find(v, 8);

    return 0;
}

template <class Type>
Type find(const vector<Type> &vec, Type x)
{
    return find(vec, x, 0, vec.size() - 1);
}

template <class Type>
Type find(const vector<Type> &vec, Type x, int begin, int end)
{
    int mid = begin + (end - begin) / 2;
    if (begin >= end){
        if (vec[mid] == x) return mid;
        else return -1;
    }
    if (vec[mid] > x)
        return find(vec, x, begin, mid - 1);
    else if (vec[mid] < x)
        return find(vec, x, mid + 1, end);
    else if (vec[mid] == x) return find(vec, x, begin, mid);
}