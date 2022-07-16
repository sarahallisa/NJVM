#ifndef DEBUGGER_H
#define DEBUGGER_H

// Counter der SDA und Programmspeicher fuer Debugger definieren
extern int sdac;
extern int psc;

// Debugger Boolean definieren
extern int debugger;

// Variablen for Debugger definieren
extern int breakpoint;
extern int run;

void debug(unsigned int instruction);

// Listen die Nummer fuer Stack in Debug
void printPointer(int i);

// Listen die Nummer der aktuellen Instruktion
void printNumber(int pc);

#endif
