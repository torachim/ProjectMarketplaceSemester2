#pragma once
#include <iostream>
#include <list>
#include <string>
#include "ObjektInterface.hpp"


using namespace std;

namespace ProjectGamma{

    class Objekt : public ObjektInterface {

        private:

            float Preis;
            string Produkt;
            string Seller;

        public:

            Objekt(const std::string& produktName, double produktPreis,string produktSeller);
            std::string getProdukt() const;
            double getPreis();
            string getSeller();
            void changeSeller(string Nutzer);


    };
}