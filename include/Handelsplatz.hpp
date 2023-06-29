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
  void login();
  void einloggen();
  void showMarket();
  void showUsers();
  void addProdukt(string Produkt, double Preis);
  // void createNutzer(string Name, int Passwort);
  bool nameVergeben(string Name);
  bool findeBenutzer(string Benutzername);

private:
  struct nutzerobjekt {
    Nutzer n = Nutzer("NULL");
  };
  nutzerobjekt nu;
  struct marktobjekte {
    Objekt o = Objekt("NULL", 0, "NULL");
  };
  marktobjekte mo;
  std::list<marktobjekte> Markt;
  std::list<nutzerobjekt> MarktNutzer;
  std::map<string, string> Information;
};
} // namespace ProjectGamma