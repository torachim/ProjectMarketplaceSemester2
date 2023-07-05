#include <iostream>
#include <list>
#include <string>
#include <map>
#include "../include/Handelsplatz.hpp"


using namespace std; 

namespace ProjectGamma{

    Handelsplatz::Handelsplatz(){

        }
    /**
     * @brief Diese Funktion ermöglicht das erstellen eines eigenes Kontos, durch Eingabe von einem username und eines Passwortes.
     * 
     */
    void Handelsplatz::login()
        {
            string Benutzername;
            string Passwort;
            cout << "Bitte einen gewünschten Benutzernamen eingeben" << endl;
            cin >> Benutzername;
            if (nameVergeben(Benutzername) == false) //testet ob Name schon benutzt
            {
                cout<< "Schon Vergeben. Wähle einen anderen Namen" <<endl;
                login(); //dann nochmal versuchen
            }
            else
            {
                cout << "Bitte Passwort eingeben" << endl;
                cin >> Passwort;
                bool t = false; //da nur einmal eingegeben
                while(t == false){ //wiedreholen Passwort 2x oder bei vertippen
                    string Passwort2;
                    cout <<"Bitte Passwort wiederholen!" << endl;
                    cin >> Passwort2;
                    if(Passwort == Passwort2){ //testet, ob selbes Passwort eingegeben wurde
                        Information.insert(pair<string,string>(Benutzername, Passwort)); //Hinzuügen zur Kontosammlung
                        cout << "Account erfolgreich angelegt. Sie kehren zur Anmeldung zurueck!" << endl;
                        t = true; // Passwort 2x erfolgreich eingegeben
                    }
                    else{
                        cout << "Passowert falsche! Bitte wiederholen" << endl; //wiedreholen
                    }
                Information.insert(pair<string,string> (Benutzername, Passwort));
                einloggen(); //weiterleiten zur Anmeldung 
                }
            }
        }
     
        /**
         * @brief Funktion leitet entweder zur login funktion oder zur Anmeldung bei einem vorhanden Konto. Abgefragt wird der Bneutzername und das Passwort.
         * 
         */
        void Handelsplatz::einloggen()
        {
            int n;
            cout << "Bitte logen sie sich ein oder krieieren sie einen neuen Account" << endl;
            cout << "Einloogen (1), Neuen Account machen (2)" << endl; //auswahl für Acc erstellen oder einloggen
            cin >> n;
            if (n > 2 || n < 1){
                throw logic_error("Falsche Eingabe bitte erneut versuchen"); //Ausnahmebehandlung bei falscher Eingabe
            }
            else{
                if(n == 1){
                    string Benutzername;
                    string Passwort;
                    cout << "Bitte Benutzername eingeben" << endl;
                    cin >> Benutzername;
                    if(findeBenutzer(Benutzername)){  // falls dieser Benutzer existiert
                        bool t = false;
                        while (t == false){
                            cout << "Bitte Passwort eingeben" << endl;
                            cin >> Passwort;
                            if(Information.at(Benutzername) == Passwort){ //falls das Passwort richtig ist
                                cout << "Einloggen erfolgreich" << endl;
                                Nutzer k = Nutzer(Benutzername);  //auf diesen Benutzer schalten
                                nu.n = k;
                                MarktNutzer.push_front(nu); //Aktualiseren Benutzerstand auf dem Markt
                                t = true;
                            }
                            else{
                                cout << "Passwort falsch Anmeldung fehlgeschlagen!" << endl; //falls Passwort falsch, Zugriff voerst nicht möglich
                            }            
                        }
                    }
                    else{
                        throw logic_error("Benutzername Falsch oder nicht vorhanden. Bitte erneut versuchen");  //Fehlermeldung bei falscher Benutzereingabe
                    }
                }
                else{
                    login(); // falls noch kein Acc existiert
                }
            }
        }
        
        /**
         * @brief Funktion überprüft, ob bei erstellen eines Kontos der Benutzername bereits vergeben ist. Falls dies der Fall ist wird false zurückgegeben, sonst true.
         * 
         * @param Name 
         * @return true 
         * @return false 
         */
        bool Handelsplatz::nameVergeben (string Name)
        {
           for (auto it = MarktNutzer.begin(); it != MarktNutzer.end();) // durchläuft map mit Nutzer auf dem Markt
           {
                if (it -> n.getName() == Name) //falls Nmae vergeben
                {
                return false; // dann false returned
                } 
                else{
                    ++it; //iterator erhöhen 
                }
            }
            return true;  // bei nicht vorhandensein des Namens wird true zurückgegeben
        }
        /**
         * @brief Funktion druckt alle Produkte auf dem Markt und den zugehörigen Preis.
         * 
         */
        void Handelsplatz::showMarket() 
        {
            cout << "Marktangebot:" << endl;
            for (auto it = Markt.begin(); it != Markt.end();) //durchläuft Produkten auf dem Markt 
            {
                cout << it -> o.getProdukt() << " - Preis: " << it -> o.getPreis() << endl; // Einzelene Produkte und der zugehörige Preis wird ausgegeben
                ++it;
            }
        }
        
