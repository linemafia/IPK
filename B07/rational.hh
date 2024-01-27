#ifndef H_RATIONAL
#define H_RATIONAL

//#include <stdexcept>
#include <iostream>

class Rational {
    private:
        // a)
        int numerator, denominator;
        static int gcd(int a, int b) {
            while (b != 0) {
                int c = a % b;
                a = b; b = c;
            }
            return a;
        }
    public:
        // a)
        Rational(int numeratorInit = 0, int denominatorInit = 1)
            : numerator(numeratorInit), denominator(denominatorInit) {
            if (denominator == 0)  {
                //throw std::invalid_argument("Error: division by zero.");
                std::cerr << "Error: division by zero." << std::endl;
                numerator = 0;
                denominator = 1;
                return;
            }
            int greatestCommonDivisor = gcd(numerator, denominator);
            numerator /= greatestCommonDivisor;
            denominator /= greatestCommonDivisor;
            if (denominator < 0) {
                denominator *= -1;
                numerator *= -1;
            }
        }

        // b)
        friend std::ostream& operator<< (std::ostream& s, const Rational& frac) {
            if (frac.denominator == 1)
                return s << frac.numerator;
            return s << frac.numerator << "/" << frac.denominator;
        }

        // c)
        Rational operator+(const Rational& other) const {
            return Rational(numerator * other.denominator + denominator * other.numerator, 
                            denominator * other.denominator);
        }
        Rational operator-(const Rational& other) const {
            return Rational(numerator * other.denominator - denominator * other.numerator, 
                            denominator * other.denominator);
        }
        Rational operator*(const Rational& other) const {
            return Rational(numerator * other.numerator, 
                            denominator * other.denominator);
        }
        Rational operator/(const Rational& other) const {
            return Rational(numerator * other.denominator, 
                            denominator * other.numerator);
        }
        // unary +, -
        Rational operator+() const {
            return Rational(*this);
        }
        Rational operator-() const {
            return Rational(-numerator, denominator);
        }

        // d)
        double eval() const {
            return static_cast<double>(numerator) / static_cast<double>(denominator);
        }
        double operator+(double other) {
            return eval() + other;
        }
        double operator-(double other) {
            return eval() - other;
        }
        double operator*(double other) {
            return eval() * other;
        }
        double operator/(double other) {
            return eval() / other;
        }
        // friendly operators with first double
        friend double operator+(double other, Rational frac) {
            return other + frac.eval();
        }
        friend double operator-(double other, Rational frac) {
            return other - frac.eval();
        }
        friend double operator*(double other, Rational frac) {
            return other * frac.eval();
        }
        friend double operator/(double other, Rational frac) {
            return other / frac.eval();
        }

        // e)
        Rational& operator= (const Rational& other) {
            if (this == &other) {
                return *this;
            }
            numerator = other.numerator;
            denominator = other.denominator;
            return *this;
        }
        Rational& operator+= (const Rational& other) {
            return *this = *this + other;
        }
        Rational& operator-= (const Rational& other) {
            return *this = *this - other;
        }
        Rational& operator*= (const Rational& other) {
            return *this = *this * other;
        }
        Rational& operator/= (const Rational& other) {
            return *this = *this / other;
        }

        // f)
        bool operator==(const Rational& other) const {
            return (numerator == other.numerator) && (denominator == other.denominator);
        }
        bool operator!=(const Rational& other) const {
            return !(*this == other);
        }
        bool operator<(const Rational& other) const {
            return (numerator * other.denominator < other.numerator * denominator);
        }
        bool operator>(const Rational& other) const {
            return (numerator * other.denominator > other.numerator * denominator);
        }
        bool operator<=(const Rational& other) const {
            return !(*this > other);
        }
        bool operator>=(const Rational& other) const {
            return !(*this < other);
        }

        // g)
        explicit operator bool() const {
            return numerator != 0;
        }
};

#endif