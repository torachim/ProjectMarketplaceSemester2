#pragma once
#include <iostream>
#include <list>
#include <string>
#include "NutzerInterface.hpp"
#include "Objekt.hpp"
#include <map>


using namespace std;

namespace ProjectGamma{

    class Nutzer : public NutzerInterface {

        private:

            string myName; // eigentlich erstellen bei Nutzer erstellen Funktion
            double Guthaben = 100.0; // wo anfangs Betrag festlegen
            std::list<Objekt> myObjects;
            map<Objekt, int> Anzahl;
            list<Objekt>VerkaufsObjekte;
            list<int>AnzahlVerkauf;

        public:

            Nutzer(const std::string& Name);
            int getPasswort();
            void kaufen(const std::string& Objekt);
            void verkaufen(string Produkt,bool ja);
            void verkauft(string Produkt, double Preis);
            void pay(double Preis, string Seller);
            bool available ( string Produkt);
            std::list<Objekt> getMyList();
            double getGuthaben() const;
            string getName() const;
            void druckeObjekte() const;
            void Objekteaussortieren();
    };
}