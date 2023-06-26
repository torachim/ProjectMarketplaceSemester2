#include <iostream>
#include <list>
#include <string>
#include "../include/Nutzer.hpp"
#include "../include/Handelsplatz.hpp"
#include "../include/Objekt.hpp"

using namespace std; 
namespace ProjectGamma{


        Nutzer::Nutzer(const std::string& Name)
        {
         myName = Name;
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
                cout<< "Produkt wird nicht verkauft" << endl;
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
            myObjects.remove(Produkt);
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

        std::list<Objekt> Nutzer::getMyList()
        {
            return myObjects;
        }

        double Nutzer::getGuthaben() const
        {
            return Guthaben;
        }

        string Nutzer::getName() const
        {
            return myName;
        }

        void Nutzer::druckeObjekte() const{
            for(const Objekt& Obj : myObjects){
                string name = Obj.getProdukt();
                for(const auto& [key, value] : Anzahl){
                    if(key.getProdukt() == name){
                        cout << "Produkt: " << name << "Anzahl: " << value << endl;
                    }
                }
            }
        }

        void Nutzer::Objekteaussortieren(){
            int n;
            cout << "Moechtest du Objekte aussortieren um diese zum verkauf bereitzustellen? Ja(1), Nein(2)" << endl;
            cin >> n;
            if(n > 2 || 1 > n){
                throw logic_error("Falsche Eingabe bitte erneut versuchen");
            }
            else{
                if(n == 1){
                    bool r = false;
                    while(r == false){
                        druckeObjekte();
                        string Verkauf;
                        cout << "Welches der Objekte möchtest du verkaufen?" << endl;
                        cin >> Verkauf;
                        for(const auto& [key, value] : Anzahl){
                            if(key.getProdukt() == Verkauf){
                                cout << "Wie viele dieser Objekte möchtest du zum Verkauf bereitstellen?" << endl;
                                int k;
                                cin >> k;
                                if(k <= value || k > 0){
                                    VerkaufsObjekte.push_front(key);
                                    AnzahlVerkauf.push_front(k);
                                    cout << "Moechtest du noch mehr Objekte zum Verkauf bereit stellen? Ja(1), Nein(2)" >> endl;
                                    int p;
                                    cin >> p;
                                    if(p == 2){
                                        r = true;
                                    }    
                                }
                                else{
                                    cout << "Unpassende Anzahl an Objekten ausgewählt" << endl;
                                }
                            }
                            else{
                                cout << "Falsche Eingabe. Objekt konnte nicht gefunden werden!" << endl;
                            }
                        }
                    }
                }
            }
        }        
}