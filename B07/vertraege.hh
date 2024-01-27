#ifndef H_VERTRAEGE
#define H_VERTRAEGE

#include <cmath>
#include <vector>
#include <memory>
#include <string>

// a)
class AbstrakterVertrag {
    public:
        virtual double berechneKosten() const = 0;
        virtual void verbraucheTelefonEinheiten(double) = 0;
        virtual void verbraucheSMSEinheit() = 0;
};

// b)
class FlatrateVertrag : public AbstrakterVertrag {
    protected:
        double fixrate;
    public:
        FlatrateVertrag(double fixrateInit);
        
        virtual double berechneKosten() const;
        virtual void verbraucheTelefonEinheiten(double);
        virtual void verbraucheSMSEinheit();
};

// c)
class GrundgebuehrVertrag : public AbstrakterVertrag {
    protected:
        double fixedCharge;
        double callMinutes;
        int smsNum;
        double callPrise, smsPrise;
    public:
        GrundgebuehrVertrag(double fixedChargeInit, double callPriseInit, double smsPriseInit);
        
        virtual double berechneKosten() const;
        virtual void verbraucheTelefonEinheiten(double min);
        virtual void verbraucheSMSEinheit();
};
class OhneGrundgebuehrVertrag : public GrundgebuehrVertrag {
    public:
        OhneGrundgebuehrVertrag(double callPriseInit, double smsPriseInit);
};

// d)
class SekuendlicherVertrag: public GrundgebuehrVertrag {
    public:
        SekuendlicherVertrag(double fixedChargeInit, double callPriseInit, double smsPriseInit);
        virtual void verbraucheTelefonEinheiten(double min);
};

// e)
class GuthabenVertrag : public OhneGrundgebuehrVertrag {
    protected:
        //double balance = 0;
        double fixedCredit;
        //double check = 0;
    public:
        GuthabenVertrag(double callPriseInit, double smsPriseInit, double fixedCreditInit);
        virtual double berechneKosten() const;
};

// f)
class VertragsBundle : public AbstrakterVertrag {
    std::vector<std::shared_ptr<AbstrakterVertrag>> deals;
    std::shared_ptr<AbstrakterVertrag> mainDeal;
    public:
        VertragsBundle(std::shared_ptr<AbstrakterVertrag> mainDealInit);

        virtual double berechneKosten() const;
        virtual void verbraucheTelefonEinheiten(double);
        virtual void verbraucheSMSEinheit();

        std::shared_ptr<AbstrakterVertrag> get();
        std::shared_ptr<AbstrakterVertrag> get(unsigned int i);
        void vertragRegistrieren(std::shared_ptr<AbstrakterVertrag> subDeal);
};

// g)
class Rechnung {
    private:
        std::string name;
        std::string address;
        std::shared_ptr<AbstrakterVertrag> deal;
    public:
        Rechnung(const std::string& nameInit, const std::string& addressInit, std::shared_ptr<AbstrakterVertrag> dealInit);
        std::shared_ptr<AbstrakterVertrag> getVertrag();
        friend std::ostream& operator<< (std::ostream& s, const Rechnung& check);
};

#endif