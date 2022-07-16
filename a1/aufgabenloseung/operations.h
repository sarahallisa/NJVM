#ifndef OPERATIONS_H
#define OPERATIONS_H

// Das Kodieren des Immediate-Wertes definieren
#define IMMEDIATE(x) ((x) & 0x00FFFFFF)

// Verwendung von Makro, weil der Immediate-Wert auch negativ sein kann
#define SIGN_EXTEND(i) ((i) & 0x00800000 ? (i) | 0xFF000000 : (i))

// Die Opcodes definieren
#define HALT 0
#define PUSHC 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6
#define RDINT 7
#define WRINT 8
#define RDCHR 9
#define WRCHR 10

// Methode des Programms
void halt();

void pushc(int x);

void add();

void sub();

void mul();

void divide();

void mod();

void rdint();

void wrint();

void rdchr();

void wrchr();

#endif
