#pragma once 
#include <iostream>
#include <list>
#include "Objekt.hpp"

using namespace std;
namespace ProjectGamma {

    class NutzerInterface{
        public:
            
            virtual void verkauft(Objekt Produkt, double Preis, int anzahl)=0;
            virtual bool gekauft(double Preis, Objekt Produkt, int anzahl)=0;
            virtual double getGuthaben() const =0;
            virtual string getName() const = 0;
            
    };
}