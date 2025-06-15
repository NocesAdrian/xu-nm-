// ----------- headers ----------- //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

// ----- Creator Defined headers ----- //
#include "HEADERS/fileio.h"


// --------- MAIN ---------- //
int main() {

    StringStorage array;

    fetch_stringf("DATA/src/test.txt", &array, 1500);
    printf("count: %ld\n", array.count);
    print_elements(&array);
    free_array(&array);
    print_elements(&array);
 
    return 0;
}