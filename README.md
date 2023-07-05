# Projekt3Handelsplatz

## Handelsplatz

Wir planen die Implementierung eines Handelsplatzes auf welchem noch nicht näher bekannte Objekte gehandelt werden. Wir planen die Implementierung erstmal mit drei Klassen die im folgenden beschrieben werden. Am Ende soll alles noch mmit Server und Client realisiert werden.


## Checkliste

- [ ] Zeitplan anlegen
- [ ] UML Diagramm anlegen
- [ ] hpp zu den entsprechenden Klassen anlegen
- [ ] Implementierung der zuvor entworfenen Klassen in C++
- [ ] Testen der Funktionenen der implementierten Klassen über GoogleTests
- [ ] Server und Client zur Ausführung des Projektes in Python implementieren
- [ ] Parallele Dukomentation beachten


## Handelsplatz Klasse

Auf dem Handelsplatz werden Waren in Form von noch nocht näher bekannten Objekten gehandelt. Auf dem Handelsplatz soll es sowohl möglich sein Objekte zu kaufen als auch welche zu verkaufen. Die Klasse Handelsplatz bitet somit die Grundlage für den Server.
- [ ] Membervariablen:
    - [ ] Information : Hashtabelle welche die Benutzer des Servers als Key und das von ihnen gewählte Passwort als Value enthält. Darüber können sich Benutzer des Handeslplatzes auf diesen Einloggen
    - [ ] MarktNutzer: Eine Liste welche die aktuell auf dem Markt befindlichen Nutzer als struct speichert
    - [ ] Markt: Eine Liste welche alle aktuellen Objekte auf dem Marktplatz enthält. Die Objekte werden als struct gespeichert
- [ ] Memberfunktionen:
    - [ ] Einloggen : Damit loggt sich ein Benutzer auf den Handelsplatz ein. Beim ersten Log-In des Serverdurchlauf soll der Benutzer sein eigenes Passwort wählen können. Das geschieht über eine Login Funktion
    - [ ] showMarket: Druckt die Handelsgüter des Marktplatzes aus
    - [ ] showUsers: Druckt die aktuellen Nutzer auf dem Marktplatz aus
    - [ ] addProdukt: Fügt ein Produkt auf den Marktplatz hinzu
    - [ ] nameVergeben: Prüft ob ein von einem Nutzer gewünschter Benutzername bereits vergeben wurde da doppelte Benutzernamen unzulässig sind
    - [ ] findeBenutzer: gibt anhand eines Benutzernamen aus ob ein solcher Nutzer auf dem Marktplatz existiert
    - [ ] Preisanpassung: Sorgt dafür das alle Objekte nach der Formel des 5. Übungsblattes ihren Preis ändern
    - [ ] Handel: Dadurch wird Handel mit dem Marktplatz durchgeführt


## Objekt Klasse

Die Objekte bilden die Waren welche auf dem Handelsplatz verkauft bzw. gekauft werden. Noch steht was für Objekte auf dem Handelsplatz verkauft werden.
- [ ] Membervariablen:
    - [ ] Produkt: Name des Produktes zur identifikation
    - [ ] Preis : Der Anfangswert eines Objektes für welches es zu beginn eingekauft bzw. verkauft werden kann.
    - [ ] Seller: Speichert den Benutzernamen des aktuellen Benutzers
    - [ ] Tendenz: ZUfallswert wichtig für die Berechnung der Preisänderung
- [ ] Memberfunktionen:
    - [ ] Preisanpassung : Sorgt dafür das sich der Wert eines Objektes ändert. Die dafür benutzte Formel ist die vom Übungsblatt. Eine Wertsteigerung bzw. ein Wertverlust soll nicht vorhersehbar sein
    - [ ] getProdukt: Gibt den Namen des Produktes zurück
    - [ ] getSeller: Gibt den aktuellen Besitzer des Objektes zurück
    - [ ] getTendenz: Gibt die Tendenz des aktuellen Objektes zurück


## Nutzer Klasse

