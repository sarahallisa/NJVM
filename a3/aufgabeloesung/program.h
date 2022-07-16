#ifndef PROGRAM_H
#define PROGRAM_H

// Maximal Stack-Anzahl definieren
#define MAX 10000

// Stack als Global-Variablen definieren
extern int stack[MAX];
extern int sp; 

// Programmspeicher als Global-Variablen definieren
extern unsigned int * programmspeicher;

// Programmcounter als Global-Variablen definieren
extern int pc;

// Static Data Area als Global-Variablen definieren
extern int * sda;

// Name der Datei als Global-Variablen definieren
extern char *filename;

// Frame Pointer als Global-Variablen initialisieren
extern int fp;

// Laden von Progamm zu Programm-Speicher
void load(FILE *fp);

// Fuehrt das Programm aus
void runProgram();

#endif