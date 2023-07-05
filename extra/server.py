#server
#   python3 -m uvicorn server:app --port 8000  --reload

try:
  import handelsplatz
except ImportError as e:
  print(f"Importing the shared library 'handelsplatz' did not work.")
  print(f"Is (a link to) the shared library 'handelsplatz.____.so' in the same directory as this python script?")
  print(f"The import caused the following exception '{e}'")
  print(f"Exiting")
  exit(1)


from handelsplatz import Handelsplatz, Nutzer, Objekt
import os
from random import *
import uvicorn
from fastapi import FastAPI
import requests
import math


app = FastAPI()

#Handelsplatz
h = Handelsplatz()
h.produkt_hinzufuegen("15gHaze", 30.5)
h.produkt_hinzufuegen("Waschmaschiene", 15.0)
h.produkt_hinzufuegen("Bundeslade", 45.0)
#passwoerternutzer -> enthällt benutzername und passwort aller jemals auf dem Handelsplatz registrierten Nutzer
#angebote -> speichert alle angebotenen Produkte sowie ihren Preis
#berietgestellteObjekte -> Enthällt Benutzer und ihre zum Verkauf bereitgellte Objekte sowie die anzahl
#verkaufteObjekte -> Enthällt alle Verkauften Objekte ihres Ursprünglichen BEsitzers
passwoerternutzer, angebote, bereitgestellteObjekte, verkaufteObjekte = {}, {"15gHaze" : 30.5, "Waschmaschiene" : 15.0, "Bundeslade" : 45.0, "Fifa23" : 22.4, "iPhone" : 87.8, "KastenStubbi" : 12.0, "KampfpanzerLeopard" : 69.0, "Atomkraftwerk" : 152.0, "Bienenschwarm" : 5.8, "KlausurLoesungen" : 11.5, "Sonnensystem" : 1.0}, {}, {}
#Liste aller momentan eingeloggten Nutzuer
aktuellenutzer = []
#Enthällt alle Nutzer die im moment Objekte verkaufen
nutzerverkaufe = []


#login auf dem Server
@app.get("/login/{benutzername}/{passwort}")
async def login(benutzername : str, passwort : str):
    global passwoerternutzer, aktuellenutzer
    #Das Passwort vom Benutzer wird gesucht
    if(passwoerternutzer.get(benutzername)):
        #Das eingegebene Passwort wird mit dem gespeicherten verglichen. Wenn sie übereinstimmen
        if(passwoerternutzer[benutzername] == passwort):
            #Nuter wird auf den Handelsplatz hinzugefuegt
            aktuellenutzer.append(benutzername)
            nutzerneu = Nutzer(benutzername)
            nutzerverkaufe.append(nutzerneu)
            return{"information" : 'Anmeldung erfolgreich',
                    "Status":True}
    return{"information" : 'Benutzername oder Passwort falsch',"Status":False}



#registrieren 
@app.get("/registrieren/{benutzername}/{passwort}")
async def register(benutzername : str, passwort : str):
        global passwoerternutzer
        #Wenn der Benutzername bereits existiert schlägt die Registrierung fehl
        if(passwoerternutzer.get(benutzername)):
            return {"information" : 'Benutzername schon vergeben',"Status":False}
        #Ansonsten word ein Account angelegt
        else:
            passwoerternutzer[benutzername] = passwort
            return {"information" : 'Account angelegt du kehrst zur Anmeldung zurueck', "Status":True}
        

#Gibt die aktuellen Nutzer auf dem Marktplatz zurueck        
@app.get("/handel/nutzererhalten")
async def getnutzer():
        global aktuellenutzer
        return{"information":aktuellenutzer}


#logout entfernt den Nutzer aus den aktuellen Nutzer entfernt und werden somit abgemeldet
@app.get("/handel/logout/{benutzername}")
async def abmelden(benutzername : str):
      global aktuellenutzer, nutzerverkaufe
      aktuellenutzer.remove(benutzername)
      return {"information" : 'Abmeldung erfolgreich. Bis zum nächsten mal!',
              "Status" : True}


#Gibt die Angebote des Marktes zurueck
@app.get("/handel/marktkauf")
async def marktzeigen():
      global angebote
      return {"information" : angebote,
              "Status" : True}


#Objekte werden zum VErkauf bereitgestellt
@app.get("/handel/objektebereitstellen/{produkt}/{anzahl}/{benutzername}")
async def Objektebereitstellen(produkt : str, anzahl : int, benutzername : str):
      global bereitgestellteObjekte, nutzerverkaufe
      for p in nutzerverkaufe:
           #Der Nutzer wird aus der Liste gelesen
           if (p.Namensehen() == benutzername):
                #Produkte werden zum Verkauf bereitgestellt
                p.Produkteverkaufen(produkt, anzahl)
                #Wenn der Nutzer bereits Objekte verkauft
                if(benutzername in bereitgestellteObjekte):
                     #Wird das neu ausgewählte Objekt einfach in das dict hinzugefuegt
                     p = bereitgestellteObjekte[benutzername]
                     #Wenn sogar das Produkt schon existiert wird die Anzahl an verkauften Objekten aktualisiert
                     if produkt in p:
                          neueAnzahl = p[produkt] + anzahl
                          p[produkt] = neueAnzahl
                     else:     
                          p[produkt] = anzahl
               #Wenn der Nutzer noch keine Objekte verkauft
                else:
                  #Wird ein neuer Eintrag m Dict angelegt
                  k = {produkt : anzahl}
                  bereitgestellteObjekte[benutzername] = k
                print(bereitgestellteObjekte)

      return{"information" : 'Objekt(e) zum Verkauf bereitgestellt. Das Geld wird nach dem Verkauf uebermmittelt',
             "Status" : True}


