#include "temperatur.hh"

 // Default-Konstruktor: die Temperatur auf 0K setzt.
Temperatur::Temperatur() {
    this -> _kelvinT = 0;
}
 // Konstuktor, der einen Kelvin-Wert entgegen nimmt
Temperatur::Temperatur(const double& kelvinT) {
    this -> _kelvinT = kelvinT;
}

// Getter für Kelvin, Celsius und Fahrenheit
double Temperatur::getKelvin() const {
    return this -> _kelvinT;
}
double Temperatur::getCelsius() const {
    return (this -> _kelvinT) - 273.15;
}
double Temperatur::getFahrenheit() const {
    return ((this -> _kelvinT) - 273.15) * (9.0 / 5.0) + 32;
}

// Setter für Kelvin, Celsius und Fahrenheit
bool Temperatur::setKelvin(const double& kelvinT) {
    this -> _kelvinT = kelvinT;
    return true;
}
bool Temperatur::setCelsius(const double& celsiusT) {
    this -> _kelvinT = celsiusT + 273.15;
    return true;
}
bool Temperatur::setFahrenheit(const double& fahrenheitT) {
    this -> _kelvinT = (fahrenheitT - 32) * (5.0 / 9.0) + 273.15;
    return true;
}

// eine neue Temperatur zurückgeben, die die Summe beider (Kelvin-)Temperaturen enthält.
Temperatur Temperatur::add(const Temperatur& temperature) const {
    return Temperatur((this -> _kelvinT) + (temperature._kelvinT));
}
