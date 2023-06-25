#include <iostream>
#include<list>
#include "../include/Handelsplatz.hpp"
#include "../include/Objekt.hpp"

using namespace std; 

namespace ProjectGamma{

        //einloggen Funktion
        //Nutzer erstellen Funktion

        void Handelspaltz::showMarket() 
        {
            cout << "Marktangebot:" << endl;
            for (const auto& Objekte : Markt) 
            {
                cout << Objekt.getProdukt() << " - Preis: " << Objekt.getPreis() << endl;
            }
        }

        void Handelspaltz::showUsers() 
        {
            cout << "Nutzer auf dem Marktplatz:" << endl;
            for (const auto& user : nutzer) {
                cout << user.getName() << " - Kontostand: " << user.getKontostand() << endl;
            }
        }

        void Handelspaltz::addNutzer(string user) 
        {
            Nutzer.add(user);
        }

        void Handelspaltz::addProdukt(string Produkt, double Preis) 
        {
            Markt.add(Produkt);
            Objekt (Produkt, Preis, "Markt");

        }

        
}
