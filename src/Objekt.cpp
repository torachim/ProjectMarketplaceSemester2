#include <iostream>
#include <string>
#include <random>
#include "../include/Objekt.hpp"

using namespace std; 

namespace ProjectGamma{

    Objekt::Objekt(const std::string& produktName, double produktPreis,string produktSeller) //Konstruktor Objekt, welches ein Namen, den Preis und den Verkäufer speichert
        {
            Produkt = produktName;
            Preis = produktPreis;
            Seller = produktSeller;
        }

    std::string Objekt::getProdukt()const //Funktion gibt Name des Produktes zurück
        {
            return Produkt;
        }

    double Objekt::getPreis()const  //Gibt den Preis des Produktes zurück
        {
            return Preis;
        }

    string Objekt::getSeller() //Gibt den Verkäufer des Produktes zurück
        {
            return Seller;
        }

    void Objekt::changeSeller(string Nutzer) //Nutzung zu Anpassung des Verkäufers nach einem Kauf
        {
            Seller = Nutzer; //Setzt Verkäufer des Produktes auf den Käufer
        }
    

    double Objekt::getTendenz()
        {
            return Tendenz; //gibt Tendenzen des Handelswertes zurück (0.3 * ((rand() % 10) - 1 ) )
        }
    
    void Objekt::Preisanpassung()
        {
            int Startpreis = getPreis(); //entnimmt den momentanen Preis des Produktes
            int min = 1; 
            int max = 10;
            double dt = 0.002; //??
            double Tend = getTendenz();
            int Y = 2*(rand() % max) - 1;
            Preis = Startpreis * (1.0 + Tend*dt + 0.8*sqrt(dt)*Y); //berechnet neuen Preis
        }
    
}