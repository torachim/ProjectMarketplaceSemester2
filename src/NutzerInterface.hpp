#pragma once 
#include <iostream>

using namespace std;
namespace ProjectGamma {

    class Nutzerinterface{
        public:
            virtual void einkaufen() = 0;
            virtual void verkaufen() = 0;
            virtual void get_geld() = 0;
            virtual void Warenueberblich() = 0;
    };
}