#include <stdio.h>
#include "operations.h"
#include "program.h"

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

void eq() {
    if (stack[sp - 2] == stack[sp - 1]) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void ne() {
    if (stack[sp - 2] != stack[sp - 1]) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void lt() {
    if (stack[sp - 2] < stack[sp - 1]) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void le() {
    if (stack[sp - 2] <= stack[sp - 1]) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void gt() {
    if (stack[sp - 2] > stack[sp - 1]) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void ge() {
    if (stack[sp - 2] >= stack[sp - 1]) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void jmp(int x) {
    pc = x;
}

void brf(int x) {
    if (stack[sp - 1] == 0) {
        jmp(x);
    }
    sp--;
}

void brt(int x) {
    if (stack[sp - 1] == 1) {
        jmp(x);
    }
    sp--;
}
