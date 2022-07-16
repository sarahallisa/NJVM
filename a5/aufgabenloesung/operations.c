#include <stdio.h>
#include <stdlib.h>

#include "operations.h"
#include "program.h"

// Methode des Programms
void halt() {
    return;
}

void pushc(int x) {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    *(int *)obj->data = x;
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = obj;
    sp++;
}

void add() {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    int c = a + b;
    *(int *)obj->data = c;
    stack[sp - 2].isObjRef = true;
    stack[sp - 2].u.objRef = obj;
    sp--; 
}

void sub() {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    int c = a - b;
    *(int *)obj->data = c;
    stack[sp - 2].isObjRef = true;
    stack[sp - 2].u.objRef = obj;
    sp--; 
}

void mul() {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    int c = a * b;
    *(int *)obj->data = c;
    stack[sp - 2].isObjRef = true;
    stack[sp - 2].u.objRef = obj;
    sp--;  
}

void divide() {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    int c = a / b;
    *(int *)obj->data = c;
    stack[sp - 2].isObjRef = true;
    stack[sp - 2].u.objRef = obj;
    sp--; 
}

void mod() {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    int c = a % b;
    *(int *)obj->data = c;
    stack[sp - 2].isObjRef = true;
    stack[sp - 2].u.objRef = obj;
    sp--;  
}

void rdint() {
    int eingabe;
    scanf("%d", &eingabe);
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    *(int *)obj->data = eingabe;
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = obj;
    sp++;
}

void wrint() {
    int a = *(int *)stack[sp - 1].u.objRef->data;
    printf("%d", a);
    sp--;
}

void rdchr() {
    char eingabe;
    scanf("%c", &eingabe);
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(char));
    obj->size = sizeof(char);
    *(char *) obj->data = eingabe;
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = obj;
    sp++;
}

void wrchr() {
    char a = *(char *)stack[sp - 1].u.objRef->data;
    printf("%c", a);
    sp--;
}

void pushg(int x) {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    int a = *(int *) sda[x].ObjRef->data;
    *(int *)obj->data = a;
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = obj;
    sp++;
}

void popg(int x) {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    int a = *(int *)stack[sp - 1].u.objRef->data;
    *(int *)obj->data = a;
    sda[x].ObjRef = obj;
    sp--;
}

void asf(int x) {
    //pushc(fp);
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    *(int *)obj->data = fp;
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = obj;
    sp++;

    fp = sp;
    sp = sp + x;
}

void rsf() {
    int a = *(int *)stack[fp - 1].u.objRef->data;
    sp = fp;
    fp = a;
    sp--;
}

void pushl(int x) {
    int a = *(int *)stack[fp + x].u.objRef->data;
    pushc(a);
}

void popl(int x) {
    stack[fp + x].isObjRef = true;
    int a = *(int *)stack[sp - 1].u.objRef->data;
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    *(int *)obj->data = a;
    stack[fp + x].u.objRef = obj;
    sp--;
}

void eq() {
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    if (a == b) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void ne() {
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    if (a != b) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void lt() {
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    if (a < b) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void le() {
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    if (a <= b) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void gt() {
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    if (a > b) {
        sp = sp - 2;
        pushc(1);
    }
    else {
        sp = sp - 2;
        pushc(0);
    }
}

void ge() {
    int a = *(int *)stack[sp - 2].u.objRef->data;
    int b = *(int *)stack[sp - 1].u.objRef->data;
    if (a >= b) {
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
    int a = *(int *)stack[sp - 1].u.objRef->data;
    if (a == 0) {
        jmp(x);
    }
    sp--;
}

void brt(int x) {
    int a = *(int *)stack[sp - 1].u.objRef->data;
    if (a == 1) {
        jmp(x);
    }
    sp--;
}

void call(int x) {
    //pushc(pc);

    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    *(int *)obj->data = pc;
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = obj;
    sp++;

    pc = x;
}

void ret() {
    pc = *(int *)stack[sp - 1].u.objRef->data;
    sp--;
}

void drop(int x) {
    sp = sp - x;
}

void pushr() {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    int a = *(int *)rvr.ObjRef->data;
    *(int *)obj->data = a;
    stack[sp].isObjRef = true;
    stack[sp].u.objRef = obj;
    sp++;
}

void popr() {
    ObjRef obj = malloc(sizeof(unsigned int) + sizeof(int));
    obj->size = sizeof(int);
    int a = *(int *)stack[sp - 1].u.objRef->data;
    *(int *)obj->data = a;
    rvr.ObjRef = obj;
    sp--;
}

void dup() {
    pushc(*(int *)stack[sp - 1].u.objRef->data);
}
