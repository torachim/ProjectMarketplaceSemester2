#client
#python3 client.py
import time
from handelsplatz import Handelsplatz
from handelsplatz import Nutzer
from handelsplatz import Objekt
from pprint import pprint
from simple_term_menu import TerminalMenu
import requests
from threading import Thread



base_api_url = "http://127.0.0.1:8000"
benutzername = None  #benutzername zur verifizierung des Nutzers
Login = False #Login bool der true ist solange man sich auf dem Handelsplatz befindet
Nutzerich = None #Nutzer

#Funktion die immer Anfragen an den Server sendet ob zum Verkauf bereitgestellte Produkte bereits verkauft wurden
def verkauf():
    global Nutzerich, benutzername, Login
    while Login:            #Solange man eingeloggt ist auf dem Handelsplatz 
        responseig = requests.get(f"{base_api_url}/thread/verkaufbekommen/{benutzername}").json()  #Anfrage ob Produkt verkauft wurde
        if responseig["Status"]:                    #Wenn Produkt verkauft wurde
            l = responseig["information"]           #Liste mit den verkauften Objekten wird übergeben
            for k in l:                             #Für alle Elemente aus der Liste
                produkt = k[0]                      #Verkauftes Produkt
                anzahl = k[1]                       #Anzahl an verkauften Elementen
                responseig = requests.get(f"{base_api_url}/handel/werterhalten/{produkt}").json()       #Anfrage um den Wert erhalten
                preis = responseig["information"]                   #Preis des verkauften Objekts wird zurückgegeben
                Nutzerich.produktverkauft(produkt, preis, anzahl)       #Aufrufen der Produkt verkauft funktion
                responseig = requests.get(f"{base_api_url}/thread/verkaufabschließen/{benutzername}/{produkt}/{anzahl}").json()         #Verkaufabschließen an den Server senden
                responseig = requests.get(f"{base_api_url}/thread/preisanpassung").json()       #Preisanpassung der Objekte nach jedem Kauf untereinander
        time.sleep(3.0)
    


#Handel Funktion
def handel():
    global Login, benutzername, Nutzerich
    #Solange man auf dem Server angemeldet ist
    while Login:        
        print("Dein Guthaben", Nutzerich.Geldsehen(), "RD")
        Nutzerich.besitzesehen()
        m = TerminalMenu(["Momentane Nutzer", "Objekte bereitstellen", "Handel mit anderen Nutzer", "Handel mit Markt", "Abmelden"])
        auswahl = m.show()

        #Wenn man die Nutzer auf dem Marktplatz sehen möchte
        if(auswahl == 0):
            response = requests.get(f"{base_api_url}/handel/nutzererhalten").json()
            print(response["information"])
        
        #Wenn man sich vom Marktplatz abmelden will
        elif(auswahl == 4):
            response = requests.get(f"{base_api_url}/handel/logout/{benutzername}").json()
            print(response["information"])
            Login = False
        
        #Wenn man Objekte in seinem Besitz zum verkauf bereitstellen möchte
        elif(auswahl == 1):
            Nutzerich.besitzesehen()
            #Abfrage welche Objekte man bereitstellen will
            produkt = str(input("Welches deiner Objekte möchtest du zum Verkauf bereitstellen?"))
            anzahl = int(input("Wie viele dieser Objekte möchtest du verkaufen?"))
            #Produkte werden bereitgestellt
            if Nutzerich.produkteBereitstellen(str(produkt), int(anzahl)):
                response = requests.get(f"{base_api_url}/handel/objektebereitstellen/{produkt}/{anzahl}/{benutzername}").json()
                print(response["information"])

        #Wenn man Objekte eines anderen Nutzers kaufen will
        elif(auswahl == 2):
            #Nutzer werden ausgegeben
            response = requests.get(f"{base_api_url}/handel/nutzererhalten").json()
            print(response["information"])
            #Angabe mit welchem Nutzer man handeln will
            partner = str(input('Von Welchem Haendler moechtest du dir die Produkte anschauen?'))
            partner = partner.replace(str("'"), str(""))
            response = requests.get(f"{base_api_url}/handel/untereinander/{partner}").json()
            #Wenn der Partner überhaupt Produkte verkauft
            if(response["Status"]):
                #Produkte des Verkäufers werden ausgegeben
                for k in response["information"]:
                    print("Produkt: ", k, "Anzahl: ", response["information"][k])
                a = TerminalMenu(["Kaufen", "Zurueck"])
                kaufwahl = a.show()
                #Wenn man sich dazu entscheidet zu kaufen
                if kaufwahl == 0:
                    #Abfrage welches Objekt man kaufen möchte und wie viele davon
                    wahl = str(input('Welches der Objekte möchtest du kaufen?'))
                    wahl = wahl.replace(str("'"), str(""))
                    anzahl = int(input('Wie viele der angebotenen Objekte willst du kaufen?'))
                    
                    #Schauen wie viel das Objekt kostet und ob es überhauot auf dem Handelsplatz existiert
                    response = requests.get(f"{base_api_url}/handel/werterhalten/{wahl}").json()
                    #Wenn ja
                    if response["Status"]:
                        #Erhalte den Preis und vergleiche ihn mit deinem eigenen Guthaben
                        preis = response["information"]
                        #Wenn man genug Geld hat um die angegeben Objekte zu kaufen
                        if Nutzerich.Geldsehen() - preis*anzahl >= 0:
                            #Wenn das angegebene Objekt vom Partner angeboten wird
                            response = requests.get(f"{base_api_url}/handel/kaufueberpruefen/{partner}/{wahl}/{anzahl}").json()
                            if response["Status"]:
                                #Kauf wird abgeschlossen. Guthaben und Liste der Objekte wird angepasst
                                response = requests.get(f"{base_api_url}/handel/kaufvonnutzerabschließen/{partner}/{wahl}/{anzahl}").json()
                                vollstaendigerpreis = preis * anzahl
                                Nutzerich.produktgekauft(vollstaendigerpreis, wahl, anzahl)
                                print(response["information"])
                                print("Neues Guthaben: ", Nutzerich.Geldsehen(), "RD")
                            #Wenn das Objekt gar nicht angeboten wird
                            else:
                                print(response["information"])
                        #Wenn das Geld nicht ausreicht für den Handel
                        else:
                            print("Dein Geld reicht leider nicht aus!")
                    #Wenn das Objekt gar nicht auf dem Handelsplatz existiert
                    else:
                        print(response["information"])  
            #Wenn der angegebene Nutzer gar nicht existiert            
            else:
                print(response["information"])
            

        #Wenn man mit dem Markt handeln will
        elif(auswahl == 3):
            #Produkte die der Markt anbietet werden ausgegeben mit samt Preis
            print("Folgende Produkte bietet der Markt an: \n")
            response = requests.get(f"{base_api_url}/handel/marktkauf").json()
            ergebnis = response["information"]
            for k in ergebnis:
                print(k, " ", ergebnis[k], "RD")
            a = TerminalMenu(["Vom Markt kaufen", "Zurueck"])
            wahl = a.show()
            
            #Wenn man sich dazu entscheidet einen Kauf durchzufuehren
            if(wahl == 0):
                #Solange der Kauf nicht abgeschlossen ist
                kaufabschließen = False
                while not kaufabschließen:
                    #Objekt angeben welches man Kaufen möchte
                    p = 0
                    willkaufen = str(input("Welches der Objekte möchtest du kaufen?"))
                    for k in ergebnis:
                        if k == willkaufen:
                            #Angabe wie viele der Objekte man kaufen will der Markt bietet unendlich viele da
                            anzahl = int(input("Wie viele von diesem Objekt willst du kaufen?"))
                            preis = ergebnis[k] * anzahl
                            #Wenn man genug Geld hat um den Kauf abzuschließen
                            if preis <= Nutzerich.Geldsehen():
                                #Wird der Kauf abgebrochen
                                Nutzerich.produktgekauft(preis, k, anzahl)
                                print("Neues Guthaben: ", Nutzerich.Geldsehen(), "RD")
                                kaufabschließen = True
                                break
                            #Wenn das Geld nicht ausreicht
                            else:
                                print("Nicht genung Geld!")
                                p = 1
                                break 
                    #Wenn das Produkt nicht gefunden wird        
                    if not kaufabschließen and p == 0:
                        print("Produkt nicht gefunden")
                        p = 0                  
    #Wenn man sich ausloggt kehrt man zum Startscreen zurück        
    start()
        
