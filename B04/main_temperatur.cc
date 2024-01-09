#include <iostream>
#include "temperatur.cc"


/*
main-Funktion, die einen char (’K’, ’C’, ’F’) und einen double einließt,
die Temperatur entsprechend setzt, und auf der Konsole ausgibt
*/
int main() {
    std::cout << "Enter a unit of temperature measurment ";
    Temperatur temperature;
    while (true) {
        std::cout << "[K/C/F]" << std::endl;
        char measurmentT; 
        std::cin >> measurmentT;
        if (measurmentT == 'K') {
            std::cout << "Enter temperature : ";
            double valueT; std::cin >> valueT;
            temperature.setKelvin(valueT);
            break;
        } else if (measurmentT == 'C') {
            std::cout << "Enter temperature : ";
            double valueT; std::cin >> valueT;
            temperature.setCelsius(valueT);
            break;
        } else if (measurmentT == 'F') {
            std::cout << "Enter temperature : ";
            double valueT; std::cin >> valueT;
            temperature.setFahrenheit(valueT);
            break;
        } 
    }
    std::cout << "Kelvin: " << temperature.getKelvin() << " K" << std::endl;
    std::cout << "Celsius: " << temperature.getCelsius() << " °C" << std::endl;
    std::cout << "Fahrenheit: " << temperature.getFahrenheit() << " °F" << std::endl;
}