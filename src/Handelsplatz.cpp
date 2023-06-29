#include <iostream>
#include <list>
#include <string>
#include <map>
#include "../include/Handelsplatz.hpp"
#include "../include/Objekt.hpp"
#include "../include/Nutzer.hpp"

using namespace std; 

namespace ProjectGamma{

        Handelsplatz::Handelsplatz(){

        }

        void Handelsplatz::login()
        {
            string Benutzername;
            string Passwort;
            cout << "Bitte einen gewünschten Benutzernamen eingeben" << endl;
            cin >> Benutzername;
            if (nameVergeben(Benutzername) == false) 
            {
                cout<< "Schon Vergeben. Wähle einen anderen Namen" <<endl;
                login();
            }
            else
            {
                cout << "Bitte Passwort eingeben" << endl;
                cin >> Passwort;
                bool t = false;
                while(t == false){
                    string Passwort2;
                    cout <<"Bitte Passwort wiederholen!" << endl;
                    cin >> Passwort2;
                    if(Passwort == Passwort2){
                        Information.insert(pair<string,string>(Benutzername, Passwort));
                        cout << "Account erfolgreich angelegt. Sie kehren zur Anmeldung zurueck!" << endl;
                        t = true;
                    }
                    else{
                        cout << "Passowert falsche! Bitte wiederholen" << endl;
                    }
                Information.insert(pair<string,string> (Benutzername, Passwort));
                einloggen();
                }
            }
        }

        void Handelsplatz::einloggen()
        {
            int n;
            cout << "Bitte logen sie sich ein oder krieieren sie einen neuen Account" << endl;
            cout << "Einloogen (1), Neuen Account machen (2)" << endl;
            cin >> n;
            if (n > 2 || n < 1){
                throw logic_error("Falsche Eingabe bitte erneut versuchen");
            }
            else{
                if(n == 1){
                    string Benutzername;
                    string Passwort;
                    cout << "Bitte Benutzername eingeben" << endl;
                    cin >> Benutzername;
                    if(findeBenutzer(Benutzername)){
                        bool t = false;
                        while (t == false){
                            cout << "Bitte Passwort eingeben" << endl;
                            cin >> Passwort;
                            if(Information.at(Benutzername) == Passwort){
                                cout << "Einloggen erfolgreich" << endl;
                                Nutzer k = Nutzer(Benutzername);
                                nu.n = k;
                                MarktNutzer.push_front(nu);
                                t = true;
                            }
                            else{
                                cout << "Passwort falsch Anmeldung fehlgeschlagen!" << endl;
                            }            
                        }
                    }
                    else{
                        throw logic_error("Benutzername Falsch oder nicht vorhanden. Bitte erneut versuchen");
                    }
                }
                else{
                    login();
                }
            }
        }
        

        bool Handelsplatz::nameVergeben (string Name)
        {
           for (auto it = MarktNutzer.begin(); it != MarktNutzer.end();) 
           {
                if (it -> n.getName() == Name) 
                {
                return false;
                } 
                else{
                    ++it;
                }
            }
            return true;
        }

        void Handelsplatz::showMarket() 
        {
            cout << "Marktangebot:" << endl;
            for (auto it = Markt.begin(); it != Markt.end();) 
            {
                cout << it -> o.getProdukt() << " - Preis: " << it -> o.getPreis() << endl;
                ++it;
            }
        }

        void Handelsplatz::showUsers() 
        {
            cout << "Nutzer auf dem Marktplatz:" << endl;
            for (auto it = MarktNutzer.begin(); it != MarktNutzer.end();)
            {
                cout << "Nutzer: " << it -> n.getName() << endl;
                ++it;
                
            }
        }   

        /*void Handelsplatz::addNutzer(string user) 
        {
            Nutzer.add(user);
        }*/

        void Handelsplatz::addProdukt(string Produkt, double Preis) 
        {
            Objekt no = Objekt (Produkt, Preis, "Markt");
            mo.o = no;
            Markt.push_front(mo);
        }

        bool Handelsplatz::findeBenutzer(string Benutzername)
        {
            for(const auto& [key, value]: Information){
                if(key == Benutzername){
                    return true;
                }
            }
            return false;
        }

        
}
