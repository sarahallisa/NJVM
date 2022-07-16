#include <stdio.h>
#include "operations.h"
#include "stacks.h"

// Methode des Programms
void halt() {
    return;
}

void pushc(int x) {
    stack[sp] = x;
    sp++;
}

void add() {
    stack[sp - 2] = stack[sp - 2] + stack[sp - 1];
    sp--; 
}

void sub() {
    stack[sp - 2] = stack[sp - 2] - stack[sp - 1];
    sp--;
}

void mul() {
    stack[sp - 2] = stack[sp - 2] * stack[sp - 1];
    sp--;
}

void divide() {
    stack[sp - 2] = stack[sp - 2] / stack[sp - 1];
    sp--;
}

void mod() {
    stack[sp - 2] = stack[sp - 2] % stack[sp - 1];
    sp--;
}

void rdint() {
    int eingabe;
    scanf("%d", &eingabe);
    stack[sp] = eingabe;
    sp++;
}

void wrint() {
    printf("%d", stack[sp - 1]);
    sp--;
}

void rdchr() {
    char eingabe;
    scanf("%c", &eingabe);
    stack[sp] = eingabe;
    sp++;
}

void wrchr() {
    printf("%c", stack[sp - 1]);
    sp--;
}