#Startfunktion um den Startscreen aufzurufen
def start():
    global Login, benutzername, Nutzerich
    #Willkommen auf dem Handelsplatz
    print("Willkommen auf dem Handelsplatz")
    m = TerminalMenu(["Login", "Registrieren", "Beenden"])
    auswahl = m.show()
    #Wenn man sich registrieren will
    if(auswahl == 1):
        #Solange man sich nicht erfolgreich registriert hat
        k = False
        while not k:
            #Benutzername und Passwort eingebennach erster Passwort eingabe muss das einmal wiederholt werden
            benutzername = str(input("Bitte gebe einen Benutzername ein: \n"))
            benutzername = benutzername.replace(str("'"), str(""))
            passwort = str(input("Bitte gebe ein Passwort ein: \n"))
            passwort = passwort.replace(str("'"), str(""))
            passwortwiederholen = str(input("Bitte Passwort wiederholen: \n"))
            passwortwiederholen = passwortwiederholen.replace(str("'"), str(""))
            #Wenn das wiederholte Passwort mit dem originalen Übereinstimmt
            if (passwortwiederholen == passwort):
                #Account wird angelegt
                response = requests.get(f"{base_api_url}/registrieren/{benutzername}/{passwort}").json()
                if (response["Status"]):
                    print(response["information"])
                    Nutzerich = Nutzer(benutzername)
                    k =  True

                #Wenn der gewählte Benutzer schon existiert
                else:
                    print(response["information"])
            #Wenn das Passwort beim zweiten mal falsch eingegeben wurde
            else:
                print("Passwort falsch bitte erneut versuchen")
    #Wenn man sich einloggen will
    elif(auswahl == 0):
        #Solange man sich nicht erfolgreich eingeloggt hat
        k = False
        while not k:
            #Benutzername und Passwort eingeben
            benutzername = str(input("Benutzername: \n"))
            benutzername = benutzername.replace("'", "")
            passwort = str(input("Passwort: \n"))
            passwort = passwort.replace("'", "")
            response = requests.get(f"{base_api_url}/login/{benutzername}/{passwort}").json()

            #Wenn alle Informationen mit einem der Accounts übereinstimmen
            if(response["Status"]):
                print(response["information"])
                #Man wird eingeloggt
                k = True
                Login = True
                #VErkaufsfunktion wird parallel zum handelsplatz gestartet über threading
                thread1 = Thread(target=verkauf)
                thread1.start()
                handel()

            #Wenn die eingegebenen Funktionen nicht mit gespeicherten übereinstimmen darf man seine Eingabe nochmal versuchen
            else:
                print(response["information"])
                print("Erneut versuchen?")
                menu = TerminalMenu(["Ja", "Nein"])
                p = menu.show()

                if(p == 1):
                    break
    #Wenn man den Handelsplatz beenden will            
    else:
        exit()
 
    start()  

  






#Start des Clients
def main():
    base_api_url = "http://127.0.0.1:8000"
    start() #Programmstart


if __name__ == '__main__':
    main()