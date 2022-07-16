#include <stdio.h>
#include <stdlib.h>

#include "operations.h"
#include "program.h"
#include "support.h"
#include "bigint.h"
#include "gb.h"

// Methode des Programms

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
    stack[sp - 2].isObjRef = true;
    stack[sp - 2].u.objRef = bip.res;
    sp--; 
}

void sub() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    bigSub();
    stack[sp - 2].isObjRef = true;
    stack[sp - 2].u.objRef = bip.res;
    sp--;
}

void mul() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    bigMul();
    stack[sp - 2].isObjRef = true;
    stack[sp - 2].u.objRef = bip.res;
    sp--; 
}

void divide() {
    if(*(int *)stack[sp - 1].u.objRef->data != 0) {
        bip.op1 = stack[sp - 2].u.objRef;
        bip.op2 = stack[sp - 1].u.objRef;
        bigDiv();
        stack[sp - 2].isObjRef = true;
        stack[sp - 2].u.objRef = bip.res;
        sp--;                   
    } 
}

void mod() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    bigDiv();
    stack[sp - 2].isObjRef = true;
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
    int i = bigToInt();
    printf("%c", i);
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
    /*for (int i = fp; i < sp; i++) {
        stack[i].isObjRef = true;
        stack[i].u.objRef = NULL;
    }*/
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
        bigFromInt(1);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    else {
        sp = sp - 2;
        bigFromInt(0);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    sp++;
}

void ne() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() != 0) {
        sp = sp - 2;
        bigFromInt(1);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    else {
        sp = sp - 2;
        bigFromInt(0);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    sp++;
}

void lt() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() < 0) {
        sp = sp - 2;
        bigFromInt(1);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    else {
        sp = sp - 2;
        bigFromInt(0);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    sp++;
}

void le() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() < 1) {
        sp = sp - 2;
        bigFromInt(1);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    else {
        sp = sp - 2;
        bigFromInt(0);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    sp++;
}

void gt() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() > 0) {
        sp = sp - 2;
        bigFromInt(1);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    else {
        sp = sp - 2;
        bigFromInt(0);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    sp++;
}

void ge() {
    bip.op1 = stack[sp - 2].u.objRef;
    bip.op2 = stack[sp - 1].u.objRef;
    if (bigCmp() > -1) {
        sp = sp - 2;
        bigFromInt(1);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    else {
        sp = sp - 2;
        bigFromInt(0);
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = bip.res;
    }
    sp++;
}

void jmp(int x) {
    pc = x;
}

void brf(int x) {
    bip.op1 = stack[sp - 1].u.objRef;
    if (bigSgn() == 0) {
        pc = x;
    }
    sp--;
}

void brt(int x) {
    bip.op1 = stack[sp - 1].u.objRef;
    if (bigSgn() != 0) {
        pc = x;
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
    //if (stack[sp].isObjRef == true) fatalError("[ret]: error ret, it's a reference");
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
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = stack[sp - 1].u.objRef;
    sp++;
}

void new(int x) {
    ObjRef objRef;
    unsigned int size = sizeof(Object) + (x * sizeof(void *));
    objRef = saveMemory(size);
    for (int i = 0; i < x; i++) {
        GET_REFS(objRef)[i] = NULL;
    }
    objRef->size = x;
    objRef->size |= MSB;
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = objRef;
    sp++;
} 

void getf(int x) {
    ObjRef objRef = stack[sp - 1].u.objRef;
    sp--;
    if(x <= GET_SIZE(objRef) && x >= 0) {
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = GET_REFS(objRef)[x];
        sp++;
    }
}

void putf(int x) {
    ObjRef value = stack[sp - 1].u.objRef;
    GET_REFS(stack[sp - 2].u.objRef)[x] = value;
    sp = sp - 2;
}

void newa() {
    ObjRef value = stack[sp - 1].u.objRef;
    sp--;
    bip.op1 = value;
    int n = bigToInt();
    unsigned int size = sizeof(Object) + (n * sizeof(void *));
    ObjRef objRef = saveMemory(size);
    for (int i = 0; i < n; i++) {
        GET_REFS(objRef)[i] = NULL;
    }
    objRef->size = n;
    objRef->size |= MSB;
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = objRef;
    sp++;
}

void getfa() {
    bip.op1 = stack[sp - 1].u.objRef;
    sp--;
    int index = bigToInt();
    ObjRef array = stack[sp - 1].u.objRef;
    sp--;
    if ((index >= 0) && (index < GET_SIZE(array))) {
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = GET_REFS(array)[index];
        sp++;
    } //else fatalError("[getfa]: wrong index");
}

void putfa() {
    sp--;
    ObjRef value = stack[sp].u.objRef;
    sp--;
    bip.op1 = stack[sp].u.objRef;
    int index = bigToInt();
    sp--;
    ObjRef array = stack[sp].u.objRef;
    if ((index >= 0) && (index < GET_SIZE(array))) {
        GET_REFS(array)[index] = value;
    } //else fatalError("[putfa]: wrong index");
}

void getsz() {
    ObjRef objRef = stack[sp - 1].u.objRef;
    sp--;
    if (IS_PRIM(objRef)) {
        bigFromInt(-1);
    } else {
        bigFromInt(GET_SIZE(objRef));
    }
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = bip.res;
    sp++;
}

void pushn() {
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = NULL;
    sp++;
}

void refeq() {
    ObjRef obj1 = stack[sp - 1].u.objRef;
    sp--;
    ObjRef obj2 = stack[sp - 1].u.objRef;
    sp--;
    if (obj1 == obj2) {
        bigFromInt(1);
    } else bigFromInt(0);
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = bip.res;
    sp++;
}

void refne() {
    ObjRef obj1 = stack[sp - 1].u.objRef;
    sp--;
    ObjRef obj2 = stack[sp - 1].u.objRef;
    sp--;
    if (obj1 != obj2) {
        bigFromInt(1);
    } else bigFromInt(0);
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = bip.res;
    sp++;
}
