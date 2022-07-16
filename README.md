# NJVM
Projekt als vorausgesetzte Zulassung zur Teilnahme der Klausur von dem "**Konzepte Systemnaher Programmierung**"-Modul.

Konstruktion einer ***Virtuellen Maschine*** zur Ausführung von Programmen der kleinen Programmiersprache **Ninja** ("Ninja is not Java").\
Bewertung bei 1. Hausuebung = 100%.\
Bewertung bei 2. Hausuebung = 81%.\

Abgeschlossen zum Sommersemester 2022.

## Kompilieren mit njc (*.nj -> *.asm)
Mit **./njc [INPUT]** kann man den Assemblercode auf die Standardausgabe ausgegeben.\
bspw. ```./njc ../bsp.nj```\
Ausgabeumlenkung ist hier von Nützen, z.B. ```./njc ../bsp.nj --> ../bsp.asm```

## Assemblieren mit nja (*.asm -> *.bin)
Mit **./nja [INPUT] [OUTPUT]** wird eine Binär Datei assembliert, die später in der Virtuellen Maschine ausgeführt werden kann.\
bspw. ```./njc ../bsp.nj --> bsp.asm```

## Verwendung der virtuellen Maschine
* Provisorisches "Make-File" ```./mknjvm``` zum kompilieren ausführen (**zur Kompilierung ab der 6. Aufgabe**).
* Mit ```./njvm bsp.bin``` wird das Programm ausgeführt oder geladen.

## Debugen der virtuellen Maschine
Der Debuger kann interaktiv in das Geschehen der Maschine eingreifen./
Mit der Option **--debug** wird der Debuger gestartet. -> ```./njvm --debug bsp.bin```\

Folgende Optionen sind möglich:
* inspect
  * stack: Der komplette Stack wird ausgegeben.
  * data: Die statischen Daten werden ausgegeben.
  * object: Mit Eingabe der Objekt Referenz wird der Wert des Objektes ausgegeben.
* quit: Die Virtuelle Maschine wird beendet.
* run: Das Programm läuft weiter und endet entweder beim vorher gesetzten Breakpoint oder wenn es das Ende erreicht hat.
* list: Die Befehle im Programmspeicher werden aufgelistet.
* step: Der angezeigte Befehl wird ausgeführt und springt zum nächsten weiter.
* breakpoint: Das Programm setzt einen Breakpoint.
