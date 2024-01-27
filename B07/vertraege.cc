#include "vertraege.hh"
#include <cmath>
#include <stdexcept>
#include <iostream>     // std::fixed
#include <iomanip>      // std::setprecision


// b)
FlatrateVertrag::FlatrateVertrag(double fixrateInit) : fixrate(fixrateInit) {}
double FlatrateVertrag::berechneKosten() const {
    return fixrate;
}
void FlatrateVertrag::verbraucheTelefonEinheiten(double) {}
void FlatrateVertrag::verbraucheSMSEinheit() {}

// c)
GrundgebuehrVertrag::GrundgebuehrVertrag(double fixedChargeInit, double callPriseInit, double smsPriseInit) :
    fixedCharge(fixedChargeInit), callPrise(callPriseInit), smsPrise(smsPriseInit) {}

double GrundgebuehrVertrag::berechneKosten() const {
    return fixedCharge + callMinutes * callPrise + smsNum * smsPrise;
}
void GrundgebuehrVertrag::verbraucheTelefonEinheiten(double min) {
    callMinutes += std::ceil(min);
}
void GrundgebuehrVertrag::verbraucheSMSEinheit() {
    smsNum ++;
}         

OhneGrundgebuehrVertrag::OhneGrundgebuehrVertrag(double callPriseInit, double smsPriseInit) :
    GrundgebuehrVertrag(0, callPriseInit, smsPriseInit) {}

// d)
SekuendlicherVertrag::SekuendlicherVertrag(double fixedChargeInit, double callPriseInit, double smsPriseInit) :
    GrundgebuehrVertrag(fixedChargeInit, callPriseInit, smsPriseInit) {}

void SekuendlicherVertrag::verbraucheTelefonEinheiten(double min) {
    callMinutes += min;
}

// e)
GuthabenVertrag::GuthabenVertrag(double callPriseInit, double smsPriseInit, double fixedCreditInit) :
    OhneGrundgebuehrVertrag(callPriseInit, smsPriseInit), fixedCredit(fixedCreditInit) {}

double GuthabenVertrag::berechneKosten() const {
    return std::ceil(OhneGrundgebuehrVertrag::berechneKosten() / fixedCredit) * fixedCredit;
}

// f)
VertragsBundle::VertragsBundle(std::shared_ptr<AbstrakterVertrag> mainDealInit) :
    mainDeal(mainDealInit) {}

double VertragsBundle::berechneKosten() const {
    double check = mainDeal -> berechneKosten();
    for (auto deal : deals)
        check += deal -> berechneKosten();
    return check;
}
void VertragsBundle::verbraucheTelefonEinheiten(double min) {
    mainDeal -> verbraucheTelefonEinheiten(min);
}
void VertragsBundle::verbraucheSMSEinheit() {
    mainDeal -> verbraucheSMSEinheit();
}

std::shared_ptr<AbstrakterVertrag> VertragsBundle::get() {
    return mainDeal;
}
std::shared_ptr<AbstrakterVertrag> VertragsBundle::get(unsigned int i) {
    if (i >= deals.size())
        throw std::out_of_range("Error: index out of range.");
    return deals[i];
}
void VertragsBundle::vertragRegistrieren(std::shared_ptr<AbstrakterVertrag> subDeal) {
    deals.push_back(subDeal);
}

// g)
Rechnung::Rechnung(const std::string& nameInit, const std::string& addressInit, std::shared_ptr<AbstrakterVertrag> dealInit) :
    name(nameInit), address(addressInit), deal(dealInit) {}
std::shared_ptr<AbstrakterVertrag> Rechnung::getVertrag() {
    return deal;
}
// Rechnungsbetrag: XXX.XX€
std::ostream& operator<< (std::ostream& s, const Rechnung& check) {
    return s << "Rechnungsbetrag: " << std::fixed << std::setprecision(2) << check.deal -> berechneKosten() << "€";
}