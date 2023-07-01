#include <iostream>
#include "../include/Handelsplatz.hpp"
//#include "../include/Nutzer.hpp"

using namespace std;

using namespace ProjectGamma;

    int main()
    {
        Handelsplatz HP;
        HP.addProdukt("Mars", 15.5);
        HP.addProdukt("Saturn", 12.5);
        HP.addProdukt("Neptun", 20.4);
        HP.einloggen();
        HP.showMarket();
        HP.Preisanpassung();
        HP.showMarket();
        HP.Preisanpassung();
        HP.showMarket();
        return 0;
    }
