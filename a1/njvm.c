#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stacks.h"
#include "operations.h"
#include "run.h"
#include "programs.h"

// Laden von Progamm zu Programm-Speicher
void load(unsigned int * prog) {
    programmspeicher = malloc(MAX*sizeof(unsigned int));
    pc = 0;
    while(1) {
        programmspeicher[pc] = prog[pc];
        pc++;
        if(prog[pc] >> 24 == HALT) break;
    }
}

// Fuehrt das Programm aus
void runProgram() {
    unsigned int instruction;
    pc = 0;

    while (1) {
        instruction = programmspeicher[pc];

        if (pc < 10) {
            printf("00%d:\t", pc);
        }
        else if (pc > 9) {
            printf("0%d:\t", pc);
        }

        executeText(instruction);
        pc++;

        if (instruction >> 24 == HALT) break;
    }

    pc = 0;

    while (1) {
        instruction = programmspeicher[pc];
        pc++;
        execute(instruction);
        
        if (instruction >> 24 == HALT) break;
    }
}

int main(int argc, char * argv[]) {
    
    printf("Ninja Virtual Machine started\n");

    if (argc > 1) {
        // Aufruf von Code 1
        if (strcmp(argv[1], "prog1") == 0) {
            load(prog1);
        }

        // Aufruf von Code 2
        else if (strcmp(argv[1], "prog2") == 0) {
            load(prog2);
        }

        // Aufruf von Code 3
        else if (strcmp(argv[1], "prog3") == 0) {
            load(prog3);
        }

        else if (strcmp(argv[1], "--help") == 0) {
            printf("usage: ./njvm [option] [option] ...\n");
            printf("\t--version\t\tshow version and exit\n");
            printf("\t--help\t\t\tshow this help and exit\n");
            return 0;
        }

        else if (strcmp(argv[1], "--version") == 0) {
            printf("Ninja Virtual Machinne version 0\n"); // soll das aktuelle Zeit zeigen?
            return 0;
        }

        else {
            printf("unkown command line argument '%s', try '.njvm --help\n", argv[1]);
            return 0;
        }

        runProgram();
    }

    printf("Ninja Virtual Machine stopped\n");
    
    return 0;
}