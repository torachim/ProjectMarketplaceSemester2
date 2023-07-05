#include <iostream>
#include <list>
#include <string>
#include <map>
#include "../include/Nutzer.hpp"


using namespace std; 
namespace ProjectGamma{

        Nutzer::Nutzer(const std::string& Name)             //gibt Name des Nutzer zurück
        {
         myName = Name;
        }

        /**
         * @brief Funktion wird in der Handelfunktion aufgerufen. Diese Funktion sorgt dafür, dass das Produkt vom Käufer entfernt wird und das Geld übertragen wird.
         * 
         * @param Produkt 
         * @param Preis 
         * @param anzahl 
         */
        void Nutzer::verkauft(string Produkt, double Preis, int anzahl)
        {
            string name = Produkt;
            for(auto it = Anzahl.begin(); it != Anzahl.end();){                 //Entfernt die angebene Anzahl des Produktes, falls Produkt mehrfach vorhanden
                string m = it -> first;                                         
                if(m == name){                                                  // wenn Eingabe ist gespeichert 
                    if(Anzahl.at(m) - anzahl == 0){                              //Wenn alle Vorräte verkauft
                        for(auto ite = myObjects.begin(); ite != myObjects.end();){ //durchläuft meine Objekte
                            if(ite -> o.getProdukt() == name){
                                myObjects.erase(ite);                               //entfernt item von meinen Produkten
                            }
                            else{
                                ++it;                                              //itertor erhöhene
                            }
                        }
                        Anzahl.erase(it);                        
                    }
                    else{
                        int newvalue = Anzahl.at(it -> first) - anzahl;          //vorhanden Anzahl des Produktes anpassen
                        Anzahl[it -> first] = newvalue;
                    }
                }
                else{
                    ++it;
                }
            }
            Guthaben = Guthaben + (Preis * anzahl);                              //Anpassung Guthaben des Verkäufers
        }
            
        /**
         * @brief Funktion wird in der Handelfunktion aufgerufen. Diese Funktion fügt das Produkt zu den Objekten des Käufers hinz, zudem wird das Guthaben des käufers entsprechend angepasst.
         * 
         * @param Preis 
         * @param Produkt 
         * @param anzahl 
         * @return true 
         * @return false 
         */
        bool Nutzer::gekauft(double Preis, string Produkt, int anzahl)          //Anpass Funktionn für den Käufer
        {
            Guthaben = Guthaben - (Preis);                                      //Anpassung des Kontostandes
            string name = Produkt;
            string neuerverkäufer = getName();
            Objekt no = Objekt (Produkt, Preis, neuerverkäufer);                //Anpassung des Verkäufers
            om.o = no;
            for(auto it = myObjects.begin(); it != myObjects.end();){
                if(it -> o.getProdukt() == name){
                    Anzahl.at(name) = Anzahl.at(name) + anzahl;                //Anzahl des Produktes wird gespeichert
                    return true;

                }
                else{
                    ++it;
                }  

                }
            myObjects.push_front(om);                                           //speichern in map für meine Objekte
            Anzahl.insert(pair<string,int>(name, anzahl));                       
            return true;
        }
        

        /**
         * @brief Funktion gibt den Guthaben eines Nutzers zurück.
         * 
         * @return double 
         */
        double Nutzer::getGuthaben() const  //gibt Guthaben des Nutzers zurück
        {
            return Guthaben;
        }


        /**
         * @brief Funktion gibt den Namen eines Nutzers zurück.
         * 
         * @return string 
         */
        string Nutzer::getName() const   //gibt Namen des Nutzers zurück
        {
            return myName;
        }

        /**
         * @brief Funktion druckt alle Produkte eines Nutzers und deren zugehörige Anzahl aus.
         * 
         */
        void Nutzer::druckeObjekte() const{  //druckt die eigenen Objekte aus
            for(auto it = myObjects.begin(); it != myObjects.end();){  //durchläuft alle Objekte
                string name = it -> o.getProdukt();  //entnimmt Produkt Namen
                for(auto ite = Anzahl.begin(); ite != Anzahl.end();){ //durchläuft Anzahl 
                    string k = ite -> first;
                    if(k == name){     //bestimmt passende Anzahl zum Produkt
                        int wert = Anzahl.at(k);
                        cout << "Produkt: " << name << "Anzahl: " << wert << endl;  //gibt produkt und passende Anzahl zurück                   
                    }
                    else{
                        ++ite;
                    }
                }
                ++it;
            }
        }

        /**
         * @brief Funktion ermöglicht seine Produkte aauf demm Markt zu verkauf bereitszustellen.
         * 
         */
        void Nutzer::Objekteaussortieren(){ //bestimmt ob Produkt weiterverkauft wird oder nicht
            int n;
            cout << "Moechtest du Objekte aussortieren um diese zum verkauf bereitzustellen? Ja(1), Nein(2)" << endl; //abfrage, ob weiterverkauft wird oder nicht
            cin >> n;
            if(n > 2 || 1 > n){
                throw logic_error("Falsche Eingabe bitte erneut versuchen"); //Ausnahmebehandlung bei falscher Eingabe
            }
            else{
                if(n == 1){   //falls weiterverkauft werden soll      
                    bool r = false;
                    while(r == false){
                        druckeObjekte(); //ausgabe der eigenen Produkten
                        string Verkauf;
                        cout << "Welches der Objekte möchtest du verkaufen?" << endl; //auswahl des Produktes
                        cin >> Verkauf;
                        for(auto it = Anzahl.begin(); it != Anzahl.end();){ 
                            string objname = it -> first;
                            if(objname == Verkauf){  // aus map der iegen Produkte entfrenen
                                cout << "Wie viele dieser Objekte möchtest du zum Verkauf bereitstellen?" << endl; //anzahl bestimmen
                                int k;
                                cin >> k;
                                int q = Anzahl.at(objname);
                                if(k <= q|| k > 0){ //für die Anzahl
                                    //VerkaufsObjekte.push_front(oj);
                                    VerkaufsAnzahl.insert(pair <string, int> (Verkauf, k)); //Produkt wird zum verkauf bereitgestellt
                                    cout << "Moechtest du noch mehr Objekte zum Verkauf bereit stellen? Ja(1), Nein(2)" << endl; 
                                    int p;
                                    cin >> p;
                                    if(p == 2){ //falls nicht weitere Produkte verkauft werden 
                                        r = true;
                                    }    
                                }
                                else{
                                    cout << "Unpassende Anzahl an Objekten ausgewählt" << endl; // falls zu hohe odrer niedrige Anzahl gewählt
                                }
                            }
                            else{
                                ++it;
                            }
                        }
                        cout << "Objekt konnte nicht gefunden werden" << endl; //falls man diese Produkt nicht besitzt
                    }
                }
               } 
            }
}


                                        
