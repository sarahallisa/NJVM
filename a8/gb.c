#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "gb.h"
#include "program.h"
#include "debugger.h"
#include "bigint.h"
#include "operations.h"

bool allocated = false;

// gcpurge
bool gcpurge = false;

// gcstats
bool gcstats = false;

// Zielspeicher
void *zs;
void* zse;

// Quellspeicher
void* qs;
void* qse;

// Freizeiger
void* fz;

// Stack als Global-Variablen initialisieren
StackSlot *stack;
int sp = 0;
int stacksize = 64;

// Heap
void *heap = NULL;
int heapsize = 8192;

void saveStackSize() {
    unsigned int size = stacksize * 1024;
    stack = malloc(size);

    if(gcpurge) {
        memset(stack, 0, size);
    }
}

void saveHeapSize() {
    unsigned int size = heapsize * 1024;
    heap = malloc(size);
    zs = heap;
    zse = heap + (size/2);
    qs = zse;
    qse = heap + (size);

    if(gcpurge) {
        memset(heap, 0, size);
    }

    fz = zs;
}

void garbageCollector() {
    void* newz = qs;
    void* newze = qse;
    
    fz = newz;

    copyroot();

    scan(&newz);

    if (gcpurge) {
        unsigned int size = 1024 * heapsize;
        memset(zs, 0, (size/2));
    }

    qs = zs;
    qse = zse;
    zs = newz;
    zse = newze;

    allocated = false;
    if (gcstats) {

    }
}

ObjRef saveMemory(unsigned int mallocsize) {
    ObjRef pointerOfAllocatedObject;
    if (mallocsize + fz > zse) {
        if (allocated) {
            garbageCollector();
            return saveMemory(mallocsize);
        } else {
            perror("[gc]: heap is full.");
        }
    }

    pointerOfAllocatedObject = fz;
    fz += mallocsize;
    pointerOfAllocatedObject->brokenHeart = false;
    pointerOfAllocatedObject->fopo = NULL;
    allocated = true;
    return pointerOfAllocatedObject;
}

void* copyObjectToFreeMem(ObjRef objRef) {
    void* copyz = fz;
    
    return copyz;
}

void* relocate(ObjRef original) {
    ObjRef copy;
    if (original == NULL) {
        copy = NULL;
    }
    else if (original->brokenHeart) {
        copy = original->fopo;
    } else {
        unsigned long size;
        if (IS_PRIM(original)) {
            size = sizeof(Object) + original->size;
        } else {
            size = sizeof(Object) + (GET_SIZE(original) * sizeof(void*));
        }
        memcpy(fz, original, size);
        copy = fz;
        original->brokenHeart = true;
        original->fopo = fz;
        fz += size;
    }
    return copy;
}

void copyroot() {
    rvr = relocate(rvr);
    for (int i = 0; i < sdac; i++) {
        sda[i] = relocate(sda[i]);
    }
    bip.op1 = relocate(bip.op1);
    bip.op2 = relocate(bip.op2);
    bip.res = relocate(bip.res);
    bip.rem = relocate(bip.rem);
    for (int i = 0; i < sp; i++) {
        if (stack[i].isObjRef) {
            stack[i].u.objRef = relocate(stack[i].u.objRef);
        }
    }
}

void scan(void **newz) {
    void* s = *newz;
    while (s < fz) {
        ObjRef obj = s;
        if (!IS_PRIM(obj)) {
            for (int i = 0; i < GET_SIZE(obj); i++) {
                GET_REFS(obj)[i] = relocate(GET_REFS(obj)[i]);
            }
            s += sizeof(Object) + (GET_SIZE(obj) * sizeof(void *));
        } else {
            s += sizeof(Object) + obj->size;
        }
    }
}
