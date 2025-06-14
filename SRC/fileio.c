#include "../INCLUDE/fileio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

// ------ DECLARE STRUCT ONCE ------ //
storage array;

int fetch_stringf(const char *filename) {

    FILE *fp = fopen(filename, "r");
    if(!fp) return 1;
    
    array.capacity = 128;
    array.elements = (char **)malloc(array.capacity * sizeof(char *));

    fclose(fp);
    return 0;
}


