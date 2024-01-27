#include <iostream>
#include "rational.hh"

int main() {
    Rational a(1, 2);
    Rational b(3, 4);

    // Teste die Überladungen der Grundrechenarten für rationale Zahlen und unärem Minus
    Rational sum = a + b;
    Rational difference = a - b;
    Rational product = a * b;
    Rational quotient = a / b;
    Rational negation = -a;

    std::cout << "Summe: " << sum << std::endl;
    std::cout << "Differenz: " << difference << std::endl;
    std::cout << "Produkt: " << product << std::endl;
    std::cout << "Quotient: " << quotient << std::endl;
    std::cout << "Negation: " << negation << std::endl;
    std::cout << std::endl;

    // Teste die Überladungen der Grundrechenarten für double-Zahlen
    double sumDouble = a + 1.2;
    double differenceDouble = a - 1.2;
    double productDouble = a * 1.2;
    double quotientDouble = a / 1.2;

    std::cout << "a als double: " << a.eval() << std::endl;
    std::cout << "Summe mit Double: " << sumDouble << std::endl;
    std::cout << "Differenz mit Double: " << differenceDouble << std::endl;
    std::cout << "Produkt mit Double: " << productDouble << std::endl;
    std::cout << "Quotient mit Double: " << quotientDouble << std::endl;
    std::cout << std::endl;

    // Teste die Überladungen der grundlegenden Operationen mit Friend-Funktionen
    double sumDoubleReverse = 1.2 + a;
    double differenceDoubleReverse = 1.2 - a;
    double productDoubleReverse = 1.2 * a;
    double quotientDoubleReverse = 1.2 / a;

    std::cout << "Summe mit Double (andersherum): " << sumDoubleReverse << std::endl;
    std::cout << "Differenz mit Double (andersherum): " << differenceDoubleReverse << std::endl;
    std::cout << "Produkt mit Double (andersherum): " << productDoubleReverse << std::endl;
    std::cout << "Quotient mit Double (andersherum): " << quotientDoubleReverse << std::endl;
    std::cout << std::endl;

    // Teste die Überladungen der Zuweisungs-Rechen-Operatoren
    Rational c(5, 6);
    c += a;
    std::cout << "c += a: " << c << std::endl;

    c -= b;
    std::cout << "c -= b: " << c << std::endl;

    c *= a;
    std::cout << "c *= a: " << c << std::endl;

    c /= b;
    std::cout << "c /= b: " << c << std::endl;
    std::cout << std::endl;

    // Teste die Überladungen der Vergleichsoperatoren mit ternären Operatoren
    Rational x(3, 4);
    Rational y(2, 3);

    std::cout << "x ist" << (x == y ? "" : " nicht") << " gleich y" << std::endl;
    std::cout << "x ist" << (x != y ? " nicht" : "") << " gleich y" << std::endl;
    std::cout << "x ist" << (x < y ? "" : " nicht") << " kleiner als y" << std::endl;
    std::cout << "x ist" << (x <= y ? "" : " nicht") << " kleiner oder gleich y" << std::endl;
    std::cout << "x ist" << (x > y ? "" : " nicht") << " größer als y" << std::endl;
    std::cout << "x ist" << (x >= y ? "" : " nicht") << " größer oder gleich y" << std::endl;
    std::cout << std::endl;

    Rational z(3, -2);
    std::cout << z << " sollte vorne ein Minus haben." << std::endl;
    std::cout << std::endl;
    Rational err(1,0);
    std::cout << err << " sollte nach einem Fehler 0 sein." << std::endl;
    std::cout << std::endl;

    // Teste die Überladung des Umwandlungsoperators
    Rational nonZero(3, 4);
    Rational zero;

    if (nonZero) {
        std::cout << "nonZero ist true (nicht gleich 0)" << std::endl;
    } else {
        std::cout << "FEHLER: nonZero ist false (gleich 0)" << std::endl;
    }

    if (zero) {
        std::cout << "FEHLER: zero ist true (nicht gleich 0)" << std::endl;
    } else {
        std::cout << "zero ist false (gleich 0)" << std::endl;
    }

    return 0;
}
