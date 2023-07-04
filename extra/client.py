#client
#python3 client.py
import time
from handelsplatz import Handelsplatz
from handelsplatz import Nutzer
from handelsplatz import Objekt
from pprint import pprint
from simple_term_menu import TerminalMenu
import requests


base_api_url = "http://127.0.0.1:8000"
MeineObjekte = []
Verkaufsanzahl, ObjekteAnzahl = {}, {}
AktuelleRD = float (100.0)
benutzername = None
Login = False
Nutzerich = None


def handel():
    global Login, benutzername, Nutzerich
    while Login:
        print("Dein Guthaben", Nutzerich.Geldsehen(), "RD")
        Nutzerich.besitzesehen()
        m = TerminalMenu(["Momentane Nutzer", "Objekte bereitstellen", "Handel mit anderen Nutzer", "Handel mit Markt", "Abmelden"])
        auswahl = m.show()

        if(auswahl == 0):
            response = requests.get(f"{base_api_url}/handel/nutzererhalten").json()
            print(response["information"])
        
        elif(auswahl == 4):
            response = requests.get(f"{base_api_url}/handel/logout/{benutzername}").json()
            print(response["information"])
            Login = False
        
        elif(auswahl == 1):
            Nutzerich.besitzesehen()
            produkt = str(input("Welches deiner Objekte möchtest du zum Verkauf bereitstellen?"))
            anzahl = int(input("Wie viele dieser Objekte möchtest du verkaufen?"))
            if Nutzerich.produkteBereitstellen(str(produkt), int(anzahl)):
                response = requests.get(f"{base_api_url}/handel/objektebereitstellen/{produkt}/{anzahl}/{benutzername}").json()
                print(response["information"])

        elif(auswahl == 2):
            response = requests.get(f"{base_api_url}/handel/nutzererhalten").json()
            print(response["information"])
            partner = str(input("Von Welchem Haendler moechtest du dir die Produkte anschauen?"))
            response = requests.get(f"{base_api_url}/handel/untereinander/{partner}").json()
            for k in response["information"]:
                print(k)


        elif(auswahl == 3):
            print("Folgende Produkte bietet der Markt an: \n")
            response = requests.get(f"{base_api_url}/handel/marktkauf").json()
            ergebnis = response["information"]
            for k in ergebnis:
                print(k, " ", ergebnis[k], "RD")
            a = TerminalMenu(["Vom Markt kaufen", "Zurueck"])
            wahl = a.show()
            
            if(wahl == 0):
                kaufabschließen = False
                while not kaufabschließen:
                    willkaufen = str(input("Welches der Objekte möchtest du kaufen?"))
                    for k in ergebnis:
                        if k == willkaufen:
                            anzahl = int(input("Wie viele von diesem Objekt willst du kaufen?"))
                            preis = ergebnis[k] * anzahl
                            if preis <= Nutzerich.Geldsehen():
                                Nutzerich.produktgekauft(preis, k, anzahl)
                                print("Neues Guthaben: ", Nutzerich.Geldsehen(), "RD")
                                kaufabschließen = True
                                break
                            else:
                                print("Nicht genung Geld!")
                                break 
                    if not kaufabschließen:
                        print("Produkt nicht gefunden")   
            

        
    start()
        ##

def start():
    global Login, benutzername, Nutzerich
    print("Willkommen auf dem Handelsplatz")
    m = TerminalMenu(["Login", "Registrieren", "Beenden"])
    auswahl = m.show()

    if(auswahl == 1):
        k = False
        while not k:
            benutzername = str(input("Bitte gebe einen Benutzername ein: \n"))
            benutzername = benutzername.replace("'", "")
            passwort = str(input("Bitte gebe ein Passwort ein: \n"))
            passwort = passwort.replace("'", "")
            passwortwiederholen = str(input("Bitte Passwort wiederholen: \n"))
            passwortwiederholen = passwortwiederholen.replace("'", "")
            
            if (passwortwiederholen == passwort):
                response = requests.get(f"{base_api_url}/registrieren/{benutzername}/{passwort}").json()
                if (response["Status"]):
                    print(response["information"])
                    Nutzerich = Nutzer(benutzername)
                    k =  True
                
                else:
                    print(response["information"])
            
            else:
                print("Passwort falsch bitte erneut versuchen")
    elif(auswahl == 0):
        k = False
        while not k:

            benutzername = str(input("Benutzername: \n"))
            benutzername = benutzername.replace("'", "")
            passwort = str(input("Passwort: \n"))
            passwort = passwort.replace("'", "")
            response = requests.get(f"{base_api_url}/login/{benutzername}/{passwort}").json()

            if(response["Status"]):
                print(response["information"])
                k = True
                Login = True
                handel()

            else:
                print(response["information"])
                b = str(input("Erneut versuchen? (J/N)"))

                if(b == "N"):
                    break

    else:
        exit()
     
    start()  

  







def main():
    base_api_url = "http://127.0.0.1:8000"
    start()


if __name__ == '__main__':
    main()