#pragma once
#include <iostream>
#include <list>
#include <string>
#include "HandelsplatzInterface.hpp"
#include "Objekt.hpp"
#include "Nutzer.hpp"


using namespace std;

namespace ProjectGamma{

class Handelsplatz : public HandelsplatzInterface {

    private:
        std::list<string> Markt;
        std::list<string> MarktNutzer;

    public:

        void login();
        void showMarket();
        void showUsers();
        void addNutzer(string user);
        void addProdukt(string Produkt, double Preis);


   };
}