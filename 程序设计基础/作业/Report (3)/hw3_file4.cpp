#include <algorithm>
#include <iostream>
using namespace std;

template<class T>
void printArray(T array[], int size);

template<class T>
void swap(T *a, T *b) {
    T *temp = *a;
    *a = *b;
    *b = *temp;
}

template<class T>
void selectSort(T array[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        // cout << i << endl;
        int max_distance = max_element(array, array + i + 1) - array;
        // cout << array[i] << " " << array[max_distance] << endl;
        if (array[i] != array[max_distance]) swap(array[i], array[max_distance]);
        // printArray(array, size);
    }
}

template<class T>
void printArray(T array[], int size) {
    for (int i = 0; i < size; i++) cout << array[i] << " ";
    cout << endl;
}

int main() {
    int intarr[10]={20,18, 7, 19, 9, 8, 2, 12,10,1};
    float floatarr[12]={9.1, 1.9, 8.2, 7.3, 6.4, 3.7, 5.5, 4.6, 2.8, 5.8, 4.6, 2.9};
    char chararr[8]= {'C', 'd', 'e','x','B','D','A', 'a' };
    selectSort(intarr,10);
    cout << "the sorted int array:"; printArray(intarr,10);
    selectSort(floatarr,12);
    cout << "the sorted float array:"; printArray(floatarr,12);
    selectSort(chararr,8);
    cout << "the sorted char array:"; printArray(chararr,8);
    return 0;
}