        /**
         * @brief druckt alle Njutzer auf dem Markt
         * 
         */
        void Handelsplatz::showUsers() 
        {
            cout << "Nutzer auf dem Marktplatz:" << endl;
            for (auto it = MarktNutzer.begin(); it != MarktNutzer.end();) //durchläuft  Nutzer auf dem Markt 
            {
                cout << "Nutzer: " << it -> n.getName() << endl; // gibt alle Nutzer zurück
                ++it;
                
            }
        }   

        /**
         * @brief erstellt ein Produkt. Dabei wird der Produktname und der zugehörige Preis angegeben. Diese Produkt gehört dem Markt.
         * 
         * @param Produkt 
         * @param Preis 
         */
        void Handelsplatz::addProdukt(string Produkt, double Preis) //erstellen eines Produktes
        {
            Objekt no = Objekt (Produkt, Preis, "Markt"); //Erstelleung eines Objektes für dieses Produkt
            mo.o = no;
            Markt.push_front(mo); // wird zum Markt hinzugefügt
        }

        /**
         * @brief Funktion überprüft, ob der Benutzer der als Parameter übergebn wird, auf dem Markt existiert.
         * 
         * @param Benutzername 
         * @return true 
         * @return false 
         */
        bool Handelsplatz::findeBenutzer(string Benutzername) //sucht Benutzer in der Map mit den Nutzern
        {
            for(const auto& [key, value]: Information){ // in Information gespeichert
                if(key == Benutzername){ //key speichert Bneutzernamen, überprüfen ob diese gleich sind
                    return true;  // dann wird true zurückgegeben
                }
            }
            return false;  // falls nicht vorhanden, wird false zurückgegeben
 
        }

        /**
         * @brief Funktion durchläuft jedes Produkt auf dem Markt und ruft pro Produkt die eigentliche Preisanpassungsfunktion auf.
         * 
         */
        void Handelsplatz::Preisanpassung()
        {
            for(auto it = Markt.begin(); it != Markt.end();){ //Preise aller Produkte auf dem Markt werden angepasst
                it -> o.Preisanpassung(); //aufrufen der Funktion, die die Preise anpasst
                ++it; //durchlaufen aller Produkte
            }

        }

        /**
         * @brief Funktion ermöglicht den Kauf von einem Produkt. Es werden alle Produkte gedruckt und man kann diese Kaufen. Durch aufrufen anderer Funktion können die Produkte und das Geld gehandelt werden. Bei einem erfolgreichen Kauf wird true wiedregegeben, sonst false.
         * 
         * @return true 
         * @return false 
         */
        bool Handelsplatz::Handel()
        {
          nutzerobjekt an = MarktNutzer.front();
          showMarket(); // zeigt das Angebot
          cout << "Welches Objekt möchtest du kaufen?" << endl;
          string product;
          cin >> product;  //Eingabe des gewünschten Produktes
          for(auto it = Markt.begin(); it != Markt.end();){ //produkt wird gesucht
            if(it -> o.getProdukt() == product){
                cout << "Wie viele " << it -> o.getProdukt() << " möchtest du kaufen?" << endl; //gewünschte Anzahl wird abgefragt
                int k;
                cin >> k;
                double price = k*(it -> o.getPreis()); //Preis anepasst an die Anzhal der Produkte
                if(price <= an.n.getGuthaben()){ //falls Guthaben ausreicht
                    an.n.gekauft(price, product, k); //Marktanpassungs Funktion
                    cout << "Kauf abgeschlossen" << " Noch vorhandenens Guthaben: " << an.n.getGuthaben() << endl; //beendung Kaufes, ausgabe des aktualiserten Kontostandes
                    return true;
                }
                else{
                    cout << "Zu wenig Geld vorhanden. Kauf nicht möglich" << endl; // Ausgabe, falls Geld nicht genügt
                    return false;
                }
            }
            else{
                ++it;
            }
          }
          cout << "Produkt konnte nicht gefunden werden. Kauf konnte nicht abgeschlossen werden!" << endl; // falls nicht korrekte Eingabe
          return false;

        }

        
}
