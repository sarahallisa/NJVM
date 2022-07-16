#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program.h"
#include "operations.h"
#include "run.h"
#include "debugger.h"
#include "gb.h"

// Programmspeicher als Global-Variablen initialisieren
unsigned int * programmspeicher;

// Programmcounter als Global-Variablen definieren
int pc;

// Static Data Area als Global-Variablen definieren
ObjRef *sda;

// Frame Pointer als Global-Variablen initialisieren
int fp = 0; 

// Return-Value-Register als Global-Variablen definieren
ObjRef rvr;

// Laden von Progamm zu Programm-Speicher
void load(FILE *f) {
    char c[4];
    int version = 8;

    // Verify the format identifier
    fread(c, 1, 4, f);
    if (c[0] != 'N' && c[1] != 'J' && c[2] != 'B' && c[3] != 'F') {
        printf("Format Identifier Error.\n");
    } 
            
    // Verify the current VM's version number
    fread(c, 1, 4, f);
    int checkVersion = c[0];
    if (checkVersion != version) {
        printf("Version Error.\n");
    }
            
    // Read number of instructions
    unsigned int x;
    fread(&x, 1, 4, f);
    psc = SIGN_EXTEND(IMMEDIATE(x));
    // Allocate memory to hold exactly this many instructions
    programmspeicher = malloc(psc*sizeof(unsigned int));
            
    // Read the number of variables in the static data area
    fread(&x, 1, 4, f);
    sdac = SIGN_EXTEND(IMMEDIATE(x));
    // Allocate memory to hold exactly this many variables
    sda = malloc(sdac*sizeof(int));

    pc = 0;
    unsigned int n;
    while((fread(&n, sizeof(unsigned int), 1, f)) != 0) {
        programmspeicher[pc] = n;
        pc++;
    }

    pc = 0;
    sp = 0;
    fp = 0;
    fclose(f);  
}

// Fuehrt das Programm aus
void runProgram() {
    unsigned int instruction;

    pc = 0;

    saveStackSize();
    saveHeapSize(); 

    while (1) {
        instruction = programmspeicher[pc];

        pc++;

        if (debugger == 1) {
            debug(instruction); printf("%d", debugger);}
        else execute(instruction);
        if (instruction >> 24 == HALT || debugger == 2) break;
    }
}