Die Nutzer bilden die Personen welche auf dem Handelsplatz Objekte verkaufen bzw. einkaufen können. Die Nutzer können sich über ein am anfang gewähltes Passwort auf dem Handelsplatz einloggen.
- [ ] Membervariablen:
    - [ ] Guthaben : Das Geld mit dem ein Spieler handeln kann mit 100 RD initialisiert
    - [ ] myObjects : Im Inventar befinden sich die Waren die ein Nutzer esitzt mit ihrem entsprechenden Wert. Mit diesen kann der Nutzer auf dem Handelsplatz handeln. Die Objekte werden als struct gespeichert
    - [ ] Name : Der Name des Nutzers wird auch als Benutzername auf dem Handelsplatz verwendet 
    - [ ] VerkaufsAnzahl: Speichert die Produkte die der Nutzer verkaufen will sowie die Anzahl
- [ ] Memberfunktionen:
    - [ ] gekauft : Funktion die aufgerufen wird wenn ein Objekt gekauft wurde um Guthaben und ObjektListe anzupassen
    - [ ] verkauft : Funktion die aufgerufen wird wenn ein Objekt verkauft wurde um Guthaben und ObjektListe anzuapassen
    - [ ] druckeObjekte : Dient dazu um einen Überblick über die Objekte in seinem Inventar und ihren aktuellen Wert im Gegensatz zu dem entsprechenden Einkaufswert zu erhalten
    - [ ] getGuthaebn : Gibt das Geld des Nutzers zurueck
    - [ ] getName : Gibt den Namen eines Nutzers zurueck
    - [ ] Objekteaussortieren : FUnktion mit welcher man Objekte aus seinem Besitz zum Verkauf geben kann
    - [ ] getVerkaufsAnzahl : Gibt die Hashtable zurück in welcher die Objekte welche Verkauft werden soll sowie ihre Anzahl gespeichert ist
    - [ ] produktezumverkauf : Funktion mit welcher Produkte und ihre Anzahl die verkauft werden sollen in die entsprechende Hashtable gespeichert werden sollen

## Client

Über den Client wird der Handelsplatz für Nutzer verfügbar gemacht. Aufgrund von Personalmangel haben wir uns erstmal dazu entschieden den Client als Terminal Anwendung zu schreiben. Über das von Python bereitgestellte Terminal-Menu sollen die Funktionen des Clients ein wenig zugänglicher gemacht werden. Grundsätzlich verfügt der Client über 3 Funktionen:
- [ ] start : Bei Start landet man im Anmeldescreen des Handelsplatzes. Hier Hat man die Option sich einen Account zu machen. Hierfür gibt man einen Benutzernamen an (doppelte Benutzernamen sind wie üblich nicht zulässig) und ein persönliches Passwort an (dieses muss bei der registrierung wie üblich einmal wiederholt werden). Wenn amn einen Account hat kann man sich auf den Handelsplatz einloggen. Dies passiert über einen abgleich von Benutzernamen und dem zugehörigen gespeicherten Passwort auf dem Server. Wenn man eingloggt ist starten die verkaufs und handel Funktion parallel. Dies wird über Threading verfügbar gemacht. Man hat im Anmeldungsscreen auch die möglichkeit den Client zu beenden
- [ ] handel: Bei Handel handelt es sich um die Benutzeroberfläche des Handelsplatzes. Hier kann man mit dem Handelsplatz handeln oder, wenn vorhanden, mit anderen Nutzern. Auch können hier Objekte zum Verkauf angeboten werden. Das ist notwendig damit andere Nutzer überhaupt mit einem selbst Handeln können. Man kann sich auch vom Handelsplatz wieder abmelden. Ein erneuter Login ist möglich. Beim abmelden bleiben außerdem alle gekauften Objekte sowie sein aktueller Kontostand gespeichert.
- [ ] verkauf: Verkauf ist eine Funktion die dauerhaft im Hintergrund parallel läuft. Diese sendet ständig Anfragen an den Server und prüft so ob eines seiner Objekte bereits verkauft wurde nach jedem verkauf den diese Funktion abschließt werden außerdem die Preiser aller Objekte nach der Formel des Übungsblattes angepasst

## Server

Über den Server läuft die gesammte Verwaltung des Handelsplatzes. Hier wird überprüft ob  Käufe so getätigt werden könnnen oder ob sich ein Nutzer überhaupt auf dem Handelsplatz anmelden kann.  Aufgrund des Codes im Server und der art des Speichers ist Handel mit abgemeldeten Nutzern nicht möglich. Eine genaue Kommentierung der einzelnen Funktionen des Servers befindet sich im Programmcode. 

