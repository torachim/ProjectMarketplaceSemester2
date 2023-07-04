#include "../include/Handelsplatz.hpp"
#include "../include/Objekt.hpp"
#include "../include/Nutzer.hpp"
#include <iostream>
#include<string>
#include <map>
#include<pybind11/pybind11.h>

namespace py = pybind11;
using namespace ProjectGamma;

PYBIND11_MODULE(handelsplatz, m){

    m.doc() = "Handelsplatz von Torge und Snehpreet";

    py::class_<::Handelsplatz>(m, "Handelsplatz")
        .def(py::init< >())
        .def("login", &Handelsplatz::login)
        .def("Einloggen", &Handelsplatz::einloggen)
        .def("produkt_hinzufuegen", &Handelsplatz::addProdukt)
        .def("namekontrolle", &Handelsplatz::nameVergeben)
        .def("Benutzerfinden", &Handelsplatz::findeBenutzer)
        .def("Pricechange", &Handelsplatz::Preisanpassung)
        .def("marktzeigen", &Handelsplatz::showMarket)
        .def("handeln", &Handelsplatz::Handel);
    
    py::class_<::Nutzer>(m, "Nutzer")
        .def(py::init<std::string>())
        .def("produktgekauft", &Nutzer::gekauft)
        .def("produktverkauft", &Nutzer::verkauft)
        .def("Geldsehen", &Nutzer::getGuthaben)
        .def("Namensehen", &Nutzer::getName)
        .def("besitzesehen", &Nutzer::druckeObjekte)
        .def("produkteBereitstellen", &Nutzer::Objekteaussortieren)
        .def("erhalteVerkaeufe", &Nutzer::getVerkaufsAnzahl)
        .def("Produkteverkaufen", &Nutzer::produktzumverkauf);

    py::class_<::Objekt>(m, "Objekt")
        .def(py::init<std::string, double, std::string>())
        .def("ProduktName", &Objekt::getProdukt)
        .def("ErhaltePreis", &Objekt::getPreis)
        .def("ErhalteSeller", &Objekt::getSeller)
        .def("Preisaenderung", &Objekt::Preisanpassung)
        .def("erhalteTendenz", &Objekt::getTendenz);
}

