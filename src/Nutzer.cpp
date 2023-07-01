#include <iostream>
#include <list>
#include <string>
#include <map>
#include "../include/Nutzer.hpp"


using namespace std; 
namespace ProjectGamma{


        Nutzer::Nutzer(const std::string& Name)
        {
         myName = Name;
        }

        /*void Nutzer::kaufen(const std::string& Objekt) 
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
        }*/

        /*void Nutzer::verkaufen(string Produkt,bool ja)
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
        }*/

        void Nutzer::verkauft(string Produkt, double Preis, int anzahl)
        {
            string name = Produkt;
            for(auto it = Anzahl.begin(); it != Anzahl.end();){
                string m = it -> first;
                if(m == name){
                    if(Anzahl.at(m) - anzahl == 0){
                        for(auto ite = myObjects.begin(); ite != myObjects.end();){
                            if(ite -> o.getProdukt() == name){
                                myObjects.erase(ite);
                            }
                            else{
                                ++it;
                            }
                        }
                        Anzahl.erase(it);                        
                    }
                    else{
                        int newvalue = Anzahl.at(it -> first) - anzahl;
                        Anzahl[it -> first] = newvalue;
                    }
                }
                else{
                    ++it;
                }
            }
            Guthaben = Guthaben + (Preis * anzahl);
        }
            

        bool Nutzer::gekauft(double Preis, string Produkt, int anzahl)
        {
            Guthaben = Guthaben - (Preis);
            string name = Produkt;
            string neuerverkäufer = getName();
            Objekt no = Objekt (Produkt, Preis, neuerverkäufer);
            om.o = no;
            for(auto it = myObjects.begin(); it != myObjects.end();){
                if(it -> o.getProdukt() == name){
                    Anzahl.at(name) = Anzahl.at(name) + anzahl;
                    return true;

                }
                else{
                    ++it;
                }  

                }
            myObjects.push_front(om);
            Anzahl.insert(pair<string,int>(name, anzahl));
            return true;
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
            for(auto it = myObjects.begin(); it != myObjects.end();){
                string name = it -> o.getProdukt();
                for(auto ite = Anzahl.begin(); ite != Anzahl.end();){
                    string k = ite -> first;
                    if(k == name){
                        int wert = Anzahl.at(k);
                        cout << "Produkt: " << name << "Anzahl: " << wert << endl;
                    }
                    else{
                        ++ite;
                    }
                }
                ++it;
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
                        for(auto it = Anzahl.begin(); it != Anzahl.end();){
                            string objname = it -> first;
                            if(objname == Verkauf){
                                cout << "Wie viele dieser Objekte möchtest du zum Verkauf bereitstellen?" << endl;
                                int k;
                                cin >> k;
                                int q = Anzahl.at(objname);
                                if(k <= q|| k > 0){
                                    //VerkaufsObjekte.push_front(oj);
                                    VerkaufsAnzahl.insert(pair <string, int> (Verkauf, k));
                                    cout << "Moechtest du noch mehr Objekte zum Verkauf bereit stellen? Ja(1), Nein(2)" << endl;
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
                                ++it;
                            }
                        }
                        cout << "Objekt konnte nicht gefunden weerden" << endl;
                    }
                }
            }
        }


}