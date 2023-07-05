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

            string myName; // gibt Namen zurück
            double Guthaben = 100.0; // anfangsbetrag festlegen
            list<objektenutzer> myObjects; //liste mit den Objekten eines Nutzers
            map<string, int> Anzahl;     //speichert Anzahl der produkte
            map<string, int> VerkaufsAnzahl; //speichert Produkte zum Verkauf

        public:

            Nutzer(const std::string& Name);
            bool verkauft(string Produkt, double Preis, int anzahl);
            bool gekauft(double Preis, string Produkt, int anzahl);
            double getGuthaben() const;
            string getName() const;
            bool druckeObjekte() const;
            bool Objekteaussortieren(string Produkt, int anzahl);
            map<string, int> getVerkaufsAnzahl() const;
            bool produktzumverkauf(string produkt, int anzahl);
    };
};