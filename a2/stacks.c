#include "stacks.h"

// Stack als Global-Variablen initialisieren
int stack[MAX];
int sp = 0;

// Programmspeicher als Global-Variablen initialisieren
unsigned int * programmspeicher;

// Programmcounter als Global-Variablen definieren
int pc;

// Static Data Area als Global-Variablen definieren
int * sda;

// Frame Pointer als Global-Variablen initialisieren
int fp = 0; 

