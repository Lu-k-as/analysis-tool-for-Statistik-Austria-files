# Statistik Austria Document Analysis Tool

## Beschreibung
Dieses Programm wertet automatisiert Dateien von Statistik Austria aus. Dabei können bei der Auswertung folgende Einstellung getroffen werden:
- Auswahl der Einträge/Spalten, welche analysiert werden sollen.
-	Erstellung einer linearen Vorhersage, mit variabler Vorhersagedauer.
-	Auswertedaten im absolut/relativ Angaben.

## Dateien
- main.cpp:  Hauptprogramm, welche eine State-Maschine zyklisch durchläuf, bis die Benutzereingabe „Quit“ getätigt wird.
- database.cpp:  Hier handelt es sich um die Datenkapselung und Zwischenspeicherung des gesamten Projektes. Kurz gesagt handelt es sich um eine grundlegende Datenbank mit notwendigen Zugriffsfunktionen.
- importdata.cpp:  Dieser Projektteil stellt eine korrekte Verarbeitung der Input-Daten sicher. Falls eine fehlerhafte Benutzereingabe oder fehlerhafte Dateien eingelesen werden, wird eine entsprechende Fehlermeldungen ausgegeben.
