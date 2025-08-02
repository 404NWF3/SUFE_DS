#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cassert>
#include <cmath>
using namespace std;

int *getPolynomial(int num);

void setPolyCoef(int *pt, int num, int maxval);

void releaseMem(int *pt);

void printPolynomial(int *pt, int num);

double polynomialVal(int *pt, int num, double x);

int *polynomialAdd(int *pt1, int *pt2, int num1, int num2);

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int *p1, *p2, *p3, num1 = 7, num2 = 5;;
    int maxval = 50;
    p1 = getPolynomial(num1);
    setPolyCoef(p1, num1, maxval);
    printPolynomial(p1, num1);
    double x = 1.2;
    cout << "the polynomial p1’s value when x = " << x << " is: " << polynomialVal(p1, num1, x) << endl;
    p2 = getPolynomial(num2);
    setPolyCoef(p2, num2, maxval);
    printPolynomial(p2, num2);
    cout << "the polynomial p2’s value when x = " << x << " is: " << polynomialVal(p2, num2, x) << endl;
    p3 = polynomialAdd(p1, p2, num1, num2);
    printPolynomial(p3, num1);
    cout << "the polynomial p3’s value when x = " << x << " is: " << polynomialVal(p3, num1, x) << endl;
    releaseMem(p1), releaseMem(p2), releaseMem(p3);

    return 0;
}

int *getPolynomial(int num) {
    int *ret = new int[num + 2];
    //第0位用于存储最高位次数
    ret[0] = num;
    for (int i = 1; i <= num + 1; i++) {
        ret[i] = 0;
    }
    return ret;
}

void setPolyCoef(int *pt, int num, int maxval) {
    for (int i = 1; i <= num + 1; i++) {
        pt[i] = rand() % maxval;
    }
}

void printPolynomial(int *pt, int num) {
    for (int i = num + 1; i >= 3; i--) {
        if (pt[i] != 0) printf("%dx^%d+", pt[i], i - 1);
    }
    if (pt[2] != 0) printf("%dx+", pt[2]);
    if (pt[1] != 0)printf("%d\n", pt[1]);
}

void releaseMem(int *pt) {
    delete[] pt;
}

double polynomialVal(int *pt, int num, double x) {
    double ret = 0.0;
    for (int i = 1; i <= num + 1; i++) ret += pt[i] * pow(x, i - 1);
    return ret;
}

int *polynomialAdd(int *pt1, int *pt2, int num1, int num2) {
    int *ret = new int[num1];
    ret[0] = num1;
    for (int i = 1; i <= num2 + 1; i++) ret[i] = pt1[i] + pt2[i];
    for (int i = num2 + 2; i <= num1 + 1; i++) ret[i] = pt1[i];
    return ret;
}
