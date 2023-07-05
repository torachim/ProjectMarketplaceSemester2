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
         * @brief Funktion wird in der Handelsfunktion aufgerufen. Sie entfernt nac einem Kauf das Produkt vom Besitz des Käufers iund erhöht sein Guthaben entsprechend.
         * 
         * @param Produkt 
         * @param Preis 
         * @param anzahl 
         * @return true 
         * @return false 
         */
        bool Nutzer::verkauft(string Produkt, double Preis, int anzahl)
        {
            string name = Produkt;
            for(auto it = Anzahl.begin(); it != Anzahl.end();){                 //Entfernt die angebene Anzahl des Produktes, falls Produkt mehrfach vorhanden
                string m = it -> first;                                         
                if(m == name){                                                  // wenn Eingabe ist gespeichert 
                    if(Anzahl.at(m) - anzahl == 0){                              //Wenn alle Vorräte verkauft
                        for(auto ite = myObjects.begin(); ite != myObjects.end();){ //durchläuft meine Objekte
                            if(ite -> o.getProdukt() == name){
                                myObjects.erase(ite);
                                Guthaben = Guthaben + (Preis * anzahl);
                                Anzahl.erase(it); 
                                return true;  
                            }
                            else{
                                ++it;                                              //itertor erhöhene
                            }
                        }
                     
                    }
                    else{
                        int newvalue = Anzahl.at(it -> first) - anzahl;
                        Guthaben = Guthaben + (Preis * anzahl);
                        Anzahl[it -> first] = newvalue;
                        return true;
                    }
                }
                else{
                    ++it;
                }
            }
            return true;
 
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
         * @brief Die Funktion druckt die einzelen Objekte einses Nutzer mit entsprechender Anzahl
         * 
         * @return true 
         * @return false 
         */
        bool Nutzer::druckeObjekte() const{
            if(myObjects.size() == 1){
                myObjects.front().o.getProdukt();
                int wert = Anzahl.at(myObjects.front().o.getProdukt());
                cout << "Produkt: " << myObjects.front().o.getProdukt() << "Anzahl: " << wert << endl;
            }
            else{
                //for(auto it = myObjects.begin(); it != myObjects.end();){
                  //  string name = it -> o.getProdukt();
                    for(auto ite = Anzahl.begin(); ite != Anzahl.end();){
                        string k = ite -> first;
                        //if(k == name){
                        int wert = Anzahl.at(k);
                        cout << "Produkt: " << k << " Anzahl: " << wert << endl;
                    
                        ++ite;
                    }
                }
            return true;
            }    

        /**
         * @brief Funktion ermöglicht Produkte im eigenen Besitz zum Verkauf freizustellen.
         * 
         * @param Produkt 
         * @param anzahl 
         * @return true 
         * @return false 
         */
        bool Nutzer::Objekteaussortieren(string Produkt, int anzahl){
            cout << myObjects.size() << endl;              
            cout << Anzahl.size() << endl;
            for(auto it = Anzahl.begin(); it != Anzahl.end();){
                string objname = it -> first;
                if(objname == Produkt){

                    int q = Anzahl.at(objname);
                    if(anzahl <= q && anzahl > 0){

                        VerkaufsAnzahl.insert(pair <string, int> (Produkt, anzahl));
                        return true; 
                    }
                    else{
                        cout << "Unpassende Anzahl an Objekten ausgewählt" << endl;
                        return false;
                    }
                }
                else{
                    ++it;
                }
            }
            cout << "Objekt konnte nicht gefunden weerden" << endl;
            return false;          
        }

        /**
         * @brief Funktion gibt die Anzahl zu Verkauf stehende Ware eines Produktes wieder
         * 
         * @return map<string, int> 
         */
        map<string, int> Nutzer::getVerkaufsAnzahl() const{
            return VerkaufsAnzahl;
        }

        /**
         * @brief Funktion fügt Produkt eines Nutzers zum Markt zu.
         * 
         * @param Produkt 
         * @param anzahl 
         * @return true 
         * @return false 
         */
        bool Nutzer::produktzumverkauf(string Produkt, int anzahl){
            VerkaufsAnzahl.insert(pair<string, int> (Produkt, anzahl));
            return true;
        }
<<<<<<< HEAD
}              
            
=======
                
}   
>>>>>>> e73c3570e6d9c26005a9bc85cb71869be0a5a299
        


                                        