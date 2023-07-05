#server
#   python3 -m uvicorn server:app --port 8000  --reload

try:
  import handelsplatz
except ImportError as e:
  print(f"Importing the shared library 'schiffeversenken' did not work.")
  print(f"Is (a link to) the shared library 'schiffeversenken.____.so' in the same directory as this python script?")
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


h = Handelsplatz()
h.produkt_hinzufuegen("15gHaze", 30.5)
h.produkt_hinzufuegen("Waschmaschiene", 15.0)
h.produkt_hinzufuegen("Bundeslade", 45.0)
passwoerternutzer, angebote, bereitgestellteObjekte, verkaufteObjekte = {}, {"15gHaze" : 30.5, "Waschmaschiene" : 15.0, "Bundeslade" : 45.0, "Fifa23" : 22.4, "iPhone" : 87.8, "KastenStubbi" : 12.0, "KampfpanzerLeopard" : 69.0, "Atomkraftwerk" : 152.0, "Bienenschwarm" : 5.8, "KlausurLoesungen" : 11.5, "Sonnensystem" : 1.0}, {}, {}
aktuellenutzer = []
nutzerverkaufe = []



@app.get("/login/{benutzername}/{passwort}")
async def login(benutzername : str, passwort : str):
    global passwoerternutzer, aktuellenutzer
    if(passwoerternutzer.get(benutzername)):
        if(passwoerternutzer[benutzername] == passwort):
            aktuellenutzer.append(benutzername)
            nutzerneu = Nutzer(benutzername)
            nutzerverkaufe.append(nutzerneu)
            return{"information" : 'Anmeldung erfolgreich',
                    "Status":True}
    return{"information" : 'Benutzername oder Passwort falsch',"Status":False}



@app.get("/registrieren/{benutzername}/{passwort}")
async def register(benutzername : str, passwort : str):
        global passwoerternutzer
        if(passwoerternutzer.get(benutzername)):
            return {"information" : 'Benutzername schon vergeben',"Status":False}
        else:
            passwoerternutzer[benutzername] = passwort
            return {"information" : 'Account angelegt, du kehrst zur Anmeldung zurueck', "Status":True}
        

        
@app.get("/handel/nutzererhalten")
async def getnutzer():
        global aktuellenutzer
        return{"information":aktuellenutzer}



@app.get("/handel/logout/{benutzername}")
async def abmelden(benutzername : str):
      global aktuellenutzer, nutzerverkaufe
      aktuellenutzer.remove(benutzername)
      return {"information" : 'Abmeldung erfolgreich. Bis zum nächsten mal!',
              "Status" : True}



@app.get("/handel/marktkauf")
async def marktzeigen():
      global angebote
      return {"information" : angebote,
              "Status" : True}



@app.get("/handel/objektebereitstellen/{produkt}/{anzahl}/{benutzername}")
async def Objektebereitstellen(produkt : str, anzahl : int, benutzername : str):
      global bereitgestellteObjekte, nutzerverkaufe
      for p in nutzerverkaufe:
           if (p.Namensehen() == benutzername):
                p.Produkteverkaufen(produkt, anzahl)
                if(benutzername in bereitgestellteObjekte):
                     p = bereitgestellteObjekte[benutzername]
                     p[produkt] = anzahl
                else:
                  k = {produkt : anzahl}
                  bereitgestellteObjekte = {benutzername : k}
                print(bereitgestellteObjekte)

      return{"information" : 'Objekt(e) zum Verkauf bereitgestellt. Das Geld wird nach dem Verkauf uebermittelt',
             "Status" : True}



@app.get("/handel/untereinander/{partner}")
async def handeluntereinander(partner : str):
      global nutzerverkaufe,bereitgestellteObjekte
      for p in nutzerverkaufe:
           
           if(p.Namensehen() == partner):
                if(partner in bereitgestellteObjekte):
                  l = bereitgestellteObjekte[p.Namensehen()]
                  return {"information" : l,
                          "Status" : True}
                else:
                     return{"information" : "Diese Nutzer verkauft aktuell keine Ware",                          
                            "Status" : False}
      return {"information" : "Nutzer nicht gefunden",
              "Status" : False}
                

                
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
      


@app.get("/handel/kaufvonnutzerabschließen/{partner}/{wahl}/{anzahl}")
async def kaufvonnutzer(partner : str, wahl : str, anzahl : int):
      global nutzerverkaufe, bereitgestellteObjekte, angebote, verkaufteObjekte
      for k in nutzerverkaufe:
           if k.Namensehen() == partner:
                if partner in verkaufteObjekte:
                  l = verkaufteObjekte[partner]
                  l.append([wahl, anzahl])
                else:                    
                     q = []
                     u = [wahl, anzahl]
                     q.append(u)
                     verkaufteObjekte = {partner : q}

                p = bereitgestellteObjekte[partner]
                neueanzahl = p[wahl] - anzahl
                print(verkaufteObjekte)

                if neueanzahl == 0:
                     del p[wahl]
                else:
                     p[wahl] = neueanzahl
      return {"information" : "Kauf abgeschlossen",
              "Status" : True}




@app.get("/thread/verkaufbekommen/{benutzername}")
async def verkauferhalten(benutzername : str):
      global verkaufteObjekte
      if benutzername in verkaufteObjekte:
           li = verkaufteObjekte[benutzername]
           return {"information" : li,
                   "Status" : True}
      else:
           return {"Status" : False}
      


@app.get("/thread/verkaufabschließen/{benutzername}/{produkt}/{anzahl}")
async def verkaufabsch(benutzername : str, produkt : str, anzahl : int):
      global verkaufteObjekte
      li = verkaufteObjekte[benutzername]
      li.remove([produkt, anzahl])
      return {"Status" : True}



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
