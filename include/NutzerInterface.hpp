#pragma once 
#include <iostream>
#include <list>
#include <string>
#include "Objekt.hpp"

using namespace std;
namespace ProjectGamma {

    class NutzerInterface{
        public:
            
            virtual bool verkauft(string Produkt, double Preis, int anzahl)=0;
            virtual bool gekauft(double Preis, string Produkt, int anzahl)=0;
            virtual double getGuthaben() const =0;
            virtual string getName() const = 0;
            
    };
}