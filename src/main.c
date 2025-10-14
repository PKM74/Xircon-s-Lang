#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define version "RD-00001"

int main(int argC, char *argV[])
{
    if(argC != 1) {
        for( int i=1; i < argC; i++) {
            if (strcmp(argV[i], "-v") == false) { printf("Xircon's Lang Compilier %s\n", version); return false;}
        }

    } else {
        printf("Usage: %s [OPTIONS] [SERVER] [PORT]\n", argV[0]);
        return true;
    }
}