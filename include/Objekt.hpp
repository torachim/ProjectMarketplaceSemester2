#pragma once
#include <iostream>
#include <list>
#include <string>
#include <random>
#include "ObjektInterface.hpp"


using namespace std;

namespace ProjectGamma{

    class Objekt : public ObjektInterface {

        private:

            double Preis;
            string Produkt;
            string Seller;
            double Tendenz = 0.3 * ((rand() % 10) - 1 ); //Tendenz durch zufall

        public:

            Objekt(const std::string& produktName, double produktPreis,string produktSeller);
            std::string getProdukt() const;  //gibt Produktnamen zurück
            double getPreis()const;          //gibt Preis zurück
            string getSeller();              // gibt Verkäufer zurück
            void changeSeller(string Nutzer); // passt Verkäufer an
            void Preisanpassung();             //berechnet neuen Wert für den Preis
            double getTendenz();              //bestimmt Tendenzwert


    };
}