#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdbool.h>
#include "support.h"

// Maximal Stack-Anzahl definieren
#define MAX 10000

#define ISBROKENHEART(objRef) (((objRef)->size & (1<<(8*sizeof(int)-2))) != 0)
#define SETBROKENHEART(objRef) (((objRef)->size) |= (1<<(8*sizeof(int)-2)))

// Objektreferenzen
typedef struct ObjRef {
    unsigned int size; // byte count of payload data
    struct ObjRef* fopo;   // forwardpointer
    bool brokenHeart;    // brokenheart
    unsigned char data[1]; // payload data, size as needed
} Object;

typedef Object* ObjRef;

// Stack
typedef struct {
    bool isObjRef; // slot used for object reference?
    union {
        ObjRef objRef; // used if isObjRef = TRUE
        int number; // used if isObjRef = FALSE
    } u;
} StackSlot;

// Programmspeicher als Global-Variablen definieren
extern unsigned int * programmspeicher;

// Programmcounter als Global-Variablen definieren
extern int pc;

// Static Data Area als Global-Variablen definieren
extern ObjRef * sda;

// Name der Datei als Global-Variablen definieren
extern char *filename;

// Frame Pointer als Global-Variablen initialisieren
extern int fp;

// Return-Value-Register als Global-Variablen definieren
extern ObjRef rvr;

// Laden von Progamm zu Programm-Speicher
void load(FILE *fp);

// Fuehrt das Programm aus
void runProgram();

#endif