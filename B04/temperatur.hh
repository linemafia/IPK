class Temperatur {
    public:
        Temperatur(); // Default-Konstruktor: die Temperatur auf 0K setzt.
        Temperatur(const double& kelvinT); // Konstuktor, der einen Kelvin-Wert entgegen nimmt

        // Getter für Kelvin, Celsius und Fahrenheit
        double getKelvin() const;
        double getCelsius() const;
        double getFahrenheit() const;

        // Setter für Kelvin, Celsius und Fahrenheit
        bool setKelvin(const double& kelvinT);
        bool setCelsius(const double& celsiusT);
        bool setFahrenheit(const double& fahrenheitT);

        Temperatur add(const Temperatur& temperature) const; // eine neue Temperatur zurückgeben, die die Summe beider (Kelvin-)Temperaturen enthält.
    private:
        double _kelvinT; //eine Temperatur intern in Kelvin speichert
};
