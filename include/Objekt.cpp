#include <iostream>
using namespace std; 

namespace ProjectAlpha3{
class objekt{

private:
    float Preis;
    string Produkt;
    string Seller;

public:
    void menu();



Produkt(const std::string& produktName, double produktPreis,string produktSeller)
    {
        Produkt = produktName;
        Preis = produktPreis;
        Seller = produktSeller;
    }

    std::string getProdukt() const {
        return Produkt;
    }

    double getPreis() {
        return Preis;
    }
    String getSeller() {
        return Seller;
    }

    void changeSeller(string Nutzer){
        Seller = Nutzer:
    }
 };
}