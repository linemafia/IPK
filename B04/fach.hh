#pragma once

#include <iomanip>
#include <sstream>
#include <string>

class Fach {
private:
    std::string kuerzel;
    std::string name;
    unsigned int ects;
    double note;

public:
    // legt neues Fach mit Standardnote 0.0 (= nicht teilgenommen) an
    Fach(std::string name, std::string kuerzel, unsigned int ects);
    
    // trägt eine Note für das Fach ein, wenn diese zwischen 1.0 und 5.0 ist und das Fach noch nicht bestanden ist
    // gibt genau dann true zurück, wenn das funktioniert hat
    bool noteEintragen(double note);

    // ein Fach ist bestanden, wenn eine valide Note eingetragen, und diese besser oder gleich 4.0 ist
    bool bestanden() const;

    // gibt die Note mal ECTS zurück, wenn das Fach bestanden ist, sonst 0
    double gewerteteNote() const;

    // gibt ECTS zurück, wenn Fach bestanden ist, sonst 0
    unsigned int getECTS() const;
    
    // gibt name zurück
    std::string getName() const;

    // gibt kuerzel zurück
    std::string getKuerzel() const;

    // gibt eine Repräsentation der Form "KÜR (name) [ects]: note" zurück
    // ects soll auch stimmen, wenn nicht bestanden!
    std::string toString() const;
};