#Gibt die Objekte zurueck die der gewaehlte Handelspartner verkauft
@app.get("/handel/untereinander/{partner}")
async def handeluntereinander(partner : str):
      global nutzerverkaufe,bereitgestellteObjekte
      for p in nutzerverkaufe:
           
           if(p.Namensehen() == partner):
                #Die bereitgestellten Objekte werden zuruecckgegeben
                if(partner in bereitgestellteObjekte):
                  l = bereitgestellteObjekte[p.Namensehen()]
                  return {"information" : l,
                          "Status" : True}
                else:
                     return{"information" : "Diese Nutzer verkauft aktuell keine Ware",                          
                            "Status" : False}
      return {"information" : "Nutzer nicht gefunden",
              "Status" : False}
                

#Gibr den Wert eines Produktes zurueck und gibt gleichzeitig zurueck ob diese Ware überhaupt existiert                
@app.get("/handel/werterhalten/{wahl}")
async def wertgeben(wahl : str):
      global angebote
      if wahl in angebote:
          preis = angebote[wahl]
          return {"information" : preis,
               "Status" : True}
      else:
           return {"information" : "Ware existiert nicht",
                   "Status" : False}


#Überprüft ob das angegebene Objekt vom Partner gekauft werden kann da genug Produkte existieren oder das Produkt überhaupt existiert
@app.get("/handel/kaufueberpruefen/{partner}/{wahl}/{anzahl}")
async def kaufueberpruefen(partner : str, wahl : str, anzahl : int):
      global nutzerverkaufe, bereitgestellteObjekte
      k = bereitgestellteObjekte[partner]
      if wahl in k:
           if anzahl <= k[wahl]:
                return {"information" : "Kauf kann abgeschlossen werden",
                        "Status" : True}
           else:
                return {"information" : "Es werden zu wenige Objekte verkauft",
                        "Status" : False}
      else:
           return {"information" : "Objekt konnte nicht gefunden werden",
                   "Status" : False}
      

#Schließt den Kauf von einen anderen Nutzer ab
@app.get("/handel/kaufvonnutzerabschließen/{partner}/{wahl}/{anzahl}")
async def kaufvonnutzer(partner : str, wahl : str, anzahl : int):
      global nutzerverkaufe, bereitgestellteObjekte, angebote, verkaufteObjekte
      for k in nutzerverkaufe:
           if k.Namensehen() == partner:
                #Wenn der verkäufer im dict der verkauften Objekte bereits existiert wird eine Liste mit Ware und Anzahl hinzugefuegt
                if partner in verkaufteObjekte:
                  l = verkaufteObjekte[partner]
                  l.append([wahl, anzahl])
               #Ansonsten wird ein neuer Eintrag angelegt
                else:                    
                     q = []
                     u = [wahl, anzahl]
                     q.append(u)
                     verkaufteObjekte = {partner : q}

                p = bereitgestellteObjekte[partner]
                neueanzahl = p[wahl] - anzahl
                #Wenn alle Objekte dieser Art verkauft wurden wird der EIntrag dieses Produktes geloescht
                if neueanzahl == 0:
                     del p[wahl]
                #Ansonsten wird der Eintrag nur mit der neuen Anzahl aktualisiert     
                else:
                     p[wahl] = neueanzahl
      return {"information" : "Kauf abgeschlossen",
              "Status" : True}



#Gibt die Liste aller Produkte und ihre anzahl eines Nutzers zurueck die bereits an einen anderen Nutzer verkauft wurden
@app.get("/thread/verkaufbekommen/{benutzername}")
async def verkauferhalten(benutzername : str):
      global verkaufteObjekte
      if benutzername in verkaufteObjekte:
           li = verkaufteObjekte[benutzername]
           return {"information" : li,
                   "Status" : True}
      else:
           return {"Status" : False}
      

#Schließt den Verkauf ab in dem das entsprechende Produkt anzahl Paar aus der liste entfernt wird
@app.get("/thread/verkaufabschließen/{benutzername}/{produkt}/{anzahl}")
async def verkaufabsch(benutzername : str, produkt : str, anzahl : int):
      global verkaufteObjekte
      li = verkaufteObjekte[benutzername]
      li.remove([produkt, anzahl])
      return {"Status" : True}


#Passt den Preis aller gehandelten Produkte an nach der Formel an 
@app.get("/thread/preisanpassung")
async def preiseanpassen():
      global angebote
      for a in angebote:
           preis = angebote[a]
           Y = 2*(randint(0,9)) - 1
           Tendenz = 0.3 * (randint(0,9)-1)
           dt =  0.02
           preisneu = preis * (1.0 + Tendenz*dt + 0.8*math.sqrt(dt)*Y)
           preisgerundet = round(preisneu, 2)
           angebote[a] = preisgerundet
      return {"Status" : True}


           

    
if __name__ == '__main__':
    this_python_file = os.path.basename(__file__)[:-3]
    instance = uvicorn.run(f"{this_python_file}: app", host="127.0.0.1", port=8000, log_level="info", reload=True)
