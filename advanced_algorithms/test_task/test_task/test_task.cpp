#include <iostream>

template <typename T>
class Complex {
private:
    T real;   
    T imag;   

public:
    Complex(T r = T(), T i = T()) : real(r), imag(i) {}

    T getReal() const { return real; }
    T getImag() const { return imag; }

    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }

    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }

    Complex operator-() const {
        return Complex(-real, -imag);
    }

    Complex& operator=(const Complex& other) {
        if (this != &other) {
            real = other.real;
            imag = other.imag;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
        return os;
    }
};

int main() {
    Complex<double> c1(3.0, 4.0);
    Complex<double> c2(1.0, -2.0);

    Complex<double> sum = c1 + c2;
    Complex<double> difference = c1 - c2;
    Complex<double> neg = -c1;
    c1 += c2;
    c2 -= sum;

    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << difference << std::endl;
    std::cout << "Negation of c1: " << neg << std::endl;

    return 0;
}
