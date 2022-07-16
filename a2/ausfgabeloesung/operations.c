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

void pushg(int x) {
    stack[sp] = sda[x];
    sp++;
}

void popg(int x) {
    sda[x] = stack[sp - 1];
    sp--;
}

void asf(int x) {
    pushc(fp);
    fp = sp;
    sp = sp + x;
}

void rsf() {
    fp = stack[fp - 1];
    sp--;
}

void pushl(int x) {
    pushc(stack[fp + x]);
}

void popl(int x) {
    stack[fp + x] = stack[sp - 1];
    sp--;
}
