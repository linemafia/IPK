#include <iostream>
#include <string>
#include "faecher.cc"

int main() {
    FachListe fachListe;

    while (true) {
        std::cout << "1. Neues Fach hinzufuegen\n";
        std::cout << "2. Fach bearbeiten\n";
        std::cout << "3. Fachliste anzeigen\n";
        std::cout << "4. Programm beenden\n";
        std::cout << "Auswahl treffen (1-4): ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string name, kuerzel;
            unsigned int ects;
            std::cout << "Name des Fachs: ";
            std::cin >> name;
            std::cout << "Kuerzel des Fachs: ";
            std::cin >> kuerzel;
            std::cout << "ECTS des Fachs: ";
            std::cin >> ects;

            Fach newFach(name, kuerzel, ects);
            fachListe.addFach(newFach);
            std::cout << "Fach hinzugefuegt.\n";
        } else if (choice == 2) {
            std::string kuerzel;
            double note;
            std::cout << "Kuerzel des zu bearbeitenden Fachs: ";
            std::cin >> kuerzel;
            std::cout << "Neue Note eingeben: ";
            std::cin >> note;
            if (fachListe.noteEintragen(kuerzel, note)){
                std::cout << "Note eingetragen." << std::endl;
            } else  {
                std::cout << "Note kann nicht eingetragen werden." << std::endl;
            }
        } else if (choice == 3) {
            std::vector<std::string> fachliste = fachListe.list();
            for (const std::string &fach : fachliste) {
                std::cout << fach << "\n";
            }
            std::cout << "Gesamt-ECTS: " << fachListe.summeECTS() << "\n";
            std::cout << "Notendurchschnitt: " << fachListe.durchschnitt() << "\n";
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Ungueltige Auswahl. Bitte waehlen Sie erneut.\n";
        }
    }

    return 0;
}