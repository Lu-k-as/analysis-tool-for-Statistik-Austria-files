This Programm has the function to autimatical 
- read some Statistic Austria file
- detect all column-names
- ask user for which columns / time-frame / future forcast he is interested in
- generating output file

---Beschreibung---

--> main.cpp
Hierbei handelt es sich um das Hauptprogramm, dass so aufgebaut wurde dass am Schluss 
eine Art State-Maschine welche immer wieder durchlaufen wird bis eine Benutzereingabe <Q>
für Quit ist. In dieser State-Maschine werden immer Funktionen aufgerufen welche oberhalbt
deffeniert sind.

-->database.h und database.cpp
Hier handelt es sich um die Datenkapselung des gesammten Projektes. Zuerst wird hier eine
Klasse angelegt welche dynamisch erweitert werden kann. Danach folgen diverse Zugriffsfunktionen.
Es wird hier kurz gesagt eine Art Datenbank erstellt mit notwendigen Zugriffsfunktionen.

-->importdata.h und importdata.cpp
Hier geht es vor allem um die BEnutzereingabe. Es wird hier großen Wert darauf gelegt, dass
bei fehlerhaften Benutzereingaben ensprechnende Fehlermeldungen und ensprechende Fehlerkorrekturen
zu geben um das Programm vor unzulässigen Eingabedaten oder im schlimmsten Fall einem Programmabsturtz
zu schlützen.
