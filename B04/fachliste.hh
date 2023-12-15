#pragma once

#include "fach.hh"
#include <vector>

class FachListe {
private:
    std::vector<Fach> _faecher;

public:
    FachListe();
    FachListe(std::vector<Fach> faecher); // trägt die Fächer in faecher direkt in _faecher ein.
    void addFach(Fach fach); // fügt fach zu _faecher hinzu
    unsigned int summeECTS(); // summiert die ECTS aller bestandenen Fächer
    double durchschnitt(); // nach ECTS gewertete Summe aller bestandenen Fächer
    std::vector<std::string> list(); // gibt vector von Zustandsbeschreibungen aller Fächer zurück
    bool noteEintragen(std::string kuerzel, double note); // trägt für (das erste) Fach mit Kürzel kuerzel die Note note ein; gibt genau dann true zurück, wenn das funktioniert hat
};