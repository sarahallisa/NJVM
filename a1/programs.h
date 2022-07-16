#ifndef PROGRAMS_H
#define PROGRAMS_H

unsigned int prog1[] = {
    (PUSHC << 24) | IMMEDIATE(3),
    (PUSHC << 24) | IMMEDIATE(4),
    (ADD << 24),
    (PUSHC << 24) | IMMEDIATE(10),
    (PUSHC << 24) | IMMEDIATE(6),
    (SUB << 24), 
    (MUL << 24), 
    (WRINT << 24),
    (PUSHC << 24) | IMMEDIATE(10),
    (WRCHR << 24), (HALT << 24)
};

unsigned int prog2[] = {
    (PUSHC << 24) | IMMEDIATE(-2),
    (RDINT << 24), (MUL << 24),
    (PUSHC << 24) | IMMEDIATE(3),
    (ADD << 24), (WRINT << 24),
    (PUSHC << 24) | IMMEDIATE('\n'),
    (WRCHR << 24), (HALT << 24)
};

unsigned int prog3[] = {
    (RDCHR << 24), (WRINT << 24),
    (PUSHC << 24) | IMMEDIATE('\n'),
    (WRCHR << 24), (HALT << 24)
};

#endif