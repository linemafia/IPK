#include <vector>
#include <iostream>
#include <memory>

#include "vertraege.hh"

int main() {
    std::vector<Rechnung> vec;

    vec.push_back(Rechnung("Dago Bert Doug", "Am Geldspeicher 2", std::make_shared<FlatrateVertrag>(49.99)));
    vec.push_back(Rechnung("Britta Basic", "Mittelmaß 0815", std::make_shared<GrundgebuehrVertrag>(9.99, 0.09, 0.09)));
    vec.push_back(Rechnung("Papyrus Kuvert", "Postweg 69121", std::make_shared<OhneGrundgebuehrVertrag>(0.13, 0.25)));
    vec.push_back(Rechnung("Kevin Kurzgespräch", "Telefonkette 555", std::make_shared<SekuendlicherVertrag>(9.99, 0.12, 0.09)));
    vec.push_back(Rechnung("Pamela Prepaid", "Geldist-Allee 321", std::make_shared<GuthabenVertrag>(0.11, 0.11, 40.00)));
    
    auto v1 = std::make_shared<FlatrateVertrag>(39.99);
    auto vb = std::make_shared<VertragsBundle>(v1);
    vb->vertragRegistrieren(std::make_shared<GrundgebuehrVertrag>(9.99, 0.09, 0.09));
    vb->vertragRegistrieren(std::make_shared<SekuendlicherVertrag>(19.99, 0.09, 0.09));
    vb->get(0)->verbraucheSMSEinheit();
    vb->get(1)->verbraucheSMSEinheit();
    vec.push_back(Rechnung("Mareike Mutter von Zweien", "Familiensitz 7", vb));

    for (auto& rechnung : vec){
        for (int i = 0; i < 10; ++i){
            rechnung.getVertrag()->verbraucheSMSEinheit();
            rechnung.getVertrag()->verbraucheTelefonEinheiten(1.1);
        }
        std::cout << rechnung << std::endl;
        std::cout << "-----------" << std::endl;
    }
}