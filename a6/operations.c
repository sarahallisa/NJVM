#include <stdio.h>
#include <stdlib.h>

#include "operations.h"
#include "program.h"
#include "support.h"
#include "bigint.h"

// Methode des Programms
void halt() {
    return;
}

void pushc(int x) {
    bigFromInt(x);
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = bip.res;
    sp++;
}

void add() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    bigAdd();
    stack[sp - 2].u.objRef = bip.res;
    sp--; 
}

void sub() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    bigSub();
    stack[sp - 2].u.objRef = bip.res;
    sp--;
}

void mul() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    bigMul();
    stack[sp - 2].u.objRef = bip.res;
    sp--; 
}

void divide() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    bigDiv();
    stack[sp - 2].u.objRef = bip.res;
    sp--;  
}

void mod() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    bigDiv();
    stack[sp - 2].u.objRef = bip.rem;
    sp--;  
}

void rdint() {
    bigRead(stdin);
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = bip.res;
    sp++;
}

void wrint() {
    bip.op1 = stack[sp - 1].u.objRef;
    bigPrint(stdout);
    sp--;
}

void rdchr() {
    char eingabe;
    scanf("%c", &eingabe);
    pushc((int)eingabe);
}

void wrchr() {
    bip.op1 = stack[sp - 1].u.objRef;
    printf("%c", bigToInt());
    sp--;
}

void pushg(int x) {
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = sda[x];
    sp++;
}

void popg(int x) {
    sda[x] = stack[sp - 1].u.objRef;
    sp--;
}

void asf(int x) {
    stack[sp].isObjRef = false;
    stack[sp].u.number = fp;
    sp++;

    fp = sp;
    sp = sp + x;
}

void rsf() {
    sp = fp;
    fp = stack[fp - 1].u.number;
    sp--;
}

void pushl(int x) {
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = stack[fp + x].u.objRef;
    sp++;
}

void popl(int x) {
    stack[fp + x].isObjRef = true;
    stack[fp + x].u.objRef = stack[sp - 1].u.objRef;
    sp--;
}

void eq() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() == 0) {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 1;
    }
    else {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 0;
    }
    sp++;
}

void ne() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() == 0) {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 1;
    }
    else {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 0;
    }
    sp++;
}

void lt() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() < 0) {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 1;
    }
    else {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 0;
    }
    sp++;
}

void le() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() <= 0) {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 1;
    }
    else {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 0;
    }
    sp++;
}

void gt() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() > 0) {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 1;
    }
    else {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 0;
    }
    sp++;
}

void ge() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() >= 0) {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 1;
    }
    else {
        sp = sp - 2;
        stack[sp].isObjRef = false;
        stack[sp].u.number = 0;
    }
    sp++;
}

void jmp(int x) {
    pc = x;
}

void brf(int x) {
    bip.op1 = stack[sp - 1].u.objRef->data;
    if (bigToInt() == 0) {
        jmp(x);
    }
    sp--;
}

void brt(int x) {
    bip.op1 = stack[sp - 1].u.objRef->data;
    if (bigToInt() == 1) {
        jmp(x);
    }
    sp--;
}

void call(int x) {
    stack[sp].isObjRef = false;
    stack[sp].u.number = pc;
    sp++;
    pc = x;
}

void ret() {
    pc = stack[sp - 1].u.number;
    sp--;
}

void drop(int x) {
    sp = sp - x;
}

void pushr() {
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = rvr;
    sp++;
}

void popr() {
    rvr = stack[sp - 1].u.objRef;
    sp--;
}

void dup() {
    pushc(*(int *)stack[sp - 1].u.objRef->data);
}
