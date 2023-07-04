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

            struct objektenutzer{
                Objekt o = Objekt("NULL", 0, "NULL");   
            };
            objektenutzer om;

            string myName; // eigentlich erstellen bei Nutzer erstellen Funktion
            double Guthaben = 100.0; // wo anfangs Betrag festlegen
            list<objektenutzer> myObjects;
            map<string, int> Anzahl;
            map<string, int> VerkaufsAnzahl;

        public:

            Nutzer(const std::string& Name);
            void verkauft(string Produkt, double Preis, int anzahl);
            bool gekauft(double Preis, string Produkt, int anzahl);
            double getGuthaben() const;
            string getName() const;
            bool druckeObjekte() const;
            bool Objekteaussortieren(string Produkt, int anzahl);
            map<string, int> getVerkaufsAnzahl() const;
            bool produktzumverkauf(string produkt, int anzahl);
    };
};