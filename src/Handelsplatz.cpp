#include <iostream>
#include <list>
#include <string>
#include "../include/Handelsplatz.hpp"
#include "../include/Objekt.hpp"
#include "../include/Nutzer.hpp"

using namespace std; 

namespace ProjectGamma{

        void Handelsplatz::createNutzer(string Name,int Passwort)
        {
            for (const auto& Nutzer : MarktNutzer) 
            {
            if (nameVergeben(Name)== false) 
            {
                cout<<"Schon Vergeben. Wähle einen anderen Namen"<<endl;
                createNutzer(string Name);
            }
            else
            {
                Nutzer(Name,Passwort);
                Markt.add(Name);
            }
            }
        }

        bool einlogen(string Name, int Passwort)
        {
            int passwort= Nutzer.getPasswort();
            If(passwort==Passwort){
                return true;
            }
            else
            {
                return false;
            }
        }

        bool Handelsplatz::nameVergeben(string Name)
        {
           for (const auto& Nutzer : MarktNutzer) 
           {
                if (Nutzer == Name) 
                {
                return false;
                } 
            }
        }

        void Handelsplatz::showMarket() 
        {
            cout << "Marktangebot:" << endl;
            for (const auto& Objekte : Markt) 
            {
                cout << Objekte.getProdukt() << " - Preis: " << Objekte.getPreis() << endl;
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
