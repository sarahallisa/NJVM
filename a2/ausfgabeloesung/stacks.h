#ifndef STACKS_H
#define STACKS_H

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

// Frame Pointer als Global-Variablen initialisieren
extern int fp;

#endif