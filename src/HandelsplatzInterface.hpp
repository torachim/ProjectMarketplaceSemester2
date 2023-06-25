#pragma once
#include <iostream>

using namespace std;
namespace ProjectGamma{

    class HandelsplatzInterface{

        public:
            virtual void login() = 0;
            virtual void listeanpassen(string ObjektName, bool zustand) = 0;
    };
}
