#pragma once
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <vector>
#include "HandelsplatzInterface.hpp"
#include "Objekt.hpp"
#include "Nutzer.hpp"



using namespace std;

namespace ProjectGamma{

class Handelsplatz : public HandelsplatzInterface {



    public:

        void login();
        void einloggen();
        void showMarket();
        void showUsers();
        void addNutzer(string user);
        void addProdukt(string Produkt, double Preis);
        //void createNutzer(string Name, int Passwort);
        bool nameVergeben(string Name);
        bool findeBenutzer(string Benutzername);

    private:
        std::list<Objekt> Markt;
        std::list<Nutzer> MarktNutzer;
        std::map<string, string> Information;


   };
}