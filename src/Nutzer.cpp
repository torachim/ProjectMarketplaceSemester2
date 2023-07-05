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


        bool Nutzer::verkauft(string Produkt, double Preis, int anzahl)
        {
            string name = Produkt;
            for(auto it = Anzahl.begin(); it != Anzahl.end();){
                string m = it -> first;
                if(m == name){
                    if(Anzahl.at(m) - anzahl == 0){
                        for(auto ite = myObjects.begin(); ite != myObjects.end();){
                            if(ite -> o.getProdukt() == name){
                                myObjects.erase(ite);
                                Guthaben = Guthaben + (Preis * anzahl);
                                Anzahl.erase(it); 
                                return true;  
                            }
                            else{
                                ++it;
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

        map<string, int> Nutzer::getVerkaufsAnzahl() const{
            return VerkaufsAnzahl;
        }

        bool Nutzer::produktzumverkauf(string Produkt, int anzahl){
            VerkaufsAnzahl.insert(pair<string, int> (Produkt, anzahl));
            return true;
        }
                
            
        


}