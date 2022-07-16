#include <stdio.h>
#include "run.h"
#include "operations.h"

// Intrepeter zum Listen des Programms
void executeText(unsigned int instruction) {
    int opcode;
    int immediate;

    opcode = instruction >> 24;
    immediate = SIGN_EXTEND(instruction & 0x00FFFFFF);

    if (opcode == HALT) {
        printf("halt\n");
    }
    if (opcode == PUSHC) {
        printf("pushc\t%d\n", immediate);
    }
    if (opcode == ADD) {
        printf("add\n");
    }
    if (opcode == SUB) {
        printf("sub\n");
    }
    if (opcode == MUL) {
        printf("mul\n");
    }
    if (opcode == DIV) {
        printf("div\n");
    }
    if (opcode == MOD) {
        printf("mod\n");
    }
    if (opcode == RDINT) {
        printf("rdint\n");
    }
    if (opcode == WRINT) {
        printf("wrint\n");
    }
    if (opcode == RDCHR) {
        printf("rdchr\n");
    }
    if (opcode == WRCHR) {
        printf("wrchr\n");
    }
}

// Intrepeter zur eigentlichen Ausfuehrung
void execute(unsigned int instruction) {
    int opcode;
    int immediate;

    opcode = instruction >> 24;
    immediate = SIGN_EXTEND(instruction & 0x00FFFFFF);

    if (opcode == PUSHC) {
        pushc(immediate);
    }
    if (opcode == ADD) {
        add();
    }
    if (opcode == SUB) {
        sub();
    }
    if (opcode == MUL) {
        mul();
    }
    if (opcode == DIV) {
        divide();
    }
    if (opcode == MOD) {
        mod();
    }
    if (opcode == RDINT) {
        rdint();
    }
    if (opcode == WRINT) {
        wrint();
    }
    if (opcode == RDCHR) {
        rdchr();
    }
    if (opcode == WRCHR) {
        wrchr();
    }
}