#include <iostream>
using namespace std;

template <typename T>
class Vector {
private:
    int cap;
    int count;
    T *arr;

public:
    Vector() : cap(4), count(0) {
        arr = new T[cap];
    }

    Vector(int n): cap(n) {
        arr = new T[cap];
        count = 0;
    }

    Vector(const Vector &v) {
        cap = v.cap;
        count = v.count;
        arr = new T[cap];
        for (int i = 0; i < count; i++)
            arr[i] = v.arr[i];
    }

    Vector &operator=(const Vector &v) {
        if (this != &v) {
            delete [] arr;
            cap = v.cap;
            count = v.count;
            arr = new T[cap];
            for (int i = 0; i < count; i++) {
                arr[i] = v.arr[i];
            }
        }
        return *this;
    }

    void resize() {
        cap = (cap == 0) ? 4 : cap * 2;
        T* temp = new T[cap];
        for (int i = 0; i < count; i++) {
            temp[i] = arr[i];
        }
        delete [] arr;
        arr = temp;
    }

    void add(T i) {
        if (count >= cap) {
            resize();
        }
        arr[count++] = i;
    }

    T get(int i) {
        return arr[i];
    }

    int getCount() const{
        return count;
    }

    T operator[](int i) const{
        return arr[i];
    }

    T& operator[](int i){
        return arr[i];
    }

    // Vector operator+(const Vector& v) {
    //     Vector temp(max(getCount(), v.getCount()));
    //     if (getCount() > v.getCount()) {
    //         int i = 0;
    //         for (; i < v.getCount(); i++) {
    //             temp.add(arr[i] + v[i]);
    //         }
    //         while (i < getCount()) {
    //             temp.add(arr[i]);
    //         }
    //     }
    //     else {
    //         int i = 0;
    //         for (; i < getCount(); i++) {
    //             temp.add(arr[i] + v[i]);
    //         }
    //         while (i < v.getCount()) {
    //             temp.add(arr[i]);
    //         }
    //     }
    //     return temp;
    // }

    Vector operator+(const Vector &v) const {
        int size = min(getCount(), v.getCount());
        Vector res(size);
        res.count = size;
        for (int i = 0; i < size; i++) {
            res.arr[i] = arr[i] + v.arr[i];
        }
        return res;
    }

    bool operator==(const Vector& v) const {
        if (getCount() != v.getCount()) return false;
        for (int i = 0; i < getCount(); i++) {
            if (arr[i] != v[i]) return false;
        }
        return true;
    }

    friend ostream& operator<<(ostream& os, const Vector& v) {
        for (int i = 0; i < v.getCount(); i++) {
            os << v[i] << " ";
        }
        return os;
    }

    ~Vector() {
        delete[] arr;
        arr = nullptr;
    }

};

int main() {
    /*
3 3 2 2
1 2 3
4 5 6
1.5 2.5
1.5 2.5
     */

    int s1, s2, s3, s4;
    cin >> s1 >> s2 >> s3 >> s4;
    Vector<int> v1(s1), v2(s2);
    Vector<double> d1(s3), d2(s4);

    for (int i = 0; i < s1; i++) {
        int k;
        cin >> k;
        v1.add(k);
    }

    for (int i = 0; i < s2; i++) {
        int k;
        cin >> k;
        v2.add(k);
    }

    for (int i = 0; i < s3; i++) {
        double k;
        cin >> k;
        d1.add(k);
    }

    for (int i = 0; i < s4; i++) {
        double k;
        cin >> k;
        d2.add(k);
    }

    cout << v1 + v2 << endl;
    cout << (d1 == d2) << endl;

    return 0;
}