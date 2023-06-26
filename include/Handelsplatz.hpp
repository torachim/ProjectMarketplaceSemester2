#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "HandelsplatzInterface.hpp"



using namespace std;

namespace ProjectGamma{

class Handelsplatz : public HandelsplatzInterface {



    public:

        void login();
        void showMarket();
        void showUsers();
        void addNutzer(string user);
        void addProdukt(string Produkt, double Preis);
        void createNutzer(string Name, int Passwort);
        bool nameVergeben(string Name);

    private:
        std::list<string> Markt;
        std::list<string> MarktNutzer;


   };
}