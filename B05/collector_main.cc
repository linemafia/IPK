#include <iostream>
#include <string>
#include "collector.hh"

int main() {
    Collector<float> floatCollector(10.5f, -2.2f);
    floatCollector.add(5.5f);
    std::cout << "Float Collector Result: " << floatCollector.digest() << std::endl;

    Collector<std::string> stringCollector("0", ", ");
    for(int i = 1; i <= 9; ++i){
        stringCollector.add(std::to_string(i*i));
    }

    std::cout << "Die ersten 10 Quadratzahlen sind: " << stringCollector.digest() << std::endl;

    return 0;
}
