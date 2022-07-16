#ifndef GB_H
#define GB_H

#include "program.h"

// Stack als Global-Variablen definieren
extern StackSlot *stack;
extern int sp;
extern int stacksize;
extern void saveStackSize();

// Heap
extern void* heap;
extern int heapsize;
extern void saveHeapSize();

extern void *fz;

// gcpurge
extern bool gcpurge;

// gcstats
extern bool gcstats;

// Garbage Collector
extern void garbageCollector();

// Speicherallokation
extern ObjRef saveMemory(unsigned int mallocsize);

// Kopiert Objekt auf FreeMemory
void* copyObjectToFreeMem(ObjRef obj);

// Relocate Objekt
void* relocate(ObjRef original);

// Kopiert Objekt aus Register und Stack
void copyroot();

// Scannt die Zeiger
void scan();

#endif