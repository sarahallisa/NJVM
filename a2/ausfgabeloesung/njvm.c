#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stacks.h"
#include "operations.h"
#include "run.h"

// Laden von Progamm zu Programm-Speicher
void load(FILE *fp) {
    char c[4];
    int version = 2;

    // Verify the format identifier
    fread(c, 1, 4, fp);
    if (c[0] != 'N' && c[1] != 'J' && c[2] != 'B' && c[3] != 'F') {
        printf("Format Identifier Error.");
    } 
            
    // Verify the current VM's version number
    fread(c, 1, 4, fp);
    int checkVersion = c[0];
    if (checkVersion != version) {
        printf("Version Error.");
    }
            
    // Read number of instructions
    fread(&pc, 1, 4, fp);
    pc = SIGN_EXTEND(pc & 0x00FFFFFF);
    // Allocate memory to hold exactly this many instructions
    programmspeicher = malloc(MAX*sizeof(unsigned int));
            
    // Read the number of variables in the static data area
    fread(&pc, 1, 4, fp);
    pc = SIGN_EXTEND(pc & 0x00FFFFFF);
    // Allocate memory to hold exactly this many variables
    sda = malloc(MAX*sizeof(int));

    pc = 0;
    unsigned int n;
    while((fread(&n, sizeof(unsigned int), 1, fp)) != 0) {
        programmspeicher[pc] = n;
        pc++;
    }
            
    pc = 0;
    fp = 0;  
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

    FILE *fp;

    if (argc > 1) {
        // Aufruf von Code 1
        if (strcmp(argv[1], "prog1") == 0) {  
            fp = fopen("./prog1.bin", "r");
            load(fp);
        }

        // Aufruf von Code 2
        else if (strcmp(argv[1], "prog2") == 0) {
            fp = fopen("./prog2.bin", "r");
            load(fp);
        }

        // Aufruf von Code 3
        else if (strcmp(argv[1], "prog3") == 0) {
            fp = fopen("./prog3.bin", "r");
            load(fp);
        }

        // Aufruf von Code 4
        else if (strcmp(argv[1], "prog4") == 0) {
            fp = fopen("./prog4.bin", "r");
            load(fp);
        }

        // Aufruf von Code 5
        else if (strcmp(argv[1], "prog5") == 0) {
            fp = fopen("./prog5.bin", "r");
            load(fp);
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