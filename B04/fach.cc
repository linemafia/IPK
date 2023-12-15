#pragma once

//#include <iomanip>
//#include <sstream>
//#include <string>

#include "fach.hh"

// legt neues Fach mit Standardnote 0.0 (= nicht teilgenommen) an
Fach::Fach(std::string name, std::string kuerzel, unsigned int ects) 
    : name(name), kuerzel(kuerzel)
    {
        this -> ects = ects;
        this -> note = 0.0;
    }

// trägt eine Note für das Fach ein, wenn diese zwischen 1.0 und 5.0 ist und das Fach noch nicht bestanden ist
// gibt genau dann true zurück, wenn das funktioniert hat
bool Fach::noteEintragen(double note) {
    if ((note < 1.0) || (note > 5.0)) 
        return false;
    if ((this -> note) != 0.0) // schon bestanden
        return false;
    this -> note = note;
    return true;
}

// ein Fach ist bestanden, wenn eine valide Note eingetragen, und diese besser oder gleich 4.0 ist
bool Fach::bestanden() const {
    if (this -> note == 0.0)
        return false;
    if (this -> note < 4.0)
        return false;
    return true;
}

// gibt die Note mal ECTS zurück, wenn das Fach bestanden ist, sonst 0
double Fach::gewerteteNote() const {
    if (!bestanden()) 
        return 0.0;
    return (this -> note) * (this -> ects);
}

// gibt ECTS zurück, wenn Fach bestanden ist, sonst 0
unsigned int Fach::getECTS() const {
    if (!bestanden()) 
        return 0;
    return this -> ects;
}

// gibt name zurück
std::string Fach::getName() const {
    return this -> name;
}

// gibt kuerzel zurück
std::string Fach::getKuerzel() const {
    return this -> kuerzel;
}

// gibt eine Repräsentation der Form "KÜR (name) [ects]: note" zurück
// ects soll auch stimmen, wenn nicht bestanden!
std::string Fach::toString() const {
    return (this -> kuerzel) + " (" + (this -> name) + ") [" + std::to_string(this -> ects) + "]: " + std::to_string(this -> note);
}