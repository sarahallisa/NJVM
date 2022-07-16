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

    for (int i = fp; i < fp + x; i++) {
        stack[i].isObjRef = true;
        stack[i].u.objRef = NULL;
    }
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
    if (bigCmp() <= 0) {
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
    if (bigCmp() >= 0) {
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
    int y = bigToInt();
    if (stack[sp].isObjRef == false) fatalError("[brf]: error brf, it's not a reference");
    if (y == 0) {
        jmp(x);
    }
    sp--;
}

void brt(int x) {
    bip.op1 = stack[sp - 1].u.objRef;
    int y = bigToInt();
    if (stack[sp].isObjRef == false) fatalError("[brt]: error brf, it's not a reference");
    if (y != 0) {
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
    if (stack[sp].isObjRef == true) fatalError("[ret]: error ret, it's a reference");
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
    if (stack[sp - 1].isObjRef == true) {
        pushc(*(int *)stack[sp - 1].u.objRef->data);
    }
    else {
        pushc(stack[sp - 1].u.number);
    }  
}

void new(int x) {
    ObjRef *objRef;
    ObjRef record = (ObjRef) malloc(sizeof(unsigned int) + (x * sizeof(objRef)));
    record->size = x | MSB;
    for (int i = 0; i < x; i++) {
        *(GET_REFS(record) + i) = NULL;
    }
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = record;
    sp++;
} 

void getf(int x) {
    ObjRef objRef = stack[sp - 1].u.objRef;
    sp--;
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = *(GET_REFS(objRef) + x);
    sp++;
}

void putf(int x) {
    *(GET_REFS(stack[sp - 2].u.objRef) + x) = stack[sp - 1].u.objRef;
    sp = sp - 2;
}

void newa() {
    ObjRef *objRef;
    bip.op1 = stack[sp - 1].u.objRef;
    sp--;
    ObjRef record = (ObjRef) malloc(sizeof(unsigned int) + (bigToInt() * sizeof(objRef)));
    record->size = bigToInt() | MSB;
    for (int i = 0; i < bigToInt(); i++) {
        *(GET_REFS(record) + i) = NULL;
    }
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = record;
    sp++;
}

void getfa() {
    bip.op1 = stack[sp - 1].u.objRef;
    sp--;
    int index = bigToInt();
    ObjRef array = stack[sp - 1].u.objRef;
    sp--;
    if ((index >= 0) && (index < GET_SIZE(array))) {
        array = GET_REFS(array)[index];
        stack[sp].isObjRef = true;
        stack[sp].u.objRef = array;
        sp++;
    } else fatalError("[putfa]: wrong index");
}

void putfa() {
    ObjRef value = stack[sp - 1].u.objRef;
    sp--;
    bip.op1 = stack[sp - 1].u.objRef;
    sp--;
    ObjRef array = stack[sp - 1].u.objRef;
    sp--;
    int index = bigToInt();
    if ((index >= 0) && (index < GET_SIZE(array))) {
        GET_REFS(array)[index] = value;
    } else fatalError("[putfa]: wrong index");
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
    int x = 0;
    ObjRef obj1 = stack[sp - 1].u.objRef;
    sp--;
    ObjRef obj2 = stack[sp - 1].u.objRef;
    sp--;
    if (obj1 == obj2) {
        x = 1;
    } else x = 0;
    stack[sp].isObjRef = false;
    stack[sp].u.number = x;
    sp++;
}

void refne() {
    int x = 1;
    ObjRef obj1 = stack[sp - 1].u.objRef;
    sp--;
    ObjRef obj2 = stack[sp - 1].u.objRef;
    sp--;
    if (obj1 == obj2) {
        x = 0;
    } else x = 1;
    stack[sp].isObjRef = false;
    stack[sp].u.number = x;
    sp++;
}
