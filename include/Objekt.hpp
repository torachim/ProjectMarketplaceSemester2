#pragma once
#include <iostream>
#include<list>
#include "ObjektInterface.hpp"


using namespace std;

namespace ProjectGamma{

    class Objekt : public ObjektInterface {

        private:

            float Preis;
            string Produkt;
            string Seller;

        public:

            std::string getProdukt() const;
            double getPreis();
            string getSeller();
            void changeSeller(string Nutzer);


    };
}