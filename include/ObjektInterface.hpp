# pragma once 
#include <iostream>

using namespace std;
namespace ProjectGamma{

    class ObjektInterface{
        public:

            virtual std::string getProdukt() const=0;
            virtual double getPreis() const = 0;
            virtual string getSeller()=0;
            virtual void changeSeller(string Nutzer)=0;
            virtual void Preisanpassung() = 0;

    };
}