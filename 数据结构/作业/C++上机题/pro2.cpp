#include <iostream>
using namespace std;

class Complex {
private:
    double re, im;
public:
    Complex() : re(0), im(0) {}

    Complex (double re, double im) : re(re), im(im) {}

    Complex operator+(const Complex &c) const {
        return Complex(re + c.re, im + c.im);
    }

    Complex operator-(const Complex &c) const {
        return Complex(re - c.re, im - c.im);
    }

    Complex operator*(const Complex &c) const {
        return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
    }

    friend ostream &operator<<(ostream &os, const Complex& obj) {
        if (obj.re == 0 && obj.im == 0) {
            os << "0";
        }
        else if (obj.re == 0) {
            os << obj.im << "i";
        }
        else if (obj.im == 0) {
            os << obj.re;
        }
        else if (obj.im < 0) {
            os << obj.re << obj.im << "i";
        }
        else {
            os << obj.re << "+" << obj.im << "i";
        }
        return os;
    }
};

int main() {
    Complex c1(3, 4), c2(1, -2);
    cout << c1 << endl;
    cout << c2 << endl;

    cout << c1 + c2 << endl;
    cout << c1 - c2 << endl;
    cout << c1 * c2 << endl;
    return 0;
}