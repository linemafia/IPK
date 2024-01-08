template <typename T>
class Collector {
    private:
    T sum, adder;
    public:
    Collector(const T& initialSum, const T& initialAdder): sum(initialSum), adder(initialAdder) {};

    // Methode zum Hinzufügen eines Werts zu sum und adder
    void add(const T& value) {
        sum += adder;
        sum += value;
    }
    
    // Methode zum Abrufen des aktuellen Werts von sum
    T digest() const {
        return sum;
    }
};