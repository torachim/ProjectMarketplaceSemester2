#include <iostream>
#include <string>
#include <random>
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

    double Objekt::getPreis()const 
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
    

    double Objekt::getTendenz()
        {
            return Tendenz;
        }
    
    void Objekt::Preisanpassung()
        {
            int Startpreis = getPreis();
            int min = 1;
            int max = 10;
            double dt = 0.002; 
            double Tend = getTendenz();
            int Y = 2*(rand() % max) - 1;
            Preis = Startpreis * (1.0 + Tend*dt + 0.8*sqrt(dt)*Y);
        }
    
}