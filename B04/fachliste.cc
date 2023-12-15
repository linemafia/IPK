#include "fachliste.hh"

FachListe::FachListe() {}

// trägt die Fächer in faecher direkt in _faecher ein.
FachListe::FachListe(std::vector<Fach> faecher) : _faecher(_faecher) {
}

// fügt fach zu _faecher hinzu
void FachListe::addFach(Fach fach)  {
    (this -> _faecher).push_back(fach);
}

// summiert die ECTS aller bestandenen Fächer
unsigned int FachListe::summeECTS() {
    unsigned int summ = 0;
    for (Fach& f : (this -> _faecher)) 
        summ += f.getECTS();
    return summ;
}

// nach ECTS gewertete Summe aller bestandenen Fächer
double FachListe::durchschnitt() {
    double summ = 0;
    for (Fach& f : (this -> _faecher)) 
        summ += f.gewerteteNote();
    return summ;
} // !! Warum heißt diese Funktion "durchschnitt", wenn dies laut der Beschreibung eine gewichtete Summe ist?

// gibt vector von Zustandsbeschreibungen aller Fächer zurück
std::vector<std::string> FachListe::list() {
    std::vector<std::string> list((this -> _faecher).size());
    std::vector<std::string>::iterator it = list.begin();
    for (Fach& f : (this -> _faecher)) {
        *it = f.toString();
        it ++;
    }
    return list;
} 

// trägt für (das erste) Fach mit Kürzel kuerzel die Note note ein; gibt genau dann true zurück, wenn das funktioniert hat
bool FachListe::noteEintragen(std::string kuerzel, double note) {
    for (Fach& f : (this -> _faecher))
        if (f.getKuerzel() == kuerzel)
            return f.noteEintragen(note);
    return false;
}