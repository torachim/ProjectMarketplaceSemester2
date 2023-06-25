#pragma once
#include <iostream>
#include<list>
#include "Handelsplatz.hpp"
#include "Objekt.hpp"
#include "NutzerInterface.hpp"


using namespace std;

namespace ProjectGamma{

    class Nutzer : public NutzerInterface {

        priavte:

            string myName; // eigentlich erstellen bei Nutzer erstellen Funktion
            double Guthaben = 100.0; // wo anfangs Betrag festlegen
            std::list<string> myList;

        public:

            void kaufen(const std::string& Objekt);
            void verkaufen(string Produkt,bool ja);
            void verkauft(string Produkt, double Preis);
            void pay(double Preis, string Seller);
            bool available ( string Produkt);
            std::list<string> getMyList();
            double getGuthaben();
    };
}