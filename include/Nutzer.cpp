#include <iostream>
#include<list>
using namespace std; 

namespace ProjectAlpha3{
class Nutzer{

    string myName;
    double Guthaben = 100.0; // wo anfangs Betrag festlegen
    std::list<string> myList;

    void kaufen(const std::string& Produkt)
    {
        //überprüfen on Produkt auf dem Markt

        double Preis = Produkt.getPreis();
        string Seller = Produkt.getSeller();

        if(Guthaben>= Preis)
        {
        myList.add(Produkt);
        pay(Preis, Seller);
        Seller.verkauft();
        verkaufen(Produkt);
        }
        else{
            cout<< "Geld reicht nicht aus" << endl;
        }
    }

    void verkaufen(string Produkt,bool ja)
    {
        bool Antwort;

        cout<< "Willst du" <<Produkt  << "weiterverkaufen? (1 für Ja oder 0 für Nein): "<<endl; // Bei Phyton erst nach Abfrage diese Funktion aufrufen
        cin>> Antwort;

        if( Antwort== 0){
            List.remove(Produkt);
        }
        else{
           Produkt.changeSeller(myName); 
        }
    }

    void verkauft(string Produkt, double Preis)
    {
        myList.remove(Produkt);
        Guthaben = Guthaben + Preis;
    }

    pay(double Preis, string Seller)
    {
        Guthaben= Guthaben - Preis;
        double sellerGuthaben =Seller.getGuthaben();
        Seller.setGuthaben(sellerGuthaben)
    }

    std::list<string> getMyList()
    {
        return myList;
    }

    double getGuthaben()
    {
        return Guthaben;
    }

    void setGuthaben(double neuesGuthaben)
    { 
        Guthaben = neuesGuthaben
    }

};
}