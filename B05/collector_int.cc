#include <iostream>

class Collector {
private:
    int sum;
    int adder;

public:
    // Konstruktor
    Collector(int initialSum, int initialAdder) : sum(initialSum), adder(initialAdder) {}

    // Methode zum Hinzufügen eines Werts zu sum und adder
    void add(int value) {
        sum += adder;
        sum += value;
    }

    // Methode zum Abrufen des aktuellen Werts von sum
    int digest() const {
        return sum;
    }
};

int main() {
    // Beispiel für die Verwendung der Collector-Klasse
    Collector myCollector(0, 5);
    
    myCollector.add(3);
    std::cout << "Summe nach dem Hinzufügen von 3: " << myCollector.digest() << std::endl;

    myCollector.add(7);
    std::cout << "Summe nach dem Hinzufügen von 7: " << myCollector.digest() << std::endl;

    return 0;
}
