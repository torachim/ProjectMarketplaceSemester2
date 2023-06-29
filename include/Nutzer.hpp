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
            list<objektenutzer>VerkaufsObjekte;
            list<int>AnzahlVerkauf;

        public:

            Nutzer(const std::string& Name);
            void verkauft(Objekt Produkt, double Preis, int anzahl);
            bool gekauft(double Preis, Objekt Produkt, int anzahl);
            double getGuthaben() const;
            string getName() const;
            void druckeObjekte() const;
            void Objekteaussortieren();
    };
};