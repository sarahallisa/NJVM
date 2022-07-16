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
#define PUSHG 11
#define POPG 12
#define ASF 13
#define RSF 14
#define PUSHL 15
#define POPL 16
#define EQ 17
#define NE 18
#define LT 19
#define LE 20
#define GT 21
#define GE 22
#define JMP 23
#define BRF 24
#define BRT 25
#define CALL 26
#define RET 27
#define DROP 28
#define PUSHR 29
#define POPR 30
#define DUP 31
#define NEW 32
#define GETF 33
#define PUTF 34
#define NEWA 35
#define GETFA 36
#define PUTFA 37
#define GETSZ 38
#define PUSHN 39
#define REFEQ 40
#define REFNE 41

// Zum Bestimmen, ob das Objekt ein primitives Objekt ist
#define MSB (1 << (8 * sizeof(unsigned int) - 1))
#define IS_PRIM(objRef) (((objRef)->size & MSB) == 0)

// Anzahl die Objektreferenzen, die das Objekt beinhaltet
#define GET_SIZE(objRef) ((objRef)->size & ~MSB)

// Berechne einen Zeiger auf die erste Objektreferenzen in Objekt
#define GET_REFS(objRef) ((ObjRef*)(objRef)->data)

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

void pushg(int x);

void popg(int x);

void asf(int x);

void rsf();

void pushl(int x);

void popl(int x);

void eq();

void ne();

void lt();

void le();

void gt();

void ge();

void jmp(int x);

void brf(int x);

void brt(int x);

void call(int x);

void ret();

void drop(int x);

void pushr();

void popr();

void dup();

void new(int x);

void getf(int x);

void putf(int x);

void newa();

void getfa();

void putfa();

void getsz();

void pushn();

void refeq();

void refne();

#endif
