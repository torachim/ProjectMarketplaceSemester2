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
            double Tendenz = 0.3 * (rand() % 100);

        public:

            Objekt(const std::string& produktName, double produktPreis,string produktSeller);
            std::string getProdukt() const;
            double getPreis()const;
            string getSeller();
            void changeSeller(string Nutzer);
            void Preisanpassung();
            double getTendenz();


    };
}