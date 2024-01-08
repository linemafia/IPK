/*
direkt initialisiert. Testen Sie ihre Klasse in einer
triplet_main.cc, indem Sie alle Methoden einmal aufrufen und Ausgaben dafür erzeugen.
*/
#include <iostream>
#include <string>
#include "triplet.hh"

void show(const Triplet& triplet) {
    std::cout << "first : " << triplet.first() << std::endl;
    std::cout << "second : " << triplet.second() << std::endl;
    std::cout << "third : " << triplet.third() << std::endl;
}

int main() {
    Triplet<int, double, char> triplet(42, 3.14, 'F');
    std::cout << "Initial triplet: " << std::endl;
    show(triplet);

    triplet.setFirst(57);
    triplet.setSecond(2.78);
    triplet.setThird('ß');
    std::cout << "Modified triplet: " << std::endl;
    show(triplet);
}