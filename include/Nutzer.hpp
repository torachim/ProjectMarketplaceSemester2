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
            std::list<objektenutzer> myObjects;
            map<objektenutzer, int> Anzahl;
            list<objektenutzer>VerkaufsObjekte;
            list<int>AnzahlVerkauf;

        public:

            Nutzer(const std::string& Name);
            void kaufen(const std::string& Objekt);
            void verkaufen(string Produkt,bool ja);
            void verkauft(Objekt Produkt, double Preis, int anzahl);
            bool gekauft(double Preis, Objekt Produkt, int anzahl);
            bool available ( string Produkt);
            double getGuthaben() const;
            string getName() const;
            void druckeObjekte() const;
            void Objekteaussortieren();
    };
};