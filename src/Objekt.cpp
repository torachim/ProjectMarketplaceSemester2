#include <iostream>
#include <string>
#include "../include/Objekt.hpp"

using namespace std; 

namespace ProjectGamma{

    Objekt::Objekt(const std::string& produktName, double produktPreis,string produktSeller)
        {
            Produkt = produktName;
            Preis = produktPreis;
            Seller = produktSeller;
        }

    std::string Objekt::getProdukt()const
        {
            return Produkt;
        }

    double Objekt::getPreis() 
        {
            return Preis;
        }

    string Objekt::getSeller() 
        {
            return Seller;
        }

    void Objekt::changeSeller(string Nutzer)
        {
            Seller = Nutzer;
        }
    
}