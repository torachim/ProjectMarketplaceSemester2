#pragma once
#include <iostream>

using namespace std;
namespace ProjectGamma{

    class HandelsplatzInterface{

        public:
            virtual void login() = 0;
            virtual void showMarket()= 0;
            virtual void showUsers()= 0;
            virtual void addProdukt(string Produkt, double Preis)=0;
            virtual void einloggen() = 0;
            virtual bool findeBenutzer(string Benutzername) = 0;
    
    };
}
