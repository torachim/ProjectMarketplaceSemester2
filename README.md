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
    - [ ] Passwörter : Hashtabelle welche die Benutzer des Servers als Key und das von ihnen gewählte Passwort als Value enthält. Darüber können sich Benutzer des Handeslplatzes auf diesen Einloggen
    - [ ] Geld : Hashtabelle welche ie Benutzer als Key und den entsprechenden Betrag an Geld enthällt als Value enthält
    - [ ] Waren : Eine Liste welche alle aktuellen Objekte auf dem Marktplatz enthält
- [ ] Memberfunktionen:
    - [ ] Einloggen : Damit loggt sich ein Benutzer auf den Handelsplatz ein. Beim ersten Log-In des Serverdurchlauf soll der Benutzer sein eigenes Passwort wählen können


## Objekt Klasse

Die Objekte bilden die Waren welche auf dem Handelsplatz verkauft bzw. gekauft werden. Noch steht was für Objekte auf dem Handelsplatz verkauft werden.
- [ ] Membervariablen:
    - [ ] Bezeichnung : Name des Objekt zur identifikation
    - [ ] Anfangswert : Der Anfangswert eines Objektes für welches es zu beginn eingekauft bzw. verkauft werden kann.
- [ ] Memberfunktionen:
    - [ ] Wertanpassung : Sorgt dafür das sich der Wert eines Objektes ändert. Die dafür benutzte Formel ist die vom Übungsblatt. Eine Wertsteigerung bzw. ein Wertverlust soll nicht vorhersehbar sein


## Nutzer Klasse

Die Nutzer bilden die Personen welche auf dem Handelsplatz Objekte verkaufen bzw. einkaufen können. Die Nutzer können sich über ein am anfang gewähltes Passwort auf dem Handelsplatz einloggen.
- [ ] Membervariablen:
    - [ ] Vermoegen : Das Geld mit dem ein Spieler handeln kann
    - [ ] Inventar : Im Inventar befinden sich die Waren die ein Nutzer esitzt mit ihrem entsprechenden Wert. Mit diesen kann der Nutzer auf dem Handelsplatz handeln
    - [ ] Name : Der Name des Nutzers wird auch als Benutzername auf dem Handelsplatz verwendet 
- [ ] Memberfunktionen:
    - [ ] Einkaufen : Funtion um ein Objekt zu kaufen und sein Geldvermögen entsprechend zu senken
    - [ ] Verkaufen : Funktion um ein Objekt zu verkaufen und sein Geldvermögen entsprechend zu erhöhen
    - [ ] Warenüberblick : Dient dazu um einen Überblick über die Objekte in seinem Inventar und ihren aktuellen Wert im Gegensatz zu dem entsprechenden Einkaufswert zu erhalten