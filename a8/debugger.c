#include <stdio.h>
#include <string.h>

#include "debugger.h"
#include "run.h"
#include "program.h"
#include "operations.h"
#include "bigint.h"
#include "gb.h"

// Counter der SDA und Programmspeicher fuer Debugger definieren
int sdac;
int psc;

// Debugger Boolean definieren
int debugger = 0;

// Variablen for Debugger definieren
int breakpoint = -1;
int run = 0;

void debug(unsigned int instruction) {    
    while (run == 0) {

        printNumber(pc - 1);
        executeText(instruction);
        //execute(instruction);
        printf("DEBUG: inspect, list, breakpoint, step, run, quit?\n");
        char c[10] = "";
        scanf("%s", c);

        if (strcmp(c, "inspect") == 0) {
            printf("DEBUG [inspect]: stack, data, object?\n");
            scanf("%s", c);

            if (strcmp(c, "stack") == 0) {
                int k = sp;
                while (k >= 0) {
                    printPointer(k);
                    k--;
                }
		        printf("\t---------- End of Stack -----------\n");
            }
            else if (strcmp(c, "data") == 0) {
                int i = 0;
                while (i < sdac) {
                    printf("data[000%d]:\t%d\n", i, *(int *) sda[i]);
                    i++;
                }
                printf("\t--- end of data ---\n");
           }
           else if (strcmp(c, "object") == 0) {
               int *address;
               ObjRef objAddress;

               printf("DEBUG [object]: object reference?\n");
               scanf("%p", (void**)&address);
               objAddress = (ObjRef) address;

               if (IS_PRIM(objAddress)) {
                   printf("<primitive object>\n");
                   bip.op1 = objAddress;
                   printf("value = ");
                   bigPrint(stdout);
                   printf("\n");
               }
               else {
                   printf("<compound object>\n");
                   for (int i = 0; i < GET_SIZE(objAddress); i++) {
                       printf("field[%i] = %p\n", i, (void*)*(GET_REFS(objAddress) + i));
                   }
               }
           }
        }
        else if (strcmp(c, "list") == 0) {
            int temp = pc;
            pc = 0;
            while (1) {
                instruction = programmspeicher[pc];
                printNumber(pc);
                executeText(instruction);
                pc++;
                if (instruction >> 24 == HALT) break;
            }
            pc = temp;
            printf("\t--- end of code ---\n");
        }
        else if (strcmp(c, "breakpoint") == 0) {
            if (breakpoint == -1) printf("DEBUG [breakpoint]: cleared\n");
            else printf("DEBUG [breakpoint]: set at %d\n", breakpoint);
            printf("DEBUG [breakpoint]: address to set, -1 to clear, <ret> for no change?\n");
            
            int temp = breakpoint;
            if (scanf("%d", &temp) == 1) {
                if (temp == -1) {
                    breakpoint = -1;
                    printf("DEBUG [breakpoint]: now cleared\n");
                }
                else {
                    breakpoint = temp;
                    printf("DEBUG [breakpoint]: now set at %d\n", temp);
                }
            }
        }
        else if (strcmp(c, "s") == 0) {
            execute(instruction);
            break;
        }
        else if (strcmp(c, "run") == 0) {
            run = 1;
            break;
        }
        else if (strcmp(c, "quit") == 0) {
            debugger = 2;
            break;
        }
    }

    if(run == 1) {
        execute(instruction);
    }
    if(breakpoint == pc) {
        run = 0;
    }
}

// Listen die Nummer fuer Stack in Debug
void printPointer(int i) {
    if (sp == fp) {
        printf("sp, fp\t--->\t");
        printNumber(sp);
        printf("(xxxxxx) xxxxxx\n");
    }
    else if (sp == i) {
        printf("sp\t--->\t");
        printNumber(sp);
        printf("(xxxxxx) xxxxxx\n");
    }
    else if (fp == i) {
        printf("fp\t--->\t");
        printNumber(i);
        if (stack[i].isObjRef == true) {
            if (stack[i].u.objRef == NULL) {
                printf("(objref) nil\n");
            } 
            else {
                printf("(objref) %p\n", (void*)stack[i].u.objRef);
            }
        } 
        else {
            printf("(number) %i\n", stack[i].u.number);
        }
    }
    else if (stack[i].isObjRef == true) {
        printf("\t\t");
        printNumber(i);
        if (stack[i].u.objRef == NULL) {
            printf("(objref) nil\n");
        }
        else {
            printf("(objref) %p\n", (void*)stack[i].u.objRef);
        }
    }
    else {
        printf("\t\t");
        printNumber(i);
        printf("(number) %i\n", stack[i].u.number);
    }
}

// Listen die Nummer der aktuellen Instruktion
void printNumber(int pc) {
    if (pc < 10) {
        printf("000%d:\t", pc);
    }
    else if (pc < 100) {
        printf("00%d:\t", pc);
    }
    else if (pc < 1000) {
        printf("0%d:\t", pc);
    }
    else {
        printf("%d:\t", pc);
    }
}