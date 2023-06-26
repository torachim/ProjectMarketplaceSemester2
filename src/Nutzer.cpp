#include <iostream>
#include <list>
#include <string>
#include "../include/Nutzer.hpp"
#include "../include/Handelsplatz.hpp"
#include "../include/Objekt.hpp"

using namespace std; 

namespace ProjectGamma{


        Nutzer::Nutzer(const std::string& Name, int Passwort)
        {
         const std::string& myName= Name;
         int Passwort= Passwort
        }

        int Nutzer::getPasswort()
        {
            return Passwort;
        }

        void Nutzer::kaufen(const std::string& Objekt) 
        {   
            string Produkt = Objekt.getProdukt();
            bool a = available(Produkt);
            if ( a == true)
            {
    
                double Preis = Produkt.getPreis();
                string Seller = Produkt.getSeller();

                if(Guthaben>= Preis)
                {
                myList.add(Produkt);   // zu meiner Liste hinzufügen
                pay(Preis, Seller);    // Bezahlen
                Seller.verkauft();     // BezahlenSeller und entferen von der SellerListe
                verkaufen(Produkt);    // Abfrage ob Produkt weiter verkauft werden soll
                }
                else{
                    cout<< "Geld reicht nicht aus" << endl;
                }
            }
            else
            {
                cout<< "Produkt wird nicht verkauft" endl;
            }
        }

        void Nutzer::verkaufen(string Produkt,bool ja)
        {
            bool Antwort;

            //cout<< "Willst du" <<Produkt  << "weiterverkaufen? (1 für Ja oder 0 für Nein): "<<endl; // Bei Phyton erst nach Abfrage diese Funktion aufrufen
            //cin>> Antwort;

            if( Antwort== 0)
            {
                Markt.remove(Produkt);  // Produkt für Eigenbedarf wird vom Markt gelöscht
            }
            else
            {
            Produkt.changeSeller(myName); // Produkt wird vom Nutzer weiterverkauft
            }
        }

        void Nutzer::verkauft(string Produkt, double Preis)
        {
            myList.remove(Produkt);
            Guthaben = Guthaben + Preis;
        }

        void Nutzer::pay(double Preis, string Seller)
        {
            Guthaben= Guthaben - Preis;
        }

        bool Nutzer::available ( string Produkt){

            for (const auto& Objekt : Markt) {
            if (Objekt == Produkt) {
                return true;
            }
            else{ 
                return false;
            }
            }
        }

        std::list<string> Nutzer::getMyList()
        {
            return myList;
        }

        double getGuthaben()
        {
            return Guthaben;
        }

        
    
}