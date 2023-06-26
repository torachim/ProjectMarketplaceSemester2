#pragma once 
#include <iostream>
#include <list>

using namespace std;
namespace ProjectGamma {

    class NutzerInterface{
        public:
            
            virtual void kaufen(const std::string& Objekt=0);
            virtual void verkaufen(string Produkt,bool ja)=0;
            virtual void verkauft(string Produkt, double Preis)=0;
            virtual void pay(double Preis, string Seller)=0;
            virtual bool available ( string Produkt)=0;
            virtual std::list<string> getMyList()=0;
            virtual double getGuthaben()=0;
            
    };
}