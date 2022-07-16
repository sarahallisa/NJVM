#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "program.h"
#include "operations.h"
#include "run.h"
#include "debugger.h"
#include "gb.h"

int main(int argc, char * argv[]) {

    FILE *f = NULL;
    char *filename = malloc(sizeof(*filename));

    if (argc > 1) {
        int i;
        for (i = 1; i < argc; i++) {
            if(argv[i][0] == '-' && argv[i][1] == '-') {
                if (strcmp(argv[i], "--help") == 0) {
                    printf("usage: ./njvm [options] <code file>\n");
                    printf("Options:\n");
                    printf("  --debug\t\tstart virtual machine in debug mode\n");
                    printf("  --version\t\tshow version and exit\n");
                    printf("  --help\t\tshow this help and exit\n");
                    return 0;
                }
                else if (strcmp(argv[i], "--version") == 0) {
                    printf("Ninja Virtual Machinne version 7\n"); // soll die aktuelle Zeit zeigen?
                    return 0;
                }   
                else if(strcmp(argv[i], "--stack") == 0)     {
                    i = i + 1;
                    char *ptr;
                    stacksize = strtol(argv[i], &ptr, 10);
                }   
                else if(strcmp(argv[i], "--heap") == 0) {
                    i = i + 1;
                    char *ptr;
                    heapsize = strtol(argv[i], &ptr, 10);
                }     
                else if (strcmp(argv[i], "--gcpurge") == 0) {
                    gcpurge = true;
                } 
                else if (strcmp(argv[i], "--gcstats") == 0) {
                    gcstats = true;
                }
                else if (strcmp(argv[i], "--debug") == 0) {
                    debugger = 1;
                }
            }
            else {
                filename = argv[i];
                f = fopen(filename, "r");
                if (f == NULL) {
                    printf("Error: cannot open code file '%s'\n", filename);
                    return 0;
                }
                load(f);
            }
        }
    }

    if(f == NULL) {
        printf("Error: no code file specified");
        return 0;
    }

    if(debugger == 1) {
        printf("DEBUG: file '%s' loaded (coded size = %d, data size = %d)\n", filename, psc, sdac); 
    }

    printf("Ninja Virtual Machine started\n");
    runProgram();
    printf("Ninja Virtual Machine stopped\n");
    
    return 0;
}