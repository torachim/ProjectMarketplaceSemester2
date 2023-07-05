#pragma once
#include "HandelsplatzInterface.hpp"
#include "Nutzer.hpp"
#include "Objekt.hpp"
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>


using namespace std;

namespace ProjectGamma {

class Handelsplatz : public HandelsplatzInterface {

public:
  Handelsplatz();
  void login();  //erstellt Account
  void einloggen(); // Annmeldefunktion
  void showMarket(); //druckt Produkte auf dem Markt aus
  void showUsers();  //druckt Nutzer des Marktes aus
  void addProdukt(string Produkt, double Preis); // erstellt produkte
  bool nameVergeben(string Name); //überprüft, ob gewünschter Name vergegben ist
  bool findeBenutzer(string Benutzername);  //sucht Nutzer auf dem Markt
  void Preisanpassung(); // passt Preis an
  bool Handel(); //kaufen des Proudktes

private:
  struct nutzerobjekt {
    Nutzer n = Nutzer("NULL");
  };
  nutzerobjekt nu;
  struct marktobjekte {
    Objekt o = Objekt("NULL", 0, "NULL");
  };
  marktobjekte mo;
  std::list<marktobjekte> Markt;        //Produkte des Marktes
  std::list<nutzerobjekt> MarktNutzer;  //Nutzer des Marktes
  std::map<string, string> Information;  //nutzer und passendes Passwort
};
} // namespace ProjectGamma