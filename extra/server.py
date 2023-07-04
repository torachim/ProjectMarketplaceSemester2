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
import random
import uvicorn
from fastapi import FastAPI
import requests

app = FastAPI()


h = Handelsplatz()
h.produkt_hinzufuegen("15gHaze", 30.5)
h.produkt_hinzufuegen("Waschmaschiene", 15.0)
h.produkt_hinzufuegen("Bundeslade", 45.0)
passwoerternutzer, angebote, bereitgestellteObjekte = {}, {"15gHaze" : 30.5, "Waschmaschiene" : 15.0, "Bundeslade" : 45.0}, {}
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
            return {"information" : 'Account angelegt du kehrst zur Anmeldung zurueck', "Status":True}
        
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
                k = {produkt : anzahl}
                bereitgestellteObjekte[benutzername] = k

      return{"information" : 'Objekt(e) zum Verkauf bereitgestellt. Das Geld wird nach dem Verkauf uebermmittelt',
             "Status" : True}

@app.get("/handel/untereinander/{partner}")
async def handeluntereinander(partner : str):
      global nutzerverkaufe
      for p in nutzerverkaufe:
           print(partner)
           print(p.Namensehen())
           if(p.Namensehen() == partner):
                print("Jallo")
                ver = p.erhalteVerkaeufe()
                l = []
                for k,v in ver:
                     t = [k ,v]
                     l.append(t)
                     print("HAllo")
                return {"information" : l,
                        "Status" : True}
              
                





     

    
if __name__ == '__main__':
    this_python_file = os.path.basename(__file__)[:-3]
    instance = uvicorn.run(f"{this_python_file}: app", host="127.0.0.1", port=8000, log_level="info", reload=True)
