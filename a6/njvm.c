#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "program.h"
#include "operations.h"
#include "run.h"
#include "debugger.h"

int main(int argc, char * argv[]) {

    FILE *f;
    char *filename = malloc(sizeof(*filename));

    if (argc > 1) {
        
        if (strcmp(argv[1], "--help") == 0) {
            printf("usage: ./njvm [options] <code file>\n");
            printf("Options:\n");
            printf("  --debug\t\tstart virtual machine in debug mode\n");
            printf("  --version\t\tshow version and exit\n");
            printf("  --help\t\tshow this help and exit\n");
            return 0;
        }

        else if (strcmp(argv[1], "--version") == 0) {
            printf("Ninja Virtual Machinne version 4\n"); // soll das aktuelle Zeit zeigen?
            return 0;
        }

        // Aufruf von Debug ohne Datei
        else if ((strcmp(argv[1], "--debug") == 0) && argv[2] == 0) {
            printf("Error: no code file specified");
            return 0;
        }

        filename = argv[1];  
        f = fopen(filename, "r");
        if (f == NULL) {
            printf("Error: cannot open code file '%s'\n", argv[1]);
            return 0;
        }
        load(f);

        if (argc > 2) {
            // Aufruf von Debug
            if (strcmp(argv[2], "--debug") == 0) {
                debugger = 1;
                printf("%d", debugger);
            }
        }
    }
    else {
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