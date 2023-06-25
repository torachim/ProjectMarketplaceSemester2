#pragma once
#include <iostream>
#include<list>
#include "HandelsplatzInterface.hpp"
#include "Objekt.hpp"




using namespace std;

namespace ProjectGamma{

class Handelsplatz : public HandelsplatzInterface {

    private:
        std::list<string> Markt;
        std::list>string> Nutzer;

    public:

        void login();
        void showMarket();
        void showUsers();
        void addNutzer(string user);
        void addProdukt(string Produkt, double Preis);


   };
}