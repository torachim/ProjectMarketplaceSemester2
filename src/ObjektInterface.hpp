# pragma once 
#include <iostream>

using namespace std;
namespace ProjectGamma{

    class ObjektInterface{
        public:
            virtual void Preisanpassung() = 0;
            virtual void get_Sache() = 0;
            virtual void get_Preis() = 0;
    };
}